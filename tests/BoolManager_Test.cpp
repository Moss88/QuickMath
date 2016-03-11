#include "gtest/gtest.h"
#include "QBool/QBManager.h"
#include "QBool/QBBit.h"
#include "QBool/QBAlgorithms.h"
#include<iostream>
using namespace std;
using namespace QuickMath;
TEST(QBManager, GetVar) {
    QBManager bm;
    QBFunc a = bm.getBit("a");
    QBFunc b = bm.getBit("b");
    QBFunc aCopy = bm.getBit("a");

    QBBit *aPtr = dynamic_cast<QBBit*>(a.get());
    QBBit *bPtr = dynamic_cast<QBBit*>(b.get());
    QBBit *aCopyPtr = dynamic_cast<QBBit*>(aCopy.get());
    ASSERT_TRUE(aPtr);
    ASSERT_TRUE(bPtr);
    ASSERT_TRUE(aCopyPtr);

    EXPECT_EQ(aPtr->getName(), aCopyPtr->getName());
    EXPECT_EQ(aPtr->getIndex(), aCopyPtr->getIndex());
    EXPECT_NE(bPtr->getName(), aPtr->getName());
    bm.setValue(QBValue::One, "a");
    EXPECT_EQ(aPtr->value(), QBValue::One);
    EXPECT_EQ(aCopyPtr->value(), QBValue::One);
}

TEST(QBManager, GetVector)
{
    QBManager bm;
    QBVector bv = bm.getBitVector("a", 2);
    ASSERT_EQ(bv.size(), 2);
    EXPECT_EQ(bv.begin()->toString(), "a[0]");
    EXPECT_EQ((bv.begin() + 1)->toString(), "a[1]");
}
