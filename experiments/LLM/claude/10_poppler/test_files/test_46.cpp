#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Reproduce the TrueTypeLoca struct and the functor as described
struct TrueTypeLoca
{
    int idx = 0;
    int origOffset = 0;
    int newOffset = 0;
};

struct cmpTrueTypeLocaOffsetFunctor
{
public:
    bool operator()(const TrueTypeLoca loca1, const TrueTypeLoca loca2)
    {
        if (loca1.origOffset == loca2.origOffset) {
            return loca1.idx < loca2.idx;
        }
        return loca1.origOffset < loca2.origOffset;
    }
};

class CmpTrueTypeLocaOffsetFunctorTest_46 : public ::testing::Test
{
protected:
    cmpTrueTypeLocaOffsetFunctor cmp;
};

// Test: loca1 has smaller origOffset than loca2 → returns true
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SmallerOrigOffsetReturnsTrue_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 10;
    loca1.idx = 5;

    TrueTypeLoca loca2;
    loca2.origOffset = 20;
    loca2.idx = 3;

    EXPECT_TRUE(cmp(loca1, loca2));
}

// Test: loca1 has larger origOffset than loca2 → returns false
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, LargerOrigOffsetReturnsFalse_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 30;
    loca1.idx = 1;

    TrueTypeLoca loca2;
    loca2.origOffset = 20;
    loca2.idx = 10;

    EXPECT_FALSE(cmp(loca1, loca2));
}

// Test: Same origOffset, loca1 has smaller idx → returns true
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SameOrigOffsetSmallerIdxReturnsTrue_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 50;
    loca1.idx = 2;

    TrueTypeLoca loca2;
    loca2.origOffset = 50;
    loca2.idx = 7;

    EXPECT_TRUE(cmp(loca1, loca2));
}

// Test: Same origOffset, loca1 has larger idx → returns false
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SameOrigOffsetLargerIdxReturnsFalse_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 50;
    loca1.idx = 10;

    TrueTypeLoca loca2;
    loca2.origOffset = 50;
    loca2.idx = 3;

    EXPECT_FALSE(cmp(loca1, loca2));
}

// Test: Same origOffset and same idx → returns false (not strictly less)
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SameOrigOffsetSameIdxReturnsFalse_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 50;
    loca1.idx = 5;

    TrueTypeLoca loca2;
    loca2.origOffset = 50;
    loca2.idx = 5;

    EXPECT_FALSE(cmp(loca1, loca2));
}

// Test: Both origOffset and idx are zero → returns false (equal elements)
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, BothZeroReturnsFalse_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 0;
    loca1.idx = 0;

    TrueTypeLoca loca2;
    loca2.origOffset = 0;
    loca2.idx = 0;

    EXPECT_FALSE(cmp(loca1, loca2));
}

// Test: Negative origOffset values
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, NegativeOrigOffsetComparison_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = -10;
    loca1.idx = 1;

    TrueTypeLoca loca2;
    loca2.origOffset = 5;
    loca2.idx = 1;

    EXPECT_TRUE(cmp(loca1, loca2));
    EXPECT_FALSE(cmp(loca2, loca1));
}

// Test: Negative idx values with same origOffset
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, NegativeIdxWithSameOrigOffset_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 100;
    loca1.idx = -5;

    TrueTypeLoca loca2;
    loca2.origOffset = 100;
    loca2.idx = 3;

    EXPECT_TRUE(cmp(loca1, loca2));
    EXPECT_FALSE(cmp(loca2, loca1));
}

// Test: Antisymmetry property — if cmp(a, b) is true, cmp(b, a) should be false
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, AntisymmetryProperty_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 10;
    loca1.idx = 3;

    TrueTypeLoca loca2;
    loca2.origOffset = 20;
    loca2.idx = 1;

    EXPECT_TRUE(cmp(loca1, loca2));
    EXPECT_FALSE(cmp(loca2, loca1));
}

// Test: Irreflexivity — cmp(a, a) should be false
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, IrreflexivityProperty_46)
{
    TrueTypeLoca loca;
    loca.origOffset = 42;
    loca.idx = 7;

    EXPECT_FALSE(cmp(loca, loca));
}

// Test: Transitivity — if cmp(a,b) and cmp(b,c), then cmp(a,c)
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, TransitivityProperty_46)
{
    TrueTypeLoca a, b, c;
    a.origOffset = 10;
    a.idx = 1;
    b.origOffset = 20;
    b.idx = 2;
    c.origOffset = 30;
    c.idx = 3;

    EXPECT_TRUE(cmp(a, b));
    EXPECT_TRUE(cmp(b, c));
    EXPECT_TRUE(cmp(a, c));
}

// Test: Using the functor with std::sort on a vector
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, SortWithFunctor_46)
{
    std::vector<TrueTypeLoca> vec(4);
    vec[0].origOffset = 30;
    vec[0].idx = 2;
    vec[1].origOffset = 10;
    vec[1].idx = 0;
    vec[2].origOffset = 30;
    vec[2].idx = 1;
    vec[3].origOffset = 20;
    vec[3].idx = 3;

    std::sort(vec.begin(), vec.end(), cmpTrueTypeLocaOffsetFunctor());

    // Expected order by origOffset: 10, 20, 30, 30
    // For the two with origOffset=30, idx 1 < idx 2
    EXPECT_EQ(vec[0].origOffset, 10);
    EXPECT_EQ(vec[0].idx, 0);
    EXPECT_EQ(vec[1].origOffset, 20);
    EXPECT_EQ(vec[1].idx, 3);
    EXPECT_EQ(vec[2].origOffset, 30);
    EXPECT_EQ(vec[2].idx, 1);
    EXPECT_EQ(vec[3].origOffset, 30);
    EXPECT_EQ(vec[3].idx, 2);
}

// Test: Large values for origOffset
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, LargeOrigOffsetValues_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 2147483646; // near INT_MAX
    loca1.idx = 0;

    TrueTypeLoca loca2;
    loca2.origOffset = 2147483647; // INT_MAX
    loca2.idx = 0;

    EXPECT_TRUE(cmp(loca1, loca2));
    EXPECT_FALSE(cmp(loca2, loca1));
}

// Test: origOffset differs, idx is irrelevant
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, OrigOffsetDiffersIdxIrrelevant_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 5;
    loca1.idx = 100;

    TrueTypeLoca loca2;
    loca2.origOffset = 10;
    loca2.idx = 1;

    // Even though loca1.idx > loca2.idx, origOffset is the primary key
    EXPECT_TRUE(cmp(loca1, loca2));
}

// Test: newOffset field does not affect comparison
TEST_F(CmpTrueTypeLocaOffsetFunctorTest_46, NewOffsetDoesNotAffectComparison_46)
{
    TrueTypeLoca loca1;
    loca1.origOffset = 50;
    loca1.idx = 3;
    loca1.newOffset = 999;

    TrueTypeLoca loca2;
    loca2.origOffset = 50;
    loca2.idx = 3;
    loca2.newOffset = 1;

    // Should be equal (neither less than the other) regardless of newOffset
    EXPECT_FALSE(cmp(loca1, loca2));
    EXPECT_FALSE(cmp(loca2, loca1));
}
