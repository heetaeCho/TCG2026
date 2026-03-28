#include <gtest/gtest.h>
#include <string>

// We need to provide the helper function that myXmlTokenReplace depends on
static std::string myStringReplace(std::string myString, const std::string &match, const std::string &replaceStr)
{
    size_t pos = 0;
    while ((pos = myString.find(match, pos)) != std::string::npos) {
        myString.replace(pos, match.length(), replaceStr);
        pos += replaceStr.length();
    }
    return myString;
}

// Copy the function under test
static std::string myXmlTokenReplace(const char *inString)
{
    std::string myString(inString);
    myString = myStringReplace(myString, "&", "&amp;");
    myString = myStringReplace(myString, "'", "&apos;");
    myString = myStringReplace(myString, "\"", "&quot;");
    myString = myStringReplace(myString, "<", "&lt;");
    myString = myStringReplace(myString, ">", "&gt;");
    return myString;
}

class XmlTokenReplaceTest_2721 : public ::testing::Test {};

// Test empty string input
TEST_F(XmlTokenReplaceTest_2721, EmptyString_2721)
{
    std::string result = myXmlTokenReplace("");
    EXPECT_EQ(result, "");
}

// Test string with no special characters
TEST_F(XmlTokenReplaceTest_2721, NoSpecialCharacters_2721)
{
    std::string result = myXmlTokenReplace("hello world");
    EXPECT_EQ(result, "hello world");
}

// Test ampersand replacement
TEST_F(XmlTokenReplaceTest_2721, AmpersandReplacement_2721)
{
    std::string result = myXmlTokenReplace("foo & bar");
    EXPECT_EQ(result, "foo &amp; bar");
}

// Test single quote (apostrophe) replacement
TEST_F(XmlTokenReplaceTest_2721, ApostropheReplacement_2721)
{
    std::string result = myXmlTokenReplace("it's");
    EXPECT_EQ(result, "it&apos;s");
}

// Test double quote replacement
TEST_F(XmlTokenReplaceTest_2721, DoubleQuoteReplacement_2721)
{
    std::string result = myXmlTokenReplace("say \"hello\"");
    EXPECT_EQ(result, "say &quot;hello&quot;");
}

// Test less-than replacement
TEST_F(XmlTokenReplaceTest_2721, LessThanReplacement_2721)
{
    std::string result = myXmlTokenReplace("a < b");
    EXPECT_EQ(result, "a &lt; b");
}

// Test greater-than replacement
TEST_F(XmlTokenReplaceTest_2721, GreaterThanReplacement_2721)
{
    std::string result = myXmlTokenReplace("a > b");
    EXPECT_EQ(result, "a &gt; b");
}

// Test all special characters together
TEST_F(XmlTokenReplaceTest_2721, AllSpecialCharacters_2721)
{
    std::string result = myXmlTokenReplace("&'\"<>");
    EXPECT_EQ(result, "&amp;&apos;&quot;&lt;&gt;");
}

// Test multiple occurrences of the same special character
TEST_F(XmlTokenReplaceTest_2721, MultipleAmpersands_2721)
{
    std::string result = myXmlTokenReplace("a&b&c&d");
    EXPECT_EQ(result, "a&amp;b&amp;c&amp;d");
}

// Test special characters mixed with regular text
TEST_F(XmlTokenReplaceTest_2721, MixedContent_2721)
{
    std::string result = myXmlTokenReplace("<div class=\"test\">Hello & 'World'</div>");
    EXPECT_EQ(result, "&lt;div class=&quot;test&quot;&gt;Hello &amp; &apos;World&apos;&lt;/div&gt;");
}

// Test string that is only a single ampersand
TEST_F(XmlTokenReplaceTest_2721, SingleAmpersand_2721)
{
    std::string result = myXmlTokenReplace("&");
    EXPECT_EQ(result, "&amp;");
}

// Test string that is only a single less-than
TEST_F(XmlTokenReplaceTest_2721, SingleLessThan_2721)
{
    std::string result = myXmlTokenReplace("<");
    EXPECT_EQ(result, "&lt;");
}

// Test string that is only a single greater-than
TEST_F(XmlTokenReplaceTest_2721, SingleGreaterThan_2721)
{
    std::string result = myXmlTokenReplace(">");
    EXPECT_EQ(result, "&gt;");
}

// Test string that is only a single quote
TEST_F(XmlTokenReplaceTest_2721, SingleQuote_2721)
{
    std::string result = myXmlTokenReplace("'");
    EXPECT_EQ(result, "&apos;");
}

// Test string that is only a double quote
TEST_F(XmlTokenReplaceTest_2721, SingleDoubleQuote_2721)
{
    std::string result = myXmlTokenReplace("\"");
    EXPECT_EQ(result, "&quot;");
}

// Test consecutive special characters
TEST_F(XmlTokenReplaceTest_2721, ConsecutiveSpecialChars_2721)
{
    std::string result = myXmlTokenReplace("<<>>");
    EXPECT_EQ(result, "&lt;&lt;&gt;&gt;");
}

// Test that already-escaped entities get double-escaped (ampersand is replaced first)
TEST_F(XmlTokenReplaceTest_2721, AlreadyEscapedEntity_2721)
{
    std::string result = myXmlTokenReplace("&amp;");
    EXPECT_EQ(result, "&amp;amp;");
}

// Test string with numeric and alphanumeric content only
TEST_F(XmlTokenReplaceTest_2721, NumericContent_2721)
{
    std::string result = myXmlTokenReplace("12345 abcde ABCDE");
    EXPECT_EQ(result, "12345 abcde ABCDE");
}

// Test string with special characters at boundaries
TEST_F(XmlTokenReplaceTest_2721, SpecialCharsAtBoundaries_2721)
{
    std::string result = myXmlTokenReplace("&hello&");
    EXPECT_EQ(result, "&amp;hello&amp;");
}

// Test a long string with various special chars
TEST_F(XmlTokenReplaceTest_2721, LongMixedString_2721)
{
    std::string result = myXmlTokenReplace("This is a \"test\" of <xml> & 'entities' for > safety");
    EXPECT_EQ(result, "This is a &quot;test&quot; of &lt;xml&gt; &amp; &apos;entities&apos; for &gt; safety");
}

// Test whitespace-only string
TEST_F(XmlTokenReplaceTest_2721, WhitespaceOnly_2721)
{
    std::string result = myXmlTokenReplace("   \t\n  ");
    EXPECT_EQ(result, "   \t\n  ");
}

// Test string with newlines and special chars
TEST_F(XmlTokenReplaceTest_2721, NewlinesAndSpecialChars_2721)
{
    std::string result = myXmlTokenReplace("line1\n<tag>\nline2");
    EXPECT_EQ(result, "line1\n&lt;tag&gt;\nline2");
}
