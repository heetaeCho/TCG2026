#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>

// Include necessary headers from poppler
#include "TextOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class TextSelectionSizerTest_1905 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that calling takeRegion() a second time returns nullptr,
// since the first call transfers ownership and nullifies the internal list.
TEST_F(TextSelectionSizerTest_1905, TakeRegionSecondCallReturnsNullptr_1905) {
    // Create a TextPage to pass to the sizer
    TextPage *page = new TextPage(false);
    double scale = 1.0;

    TextSelectionSizer sizer(page, scale);

    // First call to takeRegion - may or may not be nullptr depending on
    // whether the constructor initializes the list
    std::vector<PDFRectangle *> *firstResult = sizer.takeRegion();

    // Second call should always return nullptr since takeRegion sets list = nullptr
    std::vector<PDFRectangle *> *secondResult = sizer.takeRegion();
    EXPECT_EQ(secondResult, nullptr);

    // Clean up first result if it was allocated
    if (firstResult) {
        for (auto *rect : *firstResult) {
            delete rect;
        }
        delete firstResult;
    }

    page->decRefCnt();
}

// Test that takeRegion returns a non-null result after construction
// (the constructor should initialize the internal list)
TEST_F(TextSelectionSizerTest_1905, TakeRegionReturnsListAfterConstruction_1905) {
    TextPage *page = new TextPage(false);
    double scale = 1.0;

    TextSelectionSizer sizer(page, scale);

    std::vector<PDFRectangle *> *result = sizer.takeRegion();
    // The constructor likely allocates the list
    EXPECT_NE(result, nullptr);

    if (result) {
        for (auto *rect : *result) {
            delete rect;
        }
        delete result;
    }

    page->decRefCnt();
}

// Test with different scale values
TEST_F(TextSelectionSizerTest_1905, ConstructWithDifferentScales_1905) {
    TextPage *page = new TextPage(false);

    // Test with scale = 0.0
    {
        TextSelectionSizer sizer(page, 0.0);
        std::vector<PDFRectangle *> *result = sizer.takeRegion();
        // Should still return a valid (possibly empty) list
        if (result) {
            EXPECT_TRUE(result->empty());
            delete result;
        }
    }

    // Test with scale = 2.0
    {
        TextSelectionSizer sizer(page, 2.0);
        std::vector<PDFRectangle *> *result = sizer.takeRegion();
        if (result) {
            EXPECT_TRUE(result->empty());
            delete result;
        }
    }

    // Test with negative scale
    {
        TextSelectionSizer sizer(page, -1.0);
        std::vector<PDFRectangle *> *result = sizer.takeRegion();
        if (result) {
            for (auto *rect : *result) {
                delete rect;
            }
            delete result;
        }
    }

    page->decRefCnt();
}

// Test that the initial list from takeRegion is empty when no visits have occurred
TEST_F(TextSelectionSizerTest_1905, InitialListIsEmpty_1905) {
    TextPage *page = new TextPage(false);
    double scale = 1.0;

    TextSelectionSizer sizer(page, scale);

    std::vector<PDFRectangle *> *result = sizer.takeRegion();
    if (result != nullptr) {
        EXPECT_EQ(result->size(), 0u);
        delete result;
    }

    page->decRefCnt();
}

// Test multiple consecutive takeRegion calls all return nullptr after first
TEST_F(TextSelectionSizerTest_1905, MultipleTakeRegionCallsReturnNullptr_1905) {
    TextPage *page = new TextPage(false);
    double scale = 1.0;

    TextSelectionSizer sizer(page, scale);

    std::vector<PDFRectangle *> *first = sizer.takeRegion();
    if (first) {
        delete first;
    }

    for (int i = 0; i < 5; ++i) {
        std::vector<PDFRectangle *> *result = sizer.takeRegion();
        EXPECT_EQ(result, nullptr) << "Call " << i << " should return nullptr";
    }

    page->decRefCnt();
}
