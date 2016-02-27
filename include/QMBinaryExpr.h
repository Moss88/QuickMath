#ifndef QM_BINARY_EXPR_H
#define QM_BINARY_EXPR_H
#include"QMExpr.h"
#include <array>
#include <memory>
namespace QuickMath {
class QMBinaryExpr : public QMExpr {
    public:
    QMBinaryExpr() = default; 
    QMBinaryExpr(const QMBinaryExpr& other);
    QMBinaryExpr(QMOpType type, std::unique_ptr<QMType> a, 
                                std::unique_ptr<QMType> b); 
    QMBinaryExpr(QMOpType type, const QMType& a, const QMType& b); 
    QMBinaryExpr& operator=(const QMBinaryExpr& other);
    QMBinaryExpr& operator=(QMBinaryExpr&& other);
    
    
    std::string toString() const;
    const QMType* leftOperand() const;
    const QMType* rightOperand() const;
    virtual std::array<std::unique_ptr<QMType>, 2>::const_iterator begin() const;  
    virtual std::array<std::unique_ptr<QMType>, 2>::const_iterator end() const; 
    virtual QMType* clone() const;
    protected:
    std::array<std::unique_ptr<QMType>, 2> operands;
};
}
#endif
