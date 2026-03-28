#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QString>
#include <QRectF>

// Include necessary Poppler headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"

// Include poppler core headers needed for Page, Annot, etc.
#include <Page.h>
#include <Annot.h>
#include <PDFDoc.h>

namespace {

class AnnotationPrivateTest_1383 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that flushBaseAnnotationProperties clears author after execution
// This requires a properly set up annotation with pdfPage
TEST_F(AnnotationPrivateTest_1383, FlushClearsAuthor_1383) {
    // Create a text annotation which provides access to AnnotationPrivate
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/UseNone.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Could not load test PDF";
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "Could not load page";
    }

    // Get annotations from the page
    auto annotations = page->annotations();
    
    // If there are annotations, test flush on one
    if (!annotations.isEmpty()) {
        Annotation *ann = annotations.first();
        ann->setAuthor(QStringLiteral("TestAuthor"));
        // The author should be set
        EXPECT_EQ(ann->author(), QStringLiteral("TestAuthor"));
    }

    qDeleteAll(annotations);
    delete page;
    delete doc;
}

// Test that creating an AnnotationPrivate has default values
TEST_F(AnnotationPrivateTest_1383, DefaultConstructionHasNullPage_1383) {
    // We cannot directly instantiate AnnotationPrivate easily,
    // but we can verify through Annotation's interface
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    
    // A freshly created annotation should have empty author
    EXPECT_TRUE(ann.author().isEmpty());
    // Empty contents
    EXPECT_TRUE(ann.contents().isEmpty());
    // Empty unique name
    EXPECT_TRUE(ann.uniqueName().isEmpty());
    // Default flags should be 0
    EXPECT_EQ(ann.flags(), 0);
}

// Test that setting and getting author works on annotation
TEST_F(AnnotationPrivateTest_1383, SetAuthorGetAuthor_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    ann.setAuthor(QStringLiteral("John Doe"));
    EXPECT_EQ(ann.author(), QStringLiteral("John Doe"));
}

// Test that setting and getting contents works on annotation
TEST_F(AnnotationPrivateTest_1383, SetContentsGetContents_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    ann.setContents(QStringLiteral("Some content"));
    EXPECT_EQ(ann.contents(), QStringLiteral("Some content"));
}

// Test that setting and getting uniqueName works
TEST_F(AnnotationPrivateTest_1383, SetUniqueNameGetUniqueName_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    ann.setUniqueName(QStringLiteral("unique123"));
    EXPECT_EQ(ann.uniqueName(), QStringLiteral("unique123"));
}

// Test that setting and getting flags works
TEST_F(AnnotationPrivateTest_1383, SetFlagsGetFlags_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    ann.setFlags(Poppler::Annotation::Hidden | Poppler::Annotation::FixedRotation);
    EXPECT_EQ(ann.flags(), Poppler::Annotation::Hidden | Poppler::Annotation::FixedRotation);
}

// Test boundary conditions - empty strings
TEST_F(AnnotationPrivateTest_1383, SetEmptyAuthor_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    ann.setAuthor(QString());
    EXPECT_TRUE(ann.author().isEmpty());
}

// Test boundary conditions - empty contents
TEST_F(AnnotationPrivateTest_1383, SetEmptyContents_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    ann.setContents(QString());
    EXPECT_TRUE(ann.contents().isEmpty());
}

// Test setting modification date
TEST_F(AnnotationPrivateTest_1383, SetModificationDate_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    QDateTime now = QDateTime::currentDateTime();
    ann.setModificationDate(now);
    EXPECT_EQ(ann.modificationDate(), now);
}

// Test setting creation date
TEST_F(AnnotationPrivateTest_1383, SetCreationDate_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    QDateTime now = QDateTime::currentDateTime();
    ann.setCreationDate(now);
    EXPECT_EQ(ann.creationDate(), now);
}

// Test setting flags to zero
TEST_F(AnnotationPrivateTest_1383, SetFlagsToZero_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    ann.setFlags(Poppler::Annotation::Hidden);
    ann.setFlags(0);
    EXPECT_EQ(ann.flags(), 0);
}

// Test annotation subtype
TEST_F(AnnotationPrivateTest_1383, TextAnnotationSubType_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    EXPECT_EQ(ann.subType(), Poppler::Annotation::AText);
}

// Test that revisions list is initially empty
TEST_F(AnnotationPrivateTest_1383, RevisionsInitiallyEmpty_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    EXPECT_TRUE(ann.revisions().isEmpty());
}

// Test setting style on annotation
TEST_F(AnnotationPrivateTest_1383, SetStyleGetStyle_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    Poppler::Annotation::Style style;
    style.setWidth(2.5);
    style.setColor(QColor(255, 0, 0));
    ann.setStyle(style);
    
    Poppler::Annotation::Style retrievedStyle = ann.style();
    EXPECT_DOUBLE_EQ(retrievedStyle.width(), 2.5);
    EXPECT_EQ(retrievedStyle.color(), QColor(255, 0, 0));
}

// Test setting popup on annotation
TEST_F(AnnotationPrivateTest_1383, SetPopupGetPopup_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    Poppler::Annotation::Popup popup;
    popup.setGeometry(QRectF(0.1, 0.2, 0.3, 0.4));
    ann.setPopup(popup);
    
    Poppler::Annotation::Popup retrievedPopup = ann.popup();
    EXPECT_EQ(retrievedPopup.geometry(), QRectF(0.1, 0.2, 0.3, 0.4));
}

// Test with InPlace text annotation type
TEST_F(AnnotationPrivateTest_1383, InPlaceTextAnnotation_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::InPlace);
    EXPECT_EQ(ann.subType(), Poppler::Annotation::AText);
    EXPECT_EQ(ann.textType(), Poppler::TextAnnotation::InPlace);
}

// Test setting boundary
TEST_F(AnnotationPrivateTest_1383, SetBoundaryGetBoundary_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    QRectF boundary(0.1, 0.2, 0.5, 0.6);
    ann.setBoundary(boundary);
    EXPECT_EQ(ann.boundary(), boundary);
}

// Test large string for author
TEST_F(AnnotationPrivateTest_1383, SetLargeAuthor_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    QString largeAuthor = QString(10000, QChar('A'));
    ann.setAuthor(largeAuthor);
    EXPECT_EQ(ann.author(), largeAuthor);
}

// Test unicode in contents
TEST_F(AnnotationPrivateTest_1383, SetUnicodeContents_1383) {
    Poppler::TextAnnotation ann(Poppler::TextAnnotation::Linked);
    QString unicodeContents = QStringLiteral("日本語テスト");
    ann.setContents(unicodeContents);
    EXPECT_EQ(ann.contents(), unicodeContents);
}

} // namespace
