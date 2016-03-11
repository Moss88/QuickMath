#include "QBool/QBNaryExpr.h"
#include "QBool/QBFunc.h"
namespace QuickMath {
void QBNaryExpr::addOperand(const QBType& func) {
    this->operands.push_back(std::unique_ptr<QBType>(func.clone()));
}
}
