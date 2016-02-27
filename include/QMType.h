#ifndef QMTYPE_H
#define QMTYPE_H
#include <string>

namespace QuickMath { 
class QMType {
public:
    virtual QMType* clone() const = 0;
    virtual std::string toString() const = 0;

    virtual bool isVar() const {
        return false;
    }

    virtual bool isExpr() const {
        return false;
    }

    virtual bool isConstant() const {
        return false;
    }


protected:
    friend std::ostream& operator<< (std::ostream& outStream, const QMType& val);

};


}

#endif 

