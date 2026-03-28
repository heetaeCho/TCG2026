#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>

// We need to test the static function cvtUserToDev which is file-local.
// Since Page is a complex class, we'll create a minimal mock setup.

#include "poppler/PDFDoc.h"
#include "poppler/Page.h"

// Include the source to access the static function
// We need to declare it or use a workaround

// Since cvtUserToDev is static in the .cc file, we need to include it
// or replicate access. We'll test through the actual source inclusion.

namespace {

// Forward-declare or re-expose the function for testing.
// We include the .cc file to get access to the static function.
}

// We'll define our own test wrapper since the function is static in the .cc
// We replicate the pure computation logic test since we can't easily mock Page
// without the full poppler infrastructure. Instead, we test with real Page objects
// via PDFDoc if possible, or test the math directly.

// Since we need to test the actual function and it requires a real Page object,
// let's try to create a minimal PDF in memory and test with it.

#include "poppler/GlobalParams.h"
#include "poppler/PDFDoc.h"
#include "poppler/Page.h"

#include <memory>
#include <cstring>

// Re-declare the function signature to test it - include the .cc
// The function is static so we need to include the implementation file
#define private public
#define protected public
#include "qt5/src/poppler-link.cc"
#undef private
#undef protected

class CvtUserToDevTest_1251 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test with a simple identity-like CTM
// Since we can't easily mock Page, we test with known PDF pages
// However, we can test the mathematical formula directly

// Test: verify the function exists and compiles with proper types
TEST_F(CvtUserToDevTest_1251, BasicComputation_1251) {
    // Load a simple PDF to get a Page object
    // Create a minimal PDF in memory
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        int xd = 0, yd = 0;
        // Call the function with origin (0,0)
        Poppler::cvtUserToDev(page, 0.0, 0.0, &xd, &yd);

        // With (0,0) input, result should be (int)(ctm[4]+0.5), (int)(ctm[5]+0.5)
        double ctm[6];
        page->getDefaultCTM(ctm, 72.0, 72.0, 0, false, true);
        int expectedX = (int)(ctm[4] + 0.5);
        int expectedY = (int)(ctm[5] + 0.5);

        EXPECT_EQ(xd, expectedX);
        EXPECT_EQ(yd, expectedY);
    }
}

TEST_F(CvtUserToDevTest_1251, NonZeroCoordinates_1251) {
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        double xu = 100.0, yu = 200.0;
        int xd = 0, yd = 0;
        Poppler::cvtUserToDev(page, xu, yu, &xd, &yd);

        double ctm[6];
        page->getDefaultCTM(ctm, 72.0, 72.0, 0, false, true);
        int expectedX = (int)(ctm[0] * xu + ctm[2] * yu + ctm[4] + 0.5);
        int expectedY = (int)(ctm[1] * xu + ctm[3] * yu + ctm[5] + 0.5);

        EXPECT_EQ(xd, expectedX);
        EXPECT_EQ(yd, expectedY);
    }
}

TEST_F(CvtUserToDevTest_1251, NegativeCoordinates_1251) {
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        double xu = -50.0, yu = -75.0;
        int xd = 0, yd = 0;
        Poppler::cvtUserToDev(page, xu, yu, &xd, &yd);

        double ctm[6];
        page->getDefaultCTM(ctm, 72.0, 72.0, 0, false, true);
        int expectedX = (int)(ctm[0] * xu + ctm[2] * yu + ctm[4] + 0.5);
        int expectedY = (int)(ctm[1] * xu + ctm[3] * yu + ctm[5] + 0.5);

        EXPECT_EQ(xd, expectedX);
        EXPECT_EQ(yd, expectedY);
    }
}

TEST_F(CvtUserToDevTest_1251, LargeCoordinates_1251) {
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        double xu = 10000.0, yu = 10000.0;
        int xd = 0, yd = 0;
        Poppler::cvtUserToDev(page, xu, yu, &xd, &yd);

        double ctm[6];
        page->getDefaultCTM(ctm, 72.0, 72.0, 0, false, true);
        int expectedX = (int)(ctm[0] * xu + ctm[2] * yu + ctm[4] + 0.5);
        int expectedY = (int)(ctm[1] * xu + ctm[3] * yu + ctm[5] + 0.5);

        EXPECT_EQ(xd, expectedX);
        EXPECT_EQ(yd, expectedY);
    }
}

TEST_F(CvtUserToDevTest_1251, ZeroCoordinates_1251) {
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        int xd = -1, yd = -1;
        Poppler::cvtUserToDev(page, 0.0, 0.0, &xd, &yd);

        // Results should be translation components of CTM
        double ctm[6];
        page->getDefaultCTM(ctm, 72.0, 72.0, 0, false, true);

        EXPECT_EQ(xd, (int)(ctm[4] + 0.5));
        EXPECT_EQ(yd, (int)(ctm[5] + 0.5));
    }
}

TEST_F(CvtUserToDevTest_1251, FractionalCoordinates_1251) {
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        double xu = 0.5, yu = 0.5;
        int xd = 0, yd = 0;
        Poppler::cvtUserToDev(page, xu, yu, &xd, &yd);

        double ctm[6];
        page->getDefaultCTM(ctm, 72.0, 72.0, 0, false, true);
        int expectedX = (int)(ctm[0] * xu + ctm[2] * yu + ctm[4] + 0.5);
        int expectedY = (int)(ctm[1] * xu + ctm[3] * yu + ctm[5] + 0.5);

        EXPECT_EQ(xd, expectedX);
        EXPECT_EQ(yd, expectedY);
    }
}

TEST_F(CvtUserToDevTest_1251, PageCornerCoordinates_1251) {
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        // Test with page corner coordinates (612, 792) for US Letter
        double xu = 612.0, yu = 792.0;
        int xd = 0, yd = 0;
        Poppler::cvtUserToDev(page, xu, yu, &xd, &yd);

        double ctm[6];
        page->getDefaultCTM(ctm, 72.0, 72.0, 0, false, true);
        int expectedX = (int)(ctm[0] * xu + ctm[2] * yu + ctm[4] + 0.5);
        int expectedY = (int)(ctm[1] * xu + ctm[3] * yu + ctm[5] + 0.5);

        EXPECT_EQ(xd, expectedX);
        EXPECT_EQ(yd, expectedY);
    }
}

TEST_F(CvtUserToDevTest_1251, ConsistentResults_1251) {
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    size_t len = strlen(pdfData);
    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, len, Object(objNull));
    auto doc = std::make_unique<PDFDoc>(stream);

    if (doc->isOk() && doc->getNumPages() > 0) {
        ::Page *page = doc->getPage(1);
        ASSERT_NE(page, nullptr);

        // Calling twice with same input should give same result
        int xd1 = 0, yd1 = 0, xd2 = 0, yd2 = 0;
        Poppler::cvtUserToDev(page, 300.0, 400.0, &xd1, &yd1);
        Poppler::cvtUserToDev(page, 300.0, 400.0, &xd2, &yd2);

        EXPECT_EQ(xd1, xd2);
        EXPECT_EQ(yd1, yd2);
    }
}
