#include "QMType.h"

namespace QuickMath {


    bool QMType::isBoolType() const {
        return false;
    }

    bool QMType::isFuncType() const {
        return false;
    }

    bool QMType::isMixedType() const {
        return false;
    }

    std::ostream& operator<< (std::ostream& outStream, const QMType& val) {
        outStream << val.toString();
        return outStream;
    }

}
