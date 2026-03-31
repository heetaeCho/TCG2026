#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QRectF>
#include <QList>
#include <QPointF>

// Include the necessary Poppler headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"

// Include poppler core headers
#include "Page.h"
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

using namespace Poppler;

class HighlightAnnotationPrivateTest_1403 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize global params if needed
    }

    void TearDown() override {
    }
};

// Test that a default-constructed HighlightAnnotation exists and has expected default SubType
TEST_F(HighlightAnnotationPrivateTest_1403, DefaultConstructionSubType_1403)
{
    HighlightAnnotation annot;
    EXPECT_EQ(annot.subType(), Annotation::AHighlight);
}

// Test that default highlight type is Highlight
TEST_F(HighlightAnnotationPrivateTest_1403, DefaultHighlightType_1403)
{
    HighlightAnnotation annot;
    EXPECT_EQ(annot.highlightType(), HighlightAnnotation::Highlight);
}

// Test setting and getting highlight type
TEST_F(HighlightAnnotationPrivateTest_1403, SetHighlightType_1403)
{
    HighlightAnnotation annot;
    
    annot.setHighlightType(HighlightAnnotation::Underline);
    EXPECT_EQ(annot.highlightType(), HighlightAnnotation::Underline);
    
    annot.setHighlightType(HighlightAnnotation::Squiggly);
    EXPECT_EQ(annot.highlightType(), HighlightAnnotation::Squiggly);
    
    annot.setHighlightType(HighlightAnnotation::StrikeOut);
    EXPECT_EQ(annot.highlightType(), HighlightAnnotation::StrikeOut);
    
    annot.setHighlightType(HighlightAnnotation::Highlight);
    EXPECT_EQ(annot.highlightType(), HighlightAnnotation::Highlight);
}

// Test setting and getting highlight quads
TEST_F(HighlightAnnotationPrivateTest_1403, SetAndGetHighlightQuads_1403)
{
    HighlightAnnotation annot;
    
    QList<HighlightAnnotation::Quad> quads;
    HighlightAnnotation::Quad quad;
    quad.points[0] = QPointF(0.0, 0.0);
    quad.points[1] = QPointF(1.0, 0.0);
    quad.points[2] = QPointF(1.0, 1.0);
    quad.points[3] = QPointF(0.0, 1.0);
    quad.capStart = true;
    quad.capEnd = true;
    quad.feather = 0.5;
    quads.append(quad);
    
    annot.setHighlightQuads(quads);
    
    QList<HighlightAnnotation::Quad> retrievedQuads = annot.highlightQuads();
    ASSERT_EQ(retrievedQuads.size(), 1);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[0].x(), 0.0);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[0].y(), 0.0);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[1].x(), 1.0);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[1].y(), 0.0);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[2].x(), 1.0);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[2].y(), 1.0);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[3].x(), 0.0);
    EXPECT_DOUBLE_EQ(retrievedQuads[0].points[3].y(), 1.0);
}

// Test empty quads list
TEST_F(HighlightAnnotationPrivateTest_1403, EmptyHighlightQuads_1403)
{
    HighlightAnnotation annot;
    
    QList<HighlightAnnotation::Quad> quads;
    annot.setHighlightQuads(quads);
    
    QList<HighlightAnnotation::Quad> retrievedQuads = annot.highlightQuads();
    EXPECT_EQ(retrievedQuads.size(), 0);
}

// Test multiple quads
TEST_F(HighlightAnnotationPrivateTest_1403, MultipleHighlightQuads_1403)
{
    HighlightAnnotation annot;
    
    QList<HighlightAnnotation::Quad> quads;
    for (int i = 0; i < 5; ++i) {
        HighlightAnnotation::Quad quad;
        quad.points[0] = QPointF(i * 0.1, 0.0);
        quad.points[1] = QPointF(i * 0.1 + 0.1, 0.0);
        quad.points[2] = QPointF(i * 0.1 + 0.1, 0.1);
        quad.points[3] = QPointF(i * 0.1, 0.1);
        quad.capStart = (i % 2 == 0);
        quad.capEnd = (i % 2 != 0);
        quad.feather = i * 0.2;
        quads.append(quad);
    }
    
    annot.setHighlightQuads(quads);
    
    QList<HighlightAnnotation::Quad> retrievedQuads = annot.highlightQuads();
    ASSERT_EQ(retrievedQuads.size(), 5);
    
    for (int i = 0; i < 5; ++i) {
        EXPECT_NEAR(retrievedQuads[i].points[0].x(), i * 0.1, 1e-6);
    }
}

// Test boundary setting on the annotation base
TEST_F(HighlightAnnotationPrivateTest_1403, BoundarySetGet_1403)
{
    HighlightAnnotation annot;
    
    QRectF boundary(0.1, 0.2, 0.5, 0.6);
    annot.setBoundary(boundary);
    
    QRectF retrievedBoundary = annot.boundary();
    EXPECT_NEAR(retrievedBoundary.x(), 0.1, 1e-6);
    EXPECT_NEAR(retrievedBoundary.y(), 0.2, 1e-6);
    EXPECT_NEAR(retrievedBoundary.width(), 0.5, 1e-6);
    EXPECT_NEAR(retrievedBoundary.height(), 0.6, 1e-6);
}

// Test setting author on highlight annotation
TEST_F(HighlightAnnotationPrivateTest_1403, AuthorSetGet_1403)
{
    HighlightAnnotation annot;
    
    annot.setAuthor(QStringLiteral("TestAuthor"));
    EXPECT_EQ(annot.author(), QStringLiteral("TestAuthor"));
}

// Test setting contents on highlight annotation
TEST_F(HighlightAnnotationPrivateTest_1403, ContentsSetGet_1403)
{
    HighlightAnnotation annot;
    
    annot.setContents(QStringLiteral("Test contents"));
    EXPECT_EQ(annot.contents(), QStringLiteral("Test contents"));
}

// Test quad feather boundary values
TEST_F(HighlightAnnotationPrivateTest_1403, QuadFeatherBoundaryValues_1403)
{
    HighlightAnnotation annot;
    
    QList<HighlightAnnotation::Quad> quads;
    HighlightAnnotation::Quad quad;
    quad.points[0] = QPointF(0.0, 0.0);
    quad.points[1] = QPointF(1.0, 0.0);
    quad.points[2] = QPointF(1.0, 1.0);
    quad.points[3] = QPointF(0.0, 1.0);
    quad.capStart = false;
    quad.capEnd = false;
    quad.feather = 0.0;
    quads.append(quad);
    
    annot.setHighlightQuads(quads);
    
    QList<HighlightAnnotation::Quad> retrieved = annot.highlightQuads();
    ASSERT_EQ(retrieved.size(), 1);
    EXPECT_DOUBLE_EQ(retrieved[0].feather, 0.0);
}

// Test replacing quads
TEST_F(HighlightAnnotationPrivateTest_1403, ReplaceHighlightQuads_1403)
{
    HighlightAnnotation annot;
    
    // Set initial quads
    QList<HighlightAnnotation::Quad> quads1;
    HighlightAnnotation::Quad q1;
    q1.points[0] = QPointF(0.0, 0.0);
    q1.points[1] = QPointF(0.5, 0.0);
    q1.points[2] = QPointF(0.5, 0.5);
    q1.points[3] = QPointF(0.0, 0.5);
    q1.capStart = true;
    q1.capEnd = false;
    q1.feather = 1.0;
    quads1.append(q1);
    annot.setHighlightQuads(quads1);
    ASSERT_EQ(annot.highlightQuads().size(), 1);
    
    // Replace with different quads
    QList<HighlightAnnotation::Quad> quads2;
    HighlightAnnotation::Quad q2a, q2b;
    q2a.points[0] = QPointF(0.1, 0.1);
    q2a.points[1] = QPointF(0.2, 0.1);
    q2a.points[2] = QPointF(0.2, 0.2);
    q2a.points[3] = QPointF(0.1, 0.2);
    q2a.capStart = false;
    q2a.capEnd = true;
    q2a.feather = 0.3;
    
    q2b.points[0] = QPointF(0.3, 0.3);
    q2b.points[1] = QPointF(0.4, 0.3);
    q2b.points[2] = QPointF(0.4, 0.4);
    q2b.points[3] = QPointF(0.3, 0.4);
    q2b.capStart = true;
    q2b.capEnd = true;
    q2b.feather = 0.7;
    
    quads2.append(q2a);
    quads2.append(q2b);
    annot.setHighlightQuads(quads2);
    
    QList<HighlightAnnotation::Quad> retrieved = annot.highlightQuads();
    ASSERT_EQ(retrieved.size(), 2);
    EXPECT_NEAR(retrieved[0].points[0].x(), 0.1, 1e-6);
    EXPECT_NEAR(retrieved[1].points[0].x(), 0.3, 1e-6);
}

// Test flags on highlight annotation
TEST_F(HighlightAnnotationPrivateTest_1403, FlagsSetGet_1403)
{
    HighlightAnnotation annot;
    
    annot.setFlags(Annotation::Hidden | Annotation::FixedRotation);
    int flags = annot.flags();
    EXPECT_TRUE(flags & Annotation::Hidden);
    EXPECT_TRUE(flags & Annotation::FixedRotation);
}

// Test that createNativeAnnot requires valid Page and DocumentData
// Since we can't easily construct these, we verify the annotation can exist standalone
TEST_F(HighlightAnnotationPrivateTest_1403, StandaloneAnnotationValidity_1403)
{
    HighlightAnnotation annot;
    // A standalone annotation (not tied to a native annot) should still function
    EXPECT_EQ(annot.subType(), Annotation::AHighlight);
    EXPECT_EQ(annot.highlightType(), HighlightAnnotation::Highlight);
    EXPECT_TRUE(annot.highlightQuads().isEmpty());
}

// Test with a loaded PDF document if possible - testing createNativeAnnot indirectly
// by adding a highlight annotation to a document page
TEST_F(HighlightAnnotationPrivateTest_1403, AnnotSubTypeMapping_1403)
{
    // Verify the subtype is always AHighlight regardless of highlight type setting
    HighlightAnnotation annot;
    
    annot.setHighlightType(HighlightAnnotation::Underline);
    EXPECT_EQ(annot.subType(), Annotation::AHighlight);
    
    annot.setHighlightType(HighlightAnnotation::Squiggly);
    EXPECT_EQ(annot.subType(), Annotation::AHighlight);
    
    annot.setHighlightType(HighlightAnnotation::StrikeOut);
    EXPECT_EQ(annot.subType(), Annotation::AHighlight);
}

// Test unique name
TEST_F(HighlightAnnotationPrivateTest_1403, UniqueNameSetGet_1403)
{
    HighlightAnnotation annot;
    
    annot.setUniqueName(QStringLiteral("unique-id-12345"));
    EXPECT_EQ(annot.uniqueName(), QStringLiteral("unique-id-12345"));
}

// Test zero-area boundary
TEST_F(HighlightAnnotationPrivateTest_1403, ZeroAreaBoundary_1403)
{
    HighlightAnnotation annot;
    
    QRectF zeroBoundary(0.5, 0.5, 0.0, 0.0);
    annot.setBoundary(zeroBoundary);
    
    QRectF retrieved = annot.boundary();
    EXPECT_DOUBLE_EQ(retrieved.width(), 0.0);
    EXPECT_DOUBLE_EQ(retrieved.height(), 0.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
