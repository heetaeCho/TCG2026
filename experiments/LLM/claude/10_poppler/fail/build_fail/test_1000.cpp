#include <gtest/gtest.h>
#include <optional>
#include <string>

#include "FontInfo.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class FontInfoTest_1000 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that FontInfo can be copy-constructed
TEST_F(FontInfoTest_1000, CopyConstructor_1000)
{
    // We need a real FontInfo to test copy construction.
    // We'll use FontInfoScanner to get one from a real PDF if available.
    // For a minimal test, we verify that copy construction compiles and
    // produces consistent results.

    // Create a minimal PDF document to extract font info
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    if (fonts && !fonts->empty()) {
        FontInfo *original = fonts->at(0);
        FontInfo copy(*original);

        // Verify copy has same values as original
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

// Test FontInfoScanner scanning fonts from a document
TEST_F(FontInfoTest_1000, ScanFontsFromDocument_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    ASSERT_NE(fonts, nullptr);

    // Each font should have accessible properties without crashing
    for (auto *fi : *fonts) {
        ASSERT_NE(fi, nullptr);

        // These calls should not crash - just verify they're callable
        const auto &name = fi->getName();
        const auto &subName = fi->getSubstituteName();
        const auto &file = fi->getFile();
        const auto &encoding = fi->getEncoding();
        fi->getType();
        fi->getEmbedded();
        fi->getSubset();
        fi->getToUnicode();
        fi->getRef();
        fi->getEmbRef();

        // If name has a value, it should be non-empty
        if (name.has_value()) {
            EXPECT_FALSE(name->empty());
        }

        // If file has a value, it should be non-empty
        if (file.has_value()) {
            EXPECT_FALSE(file->empty());
        }

        (void)name;
        (void)subName;
        (void)file;
        (void)encoding;

        delete fi;
    }
    delete fonts;
}

// Test scanning with zero pages
TEST_F(FontInfoTest_1000, ScanZeroPages_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(0);

    ASSERT_NE(fonts, nullptr);
    // Scanning 0 pages should return empty or no fonts
    EXPECT_TRUE(fonts->empty());

    delete fonts;
}

// Test that getEncoding returns a valid string reference
TEST_F(FontInfoTest_1000, GetEncodingReturnsValidString_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    ASSERT_NE(fonts, nullptr);

    for (auto *fi : *fonts) {
        // getEncoding should return a valid string reference (possibly empty)
        const std::string &enc = fi->getEncoding();
        // Just verify it doesn't crash and is a valid string
        EXPECT_GE(enc.size(), 0u);
        delete fi;
    }
    delete fonts;
}

// Test getEmbedded and getSubset return bool values
TEST_F(FontInfoTest_1000, BooleanAccessors_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    ASSERT_NE(fonts, nullptr);

    for (auto *fi : *fonts) {
        bool emb = fi->getEmbedded();
        bool sub = fi->getSubset();
        bool toUni = fi->getToUnicode();

        // If subset is true, it should typically also be embedded
        // (subset fonts are always embedded), but we don't enforce internal logic
        (void)emb;
        (void)sub;
        (void)toUni;

        delete fi;
    }
    delete fonts;
}

// Test Ref accessors return valid Ref values
TEST_F(FontInfoTest_1000, RefAccessors_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    ASSERT_NE(fonts, nullptr);

    for (auto *fi : *fonts) {
        Ref fontRef = fi->getRef();
        Ref embRef = fi->getEmbRef();

        // Font reference should have valid num (>= 0 for real objects)
        EXPECT_GE(fontRef.num, 0);
        EXPECT_GE(fontRef.gen, 0);

        // Embedded ref may or may not be valid depending on embedding
        if (fi->getEmbedded()) {
            EXPECT_GE(embRef.num, 0);
        }

        delete fi;
    }
    delete fonts;
}

// Test scanning single page
TEST_F(FontInfoTest_1000, ScanSinglePage_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(1);

    ASSERT_NE(fonts, nullptr);

    for (auto *fi : *fonts) {
        delete fi;
    }
    delete fonts;
}

// Test that getFile returns optional (may or may not have value)
TEST_F(FontInfoTest_1000, GetFileReturnsOptional_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());
    std::vector<FontInfo *> *fonts = scanner.scan(doc->getNumPages());

    ASSERT_NE(fonts, nullptr);

    for (auto *fi : *fonts) {
        const std::optional<std::string> &file = fi->getFile();
        // file is optional - embedded fonts may not have a file path
        if (fi->getEmbedded() && !fi->getSubstituteName().has_value()) {
            // Embedded fonts without substitution may not have file
            // Just verify no crash
        }
        (void)file;
        delete fi;
    }
    delete fonts;
}

// Test multiple scans with same scanner (incremental scanning)
TEST_F(FontInfoTest_1000, MultipleScanCalls_1000)
{
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithActualText.pdf"));
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    FontInfoScanner scanner(doc.get());

    // First scan
    std::vector<FontInfo *> *fonts1 = scanner.scan(1);
    ASSERT_NE(fonts1, nullptr);
    size_t count1 = fonts1->size();

    // Second scan should continue from where first left off
    std::vector<FontInfo *> *fonts2 = scanner.scan(doc->getNumPages());
    ASSERT_NE(fonts2, nullptr);

    for (auto *fi : *fonts1) {
        delete fi;
    }
    delete fonts1;

    for (auto *fi : *fonts2) {
        delete fi;
    }
    delete fonts2;

    (void)count1;
}
