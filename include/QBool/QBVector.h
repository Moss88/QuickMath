#ifndef QB_BIT_VECTOR_H
#define QB_BIT_VECTOR_H
#include <vector>
#include "./QBFunc.h"

namespace QuickMath {
class QBFunc;
class QBVector {
public:
    QBVector() = default;
    QBVector(const std::vector<QBFunc> &bits);
    QBVector(const std::vector<QBFunc> &&bits);
    QBFunc operator&(const QBVector& other)  const;
    QBFunc operator|(const QBVector& other)  const;
    QBFunc operator<(const QBVector& other)  const;
    QBFunc operator<=(const QBVector& other) const;
    QBFunc operator>(const QBVector& other)  const;
    QBFunc operator>=(const QBVector& other) const;
    QBFunc operator==(const QBVector& other) const;
    QBFunc operator!=(const QBVector& other) const;

    std::vector<QBFunc>::iterator begin();
    std::vector<QBFunc>::iterator end();
    std::vector<QBFunc>::const_iterator begin() const;
    std::vector<QBFunc>::const_iterator end() const;
    unsigned int size() const;

private:
    std::vector<QBFunc> bits;
};
}
#endif // BOOLBITVECTOR_H

