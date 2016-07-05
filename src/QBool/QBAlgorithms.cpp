#include "QBool/QBAlgorithms.h"
#include "QBool/QBExpr.h"
#include "QBool/QBManager.h"
#include "QBool/QBAnd.h"
#include "QBool/QBOr.h"
#include "QBool/QBNot.h"
#include "QBool/QBFunc.h"
extern "C" {
#include "picosat.h"
}
#include <atomic>
#include <fstream>
#include <iostream>
#include <string>
#include <stack>
#include <tuple>
#include <map>
#include <sstream>
#include <cassert>
#include <unistd.h>
#include <mutex>

using std::string;
using std::stack;
using std::tuple;
using std::vector;
namespace QuickMath {
namespace QBAlgo {

bool isInvVar(const QBType* expr) {
    if(expr->isNot())
        return static_cast<const QBNot*>(expr)->begin()->get()->isVar();
    return false;
}


QBFunc generateCNF(const QBFunc& func, QBManager& bMan) {
    if(!func.get()->isExpr())
        return func;
    QBFunc CNF(true);
    stack<tuple<const QBExpr*, QBFunc>> ptrs;
    QBFunc topLevelTemp = bMan.getTempVar();
    ptrs.push(std::make_tuple(dynamic_cast<const QBExpr*>(func.get()),
                                topLevelTemp));
    QBFunc topVar = std::get<1>(ptrs.top());
    while(!ptrs.empty())
    {
        tuple<const QBExpr*, QBFunc> parent = ptrs.top();
        ptrs.pop();

        const QBExpr* expr = std::get<0>(parent);
        QBFunc tempVar(std::get<1>(parent));
        assert(expr);

        vector<QBFunc> operands;
        for(auto &op:*expr)
        {

            if(op->isExpr() && !isInvVar(op.get()))
            {
                const QBExpr* opExpr = dynamic_cast<const QBExpr*>(op.get());
                QBFunc bit = bMan.getTempVar();
                ptrs.push(std::make_tuple(opExpr, bit));
                operands.push_back(bit);
            }
            else
                operands.push_back(QBFunc(op.get()));

        }

        // Process Operands
        if(expr->isAnd())
        {
            QBFunc term(false);
            for(auto &op:operands)
                CNF &= !tempVar | op;
            for(auto &op:operands)
                term |= !op;
            CNF &= term | tempVar;
        }
        else if(expr->isOr())
        {
            QBFunc term(false);
            for(auto &op:operands)
                CNF &= tempVar | !QBFunc(op.get());

            for(auto &op:operands)
                term |= op;
            CNF &= term | !tempVar;
        }
        else if(expr->isNot())
        {
            CNF &= (!tempVar | !operands.front()) &
                   (tempVar | operands.front());
        }
        else
            throw std::runtime_error("Unknown expression type for CNF generation");
    }
    return std::move(std::move(CNF) & std::move(topVar));
}

bool isCNFOrTerm(const QBOr* expr) {
    for(auto &literal:*expr)
    {
        if((literal->isNot() && !isInvVar(static_cast<const QBNot*>(literal.get()))) ||
          (!literal->isNot() && !literal->isVar()))
            return false;
    }
    return true;
}

bool isCNF(const QBFunc &func) {
    if(!func.isExpr())
        return false;
    if(func.get()->isOr())
       return isCNFOrTerm(static_cast<const QBOr*>(func.get()));
    else if(!func.get()->isAnd())
       return false;

    const QBAnd* ptr = static_cast<const QBAnd*>(func.get());
    for(auto &op:*ptr)
    {
        if(op->isOr() && !isCNFOrTerm(static_cast<const QBOr*>(op.get())))
            return false;
        else if(op->isNot() && !isInvVar(static_cast<const QBNot*>(op.get())))
            return false;
    }
    return true;
}

struct QBBitCmp{
    bool operator()(const QBBit* a, const QBBit *b)
    {
        int cmpResult = a->getName().compare(b->getName());
        return (cmpResult < 0) ||
               ((cmpResult == 0) && (a->getIndex() < b->getIndex()));
    }
};

// Should Be Dimacs Compatiable, a Zero Should be Placed at the end of Each Clause
vector<int> runPicoSat(const std::vector<int>& input, int nVars)
{
    static std::mutex picoMutex;

    std::unique_lock<std::mutex> lock(picoMutex); 
    vector<int> resultVec;
    const int decisionLimit = -1;
    auto solver = picosat_init();
    if(nVars >= 0)
        picosat_adjust(solver, nVars);

    for(auto &lit:input)
        picosat_add(solver, lit);
    
    auto result = picosat_sat(solver, decisionLimit);
    if(result == PICOSAT_UNKNOWN)
        throw std::runtime_error("runPicoSat: Unknown Solution v" + std::to_string(nVars));
    else if(result == PICOSAT_SATISFIABLE)
    {
        int nPicoVars = picosat_variables(solver);
        resultVec = std::vector<int>(nPicoVars, 0);
        for(int i = 0; i < nPicoVars; ++i)
            resultVec[i] = picosat_deref(solver, i + 1) * (i + 1);
    }
    picosat_reset(solver);
    return std::move(resultVec);
}


vector<int> runLingelingSat(std::string &&dimacsStr) {
    
    int p2cFD[2];
    int c2pFD[2];

    if(pipe(p2cFD) == -1)
        std::perror("QBAlgorithms.runLinglingSat: Failed to generate p2cFD pipe");

    if(pipe(c2pFD) == -1)
        std::perror("QBAlgorithms.runLinglingSat: Failed to generate c2pFD pipe");

    FILE *fp = popen("which lingeling", "r");

    char path[256];
    if(fgets(path, 256, fp) == nullptr)
        throw std::runtime_error("QBAlgorithms: Failed to get pipe path");
    pclose(fp);
    string filePath = path;


    vector<int> solution;
    // Fork
    if(!fork())
    {
        dup2(c2pFD[1], 1);
        close(c2pFD[0]);
        close(c2pFD[1]);
        dup2(p2cFD[0], 0);
        close(p2cFD[0]);
        close(p2cFD[1]);

        int error = execl((filePath.substr(0,filePath.length() - 1)).c_str(), (filePath.substr(0,filePath.length() - 1)).c_str(), NULL);
        if(error == -1)
            throw std::runtime_error("isSat process error " + std::to_string(error));
    }
    else
    {
        char buffer[256];
        close(p2cFD[0]);
        close(c2pFD[1]);
        if(write(p2cFD[1], dimacsStr.c_str(), dimacsStr.length()) == -1)
            std::perror("QBAlgorithms.runLinglingSat: Failed to write to pipe");

        close(p2cFD[1]);
        FILE *in = fdopen(c2pFD[0], "r");
        while (fgets(buffer, 256, in))
        {
            if(buffer[0] == 's')
            {
                string str(buffer);
                size_t idx = str.find("UNSATISFIABLE");
                if(idx != string::npos)
                    return vector<int>();
            }
            else if(buffer[0] == 'v')
            {
                buffer[0] = ' ';
                std::stringstream ss(buffer);
                int num = 1;
                while(!ss.eof() && num != 0)
                {
                    ss >> num;
                    if(num != 0)
                        solution.push_back(num);
                }
            }
        }
        close(c2pFD[0]);
    }
    return std::move(solution);
}

vector<QBFunc> isSat(const QBFunc& func) {
    // Get Unique Ids for all bits
    std::map<int, const QBBit*> idToBit;
    std::map<int64_t, unsigned int> refToId;
   
    assert(func.get());
    int varNum = 1;


    const QBAnd* andExpr = dynamic_cast<const QBAnd*>(func.get());
    if(!andExpr)
        throw std::runtime_error("IsSat: function is not CNF, expression not and");
    std::stringstream buffer;
    unsigned int nClauses = 0;
    for(auto &term:*andExpr)
    {
        if(term->isVar())
        {
            const QBBit* bit = static_cast<const QBBit*>(term.get());
            auto srchIter = refToId.find(bit->getRef());
            if(srchIter == refToId.end())
            {
                refToId[bit->getRef()] = varNum;
                buffer << varNum << " ";
                idToBit[varNum++] = bit;
            }
            else
                buffer << srchIter->second << " ";
        }
        else if(term->isOr())
        {
            const QBOr* orExpr = static_cast<const QBOr*>(term.get());
            for(auto &op:*orExpr)
            {
                if(op->isExpr())
                {
                    const QBNot* notOp = dynamic_cast<const QBNot*>(op.get());
                    const QBBit* bit = dynamic_cast<const QBBit*>(notOp->begin()->get());
                    auto srchIter = refToId.find(bit->getRef());
                    if(srchIter == refToId.end())
                    {
                        refToId[bit->getRef()] = varNum;
                        buffer << "-" << varNum << " ";
                        idToBit[varNum++] = bit;
                    }
                    else
                        buffer << "-" << srchIter->second << " ";       
                }
                else if(op->isVar())
                {
                    const QBBit* bit = static_cast<const QBBit*>(op.get());
                    auto srchIter = refToId.find(bit->getRef());
                    if(srchIter == refToId.end())
                    {
                        refToId[bit->getRef()] = varNum;
                        buffer << varNum << " ";
                        idToBit[varNum++] = bit;
                    }
                    else
                        buffer << srchIter->second << " ";   
                }
            }
        }
        else
            throw std::runtime_error("QBAlgorithms.isSat: invalid CNF");
        buffer << "0" << std::endl;
        ++nClauses;
    }
    vector<int> idSolution = std::move(runLingelingSat("p cnf " + std::to_string(refToId.size()) + " " +
                            std::to_string(nClauses) + "\n" + buffer.str()));
    vector<QBFunc> solution;
    for(auto id:idSolution)
    {
        if(id < 0)
            solution.push_back(!QBFunc(idToBit[abs(id)]));
        else
            solution.push_back(QBFunc(idToBit[id]));
    }
    return std::move(solution);
}


}
/*
QBFunc QBAlgo::dnfToCnf(const QBFunc& func) {
    auto topOr = dynamic_cast<const QBOr*>(func.get());
    if(!topOr)
        throw std::runtime_error("dnfToCnf: not in DNF form, no top level or");

    auto topAnd = std::unique_ptr<QBAnd>(new QBAnd());
    // There are three possibilites here, and, literal, not
    // Apply Demorgan
    for(auto &expr:topOr)
    {
        if(expr->isAnd())
        {
            auto opExpr = std::unique_ptr<QBOr>(new QBOr());
            for(auto    
        }
        else if(expr->isNot())
        {
        }
        else if(expr->isVar())
        {
        }
        else
            throw std::runtime_error("dnfToCnf: not in DNF form, expected conjunctive term");
    }


}
*/
}



