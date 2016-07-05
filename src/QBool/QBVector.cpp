#include "QBool/QBVector.h"
#include "QBool/QBFunc.h"
#include "QBool/QBAlgorithms.h"
#include "QBool/QBBit.h"
#include <iostream>
using std::cout;
using std::endl;
using std::move;
namespace QuickMath {
void sizeExcept(const QBVector& a, const QBVector& b){
    if(a.size() != b.size())
        throw std::runtime_error("QBVector: bitvectors do not match " +
                                 std::to_string(a.size()) + " and " +
                                 std::to_string(b.size()));
}

QBVector::QBVector(const std::vector<QBFunc> &bits) {
    this->bits.insert(this->bits.end(), bits.begin(), bits.end());
}

QBVector::QBVector(const std::vector<QBFunc> &&bits) {
    this->bits = move(bits);
}


QBFunc QBVector::operator<(const QBVector& other) const {
    sizeExcept(*this, other);
    
    std::function<QBFunc(int)> recurGen = [&](int idx) {
        if(idx == 0)
            return !this->bits[0] & other.bits[0];
        return (!this->bits[idx] & other.bits[idx]) | 
            (((this->bits[idx] & other.bits[idx]) | ((!this->bits[idx]) & (!other.bits[idx]))) & recurGen(idx - 1)); 
    };
    return recurGen(this->bits.size() - 1);
   
}

QBFunc QBVector::operator<=(const QBVector& other) const {
    QBFunc func = (*this < other) | (*this == other);
    return move(func);
}

QBFunc QBVector::operator>(const QBVector& other)  const {
    return move(other < *this);
}

QBFunc QBVector::operator>=(const QBVector& other) const {
    return move(other <= *this);
}

QBFunc QBVector::operator==(const QBVector& other) const {
    QBFunc func(true);
    sizeExcept(*this, other);
    auto otherIter = other.begin();
    for(auto thisIter = begin(); thisIter != end(); thisIter++, otherIter++)
        func &= ((*thisIter) & (*otherIter)) | ((!*thisIter) & (!*otherIter));
    return func;
}

QBFunc QBVector::operator!=(const QBVector& other) const {
    return move(!(*this == other));
}

std::vector<QBFunc>::iterator QBVector::begin() {
    return bits.begin();
}

std::vector<QBFunc>::iterator QBVector::end() {
    return bits.end();
}

std::vector<QBFunc>::const_iterator QBVector::begin() const {
    return this->bits.cbegin();
}
std::vector<QBFunc>::const_iterator QBVector::end() const {
    return this->bits.cend();
}

unsigned int QBVector::size() const {
    return bits.size();
}

int64_t QBVector::convertToInt() const {
    int64_t twoPow = 1;
    int64_t decNum = 0; 
    for(unsigned int i = 0; i < bits.size(); i++)
    {
        auto value = static_cast<const QBBit*>(bits[i].get())->value();
        if(value == QBValue::One)
            decNum += twoPow;
        else if(value != QBValue::Zero)
            return -1;
        twoPow *= 2;
    }
    return decNum;    
}

}
