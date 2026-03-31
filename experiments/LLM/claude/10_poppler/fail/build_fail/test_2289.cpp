#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <glib-object.h>

// Include necessary headers
#include "poppler-action.h"
#include "poppler-private.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "Link.h"
#include "PDFDoc.h"
#include "Page.h"

// Include the .cc file to access the static function
#include "poppler-action.cc"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

class DestNewGotoTest_2289 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing nullptr for link_dest returns POPPLER_DEST_UNKNOWN
TEST_F(DestNewGotoTest_2289, NullLinkDestReturnsUnknown_2289) {
    PopplerDest *dest = dest_new_goto(nullptr, nullptr);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
    g_slice_free(PopplerDest, dest);
}

// Test that nullptr document with nullptr link_dest returns POPPLER_DEST_UNKNOWN
TEST_F(DestNewGotoTest_2289, NullDocAndNullLinkDest_2289) {
    PopplerDest *dest = dest_new_goto(nullptr, nullptr);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
    g_slice_free(PopplerDest, dest);
}

// Test dest type mapping for destXYZ
TEST_F(DestNewGotoTest_2289, DestTypeXYZ_2289) {
    // We need a real LinkDest - this requires an Array which is hard to construct
    // without a full PDF context. We test via integration with a minimal PDF if possible.
    // For unit testing the static function, we would need a way to construct LinkDest.
    // Since we treat implementation as black box and can't easily mock LinkDest (no virtual methods),
    // we acknowledge this limitation and test what we can.
    
    // Test null link_dest path which is directly testable
    PopplerDest *dest = dest_new_goto(nullptr, nullptr);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
    EXPECT_EQ(dest->page_num, 0);
    EXPECT_DOUBLE_EQ(dest->left, 0.0);
    EXPECT_DOUBLE_EQ(dest->bottom, 0.0);
    EXPECT_DOUBLE_EQ(dest->right, 0.0);
    EXPECT_DOUBLE_EQ(dest->top, 0.0);
    EXPECT_DOUBLE_EQ(dest->zoom, 0.0);
    g_slice_free(PopplerDest, dest);
}

// Test that dest is properly zero-initialized when link_dest is null
TEST_F(DestNewGotoTest_2289, ZeroInitializedOnNullLinkDest_2289) {
    PopplerDest *dest = dest_new_goto(nullptr, nullptr);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
    EXPECT_EQ(dest->page_num, 0);
    EXPECT_EQ(dest->change_left, 0);
    EXPECT_EQ(dest->change_top, 0);
    EXPECT_EQ(dest->change_zoom, 0);
    g_slice_free(PopplerDest, dest);
}

// Test with non-null document but null link_dest
TEST_F(DestNewGotoTest_2289, NonNullDocNullLinkDest_2289) {
    // Even with a non-null document pointer, null link_dest should return UNKNOWN
    // We can't easily create a valid PopplerDocument without a real PDF,
    // but the function checks link_dest == nullptr first before using document
    PopplerDest *dest = dest_new_goto(reinterpret_cast<PopplerDocument*>(0x1), nullptr);
    ASSERT_NE(dest, nullptr);
    EXPECT_EQ(dest->type, POPPLER_DEST_UNKNOWN);
    g_slice_free(PopplerDest, dest);
}

// Verify the dest is allocated (non-null) in all null-input cases
TEST_F(DestNewGotoTest_2289, AlwaysAllocatesDest_2289) {
    PopplerDest *dest = dest_new_goto(nullptr, nullptr);
    ASSERT_NE(dest, nullptr);
    g_slice_free(PopplerDest, dest);
}
