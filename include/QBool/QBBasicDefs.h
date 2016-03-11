#ifndef QBBASICDEFS_H
#define QBBASICDEFS_H
#include<string>
#include<memory>
namespace QuickMath {
class QBType;
class QBBit;

typedef std::shared_ptr<QBType> SQBType;
typedef std::unique_ptr<QBType> UQBType;
typedef std::shared_ptr<QBBit> SQBBit;
typedef std::unique_ptr<QBBit> UQBBit;

enum class QBValue {Unknown, One, Zero, DontCare};

std::string to_string(const QBValue& value);
}
#endif // BOOLBASICDEFS_H

