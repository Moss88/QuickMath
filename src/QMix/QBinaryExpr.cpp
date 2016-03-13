#include "QMix/QBinaryExpr.h"

namespace QuickMath {

QBinaryExpr::QBinaryExpr(const QBinaryExpr& other) {
    this->op = other.op;
    operands.front() = other.operands.front()->clone();
    operands.back() = other.operands.back()->clone();
}

QBinaryExpr::QBinaryExpr(QMOpType type, std::unique_ptr<QMType>&& a, 
                                        std::unique_ptr<QMType>&& b) {
    this->op = type;
    operands.front() = std::move(a);
    operands.back() = std::move(b);
}

QBinaryExpr::QBinaryExpr(QMOpType type, const QMType& a, const QMType& b) {
    this->op = type;
    operands.front() = a.clone();
    operands.back() = b.clone();
}

QBinaryExpr& QBinaryExpr::operator=(const QBinaryExpr& other) {
    if(this != &other)
    {
        this->op = other.op;
        operands.front() = other.operands.front()->clone();
        operands.back() = other.operands.back()->clone();
    }
    return *this;
}

QBinaryExpr& QBinaryExpr::operator=(QBinaryExpr&& other) {
    if(this != &other)
    {
        this->op = other.op;
        operands.front() = std::move(other.operands.front());
        operands.back() = std::move(other.operands.back());
    }
    return *this;
}
    
std::string QBinaryExpr::toString() const {
    return "";
}

const QMType* QBinaryExpr::leftOperand() const {
    return operands.front().get();
}

const QMType* QBinaryExpr::rightOperand() const {
    return operands.back().get();
}

std::array<std::unique_ptr<QMType>, 2>::const_iterator QBinaryExpr::begin() const {
    return operands.cbegin();
}

std::array<std::unique_ptr<QMType>, 2>::const_iterator QBinaryExpr::end() const {
    return operands.cend();
}

std::unique_ptr<QMType> QBinaryExpr::clone() const {
    return std::unique_ptr<QMType>(nullptr);
}

}

