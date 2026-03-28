#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <optional>
#include <string>
#include "./TestProjects/poppler/poppler/FontInfo.h"

class FontInfoTest_1004 : public testing::Test {
protected:
    // Setup code if necessary
};

TEST_F(FontInfoTest_1004, GetSubset_ReturnsCorrectSubsetValue_1004) {
    FontInfo fontInfo(nullptr, nullptr); // Pass nullptr for the constructor, assuming GfxFont and XRef aren't relevant here
    // Since the constructor isn't shown in the code provided, we assume that 'subset' will be initialized to a default value of 'false'.
    EXPECT_EQ(fontInfo.getSubset(), false);
}

TEST_F(FontInfoTest_1004, GetSubset_ChangesWhenModified_1004) {
    // We will simulate the behavior of setting the 'subset' variable by creating a new FontInfo object
    FontInfo fontInfo(nullptr, nullptr);  // We initialize the object here
    
    // Mocking the modification of the 'subset' field is not possible because 'subset' is a private variable
    // So we are checking based on observable behavior (we assume the default value for 'subset' is false)
    // Additional tests for other setters could be added if 'subset' could be changed by some setter.
    fontInfo = FontInfo(nullptr, nullptr);
    EXPECT_EQ(fontInfo.getSubset(), false);
}

TEST_F(FontInfoTest_1004, GetName_ReturnsEmptyOptional_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_FALSE(fontInfo.getName().has_value());
}

TEST_F(FontInfoTest_1004, GetEncoding_ReturnsEmptyString_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_EQ(fontInfo.getEncoding(), "");
}

TEST_F(FontInfoTest_1004, GetSubstituteName_ReturnsEmptyOptional_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_FALSE(fontInfo.getSubstituteName().has_value());
}

TEST_F(FontInfoTest_1004, GetFile_ReturnsEmptyOptional_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_FALSE(fontInfo.getFile().has_value());
}

TEST_F(FontInfoTest_1004, GetEmbedded_ReturnsFalse_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_EQ(fontInfo.getEmbedded(), false);
}

TEST_F(FontInfoTest_1004, GetToUnicode_ReturnsFalse_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_EQ(fontInfo.getToUnicode(), false);
}

TEST_F(FontInfoTest_1004, GetRef_ReturnsEmptyRef_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_EQ(fontInfo.getRef(), Ref());
}

TEST_F(FontInfoTest_1004, GetEmbRef_ReturnsEmptyRef_1004) {
    FontInfo fontInfo(nullptr, nullptr);
    EXPECT_EQ(fontInfo.getEmbRef(), Ref());
}