#include "QBool/QBFunc.h"
#include "QBool/QBConstants.h"
#include "QBool/QBAnd.h"
#include "QBool/QBOr.h"
#include "QBool/QBNot.h"
#include "QMDefs.h"
#include <iostream>
using std::cout;
using std::endl;

using std::unique_ptr;

namespace QuickMath {
QBFunc::QBFunc(UQBType val) : bValue(move(val)) {}

QBFunc::QBFunc(bool val) {
    if(val)
        bValue = std::unique_ptr<QBOne>(new QBOne());
    else
        bValue = std::unique_ptr<QBZero>(new QBZero());
}

QBFunc::QBFunc(const QBFunc& func) {
    this->bValue = static_uptr_cast<QBType>(func.bValue->clone());
}

QBFunc::QBFunc(QBFunc&& func) {
    this->bValue = move(func.bValue);
}

QBFunc::QBFunc(const QBType *pVal) {
    this->bValue = static_uptr_cast<QBType>(pVal->clone());
}


QBFunc QBFunc::operator=(const QBFunc& func) {
    if(this == &func)
        return *this;
    this->bValue = static_uptr_cast<QBType>(func.bValue->clone());
    return *this;
}

QBFunc& QBFunc::operator=(QBFunc&& func) {
    this->bValue = std::move(func.bValue);
    return *this;
}

QBFunc& QBFunc::operator&=(const QBFunc& func) {
    if(func.get()->isOne())
        return *this;
    else if(this->get()->isOne())
    {
        *this = func;
        return *this;
    }
    else if(func.get()->isZero() || this->get()->isZero())
    {
        *this = QBFunc(false);
        return *this;
    }
    unique_ptr<QBAnd> newFunc = unique_ptr<QBAnd>(new QBAnd(std::move(this->bValue), *func.bValue));
    this->bValue = move(newFunc);
    return *this;
}

QBFunc& QBFunc::operator&=(QBFunc&& func) {
    if(func.get()->isOne())
        return *this;
    else if(this->get()->isOne())
    {
        this->bValue = std::move(func.bValue);
        return *this;
    }
    else if(func.get()->isZero() || this->get()->isZero())
    {
        *this = QBFunc(false);
        return *this;
    }
    
    this->bValue = unique_ptr<QBAnd>(new QBAnd(std::move(this->bValue), std::move(func.bValue)));
    return *this;
}

QBFunc operator&(QBFunc&& aFunc, QBFunc&& bFunc) {
    if(aFunc.get()->isOne())
        return std::move(bFunc);
    else if(bFunc.get()->isOne())
        return std::move(aFunc);
    else if(aFunc.get()->isZero() || bFunc.get()->isZero())
        return QBFunc(false);
    return QBFunc(unique_ptr<QBAnd>(new QBAnd(std::move(aFunc.bValue), std::move(bFunc.bValue))));
}

QBFunc operator&(const QBFunc& aFunc, QBFunc&& bFunc) {
    if(aFunc.get()->isOne())
        return std::move(bFunc);
    else if(bFunc.get()->isOne())
        return aFunc;
    else if(aFunc.get()->isZero() || bFunc.get()->isZero())
        return QBFunc(false);
    return QBFunc(unique_ptr<QBAnd>(new QBAnd(*aFunc.bValue, std::move(bFunc.bValue))));
}

QBFunc operator&(QBFunc&& aFunc, const QBFunc& bFunc) {
   return bFunc & std::move(aFunc); 
}

QBFunc operator&(const QBFunc& aFunc, const QBFunc& bFunc) {
    if(aFunc.get()->isOne())
        return bFunc;
    else if(bFunc.get()->isOne())
        return aFunc;
    else if(aFunc.get()->isZero() || bFunc.get()->isZero())
        return QBFunc(false);
    return QBFunc(unique_ptr<QBAnd>(new QBAnd(*aFunc.bValue, *bFunc.bValue)));
}

QBFunc operator|(const QBFunc& a, const QBFunc& b) {
    if(a.get()->isZero())
        return b;
    else if(b.get()->isZero())
        return a;
    else if(a.get()->isOne() || b.get()->isOne())
        return QBFunc(true);
    return QBFunc(unique_ptr<QBOr>(new QBOr(*a.bValue, *b.bValue)));
}

QBFunc operator|(const QBFunc& a, QBFunc&& b) {
    if(a.get()->isZero())
        return std::move(b);
    else if(b.get()->isZero())
        return a;
    else if(a.get()->isOne() || b.get()->isOne())
        return QBFunc(true);
    return QBFunc(unique_ptr<QBOr>(new QBOr(*a.bValue, move(b.bValue))));
}

QBFunc operator|(QBFunc&& a, const QBFunc& b) {
    return b | std::move(a);
}

QBFunc operator|(QBFunc&& a, QBFunc&& b) {
    if(a.get()->isZero())
        return std::move(b);
    else if(b.get()->isZero())
        return std::move(a);
    else if(a.get()->isOne() || b.get()->isOne())
        return QBFunc(true);
    return QBFunc(unique_ptr<QBOr>(new QBOr(std::move(a.bValue), move(b.bValue))));
}


QBFunc& QBFunc::operator|=(const QBFunc& func) {
    if(func.get()->isZero())
        return *this;
    else if(this->get()->isZero())
    {
        *this = func;
        return *this;
    }
    else if(func.get()->isOne() | this->get()->isOne())
    {
        *this = QBFunc(true);
        return *this;
    }
    unique_ptr<QBOr> newFunc = unique_ptr<QBOr>(new QBOr(std::move(this->bValue), *func.bValue));
    this->bValue = move(newFunc);
    return *this;
}

QBFunc& QBFunc::operator|=(QBFunc&& func) {
    if(func.get()->isZero())
        return *this;
    else if(this->get()->isZero())
        this->bValue = std::move(func.bValue);
    else if(func.get()->isOne() | this->get()->isOne())
        *this = QBFunc(true);
    else
        this->bValue = unique_ptr<QBOr>(new QBOr(std::move(this->bValue), 
                                                     std::move(func.bValue)));
    return *this;
}


QBFunc QBFunc::operator|=(const QBType& func) {
    if(func.isZero())
        return *this;
    else if(this->get()->isZero())
    {
        *this = QBFunc(&func);
        return *this;
    }
    else if(func.isOne() | this->get()->isOne())
        return QBFunc(true);

    unique_ptr<QBOr> newFunc = unique_ptr<QBOr>(new QBOr(std::move(this->bValue), func));
    this->bValue = move(newFunc);
    return *this;
}

QBFunc operator!(QBFunc&& func) {
    if(func.get()->isZero())
        return QBFunc(true);
    else if(func.get()->isOne())
        return QBFunc(false);
    else if(func.get()->isNot())
        return QBFunc(unique_ptr<QBType>(std::move(*static_cast<QBNot*>(func.get())->begin())));
    return QBFunc(unique_ptr<QBNot>(new QBNot(std::move(func.bValue))));
}

QBFunc operator!(const QBFunc& func) {
    if(func.get()->isZero())
        return QBFunc(true);
    else if(func.get()->isOne())
        return QBFunc(false);
    else if(func.get()->isNot())
        return QBFunc(static_uptr_cast<QBType>(static_cast<const QBNot*>(func.get())->begin()->get()->clone()));
    return QBFunc(unique_ptr<QBNot>(new QBNot(*func.bValue)));
}
  
QBFunc biConditional(const QBFunc& antecedent, const QBFunc& consequent) {
    return (!antecedent & !consequent) |  (antecedent & consequent);
} 

QBFunc implication(const QBFunc& antecedent, const QBFunc& consequent) {
    return (!antecedent) |  (antecedent & consequent);
}

const QBType* QBFunc::get() const {
    return this->bValue.get();
}

QBType* QBFunc::get() {
    return this->bValue.get();
}

std::string QBFunc::toString() const {
    return this->bValue->toString();
}

QBValue QBFunc::evaluate() const {
    return this->bValue->value();
}

bool QBFunc::isExpr() const {
    return this->bValue->isExpr();
}
bool QBFunc::isVar() const {
    return this->bValue->isVar();
}

std::ostream& operator<<(std::ostream &stream, const QBFunc& func) {
    stream << func.toString();
    return stream;
}

}
