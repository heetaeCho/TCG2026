#include <gtest/gtest.h>

#include "GfxFont.h"



// Mock class for GfxFontCIDWidthExcepV if needed (not required in this case)



class cmpWidthExcepVFunctorTest : public ::testing::Test {

protected:

    cmpWidthExcepVFunctor comparator;

};



TEST_F(cmpWidthExcepVFunctorTest, CompareDifferentValues_1972) {

    GfxFontCIDWidthExcepV w1 = {0.5, 1.0, 1.0};

    GfxFontCIDWidthExcepV w2 = {1.5, 1.0, 1.0};



    EXPECT_TRUE(comparator(w1, w2));

    EXPECT_FALSE(comparator(w2, w1));

}



TEST_F(cmpWidthExcepVFunctorTest, CompareSameValues_1972) {

    GfxFontCIDWidthExcepV w1 = {1.5, 1.0, 1.0};

    GfxFontCIDWidthExcepV w2 = {1.5, 1.0, 1.0};



    EXPECT_FALSE(comparator(w1, w2));

}



TEST_F(cmpWidthExcepVFunctorTest, CompareBoundaryValues_1972) {

    GfxFontCIDWidthExcepV w1 = {std::numeric_limits<double>::min(), 1.0, 1.0};

    GfxFontCIDWidthExcepV w2 = {std::numeric_limits<double>::max(), 1.0, 1.0};



    EXPECT_TRUE(comparator(w1, w2));

    EXPECT_FALSE(comparator(w2, w1));

}



TEST_F(cmpWidthExcepVFunctorTest, CompareNegativeValues_1972) {

    GfxFontCIDWidthExcepV w1 = {-1.5, 1.0, 1.0};

    GfxFontCIDWidthExcepV w2 = {-0.5, 1.0, 1.0};



    EXPECT_TRUE(comparator(w1, w2));

    EXPECT_FALSE(comparator(w2, w1));

}
