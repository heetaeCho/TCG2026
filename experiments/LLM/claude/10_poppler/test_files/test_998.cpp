#include <gtest/gtest.h>
#include <optional>
#include <string>

#include "FontInfo.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class FontInfoTest_998 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that FontInfo can be copy constructed
TEST_F(FontInfoTest_998, CopyConstructorWorks_998) {
    // We need a real FontInfo to test copy. We'll scan a document if possible.
    // Since we can't easily create GfxFont/XRef from scratch, we test
    // that the interface compiles and copy semantics work with FontInfoScanner.

    // Create a minimal test by loading a PDF if available
    // This test verifies the copy constructor compiles and works
    // We use FontInfoScanner to get FontInfo objects

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *original = (*fonts)[0];
        // Test copy constructor
        FontInfo copy(*original);

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

// Test that getName returns a valid optional
TEST_F(FontInfoTest_998, GetNameReturnsOptional_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = (*fonts)[0];
        const std::optional<std::string> &name = fi->getName();
        // Name is either set or not - just verify it's a valid optional
        if (name.has_value()) {
            EXPECT_FALSE(name->empty());
        }

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getEncoding returns a string (possibly empty)
TEST_F(FontInfoTest_998, GetEncodingReturnsString_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = (*fonts)[0];
        const std::string &enc = fi->getEncoding();
        // Just verify it doesn't crash; encoding can be empty
        (void)enc;
        SUCCEED();

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test boolean getters return valid booleans
TEST_F(FontInfoTest_998, BooleanGettersWork_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = (*fonts)[0];
        bool emb = fi->getEmbedded();
        bool sub = fi->getSubset();
        bool toUni = fi->getToUnicode();
        // Just verify they return without crashing
        (void)emb;
        (void)sub;
        (void)toUni;
        SUCCEED();

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getRef and getEmbRef return valid Ref objects
TEST_F(FontInfoTest_998, RefGettersReturnValidRefs_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = (*fonts)[0];
        Ref ref = fi->getRef();
        Ref embRef = fi->getEmbRef();
        // Font ref should typically have a valid object number
        EXPECT_GE(ref.num, 0);
        // embRef may or may not be valid depending on embedding
        (void)embRef;

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test scanning with 0 pages returns empty or null
TEST_F(FontInfoTest_998, ScanZeroPagesReturnsEmpty_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(0);

    if (fonts) {
        EXPECT_TRUE(fonts->empty());
        delete fonts;
    } else {
        SUCCEED();
    }
}

// Test getFile returns valid optional
TEST_F(FontInfoTest_998, GetFileReturnsOptional_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = (*fonts)[0];
        const std::optional<std::string> &file = fi->getFile();
        // File may or may not be present
        if (file.has_value()) {
            EXPECT_FALSE(file->empty());
        }

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getSubstituteName returns valid optional
TEST_F(FontInfoTest_998, GetSubstituteNameReturnsOptional_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *fi = (*fonts)[0];
        const std::optional<std::string> &subName = fi->getSubstituteName();
        // Substitute name may or may not be present
        if (subName.has_value()) {
            EXPECT_FALSE(subName->empty());
        }

        for (auto *f : *fonts) {
            delete f;
        }
    }
    delete fonts;
}

// Test getType returns a valid type
TEST_F(FontInfoTest_998, GetTypeReturnsValidType_998) {
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

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
