#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QLinkedList>
#include <QPointF>
#include <QRectF>
#include <memory>

#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"

// We need access to AnnotPath and related types
#include "Annot.h"

namespace Poppler {

// A concrete subclass to allow instantiation for testing purposes
// since AnnotationPrivate itself may be abstract or hard to instantiate directly
class TestableAnnotationPrivate : public AnnotationPrivate {
public:
    TestableAnnotationPrivate() : AnnotationPrivate() {}

    std::shared_ptr<Annot> createNativeAnnot(::Page *destPage, DocumentData *doc) override {
        return nullptr;
    }
};

class AnnotationPrivateTest_1389 : public ::testing::Test {
protected:
    void SetUp() override {
        priv = std::make_unique<TestableAnnotationPrivate>();
        // Set boundary to a known rectangle - identity-like transform
        // When pdfAnnot is null, fillTransformationMTX should produce
        // a transformation based on the boundary member
        priv->boundary = QRectF(0.0, 0.0, 1.0, 1.0);
    }

    std::unique_ptr<TestableAnnotationPrivate> priv;
};

// Test that toAnnotPath with an empty list returns an AnnotPath (non-null) with 0 coords
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathEmptyList_1389) {
    QLinkedList<QPointF> emptyList;
    auto path = priv->toAnnotPath(emptyList);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 0);
}

// Test that toAnnotPath with a single point returns an AnnotPath with 1 coord
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathSinglePoint_1389) {
    QLinkedList<QPointF> list;
    list.append(QPointF(0.5, 0.5));
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 1);
}

// Test that toAnnotPath with multiple points returns correct count
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathMultiplePoints_1389) {
    QLinkedList<QPointF> list;
    list.append(QPointF(0.0, 0.0));
    list.append(QPointF(0.5, 0.5));
    list.append(QPointF(1.0, 1.0));
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 3);
}

// Test that toAnnotPath preserves the number of points for a larger list
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathManyPoints_1389) {
    QLinkedList<QPointF> list;
    const int numPoints = 100;
    for (int i = 0; i < numPoints; ++i) {
        list.append(QPointF(i * 0.01, i * 0.01));
    }
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), numPoints);
}

// Test with negative coordinate values
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathNegativeCoordinates_1389) {
    QLinkedList<QPointF> list;
    list.append(QPointF(-1.0, -1.0));
    list.append(QPointF(-0.5, -0.5));
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 2);
}

// Test with origin point
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathOriginPoint_1389) {
    QLinkedList<QPointF> list;
    list.append(QPointF(0.0, 0.0));
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 1);
}

// Test with very large coordinate values
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathLargeCoordinates_1389) {
    QLinkedList<QPointF> list;
    list.append(QPointF(1e6, 1e6));
    list.append(QPointF(-1e6, -1e6));
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 2);
}

// Test with duplicate points
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathDuplicatePoints_1389) {
    QLinkedList<QPointF> list;
    list.append(QPointF(0.5, 0.5));
    list.append(QPointF(0.5, 0.5));
    list.append(QPointF(0.5, 0.5));
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 3);
}

// Test that returned pointer is unique (not null)
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathReturnsUniquePtr_1389) {
    QLinkedList<QPointF> list;
    list.append(QPointF(0.1, 0.2));
    auto path1 = priv->toAnnotPath(list);
    auto path2 = priv->toAnnotPath(list);
    ASSERT_NE(path1, nullptr);
    ASSERT_NE(path2, nullptr);
    // They should be different objects
    EXPECT_NE(path1.get(), path2.get());
}

// Test with boundary set to different rectangle
TEST_F(AnnotationPrivateTest_1389, ToAnnotPathWithDifferentBoundary_1389) {
    priv->boundary = QRectF(0.0, 0.0, 2.0, 2.0);
    QLinkedList<QPointF> list;
    list.append(QPointF(1.0, 1.0));
    auto path = priv->toAnnotPath(list);
    ASSERT_NE(path, nullptr);
    EXPECT_EQ(path->getCoordsLength(), 1);
}

} // namespace Poppler
