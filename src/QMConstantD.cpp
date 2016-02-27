#include "QMConstantD.h"
namespace QuickMath {
QMConstantD::QMConstantD(double val) : value(val) {}

QMConstantD::QMConstantD(const QMConstantD& other) : 
                                     value(other.value) {}

QMType* QMConstantD::clone() const {
    return new QMConstantD(*this);
}

std::string QMConstantD::toString() const {
    return std::move(std::to_string(value));
}
}
