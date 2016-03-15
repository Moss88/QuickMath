#include "QFunc/QFExpr.h"
namespace QuickMath {
bool QFExpr::isExpr() const {
    return true;
}

QMOpType QFExpr::opType() const {
    return op;
}

bool QFExpr::isUnaryExpr() const {
    return false;
}

bool QFExpr::isBinaryExpr() const {
    return false;
}

}
