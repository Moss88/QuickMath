#ifndef QBALGORITHMS_H
#define QBALGORITHMS_H
#include "./QBFunc.h"
#include "./QBExpr.h"
#include <functional>

namespace QuickMath {
class QBManager;
namespace QBAlgo {


template<typename BFunc, typename Func>
bool depthRecur(BFunc* expr, Func func) {
    if(expr == nullptr)
        return false;
    if(expr->isExpr())
    {
        auto expression = static_cast<const QBExpr*>(expr);
        for(auto &operand:*expression)
        {
            if(!depthRecur(operand.get(), func))
                return false;
        }
    }
    return func(expr);
}

template<typename BFunc, typename Func>
void depthTraversal(BFunc& expr, Func func) {
    if(expr.get() != nullptr)
        depthRecur(expr.get(), func);
}

template<typename Func>
void depthTraversal(QBType& expr, Func func) {
    depthRecur(&expr, func);
}

std::vector<int> runLingelingSat(std::string &&dimacsStr);
std::vector<int> runPicoSat(const std::vector<int>& input, int nVars);
QBFunc generateCNF(const QBFunc& func, QBManager& bMan);
bool isCNF(const QBFunc &func);
std::vector<QBFunc> isSat(const QBFunc& func);

QBFunc dnfToCnf(const QBFunc& func);


}
}
#endif // BOOLALGORITHMS_H

