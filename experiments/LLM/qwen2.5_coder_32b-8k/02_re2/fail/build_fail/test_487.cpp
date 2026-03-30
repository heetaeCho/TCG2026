#include <gtest/gtest.h>

#include "regexp.h"



using namespace re2;



class AddFoldedRangeLatin1Test_487 : public ::testing::Test {

protected:

    CharClassBuilder* cc;



    void SetUp() override {

        cc = new CharClassBuilder();

    }



    void TearDown() override {

        delete cc;

    }

};



TEST_F(AddFoldedRangeLatin1Test_487, NormalOperationLowerCase_487) {

    AddFoldedRangeLatin1(cc, 'a', 'c');

    EXPECT_TRUE(cc->Contains('a'));

    EXPECT_TRUE(cc->Contains('b'));

    EXPECT_TRUE(cc->Contains('c'));

    EXPECT_TRUE(cc->Contains('A'));

    EXPECT_TRUE(cc->Contains('B'));

    EXPECT_TRUE(cc->Contains('C'));

}



TEST_F(AddFoldedRangeLatin1Test_487, NormalOperationUpperCase_487) {

    AddFoldedRangeLatin1(cc, 'A', 'C');

    EXPECT_TRUE(cc->Contains('a'));

    EXPECT_TRUE(cc->Contains('b'));

    EXPECT_TRUE(cc->Contains('c'));

    EXPECT_TRUE(cc->Contains('A'));

    EXPECT_TRUE(cc->Contains('B'));

    EXPECT_TRUE(cc->Contains('C'));

}



TEST_F(AddFoldedRangeLatin1Test_487, BoundaryConditionsSingleCharLowerCase_487) {

    AddFoldedRangeLatin1(cc, 'a', 'a');

    EXPECT_TRUE(cc->Contains('a'));

    EXPECT_TRUE(cc->Contains('A'));

}



TEST_F(AddFoldedRangeLatin1Test_487, BoundaryConditionsSingleCharUpperCase_487) {

    AddFoldedRangeLatin1(cc, 'A', 'A');

    EXPECT_TRUE(cc->Contains('a'));

    EXPECT_TRUE(cc->Contains('A'));

}



TEST_F(AddFoldedRangeLatin1Test_487, BoundaryConditionsEmptyRange_487) {

    AddFoldedRangeLatin1(cc, 'b', 'a'); // lo > hi, should not add any range

    EXPECT_FALSE(cc->Contains('a'));

    EXPECT_FALSE(cc->Contains('A'));

}



TEST_F(AddFoldedRangeLatin1Test_487, BoundaryConditionsOutsideLatin1_487) {

    AddFoldedRangeLatin1(cc, 0x100, 0x200); // Outside Latin1 range, should not add any range

    for (Rune r = 'a'; r <= 'z'; ++r) {

        EXPECT_FALSE(cc->Contains(r));

        EXPECT_FALSE(cc->Contains(r - 'a' + 'A'));

    }

    for (Rune r = 'A'; r <= 'Z'; ++r) {

        EXPECT_FALSE(cc->Contains(r));

        EXPECT_FALSE(cc->Contains(r - 'A' + 'a'));

    }

}



TEST_F(AddFoldedRangeLatin1Test_487, MixedCaseRange_487) {

    AddFoldedRangeLatin1(cc, 'b', 'D');

    EXPECT_TRUE(cc->Contains('b'));

    EXPECT_TRUE(cc->Contains('c'));

    EXPECT_TRUE(cc->Contains('d'));

    EXPECT_TRUE(cc->Contains('B'));

    EXPECT_TRUE(cc->Contains('C'));

    EXPECT_TRUE(cc->Contains('D'));

    EXPECT_TRUE(cc->Contains('a'));

    EXPECT_TRUE(cc->Contains('A'));

}



TEST_F(AddFoldedRangeLatin1Test_487, OverlappingRanges_487) {

    AddFoldedRangeLatin1(cc, 'a', 'c');

    AddFoldedRangeLatin1(cc, 'b', 'd');

    EXPECT_TRUE(cc->Contains('a'));

    EXPECT_TRUE(cc->Contains('b'));

    EXPECT_TRUE(cc->Contains('c'));

    EXPECT_TRUE(cc->Contains('d'));

    EXPECT_TRUE(cc->Contains('A'));

    EXPECT_TRUE(cc->Contains('B'));

    EXPECT_TRUE(cc->Contains('C'));

    EXPECT_TRUE(cc->Contains('D'));

}
