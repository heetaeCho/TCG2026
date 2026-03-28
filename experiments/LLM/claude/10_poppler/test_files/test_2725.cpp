#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <sstream>
#include <iomanip>
#include <memory>

// Include necessary headers
#include "TextOutputDev.h"
#include "GfxState.h"
#include "GfxFont.h"

// The function under test is static in pdftotext.cc, so we need to
// either include it or declare it. We'll include the relevant parts.
// Since printLine is static, we need to make it accessible for testing.
// We'll redefine it or use a test-accessible version.

// For testing, we include the source with a workaround
// to make the static function accessible.
#define static
#include "pdftotext.cc"
#undef static

class PrintLineTest_2725 : public ::testing::Test {
protected:
    FILE *tmpFile;
    
    void SetUp() override {
        tmpFile = tmpfile();
        ASSERT_NE(tmpFile, nullptr);
    }
    
    void TearDown() override {
        if (tmpFile) {
            fclose(tmpFile);
        }
    }
    
    std::string readTmpFile() {
        fflush(tmpFile);
        fseek(tmpFile, 0, SEEK_SET);
        std::string result;
        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), tmpFile)) > 0) {
            result.append(buf, n);
        }
        return result;
    }
};

// Test myXmlTokenReplace function for normal text
TEST_F(PrintLineTest_2725, XmlTokenReplaceNormalText_2725) {
    std::string result = myXmlTokenReplace("hello");
    EXPECT_EQ(result, "hello");
}

// Test myXmlTokenReplace function for text with ampersand
TEST_F(PrintLineTest_2725, XmlTokenReplaceAmpersand_2725) {
    std::string result = myXmlTokenReplace("a&b");
    EXPECT_NE(result.find("&amp;"), std::string::npos);
}

// Test myXmlTokenReplace function for text with less-than
TEST_F(PrintLineTest_2725, XmlTokenReplaceLessThan_2725) {
    std::string result = myXmlTokenReplace("a<b");
    EXPECT_NE(result.find("&lt;"), std::string::npos);
}

// Test myXmlTokenReplace function for text with greater-than
TEST_F(PrintLineTest_2725, XmlTokenReplaceGreaterThan_2725) {
    std::string result = myXmlTokenReplace("a>b");
    EXPECT_NE(result.find("&gt;"), std::string::npos);
}

// Test myXmlTokenReplace function for text with quote
TEST_F(PrintLineTest_2725, XmlTokenReplaceQuote_2725) {
    std::string result = myXmlTokenReplace("a\"b");
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

// Test myXmlTokenReplace function for empty string
TEST_F(PrintLineTest_2725, XmlTokenReplaceEmptyString_2725) {
    std::string result = myXmlTokenReplace("");
    EXPECT_EQ(result, "");
}

// Test myXmlTokenReplace function for multiple special characters
TEST_F(PrintLineTest_2725, XmlTokenReplaceMultipleSpecialChars_2725) {
    std::string result = myXmlTokenReplace("<>&\"");
    EXPECT_NE(result.find("&lt;"), std::string::npos);
    EXPECT_NE(result.find("&gt;"), std::string::npos);
    EXPECT_NE(result.find("&amp;"), std::string::npos);
    EXPECT_NE(result.find("&quot;"), std::string::npos);
}

// Test myXmlTokenReplace with no special characters
TEST_F(PrintLineTest_2725, XmlTokenReplaceNoSpecialChars_2725) {
    std::string result = myXmlTokenReplace("plain text 123");
    EXPECT_EQ(result, "plain text 123");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
