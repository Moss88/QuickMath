#include "QBool/QBVector.h"
#include "QBool/QBFunc.h"
#include "QBool/QBAlgorithms.h"
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

    // Perform Algorithm
    int i;
    QBFunc x;
    QBFunc func;
    bool xSet = false;
    for(i = this->size() - 1; i >= 0; i--)
    {
        // Generate term = ~AB;
        QBFunc term = !bits[i] & other.bits[i];

        // Generate X
        QBFunc eq1 =  bits[i] & other.bits[i];
        QBFunc eq2 =  (!bits[i]) & (!other.bits[i]);

        if(xSet)
        {
            // Use Old X Term
            func |= term & x;
            x = x & (eq1 | eq2);
        }
        else
        {
            x = eq1 | eq2;
            func = term;
            xSet = true;
        }
    }
    return move(func);
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

}
