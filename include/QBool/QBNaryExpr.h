#ifndef QB_NARY_EXPR_H
#define QB_NARY_EXPR_H
#include "./QBExpr.h"

namespace QuickMath {

class QBFunc;
class QBNaryExpr : public QBExpr {
public:
    void addOperand(const QBType& func);
    void addOperand(QBType&& func);

};

}

#endif // BOOLNARYEXPR_H

