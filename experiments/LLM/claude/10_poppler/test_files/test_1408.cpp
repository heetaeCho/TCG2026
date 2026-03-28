#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary Poppler Qt5 headers
#include "poppler-annotation.h"
#include "poppler-qt5.h"

#include <memory>

namespace {

// Test fixture for LinkAnnotation tests
class LinkAnnotationTest_1408 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a LinkAnnotation can be created without crashing
TEST_F(LinkAnnotationTest_1408, DefaultConstruction_1408) {
    Poppler::LinkAnnotation annot;
    // Should be able to create a LinkAnnotation without issues
    EXPECT_EQ(annot.subType(), Poppler::Annotation::ALink);
}

// Test that linkDestination is initially null
TEST_F(LinkAnnotationTest_1408, InitialLinkDestinationIsNull_1408) {
    Poppler::LinkAnnotation annot;
    EXPECT_EQ(annot.linkDestination(), nullptr);
}

// Test that the annotation type is ALink
TEST_F(LinkAnnotationTest_1408, SubTypeIsALink_1408) {
    Poppler::LinkAnnotation annot;
    EXPECT_EQ(annot.subType(), Poppler::Annotation::ALink);
}

// Test that setting and getting linkDestination works
TEST_F(LinkAnnotationTest_1408, SetAndGetLinkDestination_1408) {
    Poppler::LinkAnnotation annot;
    // Create a Link object to set
    Poppler::LinkGoto *link = new Poppler::LinkGoto(QRectF(), false, Poppler::LinkDestination(QString()));
    annot.setLinkDestination(link);
    EXPECT_NE(annot.linkDestination(), nullptr);
}

// Test that destroying LinkAnnotation with a set linkDestination doesn't leak or crash
TEST_F(LinkAnnotationTest_1408, DestructorCleansUpLinkDestination_1408) {
    // This test verifies no crash occurs on destruction
    {
        Poppler::LinkAnnotation annot;
        Poppler::LinkGoto *link = new Poppler::LinkGoto(QRectF(), false, Poppler::LinkDestination(QString()));
        annot.setLinkDestination(link);
    }
    // If we reach here, destruction was successful
    SUCCEED();
}

// Test that destroying LinkAnnotation with null linkDestination doesn't crash
TEST_F(LinkAnnotationTest_1408, DestructorWithNullLinkDestination_1408) {
    {
        Poppler::LinkAnnotation annot;
        // Don't set any link destination, leave it null
    }
    // If we reach here, destruction of annotation with null linkDestination was successful
    SUCCEED();
}

// Test that highlightMode has a default value
TEST_F(LinkAnnotationTest_1408, DefaultHighlightMode_1408) {
    Poppler::LinkAnnotation annot;
    // Check that highlightMode returns a valid enum value
    Poppler::LinkAnnotation::HighlightMode mode = annot.linkHighlightMode();
    EXPECT_GE(static_cast<int>(mode), 0);
}

// Test setting highlight mode
TEST_F(LinkAnnotationTest_1408, SetHighlightMode_1408) {
    Poppler::LinkAnnotation annot;
    annot.setLinkHighlightMode(Poppler::LinkAnnotation::Invert);
    EXPECT_EQ(annot.linkHighlightMode(), Poppler::LinkAnnotation::Invert);
}

// Test setting different highlight modes
TEST_F(LinkAnnotationTest_1408, SetHighlightModeOutline_1408) {
    Poppler::LinkAnnotation annot;
    annot.setLinkHighlightMode(Poppler::LinkAnnotation::Outline);
    EXPECT_EQ(annot.linkHighlightMode(), Poppler::LinkAnnotation::Outline);
}

// Test setting highlight mode to Push
TEST_F(LinkAnnotationTest_1408, SetHighlightModePush_1408) {
    Poppler::LinkAnnotation annot;
    annot.setLinkHighlightMode(Poppler::LinkAnnotation::Push);
    EXPECT_EQ(annot.linkHighlightMode(), Poppler::LinkAnnotation::Push);
}

// Test that linkRegion can be accessed
TEST_F(LinkAnnotationTest_1408, LinkRegionAccessible_1408) {
    Poppler::LinkAnnotation annot;
    QList<QPointF> region = annot.linkRegionPoint();
    // Default region should be accessible (may be empty or have default points)
    // Just verify it doesn't crash
    SUCCEED();
}

// Test setting link region points
TEST_F(LinkAnnotationTest_1408, SetLinkRegionPoints_1408) {
    Poppler::LinkAnnotation annot;
    QList<QPointF> region;
    region << QPointF(0.0, 0.0) << QPointF(1.0, 0.0) << QPointF(1.0, 1.0) << QPointF(0.0, 1.0);
    annot.setLinkRegionPoint(region);
    QList<QPointF> retrieved = annot.linkRegionPoint();
    EXPECT_EQ(retrieved.size(), region.size());
}

// Test setting empty link region
TEST_F(LinkAnnotationTest_1408, SetEmptyLinkRegion_1408) {
    Poppler::LinkAnnotation annot;
    QList<QPointF> emptyRegion;
    annot.setLinkRegionPoint(emptyRegion);
    QList<QPointF> retrieved = annot.linkRegionPoint();
    EXPECT_EQ(retrieved.size(), 0);
}

// Test replacing linkDestination
TEST_F(LinkAnnotationTest_1408, ReplaceLinkDestination_1408) {
    Poppler::LinkAnnotation annot;
    Poppler::LinkGoto *link1 = new Poppler::LinkGoto(QRectF(), false, Poppler::LinkDestination(QString()));
    annot.setLinkDestination(link1);
    EXPECT_NE(annot.linkDestination(), nullptr);

    Poppler::LinkGoto *link2 = new Poppler::LinkGoto(QRectF(), true, Poppler::LinkDestination(QString()));
    annot.setLinkDestination(link2);
    EXPECT_NE(annot.linkDestination(), nullptr);
}

// Test common Annotation interface properties
TEST_F(LinkAnnotationTest_1408, SetAndGetAuthor_1408) {
    Poppler::LinkAnnotation annot;
    annot.setAuthor(QString("TestAuthor"));
    EXPECT_EQ(annot.author(), QString("TestAuthor"));
}

// Test setting contents on annotation
TEST_F(LinkAnnotationTest_1408, SetAndGetContents_1408) {
    Poppler::LinkAnnotation annot;
    annot.setContents(QString("TestContents"));
    EXPECT_EQ(annot.contents(), QString("TestContents"));
}

// Test boundary property
TEST_F(LinkAnnotationTest_1408, SetAndGetBoundary_1408) {
    Poppler::LinkAnnotation annot;
    QRectF boundary(0.1, 0.2, 0.3, 0.4);
    annot.setBoundary(boundary);
    QRectF retrieved = annot.boundary();
    EXPECT_DOUBLE_EQ(retrieved.x(), boundary.x());
    EXPECT_DOUBLE_EQ(retrieved.y(), boundary.y());
    EXPECT_DOUBLE_EQ(retrieved.width(), boundary.width());
    EXPECT_DOUBLE_EQ(retrieved.height(), boundary.height());
}

} // namespace
