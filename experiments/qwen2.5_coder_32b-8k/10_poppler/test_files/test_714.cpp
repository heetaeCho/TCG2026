#include <gtest/gtest.h>

#include "poppler/Page.h"

#include "poppler/GooString.h"



class PageTest_714 : public ::testing::Test {

protected:

    std::unique_ptr<PageAttrs> attrs;

    Page* page;



    virtual void SetUp() {

        attrs = std::make_unique<PageAttrs>(nullptr, nullptr);

        page = new Page(nullptr, 1, Object(), Ref(), std::move(attrs));

    }



    virtual void TearDown() {

        delete page;

    }

};



TEST_F(PageTest_714, GetLastModified_ReturnsNullPointerWhenNotSet_714) {

    EXPECT_EQ(page->getLastModified(), nullptr);

}



TEST_F(PageTest_714, GetMediaBox_ReturnsValidPointer_714) {

    EXPECT_NE(page->getMediaBox(), nullptr);

}



TEST_F(PageTest_714, GetCropBox_ReturnsValidPointer_714) {

    EXPECT_NE(page->getCropBox(), nullptr);

}



TEST_F(PageTest_714, IsCropped_ReturnsFalseWhenNotSet_714) {

    EXPECT_FALSE(page->isCropped());

}



TEST_F(PageTest_714, GetBleedBox_ReturnsValidPointer_714) {

    EXPECT_NE(page->getBleedBox(), nullptr);

}



TEST_F(PageTest_714, GetTrimBox_ReturnsValidPointer_714) {

    EXPECT_NE(page->getTrimBox(), nullptr);

}



TEST_F(PageTest_714, GetArtBox_ReturnsValidPointer_714) {

    EXPECT_NE(page->getArtBox(), nullptr);

}



TEST_F(PageTest_714, GetRotate_ReturnsZeroWhenNotSet_714) {

    EXPECT_EQ(page->getRotate(), 0);

}



TEST_F(PageTest_714, IsOk_ReturnsTrue_714) {

    EXPECT_TRUE(page->isOk());

}



TEST_F(PageTest_714, GetNum_ReturnsCorrectNumber_714) {

    EXPECT_EQ(page->getNum(), 1);

}



TEST_F(PageTest_714, GetMediaWidth_ReturnsPositiveValue_714) {

    EXPECT_GT(page->getMediaWidth(), 0.0);

}



TEST_F(PageTest_714, GetMediaHeight_ReturnsPositiveValue_714) {

    EXPECT_GT(page->getMediaHeight(), 0.0);

}



TEST_F(PageTest_714, GetCropWidth_ReturnsPositiveOrZeroValue_714) {

    EXPECT_GE(page->getCropWidth(), 0.0);

}



TEST_F(PageTest_714, GetCropHeight_ReturnsPositiveOrZeroValue_714) {

    EXPECT_GE(page->getCropHeight(), 0.0);

}
