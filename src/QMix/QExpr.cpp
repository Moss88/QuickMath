#include "QMix/QExpr.h"
namespace QuickMath {
bool QExpr::isExpr() const {
    return true;
}

QMOpType QExpr::opType() const {
    return op;
}
}
