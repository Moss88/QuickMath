#ifndef QB_MANAGER_H
#define QB_MANAGER_H
#include <string>
#include <map>
#include <memory>
#include <list>
#include "./QBFunc.h"
#include "./QBVector.h"
#include "./QBBit.h"

namespace QuickMath {

class QBManager {
    struct KeyPair {
        KeyPair() = default;
        KeyPair(std::string name, unsigned int idx) : name(name), idx(idx) {}
        std::string name;
        int idx = 0;
        bool operator<(const KeyPair& other) const {
            return (this->name.compare(other.name) < 0) ||
                    ((this->name == other.name) && (this->idx < other.idx));
        }
    };

public:
    QBManager();
    QBFunc getTempVar();
    QBFunc getBit(const std::string& name, int idx = 0);
    QBVector getBitVector(const std::string& name, unsigned int size);
    void setValue(QBValue val, const std::string& name, int idx = 0);
    unsigned int numberVars() const;
    ~QBManager();

private:
    int64_t tCount = 0;
    std::list<std::shared_ptr<QBBitShared>> tempVars;
    std::map<KeyPair, std::shared_ptr<QBBitShared>> vars;
};

}

#endif // BOOLMANAGER_H

