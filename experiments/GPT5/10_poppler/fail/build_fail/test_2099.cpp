#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-annot.h"
#include "poppler-annot.cc"

// Mock external dependencies (if any)
class MockCatalog : public Catalog {
public:
    MOCK_METHOD(int, getNumPages, (), (override));
    MOCK_METHOD(Page*, getPage, (int i), (override));
    MOCK_METHOD(Ref*, getPageRef, (int i), (override));
    MOCK_METHOD(Form*, getCreateForm, (), (override));
};

// TEST CASE 1: poppler_annot_free_text_set_da_to_native applies default font if no font_desc is provided
TEST_F(PopplerAnnotFreeTextTest_2099, DefaultFontWhenNoFontDesc_2099) {
    PopplerAnnotFreeText annot;
    annot.font_desc = nullptr; // No font_desc provided
    annot.font_color = PopplerColor{0, 0, 0}; // Default black color

    // Assuming the default font and size should be applied
    poppler_annot_free_text_set_da_to_native(&annot);

    // Check that the font is "Sans" and size is 11
    EXPECT_EQ(annot.font_desc->font_name, "Sans");
    EXPECT_EQ(annot.font_desc->size_pt, 11.0);
}

// TEST CASE 2: poppler_annot_free_text_set_da_to_native applies custom font and size if font_desc is provided
TEST_F(PopplerAnnotFreeTextTest_2099, CustomFontWhenFontDescProvided_2099) {
    // Setup a mock font_desc
    PopplerFontDescription font_desc;
    font_desc.font_name = "Arial";
    font_desc.size_pt = 12.0;
    PopplerAnnotFreeText annot;
    annot.font_desc = &font_desc;
    annot.font_color = PopplerColor{0, 0, 0};

    poppler_annot_free_text_set_da_to_native(&annot);

    // Check that the custom font and size are applied
    EXPECT_EQ(annot.font_desc->font_name, "Arial");
    EXPECT_EQ(annot.font_desc->size_pt, 12.0);
}

// TEST CASE 3: poppler_annot_free_text_set_da_to_native applies font from form when available
TEST_F(PopplerAnnotFreeTextTest_2099, FontFromForm_2099) {
    // Setup a mock catalog and form
    MockCatalog mockCatalog;
    Form mockForm;
    PopplerAnnotFreeText annot;
    annot.font_desc = nullptr; // No font_desc provided
    annot.font_color = PopplerColor{0, 0, 0}; // Default black color

    // Mock the form to return "Arial" font when findFontInDefaultResources is called
    EXPECT_CALL(mockCatalog, getCreateForm()).WillOnce(testing::Return(&mockForm));
    EXPECT_CALL(mockForm, findFontInDefaultResources(testing::_, testing::_))
        .WillOnce(testing::Return("Arial"));

    // Assuming the font should be applied from form
    poppler_annot_free_text_set_da_to_native(&annot);

    // Check that the font from form ("Arial") is applied
    EXPECT_EQ(annot.font_desc->font_name, "Arial");
}

// TEST CASE 4: poppler_annot_free_text_set_da_to_native ensures font is added to default resources when not found
TEST_F(PopplerAnnotFreeTextTest_2099, AddFontToDefaultResourcesWhenNotFound_2099) {
    // Setup a mock catalog and form
    MockCatalog mockCatalog;
    Form mockForm;
    PopplerAnnotFreeText annot;
    annot.font_desc = nullptr; // No font_desc provided
    annot.font_color = PopplerColor{0, 0, 0}; // Default black color

    // Mock the form to simulate a font not found in resources, and adding it
    EXPECT_CALL(mockCatalog, getCreateForm()).WillOnce(testing::Return(&mockForm));
    EXPECT_CALL(mockForm, findFontInDefaultResources(testing::_, testing::_))
        .WillOnce(testing::Return(""));
    EXPECT_CALL(mockForm, addFontToDefaultResources(testing::_, testing::_))
        .WillOnce(testing::Return(Form::AddFontResult{}));

    poppler_annot_free_text_set_da_to_native(&annot);

    // Verify that font is added to default resources
    EXPECT_EQ(annot.font_desc->font_name, "Arial"); // Assuming font name added is "Arial"
}

// TEST CASE 5: poppler_annot_free_text_set_da_to_native handles edge case when font_desc is empty
TEST_F(PopplerAnnotFreeTextTest_2099, HandlesEmptyFontDesc_2099) {
    // Setup an empty font_desc
    PopplerFontDescription font_desc;
    font_desc.font_name = "";
    font_desc.size_pt = 0.0;
    PopplerAnnotFreeText annot;
    annot.font_desc = &font_desc;
    annot.font_color = PopplerColor{0, 0, 0};

    poppler_annot_free_text_set_da_to_native(&annot);

    // Check that the default font and size are applied when font_desc is empty
    EXPECT_EQ(annot.font_desc->font_name, "Sans");
    EXPECT_EQ(annot.font_desc->size_pt, 11.0);
}