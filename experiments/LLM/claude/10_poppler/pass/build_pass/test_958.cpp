#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PDFDocTest_958 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const std::string &filename) {
        auto fileName = std::make_unique<GooString>(filename);
        auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
        return doc;
    }
};

// Test that a non-existent file results in a document that is not ok
TEST_F(PDFDocTest_958, NonExistentFileIsNotOk_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    EXPECT_FALSE(doc->isOk());
}

// Test that error code is non-zero for a failed document
TEST_F(PDFDocTest_958, NonExistentFileHasErrorCode_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    EXPECT_NE(doc->getErrorCode(), 0);
}

// Test ErrorPDFDoc creates a doc with the specified error code
TEST_F(PDFDocTest_958, ErrorPDFDocSetsErrorCode_958) {
    auto fileName = std::make_unique<GooString>("error_doc.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(42, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 42);
}

// Test ErrorPDFDoc stores the filename
TEST_F(PDFDocTest_958, ErrorPDFDocStoresFileName_958) {
    auto fileName = std::make_unique<GooString>("my_error_file.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "my_error_file.pdf");
}

// Test getPageRotate returns 0 for invalid page (null page)
TEST_F(PDFDocTest_958, GetPageRotateReturnsZeroForInvalidPage_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    // Document is not ok, getPage should return nullptr, so getPageRotate returns 0
    int rotate = doc->getPageRotate(1);
    EXPECT_EQ(rotate, 0);
}

// Test getPageRotate returns 0 for out of range page number on invalid doc
TEST_F(PDFDocTest_958, GetPageRotateReturnsZeroForOutOfRangePage_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    int rotate = doc->getPageRotate(0);
    EXPECT_EQ(rotate, 0);
    rotate = doc->getPageRotate(-1);
    EXPECT_EQ(rotate, 0);
    rotate = doc->getPageRotate(9999);
    EXPECT_EQ(rotate, 0);
}

// Test getPage returns nullptr for invalid doc
TEST_F(PDFDocTest_958, GetPageReturnsNullForInvalidDoc_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    EXPECT_EQ(doc->getPage(1), nullptr);
}

// Test getXRef returns nullptr or valid for an error doc
TEST_F(PDFDocTest_958, GetXRefOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    // XRef may be null for error docs
    // Just ensure it doesn't crash
    doc->getXRef();
}

// Test getCatalog on error doc doesn't crash
TEST_F(PDFDocTest_958, GetCatalogOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    doc->getCatalog();
}

// Test getBaseStream on error doc doesn't crash
TEST_F(PDFDocTest_958, GetBaseStreamOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    doc->getBaseStream();
}

// Test getPageMediaWidth returns 0 for invalid page on invalid doc
TEST_F(PDFDocTest_958, GetPageMediaWidthInvalidPage_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    double width = doc->getPageMediaWidth(1);
    EXPECT_EQ(width, 0);
}

// Test getPageMediaHeight returns 0 for invalid page on invalid doc
TEST_F(PDFDocTest_958, GetPageMediaHeightInvalidPage_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    double height = doc->getPageMediaHeight(1);
    EXPECT_EQ(height, 0);
}

// Test getPageCropWidth returns 0 for invalid page on invalid doc
TEST_F(PDFDocTest_958, GetPageCropWidthInvalidPage_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    double width = doc->getPageCropWidth(1);
    EXPECT_EQ(width, 0);
}

// Test getPageCropHeight returns 0 for invalid page on invalid doc
TEST_F(PDFDocTest_958, GetPageCropHeightInvalidPage_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    double height = doc->getPageCropHeight(1);
    EXPECT_EQ(height, 0);
}

// Test isEncrypted on an error doc
TEST_F(PDFDocTest_958, IsEncryptedOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    // Should not crash; encryption status may be false for error doc
    EXPECT_FALSE(doc->isEncrypted());
}

// Test getPDFMajorVersion on error doc
TEST_F(PDFDocTest_958, GetPDFMajorVersionOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    // Just verify it doesn't crash and returns some value
    doc->getPDFMajorVersion();
}

// Test getPDFMinorVersion on error doc
TEST_F(PDFDocTest_958, GetPDFMinorVersionOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    doc->getPDFMinorVersion();
}

// Test that copy constructor is deleted (compile-time check, just document it)
// PDFDoc(const PDFDoc&) = delete; -- cannot be tested at runtime

// Test getFileName on non-existent file returns the filename
TEST_F(PDFDocTest_958, GetFileNameReturnsProvidedName_958) {
    std::string path = "/some/test/path.pdf";
    auto fileName = std::make_unique<GooString>(path);
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    const GooString *name = doc->getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_EQ(std::string(name->c_str()), path);
}

// Test getNumPages on invalid doc - should handle gracefully
TEST_F(PDFDocTest_958, GetNumPagesOnInvalidDoc_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    if (!doc->isOk()) {
        // We just ensure it doesn't crash
        // The result is implementation-defined for invalid docs
        doc->getNumPages();
    }
}

// Test readMetadata on error doc doesn't crash
TEST_F(PDFDocTest_958, ReadMetadataOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    auto metadata = doc->readMetadata();
    // Metadata may be null for error doc
}

// Test getFopenErrno returns a value
TEST_F(PDFDocTest_958, GetFopenErrnoNonExistentFile_958) {
    auto doc = loadTestDoc("/nonexistent/path/to/file.pdf");
    // The errno should be non-zero for a file open failure
    int err = doc->getFopenErrno();
    EXPECT_NE(err, 0);
}

// Test getOutline on error doc doesn't crash
TEST_F(PDFDocTest_958, GetOutlineOnErrorDoc_958) {
    auto fileName = std::make_unique<GooString>("error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    // Should not crash
    doc->getOutline();
}
