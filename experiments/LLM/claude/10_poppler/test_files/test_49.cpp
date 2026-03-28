#include <gtest/gtest.h>
#include <optional>
#include <string_view>
#include <string>
#include <vector>

// Since we need to test FoFiType1Tokenizer but it's defined in a .cc file,
// we'll include the necessary pieces. Based on the provided code, we reconstruct
// the class definition needed for testing.

static const char tokenSeparators[] = " \t\n\r";

class FoFiType1Tokenizer
{
public:
    explicit FoFiType1Tokenizer(std::string_view &&stringViewA) : stringView(stringViewA) { }

    std::optional<std::string_view> getToken()
    {
        const auto length = stringView.length();
        if (currentPos >= length) {
            return {};
        }

        std::string_view::size_type pos = stringView.find_first_of(tokenSeparators, currentPos);
        while (pos == currentPos) {
            ++currentPos;
            pos = stringView.find_first_of(tokenSeparators, currentPos);
        }

        if (pos == std::string_view::npos) {
            const auto tokenLength = length - currentPos;
            if (tokenLength > 0) {
                std::string_view token = stringView.substr(currentPos, tokenLength);
                currentPos = length;
                return token;
            }
            currentPos = length;
            return {};
        }

        std::string_view token = stringView.substr(currentPos, pos - currentPos);
        currentPos = pos + 1;
        return token;
    }

private:
    std::string_view::size_type currentPos = 0;
    const std::string_view stringView;
};

// Helper to collect all tokens from a tokenizer
std::vector<std::string> collectAllTokens(FoFiType1Tokenizer &tokenizer)
{
    std::vector<std::string> tokens;
    while (auto tok = tokenizer.getToken()) {
        tokens.emplace_back(*tok);
    }
    return tokens;
}

class FoFiType1TokenizerTest_49 : public ::testing::Test
{
};

// Test that an empty string produces no tokens
TEST_F(FoFiType1TokenizerTest_49, EmptyString_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view(""));
    auto token = tokenizer.getToken();
    EXPECT_FALSE(token.has_value());
}

// Test a single token with no separators
TEST_F(FoFiType1TokenizerTest_49, SingleTokenNoSeparators_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("hello"));
    auto token = tokenizer.getToken();
    ASSERT_TRUE(token.has_value());
    EXPECT_EQ(*token, "hello");

    auto token2 = tokenizer.getToken();
    EXPECT_FALSE(token2.has_value());
}

// Test two tokens separated by a space
TEST_F(FoFiType1TokenizerTest_49, TwoTokensSeparatedBySpace_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("hello world"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0], "hello");
    EXPECT_EQ(tokens[1], "world");
}

// Test multiple tokens separated by various whitespace
TEST_F(FoFiType1TokenizerTest_49, MultipleTokensVariousSeparators_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("one\ttwo\nthree\rfour"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 4u);
    EXPECT_EQ(tokens[0], "one");
    EXPECT_EQ(tokens[1], "two");
    EXPECT_EQ(tokens[2], "three");
    EXPECT_EQ(tokens[3], "four");
}

// Test leading separators are skipped
TEST_F(FoFiType1TokenizerTest_49, LeadingSeparators_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("   hello"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 1u);
    EXPECT_EQ(tokens[0], "hello");
}

// Test trailing separators are handled
TEST_F(FoFiType1TokenizerTest_49, TrailingSeparators_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("hello   "));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 1u);
    EXPECT_EQ(tokens[0], "hello");
}

// Test multiple consecutive separators between tokens
TEST_F(FoFiType1TokenizerTest_49, MultipleSeparatorsBetweenTokens_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("hello   \t\n  world"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0], "hello");
    EXPECT_EQ(tokens[1], "world");
}

// Test string consisting only of separators
TEST_F(FoFiType1TokenizerTest_49, OnlySeparators_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("   \t\n\r  "));
    auto token = tokenizer.getToken();
    EXPECT_FALSE(token.has_value());
}

// Test single character token
TEST_F(FoFiType1TokenizerTest_49, SingleCharacterToken_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("a"));
    auto token = tokenizer.getToken();
    ASSERT_TRUE(token.has_value());
    EXPECT_EQ(*token, "a");

    auto token2 = tokenizer.getToken();
    EXPECT_FALSE(token2.has_value());
}

// Test single separator character
TEST_F(FoFiType1TokenizerTest_49, SingleSeparatorCharacter_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view(" "));
    auto token = tokenizer.getToken();
    EXPECT_FALSE(token.has_value());
}

// Test calling getToken after exhaustion returns empty repeatedly
TEST_F(FoFiType1TokenizerTest_49, RepeatedCallsAfterExhaustion_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("hello"));
    auto token1 = tokenizer.getToken();
    ASSERT_TRUE(token1.has_value());
    EXPECT_EQ(*token1, "hello");

    auto token2 = tokenizer.getToken();
    EXPECT_FALSE(token2.has_value());

    auto token3 = tokenizer.getToken();
    EXPECT_FALSE(token3.has_value());

    auto token4 = tokenizer.getToken();
    EXPECT_FALSE(token4.has_value());
}

// Test with tab as only separator
TEST_F(FoFiType1TokenizerTest_49, TabSeparator_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("foo\tbar"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0], "foo");
    EXPECT_EQ(tokens[1], "bar");
}

// Test with newline as separator
TEST_F(FoFiType1TokenizerTest_49, NewlineSeparator_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("foo\nbar"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0], "foo");
    EXPECT_EQ(tokens[1], "bar");
}

// Test with carriage return as separator
TEST_F(FoFiType1TokenizerTest_49, CarriageReturnSeparator_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("foo\rbar"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0], "foo");
    EXPECT_EQ(tokens[1], "bar");
}

// Test mixed separators at beginning, middle, and end
TEST_F(FoFiType1TokenizerTest_49, MixedSeparatorsEverywhere_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("\t\n abc \r\n def \t "));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0], "abc");
    EXPECT_EQ(tokens[1], "def");
}

// Test with many tokens
TEST_F(FoFiType1TokenizerTest_49, ManyTokens_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("a b c d e f g h i j"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 10u);
    EXPECT_EQ(tokens[0], "a");
    EXPECT_EQ(tokens[9], "j");
}

// Test that non-separator special characters are preserved in tokens
TEST_F(FoFiType1TokenizerTest_49, SpecialCharactersInTokens_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("/FontName (hello) {def}"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 3u);
    EXPECT_EQ(tokens[0], "/FontName");
    EXPECT_EQ(tokens[1], "(hello)");
    EXPECT_EQ(tokens[2], "{def}");
}

// Test typical PostScript-like content
TEST_F(FoFiType1TokenizerTest_49, PostScriptLikeContent_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("/FontType 1 def"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 3u);
    EXPECT_EQ(tokens[0], "/FontType");
    EXPECT_EQ(tokens[1], "1");
    EXPECT_EQ(tokens[2], "def");
}

// Test with CRLF line endings
TEST_F(FoFiType1TokenizerTest_49, CRLFLineEndings_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("line1\r\nline2\r\nline3"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 3u);
    EXPECT_EQ(tokens[0], "line1");
    EXPECT_EQ(tokens[1], "line2");
    EXPECT_EQ(tokens[2], "line3");
}

// Test token with all separator types surrounding it
TEST_F(FoFiType1TokenizerTest_49, AllSeparatorsSurrounding_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view(" \t\r\ntoken \t\r\n"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 1u);
    EXPECT_EQ(tokens[0], "token");
}

// Test long token without any separators
TEST_F(FoFiType1TokenizerTest_49, LongTokenNoSeparators_49)
{
    std::string longStr(1000, 'x');
    FoFiType1Tokenizer tokenizer(std::string_view(longStr));
    auto token = tokenizer.getToken();
    ASSERT_TRUE(token.has_value());
    EXPECT_EQ(token->length(), 1000u);
    EXPECT_EQ(*token, longStr);
}

// Test that returned string_view points to correct data
TEST_F(FoFiType1TokenizerTest_49, ReturnedViewsAreCorrect_49)
{
    std::string input = "abc def ghi";
    FoFiType1Tokenizer tokenizer(std::string_view(input));

    auto t1 = tokenizer.getToken();
    ASSERT_TRUE(t1.has_value());
    EXPECT_EQ(*t1, "abc");
    // Verify it's a view into the original string
    EXPECT_GE(t1->data(), input.data());
    EXPECT_LE(t1->data(), input.data() + input.size());

    auto t2 = tokenizer.getToken();
    ASSERT_TRUE(t2.has_value());
    EXPECT_EQ(*t2, "def");

    auto t3 = tokenizer.getToken();
    ASSERT_TRUE(t3.has_value());
    EXPECT_EQ(*t3, "ghi");

    auto t4 = tokenizer.getToken();
    EXPECT_FALSE(t4.has_value());
}

// Test two single-char tokens separated by one separator
TEST_F(FoFiType1TokenizerTest_49, TwoSingleCharTokens_49)
{
    FoFiType1Tokenizer tokenizer(std::string_view("a b"));
    auto tokens = collectAllTokens(tokenizer);
    ASSERT_EQ(tokens.size(), 2u);
    EXPECT_EQ(tokens[0], "a");
    EXPECT_EQ(tokens[1], "b");
}
