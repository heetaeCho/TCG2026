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

// Since we cannot easily construct FormFieldText objects (they require PDFDoc, Object, etc.),
// we'll focus on testing the static method tokenizeDA which doesn't require an instance,
// and test what we can through the public interface.

class FormFieldTextTokenizeDATest_909 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test tokenizeDA with an empty DA string
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_EmptyString_909) {
    std::vector<std::string> tokens;
    auto result = FormFieldText::tokenizeDA("", &tokens, "Tf");
    // With an empty string, we expect no tokens found and no match
    EXPECT_FALSE(result.has_value());
    EXPECT_TRUE(tokens.empty());
}

// Test tokenizeDA with a typical DA string containing "Tf"
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_TypicalDAString_909) {
    std::vector<std::string> tokens;
    std::string daString = "/Helv 12 Tf 0 g";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "Tf");
    // We expect tokens to be populated and result to have a value pointing to "Tf" token
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(tokens.empty());
}

// Test tokenizeDA when the search token is not present
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_TokenNotFound_909) {
    std::vector<std::string> tokens;
    std::string daString = "/Helv 12 Tf 0 g";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "rg");
    // "rg" is not in the string (only "g" is), so we expect no match
    // Tokens should still be populated
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with a DA string that has color operator "rg"
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_WithColorOperator_909) {
    std::vector<std::string> tokens;
    std::string daString = "0.5 0.5 0.5 rg /Helv 10 Tf";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "rg");
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(tokens.empty());
}

// Test tokenizeDA with nullptr search token behavior (edge case)
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_NullSearchToken_909) {
    std::vector<std::string> tokens;
    std::string daString = "/Helv 12 Tf";
    // Passing nullptr as searchTok - behavior depends on implementation
    auto result = FormFieldText::tokenizeDA(daString, &tokens, nullptr);
    // We just verify it doesn't crash and returns something reasonable
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with only the search token in the string
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_OnlySearchToken_909) {
    std::vector<std::string> tokens;
    std::string daString = "Tf";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "Tf");
    EXPECT_TRUE(result.has_value());
    if (result.has_value()) {
        EXPECT_EQ(result.value(), 0u);
    }
}

// Test tokenizeDA with multiple spaces between tokens
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_MultipleSpaces_909) {
    std::vector<std::string> tokens;
    std::string daString = "/Helv   12   Tf   0   g";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "Tf");
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(tokens.empty());
}

// Test tokenizeDA with search token "g"
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_SearchForG_909) {
    std::vector<std::string> tokens;
    std::string daString = "/Helv 12 Tf 0 g";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "g");
    EXPECT_TRUE(result.has_value());
}

// Test tokenizeDA returns correct index for the found token
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_CorrectIndex_909) {
    std::vector<std::string> tokens;
    std::string daString = "/Helv 12 Tf 0 g";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "Tf");
    EXPECT_TRUE(result.has_value());
    if (result.has_value()) {
        // "Tf" should be at index 2 (after "/Helv" and "12")
        EXPECT_EQ(result.value(), 2u);
        EXPECT_GE(tokens.size(), 3u);
        if (tokens.size() > result.value()) {
            EXPECT_EQ(tokens[result.value()], "Tf");
        }
    }
}

// Test tokenizeDA with a complex DA string
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_ComplexDAString_909) {
    std::vector<std::string> tokens;
    std::string daString = "0.0 0.0 0.0 rg /Courier 10 Tf";
    auto resultRg = FormFieldText::tokenizeDA(daString, &tokens, "Tf");
    EXPECT_TRUE(resultRg.has_value());
    // Verify tokens are properly populated
    EXPECT_GE(tokens.size(), 7u); // Should have: 0.0, 0.0, 0.0, rg, /Courier, 10, Tf
}

// Test tokenizeDA preserves all tokens
TEST_F(FormFieldTextTokenizeDATest_909, TokenizeDA_AllTokensPreserved_909) {
    std::vector<std::string> tokens;
    std::string daString = "/Helv 12 Tf";
    auto result = FormFieldText::tokenizeDA(daString, &tokens, "Tf");
    EXPECT_TRUE(result.has_value());
    EXPECT_EQ(tokens.size(), 3u);
    if (tokens.size() == 3) {
        EXPECT_EQ(tokens[0], "/Helv");
        EXPECT_EQ(tokens[1], "12");
        EXPECT_EQ(tokens[2], "Tf");
    }
}
