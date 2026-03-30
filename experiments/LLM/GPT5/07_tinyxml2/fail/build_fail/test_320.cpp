// TEST_ID: 320
#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <string>
#include <type_traits>

#include "tinyxml2.h"

namespace {

using namespace tinyxml2;

class XMLPrinterVisitCommentTest_320 : public ::testing::Test {
protected:
    static XMLPrinter MakePrinter() {
        // tinyxml2 versions differ: some have (FILE*, bool, int), newer ones add a 4th parameter.
        if constexpr (std::is_constructible_v<XMLPrinter, FILE*, bool, int>) {
            return XMLPrinter(nullptr, /*compact=*/false, /*depth=*/0);
        } else if constexpr (std::is_constructible_v<XMLPrinter, FILE*, bool, int, EscapeAposCharsInAttributes>) {
            // Use a safe default value without assuming enum names.
            return XMLPrinter(nullptr, /*compact=*/false, /*depth=*/0,
                              static_cast<EscapeAposCharsInAttributes>(0));
        } else {
            // If neither matches, fail at compile time with a clear message.
            static_assert(std::is_constructible_v<XMLPrinter, FILE*, bool, int> ||
                              std::is_constructible_v<XMLPrinter, FILE*, bool, int, EscapeAposCharsInAttributes>,
                          "Unsupported XMLPrinter constructor signature for this tinyxml2 version.");
            return XMLPrinter(nullptr, false, 0); // Unreachable, silences warnings.
        }
    }

    static XMLComment* NewComment(XMLDocument& doc, const char* text) {
        XMLComment* c = doc.NewComment(text);
        // In tinyxml2, NewComment should return non-null for valid inputs.
        EXPECT_NE(c, nullptr);
        return c;
    }

    static std::string PrinterString(const XMLPrinter& p) {
        const char* s = p.CStr();
        return s ? std::string(s) : std::string();
    }
};

TEST_F(XMLPrinterVisitCommentTest_320, VisitReturnsTrueAndEmitsCommentText_320) {
    XMLDocument doc;
    XMLComment* comment = NewComment(doc, "hello");

    XMLPrinter printer = MakePrinter();
    const bool result = printer.Visit(*comment);

    EXPECT_TRUE(result);
    EXPECT_GT(printer.CStrSize(), 0u);

    const std::string out = PrinterString(printer);
    EXPECT_NE(out.find("hello"), std::string::npos);
}

TEST_F(XMLPrinterVisitCommentTest_320, VisitHandlesEmptyCommentWithoutFailure_320) {
    XMLDocument doc;
    XMLComment* comment = NewComment(doc, "");

    XMLPrinter printer = MakePrinter();
    const bool result = printer.Visit(*comment);

    EXPECT_TRUE(result);
    // Even an empty comment should produce some output or at least not crash.
    EXPECT_GE(printer.CStrSize(), 0u);
}

TEST_F(XMLPrinterVisitCommentTest_320, VisitAppendsMultipleCommentsInCallOrder_320) {
    XMLDocument doc;
    XMLComment* c1 = NewComment(doc, "one");
    XMLComment* c2 = NewComment(doc, "two");

    XMLPrinter printer = MakePrinter();
    EXPECT_TRUE(printer.Visit(*c1));
    EXPECT_TRUE(printer.Visit(*c2));

    const std::string out = PrinterString(printer);
    const auto p1 = out.find("one");
    const auto p2 = out.find("two");

    EXPECT_NE(p1, std::string::npos);
    EXPECT_NE(p2, std::string::npos);
    EXPECT_LT(p1, p2);
}

TEST_F(XMLPrinterVisitCommentTest_320, VisitDoesNotEraseExistingPrinterBuffer_320) {
    XMLDocument doc;
    XMLComment* comment = NewComment(doc, "cmt");

    XMLPrinter printer = MakePrinter();
    printer.PushText("prefix", /*cdata=*/false);

    const std::string before = PrinterString(printer);
    ASSERT_NE(before.find("prefix"), std::string::npos);

    EXPECT_TRUE(printer.Visit(*comment));

    const std::string after = PrinterString(printer);
    EXPECT_NE(after.find("prefix"), std::string::npos);
    EXPECT_NE(after.find("cmt"), std::string::npos);

    // Prefix should appear before the comment text if the comment was appended.
    EXPECT_LT(after.find("prefix"), after.find("cmt"));
}

TEST_F(XMLPrinterVisitCommentTest_320, VisitWithDashDashInCommentStillReturnsTrueAndContainsParts_320) {
    // XML comments typically disallow "--" inside, but Visit should still be robust/observable.
    XMLDocument doc;
    XMLComment* comment = NewComment(doc, "a--b");

    XMLPrinter printer = MakePrinter();
    const bool result = printer.Visit(*comment);

    EXPECT_TRUE(result);

    const std::string out = PrinterString(printer);
    // Avoid asserting exact escaping/rewriting rules; just verify the content is reflected.
    EXPECT_NE(out.find("a"), std::string::npos);
    EXPECT_NE(out.find("b"), std::string::npos);
}

}  // namespace
