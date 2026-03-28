#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"

// Since Gfx8BitFont has a complex constructor requiring XRef, Dict, etc.,
// and we cannot easily construct one in isolation without the full Poppler
// infrastructure, we test what we can through the public interface.
// 
// However, given the constraints that we cannot re-implement internal logic
// and must treat the implementation as a black box, we focus on testing
// the accessor methods that are available through the interface.
//
// For meaningful tests, we need to work with the actual Poppler types.
// We include necessary headers to construct test objects where possible.

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "Dict.h"
#include "XRef.h"
#include <memory>
#include <cstring>

class Gfx8BitFontTest_1165 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that we can load a PDF with a Type1 font and check getHasEncoding
TEST_F(Gfx8BitFontTest_1165, GetHasEncodingReturnsBool_1165)
{
    // We test the accessor method getHasEncoding() which returns a bool.
    // Since we can't easily construct a Gfx8BitFont without a valid PDF,
    // we test through loading a document if available, or verify the
    // interface contract.
    
    // Create a minimal PDF in memory to test font loading
    // This is a minimal valid PDF with a Type1 font
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica"
        "/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000407 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n503\n%%EOF\n";

    // Try to create a PDFDoc from the data
    // We'll use a file-based approach or GooString-based approach
    // depending on what's available
    
    // For this test, we verify the method signature and return type
    // by using a real PDF document
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Cannot create temporary file for test";
    }
    
    size_t len = strlen(pdfData);
    fwrite(pdfData, 1, len, tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    // Get file descriptor and create a PDFDoc
    int fd = fileno(tmpFile);
    if (fd < 0) {
        fclose(tmpFile);
        GTEST_SKIP() << "Cannot get file descriptor";
    }
    
    // Duplicate the fd so PDFDoc doesn't close our tmpFile
    int dupFd = dup(fd);
    
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not parse minimal PDF";
    }
    
    // Get the page and its font resources
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not get page";
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not get resources";
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP() << "No Font dictionary in resources";
    }
    
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP() << "F1 font not found";
    }
    
    // Try to create a GfxFont from the font dictionary
    Object fontRef = fontDictObj.dictLookupNF("F1");
    Ref ref = { 4, 0 };
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not create GfxFont";
    }
    
    // Check if it's an 8-bit font (Type1/Helvetica should be)
    if (font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Font is CID, not 8-bit";
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // Helvetica with WinAnsiEncoding should have an encoding
    bool hasEnc = font8->getHasEncoding();
    EXPECT_TRUE(hasEnc) << "Helvetica with WinAnsiEncoding should have encoding set";
    
    fclose(tmpFile);
}

// Test getUsesMacRomanEnc for a font with WinAnsiEncoding
TEST_F(Gfx8BitFontTest_1165, GetUsesMacRomanEncReturnsFalseForWinAnsi_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica"
        "/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000407 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n503\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP() << "Cannot create temporary file";
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP() << "Could not parse PDF";
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // WinAnsiEncoding is not MacRomanEncoding
    EXPECT_FALSE(font8->getUsesMacRomanEnc());
    
    fclose(tmpFile);
}

// Test getWidth returns non-negative values for standard characters
TEST_F(Gfx8BitFontTest_1165, GetWidthReturnsNonNegativeForStandardFont_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000381 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n477\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // For Helvetica (a base14 font), widths should be defined for printable ASCII
    // Character 'A' = 65
    double widthA = font8->getWidth(65);
    EXPECT_GE(widthA, 0.0) << "Width of 'A' should be non-negative";
    
    // Space character = 32
    double widthSpace = font8->getWidth(32);
    EXPECT_GE(widthSpace, 0.0) << "Width of space should be non-negative";
    
    // 'A' should typically be wider than space or at least positive for Helvetica
    EXPECT_GT(widthA, 0.0) << "Width of 'A' in Helvetica should be positive";
    
    fclose(tmpFile);
}

// Test getWidth boundary: character code 0 and 255
TEST_F(Gfx8BitFontTest_1165, GetWidthBoundaryCharCodes_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000381 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n477\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // Test boundary character codes 0 and 255
    double width0 = font8->getWidth(0);
    EXPECT_GE(width0, 0.0) << "Width at code 0 should be non-negative";
    
    double width255 = font8->getWidth(255);
    EXPECT_GE(width255, 0.0) << "Width at code 255 should be non-negative";
    
    fclose(tmpFile);
}

// Test getEncoding returns non-null
TEST_F(Gfx8BitFontTest_1165, GetEncodingReturnsNonNull_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica"
        "/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000407 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n503\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    char **encoding = font8->getEncoding();
    EXPECT_NE(encoding, nullptr) << "getEncoding should return non-null pointer";
    
    fclose(tmpFile);
}

// Test getCharName for a known character code in WinAnsiEncoding
TEST_F(Gfx8BitFontTest_1165, GetCharNameForKnownCode_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica"
        "/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000407 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n503\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // In WinAnsiEncoding, code 65 = 'A'
    const char *charName = font8->getCharName(65);
    if (charName != nullptr) {
        EXPECT_STREQ(charName, "A") << "Character code 65 should map to 'A' in WinAnsiEncoding";
    }
    
    // Code 32 = space
    const char *spaceName = font8->getCharName(32);
    if (spaceName != nullptr) {
        EXPECT_STREQ(spaceName, "space") << "Character code 32 should map to 'space'";
    }
    
    fclose(tmpFile);
}

// Test font without explicit encoding (base14 default)
TEST_F(Gfx8BitFontTest_1165, FontWithoutExplicitEncoding_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000381 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n477\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // Font without explicit Encoding entry should not have hasEncoding set
    // (the default encoding comes from the font program or built-in)
    bool hasEnc = font8->getHasEncoding();
    EXPECT_FALSE(hasEnc) << "Font without explicit Encoding should have hasEncoding=false";
    
    fclose(tmpFile);
}

// Test MacRomanEncoding
TEST_F(Gfx8BitFontTest_1165, FontWithMacRomanEncoding_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica"
        "/Encoding/MacRomanEncoding>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000408 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n504\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    EXPECT_TRUE(font8->getHasEncoding()) << "Font with MacRomanEncoding should have encoding";
    EXPECT_TRUE(font8->getUsesMacRomanEnc()) << "Font with MacRomanEncoding should report usesMacRomanEnc=true";
    
    fclose(tmpFile);
}

// Test getToUnicode returns a valid pointer or null
TEST_F(Gfx8BitFontTest_1165, GetToUnicodeReturnsValidOrNull_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica"
        "/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000407 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n503\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // getToUnicode may return null or a valid pointer - just verify it doesn't crash
    const CharCodeToUnicode *ctu = font8->getToUnicode();
    // For a standard base14 font with WinAnsiEncoding, a ToUnicode mapping
    // is typically synthesized
    // We just check it doesn't crash; the return can be null or non-null
    SUCCEED() << "getToUnicode() did not crash";
    (void)ctu; // suppress unused warning
    
    fclose(tmpFile);
}

// Test multiple width queries across the full range
TEST_F(Gfx8BitFontTest_1165, GetWidthFullRange_1165)
{
    const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R"
        "/Resources<</Font<</F1 4 0 R>>>>"
        "/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Courier>>endobj\n"
        "5 0 obj<</Length 44>>\nstream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000296 00000 n \n"
        "0000000377 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n473\n%%EOF\n";
    
    FILE *tmpFile = tmpfile();
    if (!tmpFile) {
        GTEST_SKIP();
    }
    
    fwrite(pdfData, 1, strlen(pdfData), tmpFile);
    fseek(tmpFile, 0, SEEK_SET);
    
    int dupFd = dup(fileno(tmpFile));
    auto doc = std::make_unique<PDFDoc>(dupFd);
    
    if (!doc->isOk()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Page *page = doc->getPage(1);
    if (!page) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Dict *resources = page->getResourceDict();
    if (!resources) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Object fontDictObj = resources->lookup("Font");
    if (!fontDictObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Ref ref = { 4, 0 };
    Object fontObj = fontDictObj.dictLookup("F1");
    if (!fontObj.isDict()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    std::shared_ptr<GfxFont> font = GfxFont::makeFont(doc->getXRef(), "F1", ref, fontObj.getDict());
    
    if (!font || font->isCIDFont()) {
        fclose(tmpFile);
        GTEST_SKIP();
    }
    
    Gfx8BitFont *font8 = static_cast<Gfx8BitFont *>(font.get());
    
    // Courier is a monospaced font - all defined glyphs should have the same width
    // Query all 256 possible character codes
    for (int i = 0; i < 256; i++) {
        double w = font8->getWidth(static_cast<unsigned char>(i));
        EXPECT_GE(w, 0.0) << "Width at code " << i << " should be non-negative";
    }
    
    // For Courier, printable ASCII characters should all have the same width (0.6)
    double widthA = font8->getWidth('A');
    double widthZ = font8->getWidth('z');
    if (widthA > 0.0 && widthZ > 0.0) {
        EXPECT_DOUBLE_EQ(widthA, widthZ) << "Courier should be monospaced";
    }
    
    fclose(tmpFile);
}
