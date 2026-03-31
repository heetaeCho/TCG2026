#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "goo/GooString.h"
#include <set>
#include <vector>
#include <string>
#include <optional>
#include <memory>

// Since we can't easily construct FormFieldText objects without a valid PDFDoc
// and dictionary, we'll focus on testing the static method tokenizeDA which
// doesn't require object construction, and test what we can through the interface.

class FormFieldTextTokenizeDATest_904 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test tokenizeDA with a simple DA string containing "Tf" token
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_FindsTfToken_904) {
    std::string daString = "/Helv 12 Tf 0 g";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "Tf");
    
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(daToks.empty());
}

// Test tokenizeDA with empty DA string
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_EmptyString_904) {
    std::string daString = "";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "Tf");
    
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(daToks.empty());
}

// Test tokenizeDA when search token is not found
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_TokenNotFound_904) {
    std::string daString = "/Helv 12 Tf 0 g";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "rg");
    
    // "rg" is not in the string, so result should be empty optional
    // but tokens should still be parsed
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with "g" token for color
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_FindsGToken_904) {
    std::string daString = "/Helv 12 Tf 0 g";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "g");
    
    EXPECT_TRUE(result.has_value());
}

// Test tokenizeDA with multiple tokens in DA string
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_MultipleTokens_904) {
    std::string daString = "/Helv 10 Tf 1 0 0 rg";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "rg");
    
    EXPECT_TRUE(result.has_value());
}

// Test tokenizeDA with nullptr searchTok - boundary case
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_NullSearchToken_904) {
    std::string daString = "/Helv 12 Tf 0 g";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, nullptr);
    
    // With null search token, it should still tokenize but not find anything
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with whitespace-only DA string
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_WhitespaceOnly_904) {
    std::string daString = "   ";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "Tf");
    
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with single token matching search
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_SingleTokenMatch_904) {
    std::string daString = "Tf";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "Tf");
    
    EXPECT_TRUE(result.has_value());
}

// Test tokenizeDA verifying token count
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_CorrectTokenCount_904) {
    std::string daString = "/Helv 12 Tf 0 g";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "Tf");
    
    // Expected tokens: /Helv, 12, Tf, 0, g = 5 tokens
    EXPECT_EQ(daToks.size(), 5u);
}

// Test tokenizeDA returns correct index for found token
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_CorrectIndex_904) {
    std::string daString = "/Helv 12 Tf 0 g";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "Tf");
    
    ASSERT_TRUE(result.has_value());
    // "Tf" should be at index 2 (0-based: /Helv=0, 12=1, Tf=2)
    EXPECT_EQ(result.value(), 2u);
    if (daToks.size() > result.value()) {
        EXPECT_EQ(daToks[result.value()], "Tf");
    }
}

// Test tokenizeDA with complex DA string
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_ComplexDAString_904) {
    std::string daString = "0.0 0.0 0.0 rg /Cour 10 Tf";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "Tf");
    
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(daToks.empty());
}

// Test tokenizeDA looking for "rg" in complex string
TEST_F(FormFieldTextTokenizeDATest_904, TokenizeDA_FindsRGInComplex_904) {
    std::string daString = "0.0 0.0 0.0 rg /Cour 10 Tf";
    std::vector<std::string> daToks;
    auto result = FormFieldText::tokenizeDA(daString, &daToks, "rg");
    
    EXPECT_TRUE(result.has_value());
}
