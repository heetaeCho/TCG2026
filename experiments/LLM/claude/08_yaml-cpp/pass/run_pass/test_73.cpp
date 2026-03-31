#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// Test the static eof() method
TEST(StreamTest_73, EofReturnsExpectedValue_73) {
    char eof_char = Stream::eof();
    EXPECT_EQ(eof_char, 0x04);
}

// Test construction with a valid input stream
TEST(StreamTest_73, ConstructWithValidStream_73) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test construction with an empty stream
TEST(StreamTest_73, ConstructWithEmptyStream_73) {
    std::istringstream input("");
    Stream stream(input);
    // An empty stream may still be valid initially or not, 
    // but peek should return eof
    char c = stream.peek();
    EXPECT_EQ(c, Stream::eof());
}

// Test peek returns the first character without consuming it
TEST(StreamTest_73, PeekReturnsFirstCharacter_73) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ(stream.peek(), 'a');
    // Peek again should return same character
    EXPECT_EQ(stream.peek(), 'a');
}

// Test get() returns and consumes one character
TEST(StreamTest_73, GetReturnsSingleCharacter_73) {
    std::istringstream input("abc");
    Stream stream(input);
    char c = stream.get();
    EXPECT_EQ(c, 'a');
    EXPECT_EQ(stream.peek(), 'b');
}

// Test get(int n) returns a string of n characters
TEST(StreamTest_73, GetNReturnsNCharacters_73) {
    std::istringstream input("hello world");
    Stream stream(input);
    std::string result = stream.get(5);
    EXPECT_EQ(result, "hello");
    EXPECT_EQ(stream.peek(), ' ');
}

// Test get() consumes all characters sequentially
TEST(StreamTest_73, GetAllCharactersSequentially_73) {
    std::istringstream input("xyz");
    Stream stream(input);
    EXPECT_EQ(stream.get(), 'x');
    EXPECT_EQ(stream.get(), 'y');
    EXPECT_EQ(stream.get(), 'z');
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test eat(int n) consumes n characters
TEST(StreamTest_73, EatConsumesNCharacters_73) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.eat(3);
    EXPECT_EQ(stream.peek(), 'd');
}

// Test eat(0) does nothing
TEST(StreamTest_73, EatZeroDoesNothing_73) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.eat(0);
    EXPECT_EQ(stream.peek(), 'a');
}

// Test operator bool on a valid stream
TEST(StreamTest_73, OperatorBoolTrueForValidStream_73) {
    std::istringstream input("test");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test operator! on a valid stream
TEST(StreamTest_73, OperatorNotFalseForValidStream_73) {
    std::istringstream input("test");
    Stream stream(input);
    EXPECT_FALSE(!stream);
}

// Test operator bool after consuming all content
TEST(StreamTest_73, OperatorBoolAfterConsumingAll_73) {
    std::istringstream input("a");
    Stream stream(input);
    stream.get();
    // After consuming everything, the stream should indicate no more data
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test mark/pos/line/column initial values
TEST(StreamTest_73, InitialMarkValues_73) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_EQ(stream.pos(), 0);
    EXPECT_EQ(stream.line(), 0);
    EXPECT_EQ(stream.column(), 0);
}

// Test pos increments after get
TEST(StreamTest_73, PosIncrementsAfterGet_73) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.get();
    EXPECT_EQ(stream.pos(), 1);
    stream.get();
    EXPECT_EQ(stream.pos(), 2);
}

// Test column increments after get
TEST(StreamTest_73, ColumnIncrementsAfterGet_73) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.get();
    EXPECT_EQ(stream.column(), 1);
    stream.get();
    EXPECT_EQ(stream.column(), 2);
}

// Test line increments after newline
TEST(StreamTest_73, LineIncrementsAfterNewline_73) {
    std::istringstream input("a\nb");
    Stream stream(input);
    stream.get(); // 'a'
    EXPECT_EQ(stream.line(), 0);
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
}

// Test column resets after newline
TEST(StreamTest_73, ColumnResetsAfterNewline_73) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    EXPECT_EQ(stream.column(), 2);
    stream.get(); // '\n'
    EXPECT_EQ(stream.column(), 0);
    stream.get(); // 'c'
    EXPECT_EQ(stream.column(), 1);
}

// Test ResetColumn
TEST(StreamTest_73, ResetColumnResetsToZero_73) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.get();
    stream.get();
    EXPECT_EQ(stream.column(), 2);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// Test mark() returns current position info
TEST(StreamTest_73, MarkReturnsCurrentPosition_73) {
    std::istringstream input("ab\ncd");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // 'b'
    stream.get(); // '\n'
    stream.get(); // 'c'
    Mark m = stream.mark();
    EXPECT_EQ(m.line, 1);
    EXPECT_EQ(m.column, 1);
    EXPECT_EQ(m.pos, 4);
}

// Test get(n) with n larger than remaining characters
TEST(StreamTest_73, GetNLargerThanRemaining_73) {
    std::istringstream input("ab");
    Stream stream(input);
    std::string result = stream.get(10);
    // Should return what's available
    EXPECT_EQ(result.length(), 2u);
    EXPECT_EQ(result, "ab");
}

// Test get on empty stream returns eof
TEST(StreamTest_73, GetOnEmptyStreamReturnsEof_73) {
    std::istringstream input("");
    Stream stream(input);
    char c = stream.get();
    EXPECT_EQ(c, Stream::eof());
}

// Test peek on exhausted stream returns eof
TEST(StreamTest_73, PeekOnExhaustedStreamReturnsEof_73) {
    std::istringstream input("a");
    Stream stream(input);
    stream.get();
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test eat followed by get
TEST(StreamTest_73, EatThenGet_73) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.eat(2);
    char c = stream.get();
    EXPECT_EQ(c, 'c');
}

// Test get(n) with n = 0
TEST(StreamTest_73, GetZeroReturnsEmptyString_73) {
    std::istringstream input("abc");
    Stream stream(input);
    std::string result = stream.get(0);
    EXPECT_EQ(result, "");
    EXPECT_EQ(stream.peek(), 'a');
}

// Test stream with only newlines
TEST(StreamTest_73, StreamWithOnlyNewlines_73) {
    std::istringstream input("\n\n\n");
    Stream stream(input);
    stream.get(); // first '\n'
    EXPECT_EQ(stream.line(), 1);
    stream.get(); // second '\n'
    EXPECT_EQ(stream.line(), 2);
    stream.get(); // third '\n'
    EXPECT_EQ(stream.line(), 3);
}

// Test stream with tab character
TEST(StreamTest_73, StreamWithTabCharacter_73) {
    std::istringstream input("\t");
    Stream stream(input);
    char c = stream.get();
    EXPECT_EQ(c, '\t');
}

// Test UTF-8 BOM handling
TEST(StreamTest_73, Utf8BomHandling_73) {
    // UTF-8 BOM: EF BB BF
    std::string bom_str = "\xEF\xBB\xBF" "hello";
    std::istringstream input(bom_str);
    Stream stream(input);
    // After BOM is consumed, first visible character should be 'h'
    // (The stream should detect and skip BOM)
    // We check that stream is valid and can read
    EXPECT_TRUE(static_cast<bool>(stream));
}

// Test copy constructor is deleted
TEST(StreamTest_73, CopyConstructorDeleted_73) {
    EXPECT_FALSE(std::is_copy_constructible<Stream>::value);
}

// Test move constructor is deleted
TEST(StreamTest_73, MoveConstructorDeleted_73) {
    EXPECT_FALSE(std::is_move_constructible<Stream>::value);
}

// Test copy assignment is deleted
TEST(StreamTest_73, CopyAssignmentDeleted_73) {
    EXPECT_FALSE(std::is_copy_assignable<Stream>::value);
}

// Test move assignment is deleted
TEST(StreamTest_73, MoveAssignmentDeleted_73) {
    EXPECT_FALSE(std::is_move_assignable<Stream>::value);
}

// Test large input stream
TEST(StreamTest_73, LargeInputStream_73) {
    std::string large_input(4096, 'x');
    std::istringstream input(large_input);
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ(stream.peek(), 'x');
    stream.eat(4096);
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test eat all characters
TEST(StreamTest_73, EatAllCharacters_73) {
    std::istringstream input("abcd");
    Stream stream(input);
    stream.eat(4);
    EXPECT_EQ(stream.peek(), Stream::eof());
    EXPECT_EQ(stream.pos(), 4);
}

// Test mixed get and eat operations
TEST(StreamTest_73, MixedGetAndEat_73) {
    std::istringstream input("abcdefgh");
    Stream stream(input);
    EXPECT_EQ(stream.get(), 'a');
    stream.eat(2);
    EXPECT_EQ(stream.get(), 'd');
    std::string s = stream.get(2);
    EXPECT_EQ(s, "ef");
    stream.eat(1);
    EXPECT_EQ(stream.get(), 'h');
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// Test position after get(n)
TEST(StreamTest_73, PositionAfterGetN_73) {
    std::istringstream input("abcde");
    Stream stream(input);
    stream.get(3);
    EXPECT_EQ(stream.pos(), 3);
    EXPECT_EQ(stream.column(), 3);
}

}  // namespace
}  // namespace YAML
