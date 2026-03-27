#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "GfxFont.h"



// Assuming CID is an integer type for this context

using CID = int;



TEST(cmpWidthExcepFunctorTest_1971, CompareFirstCID_LessThan_ReturnsTrue_1971) {

    cmpWidthExcepFunctor comparator;

    GfxFontCIDWidthExcep w1{1, 2};

    GfxFontCIDWidthExcep w2{3, 4};



    EXPECT_TRUE(comparator(w1, w2));

}



TEST(cmpWidthExcepFunctorTest_1971, CompareFirstCID_Equal_ReturnsFalse_1971) {

    cmpWidthExcepFunctor comparator;

    GfxFontCIDWidthExcep w1{3, 2};

    GfxFontCIDWidthExcep w2{3, 4};



    EXPECT_FALSE(comparator(w1, w2));

}



TEST(cmpWidthExcepFunctorTest_1971, CompareFirstCID_GreaterThan_ReturnsFalse_1971) {

    cmpWidthExcepFunctor comparator;

    GfxFontCIDWidthExcep w1{5, 2};

    GfxFontCIDWidthExcep w2{3, 4};



    EXPECT_FALSE(comparator(w1, w2));

}



TEST(cmpWidthExcepFunctorTest_1971, BoundaryCondition_FirstCID_MinInt_ReturnsTrue_1971) {

    cmpWidthExcepFunctor comparator;

    GfxFontCIDWidthExcep w1{std::numeric_limits<CID>::min(), 2};

    GfxFontCIDWidthExcep w2{3, 4};



    EXPECT_TRUE(comparator(w1, w2));

}



TEST(cmpWidthExcepFunctorTest_1971, BoundaryCondition_SecondCID_MaxInt_ReturnsFalse_1971) {

    cmpWidthExcepFunctor comparator;

    GfxFontCIDWidthExcep w1{5, std::numeric_limits<CID>::max()};

    GfxFontCIDWidthExcep w2{3, 4};



    EXPECT_FALSE(comparator(w1, w2));

}
