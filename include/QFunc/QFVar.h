#ifndef QF_VAR_H
#define QF_VAR_H
#include "./QFType.h"

namespace QuickMath {

class QFVar : public QFType {
    public:
        QFVar() = default;
        QFVar(const std::string& name, int idx = 0);
        QFVar(const QFVar& var);
        QFVar(QFVar&& var);
        QFVar& operator=(const QFVar& other);
        QFVar& operator=(QFVar&& other);


        std::unique_ptr<QMType> clone() const;
        std::string toString() const;
        bool isVar() const;
        
        const std::string& getName() const;
        int getIndex() const;
        bool operator==(const QFVar& rhs) const;
        bool operator<(const QFVar& rhs) const;
        virtual ~QFVar();
    private:
        std::string name;
        int idx = 0;
};

}

#endif

