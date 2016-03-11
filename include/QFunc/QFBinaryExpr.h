#ifndef QF_BINARY_EXPR_H
#define QF_BINARY_EXPR_H
#include"./QFExpr.h"
#include <array>
#include <memory>
namespace QuickMath {
class QFBinaryExpr : public QFExpr {
    public:
    QFBinaryExpr() = default; 
    QFBinaryExpr(const QFBinaryExpr& other);
    QFBinaryExpr(QMOpType type, std::unique_ptr<QFType> a, 
                                std::unique_ptr<QFType> b); 
    QFBinaryExpr(QMOpType type, const QFType& a, const QFType& b); 
    QFBinaryExpr& operator=(const QFBinaryExpr& other);
    QFBinaryExpr& operator=(QFBinaryExpr&& other);
    
    
    std::string toString() const;
    const QFType* leftOperand() const;
    const QFType* rightOperand() const;
    virtual std::array<std::unique_ptr<QFType>, 2>::const_iterator begin() const;  
    virtual std::array<std::unique_ptr<QFType>, 2>::const_iterator end() const; 
    virtual std::unique_ptr<QMType> clone() const;
    protected:
    std::array<std::unique_ptr<QFType>, 2> operands;
};
}
#endif
