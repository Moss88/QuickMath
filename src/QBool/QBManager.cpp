#include "QBool/QBManager.h"
#include "QBool/QBBit.h"
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::unique_ptr;
namespace QuickMath {
QBFunc QBManager::getBit(const std::string& name, int idx) {
    auto iter = vars.find(KeyPair(name, idx));
    if(iter == vars.end())
    {
        shared_ptr<QBBitShared> sbb = shared_ptr<QBBitShared>(new QBBitShared(name, idx));
        this->vars[QBManager::KeyPair(name, idx)] = sbb;
        return QBFunc(unique_ptr<QBBit>(new QBBit(sbb)));
    }
    return QBFunc(unique_ptr<QBBit>(new QBBit(iter->second)));
}

QBVector QBManager::getBitVector(const std::string& name, unsigned int size) {
    vector<QBFunc> bits;
    for(unsigned int i = 0; i < size; i++)
    {
        auto key = vars.find(KeyPair(name, i));
        if(key != vars.end())
            bits.push_back(QBFunc(unique_ptr<QBBit>(new QBBit(key->second))));
        else
        {
            shared_ptr<QBBitShared> sbb = std::make_shared<QBBitShared>(QBBitShared(name, i));
            this->vars[QBManager::KeyPair(name, i)] = sbb;
            bits.push_back(QBFunc(unique_ptr<QBBit>(new QBBit(sbb))));
        }
    }
    return QBVector(move(bits));
}

unsigned int QBManager::numberVars() const {
    return this->vars.size();
}

void QBManager::setValue(QBValue val, const std::string& name, int idx) {
    this->vars[QBManager::KeyPair(name, idx)]->setVar(val);
}
}
