#ifndef QM_CONSTANT_D_H
#define QM_CONSTANT_D_H
#include "QMConstant.h"
namespace QuickMath {
class QMConstantD : public QMConstant {
    public:
        QMConstantD() = default;
        QMConstantD(double val);
        QMConstantD(const QMConstantD& other);
        
        QMType* clone() const;
        std::string toString() const;
    private:
        double value;
};
}
#endif
