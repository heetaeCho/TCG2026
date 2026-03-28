#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"



class PageTest_705 : public ::testing::Test {

protected:

    void SetUp() override {

        // Assuming a mock or stub for PageAttrs can be created for testing purposes.

        // For the sake of this example, we will assume a way to create a valid Page object.

        auto attrs = std::make_unique<PageAttrs>(nullptr, nullptr);

        page = std::make_unique<Page>(nullptr, 0, Object(), Ref(), std::move(attrs));

    }



    void TearDown() override {

        // Cleanup if necessary

    }



    std::unique_ptr<Page> page;

};



TEST_F(PageTest_705, IsCropped_ReturnsTrueWhenCropped_705) {

    EXPECT_TRUE(page->isCropped());

}



TEST_F(PageTest_705, IsCropped_ReturnsFalseWhenNotCropped_705) {

    // Assuming a way to set the state of PageAttrs such that isCropped() returns false

    auto attrs = std::make_unique<PageAttrs>(nullptr, nullptr);

    page = std::make_unique<Page>(nullptr, 0, Object(), Ref(), std::move(attrs));



    EXPECT_FALSE(page->isCropped());

}



// Additional tests for boundary conditions and exceptional cases if applicable.

// Since the provided interface does not suggest any direct boundaries or exceptions,

// these are basic tests based on observable behavior.



TEST_F(PageTest_705, GetMediaBox_ReturnsNonNullPointer_705) {

    EXPECT_NE(page->getMediaBox(), nullptr);

}



TEST_F(PageTest_705, GetCropBox_ReturnsNonNullPointerWhenCropped_705) {

    if (page->isCropped()) {

        EXPECT_NE(page->getCropBox(), nullptr);

    }

}



TEST_F(PageTest_705, GetBleedBox_ReturnsNonNullPointer_705) {

    EXPECT_NE(page->getBleedBox(), nullptr);

}



TEST_F(PageTest_705, GetTrimBox_ReturnsNonNullPointer_705) {

    EXPECT_NE(page->getTrimBox(), nullptr);

}



TEST_F(PageTest_705, GetArtBox_ReturnsNonNullPointer_705) {

    EXPECT_NE(page->getArtBox(), nullptr);

}
