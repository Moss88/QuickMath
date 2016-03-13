#ifndef QB_NOT_H
#define QB_NOT_H
#include "./QBExpr.h"

namespace QuickMath {

class QBNot : public QBExpr {
public:
    QBNot() = default;
    QBNot(const QBNot &a);
    QBNot(QBType& a);
    QBNot(std::unique_ptr<QBType> a);
    std::string toString() const;
    QBValue value() const;
    std::unique_ptr<QMType> clone() const;
    bool isNot() const;

};

}
#endif // BOOLNOT_H

