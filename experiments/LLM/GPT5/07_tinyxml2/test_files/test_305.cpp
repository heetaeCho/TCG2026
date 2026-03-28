// TEST_ID: 305
#include <gtest/gtest.h>
#include <cstring>
#include <string>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLPrinterPushTextTest_305 : public ::testing::Test {
protected:
    static XMLPrinter MakePrinter()
    {
        // Use in-memory buffer (file == nullptr). Avoid depending on specific enum values.
        return XMLPrinter(nullptr, /*compact=*/true, /*depth=*/0,
                          static_cast<EscapeAposCharsInAttributes>(0));
    }

    static std::string Str(const XMLPrinter& p)
    {
        const char* s = p.CStr();
        return s ? std::string(s) : std::string();
    }
};

TEST_F(XMLPrinterPushTextTest_305, NonCDataEscapesMarkupCharacters_305)
{
    XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/true);
    printer.PushText("a<b&c>d", /*cdata=*/false);
    printer.CloseElement(/*compactMode=*/true);

    const std::string out = Str(printer);

    // Basic structure should exist.
    EXPECT_NE(out.find("<root"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);

    // Should not contain raw markup characters from the text payload.
    EXPECT_EQ(out.find("a<b"), std::string::npos);
    EXPECT_EQ(out.find("&c>"), std::string::npos);

    // Escaped entities should appear.
    EXPECT_NE(out.find("a&lt;b"), std::string::npos);
    EXPECT_NE(out.find("&amp;"), std::string::npos);
    EXPECT_NE(out.find("&gt;d"), std::string::npos);
}

TEST_F(XMLPrinterPushTextTest_305, CDataWrapsTextAndPreservesRawCharacters_305)
{
    XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/true);
    printer.PushText("a<b&c>d", /*cdata=*/true);
    printer.CloseElement(/*compactMode=*/true);

    const std::string out = Str(printer);

    EXPECT_NE(out.find("<root"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);

    // CDATA wrapper must exist.
    EXPECT_NE(out.find("<![CDATA["), std::string::npos);
    EXPECT_NE(out.find("]]>"), std::string::npos);

    // Inside CDATA, raw characters should remain (no entity escaping required/expected).
    EXPECT_NE(out.find("a<b&c>d"), std::string::npos);
}

TEST_F(XMLPrinterPushTextTest_305, PushTextSealsJustOpenedElementBeforeWritingText_305)
{
    XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/true);
    printer.PushText("text", /*cdata=*/false);
    printer.CloseElement(/*compactMode=*/true);

    const std::string out = Str(printer);

    // Ensure the opening tag is sealed before the text appears: "<root>text"
    const auto posOpen = out.find("<root");
    ASSERT_NE(posOpen, std::string::npos);

    const auto posGt = out.find('>', posOpen);
    ASSERT_NE(posGt, std::string::npos);

    const auto posText = out.find("text");
    ASSERT_NE(posText, std::string::npos);

    EXPECT_LT(posGt, posText);
}

TEST_F(XMLPrinterPushTextTest_305, EmptyStringProducesNoVisibleTextButKeepsElementStructure_305)
{
    XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/true);
    printer.PushText("", /*cdata=*/false);
    printer.CloseElement(/*compactMode=*/true);

    const std::string out = Str(printer);

    EXPECT_NE(out.find("<root"), std::string::npos);
    EXPECT_NE(out.find("</root>"), std::string::npos);

    // Should not add CDATA markers for non-cdata empty string.
    EXPECT_EQ(out.find("<![CDATA["), std::string::npos);
}

TEST_F(XMLPrinterPushTextTest_305, MultiplePushTextCallsAppendInOrder_305)
{
    XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/true);
    printer.PushText("A", /*cdata=*/false);
    printer.PushText("B", /*cdata=*/false);
    printer.CloseElement(/*compactMode=*/true);

    const std::string out = Str(printer);

    const auto posA = out.find("A");
    const auto posB = out.find("B");
    ASSERT_NE(posA, std::string::npos);
    ASSERT_NE(posB, std::string::npos);

    EXPECT_LT(posA, posB);
    EXPECT_NE(out.find("AB"), std::string::npos);
}

TEST_F(XMLPrinterPushTextTest_305, MixedCDataAndNonCDataBothAppear_305)
{
    XMLPrinter printer = MakePrinter();

    printer.OpenElement("root", /*compactMode=*/true);
    printer.PushText("x<y", /*cdata=*/false);   // should escape
    printer.PushText("raw<z", /*cdata=*/true);  // should be inside CDATA
    printer.CloseElement(/*compactMode=*/true);

    const std::string out = Str(printer);

    // Non-CDATA part should be escaped.
    EXPECT_NE(out.find("x&lt;y"), std::string::npos);

    // CDATA part should be present and raw.
    EXPECT_NE(out.find("<![CDATA["), std::string::npos);
    EXPECT_NE(out.find("raw<z"), std::string::npos);
    EXPECT_NE(out.find("]]>"), std::string::npos);
}
