#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Page.h"



class PageTest_711 : public ::testing::Test {

protected:

    class MockPageAttrs : public PageAttrs {

    public:

        MOCK_CONST_METHOD0(getTrimBox, const PDFRectangle*());

    };



    std::unique_ptr<MockPageAttrs> mockAttrs;

    Page* page;



    void SetUp() override {

        mockAttrs = std::make_unique<MockPageAttrs>();

        page = new Page(nullptr, 1, Object(), Ref(), std::move(mockAttrs));

    }



    void TearDown() override {

        delete page;

    }

};



TEST_F(PageTest_711, GetTrimBox_ReturnsExpectedValue_711) {

    const PDFRectangle expectedRect = {0, 0, 612, 792};

    EXPECT_CALL(*mockAttrs, getTrimBox()).WillOnce(::testing::Return(&expectedRect));



    const PDFRectangle* result = page->getTrimBox();

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->x1, expectedRect.x1);

    EXPECT_EQ(result->y1, expectedRect.y1);

    EXPECT_EQ(result->x2, expectedRect.x2);

    EXPECT_EQ(result->y2, expectedRect.y2);

}



TEST_F(PageTest_711, GetTrimBox_ReturnsNullPtr_711) {

    EXPECT_CALL(*mockAttrs, getTrimBox()).WillOnce(::testing::Return(nullptr));



    const PDFRectangle* result = page->getTrimBox();

    EXPECT_EQ(result, nullptr);

}
