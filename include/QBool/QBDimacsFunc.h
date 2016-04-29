#ifndef QB_DIMACS_FUNC
#define QB_DIMACS_FUNC
#include <vector>
#include <map>
#include <tuple>
#include <iostream>
#include "./QBFunc.h"
#include "./QBBit.h"

namespace QuickMath {
class QBDimacsFunc {

    public:
        QBDimacsFunc() = default;
        QBDimacsFunc(const QBFunc& bfunc, const std::vector<std::tuple<std::string, int>>& inputs);
        int numVars() const;
        int numClauses() const;
        void cnfsToStream(std::ostream& os, const std::vector<int>& inputIdxs, int tmpVarSIdx) const;
        int numTmpVars() const;
        const std::vector<std::tuple<std::string, int>>& getInputs() const;
    private:
        void setupCNFs(const QBFunc& func);
        void setupVarMaps(const QBFunc& bfunc);
        int getRef(const QBBit* bit);
        void insertCNFLiteral(const QBBit* bit, bool positive);
    
        int varCnt = 0;
        std::vector<std::vector<int>> cnfs;
      
        // Maintains input Order 
        std::vector<std::tuple<std::string, int>> inputOrder;
         
        // VarName  ->  <StartIndex, Size>
        std::map<std::string, std::tuple<int, int>> vecMap;
        
        // DimacVarRef idx -> to all locations in cnfs
        std::vector<std::vector<std::tuple<int, int>>> refLocs;
        
        // TempIdx -> DimacVarRef
        std::map<int, int> tmpVars;
};
}


#endif
