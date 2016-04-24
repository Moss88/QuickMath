#include "QBool/QBFuncGen.h"
#include "QBool/QBAlgorithms.h"
namespace QuickMath {

QBFuncGen::QBFuncGen(const QBFunc& func) : func(func) {
    getRefs();
}

QBFuncGen::QBFuncGen(QBFunc&& func) : func(std::move(func)) {
    getRefs();
}

// First String is original -> vector   f(x -> a, y -> b)
QBFunc QBFuncGen::generateFunc(const std::map<std::string, std::string>& varMap,
                                                    QBManager& manager) const {
    for(auto &mKey:vecMap)
    {
        auto srchIter = varMap.find(mKey.first);
        if(srchIter == varMap.end())
            throw std::runtime_error("QBFuncGen.generateFunc: incomplete input map, missing " + mKey.first);
        for(auto &bitRef:mKey.second)
        {
            QBFunc bitFunc = manager.getBit(srchIter->second, bitRef.first);
            auto bit = static_cast<QBBit*>(bitFunc.get());
            for(auto &ref:bitRef.second)
                ref->setShared(bit->getSharedPtr());    
        }
    }

    for(auto &tVar:tmpVars)
    {
        auto newTVar = manager.getTempVar();
        auto bit = static_cast<QBBit*>(newTVar.get());
        for(auto &ref:tVar.second)
            ref->setShared(bit->getSharedPtr());
    }
    return func;
}   

void QBFuncGen::getRefs() {
    auto fetchRef = [this](QBType* type) {
        if(type->isVar()) {
            auto bit = static_cast<QBBit*>(type);
            if(bit->getName() == tmpVarName)
                storeTmpVarRef(bit);
            else
                storeVarRef(bit);
        }
        return true;
    };
    QBAlgo::depthTraversal(*func.get(), fetchRef);    
}

void QBFuncGen::storeTmpVarRef(QBBit* bit) {
    auto idx = bit->getIndex();
    tmpVars[idx].push_back(bit);
}

void QBFuncGen::storeVarRef(QBBit* bit) {
    auto idx = bit->getIndex();
    std::map<int, std::vector<QBBit*>>& bitMap = vecMap[bit->getName()]; 
    bitMap[idx].push_back(bit);
 }



}
