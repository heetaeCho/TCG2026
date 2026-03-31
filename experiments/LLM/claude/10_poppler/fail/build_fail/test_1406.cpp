#include <gtest/gtest.h>
#include <QList>
#include <QLinkedList>
#include <QPointF>
#include <memory>
#include <vector>

#include "poppler-annotation.h"
#include "poppler-annotation-private.h"

// If direct headers aren't available, we may need to include the implementation
// or relevant poppler headers
#include "Annot.h"

namespace Poppler {

class InkAnnotationPrivateTest_1406 : public ::testing::Test {
protected:
    InkAnnotationPrivate privateObj;
};

// Test with empty paths list
TEST_F(InkAnnotationPrivateTest_1406, EmptyPathsReturnsEmptyVector_1406) {
    QList<QLinkedList<QPointF>> emptyPaths;
    auto result = privateObj.toAnnotPaths(emptyPaths);
    EXPECT_EQ(result.size(), 0u);
    EXPECT_TRUE(result.empty());
}

// Test with single path containing no points
TEST_F(InkAnnotationPrivateTest_1406, SingleEmptyPathReturnsSingleAnnotPath_1406) {
    QList<QLinkedList<QPointF>> paths;
    QLinkedList<QPointF> emptyPath;
    paths.append(emptyPath);

    auto result = privateObj.toAnnotPaths(paths);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result[0], nullptr);
}

// Test with single path containing one point
TEST_F(InkAnnotationPrivateTest_1406, SinglePathWithOnePoint_1406) {
    QList<QLinkedList<QPointF>> paths;
    QLinkedList<QPointF> path;
    path.append(QPointF(1.0, 2.0));
    paths.append(path);

    auto result = privateObj.toAnnotPaths(paths);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result[0], nullptr);
}

// Test with single path containing multiple points
TEST_F(InkAnnotationPrivateTest_1406, SinglePathWithMultiplePoints_1406) {
    QList<QLinkedList<QPointF>> paths;
    QLinkedList<QPointF> path;
    path.append(QPointF(0.0, 0.0));
    path.append(QPointF(1.0, 1.0));
    path.append(QPointF(2.0, 2.0));
    paths.append(path);

    auto result = privateObj.toAnnotPaths(paths);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result[0], nullptr);
}

// Test with multiple paths
TEST_F(InkAnnotationPrivateTest_1406, MultiplePathsReturnsCorrectCount_1406) {
    QList<QLinkedList<QPointF>> paths;

    for (int i = 0; i < 5; ++i) {
        QLinkedList<QPointF> path;
        path.append(QPointF(i * 1.0, i * 2.0));
        path.append(QPointF(i * 3.0, i * 4.0));
        paths.append(path);
    }

    auto result = privateObj.toAnnotPaths(paths);
    EXPECT_EQ(result.size(), 5u);
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NE(result[i], nullptr);
    }
}

// Test with paths containing negative coordinates
TEST_F(InkAnnotationPrivateTest_1406, PathsWithNegativeCoordinates_1406) {
    QList<QLinkedList<QPointF>> paths;
    QLinkedList<QPointF> path;
    path.append(QPointF(-1.0, -2.0));
    path.append(QPointF(-3.5, -4.5));
    paths.append(path);

    auto result = privateObj.toAnnotPaths(paths);
    EXPECT_EQ(result.size(), 1u);
    EXPECT_NE(result[0], nullptr);
}

// Test result size matches input size for various sizes
TEST_F(InkAnnotationPrivateTest_1406, ResultSizeMatchesInputSize_1406) {
    for (int count = 0; count <= 10; ++count) {
        QList<QLinkedList<QPointF>> paths;
        for (int i = 0; i < count; ++i) {
            QLinkedList<QPointF> path;
            path.append(QPointF(0.0, 0.0));
            paths.append(path);
        }
        auto result = privateObj.toAnnotPaths(paths);
        EXPECT_EQ(static_cast<int>(result.size()), count);
    }
}

} // namespace Poppler
