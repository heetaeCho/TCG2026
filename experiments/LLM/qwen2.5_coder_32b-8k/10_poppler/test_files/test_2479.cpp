#include <gtest/gtest.h>

#include "poppler-page.h"



// Assuming the function poppler_text_attributes_free is part of a class or can be tested in isolation.

// Since it's a standalone function and there's no class to inherit from, we'll use TEST instead of TEST_F.



TEST(PopplerTextAttributesFreeTest_2479, FreesFontNamePointer_2479) {

    // Arrange

    char* font_name = strdup("Sample Font");

    PopplerTextAttributes text_attrs;

    text_attrs.font_name = font_name;



    // Act & Assert (We assume that if the function doesn't crash and there are no memory leaks, it works)

    poppler_text_attributes_free(&text_attrs);

    // No assertion here as we're checking for memory management which is typically done via valgrind or similar tools.

}



TEST(PopplerTextAttributesFreeTest_2479, NullFontNamePointer_2479) {

    // Arrange

    PopplerTextAttributes text_attrs;

    text_attrs.font_name = nullptr;



    // Act & Assert (We assume that if the function doesn't crash and there are no memory leaks, it works)

    poppler_text_attributes_free(&text_attrs);

}



TEST(PopplerTextAttributesFreeTest_2479, ValidData_2479) {

    // Arrange

    char* font_name = strdup("Sample Font");

    PopplerTextAttributes text_attrs;

    text_attrs.font_name = font_name;

    text_attrs.font_size = 12;

    text_attrs.is_underlined = true;

    text_attrs.color.red = 0xFF;

    text_attrs.color.green = 0x00;

    text_attrs.color.blue = 0x00;

    text_attrs.start_index = 0;

    text_attrs.end_index = 10;



    // Act & Assert (We assume that if the function doesn't crash and there are no memory leaks, it works)

    poppler_text_attributes_free(&text_attrs);

}



TEST(PopplerTextAttributesFreeTest_2479, ZeroedData_2479) {

    // Arrange

    PopplerTextAttributes text_attrs = {0};



    // Act & Assert (We assume that if the function doesn't crash and there are no memory leaks, it works)

    poppler_text_attributes_free(&text_attrs);

}
