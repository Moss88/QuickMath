#include "QBool/QBType.h"
namespace QuickMath {
std::ostream& operator<< (std::ostream& outStream, const QBType& val) {
    outStream << val.toString();
    return outStream;
}
}
