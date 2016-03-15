#ifndef QM_TYPE_H
#define QM_TYPE_H

#include <ostream>
#include <memory>

namespace QuickMath {
class QMType {
    public:
    virtual std::string toString() const = 0;
    virtual bool isBoolType() const;
    virtual bool isFuncType() const;
    virtual bool isMixedType() const;
    virtual bool isVar() const;
    virtual bool isExpr() const;
    virtual bool isConstant() const;
    virtual std::unique_ptr<QMType> clone() const = 0;
    protected:
    friend std::ostream& operator<< (std::ostream& outStream, const QMType& val);
};

}

#endif
