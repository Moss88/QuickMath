#include "QMix/QUnaryExpr.h"

namespace QuickMath {

    QUnaryExpr::QUnaryExpr(const QUnaryExpr& other) {
        this->op = other.op;
        operand = other.clone();
    }

    QUnaryExpr::QUnaryExpr(QMOpType type, std::unique_ptr<QMType>&& expr) {
        this->op = type;
        operand = std::move(expr);
    }

    QUnaryExpr::QUnaryExpr(QMOpType type, const QMType& expr) {
        this->op = type;
        operand = expr.clone();
    }

    QUnaryExpr& QUnaryExpr::operator=(const QUnaryExpr& other) {
        if(this != &other)
        {
            this->op = other.op;
            operand = other.operand->clone();
        }
        return *this;
    }

    QUnaryExpr& QUnaryExpr::operator=(QUnaryExpr&& other) {
        if(this != &other)
        {
            this->op = other.op;
            operand = std::move(other.operand);
        }
        return *this;
    }
    
    std::string QUnaryExpr::toString() const {
        return "";
    }

    const QMType* QUnaryExpr::getOperand() const {
        return operand.get();
    }

    std::unique_ptr<QMType> QUnaryExpr::clone() const {
        return std::unique_ptr<QUnaryExpr>(new QUnaryExpr(*this));
    }

    bool QUnaryExpr::isUnaryExpr() const {
        return true;
    }
}


