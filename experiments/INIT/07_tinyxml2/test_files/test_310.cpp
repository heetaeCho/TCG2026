// File: ./TestProjects/tinyxml2/tests/xmlprinter_pushtext_bool_test_310.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <cstdio>
#include <cstring>
#include <string>

#include "tinyxml2.h"

using ::testing::HasSubstr;

namespace tinyxml2 {

class XMLPrinterPushTextBoolTest_310 : public ::testing::Test {
protected:
    void SetUp() override {
        // Make bool serialization deterministic for these tests.
        XMLUtil::SetBoolSerialization("YES", "NO");
    }

    void TearDown() override {
        // Best-effort restore to common defaults to avoid impacting other tests.
        XMLUtil::SetBoolSerialization("true", "false");
    }

    static EscapeAposCharsInAttributes DefaultAposMode() {
        // Avoid depending on specific enum constants that may vary by version.
        return static_cast<EscapeAposCharsInAttributes>(0);
    }
};

TEST_F(XMLPrinterPushTextBoolTest_310, PushTextTrue_AppendsSerializedTrue_310) {
    XMLPrinter printer(nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode());

    printer.PushText(true);

    const char* outC = printer.CStr();
    ASSERT_NE(outC, nullptr);
    const std::string out(outC);

    EXPECT_THAT(out, HasSubstr("YES"));
    EXPECT_EQ(printer.CStrSize(), out.size());
}

TEST_F(XMLPrinterPushTextBoolTest_310, PushTextFalse_AppendsSerializedFalse_310) {
    XMLPrinter printer(nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode());

    printer.PushText(false);

    const char* outC = printer.CStr();
    ASSERT_NE(outC, nullptr);
    const std::string out(outC);

    EXPECT_THAT(out, HasSubstr("NO"));
    EXPECT_EQ(printer.CStrSize(), out.size());
}

TEST_F(XMLPrinterPushTextBoolTest_310, PushTextCalledMultipleTimes_PreservesOrder_310) {
    XMLPrinter printer(nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode());

    printer.PushText(true);
    printer.PushText(false);

    const std::string out = printer.CStr() ? std::string(printer.CStr()) : std::string();

    const auto posYes = out.find("YES");
    const auto posNo  = out.find("NO");

    ASSERT_NE(posYes, std::string::npos);
    ASSERT_NE(posNo, std::string::npos);
    EXPECT_LT(posYes, posNo);
}

TEST_F(XMLPrinterPushTextBoolTest_310, ClearBuffer_RemovesPreviouslyPrintedText_310) {
    XMLPrinter printer(nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode());

    printer.PushText(true);
    const std::string before = printer.CStr() ? std::string(printer.CStr()) : std::string();
    ASSERT_THAT(before, HasSubstr("YES"));

    printer.ClearBuffer();

    const char* afterC = printer.CStr();
    ASSERT_NE(afterC, nullptr);
    const std::string after(afterC);

    // Don't assume exact empty string; just ensure prior content is no longer present.
    EXPECT_EQ(after.find("YES"), std::string::npos);
    EXPECT_EQ(printer.CStrSize(), after.size());
}

TEST_F(XMLPrinterPushTextBoolTest_310, WhenConstructedWithFile_PushTextWritesToFile_310) {
    std::FILE* fp = std::tmpfile();
    ASSERT_NE(fp, nullptr);

    {
        XMLPrinter printer(fp, /*compact=*/false, /*depth=*/0, DefaultAposMode());
        printer.PushText(true);
        std::fflush(fp);
    }

    std::fseek(fp, 0, SEEK_SET);
    char buf[256];
    std::memset(buf, 0, sizeof(buf));
    const size_t n = std::fread(buf, 1, sizeof(buf) - 1, fp);
    std::fclose(fp);

    const std::string fileOut(buf, buf + n);
    EXPECT_THAT(fileOut, HasSubstr("YES"));
}

}  // namespace tinyxml2
