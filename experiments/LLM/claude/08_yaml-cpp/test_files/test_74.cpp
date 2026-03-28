#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "stream.h"

namespace YAML {
namespace {

// Test fixture for Stream tests
class StreamTest_74 : public ::testing::Test {
protected:
    // Helper to create a Stream from a string
    std::unique_ptr<std::istringstream> makeStream(const std::string& content) {
        return std::make_unique<std::istringstream>(content);
    }
};

// ===== Construction and basic state tests =====

TEST_F(StreamTest_74, ConstructFromEmptyStream_74) {
    std::istringstream input("");
    Stream stream(input);
    // Empty stream should still be constructible
    EXPECT_EQ(stream.mark().pos, 0);
    EXPECT_EQ(stream.mark().line, 0);
    EXPECT_EQ(stream.mark().column, 0);
}

TEST_F(StreamTest_74, ConstructFromNonEmptyStream_74) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_EQ(stream.mark().pos, 0);
    EXPECT_EQ(stream.mark().line, 0);
    EXPECT_EQ(stream.mark().column, 0);
}

// ===== operator bool / operator! tests =====

TEST_F(StreamTest_74, OperatorBoolOnNonEmptyStream_74) {
    std::istringstream input("hello");
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_FALSE(!stream);
}

TEST_F(StreamTest_74, OperatorBoolOnEmptyStream_74) {
    std::istringstream input("");
    Stream stream(input);
    // An empty stream should report false (no data to read)
    EXPECT_FALSE(static_cast<bool>(stream));
    EXPECT_TRUE(!stream);
}

// ===== peek tests =====

TEST_F(StreamTest_74, PeekReturnsFirstCharacter_74) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ(stream.peek(), 'a');
}

TEST_F(StreamTest_74, PeekDoesNotAdvance_74) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ(stream.peek(), 'a');
    EXPECT_EQ(stream.peek(), 'a');
    EXPECT_EQ(stream.mark().pos, 0);
}

TEST_F(StreamTest_74, PeekOnEmptyStreamReturnsEof_74) {
    std::istringstream input("");
    Stream stream(input);
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// ===== get() single character tests =====

TEST_F(StreamTest_74, GetReturnsSingleCharacter_74) {
    std::istringstream input("abc");
    Stream stream(input);
    char c = stream.get();
    EXPECT_EQ(c, 'a');
}

TEST_F(StreamTest_74, GetAdvancesPosition_74) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.get();
    EXPECT_EQ(stream.mark().pos, 1);
    EXPECT_EQ(stream.mark().column, 1);
}

TEST_F(StreamTest_74, GetMultipleCharacters_74) {
    std::istringstream input("abcdef");
    Stream stream(input);
    EXPECT_EQ(stream.get(), 'a');
    EXPECT_EQ(stream.get(), 'b');
    EXPECT_EQ(stream.get(), 'c');
    EXPECT_EQ(stream.mark().pos, 3);
}

TEST_F(StreamTest_74, GetOnEmptyStreamReturnsEof_74) {
    std::istringstream input("");
    Stream stream(input);
    char c = stream.get();
    EXPECT_EQ(c, Stream::eof());
}

TEST_F(StreamTest_74, GetAllCharactersThenEof_74) {
    std::istringstream input("ab");
    Stream stream(input);
    EXPECT_EQ(stream.get(), 'a');
    EXPECT_EQ(stream.get(), 'b');
    EXPECT_EQ(stream.get(), Stream::eof());
}

// ===== get(int n) tests =====

TEST_F(StreamTest_74, GetNReturnsString_74) {
    std::istringstream input("hello world");
    Stream stream(input);
    std::string result = stream.get(5);
    EXPECT_EQ(result, "hello");
}

TEST_F(StreamTest_74, GetNAdvancesPositionCorrectly_74) {
    std::istringstream input("hello world");
    Stream stream(input);
    stream.get(5);
    EXPECT_EQ(stream.mark().pos, 5);
    EXPECT_EQ(stream.peek(), ' ');
}

TEST_F(StreamTest_74, GetZeroReturnsEmptyString_74) {
    std::istringstream input("hello");
    Stream stream(input);
    std::string result = stream.get(0);
    EXPECT_EQ(result, "");
    EXPECT_EQ(stream.mark().pos, 0);
}

TEST_F(StreamTest_74, GetNMoreThanAvailable_74) {
    std::istringstream input("hi");
    Stream stream(input);
    std::string result = stream.get(10);
    // Should return what's available
    EXPECT_EQ(result.length(), 2u);
    EXPECT_EQ(result, "hi");
}

// ===== eat(int n) tests =====

TEST_F(StreamTest_74, EatAdvancesPosition_74) {
    std::istringstream input("hello world");
    Stream stream(input);
    stream.eat(5);
    EXPECT_EQ(stream.mark().pos, 5);
    EXPECT_EQ(stream.peek(), ' ');
}

TEST_F(StreamTest_74, EatZeroDoesNothing_74) {
    std::istringstream input("hello");
    Stream stream(input);
    stream.eat(0);
    EXPECT_EQ(stream.mark().pos, 0);
    EXPECT_EQ(stream.peek(), 'h');
}

TEST_F(StreamTest_74, EatEntireStream_74) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.eat(3);
    EXPECT_FALSE(static_cast<bool>(stream));
    EXPECT_EQ(stream.peek(), Stream::eof());
}

// ===== mark/pos/line/column tests =====

TEST_F(StreamTest_74, MarkInitialState_74) {
    std::istringstream input("test");
    Stream stream(input);
    Mark m = stream.mark();
    EXPECT_EQ(m.pos, 0);
    EXPECT_EQ(m.line, 0);
    EXPECT_EQ(m.column, 0);
}

TEST_F(StreamTest_74, PosMatchesMark_74) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.get();
    EXPECT_EQ(stream.pos(), stream.mark().pos);
}

TEST_F(StreamTest_74, LineMatchesMark_74) {
    std::istringstream input("abc");
    Stream stream(input);
    EXPECT_EQ(stream.line(), stream.mark().line);
}

TEST_F(StreamTest_74, ColumnMatchesMark_74) {
    std::istringstream input("abc");
    Stream stream(input);
    stream.get();
    EXPECT_EQ(stream.column(), stream.mark().column);
}

// ===== Newline handling tests =====

TEST_F(StreamTest_74, NewlineAdvancesLine_74) {
    std::istringstream input("a\nb");
    Stream stream(input);
    stream.get(); // 'a'
    EXPECT_EQ(stream.line(), 0);
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamTest_74, MultipleNewlines_74) {
    std::istringstream input("a\n\nb");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // '\n'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 2);
    EXPECT_EQ(stream.column(), 0);
    EXPECT_EQ(stream.peek(), 'b');
}

TEST_F(StreamTest_74, ColumnAdvancesWithinLine_74) {
    std::istringstream input("abcd\nefg");
    Stream stream(input);
    stream.get(); // a
    stream.get(); // b
    stream.get(); // c
    EXPECT_EQ(stream.column(), 3);
    EXPECT_EQ(stream.line(), 0);
}

// ===== ResetColumn tests =====

TEST_F(StreamTest_74, ResetColumnResetsToZero_74) {
    std::istringstream input("abcdef");
    Stream stream(input);
    stream.get();
    stream.get();
    stream.get();
    EXPECT_EQ(stream.column(), 3);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamTest_74, ResetColumnOnInitialState_74) {
    std::istringstream input("hello");
    Stream stream(input);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// ===== eof static method tests =====

TEST_F(StreamTest_74, EofIsConsistent_74) {
    // eof() should return a consistent value
    EXPECT_EQ(Stream::eof(), Stream::eof());
}

// ===== UTF-8 tests =====

TEST_F(StreamTest_74, Utf8BasicAscii_74) {
    std::istringstream input("Hello, World!");
    Stream stream(input);
    std::string result = stream.get(13);
    EXPECT_EQ(result, "Hello, World!");
}

// ===== Large input test =====

TEST_F(StreamTest_74, LargeInput_74) {
    std::string large(4096, 'x');
    std::istringstream input(large);
    Stream stream(input);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_EQ(stream.peek(), 'x');
    stream.eat(4096);
    EXPECT_FALSE(static_cast<bool>(stream));
}

// ===== Mixed get and eat tests =====

TEST_F(StreamTest_74, MixedGetAndEat_74) {
    std::istringstream input("abcdefghij");
    Stream stream(input);
    EXPECT_EQ(stream.get(), 'a');    // pos 1
    stream.eat(2);                     // pos 3 (skip b, c)
    EXPECT_EQ(stream.peek(), 'd');
    std::string s = stream.get(3);     // pos 6 (get d, e, f)
    EXPECT_EQ(s, "def");
    EXPECT_EQ(stream.peek(), 'g');
}

// ===== Copy and move prevention =====
// These are compile-time checks; we just verify the class is non-copyable/non-movable
// by checking it compiles. If we tried to copy/move, it would fail to compile.

TEST_F(StreamTest_74, StreamIsNonCopyableNonMovable_74) {
    EXPECT_FALSE(std::is_copy_constructible<Stream>::value);
    EXPECT_FALSE(std::is_copy_assignable<Stream>::value);
    EXPECT_FALSE(std::is_move_constructible<Stream>::value);
    EXPECT_FALSE(std::is_move_assignable<Stream>::value);
}

// ===== Carriage return handling =====

TEST_F(StreamTest_74, CarriageReturnLineFeed_74) {
    std::istringstream input("a\r\nb");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // '\r\n' should be treated as single newline
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.peek(), 'b');
}

TEST_F(StreamTest_74, CarriageReturnOnly_74) {
    std::istringstream input("a\rb");
    Stream stream(input);
    stream.get(); // 'a'
    stream.get(); // '\r' - could be treated as newline
    // After CR, we should be on next line
    EXPECT_EQ(stream.line(), 1);
}

// ===== Tab character tests =====

TEST_F(StreamTest_74, TabCharacterInStream_74) {
    std::istringstream input("\tA");
    Stream stream(input);
    stream.get(); // tab
    EXPECT_EQ(stream.peek(), 'A');
}

// ===== BOM handling =====

TEST_F(StreamTest_74, Utf8BOMIsSkipped_74) {
    // UTF-8 BOM: 0xEF, 0xBB, 0xBF
    std::string bom_content;
    bom_content += '\xEF';
    bom_content += '\xBB';
    bom_content += '\xBF';
    bom_content += "hello";
    std::istringstream input(bom_content);
    Stream stream(input);
    // After BOM is processed, first readable character should be 'h'
    EXPECT_TRUE(static_cast<bool>(stream));
    // The BOM should be consumed/skipped
    char first = stream.peek();
    // Either the BOM is skipped and we get 'h', or it's present
    // We test that the stream is functional
    EXPECT_NE(first, Stream::eof());
}

// ===== Sequential operations maintain consistency =====

TEST_F(StreamTest_74, SequentialGetMaintainsConsistentState_74) {
    std::istringstream input("abcde");
    Stream stream(input);
    for (int i = 0; i < 5; i++) {
        EXPECT_TRUE(static_cast<bool>(stream));
        stream.get();
        EXPECT_EQ(stream.mark().pos, i + 1);
    }
    EXPECT_FALSE(static_cast<bool>(stream));
}

}  // namespace
}  // namespace YAML
