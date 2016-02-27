#ifndef QM_EXPR_H
#define QM_EXPR_H
#include "QMType.h"
#include "QMDefs.h"
namespace QuickMath {
class QMExpr : public QMType {
    public:
        bool isExpr() const;
        virtual QMOpType opType() const;   
    protected:
        QMOpType op;
};
}
#endif
