#ifndef QF_TYPE_H
#define QF_TYPE_H
#include <string>
#include "../QMType.h"

namespace QuickMath { 
class QFType : public QMType {
public:

    bool isFuncType() const {
        return true;
    }
    
    virtual bool isVar() const {
        return false;
    }

    virtual bool isExpr() const {
        return false;
    }

    virtual bool isConstant() const {
        return false;
    }

};


}

#endif 

