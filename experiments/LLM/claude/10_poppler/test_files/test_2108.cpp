#include <gtest/gtest.h>
#include <glib.h>

// Include the header for the function under test
extern "C" {
#include "poppler-annot.h"
}

// If the header doesn't provide the declaration, declare it externally
extern "C" {
PopplerAnnotCalloutLine *poppler_annot_callout_line_new(void);
PopplerAnnotCalloutLine *poppler_annot_callout_line_copy(PopplerAnnotCalloutLine *callout);
void poppler_annot_callout_line_free(PopplerAnnotCalloutLine *callout);
}

class PopplerAnnotCalloutLineTest_2108 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that freeing a valid callout line does not crash
TEST_F(PopplerAnnotCalloutLineTest_2108, FreeValidCalloutLine_2108)
{
    PopplerAnnotCalloutLine *callout = (PopplerAnnotCalloutLine *)g_malloc0(sizeof(PopplerAnnotCalloutLine));
    ASSERT_NE(callout, nullptr);

    // Should not crash or cause errors
    poppler_annot_callout_line_free(callout);
}

// Test that freeing a NULL pointer does not crash (g_free handles NULL gracefully)
TEST_F(PopplerAnnotCalloutLineTest_2108, FreeNullCalloutLine_2108)
{
    // g_free(NULL) is safe and should not crash
    poppler_annot_callout_line_free(nullptr);
}

// Test that freeing a callout line with populated fields works correctly
TEST_F(PopplerAnnotCalloutLineTest_2108, FreePopulatedCalloutLine_2108)
{
    PopplerAnnotCalloutLine *callout = (PopplerAnnotCalloutLine *)g_malloc0(sizeof(PopplerAnnotCalloutLine));
    ASSERT_NE(callout, nullptr);

    callout->multiline = 1;
    callout->x3 = 100;
    callout->y3 = 200;

    // Should not crash
    poppler_annot_callout_line_free(callout);
}

// Test freeing a callout line allocated with g_new
TEST_F(PopplerAnnotCalloutLineTest_2108, FreeGNewAllocatedCalloutLine_2108)
{
    PopplerAnnotCalloutLine *callout = g_new0(PopplerAnnotCalloutLine, 1);
    ASSERT_NE(callout, nullptr);

    callout->multiline = 0;
    callout->x3 = -50;
    callout->y3 = -75;

    poppler_annot_callout_line_free(callout);
}

// Test that the struct fields are accessible and writable before free
TEST_F(PopplerAnnotCalloutLineTest_2108, StructFieldsAccessible_2108)
{
    PopplerAnnotCalloutLine *callout = (PopplerAnnotCalloutLine *)g_malloc0(sizeof(PopplerAnnotCalloutLine));
    ASSERT_NE(callout, nullptr);

    callout->multiline = 42;
    callout->x3 = 999;
    callout->y3 = -999;

    EXPECT_EQ(callout->multiline, 42);
    EXPECT_EQ(callout->x3, 999);
    EXPECT_EQ(callout->y3, -999);

    poppler_annot_callout_line_free(callout);
}

// Test with zero-initialized struct
TEST_F(PopplerAnnotCalloutLineTest_2108, FreeZeroInitializedCalloutLine_2108)
{
    PopplerAnnotCalloutLine *callout = (PopplerAnnotCalloutLine *)g_malloc0(sizeof(PopplerAnnotCalloutLine));
    ASSERT_NE(callout, nullptr);

    EXPECT_EQ(callout->multiline, 0);
    EXPECT_EQ(callout->x3, 0);
    EXPECT_EQ(callout->y3, 0);

    poppler_annot_callout_line_free(callout);
}

// Test with boundary integer values
TEST_F(PopplerAnnotCalloutLineTest_2108, FreeBoundaryValues_2108)
{
    PopplerAnnotCalloutLine *callout = (PopplerAnnotCalloutLine *)g_malloc0(sizeof(PopplerAnnotCalloutLine));
    ASSERT_NE(callout, nullptr);

    callout->multiline = INT_MAX;
    callout->x3 = INT_MIN;
    callout->y3 = INT_MAX;

    EXPECT_EQ(callout->multiline, INT_MAX);
    EXPECT_EQ(callout->x3, INT_MIN);
    EXPECT_EQ(callout->y3, INT_MAX);

    poppler_annot_callout_line_free(callout);
}
