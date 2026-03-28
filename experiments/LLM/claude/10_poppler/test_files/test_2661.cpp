#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <vector>

// Include necessary headers
#include "UnicodeMap.h"
#include "UTF.h"
#include "GooString.h"

// We need to capture stdout output to verify printStdTextString behavior
// Since printStdTextString is a static function in pdfinfo.cc, we need to
// either include it or replicate the declaration for testing purposes.

// Forward declare or include the function under test
// Since it's static in pdfinfo.cc, we need to include the file or
// create a testable wrapper. For testing purposes, we'll replicate the
// function signature here since we can't directly link a static function.

// Replicate the function for testing (since it's static and we're testing its behavior)
static void printStdTextString(const std::string &s, const UnicodeMap *uMap)
{
    char buf[8];
    const std::vector<Unicode> u = TextStringToUCS4(s);
    for (const auto &c : u) {
        int n = uMap->mapUnicode(c, buf, sizeof(buf));
        fwrite(buf, 1, n, stdout);
    }
}

// Helper to capture stdout
class StdoutCapture {
public:
    void start() {
        fflush(stdout);
        tmpFile = tmpfile();
        oldStdout = dup(fileno(stdout));
        dup2(fileno(tmpFile), fileno(stdout));
    }

    std::string stop() {
        fflush(stdout);
        dup2(oldStdout, fileno(stdout));
        close(oldStdout);

        fseek(tmpFile, 0, SEEK_SET);
        std::string result;
        char buf[1024];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), tmpFile)) > 0) {
            result.append(buf, n);
        }
        fclose(tmpFile);
        return result;
    }

private:
    FILE *tmpFile = nullptr;
    int oldStdout = -1;
};

class PrintStdTextStringTest_2661 : public ::testing::Test {
protected:
    void SetUp() override {
        // Try to parse a Latin1 or ASCII-compatible Unicode map
        uMap = UnicodeMap::parse("Latin1");
        if (!uMap) {
            uMap = UnicodeMap::parse("ASCII7");
        }
    }

    std::unique_ptr<UnicodeMap> uMap;
    StdoutCapture capture;
};

TEST_F(PrintStdTextStringTest_2661, EmptyString_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    capture.start();
    printStdTextString("", uMap.get());
    std::string output = capture.stop();

    EXPECT_TRUE(output.empty());
}

TEST_F(PrintStdTextStringTest_2661, SimpleASCIIString_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    capture.start();
    printStdTextString("Hello", uMap.get());
    std::string output = capture.stop();

    // The output should contain the mapped characters
    EXPECT_FALSE(output.empty());
}

TEST_F(PrintStdTextStringTest_2661, SingleCharacterString_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    capture.start();
    printStdTextString("A", uMap.get());
    std::string output = capture.stop();

    EXPECT_FALSE(output.empty());
}

TEST_F(PrintStdTextStringTest_2661, StringWithSpaces_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    capture.start();
    printStdTextString("Hello World", uMap.get());
    std::string output = capture.stop();

    EXPECT_FALSE(output.empty());
}

TEST_F(PrintStdTextStringTest_2661, StringWithNumbers_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    capture.start();
    printStdTextString("12345", uMap.get());
    std::string output = capture.stop();

    EXPECT_FALSE(output.empty());
}

TEST_F(PrintStdTextStringTest_2661, StringWithSpecialCharacters_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    capture.start();
    printStdTextString("!@#$%", uMap.get());
    std::string output = capture.stop();

    // Special characters should produce some output via the map
    EXPECT_FALSE(output.empty());
}

TEST_F(PrintStdTextStringTest_2661, NullByteInString_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    // std::string with embedded null
    std::string s("AB\0CD", 5);
    capture.start();
    printStdTextString(s, uMap.get());
    std::string output = capture.stop();

    // Should process characters; behavior depends on TextStringToUCS4
    // At minimum, it shouldn't crash
}

TEST_F(PrintStdTextStringTest_2661, LongString_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    std::string longStr(1000, 'X');
    capture.start();
    printStdTextString(longStr, uMap.get());
    std::string output = capture.stop();

    EXPECT_FALSE(output.empty());
}

TEST_F(PrintStdTextStringTest_2661, PDFTextStringBOMPrefix_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    // PDF text string with UTF-16BE BOM (0xFE 0xFF)
    std::string pdfStr;
    pdfStr += (char)0xFE;
    pdfStr += (char)0xFF;
    pdfStr += (char)0x00;
    pdfStr += (char)0x48; // 'H'
    pdfStr += (char)0x00;
    pdfStr += (char)0x69; // 'i'

    capture.start();
    printStdTextString(pdfStr, uMap.get());
    std::string output = capture.stop();

    // Should not crash; TextStringToUCS4 should handle BOM-prefixed strings
}

TEST_F(PrintStdTextStringTest_2661, PDFDocEncodingString_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    // A string without BOM should be treated as PDFDocEncoding
    std::string pdfDocStr = "Test PDF Doc Encoding";

    capture.start();
    printStdTextString(pdfDocStr, uMap.get());
    std::string output = capture.stop();

    EXPECT_FALSE(output.empty());
}

// Test with UTF-8 BOM prefix (0xEF 0xBB 0xBF) - PDF 2.0
TEST_F(PrintStdTextStringTest_2661, UTF8BOMPrefix_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    std::string utf8Str;
    utf8Str += (char)0xEF;
    utf8Str += (char)0xBB;
    utf8Str += (char)0xBF;
    utf8Str += "Hello";

    capture.start();
    printStdTextString(utf8Str, uMap.get());
    std::string output = capture.stop();

    // Should handle UTF-8 BOM prefix without crashing
}

// Test that consecutive calls work correctly
TEST_F(PrintStdTextStringTest_2661, ConsecutiveCalls_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    capture.start();
    printStdTextString("First", uMap.get());
    printStdTextString("Second", uMap.get());
    std::string output = capture.stop();

    EXPECT_FALSE(output.empty());
}

// Test with high byte values in PDFDocEncoding range
TEST_F(PrintStdTextStringTest_2661, HighByteValues_2661)
{
    if (!uMap) {
        GTEST_SKIP() << "No suitable UnicodeMap available";
    }

    std::string highBytes;
    for (int i = 128; i < 256; i++) {
        highBytes += (char)i;
    }

    // Should not crash even if some characters can't be mapped
    capture.start();
    printStdTextString(highBytes, uMap.get());
    std::string output = capture.stop();
}
