#include "QBool/QBAlgorithms.h"
#include "QBool/QBExpr.h"
#include "QBool/QBManager.h"
#include "QBool/QBAnd.h"
#include "QBool/QBOr.h"
#include "QBool/QBNot.h"
#include "QBool/QBFunc.h"

#include <iostream>
#include <string>
#include <stack>
#include <tuple>
#include <map>
#include <sstream>
#include <cassert>
#include <unistd.h>

using std::string;
using std::stack;
using std::tuple;
using std::vector;
namespace QuickMath {
namespace QBAlgo {


QBFunc generateCNF(const QBFunc& func, string prefix, QBManager& bMan) {
    if(!func.get()->isExpr())
        return func;
    QBFunc CNF(true);
    unsigned int cnt = 0;
    stack<tuple<const QBExpr*, QBFunc>> ptrs;
    ptrs.push(std::make_tuple(dynamic_cast<const QBExpr*>(func.get()),
                              bMan.getBit(prefix, cnt++)));
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

            if(op->isExpr())
            {
                const QBExpr* opExpr = dynamic_cast<const QBExpr*>(op.get());
                QBFunc bit = bMan.getBit(prefix, cnt++);
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
    return std::move(CNF) & std::move(topVar);
}

bool isCNFNotTerm(const QBNot* expr) {
    return expr->begin()->get()->isVar();
}

bool isCNFOrTerm(const QBOr* expr) {
    for(auto &literal:*expr)
    {
        if((literal->isNot() && !isCNFNotTerm(static_cast<const QBNot*>(literal.get()))) ||
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
        else if(op->isNot() && !isCNFNotTerm(static_cast<const QBNot*>(op.get())))
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
                vector<int> solution;
                buffer[0] = ' ';
                std::stringstream ss(buffer);
                int num = 1;
                while(!ss.eof() && num != 0)
                {
                    ss >> num;
                    if(num != 0)
                        solution.push_back(num);
                }
                return move(solution);
            }
        }
        close(c2pFD[0]);
    }
    return vector<int>();
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
}
