#include "QFunc/QFUnaryExpr.h"
#include "QMDefs.h"

namespace QuickMath {

QFUnaryExpr::QFUnaryExpr(const QFUnaryExpr& other) {
    this->op = other.op;
    operand = static_uptr_cast<QFType>(other.clone());
}

QFUnaryExpr::QFUnaryExpr(QMOpType type, std::unique_ptr<QFType>&& expr) {
    this->op = type;
    operand = std::move(expr);
}

QFUnaryExpr::QFUnaryExpr(QMOpType type, const QFType& expr) {
    this->op = type;
    operand = static_uptr_cast<QFType>(expr.clone());
}

QFUnaryExpr& QFUnaryExpr::operator=(const QFUnaryExpr& other) {
    if(this != &other)
    {
        this->op = other.op;
        operand = static_uptr_cast<QFType>(other.operand->clone());
    }
    return *this;
}

QFUnaryExpr& QFUnaryExpr::operator=(QFUnaryExpr&& other) {
    if(this != &other)
    {
        this->op = other.op;
        operand = std::move(other.operand);
    }
    return *this;
}
    
std::string QFUnaryExpr::toString() const {
    return OpTypeToString(this->opType()) + operand->toString();
}

const QFType* QFUnaryExpr::getOperand() const {
    return operand.get();
}

std::unique_ptr<QMType> QFUnaryExpr::clone() const {
    return std::unique_ptr<QFUnaryExpr>(new QFUnaryExpr(*this));
}

bool QFUnaryExpr::isUnaryExpr() const {
    return true;
}

size_t QFUnaryExpr::numOperands() const {
    return 1;
}

const QFType* QFUnaryExpr::getOperand(size_t idx) const {
    if(idx > 0)
        throw std::runtime_error("QFUnaryExpr.getOperand: invalid idx");
    return operand.get();
} 

QFType* QFUnaryExpr::getOperand(size_t idx) {
    if(idx > 0)
        throw std::runtime_error("QFUnaryExpr.getOperand: invalid idx");
    return operand.get();
} 
 
}


