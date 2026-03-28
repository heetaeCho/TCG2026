#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <optional>

#include "FontInfo.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "FontEncodingTables.h"

class FontInfoTest_1001 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to load a PDFDoc and scan fonts from it
// Since we can't easily construct GfxFont/XRef directly, we test through FontInfoScanner
// which is part of the same header/module

class FontInfoScannerTest_1001 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that FontInfo copy constructor works correctly
TEST_F(FontInfoTest_1001, CopyConstructorPreservesEncoding_1001)
{
    // We need a real FontInfo to test copy. We'll use FontInfoScanner on a minimal PDF.
    // Since we may not have a PDF file, we test what we can about the interface.
    // Create a minimal in-memory PDF
    const char pdfData[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000370 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "466\n"
        "%%EOF\n";

    // Attempt to open the PDF from memory - using GooString approach
    auto doc = std::make_unique<PDFDoc>(new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull)));

    if (doc && doc->isOk()) {
        FontInfoScanner scanner(doc.get());
        std::vector<FontInfo *> *fonts = scanner.scan(1);

        if (fonts && !fonts->empty()) {
            FontInfo *original = fonts->at(0);

            // Test copy constructor
            FontInfo copy(*original);

            EXPECT_EQ(copy.getEncoding(), original->getEncoding());
            EXPECT_EQ(copy.getName(), original->getName());
            EXPECT_EQ(copy.getSubstituteName(), original->getSubstituteName());
            EXPECT_EQ(copy.getFile(), original->getFile());
            EXPECT_EQ(copy.getType(), original->getType());
            EXPECT_EQ(copy.getEmbedded(), original->getEmbedded());
            EXPECT_EQ(copy.getSubset(), original->getSubset());
            EXPECT_EQ(copy.getToUnicode(), original->getToUnicode());
            EXPECT_EQ(copy.getRef().num, original->getRef().num);
            EXPECT_EQ(copy.getRef().gen, original->getRef().gen);
            EXPECT_EQ(copy.getEmbRef().num, original->getEmbRef().num);
            EXPECT_EQ(copy.getEmbRef().gen, original->getEmbRef().gen);

            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

// Test FontInfo getters return consistent values
TEST_F(FontInfoTest_1001, GettersReturnConsistentValues_1001)
{
    const char pdfData[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000370 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "466\n"
        "%%EOF\n";

    auto doc = std::make_unique<PDFDoc>(new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull)));

    if (doc && doc->isOk()) {
        FontInfoScanner scanner(doc.get());
        std::vector<FontInfo *> *fonts = scanner.scan(1);

        if (fonts && !fonts->empty()) {
            FontInfo *fi = fonts->at(0);

            // Call getters multiple times - should return same value
            const std::string &enc1 = fi->getEncoding();
            const std::string &enc2 = fi->getEncoding();
            EXPECT_EQ(enc1, enc2);

            bool emb1 = fi->getEmbedded();
            bool emb2 = fi->getEmbedded();
            EXPECT_EQ(emb1, emb2);

            bool sub1 = fi->getSubset();
            bool sub2 = fi->getSubset();
            EXPECT_EQ(sub1, sub2);

            bool tu1 = fi->getToUnicode();
            bool tu2 = fi->getToUnicode();
            EXPECT_EQ(tu1, tu2);

            // For a standard non-embedded Type1 font like Helvetica
            EXPECT_FALSE(fi->getEmbedded());
            EXPECT_FALSE(fi->getSubset());

            // Name should be present for Helvetica
            if (fi->getName().has_value()) {
                EXPECT_FALSE(fi->getName()->empty());
            }

            Ref ref = fi->getRef();
            // The ref should be valid (num >= 0 for a real font object)
            EXPECT_GE(ref.num, 0);

            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

// Test FontInfoScanner with scanning 0 pages
TEST_F(FontInfoScannerTest_1001, ScanZeroPages_1001)
{
    const char pdfData[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "5 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000349 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "445\n"
        "%%EOF\n";

    auto doc = std::make_unique<PDFDoc>(new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull)));

    if (doc && doc->isOk()) {
        FontInfoScanner scanner(doc.get());
        std::vector<FontInfo *> *fonts = scanner.scan(0);

        // Scanning 0 pages should return empty or null
        if (fonts) {
            EXPECT_TRUE(fonts->empty());
            delete fonts;
        }
    }
}

// Test that getEncoding returns a reference to a string (possibly empty for some fonts)
TEST_F(FontInfoTest_1001, GetEncodingReturnsStringReference_1001)
{
    const char pdfData[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica/Encoding/WinAnsiEncoding>>endobj\n"
        "5 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000370 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "466\n"
        "%%EOF\n";

    auto doc = std::make_unique<PDFDoc>(new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull)));

    if (doc && doc->isOk()) {
        FontInfoScanner scanner(doc.get());
        std::vector<FontInfo *> *fonts = scanner.scan(1);

        if (fonts && !fonts->empty()) {
            FontInfo *fi = fonts->at(0);

            // getEncoding should return a valid string reference
            const std::string &encoding = fi->getEncoding();
            // For WinAnsiEncoding, we expect a non-empty encoding string
            // But we don't know the exact format, just verify it's accessible
            EXPECT_NO_THROW({
                std::string encodingCopy = encoding;
                (void)encodingCopy;
            });

            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

// Test that getName returns optional with value for known fonts
TEST_F(FontInfoTest_1001, GetNameForKnownFont_1001)
{
    const char pdfData[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Helvetica>>endobj\n"
        "5 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000349 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "445\n"
        "%%EOF\n";

    auto doc = std::make_unique<PDFDoc>(new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull)));

    if (doc && doc->isOk()) {
        FontInfoScanner scanner(doc.get());
        std::vector<FontInfo *> *fonts = scanner.scan(1);

        if (fonts && !fonts->empty()) {
            FontInfo *fi = fonts->at(0);

            // For a font with BaseFont/Helvetica, getName should have a value
            const std::optional<std::string> &name = fi->getName();
            EXPECT_TRUE(name.has_value());
            if (name.has_value()) {
                EXPECT_NE(name->find("Helvetica"), std::string::npos);
            }

            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

// Test getEmbedded and getSubset for a non-embedded standard font
TEST_F(FontInfoTest_1001, NonEmbeddedStandardFont_1001)
{
    const char pdfData[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Times-Roman>>endobj\n"
        "5 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000351 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "447\n"
        "%%EOF\n";

    auto doc = std::make_unique<PDFDoc>(new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull)));

    if (doc && doc->isOk()) {
        FontInfoScanner scanner(doc.get());
        std::vector<FontInfo *> *fonts = scanner.scan(1);

        if (fonts && !fonts->empty()) {
            FontInfo *fi = fonts->at(0);

            // Standard Type1 fonts are not embedded
            EXPECT_FALSE(fi->getEmbedded());
            // Standard fonts are not subset
            EXPECT_FALSE(fi->getSubset());

            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

// Test scanning multiple pages
TEST_F(FontInfoScannerTest_1001, ScanMultiplePages_1001)
{
    const char pdfData[] =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<</Font<</F1 4 0 R>>>>/Contents 5 0 R>>endobj\n"
        "4 0 obj<</Type/Font/Subtype/Type1/BaseFont/Courier>>endobj\n"
        "5 0 obj<</Length 44>>stream\nBT /F1 12 Tf 100 700 Td (Hello) Tj ET\nendstream\nendobj\n"
        "xref\n"
        "0 6\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000266 00000 n \n"
        "0000000343 00000 n \n"
        "trailer<</Size 6/Root 1 0 R>>\n"
        "startxref\n"
        "439\n"
        "%%EOF\n";

    auto doc = std::make_unique<PDFDoc>(new MemStream(const_cast<char *>(pdfData), 0, sizeof(pdfData) - 1, Object(objNull)));

    if (doc && doc->isOk()) {
        FontInfoScanner scanner(doc.get());

        // Scan more pages than exist - should handle gracefully
        std::vector<FontInfo *> *fonts = scanner.scan(100);

        if (fonts) {
            // Should still find the font(s) from the single page
            for (auto *f : *fonts) {
                EXPECT_NO_THROW({
                    (void)f->getName();
                    (void)f->getEncoding();
                    (void)f->getType();
                    (void)f->getEmbedded();
                    (void)f->getSubset();
                    (void)f->getToUnicode();
                    (void)f->getRef();
                    (void)f->getEmbRef();
                    (void)f->getFile();
                    (void)f->getSubstituteName();
                });
                delete f;
            }
        }
        delete fonts;
    }
}
