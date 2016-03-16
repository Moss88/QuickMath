#include "QMix/QExpr.h"
namespace QuickMath {
bool QExpr::isExpr() const {
    return true;
}

bool QExpr::isBinaryExpr() const {
    return false;
}

bool QExpr::isUnaryExpr() const {
    return false;
}
 
QMOpType QExpr::opType() const {
    return op;
}
}
