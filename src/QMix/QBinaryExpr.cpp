#include "QMix/QBinaryExpr.h"

namespace QuickMath {

QBinaryExpr::QBinaryExpr(const QBinaryExpr& other) {
    operands.front() = std::unique_ptr<QMType>(other.operands.front()->clone());
    operands.back() = std::unique_ptr<QMType>(other.operands.back()->clone());
}
/*
QBinaryExpr::QBinaryExpr(QMOpType type, std::unique_ptr<QMType> a, 
                               std::unique_ptr<QMType> b); 
QBinaryExpr::QBinaryExpr(QMOpType type, const QMType& a, const QMType& b); 
 QBinaryExpr::   QBinaryExpr& operator=(const QBinaryExpr& other);
 QBinaryExpr::   QBinaryExpr& operator=(QBinaryExpr&& other);
    
    
std::string QBinaryExpr::toString() const;
*/
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

