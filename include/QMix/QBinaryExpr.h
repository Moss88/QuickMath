#ifndef Q_BINARY_EXPR_H
#define Q_BINARY_EXPR_H

#include <memory>
#include "./QExpr.h"
#include "../QMDefs.h"

namespace QuickMath {

class QBinaryExpr : public QExpr {
    public:
    QBinaryExpr() = default; 
    QBinaryExpr(const QBinaryExpr& other);
    QBinaryExpr(QMOpType type, std::unique_ptr<QMType>&& a, 
                               std::unique_ptr<QMType>&& b); 
    QBinaryExpr(QMOpType type, const QMType& a, const QMType& b); 
    QBinaryExpr& operator=(const QBinaryExpr& other);
    QBinaryExpr& operator=(QBinaryExpr&& other);
    
    
    bool isBinaryExpr() const;
    std::string toString() const;
    const QMType* leftOperand() const;
    const QMType* rightOperand() const;
    virtual std::array<std::unique_ptr<QMType>, 2>::const_iterator begin() const;  
    virtual std::array<std::unique_ptr<QMType>, 2>::const_iterator end() const; 
    virtual std::unique_ptr<QMType> clone() const;

    protected:
    std::array<std::unique_ptr<QMType>, 2> operands;
};


}

#endif
