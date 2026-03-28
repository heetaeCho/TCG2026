#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Forward declarations and minimal type definitions needed for testing
// Based on the known/inferred dependencies

extern "C" {

typedef struct {
    char *family_name;
    double size;
} PopplerFontDescription;

typedef struct {
    unsigned short red;
    unsigned short green;
    unsigned short blue;
} PopplerColor;

typedef struct {
    PopplerFontDescription *font_desc;
    PopplerColor font_color;
} PopplerAnnotFreeText;

// Function under test
PopplerFontDescription *poppler_annot_free_text_get_font_desc(PopplerAnnotFreeText *poppler_annot);

// We need the copy function declaration - it's used internally
PopplerFontDescription *poppler_font_description_copy(const PopplerFontDescription *desc);

} // extern "C"

class PopplerAnnotFreeTextGetFontDescTest_2101 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that when font_desc is nullptr, the function returns nullptr
TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, ReturnsNullWhenFontDescIsNull_2101)
{
    PopplerAnnotFreeText annot;
    annot.font_desc = nullptr;
    annot.font_color = {0, 0, 0};

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(&annot);

    EXPECT_EQ(result, nullptr);
}

// Test that when font_desc is set, the function returns a non-null copy
TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, ReturnsNonNullWhenFontDescIsSet_2101)
{
    PopplerFontDescription desc;
    desc.family_name = nullptr;
    desc.size = 12.0;

    PopplerAnnotFreeText annot;
    annot.font_desc = &desc;
    annot.font_color = {0, 0, 0};

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(&annot);

    // The function should return a copy (non-null) when font_desc is non-null
    EXPECT_NE(result, nullptr);

    // The returned pointer should be a copy, not the same pointer
    if (result != nullptr) {
        EXPECT_NE(result, &desc);
        // Clean up - in real usage poppler_font_description_free would be called
        g_free(result);
    }
}

// Test that the returned copy has the same size value as the original
TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, ReturnedCopyHasCorrectSize_2101)
{
    PopplerFontDescription desc;
    desc.family_name = nullptr;
    desc.size = 24.5;

    PopplerAnnotFreeText annot;
    annot.font_desc = &desc;
    annot.font_color = {0, 0, 0};

    PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(&annot);

    ASSERT_NE(result, nullptr);
    EXPECT_DOUBLE_EQ(result->size, 24.5);

    if (result) {
        g_free(result);
    }
}

// Test that calling the function multiple times with null font_desc consistently returns nullptr
TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, ConsistentlyReturnsNullForNullFontDesc_2101)
{
    PopplerAnnotFreeText annot;
    annot.font_desc = nullptr;
    annot.font_color = {0, 0, 0};

    for (int i = 0; i < 5; i++) {
        PopplerFontDescription *result = poppler_annot_free_text_get_font_desc(&annot);
        EXPECT_EQ(result, nullptr);
    }
}

// Test that each call returns a distinct copy (not the same pointer)
TEST_F(PopplerAnnotFreeTextGetFontDescTest_2101, EachCallReturnsDistinctCopy_2101)
{
    PopplerFontDescription desc;
    desc.family_name = nullptr;
    desc.size = 10.0;

    PopplerAnnotFreeText annot;
    annot.font_desc = &desc;
    annot.font_color = {0, 0, 0};

    PopplerFontDescription *result1 = poppler_annot_free_text_get_font_desc(&annot);
    PopplerFontDescription *result2 = poppler_annot_free_text_get_font_desc(&annot);

    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1, result2);

    if (result1) g_free(result1);
    if (result2) g_free(result2);
}
