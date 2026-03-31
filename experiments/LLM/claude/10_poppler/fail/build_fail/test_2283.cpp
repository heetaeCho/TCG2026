#include <gtest/gtest.h>
#include <glib.h>

// Include the header for PopplerDest and poppler_dest_copy
extern "C" {
#include "poppler-action.h"
}

// Forward declare the function under test
extern "C" PopplerDest *poppler_dest_copy(PopplerDest *dest);

class PopplerDestCopyTest_2283 : public ::testing::Test {
protected:
    void TearDown() override {
        // Cleanup handled in individual tests
    }
};

TEST_F(PopplerDestCopyTest_2283, CopyBasicDest_NoNamedDest_2283) {
    PopplerDest dest;
    memset(&dest, 0, sizeof(PopplerDest));
    dest.type = POPPLER_DEST_XYZ;
    dest.page_num = 5;
    dest.named_dest = nullptr;
    dest.change_left = 100;
    dest.change_top = 200;
    dest.change_zoom = 150;

    PopplerDest *copy = poppler_dest_copy(&dest);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_DEST_XYZ);
    EXPECT_EQ(copy->page_num, 5);
    EXPECT_EQ(copy->named_dest, nullptr);
    EXPECT_EQ(copy->change_left, 100);
    EXPECT_EQ(copy->change_top, 200);
    EXPECT_EQ(copy->change_zoom, 150);

    // The copy should be a different pointer
    EXPECT_NE(copy, &dest);

    g_slice_free(PopplerDest, copy);
}

TEST_F(PopplerDestCopyTest_2283, CopyDestWithNamedDest_2283) {
    PopplerDest dest;
    memset(&dest, 0, sizeof(PopplerDest));
    dest.type = POPPLER_DEST_NAMED;
    dest.page_num = 10;
    dest.named_dest = g_strdup("chapter1");
    dest.change_left = 0;
    dest.change_top = 1;
    dest.change_zoom = 0;

    PopplerDest *copy = poppler_dest_copy(&dest);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, POPPLER_DEST_NAMED);
    EXPECT_EQ(copy->page_num, 10);
    ASSERT_NE(copy->named_dest, nullptr);
    // The named_dest should be a deep copy (different pointer, same content)
    EXPECT_NE(copy->named_dest, dest.named_dest);
    EXPECT_STREQ(copy->named_dest, "chapter1");
    EXPECT_EQ(copy->change_left, 0);
    EXPECT_EQ(copy->change_top, 1);
    EXPECT_EQ(copy->change_zoom, 0);

    g_free(dest.named_dest);
    g_free(copy->named_dest);
    g_slice_free(PopplerDest, copy);
}

TEST_F(PopplerDestCopyTest_2283, CopyDestWithEmptyNamedDest_2283) {
    PopplerDest dest;
    memset(&dest, 0, sizeof(PopplerDest));
    dest.type = POPPLER_DEST_NAMED;
    dest.page_num = 0;
    dest.named_dest = g_strdup("");
    dest.change_left = 0;
    dest.change_top = 0;
    dest.change_zoom = 0;

    PopplerDest *copy = poppler_dest_copy(&dest);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->named_dest, nullptr);
    EXPECT_STREQ(copy->named_dest, "");
    EXPECT_NE(copy->named_dest, dest.named_dest);

    g_free(dest.named_dest);
    g_free(copy->named_dest);
    g_slice_free(PopplerDest, copy);
}

TEST_F(PopplerDestCopyTest_2283, CopyPreservesAllFields_2283) {
    PopplerDest dest;
    memset(&dest, 0, sizeof(PopplerDest));
    dest.type = POPPLER_DEST_FIT;
    dest.page_num = 999;
    dest.named_dest = nullptr;
    dest.change_left = -50;
    dest.change_top = -100;
    dest.change_zoom = 300;

    PopplerDest *copy = poppler_dest_copy(&dest);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->type, dest.type);
    EXPECT_EQ(copy->page_num, dest.page_num);
    EXPECT_EQ(copy->named_dest, dest.named_dest);
    EXPECT_EQ(copy->change_left, dest.change_left);
    EXPECT_EQ(copy->change_top, dest.change_top);
    EXPECT_EQ(copy->change_zoom, dest.change_zoom);

    g_slice_free(PopplerDest, copy);
}

TEST_F(PopplerDestCopyTest_2283, CopyDestWithLongNamedDest_2283) {
    PopplerDest dest;
    memset(&dest, 0, sizeof(PopplerDest));
    dest.type = POPPLER_DEST_NAMED;
    dest.page_num = 1;

    // Create a long named destination string
    std::string long_name(1024, 'a');
    dest.named_dest = g_strdup(long_name.c_str());
    dest.change_left = 1;
    dest.change_top = 1;
    dest.change_zoom = 1;

    PopplerDest *copy = poppler_dest_copy(&dest);

    ASSERT_NE(copy, nullptr);
    ASSERT_NE(copy->named_dest, nullptr);
    EXPECT_NE(copy->named_dest, dest.named_dest);
    EXPECT_STREQ(copy->named_dest, long_name.c_str());

    g_free(dest.named_dest);
    g_free(copy->named_dest);
    g_slice_free(PopplerDest, copy);
}

TEST_F(PopplerDestCopyTest_2283, CopyIsIndependent_2283) {
    PopplerDest dest;
    memset(&dest, 0, sizeof(PopplerDest));
    dest.type = POPPLER_DEST_XYZ;
    dest.page_num = 42;
    dest.named_dest = g_strdup("test_dest");
    dest.change_left = 10;
    dest.change_top = 20;
    dest.change_zoom = 30;

    PopplerDest *copy = poppler_dest_copy(&dest);

    // Modify the original after copying
    g_free(dest.named_dest);
    dest.named_dest = g_strdup("modified");
    dest.page_num = 99;

    // The copy should retain original values
    EXPECT_EQ(copy->page_num, 42);
    EXPECT_STREQ(copy->named_dest, "test_dest");

    g_free(dest.named_dest);
    g_free(copy->named_dest);
    g_slice_free(PopplerDest, copy);
}

TEST_F(PopplerDestCopyTest_2283, CopyDestPageNumZero_2283) {
    PopplerDest dest;
    memset(&dest, 0, sizeof(PopplerDest));
    dest.type = POPPLER_DEST_FIT;
    dest.page_num = 0;
    dest.named_dest = nullptr;
    dest.change_left = 0;
    dest.change_top = 0;
    dest.change_zoom = 0;

    PopplerDest *copy = poppler_dest_copy(&dest);

    ASSERT_NE(copy, nullptr);
    EXPECT_EQ(copy->page_num, 0);
    EXPECT_EQ(copy->named_dest, nullptr);

    g_slice_free(PopplerDest, copy);
}
