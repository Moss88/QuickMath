#include "QBool/QBOr.h"
namespace QuickMath {
using std::unique_ptr;

QBOr::QBOr(unique_ptr<QBType> a, unique_ptr<QBType> b) {
    if(a.get()->isOr())
    {
        QBOr* orPtr = static_cast<QBOr*>(a.get());
        this->operands = std::move(orPtr->operands);
    }
    else
        this->operands.push_back(move(a));

    if(b->isOr())
    {
        QBOr* ptr = static_cast<QBOr*>(b.get());
        std::move(ptr->operands.begin(), ptr->operands.end(), std::back_inserter(this->operands));
    }
    else
        this->operands.emplace_back(move(b));
}

QBOr::QBOr(unique_ptr<QBType> a, const QBType &b) {
    if(a.get()->isOr())
    {
        QBOr* andPtr = static_cast<QBOr*>(a.get());
        for(auto &op:*andPtr)
            this->operands.push_back(move(op));
    }
    else
        this->operands.push_back(move(a));

    if(b.isOr())
    {
        const QBOr* ptr = static_cast<const QBOr*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<QBType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<QBType>(b.clone()));
}

QBOr::QBOr(const QBType& a, unique_ptr<QBType> b) :
                                         QBOr(std::move(b), a) {}

QBOr::QBOr(const QBType& a, const QBType& b) {
    if(a.isOr())
    {
        const QBOr* ptr = static_cast<const QBOr*>(&a);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<QBType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<QBType>(a.clone()));

    if(b.isOr())
    {
        const QBOr* ptr = static_cast<const QBOr*>(&b);
        for(auto &op:*ptr)
            this->operands.push_back(std::unique_ptr<QBType>(op.get()->clone()));
    }
    else
        this->operands.push_back(unique_ptr<QBType>(b.clone()));
}

QBOr::QBOr(const QBOr& other) {
    for(auto &op:other.operands)
        this->operands.push_back(unique_ptr<QBType>(op->clone()));
}


std::string QBOr::toString() const {
    std::string str = "(";
    auto lastPos = operands.cend() - 1;
    for(auto iter = operands.cbegin(); iter != operands.cend(); ++iter)
    {
        str += (*iter)->toString();
        if(iter != lastPos)
            str += " | ";
    }
    return str + ")";
}

QBValue QBOr::value() const {
    bool hasDontCare = false;
    for(auto &op:operands)
    {
        if(op->value() == QBValue::One)
            return QBValue::One;
        else if(op->value() == QBValue::DontCare)
            hasDontCare = true;
    }
    if(hasDontCare)
        return QBValue::DontCare;
    return QBValue::Zero;
}

bool QBOr::isOr() const {
    return true;
}


QBType* QBOr::clone() const {
    return new QBOr(*this);
}
}
