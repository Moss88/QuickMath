#include "QBool/QBAnd.h"
#include "QMDefs.h"
#include <iostream>
namespace QuickMath {
using std::unique_ptr;

QBAnd::QBAnd(unique_ptr<QBType> a, unique_ptr<QBType> b) {       
    if(a.get()->isAnd())
    {
        QBAnd* andPtr = static_cast<QBAnd*>(a.get());
        this->operands = std::move(andPtr->operands);
    }
    else
        this->operands.emplace_back(move(a));

    if(b->isAnd())
    {
        QBAnd* ptr = static_cast<QBAnd*>(b.get());
        std::move(ptr->operands.begin(), ptr->operands.end(), std::back_inserter(this->operands));
    }
    else
        this->operands.emplace_back(move(b));
}



QBAnd::QBAnd(unique_ptr<QBType> a, const QBType &b) {       
    if(a.get()->isAnd())
    {
        QBAnd* andPtr = static_cast<QBAnd*>(a.get());
        this->operands = std::move(andPtr->operands);
    }
    else
        this->operands.push_back(move(a));

    if(b.isAnd())
    {
        const QBAnd* ptr = static_cast<const QBAnd*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(static_uptr_cast<QBType>(op.get()->clone()));
    }
    else
        this->operands.push_back(static_uptr_cast<QBType>(b.clone()));
}

QBAnd::QBAnd(const QBType& a, unique_ptr<QBType> b) : 
                                    QBAnd::QBAnd(move(b), a) {}

QBAnd::QBAnd(const QBType &a, const QBType &b) {
    if(a.isAnd())
    {
        const QBAnd* ptr = static_cast<const QBAnd*>(&a);
        for(auto &op:*ptr)
            this->operands.push_back(static_uptr_cast<QBType>(op.get()->clone()));
    }
    else
        this->operands.push_back(static_uptr_cast<QBType>(a.clone()));

    if(b.isAnd())
    {
        const QBAnd* ptr = static_cast<const QBAnd*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(static_uptr_cast<QBType>(op.get()->clone()));
    }
    else
        this->operands.push_back(static_uptr_cast<QBType>(b.clone()));
}

QBAnd::QBAnd(const QBAnd& other) {
    for(auto &op:other.operands)
        this->operands.push_back(static_uptr_cast<QBType>(op->clone()));
}

std::string QBAnd::toString() const {
    std::string str = "(";
    auto lastPos = operands.cend() - 1;
    for(auto iter = operands.cbegin(); iter != operands.cend(); ++iter)
    {
        str += (*iter)->toString();
        if(iter != lastPos)
            str += " & ";
    }
    return str + ")";
}

QBValue QBAnd::value() const {
    bool hasDontCare = false;
    for(auto &op:operands)
    {
        if(op->value() == QBValue::Zero)
            return QBValue::Zero;
        else if(op->value() == QBValue::DontCare)
            hasDontCare = true;
    }
    if(hasDontCare)
        return QBValue::DontCare;
    return QBValue::One;
}

bool QBAnd::isAnd() const {
    return true;
}


std::unique_ptr<QMType> QBAnd::clone() const {
    return std::unique_ptr<QBAnd>(new QBAnd(*this));
}


}
