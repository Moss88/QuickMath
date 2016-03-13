#include "QBool/QBBit.h"
namespace QuickMath {
QBBit::QBBit(std::shared_ptr<QBBitShared> bb)
    : bb(bb) {}

bool QBBit::isVar() const {
    return true;
}

std::string QBBit::toString() const {
    return bb->getName() + "[" + std::to_string(bb->getIndex()) + "]";
}

QBValue QBBit::value() const {
    return this->bb->value();
}

unsigned int QBBit::getIndex() const {
    return this->bb->getIndex();
}

const std::string& QBBit::getName() const {
    return this->bb->getName();
}

int64_t QBBit::getRef() const {
    return this->bb->getRef();
}

void QBBit::setValue(QBValue val) {
    this->bb->setVar(val);
}

std::unique_ptr<QMType> QBBit::clone() const {
    return std::unique_ptr<QBBit>(new QBBit(this->bb));
}

/////////////////// QBBitShared ///////////////////////////
int64_t QBBitShared::refCnt = 0;
QBBitShared::QBBitShared(const std::string& name, 
                             unsigned int index,
                             QBValue val) :
                             val(val), idx(index),  
                             ref(++QBBitShared::refCnt),
                             name(name) {}

QBBitShared::QBBitShared(const QBBitShared& other) {
    *this = other;
}


bool QBBitShared::isVar() const {
    return true;
}

std::string QBBitShared::toString() const {
    return name + "[" + std::to_string(idx) + "]";
}

QBValue QBBitShared::value() const {
    return this->val;
}

int64_t QBBitShared::getRef() const {
    return this->ref;
}

unsigned int QBBitShared::getIndex() const {
    return this->idx;
}

const std::string& QBBitShared::getName() const {
    return this->name;
}

void QBBitShared::setVar(QBValue val) {
    this->val = val;
}

std::unique_ptr<QMType> QBBitShared::clone() const {
    return std::unique_ptr<QBBitShared>(new QBBitShared(*this));
}
}
