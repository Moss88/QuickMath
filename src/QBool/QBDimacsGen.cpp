#include "QBool/QBDimacsGen.h"
#include <sstream>
namespace QuickMath {
void QBDimacsGen::addFunction(const QBDimacsFunc* dFunc, 
                              const std::vector<std::tuple<const QFVar*,int>>& vars) {
    if(!validate(dFunc, vars))
        throw std::runtime_error("QBDimacsGen.addFunction: invalid input vector"); 
   
    std::vector<int> mapInput;
    for(auto &var:vars)
    {
        auto srchIter = varMap.find(std::get<0>(var)->toString());
        if(srchIter == varMap.end())
        {
            varMap[std::get<0>(var)->toString()] = std::make_tuple(curIdx, std::get<1>(var)); 
            mapInput.push_back(curIdx);
            curIdx += std::get<1>(var);
        }
        else
            mapInput.push_back(std::get<0>(srchIter->second));       
    }
    funcs.push_back(std::make_tuple(dFunc, std::move(mapInput), curIdx));
    curIdx += dFunc->numTmpVars();
}

bool QBDimacsGen::validate(const QBDimacsFunc* dFunc, 
        const std::vector<std::tuple<const QFVar*, int>>& vars)
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
    ss << "0\n";
    return std::move(ss.str());
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
