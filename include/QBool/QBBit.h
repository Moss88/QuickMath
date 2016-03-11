#ifndef QB_BIT_H
#define QB_BIT_H
#include <string>
#include "./QBType.h"

namespace QuickMath {
class QBBitShared : public QBType {
public:
    QBBitShared(const std::string& name, 
                  unsigned int index = 0,
                  QBValue val = QBValue::Unknown);
    QBBitShared(const QBBitShared& other);
    virtual bool isVar() const;
    virtual std::string toString() const;
    virtual QBValue value() const;
    unsigned int getIndex() const;
    int64_t getRef() const;
    const std::string& getName() const;
    void setVar(QBValue val);
    QBType* clone() const;

private:
    static int64_t refCnt;

    QBValue val = QBValue::Unknown;
    unsigned int idx = 0;
    int64_t ref = 0;
    std::string name = "";
};

class QBBit : public QBType {
public:
    QBBit(std::shared_ptr<QBBitShared> bb);
    void setValue(QBValue val);
    bool isVar() const;
    std::string toString() const;
    QBValue value() const;
    int64_t getRef() const;
    QBType* clone() const;
    unsigned int getIndex() const;
    const std::string& getName() const;

private:
    std::shared_ptr<QBBitShared> bb;
};
}

#endif // BOOLBIT_H

