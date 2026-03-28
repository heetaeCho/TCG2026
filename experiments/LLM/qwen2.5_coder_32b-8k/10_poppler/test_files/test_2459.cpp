#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Page.h"

#include "poppler/Annot.h"



using namespace testing;



class AnnotQuadrilateralsMock : public AnnotQuadrilaterals {

public:

    MOCK_METHOD(int, getQuadrilateralsLength, (), (const, override));

    MOCK_METHOD(double, getX1, (int), (const, override));

    MOCK_METHOD(double, getY1, (int), (const, override));

    MOCK_METHOD(double, getX2, (int), (const, override));

    MOCK_METHOD(double, getY2, (int), (const, override));

    MOCK_METHOD(double, getX3, (int), (const, override));

    MOCK_METHOD(double, getY3, (int), (const, override));

    MOCK_METHOD(double, getX4, (int), (const, override));

    MOCK_METHOD(double, getY4, (int), (const, override));



    AnnotQuadrilateralsMock() : AnnotQuadrilaterals(0) {}

};



class PageMock : public Page {

public:

    MOCK_METHOD(void, _page_unrotate_xy, (double*, double*), ());

    PageMock(PDFDoc * docA, int numA, Object && pageDict, Ref pageRefA, std::unique_ptr<PageAttrs> attrsA)

        : Page(docA, numA, std::move(pageDict), pageRefA, std::move(attrsA)) {}

};



TEST_F(AnnotQuadrilateralsTest_2459, SingleQuadrilateral_NormalOperation_2459) {

    AnnotQuadrilateralsMock mockQuads;

    PageMock mockPage(nullptr, 1, Object(), Ref(), nullptr);



    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(Return(1));

    EXPECT_CALL(mockQuads, getX1(0)).WillOnce(Return(1.0));

    EXPECT_CALL(mockQuads, getY1(0)).WillOnce(Return(2.0));

    EXPECT_CALL(mockQuads, getX2(0)).WillOnce(Return(3.0));

    EXPECT_CALL(mockQuads, getY2(0)).WillOnce(Return(4.0));

    EXPECT_CALL(mockQuads, getX3(0)).WillOnce(Return(5.0));

    EXPECT_CALL(mockQuads, getY3(0)).WillOnce(Return(6.0));

    EXPECT_CALL(mockQuads, getX4(0)).WillOnce(Return(7.0));

    EXPECT_CALL(mockQuads, getY4(0)).WillOnce(Return(8.0));



    double x1 = 1.0, y1 = 2.0;

    double x2 = 3.0, y2 = 4.0;

    double x3 = 5.0, y3 = 6.0;

    double x4 = 7.0, y4 = 8.0;



    EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x1), Pointee(y1)));

    EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x2), Pointee(y2)));

    EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x3), Pointee(y3)));

    EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x4), Pointee(y4)));



    AnnotQuadrilaterals* result = _page_new_quads_unrotated(&mockPage, &mockQuads);

    ASSERT_NE(result, nullptr);



    delete result;

}



TEST_F(AnnotQuadrilateralsTest_2459, ZeroQuadrilaterals_BoundaryCondition_2459) {

    AnnotQuadrilateralsMock mockQuads;

    PageMock mockPage(nullptr, 1, Object(), Ref(), nullptr);



    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(Return(0));



    AnnotQuadrilaterals* result = _page_new_quads_unrotated(&mockPage, &mockQuads);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->getQuadrilateralsLength(), 0);



    delete result;

}



TEST_F(AnnotQuadrilateralsTest_2459, MultipleQuadrilaterals_NormalOperation_2459) {

    AnnotQuadrilateralsMock mockQuads;

    PageMock mockPage(nullptr, 1, Object(), Ref(), nullptr);



    EXPECT_CALL(mockQuads, getQuadrilateralsLength()).WillOnce(Return(3));



    for (int i = 0; i < 3; ++i) {

        EXPECT_CALL(mockQuads, getX1(i)).WillOnce(Return(1.0 + i));

        EXPECT_CALL(mockQuads, getY1(i)).WillOnce(Return(2.0 + i));

        EXPECT_CALL(mockQuads, getX2(i)).WillOnce(Return(3.0 + i));

        EXPECT_CALL(mockQuads, getY2(i)).WillOnce(Return(4.0 + i));

        EXPECT_CALL(mockQuads, getX3(i)).WillOnce(Return(5.0 + i));

        EXPECT_CALL(mockQuads, getY3(i)).WillOnce(Return(6.0 + i));

        EXPECT_CALL(mockQuads, getX4(i)).WillOnce(Return(7.0 + i));

        EXPECT_CALL(mockQuads, getY4(i)).WillOnce(Return(8.0 + i));



        double x1 = 1.0 + i, y1 = 2.0 + i;

        double x2 = 3.0 + i, y2 = 4.0 + i;

        double x3 = 5.0 + i, y3 = 6.0 + i;

        double x4 = 7.0 + i, y4 = 8.0 + i;



        EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x1), Pointee(y1)));

        EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x2), Pointee(y2)));

        EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x3), Pointee(y3)));

        EXPECT_CALL(mockPage, _page_unrotate_xy(Pointee(x4), Pointee(y4)));

    }



    AnnotQuadrilaterals* result = _page_new_quads_unrotated(&mockPage, &mockQuads);

    ASSERT_NE(result, nullptr);

    EXPECT_EQ(result->getQuadrilateralsLength(), 3);



    delete result;

}
