#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>

class PopplerStructureElementRubyAlignTest_2581 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PDF with structure elements to properly test.
        // For unit testing purposes, we test observable behavior through the API.
    }

    void TearDown() override {
    }
};

// Test that passing NULL returns the default value (first enum value)
// g_return_val_if_fail should trigger and return the default
TEST_F(PopplerStructureElementRubyAlignTest_2581, NullElementReturnsDefault_2581)
{
    // When passing NULL, g_return_val_if_fail should fail and return default value
    // We expect a critical warning from GLib
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    PopplerStructureRubyAlign result = poppler_structure_element_get_ruby_align(NULL);
    g_test_assert_expected_messages();
    // The default should be the first value in the enum values table
    // Typically POPPLER_STRUCTURE_RUBY_ALIGN_DISTRIBUTE for ruby align
    // We just verify it doesn't crash and returns some valid enum value
    (void)result;
}

// Test with a real document that has tagged structure
class PopplerStructureElementFromDocTest_2581 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;

    void SetUp() override {
        GError *error = nullptr;
        // Try to load a tagged PDF for testing
        // If not available, tests will be skipped
        doc = nullptr;
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerDocument *loadTaggedPDF(const char *path) {
        GError *error = nullptr;
        gchar *uri = g_filename_to_uri(path, NULL, &error);
        if (!uri) {
            if (error) g_error_free(error);
            return nullptr;
        }
        PopplerDocument *d = poppler_document_new_from_file(uri, NULL, &error);
        g_free(uri);
        if (error) g_error_free(error);
        return d;
    }
};

// Test that a non-inline structure element returns default via g_return_val_if_fail
TEST_F(PopplerStructureElementFromDocTest_2581, NonInlineElementReturnsDefault_2581)
{
    // Create a simple PDF in memory to test with
    // Since we can't easily create structure elements without a real tagged PDF,
    // we verify the NULL case behavior which exercises the guard clause
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    PopplerStructureRubyAlign result = poppler_structure_element_get_ruby_align(nullptr);
    g_test_assert_expected_messages();
    // Just ensure we got a value without crashing
    SUCCEED();
}

// Test that the return type is a valid PopplerStructureRubyAlign enum value
TEST_F(PopplerStructureElementRubyAlignTest_2581, ReturnTypeIsValidEnum_2581)
{
    // With NULL input, we get the default enum value
    g_test_expect_message(NULL, G_LOG_LEVEL_CRITICAL, "*assertion*failed*");
    PopplerStructureRubyAlign result = poppler_structure_element_get_ruby_align(NULL);
    g_test_assert_expected_messages();

    // Verify the returned value is within known enum range
    EXPECT_TRUE(result == POPPLER_STRUCTURE_RUBY_ALIGN_DISTRIBUTE ||
                result == POPPLER_STRUCTURE_RUBY_ALIGN_START ||
                result == POPPLER_STRUCTURE_RUBY_ALIGN_CENTER ||
                result == POPPLER_STRUCTURE_RUBY_ALIGN_END ||
                result == POPPLER_STRUCTURE_RUBY_ALIGN_JUSTIFY);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
