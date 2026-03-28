#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <vector>
#include <string>
#include <set>
#include <optional>

#include "poppler/Form.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "goo/GooString.h"

// Since we cannot construct FormFieldText without a PDFDoc and proper PDF objects,
// we focus on testing the static method tokenizeDA which doesn't require an instance,
// and test observable behavior through the public interface where possible.

class FormFieldTextTokenizeDATest_911 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test tokenizeDA with an empty DA string
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_EmptyString_911) {
    std::string daString = "";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    // Empty string should not find the search token
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with a DA string that contains the search token
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_FindsSearchToken_911) {
    std::string daString = "0 0 0 rg /Helv 12 Tf";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    // Should find "Tf" token
    EXPECT_TRUE(result.has_value());
    // daToks should contain the tokenized elements
    EXPECT_FALSE(daToks.empty());
}

// Test tokenizeDA with a DA string that does not contain the search token
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_DoesNotFindSearchToken_911) {
    std::string daString = "0 0 0 rg /Helv 12";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    // Should not find "Tf" token since it's not present
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with a DA string searching for "rg"
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_FindsRgToken_911) {
    std::string daString = "0 0 0 rg /Helv 12 Tf";
    std::vector<std::string> daToks;
    const char* searchTok = "rg";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(daToks.empty());
}

// Test tokenizeDA with nullptr for daToks parameter
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_NullDaToks_911) {
    std::string daString = "0 0 0 rg /Helv 12 Tf";
    const char* searchTok = "Tf";
    
    // Passing nullptr for daToks - behavior depends on implementation
    // This tests robustness
    auto result = FormFieldText::tokenizeDA(daString, nullptr, searchTok);
    
    // We just verify it doesn't crash; result may or may not have value
    // The important thing is no segfault
}

// Test tokenizeDA with a single token DA string
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_SingleToken_911) {
    std::string daString = "Tf";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    EXPECT_TRUE(result.has_value());
}

// Test tokenizeDA with multiple spaces between tokens
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_MultipleSpaces_911) {
    std::string daString = "0  0  0  rg  /Helv  12  Tf";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    EXPECT_TRUE(result.has_value());
}

// Test tokenizeDA returns correct index for the search token
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_CorrectIndex_911) {
    std::string daString = "0 0 0 rg /Helv 12 Tf";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    EXPECT_TRUE(result.has_value());
    if (result.has_value()) {
        // The returned index should be valid within daToks
        EXPECT_LT(result.value(), daToks.size());
        // The token at the returned index should be "Tf"
        EXPECT_EQ(daToks[result.value()], "Tf");
    }
}

// Test tokenizeDA with DA string containing color specification
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_ColorSpec_911) {
    std::string daString = "1 0 0 rg";
    std::vector<std::string> daToks;
    const char* searchTok = "rg";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    EXPECT_TRUE(result.has_value());
    if (result.has_value()) {
        EXPECT_EQ(daToks[result.value()], "rg");
    }
}

// Test tokenizeDA with complex DA string
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_ComplexDAString_911) {
    std::string daString = "0.5 0.5 0.5 rg /Courier 10 Tf 0 g";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    EXPECT_TRUE(result.has_value());
    EXPECT_FALSE(daToks.empty());
}

// Test tokenizeDA searching for a token that appears multiple times
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_MultipleOccurrences_911) {
    std::string daString = "0 g 0.5 g";
    std::vector<std::string> daToks;
    const char* searchTok = "g";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    // Should find at least one occurrence
    EXPECT_TRUE(result.has_value());
}

// Test tokenizeDA with whitespace-only DA string
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_WhitespaceOnly_911) {
    std::string daString = "   ";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    EXPECT_FALSE(result.has_value());
}

// Test tokenizeDA with partial token match (should not match)
TEST_F(FormFieldTextTokenizeDATest_911, TokenizeDA_PartialMatch_911) {
    std::string daString = "0 0 0 rg /Helv 12 Tff";
    std::vector<std::string> daToks;
    const char* searchTok = "Tf";
    
    auto result = FormFieldText::tokenizeDA(daString, &daToks, searchTok);
    
    // "Tff" should not match "Tf" as it's a different token
    // (depends on implementation - tokens are typically space-separated)
}
