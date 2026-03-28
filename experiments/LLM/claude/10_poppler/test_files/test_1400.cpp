#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QColor>
#include <QRectF>

// Include necessary headers
#include "poppler-annotation.h"
#include "poppler-annotation-private.h"
#include "poppler-private.h"
#include "poppler-qt5.h"
#include "Page.h"
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

using namespace Poppler;

class GeomAnnotationTest_1400 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize global params if needed
        globalParams = std::make_unique<GlobalParams>();
    }

    void TearDown() override {
        globalParams.reset();
    }

    // Helper to create a minimal PDF document for testing
    std::unique_ptr<Poppler::Document> createTestDocument() {
        // Create a minimal valid PDF in memory
        QByteArray pdfData(
            "%PDF-1.4\n"
            "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
            "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
            "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer<</Size 4/Root 1 0 R>>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n"
        );
        return std::unique_ptr<Poppler::Document>(Poppler::Document::loadFromData(pdfData));
    }
};

// Test that a GeomAnnotation with InscribedSquare type can be created
TEST_F(GeomAnnotationTest_1400, CreateSquareAnnotation_1400) {
    auto doc = createTestDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    // Create a GeomAnnotation with InscribedSquare
    auto *annot = new Poppler::GeomAnnotation();
    annot->setGeomType(Poppler::GeomAnnotation::InscribedSquare);
    annot->setBoundary(QRectF(0.1, 0.1, 0.5, 0.5));

    // Verify the annotation type
    EXPECT_EQ(annot->subType(), Poppler::Annotation::AGeom);
    EXPECT_EQ(annot->geomType(), Poppler::GeomAnnotation::InscribedSquare);

    delete annot;
    delete page;
}

// Test that a GeomAnnotation with InscribedCircle type can be created
TEST_F(GeomAnnotationTest_1400, CreateCircleAnnotation_1400) {
    auto doc = createTestDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    auto *annot = new Poppler::GeomAnnotation();
    annot->setGeomType(Poppler::GeomAnnotation::InscribedCircle);
    annot->setBoundary(QRectF(0.2, 0.2, 0.6, 0.6));

    EXPECT_EQ(annot->subType(), Poppler::Annotation::AGeom);
    EXPECT_EQ(annot->geomType(), Poppler::GeomAnnotation::InscribedCircle);

    delete annot;
    delete page;
}

// Test setting and getting inner color on a GeomAnnotation
TEST_F(GeomAnnotationTest_1400, SetAndGetGeomInnerColor_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QColor testColor(255, 0, 0);
    annot->setGeomInnerColor(testColor);
    EXPECT_EQ(annot->geomInnerColor(), testColor);

    delete annot;
}

// Test default inner color
TEST_F(GeomAnnotationTest_1400, DefaultGeomInnerColor_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QColor defaultColor = annot->geomInnerColor();
    // Default inner color should be an invalid/default QColor
    EXPECT_FALSE(defaultColor.isValid()) << "Default inner color should be invalid (transparent/unset)";

    delete annot;
}

// Test setting inner color with transparent color
TEST_F(GeomAnnotationTest_1400, SetTransparentInnerColor_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QColor transparentColor(0, 0, 0, 0);
    annot->setGeomInnerColor(transparentColor);
    QColor result = annot->geomInnerColor();
    EXPECT_EQ(result.alpha(), 0);

    delete annot;
}

// Test default geom type
TEST_F(GeomAnnotationTest_1400, DefaultGeomType_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    // Check default geom type - should be InscribedSquare (0)
    Poppler::GeomAnnotation::GeomType gtype = annot->geomType();
    EXPECT_EQ(gtype, Poppler::GeomAnnotation::InscribedSquare);

    delete annot;
}

// Test setting geom type to InscribedCircle
TEST_F(GeomAnnotationTest_1400, SetGeomTypeCircle_1400) {
    auto *annot = new Poppler::GeomAnnotation();
    annot->setGeomType(Poppler::GeomAnnotation::InscribedCircle);

    EXPECT_EQ(annot->geomType(), Poppler::GeomAnnotation::InscribedCircle);

    delete annot;
}

// Test setting geom type to InscribedSquare
TEST_F(GeomAnnotationTest_1400, SetGeomTypeSquare_1400) {
    auto *annot = new Poppler::GeomAnnotation();
    annot->setGeomType(Poppler::GeomAnnotation::InscribedSquare);

    EXPECT_EQ(annot->geomType(), Poppler::GeomAnnotation::InscribedSquare);

    delete annot;
}

// Test boundary setting and retrieval
TEST_F(GeomAnnotationTest_1400, SetBoundary_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QRectF boundary(0.1, 0.2, 0.3, 0.4);
    annot->setBoundary(boundary);

    QRectF result = annot->boundary();
    EXPECT_DOUBLE_EQ(result.x(), 0.1);
    EXPECT_DOUBLE_EQ(result.y(), 0.2);
    EXPECT_DOUBLE_EQ(result.width(), 0.3);
    EXPECT_DOUBLE_EQ(result.height(), 0.4);

    delete annot;
}

// Test annotation subtype
TEST_F(GeomAnnotationTest_1400, SubType_1400) {
    auto *annot = new Poppler::GeomAnnotation();
    EXPECT_EQ(annot->subType(), Poppler::Annotation::AGeom);
    delete annot;
}

// Test boundary at origin
TEST_F(GeomAnnotationTest_1400, BoundaryAtOrigin_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QRectF boundary(0.0, 0.0, 1.0, 1.0);
    annot->setBoundary(boundary);

    QRectF result = annot->boundary();
    EXPECT_DOUBLE_EQ(result.x(), 0.0);
    EXPECT_DOUBLE_EQ(result.y(), 0.0);
    EXPECT_DOUBLE_EQ(result.width(), 1.0);
    EXPECT_DOUBLE_EQ(result.height(), 1.0);

    delete annot;
}

// Test setting various inner colors
TEST_F(GeomAnnotationTest_1400, SetBlueInnerColor_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QColor blueColor(0, 0, 255);
    annot->setGeomInnerColor(blueColor);
    QColor result = annot->geomInnerColor();
    EXPECT_EQ(result.red(), 0);
    EXPECT_EQ(result.green(), 0);
    EXPECT_EQ(result.blue(), 255);

    delete annot;
}

// Test adding GeomAnnotation to page via Document API
TEST_F(GeomAnnotationTest_1400, AddAnnotationToPage_1400) {
    auto doc = createTestDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    auto *annot = new Poppler::GeomAnnotation();
    annot->setGeomType(Poppler::GeomAnnotation::InscribedSquare);
    annot->setBoundary(QRectF(0.1, 0.1, 0.3, 0.3));
    annot->setGeomInnerColor(QColor(255, 0, 0));

    // Adding annotation to page triggers createNativeAnnot internally
    page->addAnnotation(annot);

    // After adding, the annotation list should contain the new annotation
    QList<Poppler::Annotation *> annotations = page->annotations();
    bool found = false;
    for (auto *a : annotations) {
        if (a->subType() == Poppler::Annotation::AGeom) {
            found = true;
            auto *geom = static_cast<Poppler::GeomAnnotation *>(a);
            EXPECT_EQ(geom->geomType(), Poppler::GeomAnnotation::InscribedSquare);
        }
        delete a;
    }
    EXPECT_TRUE(found) << "GeomAnnotation should be found on page after adding";

    delete page;
}

// Test adding circle annotation to page
TEST_F(GeomAnnotationTest_1400, AddCircleAnnotationToPage_1400) {
    auto doc = createTestDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    auto *annot = new Poppler::GeomAnnotation();
    annot->setGeomType(Poppler::GeomAnnotation::InscribedCircle);
    annot->setBoundary(QRectF(0.2, 0.2, 0.4, 0.4));

    page->addAnnotation(annot);

    QList<Poppler::Annotation *> annotations = page->annotations();
    bool found = false;
    for (auto *a : annotations) {
        if (a->subType() == Poppler::Annotation::AGeom) {
            auto *geom = static_cast<Poppler::GeomAnnotation *>(a);
            if (geom->geomType() == Poppler::GeomAnnotation::InscribedCircle) {
                found = true;
            }
        }
        delete a;
    }
    EXPECT_TRUE(found) << "Circle GeomAnnotation should be found on page after adding";

    delete page;
}

// Test inner color preservation after adding to page
TEST_F(GeomAnnotationTest_1400, InnerColorPreservedAfterAddToPage_1400) {
    auto doc = createTestDocument();
    if (!doc) {
        GTEST_SKIP() << "Could not create test document";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    auto *annot = new Poppler::GeomAnnotation();
    annot->setGeomType(Poppler::GeomAnnotation::InscribedSquare);
    annot->setBoundary(QRectF(0.1, 0.1, 0.5, 0.5));
    annot->setGeomInnerColor(QColor(0, 255, 0));

    page->addAnnotation(annot);

    QList<Poppler::Annotation *> annotations = page->annotations();
    for (auto *a : annotations) {
        if (a->subType() == Poppler::Annotation::AGeom) {
            auto *geom = static_cast<Poppler::GeomAnnotation *>(a);
            QColor innerColor = geom->geomInnerColor();
            // The inner color should be preserved
            EXPECT_EQ(innerColor.green(), 255);
        }
        delete a;
    }

    delete page;
}

// Test setting inner color to invalid/default QColor
TEST_F(GeomAnnotationTest_1400, SetInvalidInnerColor_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QColor invalidColor;
    annot->setGeomInnerColor(invalidColor);
    QColor result = annot->geomInnerColor();
    EXPECT_FALSE(result.isValid());

    delete annot;
}

// Test multiple geom type changes
TEST_F(GeomAnnotationTest_1400, ChangeGeomType_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    annot->setGeomType(Poppler::GeomAnnotation::InscribedSquare);
    EXPECT_EQ(annot->geomType(), Poppler::GeomAnnotation::InscribedSquare);

    annot->setGeomType(Poppler::GeomAnnotation::InscribedCircle);
    EXPECT_EQ(annot->geomType(), Poppler::GeomAnnotation::InscribedCircle);

    annot->setGeomType(Poppler::GeomAnnotation::InscribedSquare);
    EXPECT_EQ(annot->geomType(), Poppler::GeomAnnotation::InscribedSquare);

    delete annot;
}

// Test very small boundary
TEST_F(GeomAnnotationTest_1400, VerySmallBoundary_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QRectF smallBoundary(0.0, 0.0, 0.001, 0.001);
    annot->setBoundary(smallBoundary);

    QRectF result = annot->boundary();
    EXPECT_NEAR(result.width(), 0.001, 1e-6);
    EXPECT_NEAR(result.height(), 0.001, 1e-6);

    delete annot;
}

// Test full page boundary
TEST_F(GeomAnnotationTest_1400, FullPageBoundary_1400) {
    auto *annot = new Poppler::GeomAnnotation();

    QRectF fullBoundary(0.0, 0.0, 1.0, 1.0);
    annot->setBoundary(fullBoundary);

    QRectF result = annot->boundary();
    EXPECT_DOUBLE_EQ(result.width(), 1.0);
    EXPECT_DOUBLE_EQ(result.height(), 1.0);

    delete annot;
}
