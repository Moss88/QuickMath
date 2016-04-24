#include <cassert>
#include "QBool/QBDimacsFunc.h"
#include "QBool/QBAlgorithms.h"
#include "QBool/QBAnd.h"
#include "QBool/QBOr.h"
#include "QBool/QBNot.h"

namespace QuickMath {
QBDimacsFunc::QBDimacsFunc(const QBFunc& bfunc, const std::vector<std::tuple<std::string, int>>& inputs) 
                                                                                : inputOrder(inputs) {
    refLocs.push_back(std::vector<std::tuple<int,int>>()); // Ref zero is invalid
    setupVarMaps(bfunc);
    setupCNFs(bfunc);
    
}

const std::vector<std::tuple<std::string, int>>& 
QBDimacsFunc::getInputs() const {
    return inputOrder;
}

void QBDimacsFunc::setupVarMaps(const QBFunc& bfunc) {
    int nVecVars = 1;
    for(auto &input:inputOrder)
    {
        int vecSize = std::get<1>(input);
        vecMap[std::get<0>(input)] = std::make_tuple(nVecVars, vecSize);
        nVecVars += vecSize;
    }

    // Get all Temp Vars
    std::map<int, int> tmpMap;
    auto tmpVarCount = [&tmpMap](const QBType* expr) {
        if(expr->isVar())
        {
            auto bit = static_cast<const QBBit*>(expr);
            if(bit->isTempVar())
                tmpMap[bit->getIndex()] = 0;
        }
        return true;
    };
    QBAlgo::depthTraversal(bfunc, tmpVarCount); 
    tmpVars = tmpMap;
    for(auto &mKey:tmpVars)
        mKey.second = nVecVars++;
    refLocs = std::vector<std::vector<std::tuple<int, int>>>(nVecVars);
}


int QBDimacsFunc::getRef(const QBBit* bit) {
    if(bit->isTempVar())
        return tmpVars.at(bit->getIndex());
    else
    {
        std::tuple<int,int>& ref = vecMap.at(bit->getName());
        if(bit->getIndex() >= std::get<1>(ref))
           throw std::runtime_error("QBDimacsFunc: vector outside of range");
        return std::get<0>(ref) + bit->getIndex(); 
    }
}

int QBDimacsFunc::numVars() const {
    return refLocs.size() - 1 - numTmpVars();
}

int QBDimacsFunc::numClauses() const {
    return cnfs.size();
}

int QBDimacsFunc::numTmpVars() const {
    return tmpVars.size();
}

void QBDimacsFunc::insertCNFLiteral(const QBBit* bit, bool positive)
{
    int row = cnfs.size() - 1;
    int col = cnfs.back().size();
    int ref = getRef(bit);
    if(positive)
        cnfs.back().push_back(ref);
    else
        cnfs.back().push_back(-ref);
    refLocs[ref].push_back(std::make_tuple(row, col));
}

void QBDimacsFunc::setupCNFs(const QBFunc& func) {
    const QBAnd* andExpr = dynamic_cast<const QBAnd*>(func.get());
    if(!andExpr)
        throw std::runtime_error("QBDimacs: function is not CNF, expression not and");
    for(auto &term:*andExpr)
    {
        cnfs.push_back(std::vector<int>());
        if(term->isVar())
        {
            const QBBit* bit = static_cast<const QBBit*>(term.get());
            insertCNFLiteral(bit, true);
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
                    insertCNFLiteral(bit, false);       
                }
                else if(op->isVar())
                {
                    const QBBit* bit = static_cast<const QBBit*>(op.get());
                    insertCNFLiteral(bit, true);
                }
            }
        }
        else
            throw std::runtime_error("QBAlgorithms.isSat: invalid CNF");
    }
}


void QBDimacsFunc::cnfsToStream(std::ostream& os, const std::vector<int>& inputIdxs, int tmpVarSIdx) const {
    if(inputIdxs.size() != inputOrder.size())
        throw std::runtime_error("QBDimacsFunc.cnfsToStream: incompatible input size");
   

    std::vector<int> mappingVec(refLocs.size(), 0);
    // Map Vars
    int inputNum = 0;
    for(auto &input:inputOrder)
    {
        int startIdx = inputIdxs[inputNum];
        const std::tuple<int,int>& ref = vecMap.find(std::get<0>(input))->second;
        int orgIdx = std::get<0>(ref);
        for(int i = 0; i < std::get<1>(ref); ++i)
           mappingVec[orgIdx + i] = startIdx + i; 
        inputNum++;
    }
    
    

    // Map Temp Vars
    for(auto &key:tmpVars)
        mappingVec[key.second] = tmpVarSIdx++;
    
    for(auto &cnf:cnfs)
    {
        os << "0 ";
        for(auto &literal:cnf)
        {
            int signMulti = (literal < 0) * -1 + (literal > 0) * 1;
            int idx = signMulti * literal;
            os << signMulti * mappingVec[idx] << " ";
        }
        os << "\n";
    } 
}


}
