#include "QBool/QBNot.h"
#include "QMDefs.h"
#include <iostream>
namespace QuickMath {
using namespace std;
QBNot::QBNot(QBType &a) {
    this->operands.emplace_back(static_uptr_cast<QBType>(a.clone()));
}

QBNot::QBNot(unique_ptr<QBType> a) {
    this->operands.emplace_back(std::move(a));
}
QBNot::QBNot(const QBNot& a) {
    this->operands.push_back(static_uptr_cast<QBType>(a.operands.front()->clone()));
}


std::string QBNot::toString() const {
    return "!(" + this->operands.front()->toString() + ")";
}

QBValue QBNot::value() const {
    QBValue val = this->operands.front()->value();
    if(val == QBValue::One)
        return QBValue::Zero;
    else if(val == QBValue::Zero)
        return QBValue::One;
    else
        return val;
}

bool QBNot::isNot() const {
    return true;
}

std::unique_ptr<QMType> QBNot::clone() const {
    return std::unique_ptr<QBNot>(new QBNot(*this));
}
}
