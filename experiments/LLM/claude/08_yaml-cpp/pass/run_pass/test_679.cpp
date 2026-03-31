#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <cstring>
#include "stream.h"

// We need to include the actual implementation
// Adjust the include path as needed for your build system

namespace {

class StreamTest_679 : public ::testing::Test {
protected:
    // Helper to create a stream from a string
    std::unique_ptr<std::istringstream> makeISS(const std::string& s) {
        return std::make_unique<std::istringstream>(s);
    }
};

// ==================== Construction Tests ====================

TEST_F(StreamTest_679, ConstructFromValidStream_679) {
    std::istringstream iss("hello");
    YAML::Stream stream(iss);
    EXPECT_TRUE(static_cast<bool>(stream));
}

TEST_F(StreamTest_679, ConstructFromEmptyStream_679) {
    std::istringstream iss("");
    YAML::Stream stream(iss);
    // Empty stream should still be constructible
    // peek should return eof for empty
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, ConstructFromBadStream_679) {
    std::istringstream iss;
    iss.setstate(std::ios::badbit);
    YAML::Stream stream(iss);
    EXPECT_TRUE(!stream);
}

TEST_F(StreamTest_679, ConstructFromFailStream_679) {
    std::istringstream iss;
    iss.setstate(std::ios::failbit);
    YAML::Stream stream(iss);
    // Should handle gracefully
}

// ==================== Bool Operator Tests ====================

TEST_F(StreamTest_679, BoolOperatorTrueForValidStream_679) {
    std::istringstream iss("test");
    YAML::Stream stream(iss);
    EXPECT_TRUE(static_cast<bool>(stream));
    EXPECT_FALSE(!stream);
}

TEST_F(StreamTest_679, BoolOperatorAfterReadingAll_679) {
    std::istringstream iss("a");
    YAML::Stream stream(iss);
    stream.get();  // read 'a'
    // After reading all content, should eventually return false or eof
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// ==================== Peek Tests ====================

TEST_F(StreamTest_679, PeekReturnsFirstChar_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.peek(), 'a');
}

TEST_F(StreamTest_679, PeekDoesNotAdvance_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.peek(), 'a');
    EXPECT_EQ(stream.peek(), 'a');
    EXPECT_EQ(stream.peek(), 'a');
}

TEST_F(StreamTest_679, PeekOnEmptyReturnsEof_679) {
    std::istringstream iss("");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// ==================== Get (single char) Tests ====================

TEST_F(StreamTest_679, GetReturnsSingleChar_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.get(), 'a');
}

TEST_F(StreamTest_679, GetAdvancesPosition_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.get(), 'a');
    EXPECT_EQ(stream.peek(), 'b');
    EXPECT_EQ(stream.get(), 'b');
    EXPECT_EQ(stream.peek(), 'c');
}

TEST_F(StreamTest_679, GetAllChars_679) {
    std::istringstream iss("xyz");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.get(), 'x');
    EXPECT_EQ(stream.get(), 'y');
    EXPECT_EQ(stream.get(), 'z');
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, GetOnEmptyReturnsEof_679) {
    std::istringstream iss("");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.get(), YAML::Stream::eof());
}

// ==================== Get (n chars) Tests ====================

TEST_F(StreamTest_679, GetNCharsReturnsString_679) {
    std::istringstream iss("hello world");
    YAML::Stream stream(iss);
    std::string result = stream.get(5);
    EXPECT_EQ(result, "hello");
}

TEST_F(StreamTest_679, GetNCharsAdvancesPosition_679) {
    std::istringstream iss("abcdef");
    YAML::Stream stream(iss);
    std::string first = stream.get(3);
    EXPECT_EQ(first, "abc");
    EXPECT_EQ(stream.peek(), 'd');
}

TEST_F(StreamTest_679, GetZeroCharsReturnsEmpty_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    std::string result = stream.get(0);
    EXPECT_EQ(result, "");
    EXPECT_EQ(stream.peek(), 'a');
}

TEST_F(StreamTest_679, GetMoreThanAvailable_679) {
    std::istringstream iss("ab");
    YAML::Stream stream(iss);
    std::string result = stream.get(5);
    // Should return what's available
    EXPECT_EQ(result.size(), 2u);
    EXPECT_EQ(result, "ab");
}

// ==================== Eat Tests ====================

TEST_F(StreamTest_679, EatSkipsChars_679) {
    std::istringstream iss("abcdef");
    YAML::Stream stream(iss);
    stream.eat(3);
    EXPECT_EQ(stream.peek(), 'd');
}

TEST_F(StreamTest_679, EatZeroDoesNothing_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    stream.eat(0);
    EXPECT_EQ(stream.peek(), 'a');
}

TEST_F(StreamTest_679, EatAllChars_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    stream.eat(3);
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// ==================== Mark / Position Tests ====================

TEST_F(StreamTest_679, InitialPositionIsZero_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.pos(), 0);
    EXPECT_EQ(stream.line(), 0);
    EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamTest_679, PositionAdvancesWithGet_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    stream.get();
    EXPECT_EQ(stream.pos(), 1);
    EXPECT_EQ(stream.column(), 1);
}

TEST_F(StreamTest_679, LineAdvancesWithNewline_679) {
    std::istringstream iss("a\nb");
    YAML::Stream stream(iss);
    stream.get(); // 'a'
    EXPECT_EQ(stream.line(), 0);
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamTest_679, MarkReturnsCurrentMark_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    auto m = stream.mark();
    EXPECT_EQ(m.pos, 0);
    EXPECT_EQ(m.line, 0);
    EXPECT_EQ(m.column, 0);
}

TEST_F(StreamTest_679, MarkAfterMultipleGets_679) {
    std::istringstream iss("abcd");
    YAML::Stream stream(iss);
    stream.get();
    stream.get();
    auto m = stream.mark();
    EXPECT_EQ(m.pos, 2);
}

// ==================== ResetColumn Tests ====================

TEST_F(StreamTest_679, ResetColumnResetsToZero_679) {
    std::istringstream iss("abcdef");
    YAML::Stream stream(iss);
    stream.get();
    stream.get();
    EXPECT_EQ(stream.column(), 2);
    stream.ResetColumn();
    EXPECT_EQ(stream.column(), 0);
}

// ==================== Eof Tests ====================

TEST_F(StreamTest_679, EofIsStaticConstant_679) {
    char e = YAML::Stream::eof();
    // eof() should be a consistent value
    EXPECT_EQ(e, YAML::Stream::eof());
}

// ==================== UTF BOM Detection Tests ====================

TEST_F(StreamTest_679, Utf8BomDetection_679) {
    // UTF-8 BOM: EF BB BF
    std::string bom;
    bom += static_cast<char>(0xEF);
    bom += static_cast<char>(0xBB);
    bom += static_cast<char>(0xBF);
    bom += "hello";
    std::istringstream iss(bom);
    YAML::Stream stream(iss);
    EXPECT_TRUE(static_cast<bool>(stream));
    // Should be able to read content after BOM
}

TEST_F(StreamTest_679, Utf16LEBomDetection_679) {
    // UTF-16 LE BOM: FF FE followed by non-zero byte and 00
    std::string data;
    data += static_cast<char>(0xFF);
    data += static_cast<char>(0xFE);
    data += 'a';
    data += '\0';
    std::istringstream iss(data);
    YAML::Stream stream(iss);
    // Should construct without crashing
}

TEST_F(StreamTest_679, Utf16BEBomDetection_679) {
    // UTF-16 BE BOM: FE FF
    std::string data;
    data += static_cast<char>(0xFE);
    data += static_cast<char>(0xFF);
    data += '\0';
    data += 'a';
    std::istringstream iss(data);
    YAML::Stream stream(iss);
    // Should construct without crashing
}

TEST_F(StreamTest_679, Utf32LEBomDetection_679) {
    // UTF-32 LE BOM: FF FE 00 00
    std::string data;
    data += static_cast<char>(0xFF);
    data += static_cast<char>(0xFE);
    data += static_cast<char>(0x00);
    data += static_cast<char>(0x00);
    data += 'a';
    data += '\0';
    data += '\0';
    data += '\0';
    std::istringstream iss(data);
    YAML::Stream stream(iss);
    // Should construct without crashing
}

TEST_F(StreamTest_679, Utf32BEBomDetection_679) {
    // UTF-32 BE BOM: 00 00 FE FF
    std::string data;
    data += static_cast<char>(0x00);
    data += static_cast<char>(0x00);
    data += static_cast<char>(0xFE);
    data += static_cast<char>(0xFF);
    data += '\0';
    data += '\0';
    data += '\0';
    data += 'a';
    std::istringstream iss(data);
    YAML::Stream stream(iss);
    // Should construct without crashing
}

// ==================== Plain ASCII / UTF-8 Content Tests ====================

TEST_F(StreamTest_679, PlainAsciiContent_679) {
    std::istringstream iss("Hello, World!");
    YAML::Stream stream(iss);
    std::string result = stream.get(13);
    EXPECT_EQ(result, "Hello, World!");
}

TEST_F(StreamTest_679, MultiLineContent_679) {
    std::istringstream iss("line1\nline2\nline3");
    YAML::Stream stream(iss);
    
    // Read first line
    std::string first = stream.get(5);
    EXPECT_EQ(first, "line1");
    EXPECT_EQ(stream.line(), 0);
    
    // Read newline
    stream.get();
    EXPECT_EQ(stream.line(), 1);
    EXPECT_EQ(stream.column(), 0);
}

TEST_F(StreamTest_679, TabCharacter_679) {
    std::istringstream iss("\thello");
    YAML::Stream stream(iss);
    stream.get(); // tab
    EXPECT_EQ(stream.peek(), 'h');
}

// ==================== Copy/Move Prevention Tests ====================

// These are compile-time checks; the class declares copy/move as deleted
// We just verify the class is usable as intended

TEST_F(StreamTest_679, StreamIsNotCopyable_679) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::Stream>::value);
    EXPECT_FALSE(std::is_copy_assignable<YAML::Stream>::value);
}

TEST_F(StreamTest_679, StreamIsNotMovable_679) {
    EXPECT_FALSE(std::is_move_constructible<YAML::Stream>::value);
    EXPECT_FALSE(std::is_move_assignable<YAML::Stream>::value);
}

// ==================== Large Input Tests ====================

TEST_F(StreamTest_679, LargeInput_679) {
    // Create input larger than YAML_PREFETCH_SIZE (2048)
    std::string largeContent(4096, 'x');
    std::istringstream iss(largeContent);
    YAML::Stream stream(iss);
    
    // Read all characters
    for (size_t i = 0; i < 4096; ++i) {
        char c = stream.get();
        EXPECT_EQ(c, 'x') << "Mismatch at position " << i;
    }
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, ExactPrefetchSizeInput_679) {
    std::string content(2048, 'y');
    std::istringstream iss(content);
    YAML::Stream stream(iss);
    
    std::string result = stream.get(2048);
    EXPECT_EQ(result.size(), 2048u);
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// ==================== Single Character Input Tests ====================

TEST_F(StreamTest_679, SingleCharInput_679) {
    std::istringstream iss("Z");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.peek(), 'Z');
    EXPECT_EQ(stream.get(), 'Z');
    EXPECT_EQ(stream.peek(), YAML::Stream::eof());
}

// ==================== Eat and Get Interleaved ====================

TEST_F(StreamTest_679, EatThenGet_679) {
    std::istringstream iss("abcdefghij");
    YAML::Stream stream(iss);
    stream.eat(5);
    EXPECT_EQ(stream.get(), 'f');
    EXPECT_EQ(stream.get(), 'g');
}

TEST_F(StreamTest_679, GetThenEat_679) {
    std::istringstream iss("abcdefghij");
    YAML::Stream stream(iss);
    EXPECT_EQ(stream.get(), 'a');
    EXPECT_EQ(stream.get(), 'b');
    stream.eat(3);
    EXPECT_EQ(stream.get(), 'f');
}

// ==================== Carriage Return Tests ====================

TEST_F(StreamTest_679, CarriageReturnLineFeed_679) {
    std::istringstream iss("a\r\nb");
    YAML::Stream stream(iss);
    stream.get(); // 'a'
    stream.get(); // '\r' or handled as newline
    // After \r\n, we should be on the next line at some point
    char c = stream.get(); // might be '\n' or 'b' depending on handling
    // Just verify we can read 'b' eventually
    while (c != 'b' && c != YAML::Stream::eof()) {
        c = stream.get();
    }
    EXPECT_EQ(c, 'b');
}

TEST_F(StreamTest_679, CarriageReturnOnly_679) {
    std::istringstream iss("a\rb");
    YAML::Stream stream(iss);
    stream.get(); // 'a'
    stream.get(); // '\r' - should be treated as newline
    EXPECT_EQ(stream.line(), 1);
}

// ==================== Null byte in stream ====================

TEST_F(StreamTest_679, NullByteLeadingToDetection_679) {
    // A stream starting with 00 xx would trigger UTF detection paths
    std::string data;
    data += static_cast<char>(0x00);
    data += static_cast<char>(0x41);  // 'A'
    std::istringstream iss(data);
    YAML::Stream stream(iss);
    // Should handle without crashing
}

// ==================== Position after eat ====================

TEST_F(StreamTest_679, PositionAfterEat_679) {
    std::istringstream iss("abcdef");
    YAML::Stream stream(iss);
    stream.eat(4);
    EXPECT_EQ(stream.pos(), 4);
    EXPECT_EQ(stream.column(), 4);
}

// ==================== Multiple newlines ====================

TEST_F(StreamTest_679, MultipleNewlines_679) {
    std::istringstream iss("a\n\n\nb");
    YAML::Stream stream(iss);
    stream.get(); // 'a'
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 1);
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 2);
    stream.get(); // '\n'
    EXPECT_EQ(stream.line(), 3);
    EXPECT_EQ(stream.get(), 'b');
}

// ==================== Get(n) with n=1 ====================

TEST_F(StreamTest_679, GetNWith1_679) {
    std::istringstream iss("abc");
    YAML::Stream stream(iss);
    std::string result = stream.get(1);
    EXPECT_EQ(result, "a");
    EXPECT_EQ(stream.peek(), 'b');
}

// ==================== Special YAML characters ====================

TEST_F(StreamTest_679, SpecialYAMLCharacters_679) {
    std::istringstream iss("key: value\n- item");
    YAML::Stream stream(iss);
    std::string result = stream.get(3);
    EXPECT_EQ(result, "key");
    EXPECT_EQ(stream.peek(), ':');
}

} // namespace
