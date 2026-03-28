#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Reproduce the structures as described in the known dependencies
struct TrueTypeLoca {
    int idx = 0;
    int newOffset = 0;
};

struct cmpTrueTypeLocaIdxFunctor {
    bool operator()(const TrueTypeLoca loca1, const TrueTypeLoca loca2) {
        return loca1.idx < loca2.idx;
    }
};

// Test fixture
class CmpTrueTypeLocaIdxFunctorTest_47 : public ::testing::Test {
protected:
    cmpTrueTypeLocaIdxFunctor comparator;
};

// Normal operation: loca1.idx < loca2.idx should return true
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, SmallerIdxReturnsTrue_47) {
    TrueTypeLoca loca1;
    loca1.idx = 1;
    TrueTypeLoca loca2;
    loca2.idx = 5;
    EXPECT_TRUE(comparator(loca1, loca2));
}

// Normal operation: loca1.idx > loca2.idx should return false
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, LargerIdxReturnsFalse_47) {
    TrueTypeLoca loca1;
    loca1.idx = 10;
    TrueTypeLoca loca2;
    loca2.idx = 3;
    EXPECT_FALSE(comparator(loca1, loca2));
}

// Boundary: equal idx values should return false (strict less than)
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, EqualIdxReturnsFalse_47) {
    TrueTypeLoca loca1;
    loca1.idx = 7;
    TrueTypeLoca loca2;
    loca2.idx = 7;
    EXPECT_FALSE(comparator(loca1, loca2));
}

// Boundary: both idx values are zero (default)
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, BothDefaultIdxReturnsFalse_47) {
    TrueTypeLoca loca1;
    TrueTypeLoca loca2;
    EXPECT_FALSE(comparator(loca1, loca2));
}

// Boundary: negative idx values
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, NegativeIdxComparison_47) {
    TrueTypeLoca loca1;
    loca1.idx = -5;
    TrueTypeLoca loca2;
    loca2.idx = -1;
    EXPECT_TRUE(comparator(loca1, loca2));
}

// Boundary: negative vs positive idx
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, NegativeVsPositiveIdx_47) {
    TrueTypeLoca loca1;
    loca1.idx = -3;
    TrueTypeLoca loca2;
    loca2.idx = 3;
    EXPECT_TRUE(comparator(loca1, loca2));
}

// Boundary: positive vs negative idx
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, PositiveVsNegativeIdx_47) {
    TrueTypeLoca loca1;
    loca1.idx = 3;
    TrueTypeLoca loca2;
    loca2.idx = -3;
    EXPECT_FALSE(comparator(loca1, loca2));
}

// Verify that newOffset does not affect comparison
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, NewOffsetDoesNotAffectComparison_47) {
    TrueTypeLoca loca1;
    loca1.idx = 2;
    loca1.newOffset = 1000;
    TrueTypeLoca loca2;
    loca2.idx = 5;
    loca2.newOffset = 1;
    EXPECT_TRUE(comparator(loca1, loca2));

    // Reverse the newOffset values, result should be same based on idx
    loca1.newOffset = 1;
    loca2.newOffset = 1000;
    EXPECT_TRUE(comparator(loca1, loca2));
}

// Test that the functor can be used with std::sort
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, UsableWithStdSort_47) {
    std::vector<TrueTypeLoca> locas(5);
    locas[0].idx = 5;
    locas[1].idx = 3;
    locas[2].idx = 8;
    locas[3].idx = 1;
    locas[4].idx = 4;

    std::sort(locas.begin(), locas.end(), cmpTrueTypeLocaIdxFunctor());

    EXPECT_EQ(locas[0].idx, 1);
    EXPECT_EQ(locas[1].idx, 3);
    EXPECT_EQ(locas[2].idx, 4);
    EXPECT_EQ(locas[3].idx, 5);
    EXPECT_EQ(locas[4].idx, 8);
}

// Test sorting with duplicate idx values
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, SortWithDuplicateIdx_47) {
    std::vector<TrueTypeLoca> locas(4);
    locas[0].idx = 3;
    locas[1].idx = 1;
    locas[2].idx = 3;
    locas[3].idx = 2;

    std::sort(locas.begin(), locas.end(), cmpTrueTypeLocaIdxFunctor());

    EXPECT_EQ(locas[0].idx, 1);
    EXPECT_EQ(locas[1].idx, 2);
    EXPECT_EQ(locas[2].idx, 3);
    EXPECT_EQ(locas[3].idx, 3);
}

// Boundary: large idx values
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, LargeIdxValues_47) {
    TrueTypeLoca loca1;
    loca1.idx = 2147483646; // INT_MAX - 1
    TrueTypeLoca loca2;
    loca2.idx = 2147483647; // INT_MAX
    EXPECT_TRUE(comparator(loca1, loca2));
    EXPECT_FALSE(comparator(loca2, loca1));
}

// Test antisymmetry: if a < b then !(b < a)
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, AntisymmetryProperty_47) {
    TrueTypeLoca loca1;
    loca1.idx = 2;
    TrueTypeLoca loca2;
    loca2.idx = 8;
    EXPECT_TRUE(comparator(loca1, loca2));
    EXPECT_FALSE(comparator(loca2, loca1));
}

// Test irreflexivity: !(a < a)
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, IrreflexivityProperty_47) {
    TrueTypeLoca loca;
    loca.idx = 42;
    EXPECT_FALSE(comparator(loca, loca));
}

// Single element sort should work fine
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, SingleElementSort_47) {
    std::vector<TrueTypeLoca> locas(1);
    locas[0].idx = 42;
    std::sort(locas.begin(), locas.end(), cmpTrueTypeLocaIdxFunctor());
    EXPECT_EQ(locas[0].idx, 42);
}

// Empty vector sort should work fine
TEST_F(CmpTrueTypeLocaIdxFunctorTest_47, EmptyVectorSort_47) {
    std::vector<TrueTypeLoca> locas;
    std::sort(locas.begin(), locas.end(), cmpTrueTypeLocaIdxFunctor());
    EXPECT_TRUE(locas.empty());
}
