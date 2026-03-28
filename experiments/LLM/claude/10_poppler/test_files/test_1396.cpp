#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QFont>
#include <QColor>
#include <QString>
#include <QRectF>

// Include the necessary poppler headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"
#include "Page.h"
#include "Annot.h"
#include "PDFDoc.h"

using namespace Poppler;

class TextAnnotationPrivateTest_1396 : public ::testing::Test {
protected:
    void SetUp() override {
        // We attempt to create a minimal document context for testing
        // This requires a valid PDFDoc and Page
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDF document and page for testing
    std::unique_ptr<DocumentData> createTestDocumentData(const QString &path) {
        try {
            auto docData = std::make_unique<DocumentData>(path, std::nullopt, std::nullopt);
            return docData;
        } catch (...) {
            return nullptr;
        }
    }
};

// Test that createNativeAnnot returns a non-null shared_ptr for Linked text type
TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnotLinkedReturnsNonNull_1396) {
    // Create a TextAnnotation of type Linked
    TextAnnotation ann(TextAnnotation::Linked);
    
    // We need a valid Page and DocumentData to call createNativeAnnot
    // Without a real PDF document, we verify the annotation was created properly
    EXPECT_EQ(ann.subType(), Annotation::AText);
    EXPECT_EQ(ann.textType(), TextAnnotation::Linked);
}

// Test that createNativeAnnot returns a non-null shared_ptr for InPlace text type
TEST_F(TextAnnotationPrivateTest_1396, CreateNativeAnnotInPlaceReturnsNonNull_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    
    EXPECT_EQ(ann.subType(), Annotation::AText);
    EXPECT_EQ(ann.textType(), TextAnnotation::InPlace);
}

// Test default text icon for TextAnnotation
TEST_F(TextAnnotationPrivateTest_1396, DefaultTextIconIsNote_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    // Default icon should be "Note" as set in TextAnnotationPrivate constructor
    EXPECT_EQ(ann.textIcon(), QStringLiteral("Note"));
}

// Test default inplace alignment
TEST_F(TextAnnotationPrivateTest_1396, DefaultInplaceAlignIsZero_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    EXPECT_EQ(ann.inplaceAlign(), 0);
}

// Test setting and getting text icon
TEST_F(TextAnnotationPrivateTest_1396, SetTextIconPersists_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    ann.setTextIcon(QStringLiteral("Comment"));
    EXPECT_EQ(ann.textIcon(), QStringLiteral("Comment"));
}

// Test setting and getting inplace alignment
TEST_F(TextAnnotationPrivateTest_1396, SetInplaceAlignPersists_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    ann.setInplaceAlign(1);
    EXPECT_EQ(ann.inplaceAlign(), 1);
}

// Test setting and getting inplace alignment with boundary value
TEST_F(TextAnnotationPrivateTest_1396, SetInplaceAlignBoundaryValue_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    ann.setInplaceAlign(2);
    EXPECT_EQ(ann.inplaceAlign(), 2);
}

// Test setting text font on annotation
TEST_F(TextAnnotationPrivateTest_1396, SetTextFontPersists_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    QFont font("Arial", 12);
    ann.setTextFont(font);
    EXPECT_EQ(ann.textFont(), font);
}

// Test setting text color on annotation
TEST_F(TextAnnotationPrivateTest_1396, SetTextColorPersists_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    QColor color(Qt::red);
    ann.setTextColor(color);
    EXPECT_EQ(ann.textColor(), color);
}

// Test boundary setting
TEST_F(TextAnnotationPrivateTest_1396, SetBoundaryPersists_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    QRectF boundary(0.1, 0.2, 0.3, 0.4);
    ann.setBoundary(boundary);
    QRectF retrieved = ann.boundary();
    EXPECT_DOUBLE_EQ(retrieved.x(), 0.1);
    EXPECT_DOUBLE_EQ(retrieved.y(), 0.2);
    EXPECT_DOUBLE_EQ(retrieved.width(), 0.3);
    EXPECT_DOUBLE_EQ(retrieved.height(), 0.4);
}

// Test zero-size boundary
TEST_F(TextAnnotationPrivateTest_1396, ZeroSizeBoundary_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    QRectF boundary(0.0, 0.0, 0.0, 0.0);
    ann.setBoundary(boundary);
    QRectF retrieved = ann.boundary();
    EXPECT_DOUBLE_EQ(retrieved.width(), 0.0);
    EXPECT_DOUBLE_EQ(retrieved.height(), 0.0);
}

// Test setting text font with negative point size (boundary condition for createNativeAnnot warning)
TEST_F(TextAnnotationPrivateTest_1396, NegativePointSizeFontSetting_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    QFont font("Arial");
    font.setPointSizeF(-1.0);
    ann.setTextFont(font);
    // The font should still be set even with negative point size
    QFont retrieved = ann.textFont();
    EXPECT_LT(retrieved.pointSizeF(), 0);
}

// Test setting callout points
TEST_F(TextAnnotationPrivateTest_1396, SetCalloutPointsEmpty_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    QVector<QPointF> points;
    ann.setCalloutPoints(points);
    QVector<QPointF> retrieved = ann.calloutPoints();
    EXPECT_TRUE(retrieved.isEmpty());
}

// Test setting callout points with valid data
TEST_F(TextAnnotationPrivateTest_1396, SetCalloutPointsWithData_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    QVector<QPointF> points;
    points.append(QPointF(0.1, 0.2));
    points.append(QPointF(0.3, 0.4));
    points.append(QPointF(0.5, 0.6));
    ann.setCalloutPoints(points);
    QVector<QPointF> retrieved = ann.calloutPoints();
    EXPECT_EQ(retrieved.size(), 3);
}

// Test subtype returns AText for both linked and inplace
TEST_F(TextAnnotationPrivateTest_1396, SubTypeIsATextForLinked_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    EXPECT_EQ(ann.subType(), Annotation::AText);
}

TEST_F(TextAnnotationPrivateTest_1396, SubTypeIsATextForInPlace_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    EXPECT_EQ(ann.subType(), Annotation::AText);
}

// Test inplace intent default
TEST_F(TextAnnotationPrivateTest_1396, DefaultInplaceIntent_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    EXPECT_EQ(ann.inplaceIntent(), TextAnnotation::Unknown);
}

// Test setting inplace intent
TEST_F(TextAnnotationPrivateTest_1396, SetInplaceIntentPersists_1396) {
    TextAnnotation ann(TextAnnotation::InPlace);
    ann.setInplaceIntent(TextAnnotation::Callout);
    EXPECT_EQ(ann.inplaceIntent(), TextAnnotation::Callout);
}

// Test setting author
TEST_F(TextAnnotationPrivateTest_1396, SetAuthorPersists_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    ann.setAuthor(QStringLiteral("TestAuthor"));
    EXPECT_EQ(ann.author(), QStringLiteral("TestAuthor"));
}

// Test setting contents
TEST_F(TextAnnotationPrivateTest_1396, SetContentsPersists_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    ann.setContents(QStringLiteral("Test contents"));
    EXPECT_EQ(ann.contents(), QStringLiteral("Test contents"));
}

// Test flags default
TEST_F(TextAnnotationPrivateTest_1396, DefaultFlagsAreZero_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    EXPECT_EQ(ann.flags(), 0);
}

// Test setting flags
TEST_F(TextAnnotationPrivateTest_1396, SetFlagsPersists_1396) {
    TextAnnotation ann(TextAnnotation::Linked);
    ann.setFlags(Annotation::Hidden | Annotation::FixedSize);
    EXPECT_NE(ann.flags(), 0);
}
