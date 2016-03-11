#ifndef QF_EXPR_H
#define QF_EXPR_H
#include "./QFType.h"
#include "../QMDefs.h"
namespace QuickMath {
class QFExpr : public QFType {
    public:
        bool isExpr() const;
        virtual QMOpType opType() const;   
    protected:
        QMOpType op;
};
}
#endif
