#include "QBool/QBNaryExpr.h"
#include "QBool/QBFunc.h"
#include "QMDefs.h"
namespace QuickMath {
void QBNaryExpr::addOperand(const QBType& func) {
    this->operands.push_back(static_uptr_cast<QBType>(func.clone()));
}
}
