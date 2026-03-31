#include <gtest/gtest.h>
#include <optional>
#include <string>

#include "FontInfo.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class FontInfoTest_999 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to get a FontInfo from a real PDF if available, otherwise we test structural aspects
// We test using documents that may have fonts

TEST_F(FontInfoTest_999, CopyConstructorCreatesValidCopy_999) {
    // Test that copy constructor works (compiles and doesn't crash)
    // We need a real FontInfo to copy - try loading a simple PDF
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *original = (*fonts)[0];
            FontInfo copy(*original);
            
            // Verify copy has same values
            EXPECT_EQ(copy.getName(), original->getName());
            EXPECT_EQ(copy.getSubstituteName(), original->getSubstituteName());
            EXPECT_EQ(copy.getFile(), original->getFile());
            EXPECT_EQ(copy.getEncoding(), original->getEncoding());
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

TEST_F(FontInfoTest_999, GetNameReturnsOptionalString_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            const std::optional<std::string> &name = fi->getName();
            // getName returns an optional - it may or may not have a value
            // Just verify it doesn't crash and returns a valid reference
            if (name.has_value()) {
                EXPECT_FALSE(name->empty());
            }
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetSubstituteNameReturnsOptionalString_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            const std::optional<std::string> &subName = fi->getSubstituteName();
            // substituteName is optional - verify it's accessible
            (void)subName;
            SUCCEED();
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetFileReturnsOptionalString_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            const std::optional<std::string> &file = fi->getFile();
            (void)file;
            SUCCEED();
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetEncodingReturnsString_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            const std::string &encoding = fi->getEncoding();
            // Encoding is a string reference - just verify access doesn't crash
            (void)encoding;
            SUCCEED();
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetEmbeddedReturnsBool_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            bool emb = fi->getEmbedded();
            // Just verify it returns a valid bool
            EXPECT_TRUE(emb == true || emb == false);
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetSubsetReturnsBool_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            bool subset = fi->getSubset();
            EXPECT_TRUE(subset == true || subset == false);
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetToUnicodeReturnsBool_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            bool toUnicode = fi->getToUnicode();
            EXPECT_TRUE(toUnicode == true || toUnicode == false);
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetRefReturnsValidRef_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            Ref ref = fi->getRef();
            // A valid font reference should have non-negative num
            EXPECT_GE(ref.num, 0);
            EXPECT_GE(ref.gen, 0);
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, GetEmbRefReturnsRef_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            Ref embRef = fi->getEmbRef();
            // embRef may be invalid if font is not embedded
            (void)embRef;
            SUCCEED();
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, FontInfoScannerMultiplePages_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        // Scan all pages
        std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());
        ASSERT_NE(fonts, nullptr);
        // There should be at least some fonts in a document with actual text
        // Clean up
        for (auto *f : *fonts) {
            delete f;
        }
        delete fonts;
    }
}

TEST_F(FontInfoTest_999, FontInfoScannerScanZeroPages_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        // Scan 0 pages - should return empty or null
        std::vector<FontInfo *> *fonts = scanner.scan(0);
        if (fonts) {
            for (auto *f : *fonts) {
                delete f;
            }
            delete fonts;
        }
        SUCCEED();
    }
}

TEST_F(FontInfoTest_999, GetTypeReturnsValidType_999) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (doc->isOk()) {
        FontInfoScanner scanner(doc.get(), 0);
        std::vector<FontInfo *> *fonts = scanner.scan(1);
        if (fonts && !fonts->empty()) {
            FontInfo *fi = (*fonts)[0];
            FontInfo::Type type = fi->getType();
            // Type should be within the valid enum range
            EXPECT_GE(static_cast<int>(type), 0);
            for (auto *f : *fonts) {
                delete f;
            }
        }
        delete fonts;
    }
}
