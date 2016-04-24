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
    std::vector<int> correctNums = {0, 1, 5, 
                                    0, 2, 6};
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
    std::vector<std::tuple<const QFVar*, int>> inVec = {std::make_tuple(&x, 2),
                                                       std::make_tuple(&y, 2)};
    dGen.addFunction(&dFunc, inVec);
    inVec = {std::make_tuple(&y, 2), std::make_tuple(&z, 2)};
    dGen.addFunction(&dFunc, inVec);
    //std::cout << dGen.getDimacs() << std::endl; 
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
    std::vector<std::tuple<const QFVar*, int>> inVec = {std::make_tuple(&x, 2),
                                                       std::make_tuple(&y, 2)};
    dGen.addFunction(&dFunc, inVec);
    inVec = {std::make_tuple(&y, 2), std::make_tuple(&z, 2)};
    dGen.addFunction(&dFunc, inVec);
    //std::cout << dGen.getDimacs() << std::endl; 
}
