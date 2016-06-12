#include "QFunc/QFBinaryExpr.h"
#include <algorithm>
namespace QuickMath {

QFBinaryExpr::QFBinaryExpr(const QFBinaryExpr& other) {
    auto iter = this->operands.begin();
    for(auto &operand:other.operands)
    {
        if(operand)
            *iter = static_uptr_cast<QFType>(operand->clone());
        ++iter;
    }
    this->op = other.op;
}

QFBinaryExpr::QFBinaryExpr(QMOpType type, 
                           std::unique_ptr<QFType> a, 
                           std::unique_ptr<QFType> b) 
{
    this->op = type;
    operands[0] = std::move(a);
    operands[1] = std::move(b);
}

QFBinaryExpr::QFBinaryExpr(QMOpType type, const QFType& a, const QFType& b) 
{
    this->op = type;
    operands[0] = static_uptr_cast<QFType>(a.clone());
    operands[1] = static_uptr_cast<QFType>(b.clone());
}


QFBinaryExpr& QFBinaryExpr::operator=(const QFBinaryExpr& other) {
    if(this != &other)
    {
        auto iter = this->operands.begin();
        for(auto &operand:other.operands)
        {
            if(operand)
                *iter = static_uptr_cast<QFType>(operand->clone());
            ++iter;
        }
        this->op = other.op;
    }
    return *this;
}

QFBinaryExpr& QFBinaryExpr::operator=(QFBinaryExpr&& other) {
    this->operands[0] = std::move(other.operands[0]);    
    this->operands[1] = std::move(other.operands[1]);    
    this->op = other.op;
    return *this;
}


std::string QFBinaryExpr::toString() const  {
    return "(" + leftOperand()->toString() + OpTypeToString(this->opType()) 
               + rightOperand()->toString() + ")";
}

std::array<std::unique_ptr<QFType>, 2>::const_iterator 
QFBinaryExpr::begin() const {
    return operands.cbegin();
}  

std::array<std::unique_ptr<QFType>, 2>::const_iterator 
QFBinaryExpr::end() const {
   return operands.cend();
} 

bool QFBinaryExpr::isBinaryExpr() const {
    return true;
}

const QFType* QFBinaryExpr::leftOperand() const {
    return operands[0].get();
}

const QFType* QFBinaryExpr::rightOperand() const {
    return operands[1].get();
}
    
std::unique_ptr<QMType> QFBinaryExpr::clone() const {
    return std::unique_ptr<QMType>(new QFBinaryExpr(*this));
}

size_t QFBinaryExpr::numOperands() const {
    return 2;
}

const QFType* QFBinaryExpr::getOperand(size_t idx) const {
    if(idx > 1)
        throw std::runtime_error("QFBinaryExpr.getOperand: invalid idx");
    return operands[idx].get(); 
}

QFType* QFBinaryExpr::getOperand(size_t idx) {
    if(idx > 1)
        throw std::runtime_error("QFBinaryExpr.getOperand: invalid idx");
    return operands[idx].get(); 
} 
    
}
