#include "QFunc/QFConstantD.h"
namespace QuickMath {
QFConstantD::QFConstantD(double val) : value(val) {}

QFConstantD::QFConstantD(const QFConstantD& other) : 
                                     value(other.value) {}

std::unique_ptr<QMType> QFConstantD::clone() const {
    return std::unique_ptr<QMType>(new QFConstantD(*this));
}

std::string QFConstantD::toString() const {
    return std::move(std::to_string(value));
}

double QFConstantD::getValue() const {
    return value;
}    

}
