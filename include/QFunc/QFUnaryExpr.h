#ifndef QF_UNARY_H
#define QF_UNARY_H

#include "./QFExpr.h"
namespace QuickMath {

class QFUnaryExpr : public QFExpr {
    public:
    QFUnaryExpr(const QFUnaryExpr& other);
    QFUnaryExpr(QMOpType type, std::unique_ptr<QFType>&& expr);
    QFUnaryExpr(QMOpType type, const QFType& expr);

    QFUnaryExpr& operator=(const QFUnaryExpr& other);
    QFUnaryExpr& operator=(QFUnaryExpr&& other);
    const QFType* getOperand() const;
    std::string toString() const;
    std::unique_ptr<QMType> clone() const;
    
    private:
    std::unique_ptr<QFType> operand;

};
}


#endif
