#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/Page.h"

#include "./TestProjects/poppler/poppler/PDFRectangle.h"



using namespace testing;



class MockPageAttrs : public PageAttrs {

public:

    MOCK_METHOD(const PDFRectangle*, getCropBox, (), (const, override));

};



class PageTest_708 : public Test {

protected:

    NiceMock<MockPageAttrs> mock_attrs;

    std::unique_ptr<PageAttrs> attrs_ptr = std::make_unique<NiceMock<MockPageAttrs>>(mock_attrs);

    Page page(nullptr, 0, Object(), Ref(), std::move(attrs_ptr));

};



TEST_F(PageTest_708, GetCropWidth_NormalOperation_708) {

    PDFRectangle mock_rect(1.0, 2.0, 5.0, 6.0);

    EXPECT_CALL(mock_attrs, getCropBox()).WillOnce(Return(&mock_rect));



    double crop_width = page.getCropWidth();

    EXPECT_EQ(crop_width, 4.0); // 5.0 - 1.0

}



TEST_F(PageTest_708, GetCropWidth_BoundaryConditions_708) {

    PDFRectangle mock_rect(0.0, 0.0, 0.0, 0.0);

    EXPECT_CALL(mock_attrs, getCropBox()).WillOnce(Return(&mock_rect));



    double crop_width = page.getCropWidth();

    EXPECT_EQ(crop_width, 0.0); // 0.0 - 0.0

}



TEST_F(PageTest_708, GetCropWidth_ExceptionalCase_708) {

    EXPECT_CALL(mock_attrs, getCropBox()).WillOnce(Return(nullptr));



    double crop_width = page.getCropWidth();

    EXPECT_EQ(crop_width, 0.0); // Assuming gracefully handles nullptr

}
