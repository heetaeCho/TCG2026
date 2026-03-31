#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QApplication>
#include <QSet>
#include <QList>
#include <QString>
#include <QTemporaryFile>
#include <QFile>
#include <memory>

#include "poppler-qt5.h"
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"

// We need a QApplication for Qt5 poppler
static int argc = 1;
static char *argv[] = { (char*)"test", nullptr };

class FindAnnotationsTest_1390 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!QCoreApplication::instance()) {
            app = new QApplication(argc, argv);
        }
    }

    static void TearDownTestSuite() {
        // Don't delete app - it may be needed
    }

    static QApplication *app;

    // Helper to create a minimal valid PDF with no annotations
    std::unique_ptr<Poppler::Document> createEmptyPdf() {
        // Minimal PDF content
        QByteArray pdfData(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n190\n%%EOF\n"
        );
        return std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(pdfData));
    }

    // Helper to create a PDF with a text annotation
    std::unique_ptr<Poppler::Document> createPdfWithTextAnnotation() {
        QByteArray pdfData(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(Test)>>endobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000198 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n290\n%%EOF\n"
        );
        return std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(pdfData));
    }

    // Helper to create a PDF with a highlight annotation
    std::unique_ptr<Poppler::Document> createPdfWithHighlightAnnotation() {
        QByteArray pdfData(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Highlight/Rect[100 100 200 200]/QuadPoints[100 200 200 200 100 100 200 100]>>endobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000198 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n350\n%%EOF\n"
        );
        return std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(pdfData));
    }

    // Helper to create a PDF with multiple annotation types
    std::unique_ptr<Poppler::Document> createPdfWithMultipleAnnotations() {
        QByteArray pdfData(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R 5 0 R 6 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/Contents(Text Annot)>>endobj\n"
            "5 0 obj<</Type/Annot/Subtype/Highlight/Rect[200 200 300 300]/QuadPoints[200 300 300 300 200 200 300 200]>>endobj\n"
            "6 0 obj<</Type/Annot/Subtype/Stamp/Rect[300 300 400 400]>>endobj\n"
            "xref\n0 7\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000218 00000 n \n"
            "0000000310 00000 n \n"
            "0000000430 00000 n \n"
            "trailer<</Size 7/Root 1 0 R>>\n"
            "startxref\n510\n%%EOF\n"
        );
        return std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(pdfData));
    }

    // Helper to create PDF with ink annotation
    std::unique_ptr<Poppler::Document> createPdfWithInkAnnotation() {
        QByteArray pdfData(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]/Annots[4 0 R]>>endobj\n"
            "4 0 obj<</Type/Annot/Subtype/Ink/Rect[100 100 200 200]/InkList[[100 100 150 150 200 200]]>>endobj\n"
            "xref\n0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000198 00000 n \n"
            "trailer<</Size 5/Root 1 0 R>>\n"
            "startxref\n360\n%%EOF\n"
        );
        return std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(pdfData));
    }
};

QApplication *FindAnnotationsTest_1390::app = nullptr;

// Test: Empty PDF page with no annotations returns empty list
TEST_F(FindAnnotationsTest_1390, NoAnnotationsReturnsEmptyList_1390) {
    auto doc = createEmptyPdf();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QList<Poppler::Annotation *> annotations = page->annotations();
    EXPECT_EQ(annotations.size(), 0);
}

// Test: PDF with a text annotation returns one annotation
TEST_F(FindAnnotationsTest_1390, TextAnnotationFound_1390) {
    auto doc = createPdfWithTextAnnotation();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with text annotation";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QList<Poppler::Annotation *> annotations = page->annotations();
    EXPECT_GE(annotations.size(), 1);

    bool foundText = false;
    for (auto *ann : annotations) {
        if (ann->subType() == Poppler::Annotation::AText) {
            foundText = true;
        }
    }
    EXPECT_TRUE(foundText);

    qDeleteAll(annotations);
}

// Test: Filtering with specific subtype returns only matching annotations
TEST_F(FindAnnotationsTest_1390, FilterBySubtypeText_1390) {
    auto doc = createPdfWithTextAnnotation();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with text annotation";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::AText);
    QList<Poppler::Annotation *> annotations = page->annotations(subtypes);

    for (auto *ann : annotations) {
        EXPECT_EQ(ann->subType(), Poppler::Annotation::AText);
    }

    qDeleteAll(annotations);
}

// Test: Filtering by a subtype that doesn't exist on page returns empty
TEST_F(FindAnnotationsTest_1390, FilterByNonExistentSubtype_1390) {
    auto doc = createPdfWithTextAnnotation();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with text annotation";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::ALine);
    QList<Poppler::Annotation *> annotations = page->annotations(subtypes);

    EXPECT_EQ(annotations.size(), 0);

    qDeleteAll(annotations);
}

// Test: Empty subtype set returns all annotations (no filtering)
TEST_F(FindAnnotationsTest_1390, EmptySubtypeSetReturnsAll_1390) {
    auto doc = createPdfWithMultipleAnnotations();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> emptySubtypes;
    QList<Poppler::Annotation *> allAnnotations = page->annotations(emptySubtypes);
    QList<Poppler::Annotation *> defaultAnnotations = page->annotations();

    // Both should return the same number of annotations
    EXPECT_EQ(allAnnotations.size(), defaultAnnotations.size());

    qDeleteAll(allAnnotations);
    qDeleteAll(defaultAnnotations);
}

// Test: Multiple annotations with specific filtering returns only matching ones
TEST_F(FindAnnotationsTest_1390, FilterMultipleAnnotationsForOneType_1390) {
    auto doc = createPdfWithMultipleAnnotations();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::AStamp);
    QList<Poppler::Annotation *> annotations = page->annotations(subtypes);

    for (auto *ann : annotations) {
        EXPECT_EQ(ann->subType(), Poppler::Annotation::AStamp);
    }

    qDeleteAll(annotations);
}

// Test: Filtering with multiple subtypes returns annotations of those types only
TEST_F(FindAnnotationsTest_1390, FilterByMultipleSubtypes_1390) {
    auto doc = createPdfWithMultipleAnnotations();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::AText);
    subtypes.insert(Poppler::Annotation::AHighlight);
    QList<Poppler::Annotation *> annotations = page->annotations(subtypes);

    for (auto *ann : annotations) {
        EXPECT_TRUE(ann->subType() == Poppler::Annotation::AText ||
                    ann->subType() == Poppler::Annotation::AHighlight);
    }

    qDeleteAll(annotations);
}

// Test: Highlight annotation is correctly identified
TEST_F(FindAnnotationsTest_1390, HighlightAnnotationFound_1390) {
    auto doc = createPdfWithHighlightAnnotation();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with highlight annotation";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::AHighlight);
    QList<Poppler::Annotation *> annotations = page->annotations(subtypes);

    bool foundHighlight = false;
    for (auto *ann : annotations) {
        if (ann->subType() == Poppler::Annotation::AHighlight) {
            foundHighlight = true;
        }
    }
    EXPECT_TRUE(foundHighlight);

    qDeleteAll(annotations);
}

// Test: Ink annotation is correctly identified
TEST_F(FindAnnotationsTest_1390, InkAnnotationFound_1390) {
    auto doc = createPdfWithInkAnnotation();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with ink annotation";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::AInk);
    QList<Poppler::Annotation *> annotations = page->annotations(subtypes);

    for (auto *ann : annotations) {
        EXPECT_EQ(ann->subType(), Poppler::Annotation::AInk);
    }

    qDeleteAll(annotations);
}

// Test: Annotations list count with no filter vs specific filter
TEST_F(FindAnnotationsTest_1390, AllAnnotationsCountGreaterOrEqualFiltered_1390) {
    auto doc = createPdfWithMultipleAnnotations();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QList<Poppler::Annotation *> allAnnotations = page->annotations();

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::AText);
    QList<Poppler::Annotation *> filteredAnnotations = page->annotations(subtypes);

    EXPECT_GE(allAnnotations.size(), filteredAnnotations.size());

    qDeleteAll(allAnnotations);
    qDeleteAll(filteredAnnotations);
}

// Test: Filtering for a subtype not present among multiple types returns empty
TEST_F(FindAnnotationsTest_1390, FilterForAbsentSubtypeInMultiple_1390) {
    auto doc = createPdfWithMultipleAnnotations();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSet<Poppler::Annotation::SubType> subtypes;
    subtypes.insert(Poppler::Annotation::ACaret);
    QList<Poppler::Annotation *> annotations = page->annotations(subtypes);

    EXPECT_EQ(annotations.size(), 0);

    qDeleteAll(annotations);
}

// Test: Returned annotations have valid subType values
TEST_F(FindAnnotationsTest_1390, AnnotationsHaveValidSubType_1390) {
    auto doc = createPdfWithMultipleAnnotations();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QList<Poppler::Annotation *> annotations = page->annotations();

    for (auto *ann : annotations) {
        ASSERT_NE(ann, nullptr);
        Poppler::Annotation::SubType st = ann->subType();
        // subType should be one of the defined enum values
        EXPECT_TRUE(st == Poppler::Annotation::AText ||
                    st == Poppler::Annotation::ALine ||
                    st == Poppler::Annotation::AGeom ||
                    st == Poppler::Annotation::AHighlight ||
                    st == Poppler::Annotation::AStamp ||
                    st == Poppler::Annotation::AInk ||
                    st == Poppler::Annotation::ALink ||
                    st == Poppler::Annotation::ACaret ||
                    st == Poppler::Annotation::AFileAttachment ||
                    st == Poppler::Annotation::ASound ||
                    st == Poppler::Annotation::AMovie ||
                    st == Poppler::Annotation::AScreen ||
                    st == Poppler::Annotation::AWidget ||
                    st == Poppler::Annotation::ARichMedia ||
                    st == Poppler::Annotation::ABase);
    }

    qDeleteAll(annotations);
}

// Test: Text annotation contents match what was set in the PDF
TEST_F(FindAnnotationsTest_1390, TextAnnotationContentsMatch_1390) {
    auto doc = createPdfWithTextAnnotation();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with text annotation";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QList<Poppler::Annotation *> annotations = page->annotations();
    bool foundTextWithContent = false;
    for (auto *ann : annotations) {
        if (ann->subType() == Poppler::Annotation::AText) {
            if (ann->contents() == "Test") {
                foundTextWithContent = true;
            }
        }
    }
    EXPECT_TRUE(foundTextWithContent);

    qDeleteAll(annotations);
}

// Test: Calling annotations() multiple times on same page gives consistent results
TEST_F(FindAnnotationsTest_1390, ConsistentResultsOnMultipleCalls_1390) {
    auto doc = createPdfWithMultipleAnnotations();
    if (!doc) {
        GTEST_SKIP() << "Could not create PDF with multiple annotations";
    }
    ASSERT_GE(doc->numPages(), 1);
    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QList<Poppler::Annotation *> annotations1 = page->annotations();
    QList<Poppler::Annotation *> annotations2 = page->annotations();

    EXPECT_EQ(annotations1.size(), annotations2.size());

    qDeleteAll(annotations1);
    qDeleteAll(annotations2);
}
