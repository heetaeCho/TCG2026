#include <gtest/gtest.h>
#include <glib.h>

// Include the header for PopplerDest and poppler_dest_free
extern "C" {
#include "poppler-action.h"

// Declaration of the function under test
void poppler_dest_free(PopplerDest *dest);
PopplerDest *poppler_dest_copy(PopplerDest *dest);
}

class PopplerDestFreeTest_2284 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL does not crash
TEST_F(PopplerDestFreeTest_2284, FreeNullDest_2284)
{
    // Should not crash or cause any issues
    poppler_dest_free(nullptr);
    SUCCEED();
}

// Test freeing a PopplerDest with no named_dest (NULL named_dest)
TEST_F(PopplerDestFreeTest_2284, FreeDestWithNullNamedDest_2284)
{
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_XYZ;
    dest->page_num = 1;
    dest->named_dest = nullptr;
    dest->change_left = 0;
    dest->change_top = 0;
    dest->change_zoom = 0;

    // Should free without issues, no crash expected
    poppler_dest_free(dest);
    SUCCEED();
}

// Test freeing a PopplerDest with a valid named_dest
TEST_F(PopplerDestFreeTest_2284, FreeDestWithNamedDest_2284)
{
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_NAMED;
    dest->page_num = 5;
    dest->named_dest = g_strdup("test_destination");
    dest->change_left = 1;
    dest->change_top = 1;
    dest->change_zoom = 0;

    // Should free the named_dest string and the dest struct without issues
    poppler_dest_free(dest);
    SUCCEED();
}

// Test freeing a PopplerDest with an empty named_dest string
TEST_F(PopplerDestFreeTest_2284, FreeDestWithEmptyNamedDest_2284)
{
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_NAMED;
    dest->page_num = 0;
    dest->named_dest = g_strdup("");
    dest->change_left = 0;
    dest->change_top = 0;
    dest->change_zoom = 0;

    poppler_dest_free(dest);
    SUCCEED();
}

// Test freeing a PopplerDest with various dest types
TEST_F(PopplerDestFreeTest_2284, FreeDestWithDifferentTypes_2284)
{
    // Test with POPPLER_DEST_FIT type
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_FIT;
    dest->page_num = 10;
    dest->named_dest = nullptr;

    poppler_dest_free(dest);
    SUCCEED();
}

// Test poppler_dest_copy with a valid dest that has named_dest
TEST_F(PopplerDestFreeTest_2284, CopyDestWithNamedDest_2284)
{
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_NAMED;
    dest->page_num = 3;
    dest->named_dest = g_strdup("chapter1");
    dest->change_left = 1;
    dest->change_top = 0;
    dest->change_zoom = 1;

    PopplerDest *copy = poppler_dest_copy(dest);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, dest->type);
    EXPECT_EQ(copy->page_num, dest->page_num);
    EXPECT_STREQ(copy->named_dest, dest->named_dest);
    EXPECT_EQ(copy->change_left, dest->change_left);
    EXPECT_EQ(copy->change_top, dest->change_top);
    EXPECT_EQ(copy->change_zoom, dest->change_zoom);

    // The copy should have its own named_dest string
    EXPECT_NE(copy->named_dest, dest->named_dest);

    poppler_dest_free(dest);
    poppler_dest_free(copy);
}

// Test poppler_dest_copy with a dest that has no named_dest
TEST_F(PopplerDestFreeTest_2284, CopyDestWithoutNamedDest_2284)
{
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_XYZ;
    dest->page_num = 7;
    dest->named_dest = nullptr;
    dest->change_left = 1;
    dest->change_top = 1;
    dest->change_zoom = 1;

    PopplerDest *copy = poppler_dest_copy(dest);
    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, dest->type);
    EXPECT_EQ(copy->page_num, dest->page_num);
    EXPECT_EQ(copy->named_dest, nullptr);
    EXPECT_EQ(copy->change_left, dest->change_left);
    EXPECT_EQ(copy->change_top, dest->change_top);
    EXPECT_EQ(copy->change_zoom, dest->change_zoom);

    poppler_dest_free(dest);
    poppler_dest_free(copy);
}

// Test freeing a PopplerDest with boundary page_num values
TEST_F(PopplerDestFreeTest_2284, FreeDestWithBoundaryPageNum_2284)
{
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_FIT;
    dest->page_num = 0;
    dest->named_dest = nullptr;

    poppler_dest_free(dest);
    SUCCEED();
}

// Test freeing a dest with a long named_dest string
TEST_F(PopplerDestFreeTest_2284, FreeDestWithLongNamedDest_2284)
{
    PopplerDest *dest = g_slice_new0(PopplerDest);
    dest->type = POPPLER_DEST_NAMED;
    dest->page_num = 1;

    // Create a long string
    gchar *long_str = g_strnfill(10000, 'a');
    dest->named_dest = long_str;

    poppler_dest_free(dest);
    SUCCEED();
}
