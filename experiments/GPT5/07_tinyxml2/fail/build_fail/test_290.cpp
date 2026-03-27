// TEST_ID: 290
// File: test_xmlprinter_print_290.cpp

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

// Include the library header under test.
#include "tinyxml2.h"

namespace {

class TestableXMLPrinter_290 : public tinyxml2::XMLPrinter {
public:
    using tinyxml2::XMLPrinter::XMLPrinter;

    // Expose the protected varargs Print(...) for testing.
    // NOTE: XMLPrinter also has a protected virtual Print(const char*), so in tests
    // we always call with at least one additional argument to avoid overload ambiguity.
    using tinyxml2::XMLPrinter::Print;
};

static std::string ReadAllFromFile_290(FILE* fp) {
    if (!fp) return {};
    std::fflush(fp);
    std::fseek(fp, 0, SEEK_SET);

    std::string out;
    char buf[256];
    while (true) {
        const size_t n = std::fread(buf, 1, sizeof(buf), fp);
        if (n > 0) out.append(buf, buf + n);
        if (n < sizeof(buf)) break;
    }
    return out;
}

static tinyxml2::EscapeAposCharsInAttributes DefaultAposMode_290() {
    // Avoid depending on specific enumerator names; treat as an implementation detail.
    return static_cast<tinyxml2::EscapeAposCharsInAttributes>(0);
}

}  // namespace

// -------------------- Buffer mode (_fp == nullptr) --------------------

TEST(XMLPrinterPrintTest_290, PrintFormatsIntoInternalBuffer_290) {
    TestableXMLPrinter_290 printer(/*file=*/nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    // Produce formatted text.
    printer.Print("%d %s", 42, "ok");

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "42 ok");
    EXPECT_EQ(printer.CStrSize(), std::strlen("42 ok") + 1u);  // includes NUL
}

TEST(XMLPrinterPrintTest_290, PrintAppendsOnMultipleCallsInBufferMode_290) {
    TestableXMLPrinter_290 printer(/*file=*/nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    printer.Print("%s", "Hello");
    printer.Print("%s", ", ");
    printer.Print("%s", "World");

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "Hello, World");
    EXPECT_EQ(printer.CStrSize(), std::strlen("Hello, World") + 1u);
}

TEST(XMLPrinterPrintTest_290, PrintWithEmptyFormattedStringDoesNotCorruptBuffer_290) {
    TestableXMLPrinter_290 printer(/*file=*/nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    printer.Print("%s", "");
    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "");
    EXPECT_GE(printer.CStrSize(), 1u);
    EXPECT_EQ(printer.CStr()[printer.CStrSize() - 1], '\0');
}

TEST(XMLPrinterPrintTest_290, PrintLargeOutputGrowsBufferAndPreservesContent_290) {
    TestableXMLPrinter_290 printer(/*file=*/nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    std::string big(500, 'x');
    printer.Print("%s", big.c_str());

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_EQ(std::strlen(printer.CStr()), big.size());
    EXPECT_EQ(std::string(printer.CStr()), big);
    EXPECT_EQ(printer.CStrSize(), big.size() + 1u);
}

TEST(XMLPrinterPrintTest_290, PrintClearBufferResetsThenPrintWorksAgain_290) {
    TestableXMLPrinter_290 printer(/*file=*/nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    printer.Print("%s", "abc");
    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "abc");

    printer.ClearBuffer();
    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "");

    printer.Print("%s", "xyz");
    EXPECT_STREQ(printer.CStr(), "xyz");
}

// -------------------- File mode (_fp != nullptr) --------------------

TEST(XMLPrinterPrintTest_290, PrintWritesToFileWhenFileProvided_290) {
    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    TestableXMLPrinter_290 printer(/*file=*/fp, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    printer.Print("%s", "file-out");

    const std::string content = ReadAllFromFile_290(fp);
    EXPECT_EQ(content, "file-out");

    std::fclose(fp);
}

TEST(XMLPrinterPrintTest_290, PrintFormatsAndAppendsToFileAcrossCalls_290) {
    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    TestableXMLPrinter_290 printer(/*file=*/fp, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    printer.Print("%s", "A");
    printer.Print("%s", " ");
    printer.Print("%d", 7);
    printer.Print("%s", " ");
    printer.Print("%s", "Z");

    const std::string content = ReadAllFromFile_290(fp);
    EXPECT_EQ(content, "A 7 Z");

    std::fclose(fp);
}

TEST(XMLPrinterPrintTest_290, PrintWithVariousFormatSpecifiersToFile_290) {
    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    TestableXMLPrinter_290 printer(/*file=*/fp, /*compact=*/false, /*depth=*/0, DefaultAposMode_290());

    printer.Print("int=%d str=%s hex=%x", 12, "hi", 255);

    const std::string content = ReadAllFromFile_290(fp);
    EXPECT_EQ(content, "int=12 str=hi hex=ff");

    std::fclose(fp);
}
