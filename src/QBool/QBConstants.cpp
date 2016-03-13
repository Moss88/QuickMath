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

std::unique_ptr<QMType> QBOne::clone() const {
    return std::unique_ptr<QBOne>(new QBOne());
}

bool QBOne::isOne() const {
    return true;
}

QBValue QBZero::value() const {
    return QBValue::Zero;
}

std::unique_ptr<QMType> QBZero::clone() const {
    return std::unique_ptr<QBZero>(new QBZero());
}


bool QBZero::isZero() const {
    return true;
}

QBValue QBDontCare::value() const {
    return QBValue::DontCare;
}

std::unique_ptr<QMType> QBDontCare::clone() const {
    return std::unique_ptr<QBDontCare>(new QBDontCare());
}
}
