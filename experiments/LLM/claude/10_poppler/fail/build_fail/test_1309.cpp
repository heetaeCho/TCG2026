#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers from the poppler project
#include "PSOutputDev.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <memory>

// Helper: output function that writes to a std::string buffer
static void stringOutputFunc(void *stream, const char *data, size_t len) {
    std::string *s = static_cast<std::string *>(stream);
    s->append(data, len);
}

class PSOutputDevTest_1309 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We'll create a minimal valid PDF in memory for testing purposes
        // For tests that don't need a full PDF pipeline, we may skip construction
    }

    void TearDown() override {
    }
};

// Test that setPSShrinkLarger sets the value correctly
// We can indirectly verify by calling the setter without crash
TEST_F(PSOutputDevTest_1309, SetPSShrinkLargerTrue_1309) {
    // Create a minimal PDF document to pass to PSOutputDev
    // Use a simple one-page PDF
    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    // Write to temp file
    FILE *tmpFile = tmpfile();
    ASSERT_NE(tmpFile, nullptr);
    fwrite(pdfContent.c_str(), 1, pdfContent.size(), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);

    // Create PDFDoc from the file descriptor
    int fd = fileno(tmpFile);
    // We need a file-based approach; let's use a temp filename instead
    fclose(tmpFile);

    char tmpName[] = "/tmp/psoutputdev_test_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);
    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setPSShrinkLarger(true);
        // No crash means setter works
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetPSShrinkLargerFalse_1309) {
    char tmpName[] = "/tmp/psoutputdev_test2_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setPSShrinkLarger(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetPSExpandSmaller_1309) {
    char tmpName[] = "/tmp/psoutputdev_test3_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setPSExpandSmaller(true);
        psOut->setPSExpandSmaller(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetPSCenter_1309) {
    char tmpName[] = "/tmp/psoutputdev_test4_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setPSCenter(true);
        psOut->setPSCenter(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetEmbedType1_1309) {
    char tmpName[] = "/tmp/psoutputdev_test5_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());

        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetEmbedTrueType_1309) {
    char tmpName[] = "/tmp/psoutputdev_test6_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEmbedTrueType(true);
        EXPECT_TRUE(psOut->getEmbedTrueType());

        psOut->setEmbedTrueType(false);
        EXPECT_FALSE(psOut->getEmbedTrueType());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetEmbedCIDPostScript_1309) {
    char tmpName[] = "/tmp/psoutputdev_test7_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEmbedCIDPostScript(true);
        EXPECT_TRUE(psOut->getEmbedCIDPostScript());

        psOut->setEmbedCIDPostScript(false);
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetEmbedCIDTrueType_1309) {
    char tmpName[] = "/tmp/psoutputdev_test8_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEmbedCIDTrueType(true);
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());

        psOut->setEmbedCIDTrueType(false);
        EXPECT_FALSE(psOut->getEmbedCIDTrueType());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetFontPassthrough_1309) {
    char tmpName[] = "/tmp/psoutputdev_test9_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setFontPassthrough(true);
        EXPECT_TRUE(psOut->getFontPassthrough());

        psOut->setFontPassthrough(false);
        EXPECT_FALSE(psOut->getFontPassthrough());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetOptimizeColorSpace_1309) {
    char tmpName[] = "/tmp/psoutputdev_test10_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setOptimizeColorSpace(true);
        EXPECT_TRUE(psOut->getOptimizeColorSpace());

        psOut->setOptimizeColorSpace(false);
        EXPECT_FALSE(psOut->getOptimizeColorSpace());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetEnableLZW_1309) {
    char tmpName[] = "/tmp/psoutputdev_test11_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEnableLZW(true);
        EXPECT_TRUE(psOut->getEnableLZW());

        psOut->setEnableLZW(false);
        EXPECT_FALSE(psOut->getEnableLZW());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetEnableFlate_1309) {
    char tmpName[] = "/tmp/psoutputdev_test12_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setEnableFlate(true);
        EXPECT_TRUE(psOut->getEnableFlate());

        psOut->setEnableFlate(false);
        EXPECT_FALSE(psOut->getEnableFlate());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, GetSetPassLevel1CustomColor_1309) {
    char tmpName[] = "/tmp/psoutputdev_test13_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setPassLevel1CustomColor(true);
        EXPECT_TRUE(psOut->getPassLevel1CustomColor());

        psOut->setPassLevel1CustomColor(false);
        EXPECT_FALSE(psOut->getPassLevel1CustomColor());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, UpsideDownReturnsFalse_1309) {
    char tmpName[] = "/tmp/psoutputdev_test14_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // PostScript coordinate system is not upside down
        EXPECT_FALSE(psOut->upsideDown());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, UseDrawCharReturnsExpected_1309) {
    char tmpName[] = "/tmp/psoutputdev_test15_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // PSOutputDev uses drawString, not drawChar
        EXPECT_FALSE(psOut->useDrawChar());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetDisplayText_1309) {
    char tmpName[] = "/tmp/psoutputdev_test16_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setDisplayText(true);
        psOut->setDisplayText(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetOverprintPreview_1309) {
    char tmpName[] = "/tmp/psoutputdev_test17_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setOverprintPreview(true);
        psOut->setOverprintPreview(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetOffsetAndScale_1309) {
    char tmpName[] = "/tmp/psoutputdev_test18_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setOffset(10.0, 20.0);
        psOut->setScale(1.5, 2.0);
        psOut->setRotate(90);
        psOut->setClip(0.0, 0.0, 612.0, 792.0);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetRasterResolution_1309) {
    char tmpName[] = "/tmp/psoutputdev_test19_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setRasterResolution(300.0);
        psOut->setRasterResolution(72.0);
        psOut->setRasterAntialias(true);
        psOut->setRasterAntialias(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetUncompressPreloadedImages_1309) {
    char tmpName[] = "/tmp/psoutputdev_test20_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setUncompressPreloadedImages(true);
        psOut->setUncompressPreloadedImages(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, IsOkAfterConstruction_1309) {
    char tmpName[] = "/tmp/psoutputdev_test21_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    // With a valid PDF and output function, the device should be ok
    EXPECT_TRUE(psOut->isOk());

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetMultipleOptionsSequentially_1309) {
    char tmpName[] = "/tmp/psoutputdev_test22_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Set multiple options and verify getters
        psOut->setEmbedType1(false);
        psOut->setEmbedTrueType(true);
        psOut->setEmbedCIDPostScript(false);
        psOut->setEmbedCIDTrueType(true);
        psOut->setFontPassthrough(false);
        psOut->setOptimizeColorSpace(true);
        psOut->setEnableLZW(false);
        psOut->setEnableFlate(true);

        EXPECT_FALSE(psOut->getEmbedType1());
        EXPECT_TRUE(psOut->getEmbedTrueType());
        EXPECT_FALSE(psOut->getEmbedCIDPostScript());
        EXPECT_TRUE(psOut->getEmbedCIDTrueType());
        EXPECT_FALSE(psOut->getFontPassthrough());
        EXPECT_TRUE(psOut->getOptimizeColorSpace());
        EXPECT_FALSE(psOut->getEnableLZW());
        EXPECT_TRUE(psOut->getEnableFlate());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetBooleanOptionsToggle_1309) {
    char tmpName[] = "/tmp/psoutputdev_test23_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // Toggle embedType1 multiple times
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
        psOut->setEmbedType1(false);
        EXPECT_FALSE(psOut->getEmbedType1());
        psOut->setEmbedType1(true);
        EXPECT_TRUE(psOut->getEmbedType1());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetForceRasterize_1309) {
    char tmpName[] = "/tmp/psoutputdev_test24_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setForceRasterize(PSForceRasterize::Yes);
        psOut->setForceRasterize(PSForceRasterize::No);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, UseDrawFormReturnsTrue_1309) {
    char tmpName[] = "/tmp/psoutputdev_test25_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->useDrawForm());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, UseTilingPatternFillReturnsTrue_1309) {
    char tmpName[] = "/tmp/psoutputdev_test26_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        EXPECT_TRUE(psOut->useTilingPatternFill());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, InterpretType3CharsReturnsFalse_1309) {
    char tmpName[] = "/tmp/psoutputdev_test27_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        // PSOutputDev typically does not interpret Type 3 chars
        EXPECT_FALSE(psOut->interpretType3Chars());
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetUseASCIIHexAndBinary_1309) {
    char tmpName[] = "/tmp/psoutputdev_test28_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setUseASCIIHex(true);
        psOut->setUseASCIIHex(false);
        psOut->setUseBinary(true);
        psOut->setUseBinary(false);
        SUCCEED();
    }

    unlink(tmpName);
}

TEST_F(PSOutputDevTest_1309, SetGenerateOPIAndPreloadImagesForms_1309) {
    char tmpName[] = "/tmp/psoutputdev_test29_XXXXXX";
    int tmpFd = mkstemp(tmpName);
    ASSERT_GE(tmpFd, 0);

    std::string pdfContent = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
        "0000000058 00000 n \n0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    write(tmpFd, pdfContent.c_str(), pdfContent.size());
    close(tmpFd);

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpName));
    if (!doc->isOk()) {
        unlink(tmpName);
        GTEST_SKIP() << "Could not create test PDF document";
        return;
    }

    std::string output;
    std::vector<int> pages = {1};

    auto psOut = std::make_unique<PSOutputDev>(
        stringOutputFunc, &output, const_cast<char *>("Test"),
        doc.get(), pages, psModePS, 612, 792,
        false, false, 0, 0, 612, 792,
        PSForceRasterize::No, true, nullptr, nullptr, psLevel2);

    if (psOut->isOk()) {
        psOut->setGenerateOPI(true);
        psOut->setGenerateOPI(false);
        psOut->setPreloadImagesForms(true);
        psOut->setPreloadImagesForms(false);
        SUCCEED();
    }

    unlink(tmpName);
}
