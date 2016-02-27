#include "QMVar.h"

namespace QuickMath {

QMVar::QMVar(const std::string& name, int idx) :
                                        name(name),
                                        idx(idx) {}
QMVar::QMVar(const QMVar& var) : name(var.name),
                                 idx(var.idx) {}
QMVar::QMVar(QMVar&& var) : name(std::move(var.name)),
                            idx(var.idx) {}

QMVar& QMVar::operator=(const QMVar& other) {
    if(this != &other)
    {
        this->name = other.name;
        this->idx = other.idx;
    } 
    return *this;
}

QMVar& QMVar::operator=(QMVar&& other) {
    this->name = std::move(other.name);
    this->idx = other.idx;
    return *this;
}

QMType* QMVar::clone() const {
    return new QMVar(*this);
}

std::string QMVar::toString() const {
    return name + "_" + std::to_string(idx);
}

bool QMVar::isVar() const {
    return true;
}
        
const std::string& QMVar::getName() const {
    return name;
}

int QMVar::getIndex() const {
    return idx;
}

bool QMVar::operator==(const QMVar& rhs) const {
    return (name == rhs.name) && (idx == rhs.idx);
}

bool QMVar::operator<(const QMVar& rhs) const {
    return (name < rhs.name) || 
           ((name == rhs.name) && (idx < rhs.idx));
}

QMVar::~QMVar(){}
}
