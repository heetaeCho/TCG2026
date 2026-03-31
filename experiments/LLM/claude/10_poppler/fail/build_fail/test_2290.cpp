#include <gtest/gtest.h>
#include <glib.h>
#include "poppler-action.h"
#include "GooString.h"

// Since dest_new_named is a static function in poppler-action.cc, we need to
// either make it accessible or include the source file. We'll declare it as
// an extern or include the relevant portion. Since it's static, we need to
// work around that. One common approach for testing static functions is to
// include the .cc file directly.
#include "poppler-action.cc"

class DestNewNamedTest_2290 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup is handled per test
    }
};

// Test that passing nullptr results in POPPLER_DEST_UNKNOWN type
TEST_F(DestNewNamedTest_2290, NullptrReturnsUnknownDest_2290) {
    PopplerDest *dest = dest_new_named(nullptr);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
    g_slice_free(PopplerDest, dest);
}

// Test that a valid named destination string results in POPPLER_DEST_NAMED type
TEST_F(DestNewNamedTest_2290, ValidStringReturnsNamedDest_2290) {
    GooString named_dest("section1");
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);
    EXPECT_NE(dest->named_dest, nullptr);
    // Verify the named_dest content matches
    gchar *named = reinterpret_cast<gchar *>(dest->named_dest);
    // poppler_named_dest_from_bytestring should produce a string from the bytes
    // We can at least check it's non-null
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}

// Test with an empty string - should still be POPPLER_DEST_NAMED
TEST_F(DestNewNamedTest_2290, EmptyStringReturnsNamedDest_2290) {
    GooString named_dest("");
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}

// Test with a longer destination name
TEST_F(DestNewNamedTest_2290, LongStringReturnsNamedDest_2290) {
    std::string long_name(1024, 'A');
    GooString named_dest(long_name);
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);
    EXPECT_NE(dest->named_dest, nullptr);
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}

// Test with a string containing special characters
TEST_F(DestNewNamedTest_2290, SpecialCharsStringReturnsNamedDest_2290) {
    GooString named_dest("page#1&section=2");
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);
    EXPECT_NE(dest->named_dest, nullptr);
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}

// Test with a string containing null bytes (binary data)
TEST_F(DestNewNamedTest_2290, BinaryDataStringReturnsNamedDest_2290) {
    const char data[] = "abc\0def";
    GooString named_dest(data, 7);  // Include the null byte in the middle
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);
    EXPECT_NE(dest->named_dest, nullptr);
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}

// Test that the dest struct fields are zero-initialized (from g_slice_new0)
// when nullptr is passed
TEST_F(DestNewNamedTest_2290, NullptrDestFieldsAreZeroInitialized_2290) {
    PopplerDest *dest = dest_new_named(nullptr);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
    EXPECT_EQ(dest->page_num, 0);
    EXPECT_EQ(dest->named_dest, nullptr);
    EXPECT_EQ(dest->change_left, 0);
    EXPECT_EQ(dest->change_top, 0);
    EXPECT_EQ(dest->change_zoom, 0);
    g_slice_free(PopplerDest, dest);
}

// Test that non-named-dest fields are zero-initialized when a valid string is passed
TEST_F(DestNewNamedTest_2290, ValidStringOtherFieldsZeroInitialized_2290) {
    GooString named_dest("test_dest");
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->page_num, 0);
    EXPECT_EQ(dest->change_left, 0);
    EXPECT_EQ(dest->change_top, 0);
    EXPECT_EQ(dest->change_zoom, 0);
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}

// Test with a single character string
TEST_F(DestNewNamedTest_2290, SingleCharStringReturnsNamedDest_2290) {
    GooString named_dest("X");
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);
    EXPECT_NE(dest->named_dest, nullptr);
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}

// Test with Unicode-like content
TEST_F(DestNewNamedTest_2290, UnicodeContentReturnsNamedDest_2290) {
    GooString named_dest("\xc3\xa9\xc3\xa8\xc3\xaa");  // UTF-8 encoded éèê
    PopplerDest *dest = dest_new_named(&named_dest);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_NAMED);
    EXPECT_NE(dest->named_dest, nullptr);
    g_free(dest->named_dest);
    g_slice_free(PopplerDest, dest);
}
