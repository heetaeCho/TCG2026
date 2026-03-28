#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/glib/poppler-page.cc"

#include "./TestProjects/poppler/poppler/PDFRectangle.h"

#include "./TestProjects/poppler/poppler/Annot.h"



class AnnotQuadrilateralsMock : public AnnotQuadrilaterals {

public:

    MOCK_METHOD(int, getQuadrilateralsLength, (), (const));

    MOCK_METHOD(double, getX1, (int), (const));

    MOCK_METHOD(double, getY1, (int), (const));

    MOCK_METHOD(double, getX2, (int), (const));

    MOCK_METHOD(double, getY2, (int), (const));

    MOCK_METHOD(double, getX3, (int), (const));

    MOCK_METHOD(double, getY3, (int), (const));

    MOCK_METHOD(double, getX4, (int), (const));

    MOCK_METHOD(double, getY4, (int), (const));



    AnnotQuadrilateralsMock(int length) : quadrilateralsLength(length) {}



private:

    int quadrilateralsLength;

};



TEST(new_quads_from_offset_cropbox_Test_2456, NormalOperation_Add_2456) {

    PDFRectangle crop_box(1.0, 1.0, 2.0, 2.0);

    AnnotQuadrilateralsMock mock_quads(1);



    EXPECT_CALL(mock_quads, getQuadrilateralsLength()).WillOnce(testing::Return(1));

    EXPECT_CALL(mock_quads, getX1(0)).WillOnce(testing::Return(1.0));

    EXPECT_CALL(mock_quads, getY1(0)).WillOnce(testing::Return(2.0));

    EXPECT_CALL(mock_quads, getX2(0)).WillOnce(testing::Return(3.0));

    EXPECT_CALL(mock_quads, getY2(0)).WillOnce(testing::Return(4.0));

    EXPECT_CALL(mock_quads, getX3(0)).WillOnce(testing::Return(5.0));

    EXPECT_CALL(mock_quads, getY3(0)).WillOnce(testing::Return(6.0));

    EXPECT_CALL(mock_quads, getX4(0)).WillOnce(testing::Return(7.0));

    EXPECT_CALL(mock_quads, getY4(0)).WillOnce(testing::Return(8.0));



    AnnotQuadrilaterals* result = new_quads_from_offset_cropbox(&crop_box, &mock_quads, TRUE);



    ASSERT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), 2.0);

    EXPECT_DOUBLE_EQ(result->getY1(0), 3.0);

    EXPECT_DOUBLE_EQ(result->getX2(0), 4.0);

    EXPECT_DOUBLE_EQ(result->getY2(0), 5.0);

    EXPECT_DOUBLE_EQ(result->getX3(0), 6.0);

    EXPECT_DOUBLE_EQ(result->getY3(0), 7.0);

    EXPECT_DOUBLE_EQ(result->getX4(0), 8.0);

    EXPECT_DOUBLE_EQ(result->getY4(0), 9.0);



    delete result;

}



TEST(new_quads_from_offset_cropbox_Test_2456, NormalOperation_Subtract_2456) {

    PDFRectangle crop_box(1.0, 1.0, 2.0, 2.0);

    AnnotQuadrilateralsMock mock_quads(1);



    EXPECT_CALL(mock_quads, getQuadrilateralsLength()).WillOnce(testing::Return(1));

    EXPECT_CALL(mock_quads, getX1(0)).WillOnce(testing::Return(3.0));

    EXPECT_CALL(mock_quads, getY1(0)).WillOnce(testing::Return(4.0));

    EXPECT_CALL(mock_quads, getX2(0)).WillOnce(testing::Return(5.0));

    EXPECT_CALL(mock_quads, getY2(0)).WillOnce(testing::Return(6.0));

    EXPECT_CALL(mock_quads, getX3(0)).WillOnce(testing::Return(7.0));

    EXPECT_CALL(mock_quads, getY3(0)).WillOnce(testing::Return(8.0));

    EXPECT_CALL(mock_quads, getX4(0)).WillOnce(testing::Return(9.0));

    EXPECT_CALL(mock_quads, getY4(0)).WillOnce(testing::Return(10.0));



    AnnotQuadrilaterals* result = new_quads_from_offset_cropbox(&crop_box, &mock_quads, FALSE);



    ASSERT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), 2.0);

    EXPECT_DOUBLE_EQ(result->getY1(0), 3.0);

    EXPECT_DOUBLE_EQ(result->getX2(0), 4.0);

    EXPECT_DOUBLE_EQ(result->getY2(0), 5.0);

    EXPECT_DOUBLE_EQ(result->getX3(0), 6.0);

    EXPECT_DOUBLE_EQ(result->getY3(0), 7.0);

    EXPECT_DOUBLE_EQ(result->getX4(0), 8.0);

    EXPECT_DOUBLE_EQ(result->getY4(0), 9.0);



    delete result;

}



TEST(new_quads_from_offset_cropbox_Test_2456, BoundaryConditions_ZeroQuadrilaterals_2456) {

    PDFRectangle crop_box(1.0, 1.0, 2.0, 2.0);

    AnnotQuadrilateralsMock mock_quads(0);



    EXPECT_CALL(mock_quads, getQuadrilateralsLength()).WillOnce(testing::Return(0));



    AnnotQuadrilaterals* result = new_quads_from_offset_cropbox(&crop_box, &mock_quads, TRUE);



    ASSERT_EQ(result->getQuadrilateralsLength(), 0);



    delete result;

}



TEST(new_quads_from_offset_cropbox_Test_2456, BoundaryConditions_NegativeCoordinates_Add_2456) {

    PDFRectangle crop_box(1.0, 1.0, 2.0, 2.0);

    AnnotQuadrilateralsMock mock_quads(1);



    EXPECT_CALL(mock_quads, getQuadrilateralsLength()).WillOnce(testing::Return(1));

    EXPECT_CALL(mock_quads, getX1(0)).WillOnce(testing::Return(-1.0));

    EXPECT_CALL(mock_quads, getY1(0)).WillOnce(testing::Return(-2.0));

    EXPECT_CALL(mock_quads, getX2(0)).WillOnce(testing::Return(-3.0));

    EXPECT_CALL(mock_quads, getY2(0)).WillOnce(testing::Return(-4.0));

    EXPECT_CALL(mock_quads, getX3(0)).WillOnce(testing::Return(-5.0));

    EXPECT_CALL(mock_quads, getY3(0)).WillOnce(testing::Return(-6.0));

    EXPECT_CALL(mock_quads, getX4(0)).WillOnce(testing::Return(-7.0));

    EXPECT_CALL(mock_quads, getY4(0)).WillOnce(testing::Return(-8.0));



    AnnotQuadrilaterals* result = new_quads_from_offset_cropbox(&crop_box, &mock_quads, TRUE);



    ASSERT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), 0.0);

    EXPECT_DOUBLE_EQ(result->getY1(0), -1.0);

    EXPECT_DOUBLE_EQ(result->getX2(0), -2.0);

    EXPECT_DOUBLE_EQ(result->getY2(0), -3.0);

    EXPECT_DOUBLE_EQ(result->getX3(0), -4.0);

    EXPECT_DOUBLE_EQ(result->getY3(0), -5.0);

    EXPECT_DOUBLE_EQ(result->getX4(0), -6.0);

    EXPECT_DOUBLE_EQ(result->getY4(0), -7.0);



    delete result;

}



TEST(new_quads_from_offset_cropbox_Test_2456, BoundaryConditions_NegativeCoordinates_Subtract_2456) {

    PDFRectangle crop_box(1.0, 1.0, 2.0, 2.0);

    AnnotQuadrilateralsMock mock_quads(1);



    EXPECT_CALL(mock_quads, getQuadrilateralsLength()).WillOnce(testing::Return(1));

    EXPECT_CALL(mock_quads, getX1(0)).WillOnce(testing::Return(-1.0));

    EXPECT_CALL(mock_quads, getY1(0)).WillOnce(testing::Return(-2.0));

    EXPECT_CALL(mock_quads, getX2(0)).WillOnce(testing::Return(-3.0));

    EXPECT_CALL(mock_quads, getY2(0)).WillOnce(testing::Return(-4.0));

    EXPECT_CALL(mock_quads, getX3(0)).WillOnce(testing::Return(-5.0));

    EXPECT_CALL(mock_quads, getY3(0)).WillOnce(testing::Return(-6.0));

    EXPECT_CALL(mock_quads, getX4(0)).WillOnce(testing::Return(-7.0));

    EXPECT_CALL(mock_quads, getY4(0)).WillOnce(testing::Return(-8.0));



    AnnotQuadrilaterals* result = new_quads_from_offset_cropbox(&crop_box, &mock_quads, FALSE);



    ASSERT_EQ(result->getQuadrilateralsLength(), 1);

    EXPECT_DOUBLE_EQ(result->getX1(0), -2.0);

    EXPECT_DOUBLE_EQ(result->getY1(0), -3.0);

    EXPECT_DOUBLE_EQ(result->getX2(0), -4.0);

    EXPECT_DOUBLE_EQ(result->getY2(0), -5.0);

    EXPECT_DOUBLE_EQ(result->getX3(0), -6.0);

    EXPECT_DOUBLE_EQ(result->getY3(0), -7.0);

    EXPECT_DOUBLE_EQ(result->getX4(0), -8.0);

    EXPECT_DOUBLE_EQ(result->getY4(0), -9.0);



    delete result;

}
