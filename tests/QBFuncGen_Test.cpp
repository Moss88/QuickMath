#include "gtest/gtest.h"
#include "QBool/QBFunc.h"
#include "QBool/QBManager.h"
#include "QBool/QBFuncGen.h"

using namespace std;
using namespace QuickMath;

TEST(QBFuncGen, substitute) {
    QBManager bm;
    QBFunc a0 = bm.getBit("a", 0);
    QBFunc a1 = bm.getBit("a", 1);
    QBFunc b0 = bm.getBit("b", 0);
    QBFunc b1 = bm.getBit("b", 1);
    
    QBFunc f = (a0 & b0) | (a1 & b1);
    bm.setValue(QBValue::One, "a", 0);
    bm.setValue(QBValue::Zero, "a", 1);
    bm.setValue(QBValue::One, "b", 0);
    bm.setValue(QBValue::Zero, "b", 1);
   
    QBFuncGen fGen(f);
    std::map<std::string, std::string> varMap;
    varMap["a"] = "x";
    varMap["b"] = "y";
    QBFunc xy = fGen.generateFunc(varMap, bm);
    
    bm.setValue(QBValue::One, "x", 0);
    bm.setValue(QBValue::Zero, "x", 1);
    bm.setValue(QBValue::One, "y", 0);
    bm.setValue(QBValue::Zero, "y", 1);
    EXPECT_EQ(xy.evaluate(), QBValue::One);  
 
    bm.setValue(QBValue::Zero, "x", 0);
    EXPECT_EQ(xy.evaluate(), QBValue::Zero);  
}


