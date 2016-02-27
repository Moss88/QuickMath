#include "QMBinaryExpr.h"
#include <algorithm>
namespace QuickMath {

QMBinaryExpr::QMBinaryExpr(const QMBinaryExpr& other) {
    auto iter = this->operands.begin();
    for(auto &operand:other.operands)
    {
        if(operand)
            *iter = std::unique_ptr<QMType>(operand->clone());
        ++iter;
    }
    this->op = other.op;
}

QMBinaryExpr::QMBinaryExpr(QMOpType type, 
                           std::unique_ptr<QMType> a, 
                           std::unique_ptr<QMType> b) 
{
    this->op = type;
    operands[0] = std::move(a);
    operands[1] = std::move(b);
}

QMBinaryExpr::QMBinaryExpr(QMOpType type, const QMType& a, const QMType& b) 
{
    this->op = type;
    operands[0] = std::unique_ptr<QMType>(a.clone());
    operands[1] = std::unique_ptr<QMType>(b.clone());
}


QMBinaryExpr& QMBinaryExpr::operator=(const QMBinaryExpr& other) {
    if(this != &other)
    {
        auto iter = this->operands.begin();
        for(auto &operand:other.operands)
        {
            if(operand)
                *iter = std::unique_ptr<QMType>(operand->clone());
            ++iter;
        }
        this->op = other.op;
    }
    return *this;
}

QMBinaryExpr& QMBinaryExpr::operator=(QMBinaryExpr&& other) {
    this->operands[0] = std::move(other.operands[0]);    
    this->operands[1] = std::move(other.operands[1]);    
    this->op = other.op;
    return *this;
}


std::string QMBinaryExpr::toString() const  {
    return "";
}

std::array<std::unique_ptr<QMType>, 2>::const_iterator 
QMBinaryExpr::begin() const {
    return operands.cbegin();
}  

std::array<std::unique_ptr<QMType>, 2>::const_iterator 
QMBinaryExpr::end() const {
   return operands.cend();
} 

const QMType* QMBinaryExpr::leftOperand() const {
    return operands[0].get();
}

const QMType* QMBinaryExpr::rightOperand() const {
    return operands[1].get();
}
    
QMType* QMBinaryExpr::clone() const {
    return new QMBinaryExpr(*this);
}

}
