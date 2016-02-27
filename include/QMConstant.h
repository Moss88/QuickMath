#ifndef QM_CONSTANT_H
#define QM_CONSTANT_H
#include "QMType.h"
namespace QuickMath {
class QMConstant : public QMType {
    bool isConstant() const;
};
}
#endif
