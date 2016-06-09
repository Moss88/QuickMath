#include "gtest/gtest.h"
#include "QFunc/QFVar.h"
#include "QBool/QBManager.h"
#include "QBool/QBDimacsGen.h"
#include "QBool/QBDimacsFunc.h"
#include "QBool/QBAlgorithms.h"
#include <sstream>
using namespace std;
using namespace QuickMath;

TEST(QBDimacsFunc, substitute) {
    QBManager bm;
    QBFunc a0 = bm.getBit("a", 0);
    QBFunc a1 = bm.getBit("a", 1);
    QBFunc b0 = bm.getBit("b", 0);
    QBFunc b1 = bm.getBit("b", 1);
    
    QBFunc f = (a0 | b0) & (a1 | b1);
    std::vector<std::tuple<std::string, int>> inputMap;
    inputMap.push_back(std::make_tuple("a",2));
    inputMap.push_back(std::make_tuple("b",2));
    
    QBDimacsFunc dFunc(f, inputMap);
    EXPECT_EQ(dFunc.numClauses(), 2);
    EXPECT_EQ(dFunc.numVars(), 4);
    std::stringstream ss;
    dFunc.cnfsToStream(ss, std::vector<int>() = {1, 5}, 6);
    std::vector<int> correctNums = {1, 5, 0, 
                                    2, 6, 0};
    int i = 0;
    while(ss.good() && i < correctNums.size())
    {
        int num;
        ss >> num;
        EXPECT_EQ(num, correctNums[i]);
        ++i;
    }
}


TEST(QBDimacsFunc, subTseytin) {
    QBManager bm;
    QBFunc a0 = bm.getBit("a", 0);
    QBFunc a1 = bm.getBit("a", 1);
    QBFunc b0 = bm.getBit("b", 0);
    QBFunc b1 = bm.getBit("b", 1);
    
    QBFunc f = (a0 & b0) | (a1 & b1);
    QBFunc ts = QBAlgo::generateCNF(f, bm);
    
    std::vector<std::tuple<std::string, int>> inputMap;
    inputMap.push_back(std::make_tuple("a",2));
    inputMap.push_back(std::make_tuple("b",2));
    
    QBDimacsFunc dFunc(ts, inputMap);
    EXPECT_EQ(dFunc.numVars(), 4);
    EXPECT_EQ(dFunc.numTmpVars(), 3);

    std::stringstream ss;
    int totalVars = dFunc.numVars() + dFunc.numTmpVars();
    dFunc.cnfsToStream(ss, std::vector<int>() = {1, totalVars + 1}, totalVars + 3);
}

TEST(QBDimacsGen, cnf) {
    QBManager bm;
    QBFunc a0 = bm.getBit("a", 0);
    QBFunc a1 = bm.getBit("a", 1);
    QBFunc b0 = bm.getBit("b", 0);
    QBFunc b1 = bm.getBit("b", 1);
    
    QBFunc f = (a0 | b0) & (a1 | b1);
    std::vector<std::tuple<std::string, int>> inputMap;
    inputMap.push_back(std::make_tuple("a",2));
    inputMap.push_back(std::make_tuple("b",2));
    QBDimacsFunc dFunc(f, inputMap);
   
    QBDimacsGen dGen;
    QFVar x("x"), y("y"), z("z");
    std::vector<std::tuple<const QFType*, int>> inVec = {std::make_tuple(&x, 2),
                                                        std::make_tuple(&y, 2)};
    dGen.addFunction(&dFunc, inVec);
    inVec = {std::make_tuple(&y, 2), std::make_tuple(&z, 2)};
    dGen.addFunction(&dFunc, inVec);
}

TEST(QBDimacsGen, cnfTseytin) {
    QBManager bm;
    QBFunc a0 = bm.getBit("a", 0);
    QBFunc a1 = bm.getBit("a", 1);
    QBFunc b0 = bm.getBit("b", 0);
    QBFunc b1 = bm.getBit("b", 1);
    
    QBFunc f = (a0 & b0) | (a1 & b1);
    QBFunc ts = QBAlgo::generateCNF(f, bm);
 
    std::vector<std::tuple<std::string, int>> inputMap;
    inputMap.push_back(std::make_tuple("a",2));
    inputMap.push_back(std::make_tuple("b",2));
    QBDimacsFunc dFunc(ts, inputMap);
   
    QBDimacsGen dGen;
    QFVar x("x"), y("y"), z("z");
    std::vector<std::tuple<const QFType*, int>> inVec = {std::make_tuple(&x, 2),
                                                       std::make_tuple(&y, 2)};
    dGen.addFunction(&dFunc, inVec);
    inVec = {std::make_tuple(&y, 2), std::make_tuple(&z, 2)};
    dGen.addFunction(&dFunc, inVec);
}


TEST(QBDimacsGen, sat) {
    QBManager bm;
    auto a = bm.getBitVector("a", 1);
    auto b = bm.getBitVector("b", 1);
       
    QBFunc f = a < b;
    QBFunc ts = QBAlgo::generateCNF(f, bm);
 
    std::vector<std::tuple<std::string, int>> inputMap;
    inputMap.push_back(std::make_tuple("a",1));
    inputMap.push_back(std::make_tuple("b",1));
    QBDimacsFunc dFunc(ts, inputMap);
   
    QBDimacsGen dGen;
    QFVar x("x"), y("y");
    std::vector<std::tuple<const QFType*, int>> inVec = {std::make_tuple(&x, 1),
                                                        std::make_tuple(&y, 1)};
    dGen.addFunction(&dFunc, inVec);
    EXPECT_EQ(dGen.isSat(), true);
    auto resultVec = dGen.getSat();
    EXPECT_EQ(resultVec.size(), 2);
    int lower = -1;
    int upper = -1;
    if(std::get<0>(resultVec.front())->toString() == x.toString())
        EXPECT_LT(std::get<1>(resultVec.front()), std::get<1>(resultVec.back()));
    else
        EXPECT_LT(std::get<1>(resultVec.back()), std::get<1>(resultVec.front()));
}

TEST(QBDimacsGen, vecTest) {
    QBManager bm;
    auto a = bm.getBitVector("a", 3);
    auto b = bm.getBitVector("b", 3);
    
    QBFunc f = a < b;
    QBFunc ts = QBAlgo::generateCNF(f, bm);
 
    std::vector<std::tuple<std::string, int>> inputMap;
    inputMap.push_back(std::make_tuple("a", 3));
    inputMap.push_back(std::make_tuple("b", 3));
    QBDimacsFunc dFunc(ts, inputMap);
   
    QBDimacsGen dGen;
    QFVar w("w"), x("x"), y("y");
    // x < w < z < y
    std::vector<std::tuple<const QFType*, int>> inVec;
   
    inVec = {std::make_tuple(&x, 3), std::make_tuple(&w, 3)};
    dGen.addFunction(&dFunc, inVec);
    inVec = {std::make_tuple(&w, 3), std::make_tuple(&y, 3)};
    dGen.addFunction(&dFunc, inVec);

    std::vector<const QFType*> order = {&x, &w, &y};
    std::map<const QFType*, int> resultOrder;
    auto resultVec = dGen.getSat(false);
    ASSERT_GT(resultVec.size(), 0); 
    for(auto &result:resultVec) 
        resultOrder[std::get<0>(result)] = std::get<1>(result);
    
    for(auto iter = order.begin() + 1; iter != order.end(); ++iter)
    {
        auto left = resultOrder.find(*(iter - 1));
        ASSERT_NE(left, resultOrder.end());

        auto right = resultOrder.find(*iter);
        ASSERT_NE(right, resultOrder.end());

        EXPECT_LT(left->second, right->second);
    }
}
