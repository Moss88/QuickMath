#ifndef QFS_UNARY_H
#define QFS_UNARY_H

#include "./QFExpr.h"
namespace QuickMath {

class QFSUnaryExpr : public QFExpr {
    public:
    QFSUnaryExpr(const QFSUnaryExpr& other);
    QFSUnaryExpr(QMOpType type, std::shared_ptr<QFType>&& expr);
    QFSUnaryExpr(QMOpType type, const QFType& expr);

    QFSUnaryExpr& operator=(const QFSUnaryExpr& other);
    QFSUnaryExpr& operator=(QFSUnaryExpr&& other);
    
    bool isUnaryExpr() const;
    const QFType* getOperand() const;
    std::string toString() const;
    std::unique_ptr<QMType> clone() const;
    
    private:
    std::shared_ptr<QFType> operand;

};
}


#endif
