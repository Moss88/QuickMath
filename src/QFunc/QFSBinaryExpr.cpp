#include "QFunc/QFSBinaryExpr.h"
#include <algorithm>
namespace QuickMath {

QFSBinaryExpr::QFSBinaryExpr(const QFSBinaryExpr& other) {
    auto iter = this->operands.begin();
    for(auto &operand:other.operands)
    {
        if(operand)
            *iter = static_uptr_cast<QFType>(operand->clone());
        ++iter;
    }
    this->op = other.op;
}

QFSBinaryExpr::QFSBinaryExpr(QMOpType type, 
                           std::shared_ptr<QFType> a, 
                           std::shared_ptr<QFType> b) 
{
    this->op = type;
    operands[0] = std::move(a);
    operands[1] = std::move(b);
}

QFSBinaryExpr::QFSBinaryExpr(QMOpType type, const QFType& a, const QFType& b) 
{
    this->op = type;
    operands[0] = static_uptr_cast<QFType>(a.clone());
    operands[1] = static_uptr_cast<QFType>(b.clone());
}


QFSBinaryExpr& QFSBinaryExpr::operator=(const QFSBinaryExpr& other) {
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

QFSBinaryExpr& QFSBinaryExpr::operator=(QFSBinaryExpr&& other) {
    this->operands[0] = std::move(other.operands[0]);    
    this->operands[1] = std::move(other.operands[1]);    
    this->op = other.op;
    return *this;
}


std::string QFSBinaryExpr::toString() const  {
    return "(" + leftOperand()->toString() + OpTypeToString(this->opType()) 
               + rightOperand()->toString() + ")";
}

std::array<std::shared_ptr<QFType>, 2>::const_iterator 
QFSBinaryExpr::begin() const {
    return operands.cbegin();
}  

std::array<std::shared_ptr<QFType>, 2>::const_iterator 
QFSBinaryExpr::end() const {
   return operands.cend();
} 

bool QFSBinaryExpr::isBinaryExpr() const {
    return true;
}

const QFType* QFSBinaryExpr::leftOperand() const {
    return operands[0].get();
}

const QFType* QFSBinaryExpr::rightOperand() const {
    return operands[1].get();
}
    
std::unique_ptr<QMType> QFSBinaryExpr::clone() const {
    return  std::unique_ptr<QMType>(new QFSBinaryExpr(*this));
}

}
