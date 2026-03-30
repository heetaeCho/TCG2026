#include <gtest/gtest.h>

#include "poppler/Page.h"

#include "poppler/PDFRectangle.h"



// Mock class for PageAttrs to control its behavior during tests.

class MockPageAttrs : public PageAttrs {

public:

    MOCK_CONST_METHOD0(getMediaBox, const PDFRectangle*());

};



// Test fixture for Page class.

class PageTest_706 : public ::testing::Test {

protected:

    void SetUp() override {

        // Set up a default mock media box

        defaultMediaBox = std::make_unique<PDFRectangle>(0.0, 0.0, 100.0, 200.0);

        ON_CALL(*mockPageAttrs, getMediaBox()).WillByDefault(testing::Return(defaultMediaBox.get()));

        

        page = std::make_unique<Page>(nullptr, 1, std::move(Object()), Ref(), std::move(mockPageAttrs));

    }



    std::unique_ptr<MockPageAttrs> mockPageAttrs;

    std::unique_ptr<PDFRectangle> defaultMediaBox;

    std::unique_ptr<Page> page;

};



// Test normal operation of getMediaWidth

TEST_F(PageTest_706, GetMediaWidth_NormalOperation_706) {

    EXPECT_EQ(page->getMediaWidth(), 100.0);

}



// Test boundary condition where media box is empty

TEST_F(PageTest_706, GetMediaWidth_EmptyMediaBox_706) {

    auto emptyBox = std::make_unique<PDFRectangle>(0.0, 0.0, 0.0, 0.0);

    EXPECT_CALL(*mockPageAttrs, getMediaBox()).WillOnce(testing::Return(emptyBox.get()));

    

    EXPECT_EQ(page->getMediaWidth(), 0.0);

}



// Test boundary condition where media box has negative width

TEST_F(PageTest_706, GetMediaWidth_NegativeWidth_706) {

    auto negativeBox = std::make_unique<PDFRectangle>(100.0, 0.0, 50.0, 200.0);

    EXPECT_CALL(*mockPageAttrs, getMediaBox()).WillOnce(testing::Return(negativeBox.get()));

    

    EXPECT_EQ(page->getMediaWidth(), -50.0);

}



// Test normal operation of getMediaHeight

TEST_F(PageTest_706, GetMediaHeight_NormalOperation_706) {

    EXPECT_EQ(page->getMediaHeight(), 200.0);

}



// Test boundary condition where media box is empty

TEST_F(PageTest_706, GetMediaHeight_EmptyMediaBox_706) {

    auto emptyBox = std::make_unique<PDFRectangle>(0.0, 0.0, 0.0, 0.0);

    EXPECT_CALL(*mockPageAttrs, getMediaBox()).WillOnce(testing::Return(emptyBox.get()));

    

    EXPECT_EQ(page->getMediaHeight(), 0.0);

}



// Test boundary condition where media box has negative height

TEST_F(PageTest_706, GetMediaHeight_NegativeHeight_706) {

    auto negativeBox = std::make_unique<PDFRectangle>(0.0, 200.0, 100.0, 50.0);

    EXPECT_CALL(*mockPageAttrs, getMediaBox()).WillOnce(testing::Return(negativeBox.get()));

    

    EXPECT_EQ(page->getMediaHeight(), -150.0);

}



// Test normal operation of isCropped

TEST_F(PageTest_706, IsCropped_NormalOperation_706) {

    ON_CALL(*mockPageAttrs, isCropped()).WillByDefault(testing::Return(false));

    EXPECT_FALSE(page->isCropped());



    ON_CALL(*mockPageAttrs, isCropped()).WillByDefault(testing::Return(true));

    EXPECT_TRUE(page->isCropped());

}



// Test normal operation of getMediaBox

TEST_F(PageTest_706, GetMediaBox_NormalOperation_706) {

    EXPECT_EQ(page->getMediaBox(), defaultMediaBox.get());

}
