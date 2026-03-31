#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QString>
#include <QImage>

// Poppler Qt5 headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"

#include "Page.h"
#include "PDFDoc.h"
#include "Annot.h"

namespace {

class StampAnnotationTest_1404 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that a default-constructed StampAnnotation has the default icon name "Draft"
TEST_F(StampAnnotationTest_1404, DefaultStampIconName_1404) {
    Poppler::StampAnnotation annot;
    EXPECT_EQ(annot.stampIconName(), QStringLiteral("Draft"));
}

// Test that setStampIconName changes the icon name
TEST_F(StampAnnotationTest_1404, SetStampIconName_1404) {
    Poppler::StampAnnotation annot;
    annot.setStampIconName(QStringLiteral("Approved"));
    EXPECT_EQ(annot.stampIconName(), QStringLiteral("Approved"));
}

// Test setting icon name to empty string
TEST_F(StampAnnotationTest_1404, SetStampIconNameEmpty_1404) {
    Poppler::StampAnnotation annot;
    annot.setStampIconName(QStringLiteral(""));
    EXPECT_EQ(annot.stampIconName(), QStringLiteral(""));
}

// Test that subType returns AStamp
TEST_F(StampAnnotationTest_1404, SubTypeIsStamp_1404) {
    Poppler::StampAnnotation annot;
    EXPECT_EQ(annot.subType(), Poppler::Annotation::AStamp);
}

// Test setting and getting custom image
TEST_F(StampAnnotationTest_1404, SetAndGetCustomImage_1404) {
    Poppler::StampAnnotation annot;
    QImage img(100, 100, QImage::Format_ARGB32);
    img.fill(Qt::red);
    annot.setStampCustomImage(img);
    QImage retrieved = annot.stampCustomImage();
    EXPECT_EQ(retrieved.width(), 100);
    EXPECT_EQ(retrieved.height(), 100);
}

// Test setting custom image to null image
TEST_F(StampAnnotationTest_1404, SetNullCustomImage_1404) {
    Poppler::StampAnnotation annot;
    QImage nullImg;
    annot.setStampCustomImage(nullImg);
    QImage retrieved = annot.stampCustomImage();
    EXPECT_TRUE(retrieved.isNull());
}

// Test that multiple icon name changes work correctly
TEST_F(StampAnnotationTest_1404, MultipleIconNameChanges_1404) {
    Poppler::StampAnnotation annot;
    annot.setStampIconName(QStringLiteral("Approved"));
    EXPECT_EQ(annot.stampIconName(), QStringLiteral("Approved"));
    annot.setStampIconName(QStringLiteral("Confidential"));
    EXPECT_EQ(annot.stampIconName(), QStringLiteral("Confidential"));
    annot.setStampIconName(QStringLiteral("Draft"));
    EXPECT_EQ(annot.stampIconName(), QStringLiteral("Draft"));
}

// Test boundary setting on annotation
TEST_F(StampAnnotationTest_1404, SetBoundary_1404) {
    Poppler::StampAnnotation annot;
    QRectF rect(0.1, 0.2, 0.3, 0.4);
    annot.setBoundary(rect);
    QRectF retrieved = annot.boundary();
    EXPECT_DOUBLE_EQ(retrieved.x(), 0.1);
    EXPECT_DOUBLE_EQ(retrieved.y(), 0.2);
    EXPECT_DOUBLE_EQ(retrieved.width(), 0.3);
    EXPECT_DOUBLE_EQ(retrieved.height(), 0.4);
}

// Test default boundary
TEST_F(StampAnnotationTest_1404, DefaultBoundary_1404) {
    Poppler::StampAnnotation annot;
    QRectF boundary = annot.boundary();
    // Default boundary should be a null/empty rect
    EXPECT_TRUE(boundary.isNull() || boundary.isEmpty() || (boundary.width() == 0 && boundary.height() == 0));
}

// Test setting author on stamp annotation
TEST_F(StampAnnotationTest_1404, SetAuthor_1404) {
    Poppler::StampAnnotation annot;
    annot.setAuthor(QStringLiteral("TestAuthor"));
    EXPECT_EQ(annot.author(), QStringLiteral("TestAuthor"));
}

// Test setting contents on stamp annotation
TEST_F(StampAnnotationTest_1404, SetContents_1404) {
    Poppler::StampAnnotation annot;
    annot.setContents(QStringLiteral("Test contents"));
    EXPECT_EQ(annot.contents(), QStringLiteral("Test contents"));
}

// Test flags default
TEST_F(StampAnnotationTest_1404, DefaultFlags_1404) {
    Poppler::StampAnnotation annot;
    EXPECT_EQ(annot.flags(), 0);
}

// Test setting flags
TEST_F(StampAnnotationTest_1404, SetFlags_1404) {
    Poppler::StampAnnotation annot;
    annot.setFlags(Poppler::Annotation::Hidden);
    EXPECT_EQ(annot.flags(), static_cast<int>(Poppler::Annotation::Hidden));
}

// Test StampAnnotationPrivate default construction
TEST_F(StampAnnotationTest_1404, PrivateDefaultIconName_1404) {
    Poppler::StampAnnotation annot;
    // The private member stampIconName defaults to "Draft"
    EXPECT_EQ(annot.stampIconName(), QStringLiteral("Draft"));
}

// Test setting a custom image with specific format
TEST_F(StampAnnotationTest_1404, CustomImageWithFormat_1404) {
    Poppler::StampAnnotation annot;
    QImage img(50, 75, QImage::Format_RGB32);
    img.fill(Qt::blue);
    annot.setStampCustomImage(img);
    QImage retrieved = annot.stampCustomImage();
    EXPECT_EQ(retrieved.width(), 50);
    EXPECT_EQ(retrieved.height(), 75);
}

// Test setting unique name
TEST_F(StampAnnotationTest_1404, SetUniqueName_1404) {
    Poppler::StampAnnotation annot;
    annot.setUniqueName(QStringLiteral("unique-stamp-001"));
    EXPECT_EQ(annot.uniqueName(), QStringLiteral("unique-stamp-001"));
}

} // namespace
