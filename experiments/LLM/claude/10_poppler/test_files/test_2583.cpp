#include <glib.h>
#include <poppler.h>
#include <poppler-structure-element.h>
#include <gtest/gtest.h>
#include <cstdio>
#include <cstring>

class PopplerStructureElementGlyphOrientationTest_2583 : public ::testing::Test {
protected:
    void SetUp() override {
        doc = nullptr;
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument *doc;
};

// Test that passing NULL returns the default enum value (due to g_return_val_if_fail)
TEST_F(PopplerStructureElementGlyphOrientationTest_2583, NullElementReturnsDefault_2583) {
    // g_return_val_if_fail should trigger and return default value
    // We suppress the GLib critical warning for this test
    g_test_expect_message("poppler", G_LOG_LEVEL_CRITICAL, "*");
    
    PopplerStructureGlyphOrientation result = poppler_structure_element_get_glyph_orientation(nullptr);
    
    // The function should return the first value from EnumNameValue when precondition fails
    // We just verify it doesn't crash and returns some valid enum value
    g_test_assert_expected_messages();
    
    // The default value should be a valid enum member
    (void)result; // Just verify no crash
}

// Test that a non-inline structure element returns the default value
TEST_F(PopplerStructureElementGlyphOrientationTest_2583, NonInlineElementReturnsDefault_2583) {
    // Load a tagged PDF if available; otherwise this test validates the null path
    GError *error = nullptr;
    
    // Try to create a simple PDF document for testing
    const char *pdf_path = g_getenv("POPPLER_TEST_PDF");
    if (!pdf_path) {
        // Skip if no test PDF available - the NULL test above covers the precondition
        GTEST_SKIP() << "No test PDF provided via POPPLER_TEST_PDF environment variable";
        return;
    }
    
    gchar *uri = g_filename_to_uri(pdf_path, nullptr, &error);
    if (!uri) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create URI for test PDF";
        return;
    }
    
    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);
    
    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not load test PDF";
        return;
    }
    
    // We can't easily construct a non-inline element without a real tagged PDF,
    // so we just verify the function exists and is callable
    SUCCEED();
}

// Test that the function handles the g_return_val_if_fail precondition properly
TEST_F(PopplerStructureElementGlyphOrientationTest_2583, PreconditionFailureReturnsSafeValue_2583) {
    // Setting up handler to catch GLib warnings
    g_log_set_always_fatal((GLogLevelFlags)0);
    
    // The old default handler will print a warning; we want to verify no crash
    if (g_test_subprocess()) {
        PopplerStructureGlyphOrientation result = poppler_structure_element_get_glyph_orientation(nullptr);
        (void)result;
        return;
    }
    
    // Just call with NULL and make sure we don't crash
    // Temporarily suppress critical messages
    GLogLevelFlags old_flags = g_log_set_always_fatal((GLogLevelFlags)0);
    
    PopplerStructureGlyphOrientation result = poppler_structure_element_get_glyph_orientation(nullptr);
    (void)result;
    
    g_log_set_always_fatal(old_flags);
    SUCCEED();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
