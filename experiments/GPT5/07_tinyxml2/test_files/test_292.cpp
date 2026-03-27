// TEST_ID: 292
#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace {

class TestXMLPrinter_292 : public tinyxml2::XMLPrinter {
public:
    using tinyxml2::XMLPrinter::XMLPrinter;

    void PutcPublic(char ch) { Putc(ch); } // expose protected Putc for testing
};

static std::string ReadAllFromFile(FILE* fp) {
    std::string out;
    if (!fp) return out;

    std::fflush(fp);
    std::rewind(fp);

    char buf[256];
    while (true) {
        const size_t n = std::fread(buf, 1, sizeof(buf), fp);
        if (n == 0) break;
        out.append(buf, buf + n);
    }
    return out;
}

} // namespace

TEST(XMLPrinterPutcTest_292, BufferMode_AppendsSingleCharacter_292) {
    // Use a safe cast so the test doesn't depend on specific enum constants.
    const auto apos = static_cast<tinyxml2::EscapeAposCharsInAttributes>(0);

    TestXMLPrinter_292 printer(nullptr, /*compact=*/false, /*depth=*/0, apos);
    printer.PutcPublic('A');

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "A");

    // CStrSize() is expected to be consistent with the C string length.
    EXPECT_EQ(std::strlen(printer.CStr()), printer.CStrSize());
}

TEST(XMLPrinterPutcTest_292, BufferMode_AppendsMultipleCharactersInOrder_292) {
    const auto apos = static_cast<tinyxml2::EscapeAposCharsInAttributes>(0);

    TestXMLPrinter_292 printer(nullptr, /*compact=*/false, /*depth=*/0, apos);
    printer.PutcPublic('a');
    printer.PutcPublic('b');
    printer.PutcPublic('c');

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "abc");
    EXPECT_EQ(std::strlen(printer.CStr()), printer.CStrSize());
}

TEST(XMLPrinterPutcTest_292, BufferMode_AllowsNewlineCharacter_292) {
    const auto apos = static_cast<tinyxml2::EscapeAposCharsInAttributes>(0);

    TestXMLPrinter_292 printer(nullptr, /*compact=*/false, /*depth=*/0, apos);
    printer.PutcPublic('x');
    printer.PutcPublic('\n');
    printer.PutcPublic('y');

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_STREQ(printer.CStr(), "x\ny");
    EXPECT_EQ(std::strlen(printer.CStr()), printer.CStrSize());
}

TEST(XMLPrinterPutcTest_292, FileMode_WritesCharactersToProvidedFILE_292) {
    const auto apos = static_cast<tinyxml2::EscapeAposCharsInAttributes>(0);

    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    TestXMLPrinter_292 printer(fp, /*compact=*/false, /*depth=*/0, apos);
    printer.PutcPublic('x');
    printer.PutcPublic('y');

    const std::string fileData = ReadAllFromFile(fp);
    std::fclose(fp);

    EXPECT_EQ(fileData, "xy");
}

TEST(XMLPrinterPutcTest_292, FileMode_DoesNotCorruptExistingFileContents_292) {
    const auto apos = static_cast<tinyxml2::EscapeAposCharsInAttributes>(0);

    FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    // Seed file with some content first.
    std::fwrite("seed", 1, 4, fp);

    TestXMLPrinter_292 printer(fp, /*compact=*/false, /*depth=*/0, apos);
    printer.PutcPublic('1');
    printer.PutcPublic('2');

    const std::string fileData = ReadAllFromFile(fp);
    std::fclose(fp);

    // Observable behavior: Putc writes additional bytes; file should contain original + appended.
    EXPECT_EQ(fileData, "seed12");
}
