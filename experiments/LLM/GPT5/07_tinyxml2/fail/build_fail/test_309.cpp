// TEST_ID: 309
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "tinyxml2.h"

namespace {

class XMLPrinterPushTextUnsignedTest_309 : public ::testing::Test {
protected:
    static tinyxml2::XMLPrinter MakePrinterCompact_309() {
        // Use an explicit enum cast to avoid depending on specific enumerator names.
        return tinyxml2::XMLPrinter(
            /*file=*/nullptr,
            /*compact=*/true,
            /*depth=*/0,
            static_cast<tinyxml2::EscapeAposCharsInAttributes>(0));
    }

    static std::string WrapWithElement_309(unsigned value) {
        tinyxml2::XMLPrinter printer = MakePrinterCompact_309();
        printer.OpenElement("a", /*compactMode=*/true);
        printer.PushText(value);
        printer.CloseElement(/*compactMode=*/true);
        const char* out = printer.CStr();
        return out ? std::string(out) : std::string();
    }
};

TEST_F(XMLPrinterPushTextUnsignedTest_309, PushTextZero_WritesDecimalDigits_309) {
    EXPECT_EQ(WrapWithElement_309(0u), "<a>0</a>");
}

TEST_F(XMLPrinterPushTextUnsignedTest_309, PushTextTypicalValue_WritesDecimalDigits_309) {
    EXPECT_EQ(WrapWithElement_309(42u), "<a>42</a>");
}

TEST_F(XMLPrinterPushTextUnsignedTest_309, PushTextMaxUnsigned_WritesDecimalDigits_309) {
    const unsigned maxu = (std::numeric_limits<unsigned>::max)();

    tinyxml2::XMLPrinter printer = MakePrinterCompact_309();
    printer.OpenElement("a", /*compactMode=*/true);
    EXPECT_NO_THROW(printer.PushText(maxu));
    printer.CloseElement(/*compactMode=*/true);

    // Compare against the standard decimal string representation.
    const std::string expected = std::string("<a>") + std::to_string(maxu) + "</a>";
    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);
    EXPECT_EQ(std::string(out), expected);
}

TEST_F(XMLPrinterPushTextUnsignedTest_309, PushTextDoesNotEmitCDataMarkers_309) {
    tinyxml2::XMLPrinter printer = MakePrinterCompact_309();
    printer.OpenElement("a", /*compactMode=*/true);
    printer.PushText(123u);
    printer.CloseElement(/*compactMode=*/true);

    const std::string out = printer.CStr() ? std::string(printer.CStr()) : std::string();
    // This overload routes through PushText(buf, false); digits should not require CDATA.
    EXPECT_EQ(out.find("<![CDATA["), std::string::npos);
    EXPECT_EQ(out.find("]]>"), std::string::npos);
    EXPECT_EQ(out, "<a>123</a>");
}

TEST_F(XMLPrinterPushTextUnsignedTest_309, MultiplePushTextCalls_AppendInOrder_309) {
    tinyxml2::XMLPrinter printer = MakePrinterCompact_309();
    printer.OpenElement("a", /*compactMode=*/true);
    printer.PushText(1u);
    printer.PushText(2u);
    printer.PushText(3u);
    printer.CloseElement(/*compactMode=*/true);

    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);
    EXPECT_EQ(std::string(out), "<a>123</a>");
}

TEST_F(XMLPrinterPushTextUnsignedTest_309, CStrSizeMatchesCStrLengthAfterPushText_309) {
    tinyxml2::XMLPrinter printer = MakePrinterCompact_309();
    printer.OpenElement("a", /*compactMode=*/true);
    printer.PushText(1000u);
    printer.CloseElement(/*compactMode=*/true);

    const char* out = printer.CStr();
    ASSERT_NE(out, nullptr);

    // Observable consistency check between two public APIs.
    EXPECT_EQ(printer.CStrSize(), std::strlen(out) + 1u);  // includes null terminator
}

}  // namespace
