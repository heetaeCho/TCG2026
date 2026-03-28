#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler-annotation-private.h>

#include <QPointF>

#include <QLinkedList>



using namespace Poppler;

using testing::ElementsAre;



class AnnotationPrivateTest_1389 : public ::testing::Test {

protected:

    std::unique_ptr<AnnotationPrivate> annotationPrivate;



    AnnotationPrivateTest_1389() : annotationPrivate(std::make_unique<AnnotationPrivate>()) {}

};



TEST_F(AnnotationPrivateTest_1389, ToAnnotPath_EmptyList_ReturnsEmptyPath_1389) {

    QLinkedList<QPointF> emptyList;

    auto path = annotationPrivate->toAnnotPath(emptyList);

    EXPECT_TRUE(path->coords.empty());

}



TEST_F(AnnotationPrivateTest_1389, ToAnnotPath_SinglePoint_ConvertsCorrectly_1389) {

    double MTX[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0}; // Identity transformation matrix

    QPointF point(10.0, 20.0);

    QLinkedList<QPointF> list;

    list.append(point);



    auto path = annotationPrivate->toAnnotPath(list);

    EXPECT_EQ(path->coords.size(), 1);

    EXPECT_DOUBLE_EQ(path->coords[0].x, 10.0);

    EXPECT_DOUBLE_EQ(path->coords[0].y, 20.0);

}



TEST_F(AnnotationPrivateTest_1389, ToAnnotPath_MultiplePoints_ConvertsCorrectly_1389) {

    double MTX[6] = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0}; // Identity transformation matrix

    QPointF point1(10.0, 20.0);

    QPointF point2(30.0, 40.0);

    QLinkedList<QPointF> list;

    list.append(point1);

    list.append(point2);



    auto path = annotationPrivate->toAnnotPath(list);

    EXPECT_EQ(path->coords.size(), 2);

    EXPECT_DOUBLE_EQ(path->coords[0].x, 10.0);

    EXPECT_DOUBLE_EQ(path->coords[0].y, 20.0);

    EXPECT_DOUBLE_EQ(path->coords[1].x, 30.0);

    EXPECT_DOUBLE_EQ(path->coords[1].y, 40.0);

}
