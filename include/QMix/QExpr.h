#ifndef Q_EXPR_H
#define Q_EXPR_H
#include "./QOp.h"
#include "../QMDefs.h"
namespace QuickMath {
class QExpr : public QOp {
    public:
        bool isExpr() const;
        virtual QMOpType opType() const;   
        virtual bool isBinaryExpr() const;
        virtual bool isUnaryExpr() const;
    protected:
        QMOpType op;
};
}
#endif
