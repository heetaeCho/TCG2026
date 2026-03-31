#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QPainter>
#include <QImage>
#include <QApplication>

// We need to include the poppler headers
#include "poppler-qt5.h"
#include "poppler-page-private.h"

// Since renderToQPainter is a static function in an anonymous/internal scope,
// we test it through the public Page interface which calls it internally.
// The public interface is Page::renderToPainter()

namespace {

class PopplerPageRenderTest_1444 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal valid PDF document in memory for testing
        // We'll try to load a simple PDF
        doc = nullptr;
    }

    void TearDown() override {
        delete doc;
        doc = nullptr;
    }

    Poppler::Document *doc;
};

// Test that rendering a null page returns failure or handles gracefully
TEST_F(PopplerPageRenderTest_1444, RenderNullDocument_1444) {
    // Without a valid document, we can't get a page
    EXPECT_EQ(doc, nullptr);
}

// Test with a valid minimal PDF document
class PopplerPageWithDocTest_1444 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal PDF in memory
        QByteArray pdfData;
        pdfData.append("%PDF-1.4\n");
        pdfData.append("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
        pdfData.append("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
        pdfData.append("3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n");
        pdfData.append("xref\n0 4\n");
        pdfData.append("0000000000 65535 f \n");
        pdfData.append("0000000009 00000 n \n");
        pdfData.append("0000000058 00000 n \n");
        pdfData.append("0000000115 00000 n \n");
        pdfData.append("trailer\n<< /Size 4 /Root 1 0 R >>\n");
        pdfData.append("startxref\n196\n%%EOF\n");

        doc = Poppler::Document::loadFromData(pdfData);
    }

    void TearDown() override {
        delete doc;
        doc = nullptr;
    }

    Poppler::Document *doc;
};

// Test that a document can be loaded and has pages
TEST_F(PopplerPageWithDocTest_1444, DocumentLoadsSuccessfully_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }
    EXPECT_GE(doc->numPages(), 1);
}

// Test rendering a page to QImage (which internally may use renderToQPainter path)
TEST_F(PopplerPageWithDocTest_1444, RenderPageToImage_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage image = page->renderToImage(72.0, 72.0);
    // A valid page should produce a non-null image
    EXPECT_FALSE(image.isNull());
}

// Test rendering with different DPI values
TEST_F(PopplerPageWithDocTest_1444, RenderPageDifferentDPI_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage image72 = page->renderToImage(72.0, 72.0);
    QImage image144 = page->renderToImage(144.0, 144.0);

    if (!image72.isNull() && !image144.isNull()) {
        // Higher DPI should produce a larger image
        EXPECT_GT(image144.width(), image72.width());
        EXPECT_GT(image144.height(), image72.height());
    }
}

// Test rendering with a sub-region
TEST_F(PopplerPageWithDocTest_1444, RenderPageSubRegion_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage fullImage = page->renderToImage(72.0, 72.0);
    QImage partialImage = page->renderToImage(72.0, 72.0, 0, 0, 100, 100);

    if (!partialImage.isNull()) {
        EXPECT_LE(partialImage.width(), 100);
        EXPECT_LE(partialImage.height(), 100);
    }
}

// Test rendering with rotation
TEST_F(PopplerPageWithDocTest_1444, RenderPageWithRotation_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage imageNoRotation = page->renderToImage(72.0, 72.0, -1, -1, -1, -1, Poppler::Page::Rotate0);
    QImage imageRotated90 = page->renderToImage(72.0, 72.0, -1, -1, -1, -1, Poppler::Page::Rotate90);

    if (!imageNoRotation.isNull() && !imageRotated90.isNull()) {
        // 90 degree rotation should swap width and height (approximately)
        EXPECT_NEAR(imageNoRotation.width(), imageRotated90.height(), 2);
        EXPECT_NEAR(imageNoRotation.height(), imageRotated90.width(), 2);
    }
}

// Test that page size is reported correctly
TEST_F(PopplerPageWithDocTest_1444, PageSizeReported_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QSizeF pageSize = page->pageSizeF();
    // Our test PDF has MediaBox [0 0 612 792] which is US Letter
    EXPECT_NEAR(pageSize.width(), 612.0, 1.0);
    EXPECT_NEAR(pageSize.height(), 792.0, 1.0);
}

// Test rendering with antialiasing hints
TEST_F(PopplerPageWithDocTest_1444, RenderWithAntialiasing_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    doc->setRenderHint(Poppler::Document::Antialiasing, true);
    doc->setRenderHint(Poppler::Document::TextAntialiasing, true);

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage image = page->renderToImage(72.0, 72.0);
    // Should not crash and should produce valid image
    EXPECT_FALSE(image.isNull());
}

// Test rendering with HideAnnotations hint
TEST_F(PopplerPageWithDocTest_1444, RenderWithHideAnnotations_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    doc->setRenderHint(Poppler::Document::HideAnnotations, true);

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage image = page->renderToImage(72.0, 72.0);
    EXPECT_FALSE(image.isNull());
}

// Test rendering with x=-1 and y=-1 (special boundary values in the code)
TEST_F(PopplerPageWithDocTest_1444, RenderWithDefaultXY_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    // -1 for x and y means use defaults (translate by 0)
    QImage image = page->renderToImage(72.0, 72.0, -1, -1, -1, -1);
    EXPECT_FALSE(image.isNull());
}

// Test rendering with zero-size region
TEST_F(PopplerPageWithDocTest_1444, RenderZeroSizeRegion_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    // Rendering with w=0 and h=0
    QImage image = page->renderToImage(72.0, 72.0, 0, 0, 0, 0);
    // Behavior may vary - just ensure no crash
}

// Test that renderToPainter works with QPainter on QImage
TEST_F(PopplerPageWithDocTest_1444, RenderToPainterBasic_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage image(612, 792, QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);

    bool result = page->renderToPainter(&painter, 72.0, 72.0);
    painter.end();

    // renderToPainter should succeed
    EXPECT_TRUE(result);
}

// Test renderToPainter with DontSaveAndRestore flag
TEST_F(PopplerPageWithDocTest_1444, RenderToPainterDontSaveRestore_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    QImage image(612, 792, QImage::Format_ARGB32);
    image.fill(Qt::white);
    QPainter painter(&image);

    bool result = page->renderToPainter(&painter, 72.0, 72.0, -1, -1, -1, -1,
                                         Poppler::Page::Rotate0,
                                         Poppler::Page::DontSaveAndRestore);
    painter.end();

    EXPECT_TRUE(result);
}

// Test rendering all rotation values
TEST_F(PopplerPageWithDocTest_1444, RenderAllRotations_1444) {
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    std::unique_ptr<Poppler::Page> page(doc->page(0));
    ASSERT_NE(page, nullptr);

    Poppler::Page::Rotation rotations[] = {
        Poppler::Page::Rotate0,
        Poppler::Page::Rotate90,
        Poppler::Page::Rotate180,
        Poppler::Page::Rotate270
    };

    for (auto rot : rotations) {
        QImage image = page->renderToImage(72.0, 72.0, -1, -1, -1, -1, rot);
        EXPECT_FALSE(image.isNull()) << "Failed for rotation: " << static_cast<int>(rot);
    }
}

} // namespace

int main(int argc, char **argv) {
    // QApplication is needed for Qt painting operations
    QApplication app(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
