#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-annotation.h"

#include <QList>

#include <QLinkedList>

#include <QPointF>



using namespace Poppler;

using ::testing::_;

using ::testing::Return;



class InkAnnotationPrivateTest : public ::testing::Test {

protected:

    std::unique_ptr<InkAnnotationPrivate> inkAnnotPrivate;



    void SetUp() override {

        inkAnnotPrivate = std::make_unique<InkAnnotationPrivate>();

    }

};



TEST_F(InkAnnotationPrivateTest, ToAnnotPaths_EmptyInput_ReturnsEmptyVector_1406) {

    QList<QLinkedList<QPointF>> emptyPaths;

    auto result = inkAnnotPrivate->toAnnotPaths(emptyPaths);

    EXPECT_TRUE(result.empty());

}



TEST_F(InkAnnotationPrivateTest, ToAnnotPaths_SinglePath_ReturnsSingleElementVector_1406) {

    QPointF point(1.0, 2.0);

    QLinkedList<QPointF> path;

    path.append(point);



    QList<QLinkedList<QPointF>> paths;

    paths.append(path);



    auto result = inkAnnotPrivate->toAnnotPaths(paths);

    EXPECT_EQ(result.size(), 1);

}



TEST_F(InkAnnotationPrivateTest, ToAnnotPaths_MultiplePaths_ReturnsCorrectSizeVector_1406) {

    QPointF point1(1.0, 2.0);

    QPointF point2(3.0, 4.0);



    QLinkedList<QPointF> path1;

    path1.append(point1);



    QLinkedList<QPointF> path2;

    path2.append(point2);



    QList<QLinkedList<QPointF>> paths;

    paths.append(path1);

    paths.append(path2);



    auto result = inkAnnotPrivate->toAnnotPaths(paths);

    EXPECT_EQ(result.size(), 2);

}
