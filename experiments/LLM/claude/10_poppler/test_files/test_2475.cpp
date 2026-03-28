#include <gtest/gtest.h>

extern "C" {
#include <glib.h>

// Forward declaration of the struct and function based on the interface
typedef struct _PopplerTextAttributes PopplerTextAttributes;

struct _PopplerTextAttributes
{
    char *font_name;
    double font_size;
    gboolean is_underlined;
    PopplerColor color;
    int start_index;
    int end_index;
};

PopplerTextAttributes *poppler_text_attributes_new(void);
PopplerTextAttributes *poppler_text_attributes_copy(PopplerTextAttributes *text_attrs);
void poppler_text_attributes_free(PopplerTextAttributes *text_attrs);
}

// Include the actual poppler-glib header if available
// For this test we rely on the declarations above

class PopplerTextAttributesTest_2475 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled in individual tests
    }
};

// Test that poppler_text_attributes_new returns a non-null pointer
TEST_F(PopplerTextAttributesTest_2475, NewReturnsNonNull_2475)
{
    PopplerTextAttributes *attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr);
    poppler_text_attributes_free(attrs);
}

// Test that newly created attributes are zero-initialized
TEST_F(PopplerTextAttributesTest_2475, NewIsZeroInitialized_2475)
{
    PopplerTextAttributes *attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr);

    // Since g_slice_new0 is used, all fields should be zero-initialized
    EXPECT_EQ(attrs->font_name, nullptr);
    EXPECT_DOUBLE_EQ(attrs->font_size, 0.0);
    EXPECT_EQ(attrs->is_underlined, FALSE);
    EXPECT_EQ(attrs->color.red, 0);
    EXPECT_EQ(attrs->color.green, 0);
    EXPECT_EQ(attrs->color.blue, 0);
    EXPECT_EQ(attrs->start_index, 0);
    EXPECT_EQ(attrs->end_index, 0);

    poppler_text_attributes_free(attrs);
}

// Test that multiple allocations return distinct pointers
TEST_F(PopplerTextAttributesTest_2475, MultipleAllocationsAreDistinct_2475)
{
    PopplerTextAttributes *attrs1 = poppler_text_attributes_new();
    PopplerTextAttributes *attrs2 = poppler_text_attributes_new();

    ASSERT_NE(attrs1, nullptr);
    ASSERT_NE(attrs2, nullptr);
    EXPECT_NE(attrs1, attrs2);

    poppler_text_attributes_free(attrs1);
    poppler_text_attributes_free(attrs2);
}

// Test that freeing a null pointer doesn't crash (if the API supports it)
TEST_F(PopplerTextAttributesTest_2475, FreeNullDoesNotCrash_2475)
{
    // poppler_text_attributes_free should handle NULL gracefully
    poppler_text_attributes_free(nullptr);
    // If we reach here, the test passes
    SUCCEED();
}

// Test that fields can be modified after creation
TEST_F(PopplerTextAttributesTest_2475, FieldsCanBeModified_2475)
{
    PopplerTextAttributes *attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr);

    attrs->font_size = 12.5;
    attrs->is_underlined = TRUE;
    attrs->start_index = 5;
    attrs->end_index = 10;
    attrs->color.red = 65535;
    attrs->color.green = 32768;
    attrs->color.blue = 0;
    attrs->font_name = g_strdup("Helvetica");

    EXPECT_DOUBLE_EQ(attrs->font_size, 12.5);
    EXPECT_EQ(attrs->is_underlined, TRUE);
    EXPECT_EQ(attrs->start_index, 5);
    EXPECT_EQ(attrs->end_index, 10);
    EXPECT_EQ(attrs->color.red, 65535);
    EXPECT_EQ(attrs->color.green, 32768);
    EXPECT_EQ(attrs->color.blue, 0);
    EXPECT_STREQ(attrs->font_name, "Helvetica");

    poppler_text_attributes_free(attrs);
}

// Test copy functionality if available
TEST_F(PopplerTextAttributesTest_2475, CopyCreatesIndependentCopy_2475)
{
    PopplerTextAttributes *attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr);

    attrs->font_size = 14.0;
    attrs->is_underlined = TRUE;
    attrs->start_index = 3;
    attrs->end_index = 7;
    attrs->font_name = g_strdup("Times");
    attrs->color.red = 100;
    attrs->color.green = 200;
    attrs->color.blue = 50;

    PopplerTextAttributes *copy = poppler_text_attributes_copy(attrs);
    ASSERT_NE(copy, nullptr);
    EXPECT_NE(copy, attrs);

    EXPECT_DOUBLE_EQ(copy->font_size, 14.0);
    EXPECT_EQ(copy->is_underlined, TRUE);
    EXPECT_EQ(copy->start_index, 3);
    EXPECT_EQ(copy->end_index, 7);
    EXPECT_STREQ(copy->font_name, "Times");
    EXPECT_EQ(copy->color.red, 100);
    EXPECT_EQ(copy->color.green, 200);
    EXPECT_EQ(copy->color.blue, 50);

    poppler_text_attributes_free(attrs);
    poppler_text_attributes_free(copy);
}

// Test that copy of null returns null
TEST_F(PopplerTextAttributesTest_2475, CopyNullReturnsNull_2475)
{
    PopplerTextAttributes *copy = poppler_text_attributes_copy(nullptr);
    EXPECT_EQ(copy, nullptr);
}

// Test rapid allocation and deallocation
TEST_F(PopplerTextAttributesTest_2475, RapidAllocDealloc_2475)
{
    for (int i = 0; i < 100; i++) {
        PopplerTextAttributes *attrs = poppler_text_attributes_new();
        ASSERT_NE(attrs, nullptr);
        attrs->font_size = static_cast<double>(i);
        EXPECT_DOUBLE_EQ(attrs->font_size, static_cast<double>(i));
        poppler_text_attributes_free(attrs);
    }
}

// Test boundary values for numeric fields
TEST_F(PopplerTextAttributesTest_2475, BoundaryValues_2475)
{
    PopplerTextAttributes *attrs = poppler_text_attributes_new();
    ASSERT_NE(attrs, nullptr);

    attrs->font_size = 0.0;
    EXPECT_DOUBLE_EQ(attrs->font_size, 0.0);

    attrs->font_size = 1e308;
    EXPECT_DOUBLE_EQ(attrs->font_size, 1e308);

    attrs->start_index = G_MAXINT;
    EXPECT_EQ(attrs->start_index, G_MAXINT);

    attrs->end_index = G_MININT;
    EXPECT_EQ(attrs->end_index, G_MININT);

    attrs->color.red = 65535;
    attrs->color.green = 65535;
    attrs->color.blue = 65535;
    EXPECT_EQ(attrs->color.red, 65535);
    EXPECT_EQ(attrs->color.green, 65535);
    EXPECT_EQ(attrs->color.blue, 65535);

    poppler_text_attributes_free(attrs);
}
