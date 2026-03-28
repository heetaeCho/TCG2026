#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {

// Test default constructor initializes properly
TEST(OstreamWrapperTest_586, DefaultConstructor_586) {
    ostream_wrapper wrapper;
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
    // str() should return a valid pointer (empty string initially)
    EXPECT_NE(wrapper.str(), nullptr);
}

// Test stream constructor
TEST(OstreamWrapperTest_586, StreamConstructor_586) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

// Test writing a simple string to buffer mode
TEST(OstreamWrapperTest_586, WriteStringToBuffer_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("hello"));
    EXPECT_EQ(wrapper.pos(), 5u);
    EXPECT_EQ(wrapper.col(), 5u);
    EXPECT_EQ(wrapper.row(), 0u);
    std::string result(wrapper.str());
    EXPECT_EQ(result, "hello");
}

// Test writing a string to stream mode
TEST(OstreamWrapperTest_586, WriteStringToStream_586) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write(std::string("hello"));
    EXPECT_EQ(wrapper.pos(), 5u);
    EXPECT_EQ(wrapper.col(), 5u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(ss.str(), "hello");
}

// Test writing with char* and size to buffer mode
TEST(OstreamWrapperTest_586, WriteCharPtrToBuffer_586) {
    ostream_wrapper wrapper;
    const char* text = "world";
    wrapper.write(text, 5);
    EXPECT_EQ(wrapper.pos(), 5u);
    std::string result(wrapper.str());
    EXPECT_EQ(result, "world");
}

// Test writing with char* and size to stream mode
TEST(OstreamWrapperTest_586, WriteCharPtrToStream_586) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    const char* text = "world";
    wrapper.write(text, 5);
    EXPECT_EQ(wrapper.pos(), 5u);
    EXPECT_EQ(ss.str(), "world");
}

// Test writing an empty string
TEST(OstreamWrapperTest_586, WriteEmptyString_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string(""));
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test newline advances row and resets col
TEST(OstreamWrapperTest_586, WriteNewlineUpdatesRowAndCol_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("abc\n"));
    EXPECT_EQ(wrapper.pos(), 4u);
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test multiple newlines
TEST(OstreamWrapperTest_586, WriteMultipleNewlines_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("a\nb\nc"));
    EXPECT_EQ(wrapper.pos(), 5u);
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 1u);
}

// Test writing multiple times accumulates
TEST(OstreamWrapperTest_586, MultipleWritesAccumulate_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("hello"));
    wrapper.write(std::string(" world"));
    EXPECT_EQ(wrapper.pos(), 11u);
    std::string result(wrapper.str());
    EXPECT_EQ(result, "hello world");
}

// Test multiple writes to stream
TEST(OstreamWrapperTest_586, MultipleWritesToStream_586) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write(std::string("hello"));
    wrapper.write(std::string(" world"));
    EXPECT_EQ(wrapper.pos(), 11u);
    EXPECT_EQ(ss.str(), "hello world");
}

// Test set_comment and comment
TEST(OstreamWrapperTest_586, SetCommentAndComment_586) {
    ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test comment resets after newline
TEST(OstreamWrapperTest_586, CommentResetsAfterNewline_586) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write(std::string("\n"));
    EXPECT_FALSE(wrapper.comment());
}

// Test row() and col() after complex writes
TEST(OstreamWrapperTest_586, RowColAfterComplexWrites_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("line1\nline2\nline3"));
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 5u);  // "line3" has 5 chars
    EXPECT_EQ(wrapper.pos(), 17u);
}

// Test writing a single character
TEST(OstreamWrapperTest_586, WriteSingleCharacter_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("x"));
    EXPECT_EQ(wrapper.pos(), 1u);
    EXPECT_EQ(wrapper.col(), 1u);
    EXPECT_EQ(wrapper.row(), 0u);
    std::string result(wrapper.str());
    EXPECT_EQ(result, "x");
}

// Test writing only a newline character
TEST(OstreamWrapperTest_586, WriteOnlyNewline_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("\n"));
    EXPECT_EQ(wrapper.pos(), 1u);
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test that str() returns null-terminated string in buffer mode
TEST(OstreamWrapperTest_586, StrReturnsNullTerminated_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("test"));
    const char* s = wrapper.str();
    EXPECT_EQ(std::string(s), "test");
    EXPECT_EQ(s[4], '\0');
}

// Test writing a large string
TEST(OstreamWrapperTest_586, WriteLargeString_586) {
    ostream_wrapper wrapper;
    std::string large(10000, 'a');
    wrapper.write(large);
    EXPECT_EQ(wrapper.pos(), 10000u);
    EXPECT_EQ(wrapper.col(), 10000u);
    EXPECT_EQ(wrapper.row(), 0u);
    std::string result(wrapper.str());
    EXPECT_EQ(result, large);
}

// Test writing a large string with newlines
TEST(OstreamWrapperTest_586, WriteLargeStringWithNewlines_586) {
    ostream_wrapper wrapper;
    std::string text;
    for (int i = 0; i < 100; i++) {
        text += "line\n";
    }
    wrapper.write(text);
    EXPECT_EQ(wrapper.row(), 100u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 500u);
}

// Test writing char* with partial size
TEST(OstreamWrapperTest_586, WriteCharPtrPartialSize_586) {
    ostream_wrapper wrapper;
    const char* text = "hello world";
    wrapper.write(text, 5);
    EXPECT_EQ(wrapper.pos(), 5u);
    std::string result(wrapper.str());
    EXPECT_EQ(result, "hello");
}

// Test writing char* with zero size
TEST(OstreamWrapperTest_586, WriteCharPtrZeroSize_586) {
    ostream_wrapper wrapper;
    const char* text = "hello";
    wrapper.write(text, 0);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test that comment flag persists across writes without newline
TEST(OstreamWrapperTest_586, CommentPersistsWithoutNewline_586) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.write(std::string("some comment text"));
    EXPECT_TRUE(wrapper.comment());
}

// Test stream mode with newlines
TEST(OstreamWrapperTest_586, StreamModeWithNewlines_586) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write(std::string("abc\ndef"));
    EXPECT_EQ(ss.str(), "abc\ndef");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 3u);
}

// Test that pos() corresponds to total bytes written
TEST(OstreamWrapperTest_586, PosCorrespondsTotalBytes_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("abc"));
    EXPECT_EQ(wrapper.pos(), 3u);
    wrapper.write(std::string("de"));
    EXPECT_EQ(wrapper.pos(), 5u);
    wrapper.write(std::string("\n"));
    EXPECT_EQ(wrapper.pos(), 6u);
    wrapper.write(std::string("fg"));
    EXPECT_EQ(wrapper.pos(), 8u);
}

// Test copy and move are deleted (compilation test - just verify existence of delete)
// These would cause compilation errors if attempted, so we just verify the class is usable
TEST(OstreamWrapperTest_586, ClassIsUsable_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("test"));
    EXPECT_EQ(wrapper.pos(), 4u);
}

// Test col resets after each newline
TEST(OstreamWrapperTest_586, ColResetsAfterEachNewline_586) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("abcde"));
    EXPECT_EQ(wrapper.col(), 5u);
    wrapper.write(std::string("\n"));
    EXPECT_EQ(wrapper.col(), 0u);
    wrapper.write(std::string("fg"));
    EXPECT_EQ(wrapper.col(), 2u);
}

}  // namespace YAML
