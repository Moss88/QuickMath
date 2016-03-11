#ifndef QB_CONSTANTS_H
#define QB_CONSTANTS_H

#include <string>
#include "./QBBasicDefs.h"
#include "./QBType.h"

namespace QuickMath {

class QBConstant : public QBType {
public:
    bool isVar() const;
    bool isExpr() const;
    virtual std::string toString() const;
    virtual QBValue value() const = 0;
    bool isAnd() const {
        return false;
    }
    virtual bool isOr() const {
        return false;
    }
    virtual bool isNot() const {
        return false;
    }

};

class QBOne : public QBConstant {
public:
    QBValue value() const;
    QBType* clone() const;
    bool isOne() const;
};

class QBZero : public QBConstant {
public:
    QBValue value() const;
    QBType* clone() const;
    bool isZero() const;
};

class QBDontCare : public QBConstant {
public:
    QBValue value() const;
    QBType* clone() const;
};

}
#endif // BOOLCONSTANTS_H

