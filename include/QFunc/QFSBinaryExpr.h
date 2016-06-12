#ifndef QFS_BINARY_EXPR_H
#define QFS_BINARY_EXPR_H
#include"./QFExpr.h"
#include <array>
#include <memory>
namespace QuickMath {
class QFSBinaryExpr : public QFExpr {
    public:
    QFSBinaryExpr() = default; 
    QFSBinaryExpr(const QFSBinaryExpr& other);
    QFSBinaryExpr(QMOpType type, std::shared_ptr<QFType> a, 
                                std::shared_ptr<QFType> b); 
    QFSBinaryExpr(QMOpType type, const QFType& a, const QFType& b); 
    QFSBinaryExpr& operator=(const QFSBinaryExpr& other);
    QFSBinaryExpr& operator=(QFSBinaryExpr&& other);
    bool isBinaryExpr() const; 
    
    std::string toString() const;
    const QFType* leftOperand() const;
    const QFType* rightOperand() const;
    
    size_t numOperands() const;
    const QFType* getOperand(size_t idx) const; 
    QFType* getOperand(size_t idx); 

    virtual std::array<std::shared_ptr<QFType>, 2>::const_iterator begin() const;  
    virtual std::array<std::shared_ptr<QFType>, 2>::const_iterator end() const; 
    virtual std::unique_ptr<QMType> clone() const;
    protected:
    std::array<std::shared_ptr<QFType>, 2> operands;
};
}
#endif
