#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>

#include "goo/GooString.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/UnicodeMap.h"
#include "poppler/PDFDocEncoding.h"

// We need to include the source to access the static function
// or declare it extern if possible. Since it's static, we include the cc file.
// This is a common technique for testing static functions.
#include "pdftotext.cc"

class PrintInfoStringTest_2723 : public ::testing::Test {
protected:
    FILE *tmpFile;
    std::string tmpFileName;

    void SetUp() override {
        tmpFile = tmpfile();
        ASSERT_NE(tmpFile, nullptr);
    }

    void TearDown() override {
        if (tmpFile) {
            fclose(tmpFile);
        }
    }

    std::string readFileContents() {
        fflush(tmpFile);
        rewind(tmpFile);
        std::string result;
        char buf[1024];
        while (fgets(buf, sizeof(buf), tmpFile)) {
            result += buf;
        }
        return result;
    }

    // Helper to create a Dict with a string entry
    Dict* createDictWithString(const char* key, const std::string& value) {
        Dict* dict = new Dict(nullptr);
        dict->add(key, Object(std::make_unique<GooString>(value)));
        return dict;
    }

    Dict* createDictWithString(const char* key, const char* data, size_t len) {
        Dict* dict = new Dict(nullptr);
        dict->add(key, Object(std::make_unique<GooString>(data, len)));
        return dict;
    }

    Dict* createEmptyDict() {
        return new Dict(nullptr);
    }

    std::unique_ptr<UnicodeMap> getLatinMap() {
        // Try to get a Latin1 or ASCII unicode map
        auto uMap = UnicodeMap::parse("Latin1");
        if (!uMap) {
            uMap = UnicodeMap::parse("ASCII7");
        }
        return uMap;
    }
};

// Test that when the key is not found in the dict, nothing is printed
TEST_F(PrintInfoStringTest_2723, KeyNotFound_2723) {
    Dict* dict = createEmptyDict();
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "<title>", "</title>", uMap.get());

    std::string output = readFileContents();
    EXPECT_TRUE(output.empty());

    delete dict;
}

// Test that when the key maps to a non-string object, nothing is printed
TEST_F(PrintInfoStringTest_2723, NonStringValue_2723) {
    Dict* dict = new Dict(nullptr);
    dict->add("Count", Object(42));
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Count", "<count>", "</count>", uMap.get());

    std::string output = readFileContents();
    EXPECT_TRUE(output.empty());

    delete dict;
}

// Test basic ASCII / PDFDocEncoding string
TEST_F(PrintInfoStringTest_2723, BasicAsciiString_2723) {
    Dict* dict = createDictWithString("Title", "Hello");
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "<title>", "</title>", uMap.get());

    std::string output = readFileContents();
    EXPECT_FALSE(output.empty());
    // Should contain the prefix and suffix
    EXPECT_NE(output.find("<title>"), std::string::npos);
    EXPECT_NE(output.find("</title>"), std::string::npos);

    delete dict;
}

// Test Unicode BOM string (0xFE 0xFF prefix)
TEST_F(PrintInfoStringTest_2723, UnicodeBOMString_2723) {
    // Create a Unicode string with BOM: FE FF followed by 'A' (0x00 0x41)
    char unicodeData[] = {(char)0xFE, (char)0xFF, (char)0x00, (char)0x41, '\0'};
    Dict* dict = createDictWithString("Title", unicodeData, 4);
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "[", "]", uMap.get());

    std::string output = readFileContents();
    EXPECT_FALSE(output.empty());
    EXPECT_EQ(output.front(), '[');
    EXPECT_EQ(output.back(), ']');

    delete dict;
}

// Test empty string value
TEST_F(PrintInfoStringTest_2723, EmptyStringValue_2723) {
    Dict* dict = createDictWithString("Title", "");
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "<<", ">>", uMap.get());

    std::string output = readFileContents();
    // Should have just the prefix and suffix since the string is empty
    EXPECT_EQ(output, "<<>>");

    delete dict;
}

// Test XML special characters get replaced (& < > etc.)
TEST_F(PrintInfoStringTest_2723, XmlSpecialCharsReplaced_2723) {
    Dict* dict = createDictWithString("Title", "A&B");
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "", "", uMap.get());

    std::string output = readFileContents();
    // '&' should be replaced by '&amp;' due to myXmlTokenReplace
    EXPECT_NE(output.find("&amp;"), std::string::npos);

    delete dict;
}

// Test XML less-than character replacement
TEST_F(PrintInfoStringTest_2723, XmlLessThanReplaced_2723) {
    Dict* dict = createDictWithString("Title", "A<B");
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "", "", uMap.get());

    std::string output = readFileContents();
    EXPECT_NE(output.find("&lt;"), std::string::npos);

    delete dict;
}

// Test XML greater-than character replacement
TEST_F(PrintInfoStringTest_2723, XmlGreaterThanReplaced_2723) {
    Dict* dict = createDictWithString("Title", "A>B");
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "", "", uMap.get());

    std::string output = readFileContents();
    EXPECT_NE(output.find("&gt;"), std::string::npos);

    delete dict;
}

// Test that text1 and text2 are correctly written around the content
TEST_F(PrintInfoStringTest_2723, PrefixAndSuffixWritten_2723) {
    Dict* dict = createDictWithString("Author", "Test");
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Author", "PREFIX_", "_SUFFIX", uMap.get());

    std::string output = readFileContents();
    // Check prefix is at the start
    EXPECT_EQ(output.substr(0, 7), "PREFIX_");
    // Check suffix is at the end
    size_t len = output.size();
    EXPECT_GE(len, 7u);
    EXPECT_EQ(output.substr(len - 7), "_SUFFIX");

    delete dict;
}

// Test Unicode BOM with multiple characters
TEST_F(PrintInfoStringTest_2723, UnicodeBOMMultipleChars_2723) {
    // BOM + "AB" in UTF-16BE: FE FF 00 41 00 42
    char unicodeData[] = {(char)0xFE, (char)0xFF, (char)0x00, (char)0x41, (char)0x00, (char)0x42};
    Dict* dict = createDictWithString("Title", unicodeData, 6);
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "", "", uMap.get());

    std::string output = readFileContents();
    EXPECT_FALSE(output.empty());

    delete dict;
}

// Test single character PDFDocEncoding string
TEST_F(PrintInfoStringTest_2723, SingleCharPDFDocEncoding_2723) {
    Dict* dict = createDictWithString("Title", "X");
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "(", ")", uMap.get());

    std::string output = readFileContents();
    EXPECT_EQ(output.front(), '(');
    EXPECT_EQ(output.back(), ')');

    delete dict;
}

// Test with only BOM and no actual content (Unicode string with just BOM)
TEST_F(PrintInfoStringTest_2723, UnicodeBOMOnlyNoContent_2723) {
    char unicodeData[] = {(char)0xFE, (char)0xFF};
    Dict* dict = createDictWithString("Title", unicodeData, 2);
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "[", "]", uMap.get());

    std::string output = readFileContents();
    // Should just be prefix + suffix with no content in between
    EXPECT_EQ(output, "[]");

    delete dict;
}

// Test different key names
TEST_F(PrintInfoStringTest_2723, DifferentKeyName_2723) {
    Dict* dict = new Dict(nullptr);
    dict->add("Author", Object(std::make_unique<GooString>("John")));
    dict->add("Title", Object(std::make_unique<GooString>("Book")));
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Author", "<a>", "</a>", uMap.get());

    std::string output = readFileContents();
    EXPECT_NE(output.find("<a>"), std::string::npos);
    EXPECT_NE(output.find("</a>"), std::string::npos);

    delete dict;
}

// Test that a string starting with 0xFE but not followed by 0xFF is treated as PDFDocEncoding
TEST_F(PrintInfoStringTest_2723, FEWithoutFFNotUnicode_2723) {
    char data[] = {(char)0xFE, (char)0x41}; // FE followed by 'A', not FF
    Dict* dict = createDictWithString("Title", data, 2);
    auto uMap = getLatinMap();
    if (!uMap) {
        GTEST_SKIP() << "Could not create UnicodeMap";
    }

    printInfoString(tmpFile, dict, "Title", "", "", uMap.get());

    std::string output = readFileContents();
    // Should be treated as PDFDocEncoding, not Unicode
    EXPECT_FALSE(output.empty());

    delete dict;
}
