#include "gtest/gtest.h"
#include "QBool/QBManager.h"
#include "QBool/QBVector.h"
#include "QBool/QBExpr.h"
#include "QBool/QBAlgorithms.h"
#include "QBool/QBAnd.h"

#include<iostream>
#include<functional>

using namespace std;
using namespace QuickMath;

unsigned int treeDepth(const QBType* func, unsigned int cnt = 0) {
    if(func->isExpr())
    {
        auto maxDepth = cnt;
        const QBExpr* expr = static_cast<const QBExpr*>(func);
        for(auto &op:*expr)
        {
            unsigned int newDepth = treeDepth(op.get(), cnt);
            if(newDepth > maxDepth)
                maxDepth = newDepth;
        }
        cnt = maxDepth;
    }
    return ++cnt;
}

unsigned int litCount(const QBType* func) {
    unsigned int varCount = 0;
    if(func->isExpr())
    {
        const QBExpr* expr = static_cast<const QBExpr*>(func);
        for(auto &op:*expr)
            varCount += litCount(op.get());
    }
    else if(func->isVar() | func->isOne() | func->isZero())
        varCount++;
    return varCount;
}


TEST(QBOp, Not) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    bm.setValue(QBValue::Zero, "a");
    EXPECT_EQ(a.evaluate(), QBValue::Zero);
    QBFunc aNot = !a;
    EXPECT_EQ(aNot.evaluate(), QBValue::One);
    QBFunc aNotNot = !aNot;
    EXPECT_EQ(aNotNot.evaluate(), QBValue::Zero);
}

TEST(QBOp, AndNoValue) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    QBFunc c = bm.getBit("c");
    QBFunc d = bm.getBit("d");

    QBFunc func = a & b;
    func &= c & d;
    auto exprPtr = dynamic_cast<QBAnd*>(func.get());
    ASSERT_TRUE(exprPtr);
    EXPECT_EQ(exprPtr->size(), 4);
}

TEST(QBOp, And) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    QBFunc c = bm.getBit("c");
    QBFunc d = bm.getBit("d");
    bm.setValue(QBValue::One, "a");
    bm.setValue(QBValue::One, "b");
    bm.setValue(QBValue::Zero, "c");

    QBFunc func = a & b;
    EXPECT_EQ(func.evaluate(), QBValue::One);
    func &= c;
    EXPECT_EQ(func.evaluate(), QBValue::Zero);
    bm.setValue(QBValue::One, "c");
    EXPECT_EQ(func.evaluate(), QBValue::One);
}

TEST(QBOp, Or) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    QBFunc c = bm.getBit("c");
    bm.setValue(QBValue::Zero, "a");
    bm.setValue(QBValue::Zero, "b");
    bm.setValue(QBValue::One, "c");

    QBFunc func = a | b;
    EXPECT_EQ(func.evaluate(), QBValue::Zero);
    func |= c;
    EXPECT_EQ(func.evaluate(), QBValue::One);
    bm.setValue(QBValue::Zero, "c");
    EXPECT_EQ(func.evaluate(), QBValue::Zero);

    func = a | b | c;
    EXPECT_EQ(treeDepth(func.get()), 2);
}

TEST(QBOp, implication) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    bm.setValue(QBValue::Zero, "a");
    bm.setValue(QBValue::Zero, "b");

    QBFunc func = implication(a, b);
    EXPECT_EQ(func.evaluate(), QBValue::One);
    
    bm.setValue(QBValue::Zero, "a");
    bm.setValue(QBValue::One, "b");
    EXPECT_EQ(func.evaluate(), QBValue::One);


    bm.setValue(QBValue::One, "a");
    bm.setValue(QBValue::Zero, "b");
    EXPECT_EQ(func.evaluate(), QBValue::Zero);
    
    bm.setValue(QBValue::One, "a");
    bm.setValue(QBValue::One, "b");
    EXPECT_EQ(func.evaluate(), QBValue::One);
}

TEST(QBOp, biConditional) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    bm.setValue(QBValue::Zero, "a");
    bm.setValue(QBValue::Zero, "b");

    QBFunc func = biConditional(a, b);
    EXPECT_EQ(func.evaluate(), QBValue::One);
  
    bm.setValue(QBValue::One, "a");
    bm.setValue(QBValue::Zero, "b");
    EXPECT_EQ(func.evaluate(), QBValue::Zero);


    bm.setValue(QBValue::Zero, "a");
    bm.setValue(QBValue::One, "b");
    EXPECT_EQ(func.evaluate(), QBValue::Zero);


    bm.setValue(QBValue::One, "a");
    bm.setValue(QBValue::One, "b");
    EXPECT_EQ(func.evaluate(), QBValue::One);
}


TEST(QBOp, Constants)
{
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");

    QBFunc one(true), zero(false);
    QBFunc eq = a & one;
    EXPECT_EQ(treeDepth(eq.get()), 1);
    eq = a & b & one;
    EXPECT_EQ(treeDepth(eq.get()), 2);
    EXPECT_EQ(litCount(eq.get()), 2);

    eq = a & zero;
    EXPECT_TRUE(eq.get()->isZero());

    QBFunc oneCpy = one;
    oneCpy &= a;
    EXPECT_EQ(litCount(oneCpy.get()), 1);
    EXPECT_TRUE(oneCpy.get()->isVar());

    eq = a | zero;
    EXPECT_EQ(treeDepth(eq.get()), 1);
    eq = a | b | zero;
    EXPECT_EQ(treeDepth(eq.get()), 2);
    EXPECT_EQ(litCount(eq.get()), 2);

    eq = a | one;
    EXPECT_TRUE(eq.get()->isOne());

}


