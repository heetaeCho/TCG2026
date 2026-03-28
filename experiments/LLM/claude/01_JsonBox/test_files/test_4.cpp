#include <gtest/gtest.h>
#include <sstream>
#include <streambuf>
#include <string>

// Include necessary headers
namespace JsonBox {
    namespace Whitespace {
        const char HORIZONTAL_TAB = '\t';
        const char NEW_LINE = '\n';
    }

    class Indenter {
    private:
        bool atStartOfLine;
    public:
        Indenter() : atStartOfLine(true) {}

        std::streambuf::int_type operator()(std::streambuf &destination, std::streambuf::int_type character) {
            std::streambuf::char_type tmpChar = std::streambuf::traits_type::to_char_type(character);
            if (atStartOfLine && tmpChar != Whitespace::NEW_LINE) {
                destination.sputc(Whitespace::HORIZONTAL_TAB);
            }
            atStartOfLine = (tmpChar == Whitespace::NEW_LINE);
            return destination.sputc(tmpChar);
        }
    };
}

class IndenterTest_4 : public ::testing::Test {
protected:
    JsonBox::Indenter indenter;
    std::stringbuf destBuf;

    void SetUp() override {
        destBuf.str("");
    }

    std::string getOutput() {
        return destBuf.str();
    }

    std::streambuf::int_type feedChar(char c) {
        return indenter(destBuf, std::streambuf::traits_type::to_int_type(c));
    }

    void feedString(const std::string &s) {
        for (char c : s) {
            feedChar(c);
        }
    }
};

// Test that the first character gets indented (atStartOfLine is initially true)
TEST_F(IndenterTest_4, FirstCharacterIsIndented_4) {
    feedChar('a');
    EXPECT_EQ(getOutput(), "\ta");
}

// Test that a newline at the very start does NOT get a tab prefix
TEST_F(IndenterTest_4, FirstCharacterNewLineNoIndent_4) {
    feedChar('\n');
    EXPECT_EQ(getOutput(), "\n");
}

// Test that after a newline, the next non-newline character is indented
TEST_F(IndenterTest_4, CharAfterNewLineIsIndented_4) {
    feedChar('a');  // "\ta"
    feedChar('\n'); // "\ta\n"
    feedChar('b');  // "\ta\n\tb"
    EXPECT_EQ(getOutput(), "\ta\n\tb");
}

// Test that consecutive newlines do not produce tabs
TEST_F(IndenterTest_4, ConsecutiveNewLinesNoTabs_4) {
    feedChar('\n');
    feedChar('\n');
    feedChar('\n');
    EXPECT_EQ(getOutput(), "\n\n\n");
}

// Test that characters on the same line (no newline) don't get extra tabs
TEST_F(IndenterTest_4, MultipleCharsOnSameLineOnlyFirstIndented_4) {
    feedChar('a');
    feedChar('b');
    feedChar('c');
    EXPECT_EQ(getOutput(), "\tabc");
}

// Test a full line scenario: chars, newline, chars
TEST_F(IndenterTest_4, FullLineScenario_4) {
    feedString("hello\nworld");
    EXPECT_EQ(getOutput(), "\thello\n\tworld");
}

// Test multiple lines
TEST_F(IndenterTest_4, MultipleLines_4) {
    feedString("line1\nline2\nline3\n");
    EXPECT_EQ(getOutput(), "\tline1\n\tline2\n\tline3\n");
}

// Test that the return value is the result of sputc (the character written)
TEST_F(IndenterTest_4, ReturnValueIsCharacterWritten_4) {
    auto result = feedChar('x');
    EXPECT_EQ(std::streambuf::traits_type::to_char_type(result), 'x');
}

// Test return value for newline character
TEST_F(IndenterTest_4, ReturnValueForNewLine_4) {
    auto result = feedChar('\n');
    EXPECT_EQ(std::streambuf::traits_type::to_char_type(result), '\n');
}

// Test that after newline followed by another newline, no tab is inserted
TEST_F(IndenterTest_4, NewLineAfterNewLineNoTab_4) {
    feedChar('a');   // "\ta"
    feedChar('\n');  // "\ta\n"
    feedChar('\n');  // "\ta\n\n"
    feedChar('b');   // "\ta\n\n\tb"
    EXPECT_EQ(getOutput(), "\ta\n\n\tb");
}

// Test with tab character itself (not a newline, should be treated as regular char)
TEST_F(IndenterTest_4, TabCharacterTreatedAsRegular_4) {
    feedChar('\t');
    EXPECT_EQ(getOutput(), "\t\t");  // first tab from indent, second is the actual char
}

// Test with space character
TEST_F(IndenterTest_4, SpaceCharacterIndented_4) {
    feedChar(' ');
    EXPECT_EQ(getOutput(), "\t ");
}

// Test empty scenario - no characters fed
TEST_F(IndenterTest_4, NoCharactersFed_4) {
    EXPECT_EQ(getOutput(), "");
}

// Test single newline followed by non-newline
TEST_F(IndenterTest_4, SingleNewLineThenChar_4) {
    feedChar('\n');
    feedChar('x');
    EXPECT_EQ(getOutput(), "\n\tx");
}

// Test that return value is not EOF for valid characters
TEST_F(IndenterTest_4, ReturnValueNotEOF_4) {
    auto result = feedChar('a');
    EXPECT_NE(result, std::streambuf::traits_type::eof());
}

// Test a complex mixed scenario
TEST_F(IndenterTest_4, ComplexMixedScenario_4) {
    feedString("{\n\"key\": \"value\"\n}");
    EXPECT_EQ(getOutput(), "\t{\n\t\"key\": \"value\"\n\t}");
}

// Test with special characters (non-whitespace)
TEST_F(IndenterTest_4, SpecialCharacters_4) {
    feedString("!@#\n$%^");
    EXPECT_EQ(getOutput(), "\t!@#\n\t$%^");
}

// Test that newline at end leaves indenter ready for next line
TEST_F(IndenterTest_4, NewLineAtEndReadyForNextLine_4) {
    feedString("abc\n");
    feedChar('d');
    EXPECT_EQ(getOutput(), "\tabc\n\td");
}
