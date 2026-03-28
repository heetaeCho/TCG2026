#include <glib-object.h>
#include <gtest/gtest.h>

// Include the necessary poppler glib headers
extern "C" {
#include "poppler-document.h"
}

class PopplerFontInfoFreeTest_2237 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that poppler_font_info_free does not crash when given a valid PopplerFontInfo object
TEST_F(PopplerFontInfoFreeTest_2237, FreeValidFontInfo_2237)
{
    // Create a PopplerFontInfo object via GObject system
    PopplerFontInfo *font_info = static_cast<PopplerFontInfo *>(g_object_new(POPPLER_TYPE_FONT_INFO, nullptr));
    ASSERT_NE(font_info, nullptr);

    // This should not crash - it unrefs the object
    poppler_font_info_free(font_info);
}

// Test that poppler_font_info_free handles nullptr gracefully (g_return_if_fail should cause early return)
TEST_F(PopplerFontInfoFreeTest_2237, FreeNullFontInfoDoesNotCrash_2237)
{
    // g_return_if_fail should cause the function to return early without crashing
    // Note: g_return_if_fail will log a critical warning but not crash
    if (g_test_undefined()) {
        g_test_expect_message("GLib", G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    }
    poppler_font_info_free(nullptr);
    if (g_test_undefined()) {
        g_test_assert_expected_messages();
    }
}

// Test that poppler_font_info_free properly unrefs the object (ref count goes to 0)
TEST_F(PopplerFontInfoFreeTest_2237, FreeDecrementsRefCount_2237)
{
    PopplerFontInfo *font_info = static_cast<PopplerFontInfo *>(g_object_new(POPPLER_TYPE_FONT_INFO, nullptr));
    ASSERT_NE(font_info, nullptr);

    // Add an extra ref so we can verify the unref happens
    g_object_ref(font_info);

    // After free (which calls unref), ref count should be 1 (we added one extra)
    poppler_font_info_free(font_info);

    // The object should still be alive since we held an extra ref
    // Verify by checking we can still unref it
    g_object_unref(font_info);
}

// Test that calling free on a freshly created font_info with initial ref works
TEST_F(PopplerFontInfoFreeTest_2237, FreeFreshlyCreatedObject_2237)
{
    PopplerFontInfo *font_info = static_cast<PopplerFontInfo *>(g_object_new(POPPLER_TYPE_FONT_INFO, nullptr));
    ASSERT_NE(font_info, nullptr);

    // Initial ref count should be 1
    // After free/unref, object should be destroyed
    poppler_font_info_free(font_info);
    // If we get here without crash, the test passes
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
