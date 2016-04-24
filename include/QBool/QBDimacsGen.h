#ifndef QB_DIMACS_GEN
#define QB_DIMACS_GEN

#include <vector>
#include <tuple>
#include <string>
#include "QBDimacsFunc.h"
#include "QFunc/QFVar.h"

namespace QuickMath {
class QBDimacsGen {

    public:
        QBDimacsGen() = default;
                                                                     // Vars and Sizes
        void addFunction(const QBDimacsFunc* dFunc, 
                const std::vector<std::tuple<const QFVar*,int>>& vars);
        std::string getDimacs() const;
        int getNumClauses() const;
        int getNumVars() const; 
    private:

        bool validate(const QBDimacsFunc* dFunc, 
            const std::vector<std::tuple<const QFVar*, int>>& vars);


        int curIdx = 1;
                                   // VarIdx, Size
        std::map<std::string, std::tuple<int, int>> varMap; 
        std::vector<std::tuple<const QBDimacsFunc*, std::vector<int>, int>> funcs;
};
}


#endif
