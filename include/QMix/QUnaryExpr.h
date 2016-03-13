#ifndef Q_UNARY_EXPR_H
#define Q_UNARY_EXPR_H

#include <memory>
#include "./QExpr.h"
#include "../QMDefs.h"

namespace QuickMath {

class QUnaryExpr : public QExpr {
    public:
    QUnaryExpr() = default; 
    QUnaryExpr(const QUnaryExpr& other);
    QUnaryExpr(QMOpType type, std::unique_ptr<QMType>&& expr); 
    QUnaryExpr(QMOpType type, const QMType& expr); 
    QUnaryExpr& operator=(const QUnaryExpr& other);
    QUnaryExpr& operator=(QUnaryExpr&& other);
    
    std::string toString() const;
    const QMType* getOperand() const;
    virtual std::unique_ptr<QMType> clone() const;

    protected:
    std::unique_ptr<QMType> operand;
};


}

#endif
