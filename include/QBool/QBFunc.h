#ifndef QB_FUNC_H
#define QB_FUNC_H
#include "./QBBasicDefs.h"
#include "./QBType.h"
#include <iostream>

namespace QuickMath {

class QBFunc {
public:
    QBFunc() = default;
    QBFunc(std::unique_ptr<QBType> pVal);
    QBFunc(const QBType *pVal);
    QBFunc(bool val);
    QBFunc(const QBFunc& func);
    QBFunc(QBFunc&& func);

    // TODO implement move functionality to save performance
    // right now operations are very inefficent
    QBFunc operator=(const QBFunc& func);
    QBFunc& operator=(QBFunc&& func);

    QBFunc & operator&=(const QBFunc& func);
    QBFunc & operator&=(QBFunc&& func);
    
    
    QBFunc & operator|=(QBFunc&& func);
    
    QBFunc & operator|=(const QBFunc& func);
    QBFunc operator|=(const QBType& func);


    // Static Operators
    friend QBFunc operator|(QBFunc&& aFunc, QBFunc&& bFunc);
    friend QBFunc operator|(const QBFunc& aFunc, QBFunc&& bFunc);
    friend QBFunc operator|(QBFunc&& aFunc, const QBFunc& bFunc);
    friend QBFunc operator|(const QBFunc& aFunc, const QBFunc& bFunc);

    friend QBFunc operator&(QBFunc&& aFunc, QBFunc&& bFunc);
    friend QBFunc operator&(const QBFunc& aFunc, QBFunc&& bFunc);
    friend QBFunc operator&(QBFunc&& aFunc, const QBFunc& bFunc);
    friend QBFunc operator&(const QBFunc& aFunc, const QBFunc& bFunc);

    friend QBFunc operator!(const QBFunc& func);
    friend QBFunc operator!(QBFunc&& func);
    
    friend QBFunc biConditional(const QBFunc& antecedent, const QBFunc& consequent); 
    friend QBFunc implication(const QBFunc& antecedent, const QBFunc& consequent); 


    //QBFunc operator!() const;
    QBValue evaluate() const;
    bool isExpr() const;
    bool isVar() const;
    const QBType* get() const;
    QBType* get();
    std::string toString() const;

private:
    UQBType bValue;
};

std::ostream& operator<<(std::ostream &stream, const QBFunc& func);

}

#endif // BOOLFUNC_H

