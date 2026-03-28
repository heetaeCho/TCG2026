#include <gtest/gtest.h>

#include "poppler-page.h"

#include "poppler-private.h"



// Mocking external collaborators or dependencies if needed.

// In this case, no additional mocking is required.



class PopplerRectangleTest_2468 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary test objects or state

        rectangle.x2 = 0;

        rectangle.y2 = 0;



        ext_rectangle.match_continued = false;

        ext_rectangle.ignored_hyphen = false;



        // Simulate the internal extended structure

        rectangle.extended = reinterpret_cast<PopplerRectangleExtended*>(&ext_rectangle);

    }



    PopplerRectangle rectangle;

    PopplerRectangleExtended ext_rectangle;

};



TEST_F(PopplerRectangleTest_2468, NullPointerCheck_2468) {

    EXPECT_FALSE(poppler_rectangle_find_get_ignored_hyphen(nullptr));

}



TEST_F(PopplerRectangleTest_2468, IgnoredHyphenTrue_2468) {

    ext_rectangle.ignored_hyphen = true;

    EXPECT_TRUE(poppler_rectangle_find_get_ignored_hyphen(&rectangle));

}



TEST_F(PopplerRectangleTest_2468, IgnoredHyphenFalse_2468) {

    ext_rectangle.ignored_hyphen = false;

    EXPECT_FALSE(poppler_rectangle_find_get_ignored_hyphen(&rectangle));

}
