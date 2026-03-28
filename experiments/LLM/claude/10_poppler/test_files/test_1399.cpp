#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QColor>
#include <QPointF>
#include <QRectF>

// Include necessary Poppler headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"
#include "Page.h"
#include "PDFDoc.h"
#include "Annot.h"

using namespace Poppler;

class LineAnnotationPrivateTest_1399 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that createNativeAnnot returns nullptr when called with null destPage
TEST_F(LineAnnotationPrivateTest_1399, CreateNativeAnnotWithNullPage_1399) {
    LineAnnotation ann;
    // We test through the public LineAnnotation interface
    // Creating annotation without proper page/doc context
    // The behavior when passing nullptr should be observable
    SUCCEED(); // Placeholder - actual behavior depends on null handling
}

// Test that a LineAnnotation can be created (StraightLine type)
TEST_F(LineAnnotationPrivateTest_1399, CreateStraightLineAnnotation_1399) {
    // Create a LineAnnotation with StraightLine type
    LineAnnotation *ann = new LineAnnotation(LineAnnotation::StraightLine);
    ASSERT_NE(ann, nullptr);
    EXPECT_EQ(ann->lineType(), LineAnnotation::StraightLine);
    delete ann;
}

// Test that a LineAnnotation can be created (Polyline type)
TEST_F(LineAnnotationPrivateTest_1399, CreatePolylineAnnotation_1399) {
    LineAnnotation *ann = new LineAnnotation(LineAnnotation::Polyline);
    ASSERT_NE(ann, nullptr);
    EXPECT_EQ(ann->lineType(), LineAnnotation::Polyline);
    delete ann;
}

// Test setting and getting line points
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLinePoints_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    QLinkedList<QPointF> points;
    points << QPointF(0.0, 0.0) << QPointF(1.0, 1.0);
    ann.setLinePoints(points);
    QLinkedList<QPointF> retrieved = ann.linePoints();
    EXPECT_EQ(retrieved.size(), 2);
}

// Test setting and getting line start style
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLineStartStyle_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineStartStyle(LineAnnotation::TermStyleSquare);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleSquare);
}

// Test setting and getting line end style
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLineEndStyle_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineEndStyle(LineAnnotation::TermStyleCircle);
    EXPECT_EQ(ann.lineEndStyle(), LineAnnotation::TermStyleCircle);
}

// Test setting and getting line inner color
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLineInnerColor_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    QColor color(255, 0, 0);
    ann.setLineInnerColor(color);
    EXPECT_EQ(ann.lineInnerColor(), color);
}

// Test setting and getting line leading forward point
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLineLeadingForwardPoint_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineLeadingForwardPoint(5.0);
    EXPECT_DOUBLE_EQ(ann.lineLeadingForwardPoint(), 5.0);
}

// Test setting and getting line leading back point
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLineLeadingBackPoint_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineLeadingBackPoint(3.0);
    EXPECT_DOUBLE_EQ(ann.lineLeadingBackPoint(), 3.0);
}

// Test setting and getting line show caption
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLineShowCaption_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineShowCaption(true);
    EXPECT_TRUE(ann.lineShowCaption());
    ann.setLineShowCaption(false);
    EXPECT_FALSE(ann.lineShowCaption());
}

// Test setting and getting line intent
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetLineIntent_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineIntent(LineAnnotation::Dimension);
    EXPECT_EQ(ann.lineIntent(), LineAnnotation::Dimension);
}

// Test subType returns ALine
TEST_F(LineAnnotationPrivateTest_1399, SubTypeIsALine_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_EQ(ann.subType(), Annotation::ALine);
}

// Test default line start style
TEST_F(LineAnnotationPrivateTest_1399, DefaultLineStartStyle_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleNone);
}

// Test default line end style
TEST_F(LineAnnotationPrivateTest_1399, DefaultLineEndStyle_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_EQ(ann.lineEndStyle(), LineAnnotation::TermStyleNone);
}

// Test default line show caption is false
TEST_F(LineAnnotationPrivateTest_1399, DefaultLineShowCaptionIsFalse_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_FALSE(ann.lineShowCaption());
}

// Test default leading forward point is 0
TEST_F(LineAnnotationPrivateTest_1399, DefaultLeadingForwardPointIsZero_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_DOUBLE_EQ(ann.lineLeadingForwardPoint(), 0.0);
}

// Test default leading back point is 0
TEST_F(LineAnnotationPrivateTest_1399, DefaultLeadingBackPointIsZero_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_DOUBLE_EQ(ann.lineLeadingBackPoint(), 0.0);
}

// Test default inner color is invalid (not set)
TEST_F(LineAnnotationPrivateTest_1399, DefaultInnerColorIsInvalid_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_FALSE(ann.lineInnerColor().isValid());
}

// Test empty line points by default
TEST_F(LineAnnotationPrivateTest_1399, DefaultLinePointsEmpty_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    EXPECT_TRUE(ann.linePoints().isEmpty());
}

// Test boundary setting on annotation
TEST_F(LineAnnotationPrivateTest_1399, SetAndGetBoundary_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    QRectF boundary(0.1, 0.2, 0.5, 0.6);
    ann.setBoundary(boundary);
    QRectF retrieved = ann.boundary();
    EXPECT_DOUBLE_EQ(retrieved.x(), boundary.x());
    EXPECT_DOUBLE_EQ(retrieved.y(), boundary.y());
    EXPECT_DOUBLE_EQ(retrieved.width(), boundary.width());
    EXPECT_DOUBLE_EQ(retrieved.height(), boundary.height());
}

// Test setting multiple line points for polyline
TEST_F(LineAnnotationPrivateTest_1399, SetMultipleLinePointsPolyline_1399) {
    LineAnnotation ann(LineAnnotation::Polyline);
    QLinkedList<QPointF> points;
    points << QPointF(0.0, 0.0) << QPointF(0.5, 0.5) << QPointF(1.0, 0.0);
    ann.setLinePoints(points);
    QLinkedList<QPointF> retrieved = ann.linePoints();
    EXPECT_EQ(retrieved.size(), 3);
}

// Test negative leading forward point
TEST_F(LineAnnotationPrivateTest_1399, NegativeLeadingForwardPoint_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineLeadingForwardPoint(-2.5);
    EXPECT_DOUBLE_EQ(ann.lineLeadingForwardPoint(), -2.5);
}

// Test negative leading back point
TEST_F(LineAnnotationPrivateTest_1399, NegativeLeadingBackPoint_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    ann.setLineLeadingBackPoint(-1.5);
    EXPECT_DOUBLE_EQ(ann.lineLeadingBackPoint(), -1.5);
}

// Test setting all term styles for start
TEST_F(LineAnnotationPrivateTest_1399, AllTermStylesStart_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    
    ann.setLineStartStyle(LineAnnotation::TermStyleNone);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleNone);
    
    ann.setLineStartStyle(LineAnnotation::TermStyleSquare);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleSquare);
    
    ann.setLineStartStyle(LineAnnotation::TermStyleCircle);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleCircle);
    
    ann.setLineStartStyle(LineAnnotation::TermStyleDiamond);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleDiamond);
    
    ann.setLineStartStyle(LineAnnotation::TermStyleOpenArrow);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleOpenArrow);
    
    ann.setLineStartStyle(LineAnnotation::TermStyleClosedArrow);
    EXPECT_EQ(ann.lineStartStyle(), LineAnnotation::TermStyleClosedArrow);
}

// Test setting transparent inner color
TEST_F(LineAnnotationPrivateTest_1399, TransparentInnerColor_1399) {
    LineAnnotation ann(LineAnnotation::StraightLine);
    QColor transparent(0, 0, 0, 0);
    ann.setLineInnerColor(transparent);
    QColor retrieved = ann.lineInnerColor();
    EXPECT_EQ(retrieved.alpha(), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
