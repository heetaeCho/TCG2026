// File: ./TestProjects/tinyxml2/XMLPrinterPushCommentTest_313.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <cctype>
#include <cstring>
#include <string>

#include "tinyxml2.h"

namespace {

std::string TrimCopy(const char* s) {
    if (!s) return {};
    std::string out(s);

    auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };

    auto itBegin = std::find_if(out.begin(), out.end(), notSpace);
    auto itEnd = std::find_if(out.rbegin(), out.rend(), notSpace).base();

    if (itBegin >= itEnd) return {};
    return std::string(itBegin, itEnd);
}

std::string RemoveAllWhitespaceCopy(const char* s) {
    if (!s) return {};
    std::string out;
    for (const char* p = s; *p; ++p) {
        unsigned char ch = static_cast<unsigned char>(*p);
        if (!std::isspace(ch)) out.push_back(static_cast<char>(ch));
    }
    return out;
}

}  // namespace

namespace tinyxml2 {

class XMLPrinterPushCommentTest_313 : public ::testing::Test {
protected:
    // Use internal buffer (FILE* == nullptr). Prefer compact mode to reduce incidental whitespace.
    XMLPrinterPushCommentTest_313() : printer_(nullptr, /*compact=*/true, /*depth=*/0, EscapeAposCharsInAttributes::NEVER) {}

    void SetUp() override {
        printer_.ClearBuffer(true);
    }

    XMLPrinter printer_;
};

TEST_F(XMLPrinterPushCommentTest_313, PushComment_WritesExpectedMarkup_313) {
    printer_.PushComment("hello");

    const std::string s = TrimCopy(printer_.CStr());
    EXPECT_EQ(s, "<!--hello-->");
    EXPECT_EQ(printer_.CStrSize(), s.size() + 1);  // includes null terminator
}

TEST_F(XMLPrinterPushCommentTest_313, PushComment_EmptyString_WritesEmptyComment_313) {
    printer_.PushComment("");

    const std::string s = TrimCopy(printer_.CStr());
    EXPECT_EQ(s, "<!---->");
}

TEST_F(XMLPrinterPushCommentTest_313, PushComment_MultipleCalls_AppendsInOrder_313) {
    printer_.PushComment("a");
    printer_.PushComment("b");

    // Be tolerant of any whitespace/newlines between nodes by stripping all whitespace.
    const std::string s = RemoveAllWhitespaceCopy(printer_.CStr());
    EXPECT_EQ(s, "<!--a--><!--b-->");
}

TEST_F(XMLPrinterPushCommentTest_313, PushComment_AfterOpenElement_CommentAppearsAfterElementStart_313) {
    printer_.OpenElement("root", /*compactMode=*/true);
    printer_.PushComment("c");
    printer_.CloseElement(/*compactMode=*/true);

    const std::string s = printer_.CStr() ? std::string(printer_.CStr()) : std::string();
    const size_t posRoot = s.find("<root");
    const size_t posComment = s.find("<!--c-->");

    ASSERT_NE(posRoot, std::string::npos);
    ASSERT_NE(posComment, std::string::npos);
    EXPECT_GT(posComment, posRoot);
}

}  // namespace tinyxml2
