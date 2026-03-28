#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

// Replicate the structures as described in the known dependencies
struct TrueTypeTable {
    unsigned int tag = 0;
    unsigned int checksum = 0;
    int offset = 0;
    int origOffset = 0;
    int len = 0;
};

struct cmpTrueTypeTableTagFunctor {
    bool operator()(const TrueTypeTable &tab1, const TrueTypeTable &tab2) {
        return tab1.tag < tab2.tag;
    }
};

class CmpTrueTypeTableTagFunctorTest_48 : public ::testing::Test {
protected:
    cmpTrueTypeTableTagFunctor cmp;
};

TEST_F(CmpTrueTypeTableTagFunctorTest_48, LessThanReturnsTrue_48) {
    TrueTypeTable tab1;
    tab1.tag = 1;
    TrueTypeTable tab2;
    tab2.tag = 2;
    EXPECT_TRUE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, GreaterThanReturnsFalse_48) {
    TrueTypeTable tab1;
    tab1.tag = 5;
    TrueTypeTable tab2;
    tab2.tag = 3;
    EXPECT_FALSE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, EqualTagsReturnsFalse_48) {
    TrueTypeTable tab1;
    tab1.tag = 10;
    TrueTypeTable tab2;
    tab2.tag = 10;
    EXPECT_FALSE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, BothZeroTagsReturnsFalse_48) {
    TrueTypeTable tab1;
    tab1.tag = 0;
    TrueTypeTable tab2;
    tab2.tag = 0;
    EXPECT_FALSE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, ZeroLessThanNonZero_48) {
    TrueTypeTable tab1;
    tab1.tag = 0;
    TrueTypeTable tab2;
    tab2.tag = 1;
    EXPECT_TRUE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, NonZeroNotLessThanZero_48) {
    TrueTypeTable tab1;
    tab1.tag = 1;
    TrueTypeTable tab2;
    tab2.tag = 0;
    EXPECT_FALSE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, MaxUintBoundary_48) {
    TrueTypeTable tab1;
    tab1.tag = 0xFFFFFFFE;
    TrueTypeTable tab2;
    tab2.tag = 0xFFFFFFFF;
    EXPECT_TRUE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, MaxUintNotLessThanItself_48) {
    TrueTypeTable tab1;
    tab1.tag = 0xFFFFFFFF;
    TrueTypeTable tab2;
    tab2.tag = 0xFFFFFFFF;
    EXPECT_FALSE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, MaxUintNotLessThanSmaller_48) {
    TrueTypeTable tab1;
    tab1.tag = 0xFFFFFFFF;
    TrueTypeTable tab2;
    tab2.tag = 0xFFFFFFFE;
    EXPECT_FALSE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, IgnoresOtherFields_48) {
    TrueTypeTable tab1;
    tab1.tag = 1;
    tab1.checksum = 999;
    tab1.offset = 100;
    tab1.origOffset = 200;
    tab1.len = 300;

    TrueTypeTable tab2;
    tab2.tag = 2;
    tab2.checksum = 0;
    tab2.offset = 0;
    tab2.origOffset = 0;
    tab2.len = 0;

    EXPECT_TRUE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, IgnoresOtherFieldsReverse_48) {
    TrueTypeTable tab1;
    tab1.tag = 2;
    tab1.checksum = 0;
    tab1.offset = 0;
    tab1.origOffset = 0;
    tab1.len = 0;

    TrueTypeTable tab2;
    tab2.tag = 1;
    tab2.checksum = 999;
    tab2.offset = 100;
    tab2.origOffset = 200;
    tab2.len = 300;

    EXPECT_FALSE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, UsableWithStdSort_48) {
    std::vector<TrueTypeTable> tables(5);
    tables[0].tag = 50;
    tables[1].tag = 10;
    tables[2].tag = 40;
    tables[3].tag = 20;
    tables[4].tag = 30;

    std::sort(tables.begin(), tables.end(), cmp);

    EXPECT_EQ(tables[0].tag, 10u);
    EXPECT_EQ(tables[1].tag, 20u);
    EXPECT_EQ(tables[2].tag, 30u);
    EXPECT_EQ(tables[3].tag, 40u);
    EXPECT_EQ(tables[4].tag, 50u);
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, UsableWithStdSortAlreadySorted_48) {
    std::vector<TrueTypeTable> tables(3);
    tables[0].tag = 1;
    tables[1].tag = 2;
    tables[2].tag = 3;

    std::sort(tables.begin(), tables.end(), cmp);

    EXPECT_EQ(tables[0].tag, 1u);
    EXPECT_EQ(tables[1].tag, 2u);
    EXPECT_EQ(tables[2].tag, 3u);
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, UsableWithStdSortReverseSorted_48) {
    std::vector<TrueTypeTable> tables(3);
    tables[0].tag = 3;
    tables[1].tag = 2;
    tables[2].tag = 1;

    std::sort(tables.begin(), tables.end(), cmp);

    EXPECT_EQ(tables[0].tag, 1u);
    EXPECT_EQ(tables[1].tag, 2u);
    EXPECT_EQ(tables[2].tag, 3u);
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, StrictWeakOrderingAntiSymmetry_48) {
    TrueTypeTable tab1;
    tab1.tag = 3;
    TrueTypeTable tab2;
    tab2.tag = 7;
    // If cmp(a, b) is true, then cmp(b, a) must be false
    EXPECT_TRUE(cmp(tab1, tab2));
    EXPECT_FALSE(cmp(tab2, tab1));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, StrictWeakOrderingIrreflexivity_48) {
    TrueTypeTable tab;
    tab.tag = 42;
    // cmp(a, a) must be false
    EXPECT_FALSE(cmp(tab, tab));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, ConsecutiveValues_48) {
    TrueTypeTable tab1;
    tab1.tag = 100;
    TrueTypeTable tab2;
    tab2.tag = 101;
    EXPECT_TRUE(cmp(tab1, tab2));
    EXPECT_FALSE(cmp(tab2, tab1));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, LargeTagValues_48) {
    TrueTypeTable tab1;
    tab1.tag = 0x80000000; // 2^31
    TrueTypeTable tab2;
    tab2.tag = 0x80000001;
    EXPECT_TRUE(cmp(tab1, tab2));
}

TEST_F(CmpTrueTypeTableTagFunctorTest_48, TypicalFontTableTags_48) {
    // Typical TrueType table tags like 'cmap', 'glyf', 'head', 'loca'
    TrueTypeTable tab_cmap;
    tab_cmap.tag = 0x636D6170; // 'cmap'
    TrueTypeTable tab_glyf;
    tab_glyf.tag = 0x676C7966; // 'glyf'
    TrueTypeTable tab_head;
    tab_head.tag = 0x68656164; // 'head'

    EXPECT_TRUE(cmp(tab_cmap, tab_glyf));
    EXPECT_TRUE(cmp(tab_glyf, tab_head));
    EXPECT_TRUE(cmp(tab_cmap, tab_head));
    EXPECT_FALSE(cmp(tab_head, tab_cmap));
}
