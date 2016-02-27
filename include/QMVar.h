#ifndef QM_VAR_H
#define QM_VAR_H
#include "QMType.h"

namespace QuickMath {

class QMVar : public QMType {
    public:
        QMVar() = default;
        QMVar(const std::string& name, int idx = 0);
        QMVar(const QMVar& var);
        QMVar(QMVar&& var);
        QMVar& operator=(const QMVar& other);
        QMVar& operator=(QMVar&& other);


        QMType* clone() const;
        std::string toString() const;
        bool isVar() const;
        
        const std::string& getName() const;
        int getIndex() const;
        bool operator==(const QMVar& rhs) const;
        bool operator<(const QMVar& rhs) const;
        virtual ~QMVar();
    private:
        std::string name;
        int idx = 0;
};

}

#endif

