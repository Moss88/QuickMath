#ifndef QB_TYPE_H
#define QB_TYPE_H
#include <string>
#include "./QBBasicDefs.h"
#include "../QMType.h"

namespace QuickMath { 
class QBType : public QMType {
public:
    virtual std::string toString() const = 0;
    virtual QBValue value() const = 0;

    bool isBoolType() const {
        return true;
    }
    
   virtual bool isAnd() const {
        return false;
    }
    virtual bool isOr() const {
        return false;
    }
    virtual bool isNot() const {
        return false;
    }

    virtual bool isOne() const {
        return false;
    }

    virtual bool isZero() const {
        return false;
    }

};


}

#endif // BOOLTYPE_H

