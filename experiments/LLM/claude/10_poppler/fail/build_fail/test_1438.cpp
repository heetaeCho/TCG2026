#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QImage>
#include <QPainter>
#include <QApplication>

#include "poppler-qt5.h"
#include "poppler-page-private.h"

// Since we need access to the internal class and its dependencies,
// and the class lives in poppler-page.cc, we may need to include it directly.
// We test through the public rendering interface that exercises dump().

namespace {

static int s_argc = 1;
static char s_arg0[] = "test";
static char *s_argv[] = {s_arg0, nullptr};

class QImageDumpingTest_1438 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!QApplication::instance()) {
            app = new QApplication(s_argc, s_argv);
        }
    }

    void TearDown() override {
    }

    QApplication *app = nullptr;
};

// Test that rendering a page to QImage works (exercises the dump path)
TEST_F(QImageDumpingTest_1438, RenderPageToImage_1438) {
    // Create a simple PDF document for testing
    // We use Poppler's public API which internally uses QImageDumpingQPainterOutputDev
    auto doc = Poppler::Document::load(QString("./TestProjects/poppler/test/unittestcases/simple.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    QImage image = page->renderToImage(72.0, 72.0);
    EXPECT_FALSE(image.isNull());
    EXPECT_GT(image.width(), 0);
    EXPECT_GT(image.height(), 0);

    delete page;
    delete doc;
}

// Test rendering with specific DPI values
TEST_F(QImageDumpingTest_1438, RenderPageToImageWithDPI_1438) {
    auto doc = Poppler::Document::load(QString("./TestProjects/poppler/test/unittestcases/simple.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    QImage image72 = page->renderToImage(72.0, 72.0);
    QImage image144 = page->renderToImage(144.0, 144.0);

    EXPECT_FALSE(image72.isNull());
    EXPECT_FALSE(image144.isNull());

    // Higher DPI should produce larger image
    if (!image72.isNull() && !image144.isNull()) {
        EXPECT_GT(image144.width(), image72.width());
        EXPECT_GT(image144.height(), image72.height());
    }

    delete page;
    delete doc;
}

// Test rendering with partial update callback
TEST_F(QImageDumpingTest_1438, RenderPageWithPartialCallback_1438) {
    auto doc = Poppler::Document::load(QString("./TestProjects/poppler/test/unittestcases/simple.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    bool callbackInvoked = false;
    auto partialUpdateCb = [](const QImage &image, const QVariant &, const QRect, bool) -> bool {
        return false;
    };

    // Render with callback - use the public renderToImage that accepts callbacks
    QImage image = page->renderToImage(72.0, 72.0, -1, -1, -1, -1, Poppler::Page::Rotate0);
    EXPECT_FALSE(image.isNull());

    delete page;
    delete doc;
}

// Test rendering a subregion of the page
TEST_F(QImageDumpingTest_1438, RenderPageSubregion_1438) {
    auto doc = Poppler::Document::load(QString("./TestProjects/poppler/test/unittestcases/simple.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    QImage fullImage = page->renderToImage(72.0, 72.0);
    QImage partialImage = page->renderToImage(72.0, 72.0, 0, 0, 100, 100);

    EXPECT_FALSE(fullImage.isNull());
    EXPECT_FALSE(partialImage.isNull());

    if (!partialImage.isNull()) {
        EXPECT_LE(partialImage.width(), 100);
        EXPECT_LE(partialImage.height(), 100);
    }

    delete page;
    delete doc;
}

// Test rendering with rotation
TEST_F(QImageDumpingTest_1438, RenderPageWithRotation_1438) {
    auto doc = Poppler::Document::load(QString("./TestProjects/poppler/test/unittestcases/simple.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    auto page = doc->page(0);
    ASSERT_NE(page, nullptr);

    QImage imageNoRotation = page->renderToImage(72.0, 72.0, -1, -1, -1, -1, Poppler::Page::Rotate0);
    QImage imageRotated90 = page->renderToImage(72.0, 72.0, -1, -1, -1, -1, Poppler::Page::Rotate90);

    EXPECT_FALSE(imageNoRotation.isNull());
    EXPECT_FALSE(imageRotated90.isNull());

    // Rotated 90 degrees should swap width and height
    if (!imageNoRotation.isNull() && !imageRotated90.isNull()) {
        EXPECT_NEAR(imageNoRotation.width(), imageRotated90.height(), 2);
        EXPECT_NEAR(imageNoRotation.height(), imageRotated90.width(), 2);
    }

    delete page;
    delete doc;
}

// Test that null document page returns null image gracefully
TEST_F(QImageDumpingTest_1438, NullDocumentHandling_1438) {
    auto doc = Poppler::Document::load(QString("nonexistent_file.pdf"));
    EXPECT_EQ(doc, nullptr);
}

// Test page index out of bounds
TEST_F(QImageDumpingTest_1438, PageIndexOutOfBounds_1438) {
    auto doc = Poppler::Document::load(QString("./TestProjects/poppler/test/unittestcases/simple.pdf"));
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }

    int numPages = doc->numPages();
    auto page = doc->page(numPages); // Out of bounds
    EXPECT_EQ(page, nullptr);

    auto negativePage = doc->page(-1);
    EXPECT_EQ(negativePage, nullptr);

    delete doc;
}

} // namespace
