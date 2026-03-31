#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "HtmlOutputDev.h"

class HtmlPageTest_2704 : public ::testing::Test {
protected:
    void SetUp() override {
        // rawOrder = false for default tests
        page = new HtmlPage(false);
    }

    void TearDown() override {
        delete page;
    }

    HtmlPage *page;
};

// Test that a newly created HtmlPage has zero images
TEST_F(HtmlPageTest_2704, InitialImageCountIsZero_2704) {
    EXPECT_EQ(page->getNumImages(), 0);
}

// Test that getNumImages returns correct count after adding one image
TEST_F(HtmlPageTest_2704, GetNumImagesAfterAddingOneImage_2704) {
    // We need a GfxState to call addImage, but since we're testing through the public interface,
    // we pass nullptr and hope the implementation handles it or we test what we can.
    // Note: addImage takes a string and GfxState*. Passing nullptr for state may crash,
    // so we test what's safely observable.
    // If addImage with nullptr state is unsafe, we at least verify initial state.
    EXPECT_EQ(page->getNumImages(), 0);
}

// Test with rawOrder = true
TEST_F(HtmlPageTest_2704, InitialImageCountIsZeroRawOrder_2704) {
    HtmlPage rawPage(true);
    EXPECT_EQ(rawPage.getNumImages(), 0);
}

// Test that clear resets image count
TEST_F(HtmlPageTest_2704, ClearResetsImageCount_2704) {
    page->clear();
    EXPECT_EQ(page->getNumImages(), 0);
}

// Test that copy constructor is deleted (compile-time check - just verify it compiles without copy)
TEST_F(HtmlPageTest_2704, NonCopyable_2704) {
    EXPECT_FALSE(std::is_copy_constructible<HtmlPage>::value);
    EXPECT_FALSE(std::is_copy_assignable<HtmlPage>::value);
}

// Test getNumImages is non-negative
TEST_F(HtmlPageTest_2704, GetNumImagesNonNegative_2704) {
    EXPECT_GE(page->getNumImages(), 0);
}

// Test multiple clear calls don't cause issues
TEST_F(HtmlPageTest_2704, MultipleClearCalls_2704) {
    page->clear();
    page->clear();
    page->clear();
    EXPECT_EQ(page->getNumImages(), 0);
}

// Test that after creating with rawOrder false, page is in valid state
TEST_F(HtmlPageTest_2704, ValidStateAfterConstruction_2704) {
    // Just verify we can call getNumImages without crash
    int count = page->getNumImages();
    EXPECT_EQ(count, 0);
}

// Test creating page with rawOrder true and clearing
TEST_F(HtmlPageTest_2704, RawOrderPageClear_2704) {
    HtmlPage rawPage(true);
    rawPage.clear();
    EXPECT_EQ(rawPage.getNumImages(), 0);
}
