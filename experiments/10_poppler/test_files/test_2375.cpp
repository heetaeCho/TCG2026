#include <gtest/gtest.h>

#include "poppler-form-field.h"



using namespace testing;



// Mock class for PopplerColor if needed (not required in this case as PopplerColor is a simple struct)

struct MockPopplerColor : public PopplerColor {

    // No need to mock anything here since it's a simple structure

};



TEST_F(PopplerSigningDataTest_2375, GetBorderColor_ReturnsNonNullPointer_2375) {

    PopplerSigningData signing_data;

    const PopplerColor *border_color = poppler_signing_data_get_border_color(&signing_data);

    EXPECT_NE(border_color, nullptr);

}



TEST_F(PopplerSigningDataTest_2375, GetBorderColor_ReturnsCorrectPointer_2375) {

    PopplerSigningData signing_data;

    const PopplerColor *border_color = poppler_signing_data_get_border_color(&signing_data);

    EXPECT_EQ(border_color, &signing_data.border_color);

}



TEST_F(PopplerSigningDataTest_2375, GetBorderColor_NullPointer_ReturnsNull_2375) {

    const PopplerColor *border_color = poppler_signing_data_get_border_color(nullptr);

    EXPECT_EQ(border_color, nullptr);

}
