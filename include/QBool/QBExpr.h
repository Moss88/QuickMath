#ifndef QB_EXPR_H
#define QB_EXPR_H
#include <vector>
#include "./QBBasicDefs.h"
#include "./QBType.h"

namespace QuickMath {

class QBExpr : public QBType {
public:
    virtual std::vector<UQBType>::iterator begin() {
        return operands.begin();
    }

    virtual std::vector<UQBType>::iterator end() {
        return operands.end();
    }

    virtual std::vector<UQBType>::const_iterator begin() const {
        return operands.begin();
    }

    virtual std::vector<UQBType>::const_iterator end() const {
        return operands.end();
    }

    virtual unsigned int size() const {
        return operands.size();
    }

    bool isExpr() const {
        return true;
    }



protected:
    std::vector<UQBType> operands;
};

}

#endif // BOOLEXPR_H

