#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "FontInfo.h"
#include "GfxFont.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>
#include <string>
#include <optional>

class FontInfoTest_1004 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that FontInfo can be copy-constructed
// We need a real PDFDoc to get fonts from, but since we may not have test files,
// we test what we can about the interface.

TEST_F(FontInfoTest_1004, GetSubsetReturnsBool_1004) {
    // FontInfo::getSubset() should return a bool value
    // This is a compile-time check that the method exists and returns bool
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getSubset()), bool>,
                  "getSubset should return bool");
}

TEST_F(FontInfoTest_1004, GetNameReturnsOptionalString_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getName()), const std::optional<std::string>&>,
                  "getName should return const ref to optional<string>");
}

TEST_F(FontInfoTest_1004, GetSubstituteNameReturnsOptionalString_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getSubstituteName()), const std::optional<std::string>&>,
                  "getSubstituteName should return const ref to optional<string>");
}

TEST_F(FontInfoTest_1004, GetFileReturnsOptionalString_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getFile()), const std::optional<std::string>&>,
                  "getFile should return const ref to optional<string>");
}

TEST_F(FontInfoTest_1004, GetEncodingReturnsString_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getEncoding()), const std::string&>,
                  "getEncoding should return const ref to string");
}

TEST_F(FontInfoTest_1004, GetEmbeddedReturnsBool_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getEmbedded()), bool>,
                  "getEmbedded should return bool");
}

TEST_F(FontInfoTest_1004, GetToUnicodeReturnsBool_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getToUnicode()), bool>,
                  "getToUnicode should return bool");
}

TEST_F(FontInfoTest_1004, GetRefReturnsRef_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getRef()), Ref>,
                  "getRef should return Ref");
}

TEST_F(FontInfoTest_1004, GetEmbRefReturnsRef_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getEmbRef()), Ref>,
                  "getEmbRef should return Ref");
}

TEST_F(FontInfoTest_1004, CopyConstructorIsAvailable_1004) {
    // Verify FontInfo is copy constructible
    static_assert(std::is_copy_constructible_v<FontInfo>,
                  "FontInfo should be copy constructible");
}

TEST_F(FontInfoTest_1004, CopyAssignmentIsDeleted_1004) {
    // Verify FontInfo copy assignment is deleted
    static_assert(!std::is_copy_assignable_v<FontInfo>,
                  "FontInfo copy assignment should be deleted");
}

TEST_F(FontInfoTest_1004, GetTypeReturnsType_1004) {
    static_assert(std::is_same_v<decltype(std::declval<const FontInfo>().getType()), FontInfo::Type>,
                  "getType should return FontInfo::Type");
}
