// TEST_ID: 323
#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <string>

#include "tinyxml2.h"

// The contrib implementation lives in: ./TestProjects/tinyxml2/contrib/html5-printer.cpp
// It may not have a public header in this project layout, so we declare the interface
// exactly as provided and link against the existing implementation.
namespace tinyxml2 {
class XMLPrinterHTML5 : public XMLPrinter {
public:
    XMLPrinterHTML5(FILE* file = 0, bool compact = false, int depth = 0);

protected:
    virtual void CloseElement();
    virtual bool isVoidElement(const char* name);
};
}  // namespace tinyxml2

namespace {

class ExposedXMLPrinterHTML5_323 : public tinyxml2::XMLPrinterHTML5 {
public:
    using tinyxml2::XMLPrinterHTML5::XMLPrinterHTML5;

    // Expose protected API for testing.
    using tinyxml2::XMLPrinter::CStr;
    using tinyxml2::XMLPrinter::CStrSize;
    using tinyxml2::XMLPrinter::OpenElement;
    using tinyxml2::XMLPrinter::PushAttribute;
    using tinyxml2::XMLPrinter::PushText;
    using tinyxml2::XMLPrinterHTML5::CloseElement;
};

static std::string StripAllWhitespace_323(const char* s) {
    if (!s) return {};
    std::string out;
    for (const unsigned char ch : std::string(s)) {
        if (!std::isspace(ch)) out.push_back(static_cast<char>(ch));
    }
    return out;
}

}  // namespace

TEST(XMLPrinterHTML5Test_323, CloseElementNonVoidJustOpened_323) {
    // Compact mode to avoid indentation/newlines influencing exact output.
    ExposedXMLPrinterHTML5_323 printer(/*file=*/nullptr, /*compact=*/true, /*depth=*/0);

    printer.OpenElement("div", /*compactMode=*/true);
    printer.CloseElement();

    // Observable behavior: output string.
    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_EQ(std::string(printer.CStr()), "<div></div>");
}

TEST(XMLPrinterHTML5Test_323, CloseElementVoidElementProducesSelfClosing_323) {
    ExposedXMLPrinterHTML5_323 printer(/*file=*/nullptr, /*compact=*/true, /*depth=*/0);

    printer.OpenElement("br", /*compactMode=*/true);
    printer.CloseElement();

    ASSERT_NE(printer.CStr(), nullptr);

    // Be tolerant of formatting differences like "<br/>" vs "<br />".
    const std::string normalized = StripAllWhitespace_323(printer.CStr());
    EXPECT_EQ(normalized, "<br/>");
}

TEST(XMLPrinterHTML5Test_323, CloseElementAfterAttributeAndText_323) {
    ExposedXMLPrinterHTML5_323 printer(/*file=*/nullptr, /*compact=*/true, /*depth=*/0);

    printer.OpenElement("p", /*compactMode=*/true);
    printer.PushAttribute("class", "x");
    printer.PushText("hi", /*cdata=*/false);
    printer.CloseElement();

    ASSERT_NE(printer.CStr(), nullptr);

    // Attribute ordering is defined by the sequence of PushAttribute calls.
    // Text should appear before the closing tag.
    EXPECT_EQ(std::string(printer.CStr()), "<p class=\"x\">hi</p>");
}

TEST(XMLPrinterHTML5Test_323, NestedWithVoidChildClosesCorrectly_323) {
    ExposedXMLPrinterHTML5_323 printer(/*file=*/nullptr, /*compact=*/true, /*depth=*/0);

    printer.OpenElement("div", /*compactMode=*/true);
    printer.OpenElement("br", /*compactMode=*/true);
    printer.CloseElement();  // close br
    printer.CloseElement();  // close div

    ASSERT_NE(printer.CStr(), nullptr);

    const std::string normalized = StripAllWhitespace_323(printer.CStr());
    EXPECT_EQ(normalized, "<div><br/></div>");
}

TEST(XMLPrinterHTML5Test_323, CloseElementIdempotenceOnAlreadyClosedState_323) {
    // This test avoids calling CloseElement with an empty stack (which could be undefined).
    // Instead it checks that calling CloseElement exactly once per opened element yields
    // stable output and does not mutate output unexpectedly afterward through public APIs.
    ExposedXMLPrinterHTML5_323 printer(/*file=*/nullptr, /*compact=*/true, /*depth=*/0);

    printer.OpenElement("span", /*compactMode=*/true);
    printer.CloseElement();

    const std::string first = printer.CStr() ? std::string(printer.CStr()) : std::string();
    EXPECT_EQ(first, "<span></span>");

    // Add a second independent element sequence; previous output should remain as prefix.
    printer.OpenElement("em", /*compactMode=*/true);
    printer.PushText("t", /*cdata=*/false);
    printer.CloseElement();

    ASSERT_NE(printer.CStr(), nullptr);
    EXPECT_EQ(std::string(printer.CStr()), "<span></span><em>t</em>");
}
