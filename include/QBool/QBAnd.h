#ifndef QBAND_H
#define QBAND_H
#include "./QBNaryExpr.h"
namespace QuickMath {
class QBFunc;
class QBAnd : public QBNaryExpr {
public:
    QBAnd() = default;
    QBAnd(const QBType& a, const QBType& b);
    QBAnd(std::unique_ptr<QBType> a, const QBType& b);
    QBAnd(const QBType& a, std::unique_ptr<QBType> b);
    QBAnd(std::unique_ptr<QBType> a, std::unique_ptr<QBType> b);
    QBAnd(const QBAnd& other);

    std::string toString() const;
    QBValue value() const;
    std::unique_ptr<QMType> clone() const;
    bool isAnd() const;
};
}
#endif // BOOLAND_H

