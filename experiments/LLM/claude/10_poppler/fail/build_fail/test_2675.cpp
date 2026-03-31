#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "UnicodeMap.h"
#include "Object.h"
#include "Catalog.h"
#include "Page.h"
#include "JSInfo.h"
#include "Error.h"
#include "Stream.h"
#include "GooString.h"

// External globals used by printInfo
extern int firstPage;
extern int lastPage;
extern bool printBoxes;
extern bool isoDates;
extern bool rawDates;

// Forward declaration of the function under test
static void printInfo(PDFDoc *doc, const UnicodeMap *uMap, long long filesize, bool multiPage);

// We need to include the actual implementation
#include "pdfinfo.cc"

class CaptureStdout {
public:
    void start() {
        fflush(stdout);
        old_stdout = dup(fileno(stdout));
        tmpfile_path = std::tmpnam(nullptr);
        freopen(tmpfile_path.c_str(), "w", stdout);
    }

    std::string stop() {
        fflush(stdout);
        dup2(old_stdout, fileno(stdout));
        close(old_stdout);

        std::ifstream ifs(tmpfile_path);
        std::string content((std::istreambuf_iterator<char>(ifs)),
                            std::istreambuf_iterator<char>());
        ifs.close();
        std::remove(tmpfile_path.c_str());
        return content;
    }

private:
    int old_stdout;
    std::string tmpfile_path;
};

// Helper to create a minimal valid PDF in memory
static std::string createMinimalPDF() {
    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
    pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
    pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
    pdf += "xref\n0 4\n";
    
    char buf[32];
    pdf += "0000000000 65535 f \n";
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", 9);
    pdf += buf;
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", 58);
    pdf += buf;
    snprintf(buf, sizeof(buf), "%010d 00000 n \n", 115);
    pdf += buf;
    
    pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    snprintf(buf, sizeof(buf), "%d\n", 192);
    pdf += buf;
    pdf += "%%EOF\n";
    return pdf;
}

static std::unique_ptr<PDFDoc> createTestDoc(const std::string &pdfContent) {
    // Write to temp file
    std::string tmpPath = std::tmpnam(nullptr);
    tmpPath += ".pdf";
    {
        std::ofstream ofs(tmpPath, std::ios::binary);
        ofs.write(pdfContent.data(), pdfContent.size());
    }
    auto fileName = std::make_unique<GooString>(tmpPath.c_str());
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    return doc;
}

class PrintInfoTest_2675 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Reset globals
        firstPage = 1;
        lastPage = 0;
        printBoxes = false;
        isoDates = false;
        rawDates = false;
    }

    CaptureStdout capture;
};

TEST_F(PrintInfoTest_2675, BasicOutputContainsPages_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    
    const UnicodeMap *uMap = globalParams->getTextEncoding();
    
    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();
    
    EXPECT_THAT(output, ::testing::HasSubstr("Pages:"));
    EXPECT_THAT(output, ::testing::HasSubstr("Encrypted:"));
    EXPECT_THAT(output, ::testing::HasSubstr("File size:"));
    EXPECT_THAT(output, ::testing::HasSubstr("PDF version:"));
}

TEST_F(PrintInfoTest_2675, FileSize_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    long long testFileSize = 12345;
    capture.start();
    printInfo(doc.get(), uMap, testFileSize, false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("File size: 12345 bytes"));
}

TEST_F(PrintInfoTest_2675, NotEncrypted_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Encrypted: no"));
}

TEST_F(PrintInfoTest_2675, SinglePageOutput_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    firstPage = 1;
    lastPage = 1;
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    // Single page should use "Page size:" not "Page  1 size:"
    EXPECT_THAT(output, ::testing::HasSubstr("Page size:"));
    EXPECT_THAT(output, ::testing::HasSubstr("Page rot:"));
}

TEST_F(PrintInfoTest_2675, MultiPageFormat_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    firstPage = 1;
    lastPage = 1;
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), true);
    std::string output = capture.stop();

    // Multi page format should include page number
    EXPECT_THAT(output, ::testing::HasSubstr("Page"));
    EXPECT_THAT(output, ::testing::HasSubstr("size:"));
    EXPECT_THAT(output, ::testing::HasSubstr("rot:"));
}

TEST_F(PrintInfoTest_2675, LetterSizePage_2675) {
    std::string pdfData = createMinimalPDF(); // has 612x792 media box
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    firstPage = 1;
    lastPage = 1;
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("(letter)"));
}

TEST_F(PrintInfoTest_2675, CustomMetadataNo_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Custom Metadata:"));
}

TEST_F(PrintInfoTest_2675, MetadataStreamOutput_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Metadata Stream:"));
}

TEST_F(PrintInfoTest_2675, TaggedOutput_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Tagged:"));
    EXPECT_THAT(output, ::testing::HasSubstr("UserProperties:"));
    EXPECT_THAT(output, ::testing::HasSubstr("Suspects:"));
}

TEST_F(PrintInfoTest_2675, FormOutput_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Form:"));
}

TEST_F(PrintInfoTest_2675, JavaScriptOutput_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("JavaScript:"));
}

TEST_F(PrintInfoTest_2675, OptimizedOutput_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Optimized:"));
}

TEST_F(PrintInfoTest_2675, PrintBoxesEnabled_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    firstPage = 1;
    lastPage = 1;
    printBoxes = true;
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("MediaBox:"));
    EXPECT_THAT(output, ::testing::HasSubstr("CropBox:"));
    EXPECT_THAT(output, ::testing::HasSubstr("BleedBox:"));
    EXPECT_THAT(output, ::testing::HasSubstr("TrimBox:"));
    EXPECT_THAT(output, ::testing::HasSubstr("ArtBox:"));
}

TEST_F(PrintInfoTest_2675, ZeroFileSize_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, 0, false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("File size: 0 bytes"));
}

TEST_F(PrintInfoTest_2675, PDFVersionOutput_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("PDF version: 1.4"));
}

TEST_F(PrintInfoTest_2675, NoFormType_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Form: none"));
}

TEST_F(PrintInfoTest_2675, PagesCount_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    capture.start();
    printInfo(doc.get(), uMap, pdfData.size(), false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("Pages: 1"));
}

TEST_F(PrintInfoTest_2675, LargeFileSize_2675) {
    std::string pdfData = createMinimalPDF();
    auto doc = createTestDoc(pdfData);
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    lastPage = doc->getNumPages();
    const UnicodeMap *uMap = globalParams->getTextEncoding();

    long long largeSize = 9999999999LL;
    capture.start();
    printInfo(doc.get(), uMap, largeSize, false);
    std::string output = capture.stop();

    EXPECT_THAT(output, ::testing::HasSubstr("File size: 9999999999 bytes"));
}
