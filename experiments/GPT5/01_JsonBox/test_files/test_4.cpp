// IndenterTests_4.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>

namespace JsonBox {
namespace Whitespace {
    // Known dependency values from Grammar.h
    static const char HORIZONTAL_TAB = '\t';
    static const char NEW_LINE = '\n';
}

// Minimal declaration to use the public interface as a black box.
class Indenter {
public:
    Indenter() : atStartOfLine(true) {}

    std::streambuf::int_type operator()(std::streambuf& destination,
                                        std::streambuf::int_type character) {
        using traits = std::streambuf::traits_type;
        std::streambuf::char_type tmpChar = traits::to_char_type(character);
        if (atStartOfLine && tmpChar != Whitespace::NEW_LINE) {
            destination.sputc(Whitespace::HORIZONTAL_TAB);
        }
        atStartOfLine = (tmpChar == Whitespace::NEW_LINE);
        return destination.sputc(tmpChar);
    }

private:
    bool atStartOfLine;
};
} // namespace JsonBox

class IndenterTest_4 : public ::testing::Test {
protected:
    using traits = std::char_traits<char>;

    // Helper to feed a whole string, one char at a time, through the indenter.
    static std::string Run(JsonBox::Indenter& ind, const std::string& input) {
        std::stringbuf buf;
        for (unsigned char c : input) {
            ind(*buf.rdbuf(), traits::to_int_type(static_cast<char>(c)));
        }
        return buf.str();
    }
};

// Normal operation: first non-newline at the very start gets a leading tab.
TEST_F(IndenterTest_4, FirstNonNewlineGetsTab_4) {
    JsonBox::Indenter ind;
    std::string out = IndenterTest_4::Run(ind, "a");
    EXPECT_EQ(std::string(1, JsonBox::Whitespace::HORIZONTAL_TAB) + "a", out);
}

// Boundary: first character is a newline — no tab should be inserted.
TEST_F(IndenterTest_4, FirstNewlineNoTab_4) {
    JsonBox::Indenter ind;
    std::string out = IndenterTest_4::Run(ind, std::string(1, JsonBox::Whitespace::NEW_LINE));
    EXPECT_EQ(std::string(1, JsonBox::Whitespace::NEW_LINE), out);
}

// Normal: continuous non-newline characters should only be indented once at the line start.
TEST_F(IndenterTest_4, ContinuousCharsNoExtraTabs_4) {
    JsonBox::Indenter ind;
    std::string out = IndenterTest_4::Run(ind, "ab");
    EXPECT_EQ(std::string(1, JsonBox::Whitespace::HORIZONTAL_TAB) + "ab", out);
}

// Normal across lines: after a newline, the next non-newline gets a tab.
TEST_F(IndenterTest_4, AfterNewlineNextCharTabbed_4) {
    JsonBox::Indenter ind;
    std::string out = IndenterTest_4::Run(ind, std::string(1, JsonBox::Whitespace::NEW_LINE) + "X");
    EXPECT_EQ(std::string(1, JsonBox::Whitespace::NEW_LINE) +
                  std::string(1, JsonBox::Whitespace::HORIZONTAL_TAB) + "X",
              out);
}

// Multiple lines including blank line: verify indentation resets only for non-newline starts.
TEST_F(IndenterTest_4, MultipleLinesWithBlankLine_4) {
    JsonBox::Indenter ind;
    std::string input = std::string("a") +
                        JsonBox::Whitespace::NEW_LINE +
                        "b" +
                        JsonBox::Whitespace::NEW_LINE +
                        JsonBox::Whitespace::NEW_LINE + // blank line
                        "c";
    std::string out = IndenterTest_4::Run(ind, input);

    std::string expected;
    expected += JsonBox::Whitespace::HORIZONTAL_TAB; // before 'a'
    expected += 'a';
    expected += JsonBox::Whitespace::NEW_LINE;       // newline after 'a'
    expected += JsonBox::Whitespace::HORIZONTAL_TAB; // before 'b'
    expected += 'b';
    expected += JsonBox::Whitespace::NEW_LINE;       // newline after 'b'
    expected += JsonBox::Whitespace::NEW_LINE;       // blank line (no tab)
    expected += JsonBox::Whitespace::HORIZONTAL_TAB; // before 'c'
    expected += 'c';

    EXPECT_EQ(expected, out);
}

// Exceptional (observable via collaborator): destination sputc failure on the first write.
// We simulate a streambuf that fails the first sputc. Only the primary character should remain.
class FailingFirstSputcBuf : public std::stringbuf {
public:
    using traits_type = std::stringbuf::traits_type;
    using char_type   = std::stringbuf::char_type;
    using int_type    = std::stringbuf::int_type;

    FailingFirstSputcBuf() : fail_next_(true) {}

    int_type sputc(char_type c) override {
        if (fail_next_) {
            fail_next_ = false;
            return traits_type::eof(); // simulate failure
        }
        return std::stringbuf::sputc(c);
    }
private:
    bool fail_next_;
};

TEST_F(IndenterTest_4, DestinationSputcFailure_FirstWrite_4) {
    JsonBox::Indenter ind;
    FailingFirstSputcBuf buf;

    // At start-of-line with non-newline input: indenter attempts to write a tab first (fails),
    // then writes the actual character.
    auto ret = ind(*buf.rdbuf(), traits::to_int_type('Z'));

    // The output should contain only 'Z' because the tab write failed.
    EXPECT_EQ("Z", buf.str());

    // The return value should be the int_type of the last successfully written character.
    EXPECT_EQ(traits::to_int_type('Z'), ret);
}
