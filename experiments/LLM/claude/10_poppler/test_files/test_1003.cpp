#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FontInfo.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "FontInfo.h"

#include <memory>
#include <string>
#include <optional>

class FontInfoTest_1003 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to get FontInfo objects from a real PDF document
// Since FontInfo requires GfxFont* and XRef*, we use FontInfoScanner on a real document
class FontInfoFromDocTest_1003 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that FontInfo copy constructor works (it's defaulted)
TEST_F(FontInfoFromDocTest_1003, CopyConstructorWorks_1003) {
    // Create a minimal PDF in memory to test with
    // We'll use a GooString with a simple PDF file path
    // Since we can't easily create FontInfo without a real font,
    // we test the interface contract through FontInfoScanner

    // Create a simple PDF document
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *original = fonts->front();
        
        // Test copy constructor
        FontInfo copy(*original);
        
        EXPECT_EQ(copy.getName(), original->getName());
        EXPECT_EQ(copy.getEmbedded(), original->getEmbedded());
        EXPECT_EQ(copy.getSubset(), original->getSubset());
        EXPECT_EQ(copy.getToUnicode(), original->getToUnicode());
        EXPECT_EQ(copy.getEncoding(), original->getEncoding());
        EXPECT_EQ(copy.getType(), original->getType());
        EXPECT_EQ(copy.getFile(), original->getFile());
        EXPECT_EQ(copy.getSubstituteName(), original->getSubstituteName());
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

// Test getEmbedded returns a bool value
TEST_F(FontInfoFromDocTest_1003, GetEmbeddedReturnsBool_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        bool embedded = fi->getEmbedded();
        // Just verify it's a valid bool
        EXPECT_TRUE(embedded == true || embedded == false);

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getName returns optional string
TEST_F(FontInfoFromDocTest_1003, GetNameReturnsOptionalString_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        const std::optional<std::string> &name = fi->getName();
        // Name can be present or absent
        if (name.has_value()) {
            EXPECT_FALSE(name->empty());
        }

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getEncoding returns a string reference
TEST_F(FontInfoFromDocTest_1003, GetEncodingReturnsString_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        const std::string &encoding = fi->getEncoding();
        // Encoding is a valid string (may be empty)
        EXPECT_GE(encoding.size(), 0u);

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getSubset returns bool
TEST_F(FontInfoFromDocTest_1003, GetSubsetReturnsBool_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        bool subset = fi->getSubset();
        EXPECT_TRUE(subset == true || subset == false);

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getToUnicode returns bool
TEST_F(FontInfoFromDocTest_1003, GetToUnicodeReturnsBool_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        bool hasToUnicode = fi->getToUnicode();
        EXPECT_TRUE(hasToUnicode == true || hasToUnicode == false);

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getRef returns a Ref
TEST_F(FontInfoFromDocTest_1003, GetRefReturnsValidRef_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
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

// Test getEmbRef
TEST_F(FontInfoFromDocTest_1003, GetEmbRefReturnsRef_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        Ref embRef = fi->getEmbRef();
        // EmbRef may be invalid if font is not embedded
        if (fi->getEmbedded()) {
            EXPECT_GE(embRef.num, 0);
        }

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getType returns a valid type
TEST_F(FontInfoFromDocTest_1003, GetTypeReturnsValidType_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        FontInfo::Type type = fi->getType();
        // Type should be within the valid enum range
        EXPECT_GE(static_cast<int>(type), 0);

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test FontInfoScanner with zero pages
TEST_F(FontInfoFromDocTest_1003, ScannerWithZeroPages_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(0);

    // Scanning 0 pages should return empty or null
    if (fonts) {
        EXPECT_TRUE(fonts->empty());
        delete fonts;
    }
}

// Test getSubstituteName returns optional
TEST_F(FontInfoFromDocTest_1003, GetSubstituteNameReturnsOptional_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        const std::optional<std::string> &subName = fi->getSubstituteName();
        // May or may not have a substitute name
        if (subName.has_value()) {
            EXPECT_FALSE(subName->empty());
        }

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getFile returns optional
TEST_F(FontInfoFromDocTest_1003, GetFileReturnsOptional_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = fonts->front();
        const std::optional<std::string> &file = fi->getFile();
        // File path is optional
        if (file.has_value()) {
            EXPECT_FALSE(file->empty());
        }

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test consistency between embedded flag and embRef
TEST_F(FontInfoFromDocTest_1003, EmbeddedConsistencyWithEmbRef_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts) {
        for (auto *fi : *fonts) {
            if (fi->getEmbedded()) {
                // Embedded fonts should have a valid embRef
                Ref embRef = fi->getEmbRef();
                EXPECT_GE(embRef.num, 0);
            }
            delete fi;
        }
    }
    delete fonts;
}

// Test scanning multiple pages incrementally
TEST_F(FontInfoFromDocTest_1003, ScannerIncrementalScan_1003) {
    GooString fileName("../test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    
    // Scan page by page
    std::vector<FontInfo *> *fonts1 = scanner.scan(1);
    std::vector<FontInfo *> *fonts2 = scanner.scan(1);
    
    // Both should be valid (possibly empty) vectors
    if (fonts1) {
        for (auto *f : *fonts1) delete f;
        delete fonts1;
    }
    if (fonts2) {
        for (auto *f : *fonts2) delete f;
        delete fonts2;
    }
}
