#include "QFunc/QFSUnaryExpr.h"
#include "QMDefs.h"

namespace QuickMath {

QFSUnaryExpr::QFSUnaryExpr(const QFSUnaryExpr& other) {
    this->op = other.op;
    operand = static_uptr_cast<QFType>(other.clone());
}

QFSUnaryExpr::QFSUnaryExpr(QMOpType type, std::shared_ptr<QFType>&& expr) {
    this->op = type;
    operand = std::move(expr);
}

QFSUnaryExpr::QFSUnaryExpr(QMOpType type, const QFType& expr) {
    this->op = type;
    operand = static_uptr_cast<QFType>(expr.clone());
}

QFSUnaryExpr& QFSUnaryExpr::operator=(const QFSUnaryExpr& other) {
    if(this != &other)
    {
        this->op = other.op;
        operand = static_uptr_cast<QFType>(other.operand->clone());
    }
    return *this;
}

QFSUnaryExpr& QFSUnaryExpr::operator=(QFSUnaryExpr&& other) {
    if(this != &other)
    {
        this->op = other.op;
        operand = std::move(other.operand);
    }
    return *this;
}
    
std::string QFSUnaryExpr::toString() const {
    return OpTypeToString(this->opType()) + operand->toString();
}

const QFType* QFSUnaryExpr::getOperand() const {
    return operand.get();
}

std::unique_ptr<QMType> QFSUnaryExpr::clone() const {
    return std::unique_ptr<QFSUnaryExpr>(new QFSUnaryExpr(*this));
}

bool QFSUnaryExpr::isUnaryExpr() const {
    return true;
}

}


