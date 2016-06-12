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

size_t QFExpr::numOperands() const {
    return 0;
}

const QFType* QFExpr::getOperand(size_t idx) const {
    return nullptr;
} 

QFType* QFExpr::getOperand(size_t idx) {
    return nullptr;
} 


}
