#include "QFunc/QFVar.h"

namespace QuickMath {

QFVar::QFVar(const std::string& name, int idx) :
                                        name(name),
                                        idx(idx) {}
QFVar::QFVar(const QFVar& var) : name(var.name),
                                 idx(var.idx) {}
QFVar::QFVar(QFVar&& var) : name(std::move(var.name)),
                            idx(var.idx) {}

QFVar& QFVar::operator=(const QFVar& other) {
    if(this != &other)
    {
        this->name = other.name;
        this->idx = other.idx;
    } 
    return *this;
}

QFVar& QFVar::operator=(QFVar&& other) {
    this->name = std::move(other.name);
    this->idx = other.idx;
    return *this;
}

std::unique_ptr<QMType> QFVar::clone() const {
    return std::unique_ptr<QFVar>(new QFVar(*this));
}

std::string QFVar::toString() const {
    return name + "_" + std::to_string(idx);
}

bool QFVar::isVar() const {
    return true;
}
        
const std::string& QFVar::getName() const {
    return name;
}

int QFVar::getIndex() const {
    return idx;
}

bool QFVar::operator==(const QFVar& rhs) const {
    return (name == rhs.name) && (idx == rhs.idx);
}

bool QFVar::operator<(const QFVar& rhs) const {
    return (name < rhs.name) || 
           ((name == rhs.name) && (idx < rhs.idx));
}

QFVar::~QFVar(){}
}
