#include <gtest/gtest.h>

#include "unicode_casefold.h"

#include "parse.cc"



using namespace re2;



TEST(ApplyFoldTest_485, NormalOperation_EvenOddDelta_485) {

    CaseFold f = {1};  // delta is even <-> odd

    Rune r = 2;        // even number

    EXPECT_EQ(ApplyFold(&f, r), 3);  // should become odd



    r = 3;             // odd number

    EXPECT_EQ(ApplyFold(&f, r), 2);  // should become even

}



TEST(ApplyFoldTest_485, NormalOperation_OddEvenDelta_485) {

    CaseFold f = {-1}; // delta is odd <-> even

    Rune r = 2;        // even number

    EXPECT_EQ(ApplyFold(&f, r), 1);  // should become odd



    r = 3;             // odd number

    EXPECT_EQ(ApplyFold(&f, r), 4);  // should become even

}



TEST(ApplyFoldTest_485, BoundaryCondition_DefaultDelta_485) {

    CaseFold f = {5};  // default delta case

    Rune r = 10;

    EXPECT_EQ(ApplyFold(&f, r), 15); // should add delta



    r = -3;

    EXPECT_EQ(ApplyFold(&f, r), 2);  // should add delta

}



TEST(ApplyFoldTest_485, BoundaryCondition_ZeroDelta_485) {

    CaseFold f = {0};  // zero delta case

    Rune r = 10;

    EXPECT_EQ(ApplyFold(&f, r), 10); // should remain unchanged



    r = -3;

    EXPECT_EQ(ApplyFold(&f, r), -3); // should remain unchanged

}



TEST(ApplyFoldTest_485, EvenOddSkip_DefaultBehavior_485) {

    CaseFold f = {EvenOddSkip};

    Rune r = 2;        // even number, but not every other

    f.lo = 1;

    EXPECT_EQ(ApplyFold(&f, r), 2);  // should remain unchanged



    r = 3;             // odd number, but not every other

    EXPECT_EQ(ApplyFold(&f, r), 3);  // should remain unchanged



    r = 4;             // even number, every other (4 - 1) % 2 == 1

    EXPECT_EQ(ApplyFold(&f, r), 5);  // should become odd



    r = 5;             // odd number, every other (5 - 1) % 2 == 0

    EXPECT_EQ(ApplyFold(&f, r), 4);  // should become even

}



TEST(ApplyFoldTest_485, OddEvenSkip_DefaultBehavior_485) {

    CaseFold f = {OddEvenSkip};

    Rune r = 1;        // odd number, but not every other

    f.lo = 1;

    EXPECT_EQ(ApplyFold(&f, r), 1);  // should remain unchanged



    r = 2;             // even number, but not every other

    EXPECT_EQ(ApplyFold(&f, r), 2);  // should remain unchanged



    r = 3;             // odd number, every other (3 - 1) % 2 == 0

    EXPECT_EQ(ApplyFold(&f, r), 4);  // should become even



    r = 4;             // even number, every other (4 - 1) % 2 == 1

    EXPECT_EQ(ApplyFold(&f, r), 3);  // should become odd

}
