#include <gtest/gtest.h>

#include "poppler-form-field.h"



// Mocking external collaborators if needed (none in this case)



TEST(PopplerSigningDataTest_2369, GetFontColor_ReturnsValidPointer_2369) {

    PopplerSigningData signing_data;

    const PopplerColor* font_color = poppler_signing_data_get_font_color(&signing_data);

    EXPECT_NE(font_color, nullptr);

}



TEST(PopplerSigningDataTest_2369, GetFontColor_ReturnsNullptrForNullInput_2369) {

    const PopplerColor* font_color = poppler_signing_data_get_font_color(nullptr);

    EXPECT_EQ(font_color, nullptr);

}
