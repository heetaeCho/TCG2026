#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-page-private.h"
#include "poppler-page.h"

namespace poppler {

class PagePrivateTest_1032 : public ::testing::Test {
protected:
    // You can set up any necessary objects for testing
    page_private *privatePage;
    document_private *doc;

    // Setup before each test
    void SetUp() override {
        // Mock or create real instances of `document_private` and `page_private`
        doc = new document_private(); // Assuming document_private constructor is accessible
        privatePage = new page_private(doc, 0);  // Assuming 0 is a valid index for testing
    }

    // Cleanup after each test
    void TearDown() override {
        delete privatePage;
        delete doc;
    }
};

// Normal operation test for page_private::get
TEST_F(PagePrivateTest_1032, GetPagePrivate_1032) {
    poppler::page testPage(doc, 0);
    
    // Get page_private instance from the page object
    page_private* retrievedPrivate = page_private::get(&testPage);
    
    // Test that we get a valid pointer
    ASSERT_NE(retrievedPrivate, nullptr);
    EXPECT_EQ(retrievedPrivate, privatePage); // Assuming the page_private object matches the one in test
}

// Boundary test for page_private constructor
TEST_F(PagePrivateTest_1032, PagePrivateConstructor_1032) {
    EXPECT_NO_THROW({
        page_private testPrivate(doc, 0);
    });
}

// Exceptional case test for invalid `get` with null page
TEST_F(PagePrivateTest_1032, GetPagePrivateNull_1032) {
    poppler::page* nullPage = nullptr;
    
    // Test that the `get` function handles a null page gracefully
    EXPECT_THROW({
        page_private* retrievedPrivate = page_private::get(nullPage);
    }, std::invalid_argument);  // Or an appropriate exception type if the code throws one
}

// Test for the init_font_info_cache method (boundary and normal case)
TEST_F(PagePrivateTest_1032, InitFontInfoCache_1032) {
    EXPECT_FALSE(privatePage->font_info_cache_initialized);

    privatePage->init_font_info_cache();

    EXPECT_TRUE(privatePage->font_info_cache_initialized);
}

}  // namespace poppler