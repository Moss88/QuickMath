#include "QBool/QBDimacsGen.h"
#include "QBool/QBAlgorithms.h"
#include <sstream>
#include <cmath>
namespace QuickMath {

int QBDimacsGen::addVar(const QFType* var, int size) {
    std::string name = var->toString();
    auto srchIter = varMap.find(name);
    if(srchIter == varMap.end())
    {
        int orgIdx = curIdx;
        curIdx += size;
        varMap[name] = orgIdx;
        refToVar[Range(orgIdx, curIdx - 1)] = var;
        return orgIdx;
    }
    return srchIter->second;       
}

void QBDimacsGen::addFunction(const QBDimacsFunc* dFunc, 
                              const std::vector<std::tuple<const QFType*, int>>& vars) {
    if(!validate(dFunc, vars))
        throw std::runtime_error("QBDimacsGen.addFunction: invalid input vector"); 
   
    std::vector<int> mapInput;
    for(auto &var:vars)
    {
        int idx = addVar(std::get<0>(var), std::get<1>(var));
        //std::cout << std::get<0>(var)->toString() << " idx " << idx << std::endl;
        mapInput.push_back(idx);
    }
    funcs.push_back(std::make_tuple(dFunc, std::move(mapInput), curIdx));
    curIdx += dFunc->numTmpVars();
}

bool QBDimacsGen::validate(const QBDimacsFunc* dFunc, const std::vector<std::tuple<const QFType*, int>>& vars)
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

std::vector<std::vector<int>> QBDimacsGen::getClauses() const {
    std::vector<std::vector<int>> clauses;
    for(auto &func:funcs)
    {
        auto funcClauses = std::get<0>(func)->getClauses(std::get<1>(func), std::get<2>(func));
        clauses.insert(clauses.end(), funcClauses.begin(), funcClauses.end()); 
    }
    return std::move(clauses);

}

bool QBDimacsGen::isSat() const {
    return QBAlgo::runPicoSat(getClauses(), getNumVars()).size() > 0;
}

// Can filter single bits, used for BFAST
std::vector<std::tuple<const QFType*, unsigned int>> QBDimacsGen::getSat(bool includeBits) const {
   /*
    std::cout << "Result Vec: " << std::endl;
    for(auto &lit:resultVec)
        std::cout << lit << " ";
    std::cout << std::endl;

    std::cout << "Ref Map: " << std::endl;
    for(auto &ref:refToVar)
        std::cout << ref.first.lower << "," << ref.first.upper << ": " << ref.second->toString() << std::endl; 
*/

    std::map<const QFType*, unsigned int> resultMap;
    std::vector<std::tuple<const QFType*, unsigned int>> retVec;
    
    auto resultVec = QBAlgo::runPicoSat(getClauses(), getNumVars());
    if(resultVec.size() == 0)
        return retVec;
 
    // Init Map
    for(auto &key:refToVar)
    {
        if(key.first.getLength() > 1 || includeBits)
            resultMap[key.second] = 0;
    }
    
    // Set Integer Values
    for(auto ref:resultVec)
    {
        if(ref >= 0)
        {
            auto srchIter = refToVar.find(Range(ref, ref));
            if(srchIter == refToVar.end() || ((srchIter->first.getLength() < 2) && !includeBits))
                continue;
            auto& val = resultMap[srchIter->second];
            val += std::pow(ref - srchIter->first.lower + 1, 2);
        }
    }
   
    // Flatten
    for(auto &key:resultMap)
       retVec.push_back(std::make_tuple(key.first, key.second));
    
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

std::string QBDimacsGen::getDebug() const {
    std::stringstream ss;
    ss << "Variable Map: " << std::endl;
    for(auto &varMaps:refToVar) 
        ss << varMaps.second->toString() << ": " << varMaps.first.lower << "," << varMaps.first.upper << std::endl;
    ss << "Dimac: " << std::endl;
    for(auto &func:funcs) {
        ss << "Function: " << std::endl;
        std::get<0>(func)->cnfsToStream(ss, std::get<1>(func), std::get<2>(func));
    }
    return ss.str();
}

}
