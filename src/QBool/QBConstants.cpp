#include "QBool/QBConstants.h"
#include "QBool/QBBasicDefs.h"

namespace QuickMath {
bool QBConstant::isVar() const {
    return false;
}

bool QBConstant::isExpr() const {
    return false;
}

std::string QBConstant::toString() const {
    return to_string(this->value());
}

QBValue QBOne::value() const {
    return QBValue::One;
}

QBType* QBOne::clone() const {
    return new QBOne();
}

bool QBOne::isOne() const {
    return true;
}

QBValue QBZero::value() const {
    return QBValue::Zero;
}

QBType* QBZero::clone() const {
    return new QBZero();
}


bool QBZero::isZero() const {
    return true;
}

QBValue QBDontCare::value() const {
    return QBValue::DontCare;
}

QBType* QBDontCare::clone() const {
    return new QBDontCare();
}
}
