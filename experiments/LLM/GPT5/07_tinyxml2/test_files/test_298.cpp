// TEST_ID: 298
// File: xmlprinter_pushattribute_unsigned_test_298.cpp

#include <gtest/gtest.h>

#include <limits>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

namespace {

class XMLPrinterPushAttributeUnsignedTest_298 : public ::testing::Test {
protected:
    // Avoid depending on any particular enum value; we just need a valid value.
    static EscapeAposCharsInAttributes DefaultAposMode() {
        return static_cast<EscapeAposCharsInAttributes>(0);
    }

    static std::string ToString(unsigned v) {
        return std::to_string(static_cast<unsigned long long>(v));
    }
};

}  // namespace

TEST_F(XMLPrinterPushAttributeUnsignedTest_298, WritesUnsignedAttributeValue_298) {
    XMLPrinter printer(/*file=*/nullptr, /*compact=*/false, /*depth=*/0, DefaultAposMode());

    printer.OpenElement("root", /*compactMode=*/false);
    printer.PushAttribute("u", 42u);
    printer.CloseElement(/*compactMode=*/false);

    const std::string out = printer.CStr() ? std::string(printer.CStr()) : std::string();
    EXPECT_NE(out.find("u=\"42\""), std::string::npos) << out;
}

TEST_F(XMLPrinterPushAttributeUnsignedTest_298, WritesZeroUnsignedValue_298) {
    XMLPrinter printer(nullptr, false, 0, DefaultAposMode());

    printer.OpenElement("root", false);
    printer.PushAttribute("zero", 0u);
    printer.CloseElement(false);

    const std::string out = printer.CStr() ? std::string(printer.CStr()) : std::string();
    EXPECT_NE(out.find("zero=\"0\""), std::string::npos) << out;
}

TEST_F(XMLPrinterPushAttributeUnsignedTest_298, WritesMaxUnsignedValue_298) {
    XMLPrinter printer(nullptr, false, 0, DefaultAposMode());

    const unsigned maxU = (std::numeric_limits<unsigned>::max)();
    printer.OpenElement("root", false);
    printer.PushAttribute("max", maxU);
    printer.CloseElement(false);

    const std::string out = printer.CStr() ? std::string(printer.CStr()) : std::string();
    const std::string expected = "max=\"" + ToString(maxU) + "\"";
    EXPECT_NE(out.find(expected), std::string::npos) << out;
}

TEST_F(XMLPrinterPushAttributeUnsignedTest_298, MultipleUnsignedAttributesAppear_298) {
    XMLPrinter printer(nullptr, false, 0, DefaultAposMode());

    printer.OpenElement("root", false);
    printer.PushAttribute("a", 1u);
    printer.PushAttribute("b", 2u);
    printer.CloseElement(false);

    const std::string out = printer.CStr() ? std::string(printer.CStr()) : std::string();
    EXPECT_NE(out.find("a=\"1\""), std::string::npos) << out;
    EXPECT_NE(out.find("b=\"2\""), std::string::npos) << out;
}

TEST_F(XMLPrinterPushAttributeUnsignedTest_298, ClearBufferMakesOutputEmpty_298) {
    XMLPrinter printer(nullptr, false, 0, DefaultAposMode());

    printer.OpenElement("root", false);
    printer.PushAttribute("u", 7u);
    printer.CloseElement(false);

    // ClearBuffer is part of the public interface; verify its observable effect on output.
    printer.ClearBuffer(/*resetToFirstElement=*/true);

    const char* cstr = printer.CStr();
    const std::string out = cstr ? std::string(cstr) : std::string();
    EXPECT_TRUE(out.empty()) << out;
    EXPECT_EQ(printer.CStrSize(), static_cast<size_t>(0));
}

TEST_F(XMLPrinterPushAttributeUnsignedTest_298, ProducesNonEmptyOutputAfterAttribute_298) {
    XMLPrinter printer(nullptr, false, 0, DefaultAposMode());

    printer.OpenElement("root", false);
    printer.PushAttribute("u", 123u);
    printer.CloseElement(false);

    const char* cstr = printer.CStr();
    ASSERT_NE(cstr, nullptr);
    EXPECT_GT(printer.CStrSize(), static_cast<size_t>(0));
    EXPECT_FALSE(std::string(cstr).empty());
}
