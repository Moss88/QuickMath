#include "gtest/gtest.h"
#include "QBool/QBManager.h"
#include "QBool/QBBit.h"
#include "QBool/QBAlgorithms.h"
#include <iostream>
#include <future>
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

TEST(QBAlgo, CNFEff) {
    {
        QBManager bm;
        QBFunc a = bm.getBit("a");
        QBFunc b = bm.getBit("b");
        QBFunc c = bm.getBit("c");
        QBFunc d = bm.getBit("d");

        // 4 to 5 tseitin variables
        QBFunc eq = !(a & b) | (!c & !d);
        auto cnf = QBAlgo::generateCNF(eq, bm);
        EXPECT_EQ(bm.numberTempVars(), 4); 
    }
    {
        QBManager bm;
        QBFunc a = bm.getBit("a");
        QBFunc b = bm.getBit("b");
        QBFunc c = bm.getBit("c");
        QBFunc d = bm.getBit("d");

        QBFunc eq = !(a & b) | !(!c & !d);
        auto cnf = QBAlgo::generateCNF(eq, bm);
        EXPECT_EQ(bm.numberTempVars(), 5);
    }

    {
        QBManager bm;
        auto a = bm.getBitVector("a", 4);
        auto b = bm.getBitVector("b", 4);
        auto eq = a < b;
        auto cnf = QBAlgo::generateCNF(eq, bm);
        EXPECT_EQ(bm.numberTempVars(), 18);
    }

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

TEST(QBAlgo, picoSat)
{
    std::vector<int> clauses;
    clauses = {1, 2, 0, 1, -2, 0};
    auto result = QBAlgo::runPicoSat(clauses, 2);
    EXPECT_TRUE(!result.empty());

    clauses.clear();
    clauses = {1, 2, 0, -1, 0, -2, 0};
    result = QBAlgo::runPicoSat(clauses, 2);
    EXPECT_TRUE(result.empty());

    clauses.clear();
    clauses = {1, 2, 3, 0, -2, 0, -3, 0};
    result = QBAlgo::runPicoSat(clauses, 3);
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], -2);
    EXPECT_EQ(result[2], -3);
} 

TEST(QBAlgo, parallelPico) {
    std::vector<int> clauses;
    clauses = {1, 2, 3, 0, -2, 0, -3, 0};
    
    auto satFunc = [&clauses]() {
        return !QBAlgo::runPicoSat(clauses, 3).empty();
    };

    vector<std::future<bool>> futures;
    for(int i = 0; i < 100000; i++)
        futures.push_back(std::async(satFunc));

    for(auto &future:futures)
        ASSERT_TRUE(future.get());
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

