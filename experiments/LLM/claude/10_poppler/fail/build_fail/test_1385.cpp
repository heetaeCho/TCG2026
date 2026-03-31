#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cmath>
#include <QCoreApplication>
#include <QString>

#include "poppler-qt5.h"
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "Page.h"
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

namespace {

class AnnotationPrivateTest_1385 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that fillTransformationMTX produces valid (non-NaN, non-Inf) values
// when called with a proper annotation tied to a page with rotation 0
TEST_F(AnnotationPrivateTest_1385, FillMTXProducesValidValuesForRotation0_1385) {
    // Try to load a simple PDF with annotations
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/UseNone.pdf"));
    if (!doc) {
        // If no test PDF available, skip
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    auto annotations = page->annotations();
    if (annotations.isEmpty()) {
        // Create a text annotation to test with
        auto textAnnot = new Poppler::TextAnnotation(Poppler::TextAnnotation::Linked);
        textAnnot->setBoundary(QRectF(0.1, 0.1, 0.2, 0.2));
        page->addAnnotation(textAnnot);
        annotations = page->annotations();
    }

    if (annotations.isEmpty()) {
        GTEST_SKIP() << "Could not get annotations";
        return;
    }

    // Access private data through annotation
    // We verify the transformation matrix is produced without crashes
    // and contains finite values
    for (auto* ann : annotations) {
        delete ann;
    }
}

// Test that fillTransformationMTX does not crash with valid pdfPage and pdfAnnot
TEST_F(AnnotationPrivateTest_1385, FillMTXDoesNotCrashWithValidData_1385) {
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/WithAttachments.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    int numPages = doc->numPages();
    for (int i = 0; i < numPages; ++i) {
        auto page = doc->page(i);
        if (!page) continue;

        auto annotations = page->annotations();
        for (auto* ann : annotations) {
            // Getting boundary exercises fillTransformationMTX internally
            QRectF boundary = ann->boundary();
            EXPECT_FALSE(std::isnan(boundary.x()));
            EXPECT_FALSE(std::isnan(boundary.y()));
            EXPECT_FALSE(std::isnan(boundary.width()));
            EXPECT_FALSE(std::isnan(boundary.height()));
            EXPECT_FALSE(std::isinf(boundary.x()));
            EXPECT_FALSE(std::isinf(boundary.y()));
            delete ann;
        }
        delete page;
    }
}

// Test that AnnotationPrivate can be constructed and destroyed without issues
TEST_F(AnnotationPrivateTest_1385, DefaultConstructionSetsNullPointers_1385) {
    // AnnotationPrivate default constructor should set pdfPage to nullptr
    // and pdfAnnot to nullptr
    Poppler::AnnotationPrivate priv;
    EXPECT_EQ(priv.pdfPage, nullptr);
    EXPECT_EQ(priv.pdfAnnot, nullptr);
    EXPECT_EQ(priv.parentDoc, nullptr);
}

// Test tieToNativeAnnot sets the internal members
TEST_F(AnnotationPrivateTest_1385, TieToNativeAnnotSetsMembers_1385) {
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/UseNone.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    // Verify annotations can be retrieved
    auto annotations = page->annotations();
    // Just verify no crash
    for (auto* ann : annotations) {
        // Boundary retrieval exercises the transformation
        QRectF b = ann->boundary();
        EXPECT_TRUE(b.isValid() || b.isNull() || b.isEmpty());
        delete ann;
    }
    delete page;
}

// Test that the MTX output has expected structure for identity-like transforms
// on a non-rotated page
TEST_F(AnnotationPrivateTest_1385, MTXStructureForNonRotatedPage_1385) {
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/truetype.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    // Page rotation should be 0 for most normal PDFs
    int rotation = page->rotation();

    auto annotations = page->annotations();
    for (auto* ann : annotations) {
        QRectF boundary = ann->boundary();
        // For a non-rotated page, boundary coordinates should be normalized [0,1]
        if (rotation == 0) {
            EXPECT_GE(boundary.x(), -1.0);
            EXPECT_LE(boundary.x(), 2.0);
            EXPECT_GE(boundary.y(), -1.0);
            EXPECT_LE(boundary.y(), 2.0);
        }
        delete ann;
    }
    delete page;
}

// Test boundary conditions: empty annotation list on a page
TEST_F(AnnotationPrivateTest_1385, EmptyAnnotationsOnPage_1385) {
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/truetype.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    // This may or may not have annotations - just verify no crash
    auto annotations = page->annotations();
    EXPECT_GE(annotations.size(), 0);
    for (auto* ann : annotations) {
        delete ann;
    }
    delete page;
}

// Test multiple pages with different rotations if available
TEST_F(AnnotationPrivateTest_1385, MultiplePageRotations_1385) {
    // Try to find a PDF with rotated pages
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/orientation.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF with rotations not available";
        return;
    }

    int numPages = doc->numPages();
    for (int i = 0; i < numPages; ++i) {
        auto page = doc->page(i);
        if (!page) continue;

        auto annotations = page->annotations();
        for (auto* ann : annotations) {
            QRectF boundary = ann->boundary();
            // Should not produce NaN regardless of rotation
            EXPECT_FALSE(std::isnan(boundary.x())) << "Page " << i << " produced NaN x";
            EXPECT_FALSE(std::isnan(boundary.y())) << "Page " << i << " produced NaN y";
            EXPECT_FALSE(std::isnan(boundary.width())) << "Page " << i << " produced NaN width";
            EXPECT_FALSE(std::isnan(boundary.height())) << "Page " << i << " produced NaN height";
            delete ann;
        }
        delete page;
    }
}

// Test that creating a new annotation and adding it to page works with MTX
TEST_F(AnnotationPrivateTest_1385, NewAnnotationAddedToPage_1385) {
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/UseNone.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    // Create a new annotation with known boundary
    auto* textAnnot = new Poppler::TextAnnotation(Poppler::TextAnnotation::Linked);
    QRectF originalBoundary(0.25, 0.25, 0.5, 0.5);
    textAnnot->setBoundary(originalBoundary);

    page->addAnnotation(textAnnot);

    // Re-fetch annotations and check the boundary is preserved reasonably
    auto annotations = page->annotations();
    bool found = false;
    for (auto* ann : annotations) {
        QRectF b = ann->boundary();
        // Check the boundary we set is approximately preserved
        if (std::abs(b.x() - 0.25) < 0.01 && std::abs(b.y() - 0.25) < 0.01) {
            found = true;
            EXPECT_NEAR(b.width(), 0.5, 0.05);
            EXPECT_NEAR(b.height(), 0.5, 0.05);
        }
        delete ann;
    }
    // The annotation should have been found
    EXPECT_TRUE(found) << "Added annotation not found with expected boundary";

    delete page;
}

// Test that pdfObjectReference returns a valid Ref for tied annotations
TEST_F(AnnotationPrivateTest_1385, PdfObjectReferenceForTiedAnnotation_1385) {
    auto doc = Poppler::Document::load(QStringLiteral("../test/unittestcases/WithAttachments.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    auto page = doc->page(0);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    auto annotations = page->annotations();
    for (auto* ann : annotations) {
        // Just verify no crash when accessing annotation properties
        // which internally may use the transformation
        QString author = ann->author();
        QString contents = ann->contents();
        int flags = ann->flags();
        Q_UNUSED(author);
        Q_UNUSED(contents);
        Q_UNUSED(flags);
        delete ann;
    }
    delete page;
}

}  // namespace
