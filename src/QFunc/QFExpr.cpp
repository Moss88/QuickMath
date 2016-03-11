#include "QFunc/QFExpr.h"
namespace QuickMath {
bool QFExpr::isExpr() const {
    return true;
}

QMOpType QFExpr::opType() const {
    return op;
}
}
