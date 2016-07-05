#include "gtest/gtest.h"
#include "QBool/QBManager.h"
#include "QBool/QBVector.h"
#include "QBool/QBExpr.h"
#include "QBool/QBAlgorithms.h"

#include<iostream>
using namespace std;
using namespace QuickMath;
TEST(QBVector, lt) {
    {
        QBManager bm;
        QBVector vA = bm.getBitVector("a", 2);
        QBVector vB = bm.getBitVector("b", 2);

        QBFunc lt = vA < vB;
        bm.setValue(QBValue::One, "a", 0);
        bm.setValue(QBValue::Zero, "a", 1);
        bm.setValue(QBValue::Zero, "b", 0);
        bm.setValue(QBValue::One, "b", 1);
        QBValue val = lt.evaluate();
        EXPECT_EQ(val, QBValue::One);

        bm.setValue(QBValue::One, "a", 1);
        val = lt.evaluate();
        EXPECT_EQ(val, QBValue::Zero);

        bm.setValue(QBValue::Zero, "a", 0);
        val = lt.evaluate();
        EXPECT_EQ(val, QBValue::Zero);
    }
    {
        QBManager bm;
        QBVector vA = bm.getBitVector("a", 3);
        QBVector vB = bm.getBitVector("b", 3);

        QBFunc lt = vA < vB;
        bm.setValue(QBValue::One, "a", 0);
        bm.setValue(QBValue::One, "a", 1);
        bm.setValue(QBValue::Zero, "a", 2);
        
        bm.setValue(QBValue::Zero, "b", 0);
        bm.setValue(QBValue::Zero, "b", 1);
        bm.setValue(QBValue::One, "b", 2);
        QBValue val = lt.evaluate();
        EXPECT_EQ(val, QBValue::One);

        bm.setValue(QBValue::One, "a", 2);
        val = lt.evaluate();
        EXPECT_EQ(val, QBValue::Zero);
    }
}

TEST(QBVector, eq)
{
    QBManager bm;
    QBVector vA = bm.getBitVector("a", 2);
    QBVector vB = bm.getBitVector("b", 2);


    QBFunc eq = vA == vB;
    bm.setValue(QBValue::Zero, "a", 0);
    bm.setValue(QBValue::Zero, "a", 1);
    bm.setValue(QBValue::Zero, "b", 0);
    bm.setValue(QBValue::Zero, "b", 1);

    QBValue val = eq.evaluate();
    EXPECT_EQ(val, QBValue::One);

    bm.setValue(QBValue::One, "a", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, QBValue::Zero);

    bm.setValue(QBValue::One, "b", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, QBValue::One);
}


TEST(QBVector, lte) {
    QBManager bm;
    QBVector vA = bm.getBitVector("a", 2);
    QBVector vB = bm.getBitVector("b", 2);


    QBFunc lte = vA <= vB;
    bm.setValue(QBValue::One, "a", 0);
    bm.setValue(QBValue::Zero, "a", 1);
    bm.setValue(QBValue::Zero, "b", 0);
    bm.setValue(QBValue::One, "b", 1);

    QBValue val = lte.evaluate();
    EXPECT_EQ(val, QBValue::One);

    bm.setValue(QBValue::One, "a", 1);
    val = lte.evaluate();
    EXPECT_EQ(val, QBValue::Zero);

    bm.setValue(QBValue::Zero, "a", 0);
    val = lte.evaluate();
    EXPECT_EQ(val, QBValue::One);
}

TEST(QBVector, ne) {
    QBManager bm;
    QBVector vA = bm.getBitVector("a", 2);
    QBVector vB = bm.getBitVector("b", 2);


    QBFunc eq = vA != vB;
    bm.setValue(QBValue::Zero, "a", 0);
    bm.setValue(QBValue::Zero, "a", 1);
    bm.setValue(QBValue::Zero, "b", 0);
    bm.setValue(QBValue::Zero, "b", 1);

    QBValue val = eq.evaluate();
    EXPECT_EQ(val, QBValue::Zero);

    bm.setValue(QBValue::One, "a", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, QBValue::One);

    bm.setValue(QBValue::One, "b", 1);
    val = eq.evaluate();
    EXPECT_EQ(val, QBValue::Zero);
}

TEST(QBVector, gte) {
    QBManager bm;
    QBVector vA = bm.getBitVector("a", 2);
    QBVector vB = bm.getBitVector("b", 2);


    QBFunc gte = vA >= vB;
    bm.setValue(QBValue::One, "a", 0);
    bm.setValue(QBValue::Zero, "a", 1);
    bm.setValue(QBValue::Zero, "b", 0);
    bm.setValue(QBValue::One, "b", 1);

    QBValue val = gte.evaluate();
    EXPECT_EQ(val, QBValue::Zero);

    bm.setValue(QBValue::One, "a", 1);
    val = gte.evaluate();
    EXPECT_EQ(val, QBValue::One);

    bm.setValue(QBValue::Zero, "a", 0);
    val = gte.evaluate();
    EXPECT_EQ(val, QBValue::One);
}

TEST(QBVector, gt) {
    QBManager bm;
    QBVector vA = bm.getBitVector("a", 2);
    QBVector vB = bm.getBitVector("b", 2);


    QBFunc gt = vA > vB;
    bm.setValue(QBValue::One, "a", 0);
    bm.setValue(QBValue::Zero, "a", 1);
    bm.setValue(QBValue::Zero, "b", 0);
    bm.setValue(QBValue::One, "b", 1);
    QBValue val = gt.evaluate();
    EXPECT_EQ(val, QBValue::Zero);

    bm.setValue(QBValue::One, "a", 1);
    val = gt.evaluate();
    EXPECT_EQ(val, QBValue::One);

    bm.setValue(QBValue::Zero, "a", 0);
    val = gt.evaluate();
    EXPECT_EQ(val, QBValue::Zero);
}
