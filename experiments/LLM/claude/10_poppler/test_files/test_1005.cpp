#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FontInfo.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GfxFont.h"

#include <memory>
#include <string>
#include <optional>

class FontInfoTest_1005 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that FontInfo can be copy-constructed (copy constructor is defaulted)
TEST_F(FontInfoTest_1005, CopyConstructorWorks_1005) {
    // We need a real PDFDoc to get fonts from
    // Using a minimal approach: if we can create a FontInfo from a document, we can copy it
    // Since we can't easily create a GfxFont without a real PDF, we test with a real document if available
    // For now, test the interface contract: copy construction should compile and work
    
    // This test verifies the copy constructor is accessible (it's defaulted)
    // We'll use a document-based approach
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    // Scan for fonts to get a FontInfo object
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(1);
    
    if (fonts && !fonts->empty()) {
        FontInfo original = *(*fonts)[0];
        FontInfo copy(original);
        
        EXPECT_EQ(original.getName(), copy.getName());
        EXPECT_EQ(original.getSubstituteName(), copy.getSubstituteName());
        EXPECT_EQ(original.getFile(), copy.getFile());
        EXPECT_EQ(original.getEncoding(), copy.getEncoding());
        EXPECT_EQ(original.getType(), copy.getType());
        EXPECT_EQ(original.getEmbedded(), copy.getEmbedded());
        EXPECT_EQ(original.getSubset(), copy.getSubset());
        EXPECT_EQ(original.getToUnicode(), copy.getToUnicode());
        EXPECT_EQ(original.getRef().num, copy.getRef().num);
        EXPECT_EQ(original.getRef().gen, copy.getRef().gen);
        EXPECT_EQ(original.getEmbRef().num, copy.getEmbRef().num);
        EXPECT_EQ(original.getEmbRef().gen, copy.getEmbRef().gen);
        
        for (auto *f : *fonts) {
            delete f;
        }
        delete fonts;
    }
}

// Test FontInfoScanner scanning pages for fonts
TEST_F(FontInfoTest_1005, ScannerReturnsValidFontInfo_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(1);
    
    ASSERT_NE(fonts, nullptr);
    
    for (auto *fi : *fonts) {
        // Each FontInfo should have a valid ref
        Ref ref = fi->getRef();
        EXPECT_GE(ref.num, 0);
        
        // getEncoding should return a string (possibly empty)
        const std::string &enc = fi->getEncoding();
        (void)enc; // just verify it doesn't crash
        
        // Boolean accessors should return without crashing
        bool emb = fi->getEmbedded();
        bool sub = fi->getSubset();
        bool toUni = fi->getToUnicode();
        (void)emb;
        (void)sub;
        (void)toUni;
        
        // Type should be a valid enum value
        FontInfo::Type type = fi->getType();
        EXPECT_GE(static_cast<int>(type), 0);
        
        delete fi;
    }
    delete fonts;
}

// Test scanning with zero pages returns empty or null
TEST_F(FontInfoTest_1005, ScannerScanZeroPages_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(0);
    
    // Scanning 0 pages should yield no fonts or empty list
    if (fonts != nullptr) {
        EXPECT_TRUE(fonts->empty());
        delete fonts;
    }
}

// Test scanning more pages than document has
TEST_F(FontInfoTest_1005, ScannerScanBeyondDocumentPages_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int totalPages = doc->getNumPages();
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(totalPages + 100);
    
    // Should not crash, just scan all available pages
    if (fonts) {
        for (auto *f : *fonts) {
            delete f;
        }
        delete fonts;
    }
}

// Test getName returns optional that may or may not have value
TEST_F(FontInfoTest_1005, GetNameReturnsOptional_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(doc->getNumPages());
    
    if (fonts && !fonts->empty()) {
        for (auto *fi : *fonts) {
            const std::optional<std::string> &name = fi->getName();
            // Name is optional - it may or may not have a value
            if (name.has_value()) {
                EXPECT_FALSE(name->empty());
            }
            delete fi;
        }
    }
    delete fonts;
}

// Test getFile returns optional
TEST_F(FontInfoTest_1005, GetFileReturnsOptional_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(doc->getNumPages());
    
    if (fonts) {
        for (auto *fi : *fonts) {
            const std::optional<std::string> &file = fi->getFile();
            // File is optional - just verify accessor works
            (void)file;
            delete fi;
        }
    }
    delete fonts;
}

// Test getSubstituteName returns optional
TEST_F(FontInfoTest_1005, GetSubstituteNameReturnsOptional_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(doc->getNumPages());
    
    if (fonts) {
        for (auto *fi : *fonts) {
            const std::optional<std::string> &subName = fi->getSubstituteName();
            (void)subName;
            delete fi;
        }
    }
    delete fonts;
}

// Test getEmbRef returns a Ref
TEST_F(FontInfoTest_1005, GetEmbRefReturnsRef_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(doc->getNumPages());
    
    if (fonts) {
        for (auto *fi : *fonts) {
            Ref embRef = fi->getEmbRef();
            if (fi->getEmbedded()) {
                // If embedded, embRef should typically point to a valid object
                // but we can't guarantee specifics without knowing the PDF
                (void)embRef;
            }
            delete fi;
        }
    }
    delete fonts;
}

// Test that embedded fonts have consistent subset info
TEST_F(FontInfoTest_1005, EmbeddedAndSubsetConsistency_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo*> *fonts = scanner.scan(doc->getNumPages());
    
    if (fonts) {
        for (auto *fi : *fonts) {
            // If subset is true, the font should generally be embedded
            // (a subset that isn't embedded doesn't make sense, but we just verify no crash)
            if (fi->getSubset()) {
                // Typically subset implies embedded, but this depends on the PDF
                // Just verify both accessors work together
                (void)fi->getEmbedded();
            }
            delete fi;
        }
    }
    delete fonts;
}

// Test sequential scanning (scanner state advances)
TEST_F(FontInfoTest_1005, ScannerSequentialScanning_1005) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("./TestProjects/poppler/test-data/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int totalPages = doc->getNumPages();
    if (totalPages < 2) {
        GTEST_SKIP() << "Need multi-page PDF for this test";
    }
    
    FontInfoScanner scanner(doc.get());
    
    // Scan first page
    std::vector<FontInfo*> *fonts1 = scanner.scan(1);
    // Scan remaining pages
    std::vector<FontInfo*> *fonts2 = scanner.scan(totalPages - 1);
    
    // Clean up
    if (fonts1) {
        for (auto *f : *fonts1) delete f;
        delete fonts1;
    }
    if (fonts2) {
        for (auto *f : *fonts2) delete f;
        delete fonts2;
    }
}
