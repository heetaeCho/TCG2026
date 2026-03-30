#include <gtest/gtest.h>

#include "poppler-page.h"

#include "poppler-private.h"



class PopplerRectangleTest_2467 : public ::testing::Test {

protected:

    PopplerRectangle rectangle;

};



TEST_F(PopplerRectangleTest_2467, GetMatchContinued_ReturnsFalseForNullptr_2467) {

    EXPECT_FALSE(poppler_rectangle_find_get_match_continued(nullptr));

}



TEST_F(PopplerRectangleTest_2467, GetMatchContinued_ReturnsTrueWhenMatchContinuedIsSet_2467) {

    auto* ext_rectangle = reinterpret_cast<PopplerRectangleExtended*>(&rectangle);

    ext_rectangle->match_continued = true;

    EXPECT_TRUE(poppler_rectangle_find_get_match_continued(&rectangle));

}



TEST_F(PopplerRectangleTest_2467, GetMatchContinued_ReturnsFalseWhenMatchContinuedIsNotSet_2467) {

    auto* ext_rectangle = reinterpret_cast<PopplerRectangleExtended*>(&rectangle);

    ext_rectangle->match_continued = false;

    EXPECT_FALSE(poppler_rectangle_find_get_match_continued(&rectangle));

}
