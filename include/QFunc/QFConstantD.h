#ifndef QF_CONSTANT_D_H
#define QF_CONSTANT_D_H
#include "./QFConstant.h"
namespace QuickMath {
class QFConstantD : public QFConstant {
    public:
        QFConstantD() = default;
        QFConstantD(double val);
        QFConstantD(const QFConstantD& other);
        
        std::unique_ptr<QMType> clone() const;
        std::string toString() const;
    private:
        double value;
};
}
#endif
