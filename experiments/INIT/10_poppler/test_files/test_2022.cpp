#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XRef.h"
#include "Dict.h"
#include "GfxFont.h"

using namespace testing;

// Mock classes for external dependencies (XRef, Dict)
class MockXRef : public XRef {
public:
    MOCK_METHOD(Object, lookup, (std::string_view key), (const, override));
};

class MockDict : public Dict {
public:
    MOCK_METHOD(Object, lookup, (std::string_view key), (const, override));
    MOCK_METHOD(void, add, (std::string_view key, Object&& val), (override));
};

// Test Fixture for Annot.cc functions
class AnnotTest : public ::testing::Test {
protected:
    MockXRef xref;
    MockDict fontParentDict;
};

// TEST CASES

// Normal operation test for createAnnotDrawFont
TEST_F(AnnotTest, CreateAnnotDrawFont_Normal_2022) {
    // Arrange
    const char* resourceName = "AnnotDrawFont";
    const char* fontname = "Helvetica";

    // Expect the necessary dictionary entries to be added for a valid font creation
    EXPECT_CALL(fontParentDict, lookup("Font")).WillOnce(Return(Object(new Dict(&xref))));
    EXPECT_CALL(fontParentDict, add("Font", _)).Times(1);

    // Act
    auto font = createAnnotDrawFont(&xref, &fontParentDict, resourceName, fontname);

    // Assert
    ASSERT_NE(font, nullptr);  // Verify that font creation was successful
}

// Test for boundary case: when fontName is "ZapfDingbats" (should not have Encoding)
TEST_F(AnnotTest, CreateAnnotDrawFont_ZapfDingbats_2022) {
    // Arrange
    const char* resourceName = "AnnotDrawFont";
    const char* fontname = "ZapfDingbats";

    // Expect the necessary dictionary entries to be added for a valid font creation
    EXPECT_CALL(fontParentDict, lookup("Font")).WillOnce(Return(Object(new Dict(&xref))));
    EXPECT_CALL(fontParentDict, add("Font", _)).Times(1);

    // Act
    auto font = createAnnotDrawFont(&xref, &fontParentDict, resourceName, fontname);

    // Assert
    ASSERT_NE(font, nullptr);  // Verify that font creation was successful
}

// Exceptional case: Invalid fontName (neither "Helvetica" nor "ZapfDingbats" or "Symbol")
TEST_F(AnnotTest, CreateAnnotDrawFont_InvalidFontName_2022) {
    // Arrange
    const char* resourceName = "AnnotDrawFont";
    const char* fontname = "InvalidFont";

    // Expect the necessary dictionary entries to be added for a valid font creation
    EXPECT_CALL(fontParentDict, lookup("Font")).WillOnce(Return(Object(new Dict(&xref))));
    EXPECT_CALL(fontParentDict, add("Font", _)).Times(1);

    // Act
    auto font = createAnnotDrawFont(&xref, &fontParentDict, resourceName, fontname);

    // Assert
    ASSERT_NE(font, nullptr);  // Verify that font creation was successful even for an invalid font name
}

// Boundary test: when fontParentDict is missing the "Font" entry and it's being added
TEST_F(AnnotTest, CreateAnnotDrawFont_MissingFontEntry_2022) {
    // Arrange
    const char* resourceName = "AnnotDrawFont";
    const char* fontname = "Helvetica";

    // Mock that the Font entry is initially missing
    EXPECT_CALL(fontParentDict, lookup("Font")).WillOnce(Return(Object()));
    EXPECT_CALL(fontParentDict, add("Font", _)).Times(1);

    // Act
    auto font = createAnnotDrawFont(&xref, &fontParentDict, resourceName, fontname);

    // Assert
    ASSERT_NE(font, nullptr);  // Verify that font creation was successful and Font entry was added
}