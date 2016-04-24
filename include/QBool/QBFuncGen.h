#ifndef QB_FUNC_GEN
#define QB_FUNC_GEN
#include "QBFunc.h"
#include "QBManager.h"
#include <map>
#include <string>
#include <set>
namespace QuickMath {
class QBFuncGen {
    public:
    QBFuncGen(const QBFunc& func);
    QBFuncGen(QBFunc&& func);
    QBFunc generateFunc(const std::map<std::string, std::string>& varMap,
                        QBManager& manager) const;   

    private:
    struct BitRefs {
        BitRefs() = default;
        BitRefs(int idx) : idx(idx) {}
        bool operator<(const BitRefs& other) const {
            return idx < other.idx;
        };

        int idx = 0;
        std::vector<QBBit*> refs; // Refs inside function
    };

    void getRefs();
    void storeTmpVarRef(QBBit* bit);
    void storeVarRef(QBBit* bit);

    std::map<std::string, std::map<int, std::vector<QBBit*>>> vecMap;
    std::map<int, std::vector<QBBit*>> tmpVars; // Possible Tseytin
    QBFunc func;
};

}

#endif
