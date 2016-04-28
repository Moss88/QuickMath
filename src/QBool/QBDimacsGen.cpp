#include "QBool/QBDimacsGen.h"
#include "QBool/QBAlgorithms.h"
#include <sstream>
#include <cmath>
namespace QuickMath {

int QBDimacsGen::addVar(const QFVar* var, int size) {
    std::string name = var->toString();
    auto srchIter = varMap.find(name);
    if(srchIter == varMap.end())
    {
        int orgIdx = curIdx;
        curIdx += size;
        varMap[name] = orgIdx;
        refToVar[Range(orgIdx, curIdx - 1)] = *var;
        return orgIdx;
    }
    return srchIter->second;       
}

void QBDimacsGen::addFunction(const QBDimacsFunc* dFunc, 
                              const std::vector<std::tuple<const QFVar*, int>>& vars) {
    if(!validate(dFunc, vars))
        throw std::runtime_error("QBDimacsGen.addFunction: invalid input vector"); 
   
    std::vector<int> mapInput;
    for(auto &var:vars)
    {
        int idx = addVar(std::get<0>(var), std::get<1>(var));
        mapInput.push_back(idx);
    }
    funcs.push_back(std::make_tuple(dFunc, std::move(mapInput), curIdx));
    curIdx += dFunc->numTmpVars();
}

bool QBDimacsGen::validate(const QBDimacsFunc* dFunc, const std::vector<std::tuple<const QFVar*, int>>& vars)
{
    auto& inputVec = dFunc->getInputs();
    if(vars.size() != inputVec.size())
        return false;
    auto inputIter = inputVec.begin();
    auto varIter = vars.begin();
    for( ; inputIter != inputVec.end(); ++inputIter, ++varIter)
        if(std::get<1>(*inputIter) != std::get<1>(*varIter))
            return false;
    return true;
}


std::string QBDimacsGen::getDimacs() const {
    std::stringstream ss;
    ss << "p cnf " << getNumVars() << " " << getNumClauses() << "\n";
    for(auto &func:funcs)
        std::get<0>(func)->cnfsToStream(ss, std::get<1>(func), std::get<2>(func));
    return std::move(ss.str());
}

bool QBDimacsGen::isSat() const {
    return QBAlgo::runLingelingSat(getDimacs()).size() > 0;
}

std::vector<std::tuple<QFVar, unsigned int>> QBDimacsGen::getSat() const {
    auto resultVec = QBAlgo::runLingelingSat(getDimacs());

    std::map<const QFVar*, unsigned int> resultMap;
    std::vector<std::tuple<QFVar, unsigned int>> retVec;

    // Init Map
    for(auto &key:refToVar)
        resultMap[&key.second] = 0;
 
     // Set Integer Values
    for(auto ref:resultVec)
    {
        if(ref >= 0)
        {
            auto srchIter = refToVar.find(Range(ref, ref));
            if(srchIter == refToVar.end())
                continue;
            resultMap[&srchIter->second] = std::pow(ref - srchIter->first.lower + 1, 2);
        }
    }
   
    // Flatten
    for(auto &key:resultMap)
       retVec.push_back(std::make_tuple(*key.first, key.second));
   return std::move(retVec); 
}


int QBDimacsGen::getNumClauses() const {
    int n = 0;
    for(auto func:funcs)
        n += std::get<0>(func)->numClauses();
    return n;   
}

int QBDimacsGen::getNumVars() const {
    return curIdx;
} 


}
