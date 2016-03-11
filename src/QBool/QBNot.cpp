#include "QBool/QBNot.h"
#include <iostream>
namespace QuickMath {
using namespace std;
QBNot::QBNot(QBType &a) {
    this->operands.emplace_back(std::unique_ptr<QBType>(a.clone()));
}

QBNot::QBNot(unique_ptr<QBType> a) {
    this->operands.emplace_back(std::move(a));
}
QBNot::QBNot(const QBNot& a) {
    this->operands.push_back(std::unique_ptr<QBType>(a.operands.front()->clone()));
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

QBType* QBNot::clone() const {
    return new QBNot(*this);
}
}
