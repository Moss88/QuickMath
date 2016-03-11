#ifndef QB_OR_H
#define QB_OR_H
#include "./QBNaryExpr.h"

namespace QuickMath {

class QBOr : public QBNaryExpr {
public:
    QBOr() = default;
    QBOr(std::unique_ptr<QBType> a, const QBType &b);
    QBOr( const QBType &a, std::unique_ptr<QBType> b);
    QBOr(std::unique_ptr<QBType> a, std::unique_ptr<QBType> b);
    QBOr(const QBType& a, const QBType& b);
    QBOr(const QBOr& other);
    std::string toString() const;
    QBValue value() const;
    QBType* clone() const;
    bool isOr() const;

};
}
#endif // BOOLOR_H

