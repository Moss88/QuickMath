#ifndef QB_DIMACS_GEN
#define QB_DIMACS_GEN

#include <vector>
#include <tuple>
#include <string>
#include "./QBDimacsFunc.h"
#include "../QFunc/QFVar.h"

namespace QuickMath {
class QBDimacsGen {

    public:
        QBDimacsGen() = default;
                                                                     // Vars and Sizes
        void addFunction(const QBDimacsFunc* dFunc, 
                const std::vector<std::tuple<const QFType*, int>>& vars);
        std::string getDimacs() const;
        std::vector<int> getClauses() const;
        int getNumClauses() const;
        int getNumVars() const; 
        bool isSat() const; 
        std::vector<std::tuple<const QFType*, unsigned int>> getSat(bool includeBits = true) const;
        std::string getDebug() const;
    private:
        

        struct Range  {
            Range(int l, int u) : lower(l), upper(u){}
            int getLength() const { return upper - lower + 1;}
            int lower;
            int upper;
        };

        struct RangeCmp {
            bool operator()(const Range& a, const Range& b) const {
                return a.upper < b.lower; 
            }
        };


        bool validate(const QBDimacsFunc* dFunc, 
            const std::vector<std::tuple<const QFType*, int>>& vars);

        int addVar(const QFType* var, int size);

        int curIdx = 1;

        // Lookup for Input Vars
        std::map<std::string, int> varMap; 
        
        // Idx Range
        std::map<Range, const QFType*, RangeCmp> refToVar; 
        
        //std::map<int, std::tuple<int, int>> varMap; 
        std::vector<std::tuple<const QBDimacsFunc*, std::vector<int>, int>> funcs;
};
}


#endif
