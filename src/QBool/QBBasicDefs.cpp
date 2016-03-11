#include "QBool/QBBasicDefs.h"
namespace QuickMath {
std::string to_string(const QBValue& value) {
    if(value == QBValue::One)
        return "1";
    else if(value == QBValue::Zero)
        return "0";
    else
        return "???";
}
}
