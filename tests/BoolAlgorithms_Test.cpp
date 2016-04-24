#include "gtest/gtest.h"
#include "QBool/QBManager.h"
#include "QBool/QBBit.h"
#include "QBool/QBAlgorithms.h"
#include<iostream>
using namespace std;
using namespace QuickMath;
TEST(QBAlgo, isCNF) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    QBFunc c = bm.getBit("c");
    QBFunc d = bm.getBit("c");

    QBFunc eq = (a | b);
    EXPECT_TRUE(QBAlgo::isCNF(eq)) << "Failed CNF: "
                                     << eq;
    eq = a | (c & b);
    EXPECT_FALSE(QBAlgo::isCNF(eq)) << "Failed CNF: "
                                      << eq;
    eq = (a | b) & (!a | c);
    EXPECT_TRUE(QBAlgo::isCNF(eq)) << "Failed CNF: "
                                     << eq;
    eq = (a | b) & (!a | c) & !d;
    EXPECT_TRUE(QBAlgo::isCNF(eq)) << "Failed CNF: "
                                     << eq;
    eq = (a | b) & !(a | c);
    EXPECT_FALSE(QBAlgo::isCNF(eq)) << "Failed CNF: "
                                      << eq;
}

TEST(QBAlgo, CNF) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    QBFunc c = bm.getBit("c");

    QBFunc eq = a & b & c;
    auto cnf = QBAlgo::generateCNF(eq, bm);
    ASSERT_TRUE(QBAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
/*
    bm.setValue(QBValue::One, "a");
    bm.setValue(QBValue::One, "b");
    bm.setValue(QBValue::One, "c");

    EXPECT_EQ(cnf.evaluate(), QBValue::One);
    bm.setValue(QBValue::Zero, "c");
    EXPECT_EQ(cnf.evaluate(), QBValue::Zero);
    EXPECT_EQ(cnf.evaluate(), QBValue::One);

    eq = a | b | c;
    cnf = QBAlgo::generateCNF(eq, bm);
    EXPECT_TRUE(QBAlgo::isCNF(cnf));
    bm.setValue(QBValue::Zero, "a");
    bm.setValue(QBValue::Zero, "b");
    bm.setValue(QBValue::Zero, "c");
    EXPECT_EQ(cnf.evaluate(), QBValue::One);
    bm.setValue(QBValue::One, "c");
    EXPECT_EQ(cnf.evaluate(), QBValue::Zero);
    EXPECT_EQ(cnf.evaluate(), QBValue::One);

    eq = (a | b) & !c;
    cnf = QBAlgo::generateCNF(eq, bm);
    EXPECT_TRUE(QBAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;

    eq = a & (b | c);
    cnf = QBAlgo::generateCNF(eq, bm);
    EXPECT_TRUE(QBAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
*/
}


TEST(QBAlgo, isSat) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    QBFunc c = bm.getBit("c");
    
    QBFunc eq = a & (b | c);
    auto cnf = QBAlgo::generateCNF(eq, bm);
    ASSERT_TRUE(QBAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
    EXPECT_TRUE(QBAlgo::isSat(cnf).size());

    eq = a & !a;
    cnf = QBAlgo::generateCNF(eq, bm);
    ASSERT_TRUE(QBAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
    EXPECT_FALSE(QBAlgo::isSat(cnf).size());

    eq = a | b | !a;
    cnf = QBAlgo::generateCNF(eq, bm);
    ASSERT_TRUE(QBAlgo::isCNF(cnf)) << "Failed CNF: "
                                      << cnf;
    EXPECT_TRUE(QBAlgo::isSat(cnf).size());
}

