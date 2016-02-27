#include "QMExpr.h"
namespace QuickMath {
bool QMExpr::isExpr() const {
    return true;
}

QMOpType QMExpr::opType() const {
    return op;
}
}
