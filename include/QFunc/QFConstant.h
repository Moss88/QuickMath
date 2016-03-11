#ifndef QF_CONSTANT_H
#define QF_CONSTANT_H
#include "./QFType.h"
namespace QuickMath {
class QFConstant : public QFType {
    bool isConstant() const;
};
}
#endif
