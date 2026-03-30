// TEST_ID: 197
#include <gtest/gtest.h>

#include <cstring>
#include <string>
#include <vector>

// tinyxml2 keeps ParseDeep private in the public header in many distributions.
// The prompt's interface shows it as callable; this macro makes it accessible
// for unit testing without touching internal state.
#define private public
#define protected public
#include "tinyxml2.h"
#undef protected
#undef private

using namespace tinyxml2;

namespace {

static std::vector<char> MakeBuffer(const std::string& s) {
    std::vector<char> buf(s.begin(), s.end());
    buf.push_back('\0');
    return buf;
}

}  // namespace

class XMLCommentParseDeepTest_197 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLCommentParseDeepTest_197, SuccessfulParseReturnsPointerAndNoError_197) {
    XMLComment* c = doc_.NewComment("");
    ASSERT_NE(c, nullptr);

    // Simulate the buffer position right after "<!--"
    auto buf = MakeBuffer(" hello world -->TAIL");
    char* p = buf.data();

    // Expected: points right after the first occurrence of "-->"
    const char* terminator = std::strstr(p, "-->");
    ASSERT_NE(terminator, nullptr);
    char* expected = const_cast<char*>(terminator + 3);

    int line = 1;
    char* ret = c->ParseDeep(p, /*parentEndTag=*/nullptr, &line);

    EXPECT_NE(ret, nullptr);
    EXPECT_EQ(ret, expected);
    EXPECT_FALSE(doc_.Error());
}

TEST_F(XMLCommentParseDeepTest_197, EmptyCommentParses_197) {
    XMLComment* c = doc_.NewComment("");
    ASSERT_NE(c, nullptr);

    auto buf = MakeBuffer("-->AFTER");
    char* p = buf.data();

    const char* terminator = std::strstr(p, "-->");
    ASSERT_NE(terminator, nullptr);
    char* expected = const_cast<char*>(terminator + 3);

    int line = 42;
    char* ret = c->ParseDeep(p, /*parentEndTag=*/nullptr, &line);

    EXPECT_NE(ret, nullptr);
    EXPECT_EQ(ret, expected);
    EXPECT_FALSE(doc_.Error());
    // Line number should not go backwards.
    EXPECT_GE(line, 42);
}

TEST_F(XMLCommentParseDeepTest_197, UnterminatedCommentReturnsNullAndSetsError_197) {
    XMLComment* c = doc_.NewComment("");
    ASSERT_NE(c, nullptr);

    auto buf = MakeBuffer(" unterminated comment ");
    char* p = buf.data();

    int line = 1;
    char* ret = c->ParseDeep(p, /*parentEndTag=*/nullptr, &line);

    EXPECT_EQ(ret, nullptr);
    EXPECT_TRUE(doc_.Error());
    EXPECT_EQ(doc_.ErrorID(), XML_ERROR_PARSING_COMMENT);
}

TEST_F(XMLCommentParseDeepTest_197, LineNumberAdvancesWhenCommentContainsNewline_197) {
    XMLComment* c = doc_.NewComment("");
    ASSERT_NE(c, nullptr);

    auto buf = MakeBuffer(" line1\nline2 -->END");
    char* p = buf.data();

    int line = 10;
    char* ret = c->ParseDeep(p, /*parentEndTag=*/nullptr, &line);

    EXPECT_NE(ret, nullptr);
    EXPECT_FALSE(doc_.Error());
    // At least one newline in the comment text should not decrease line count.
    EXPECT_GE(line, 10);
    // And very typically it will increment by 1+; keep the assertion weak/observable.
    EXPECT_GE(line, 11);
}

TEST_F(XMLCommentParseDeepTest_197, SuccessDoesNotLeaveDocumentInErrorAfterClearError_197) {
    XMLComment* c = doc_.NewComment("");
    ASSERT_NE(c, nullptr);

    // First, force an error.
    {
        auto bad = MakeBuffer(" no terminator here ");
        int line = 1;
        EXPECT_EQ(c->ParseDeep(bad.data(), nullptr, &line), nullptr);
        EXPECT_TRUE(doc_.Error());
        EXPECT_EQ(doc_.ErrorID(), XML_ERROR_PARSING_COMMENT);
    }

    doc_.ClearError();
    EXPECT_FALSE(doc_.Error());

    // Then parse a valid comment; document should remain non-error.
    {
        auto good = MakeBuffer(" ok -->X");
        const char* terminator = std::strstr(good.data(), "-->");
        ASSERT_NE(terminator, nullptr);
        char* expected = const_cast<char*>(terminator + 3);

        int line = 1;
        char* ret = c->ParseDeep(good.data(), nullptr, &line);

        EXPECT_NE(ret, nullptr);
        EXPECT_EQ(ret, expected);
        EXPECT_FALSE(doc_.Error());
    }
}
