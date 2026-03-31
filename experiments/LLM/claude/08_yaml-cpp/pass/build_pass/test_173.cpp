#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

class StreamTest_173 : public ::testing::Test {
protected:
};

// Test peek on empty stream returns eof
TEST_F(StreamTest_173, PeekEmptyStreamReturnsEof_173) {
    std::stringstream ss("");
    Stream stream(ss);
    char result = stream.peek();
    EXPECT_EQ(result, Stream::eof());
}

// Test peek on non-empty stream returns first character
TEST_F(StreamTest_173, PeekNonEmptyStreamReturnsFirstChar_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    char result = stream.peek();
    EXPECT_EQ(result, 'H');
}

// Test peek does not consume the character (calling peek multiple times returns same)
TEST_F(StreamTest_173, PeekDoesNotConsumeCharacter_173) {
    std::stringstream ss("ABC");
    Stream stream(ss);
    char first = stream.peek();
    char second = stream.peek();
    EXPECT_EQ(first, second);
    EXPECT_EQ(first, 'A');
}

// Test get returns first character and advances
TEST_F(StreamTest_173, GetReturnsFirstCharAndAdvances_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    char c = stream.get();
    EXPECT_EQ(c, 'H');
    char next = stream.peek();
    EXPECT_EQ(next, 'e');
}

// Test get(n) returns string of n characters
TEST_F(StreamTest_173, GetNReturnsNCharacters_173) {
    std::stringstream ss("Hello World");
    Stream stream(ss);
    std::string result = stream.get(5);
    EXPECT_EQ(result, "Hello");
}

// Test operator bool on non-empty stream
TEST_F(StreamTest_173, OperatorBoolNonEmptyStreamIsTrue_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test operator bool on empty stream
TEST_F(StreamTest_173, OperatorBoolEmptyStreamIsFalse_173) {
    std::stringstream ss("");
    Stream stream(ss);
    EXPECT_FALSE(static_cast<bool>(stream));
}

// Test operator! on empty stream
TEST_F(StreamTest_173, OperatorNotEmptyStreamIsTrue_173) {
    std::stringstream ss("");
    Stream stream(ss);
    EXPECT_TRUE(!stream);
}

// Test operator! on non-empty stream
TEST_F(StreamTest_173, OperatorNotNonEmptyStreamIsFalse_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    EXPECT_FALSE(!stream);
}

// Test mark initial values
TEST_F(StreamTest_173, MarkInitialValues_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    Mark m = stream.mark();
    EXPECT_EQ(m.pos, 0);
    EXPECT_EQ(m.line, 0);
    EXPECT_EQ(m.column, 0);
}

// Test pos initial value
TEST_F(StreamTest_173, PosInitiallyZero_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    EXPECT_EQ(stream.pos(), 0);
}

// Test line initial value
TEST_F(StreamTest_173, LineInitiallyZero_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    EXPECT_EQ(stream.line(), 0);
}

// Test column initial value
TEST_F(StreamTest_173, ColumnInitiallyZero_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    EXPECT_EQ(stream.column(), 0);
}

// Test get advances position
TEST_F(StreamTest_173, GetAdvancesPosition_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    stream.get();
    EXPECT_EQ(stream.pos(), 1);
    EXPECT_EQ(stream.column(), 1);
}

// Test eat consumes characters
TEST_F(StreamTest_173, EatConsumesCharacters_173) {
    std::stringstream ss("Hello World");
    Stream stream(ss);
    stream.eat(5);
    char c = stream.peek();
    EXPECT_EQ(c, ' ');
}

// Test eat with zero does nothing
TEST_F(StreamTest_173, EatZeroDoesNothing_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    stream.eat(0);
    char c = stream.peek();
    EXPECT_EQ(c, 'H');
}

// Test reading entire stream character by character
TEST_F(StreamTest_173, ReadEntireStreamCharByChar_173) {
    std::string input = "ABC";
    std::stringstream ss(input);
    Stream stream(ss);
    std::string result;
    while (stream) {
        result += stream.get();
    }
    EXPECT_EQ(result, input);
}

// Test get on empty stream returns eof
TEST_F(StreamTest_173, GetOnEmptyStreamReturnsEof_173) {
    std::stringstream ss("");
    Stream stream(ss);
    char c = stream.get();
    EXPECT_EQ(c, Stream::eof());
}

// Test newline advances line counter
TEST_F(StreamTest_173, NewlineAdvancesLineCounter_173) {
    std::stringstream ss("A\nB");
    Stream stream(ss);
    stream.get(); // 'A'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
}

// Test ResetColumn resets the column
TEST_F(StreamTest_173, ResetColumnResetsColumn_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    stream.get();
    stream.get();
    EXPECT_EQ(stream.column(), 2);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// Test get(n) with n larger than available content
TEST_F(StreamTest_173, GetNMoreThanAvailable_173) {
    std::stringstream ss("Hi");
    Stream stream(ss);
    std::string result = stream.get(10);
    EXPECT_EQ(result.length(), 2u);
    EXPECT_EQ(result, "Hi");
}

// Test single character stream
TEST_F(StreamTest_173, SingleCharacterStream_173) {
    std::stringstream ss("X");
    Stream stream(ss);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ(stream.peek(), 'X');
    char c = stream.get();
    EXPECT_EQ(c, 'X');
    EXPECT_EQ(stream.peek(), Stream::eof());
    EXPECT_FALSE(static_cast<bool>(stream));
}

// Test eat past end of stream
TEST_F(StreamTest_173, EatPastEndOfStream_173) {
    std::stringstream ss("AB");
    Stream stream(ss);
    stream.eat(10);
    EXPECT_EQ(stream.peek(), Stream::eof());
    EXPECT_FALSE(static_cast<bool>(stream));
}

// Test get(n) with n=0 returns empty string
TEST_F(StreamTest_173, GetZeroReturnsEmptyString_173) {
    std::stringstream ss("Hello");
    Stream stream(ss);
    std::string result = stream.get(0);
    EXPECT_EQ(result, "");
    EXPECT_EQ(stream.peek(), 'H'); // position unchanged
}

// Test UTF-8 BOM handling (if applicable)
TEST_F(StreamTest_173, Utf8StreamBasicAscii_173) {
    std::stringstream ss("test");
    Stream stream(ss);
    EXPECT_EQ(stream.get(), 't');
    EXPECT_EQ(stream.get(), 'e');
    EXPECT_EQ(stream.get(), 's');
    EXPECT_EQ(stream.get(), 't');
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test multiple newlines tracking
TEST_F(StreamTest_173, MultipleNewlinesTracking_173) {
    std::stringstream ss("A\nB\nC");
    Stream stream(ss);
    stream.get(); // A
    stream.get(); // \n
    EXPECT_EQ(stream.line(), 1);
    stream.get(); // B
    stream.get(); // \n
    EXPECT_EQ(stream.line(), 2);
    stream.get(); // C
    EXPECT_EQ(stream.line(), 2);
    EXPECT_EQ(stream.column(), 1);
}

// Test large input stream
TEST_F(StreamTest_173, LargeInputStream_173) {
    std::string large_input(5000, 'A');
    std::stringstream ss(large_input);
    Stream stream(ss);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ(stream.peek(), 'A');
    // Consume all
    for (int i = 0; i < 5000; ++i) {
        char c = stream.get();
        EXPECT_EQ(c, 'A');
    }
    EXPECT_EQ(stream.peek(), Stream::eof());
    EXPECT_FALSE(static_cast<bool>(stream));
}

// Test pos after multiple gets
TEST_F(StreamTest_173, PosAfterMultipleGets_173) {
    std::stringstream ss("ABCDE");
    Stream stream(ss);
    stream.get();
    stream.get();
    stream.get();
    EXPECT_EQ(stream.pos(), 3);
}

// Test eat(1) behaves like get without returning
TEST_F(StreamTest_173, EatOneBehavesLikeGetWithoutReturn_173) {
    std::stringstream ss("ABC");
    Stream stream(ss);
    stream.eat(1);
    EXPECT_EQ(stream.peek(), 'B');
    EXPECT_EQ(stream.pos(), 1);
}

// Test carriage return handling
TEST_F(StreamTest_173, CarriageReturnHandling_173) {
    std::stringstream ss("A\r\nB");
    Stream stream(ss);
    stream.get(); // A
    stream.get(); // \r or \n (depending on line ending detection)
    // Just verify stream continues to work
    while (stream) {
        stream.get();
    }
    EXPECT_FALSE(static_cast<bool>(stream));
}

}  // namespace
}  // namespace YAML
