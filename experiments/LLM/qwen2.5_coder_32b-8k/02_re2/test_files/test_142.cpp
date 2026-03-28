#include <gtest/gtest.h>

#include "regexp.h"



namespace re2 {

    struct MockRuneRangeLess : public RuneRangeLess {

        MOCK_CONST_METHOD2(operator(), bool(const RuneRange& a, const RuneRange& b));

    };

}



class RuneRangeSetTest_142 : public ::testing::Test {

protected:

    using namespace re2;



    RuneRangeSet runes;

};



TEST_F(RuneRangeSetTest_142, InsertSingleElement_142) {

    re2::RuneRange range(5, 10);

    auto it = runes.insert(range);

    EXPECT_EQ(it.first->lo, 5);

    EXPECT_EQ(it.first->hi, 10);

}



TEST_F(RuneRangeSetTest_142, InsertMultipleElements_142) {

    re2::RuneRange range1(5, 10);

    re2::RuneRange range2(15, 20);

    runes.insert(range1);

    auto it = runes.insert(range2);

    EXPECT_EQ(it.first->lo, 15);

    EXPECT_EQ(it.first->hi, 20);

}



TEST_F(RuneRangeSetTest_142, InsertDuplicateElement_142) {

    re2::RuneRange range(5, 10);

    auto it1 = runes.insert(range);

    auto it2 = runes.insert(range);

    EXPECT_EQ(it1.first, it2.first);

    EXPECT_TRUE(it2.second == false); // second is false for duplicate insertion

}



TEST_F(RuneRangeSetTest_142, InsertBoundaryConditions_142) {

    re2::RuneRange rangeMin(0, 1);

    re2::RuneRange rangeMax(std::numeric_limits<re2::Rune>::max() - 1, std::numeric_limits<re2::Rune>::max());

    auto it1 = runes.insert(rangeMin);

    auto it2 = runes.insert(rangeMax);

    EXPECT_EQ(it1.first->lo, 0);

    EXPECT_EQ(it1.first->hi, 1);

    EXPECT_EQ(it2.first->lo, std::numeric_limits<re2::Rune>::max() - 1);

    EXPECT_EQ(it2.first->hi, std::numeric_limits<re2::Rune>::max());

}



TEST_F(RuneRangeSetTest_142, InsertOverlap_142) {

    re2::RuneRange range1(5, 10);

    re2::RuneRange range2(8, 12);

    runes.insert(range1);

    auto it = runes.insert(range2);

    EXPECT_EQ(it.second, false); // Overlapping ranges should not be inserted

}



TEST_F(RuneRangeSetTest_142, FindExistingElement_142) {

    re2::RuneRange range(5, 10);

    runes.insert(range);

    auto it = runes.find(re2::RuneRange(5, 10));

    EXPECT_EQ(it->lo, 5);

    EXPECT_EQ(it->hi, 10);

}



TEST_F(RuneRangeSetTest_142, FindNonExistingElement_142) {

    re2::RuneRange range(5, 10);

    auto it = runes.find(range);

    EXPECT_TRUE(it == runes.end());

}



TEST_F(RuneRangeSetTest_142, EraseElement_142) {

    re2::RuneRange range(5, 10);

    runes.insert(range);

    size_t count = runes.erase(re2::RuneRange(5, 10));

    EXPECT_EQ(count, 1);

    EXPECT_TRUE(runes.find(range) == runes.end());

}



TEST_F(RuneRangeSetTest_142, EraseNonExistingElement_142) {

    re2::RuneRange range(5, 10);

    size_t count = runes.erase(range);

    EXPECT_EQ(count, 0);

}
