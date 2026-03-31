#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// We need to test AnnotStamp's public interface.
// Based on the constraints, we treat the implementation as a black box
// and only test observable behavior through the public interface.

// Since AnnotStamp depends on PDFDoc, PDFRectangle, and other Poppler internals,
// we need to include the relevant headers.
#include "config.h"
#include "poppler/PDFDoc.h"
#include "poppler/Annot.h"
#include "poppler/PDFDocFactory.h"
#include "poppler/GlobalParams.h"

#include <memory>

class AnnotStampTest_841 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override
    {
        // Create a minimal PDF document for testing
        // We need a valid PDFDoc to create annotations
    }

    void TearDown() override { }

    std::unique_ptr<PDFDoc> createTestDoc()
    {
        // Try to create a PDFDoc from a minimal PDF in memory
        // Using a simple 1-page PDF
        static const char *minimalPDF = "%PDF-1.4\n"
                                        "1 0 obj\n"
                                        "<< /Type /Catalog /Pages 2 0 R >>\n"
                                        "endobj\n"
                                        "2 0 obj\n"
                                        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
                                        "endobj\n"
                                        "3 0 obj\n"
                                        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
                                        "endobj\n"
                                        "xref\n"
                                        "0 4\n"
                                        "0000000000 65535 f \n"
                                        "0000000009 00000 n \n"
                                        "0000000058 00000 n \n"
                                        "0000000115 00000 n \n"
                                        "trailer\n"
                                        "<< /Size 4 /Root 1 0 R >>\n"
                                        "startxref\n"
                                        "190\n"
                                        "%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, strlen(minimalPDF), Object(objNull));
        return std::make_unique<PDFDoc>(stream);
    }
};

// Test that a newly created AnnotStamp has a default icon
TEST_F(AnnotStampTest_841, DefaultIconIsNotEmpty_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    const std::string &icon = stamp->getIcon();
    // A default stamp should have some icon set (typically "Draft" or similar)
    // We just verify it returns a valid reference
    EXPECT_FALSE(icon.empty());
}

// Test that setIcon changes the icon returned by getIcon
TEST_F(AnnotStampTest_841, SetIconChangesIcon_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    std::string newIcon = "Approved";
    stamp->setIcon(newIcon);

    EXPECT_EQ(stamp->getIcon(), "Approved");
}

// Test setting icon to various standard stamp names
TEST_F(AnnotStampTest_841, SetIconToStandardNames_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    std::vector<std::string> standardIcons = { "Approved", "Experimental", "NotApproved", "AsIs", "Expired", "NotForPublicRelease", "Confidential", "Final", "Sold", "Departmental", "ForComment", "TopSecret", "Draft", "ForPublicRelease" };

    for (const auto &iconName : standardIcons) {
        stamp->setIcon(iconName);
        EXPECT_EQ(stamp->getIcon(), iconName) << "Failed for icon: " << iconName;
    }
}

// Test setting icon to empty string
TEST_F(AnnotStampTest_841, SetIconToEmptyString_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    stamp->setIcon("");
    EXPECT_EQ(stamp->getIcon(), "");
}

// Test setting icon to a custom (non-standard) string
TEST_F(AnnotStampTest_841, SetIconToCustomString_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    stamp->setIcon("MyCustomStamp");
    EXPECT_EQ(stamp->getIcon(), "MyCustomStamp");
}

// Test setting icon multiple times - last one should persist
TEST_F(AnnotStampTest_841, SetIconMultipleTimes_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    stamp->setIcon("First");
    EXPECT_EQ(stamp->getIcon(), "First");

    stamp->setIcon("Second");
    EXPECT_EQ(stamp->getIcon(), "Second");

    stamp->setIcon("Third");
    EXPECT_EQ(stamp->getIcon(), "Third");
}

// Test that getIcon returns a const reference (compile-time check essentially)
TEST_F(AnnotStampTest_841, GetIconReturnsConstReference_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    stamp->setIcon("TestIcon");
    const std::string &iconRef = stamp->getIcon();
    EXPECT_EQ(iconRef, "TestIcon");

    // Setting a new icon should be reflected if we call getIcon again
    stamp->setIcon("AnotherIcon");
    const std::string &iconRef2 = stamp->getIcon();
    EXPECT_EQ(iconRef2, "AnotherIcon");
}

// Test icon with special characters
TEST_F(AnnotStampTest_841, SetIconWithSpecialCharacters_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    stamp->setIcon("Icon With Spaces");
    EXPECT_EQ(stamp->getIcon(), "Icon With Spaces");
}

// Test icon with a very long string
TEST_F(AnnotStampTest_841, SetIconWithLongString_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    std::string longIcon(1000, 'A');
    stamp->setIcon(longIcon);
    EXPECT_EQ(stamp->getIcon(), longIcon);
    EXPECT_EQ(stamp->getIcon().size(), 1000u);
}

// Test that getAppearanceResDict returns an Object (basic check)
TEST_F(AnnotStampTest_841, GetAppearanceResDictReturnsObject_841)
{
    auto doc = createTestDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto stamp = std::make_unique<AnnotStamp>(doc.get(), &rect);

    Object resDict = stamp->getAppearanceResDict();
    // Just verify it doesn't crash and returns some object
    // The object could be null or a dict depending on state
    SUCCEED();
}
