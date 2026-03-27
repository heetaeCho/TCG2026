#include <gtest/gtest.h>
#include <optional>
#include <string>

// Include the FontInfo class and other necessary headers
#include "./TestProjects/poppler/poppler/FontInfo.h"

class FontInfoTest_998 : public ::testing::Test {
protected:
    // Setup any common test data or mocking here
    FontInfoTest_998() = default;
    ~FontInfoTest_998() override = default;
};

// Test case to verify the behavior of getName
TEST_F(FontInfoTest_998, GetName_ValidName_ReturnsCorrectValue_998) {
    // Assuming GfxFont and XRef are defined somewhere and can be instantiated
    GfxFont* font = nullptr;  // Mock or real instance as required
    XRef* xref = nullptr;  // Mock or real instance as required
    
    FontInfo fontInfo(font, xref);

    // Test with an optional with value
    std::string testName = "Arial";
    fontInfo.name = testName;

    // Test that getName returns the correct value
    EXPECT_EQ(*fontInfo.getName(), testName);
}

// Test case to verify the behavior of getSubstituteName (if it's set)
TEST_F(FontInfoTest_998, GetSubstituteName_ValidSubstituteName_ReturnsCorrectValue_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    std::string substituteName = "Arial-Substitute";
    fontInfo.substituteName = substituteName;

    EXPECT_EQ(*fontInfo.getSubstituteName(), substituteName);
}

// Test case to verify getFile returns the correct file
TEST_F(FontInfoTest_998, GetFile_ValidFile_ReturnsCorrectValue_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    std::string file = "fontfile.ttf";
    fontInfo.file = file;

    EXPECT_EQ(*fontInfo.getFile(), file);
}

// Test case to check behavior when getName returns an empty optional
TEST_F(FontInfoTest_998, GetName_NoName_ReturnsEmptyOptional_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    // Name should be empty by default
    EXPECT_FALSE(fontInfo.getName().has_value());
}

// Test case to check behavior of getEncoding
TEST_F(FontInfoTest_998, GetEncoding_ValidEncoding_ReturnsCorrectValue_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    std::string encoding = "UTF-8";
    fontInfo.encoding = encoding;

    EXPECT_EQ(fontInfo.getEncoding(), encoding);
}

// Test case to verify getEmbedded returns the expected value
TEST_F(FontInfoTest_998, GetEmbedded_ValidFlag_ReturnsCorrectValue_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    fontInfo.emb = true;
    EXPECT_TRUE(fontInfo.getEmbedded());

    fontInfo.emb = false;
    EXPECT_FALSE(fontInfo.getEmbedded());
}

// Test case to check getSubset behavior
TEST_F(FontInfoTest_998, GetSubset_ValidFlag_ReturnsCorrectValue_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    fontInfo.subset = true;
    EXPECT_TRUE(fontInfo.getSubset());

    fontInfo.subset = false;
    EXPECT_FALSE(fontInfo.getSubset());
}

// Test case to verify behavior when the optional substituteName is not set
TEST_F(FontInfoTest_998, GetSubstituteName_NoSubstituteName_ReturnsEmptyOptional_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    EXPECT_FALSE(fontInfo.getSubstituteName().has_value());
}

// Test case to verify getToUnicode behavior
TEST_F(FontInfoTest_998, GetToUnicode_ValidFlag_ReturnsCorrectValue_998) {
    GfxFont* font = nullptr;
    XRef* xref = nullptr;
    FontInfo fontInfo(font, xref);

    fontInfo.hasToUnicode = true;
    EXPECT_TRUE(fontInfo.getToUnicode());

    fontInfo.hasToUnicode = false;
    EXPECT_FALSE(fontInfo.getToUnicode());
}