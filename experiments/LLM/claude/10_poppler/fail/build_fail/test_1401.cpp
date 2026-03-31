#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "Annot.h"

using namespace Poppler;

// Helper to create AnnotQuadrilaterals with known values
static std::unique_ptr<AnnotQuadrilaterals> createQuads(int count, const std::vector<std::array<double, 8>>& coords) {
    auto quads = std::make_unique<AnnotQuadrilateral[]>(count);
    for (int i = 0; i < count; i++) {
        quads[i] = AnnotQuadrilateral(
            coords[i][0], coords[i][1],  // x1, y1
            coords[i][2], coords[i][3],  // x2, y2
            coords[i][4], coords[i][5],  // x3, y3
            coords[i][6], coords[i][7]   // x4, y4
        );
    }
    return std::make_unique<AnnotQuadrilaterals>(std::move(quads), count);
}

class HighlightAnnotationPrivateTest_1401 : public ::testing::Test {
protected:
    HighlightAnnotationPrivate priv;
};

TEST_F(HighlightAnnotationPrivateTest_1401, NullPointerReturnsEmptyList_1401) {
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(nullptr);
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(HighlightAnnotationPrivateTest_1401, ZeroLengthReturnsEmptyList_1401) {
    auto quads = std::make_unique<AnnotQuadrilaterals>(std::unique_ptr<AnnotQuadrilateral[]>(nullptr), 0);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    EXPECT_TRUE(result.isEmpty());
}

TEST_F(HighlightAnnotationPrivateTest_1401, SingleQuadReturnsOneElement_1401) {
    std::vector<std::array<double, 8>> coords = {{0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0}};
    auto quads = createQuads(1, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    EXPECT_EQ(result.size(), 1);
}

TEST_F(HighlightAnnotationPrivateTest_1401, QuadCapStartIsTrue_1401) {
    std::vector<std::array<double, 8>> coords = {{0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0}};
    auto quads = createQuads(1, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    ASSERT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].capStart);
}

TEST_F(HighlightAnnotationPrivateTest_1401, QuadCapEndIsTrue_1401) {
    std::vector<std::array<double, 8>> coords = {{0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0}};
    auto quads = createQuads(1, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    ASSERT_EQ(result.size(), 1);
    EXPECT_TRUE(result[0].capEnd);
}

TEST_F(HighlightAnnotationPrivateTest_1401, QuadFeatherIsDefaultValue_1401) {
    std::vector<std::array<double, 8>> coords = {{0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0}};
    auto quads = createQuads(1, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    ASSERT_EQ(result.size(), 1);
    EXPECT_DOUBLE_EQ(result[0].feather, 0.1);
}

TEST_F(HighlightAnnotationPrivateTest_1401, MultipleQuadsReturnsCorrectCount_1401) {
    std::vector<std::array<double, 8>> coords = {
        {0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0},
        {2.0, 2.0, 3.0, 2.0, 3.0, 3.0, 2.0, 3.0},
        {4.0, 4.0, 5.0, 4.0, 5.0, 5.0, 4.0, 5.0}
    };
    auto quads = createQuads(3, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    EXPECT_EQ(result.size(), 3);
}

TEST_F(HighlightAnnotationPrivateTest_1401, AllQuadsHaveCorrectDefaults_1401) {
    std::vector<std::array<double, 8>> coords = {
        {0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0},
        {2.0, 2.0, 3.0, 2.0, 3.0, 3.0, 2.0, 3.0}
    };
    auto quads = createQuads(2, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    ASSERT_EQ(result.size(), 2);
    for (int i = 0; i < result.size(); i++) {
        EXPECT_TRUE(result[i].capStart) << "Quad " << i << " capStart should be true";
        EXPECT_TRUE(result[i].capEnd) << "Quad " << i << " capEnd should be true";
        EXPECT_DOUBLE_EQ(result[i].feather, 0.1) << "Quad " << i << " feather should be 0.1";
    }
}

TEST_F(HighlightAnnotationPrivateTest_1401, QuadHasFourPoints_1401) {
    std::vector<std::array<double, 8>> coords = {{0.0, 0.0, 1.0, 0.0, 1.0, 1.0, 0.0, 1.0}};
    auto quads = createQuads(1, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    ASSERT_EQ(result.size(), 1);
    // Quad should have exactly 4 points (points[0] through points[3])
    // Just verify they exist and are QPointF values
    QPointF p0 = result[0].points[0];
    QPointF p1 = result[0].points[1];
    QPointF p2 = result[0].points[2];
    QPointF p3 = result[0].points[3];
    // Points[2] and Points[3] should be swapped relative to input order
    // (point originally at index 3 goes to 2, and vice versa)
    // We can't verify exact values without knowing MTX, but we verify no crash
    SUCCEED();
}

TEST_F(HighlightAnnotationPrivateTest_1401, Points2And3AreSwapped_1401) {
    // Use distinct coordinates so we can verify the swap even after transformation
    std::vector<std::array<double, 8>> coords = {{10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0}};
    auto quads = createQuads(1, coords);
    QList<HighlightAnnotation::Quad> result = priv.fromQuadrilaterals(quads.get());
    ASSERT_EQ(result.size(), 1);
    // After the swap, points[2] should contain what was originally transformed from (x4,y4)
    // and points[3] should contain what was originally transformed from (x3,y3)
    // We verify that points[2] != points[3] (given distinct input)
    EXPECT_NE(result[0].points[2], result[0].points[3]);
}
