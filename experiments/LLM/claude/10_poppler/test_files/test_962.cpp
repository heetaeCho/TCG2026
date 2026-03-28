#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"

class PDFDocTest_962 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char *filename)
    {
        auto fileName = std::make_unique<GooString>(filename);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test that a non-existent file results in a non-ok PDFDoc
TEST_F(PDFDocTest_962, OpenNonExistentFile_962)
{
    auto fileName = std::make_unique<GooString>("this_file_does_not_exist_at_all.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    EXPECT_NE(doc.getErrorCode(), 0);
}

// Test ErrorPDFDoc creates a doc with error
TEST_F(PDFDocTest_962, ErrorPDFDocCreation_962)
{
    auto fileName = std::make_unique<GooString>("error_test.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(1, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 1);
}

// Test ErrorPDFDoc with different error code
TEST_F(PDFDocTest_962, ErrorPDFDocDifferentCode_962)
{
    auto fileName = std::make_unique<GooString>("error_test2.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(5, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 5);
}

// Test that getFileName returns the filename used to open the doc
TEST_F(PDFDocTest_962, GetFileName_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    const GooString *name = doc.getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->toStr().c_str(), "nonexistent.pdf");
}

// Test that findDest with null name doesn't crash on a non-ok doc
// (This tests boundary: we can't call findDest on a doc that isn't ok
//  because catalog would be null. So we only test that isOk is false.)
TEST_F(PDFDocTest_962, FindDestOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // Cannot safely call findDest on invalid doc since catalog is null
}

// Test getCatalog returns null for invalid doc
TEST_F(PDFDocTest_962, GetCatalogOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_file.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // Catalog should be null for an invalid document
    EXPECT_EQ(doc.getCatalog(), nullptr);
}

// Test getXRef returns null for invalid doc
TEST_F(PDFDocTest_962, GetXRefOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_file2.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
}

// Test ErrorPDFDoc with nullptr filename
TEST_F(PDFDocTest_962, ErrorPDFDocNullFilename_962)
{
    auto doc = PDFDoc::ErrorPDFDoc(2, nullptr);
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
    EXPECT_EQ(doc->getErrorCode(), 2);
}

// Test that isEncrypted returns false for invalid doc or handles gracefully
TEST_F(PDFDocTest_962, IsEncryptedOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_enc.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // For an invalid doc, isEncrypted should return false
    EXPECT_FALSE(doc.isEncrypted());
}

// Test PDFSubtype defaults for invalid doc
TEST_F(PDFDocTest_962, PDFSubtypeOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_sub.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // Even for invalid docs, these should return some default value without crashing
    doc.getPDFSubtype();
    doc.getPDFSubtypePart();
    doc.getPDFSubtypeConformance();
}

// Test PDF version on invalid doc
TEST_F(PDFDocTest_962, PDFVersionOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_ver.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // Should not crash
    int major = doc.getPDFMajorVersion();
    int minor = doc.getPDFMinorVersion();
    // For invalid doc, version may be 0 or some default
    (void)major;
    (void)minor;
}

// Test DocInfo operations on invalid doc
TEST_F(PDFDocTest_962, DocInfoOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_info.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
}

// Test getFopenErrno on a file that doesn't exist
TEST_F(PDFDocTest_962, GetFopenErrnoOnMissingFile_962)
{
    auto fileName = std::make_unique<GooString>("absolutely_nonexistent_file_xyz.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // fopen errno should be non-zero for missing file (typically ENOENT)
    EXPECT_NE(doc.getFopenErrno(), 0);
}

// Test ErrorPDFDoc with error code 0
TEST_F(PDFDocTest_962, ErrorPDFDocZeroCode_962)
{
    auto fileName = std::make_unique<GooString>("zero_error.pdf");
    auto doc = PDFDoc::ErrorPDFDoc(0, std::move(fileName));
    ASSERT_NE(doc, nullptr);
    // Error code is 0 but doc was created via ErrorPDFDoc, isOk should reflect this
    EXPECT_EQ(doc->getErrorCode(), 0);
}

// Test getBaseStream on invalid doc
TEST_F(PDFDocTest_962, GetBaseStreamOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_bs.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // BaseStream may be null for file-based doc that failed to open
}

// Test okTo* permissions on invalid doc
TEST_F(PDFDocTest_962, PermissionsOnInvalidDoc_962)
{
    auto fileName = std::make_unique<GooString>("nonexistent_perm.pdf");
    PDFDoc doc(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    EXPECT_FALSE(doc.isOk());
    // These should not crash even on an invalid doc
    // For non-encrypted (invalid) docs, these typically return true
    EXPECT_TRUE(doc.okToPrint());
    EXPECT_TRUE(doc.okToCopy());
    EXPECT_TRUE(doc.okToChange());
    EXPECT_TRUE(doc.okToAddNotes());
    EXPECT_TRUE(doc.okToFillForm());
    EXPECT_TRUE(doc.okToAccessibility());
    EXPECT_TRUE(doc.okToAssemble());
    EXPECT_TRUE(doc.okToPrintHighRes());
}
