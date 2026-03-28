#include <gtest/gtest.h>

#include "poppler-annot.h"



// Mock for PopplerFontDescription if needed (not required in this case as we are treating it as a black box)

class MockPopplerFontDescription {

public:

    MOCK_METHOD(PopplerFontDescription*, poppler_font_description_copy, (), (const));

};



// Test fixture for PopplerAnnotFreeText

class PopplerAnnotFreeTextTest_2101 : public ::testing::Test {

protected:

    PopplerAnnotFreeText* annot;



    void SetUp() override {

        annot = new PopplerAnnotFreeText();

        annot->font_desc = nullptr;

    }



    void TearDown() override {

        poppler_annot_free_text_get_font_desc(annot); // Ensures any allocated font_desc is freed

        delete annot;

    }

};



// Test case for normal operation where font_desc is not null

TEST_F(PopplerAnnotFreeTextTest_2101, GetFontDesc_ReturnsCopyOfFontDesc_2101) {

    PopplerFontDescription* expected_font_desc = new PopplerFontDescription();

    annot->font_desc = expected_font_desc;



    PopplerFontDescription* result = poppler_annot_free_text_get_font_desc(annot);



    EXPECT_NE(result, nullptr);

    EXPECT_EQ(result, expected_font_desc); // Assuming copy returns the same pointer for simplicity



    delete result; // Clean up the copied font description

}



// Test case for boundary condition where font_desc is null

TEST_F(PopplerAnnotFreeTextTest_2101, GetFontDesc_ReturnsNullWhenFontDescIsNull_2101) {

    PopplerFontDescription* result = poppler_annot_free_text_get_font_desc(annot);



    EXPECT_EQ(result, nullptr);

}
