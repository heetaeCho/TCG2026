#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {

// Test default constructor initializes properly
TEST(OstreamWrapperTest_587, DefaultConstructor_587) {
    ostream_wrapper wrapper;
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
    // str() should return a valid pointer (buffer initialized with '\0')
    EXPECT_NE(wrapper.str(), nullptr);
}

// Test constructor with stream
TEST(OstreamWrapperTest_587, StreamConstructor_587) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

// Test writing a simple string to buffer
TEST(OstreamWrapperTest_587, WriteStringToBuffer_587) {
    ostream_wrapper wrapper;
    std::string text = "hello";
    wrapper.write(text);
    EXPECT_EQ(wrapper.pos(), 5u);
    EXPECT_EQ(wrapper.col(), 5u);
    EXPECT_EQ(wrapper.row(), 0u);
    std::string result(wrapper.str(), wrapper.pos());
    EXPECT_EQ(result, "hello");
}

// Test writing char array with size to buffer
TEST(OstreamWrapperTest_587, WriteCharArrayToBuffer_587) {
    ostream_wrapper wrapper;
    const char* text = "world";
    wrapper.write(text, 5);
    EXPECT_EQ(wrapper.pos(), 5u);
    std::string result(wrapper.str(), wrapper.pos());
    EXPECT_EQ(result, "world");
}

// Test writing to stream
TEST(OstreamWrapperTest_587, WriteToStream_587) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    std::string text = "hello stream";
    wrapper.write(text);
    EXPECT_EQ(ss.str(), "hello stream");
    EXPECT_EQ(wrapper.pos(), 12u);
}

// Test writing char array to stream
TEST(OstreamWrapperTest_587, WriteCharArrayToStream_587) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    const char* text = "stream test";
    wrapper.write(text, 11);
    EXPECT_EQ(ss.str(), "stream test");
    EXPECT_EQ(wrapper.pos(), 11u);
}

// Test newline updates row and resets col
TEST(OstreamWrapperTest_587, NewlineUpdatesRowAndCol_587) {
    ostream_wrapper wrapper;
    std::string text = "abc\ndef";
    wrapper.write(text);
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 3u);
    EXPECT_EQ(wrapper.pos(), 7u);
}

// Test multiple newlines
TEST(OstreamWrapperTest_587, MultipleNewlines_587) {
    ostream_wrapper wrapper;
    std::string text = "a\nb\nc";
    wrapper.write(text);
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 1u);
    EXPECT_EQ(wrapper.pos(), 5u);
}

// Test writing empty string
TEST(OstreamWrapperTest_587, WriteEmptyString_587) {
    ostream_wrapper wrapper;
    std::string text = "";
    wrapper.write(text);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test writing empty char array
TEST(OstreamWrapperTest_587, WriteEmptyCharArray_587) {
    ostream_wrapper wrapper;
    wrapper.write("", 0);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test set_comment and comment
TEST(OstreamWrapperTest_587, SetComment_587) {
    ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test newline resets comment flag
TEST(OstreamWrapperTest_587, NewlineResetsComment_587) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    std::string text = "\n";
    wrapper.write(text);
    EXPECT_FALSE(wrapper.comment());
}

// Test multiple writes accumulate in buffer
TEST(OstreamWrapperTest_587, MultipleWritesToBuffer_587) {
    ostream_wrapper wrapper;
    wrapper.write("hello", 5);
    wrapper.write(" ", 1);
    wrapper.write("world", 5);
    EXPECT_EQ(wrapper.pos(), 11u);
    std::string result(wrapper.str(), wrapper.pos());
    EXPECT_EQ(result, "hello world");
}

// Test multiple writes accumulate in stream
TEST(OstreamWrapperTest_587, MultipleWritesToStream_587) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write("hello", 5);
    wrapper.write(" ", 1);
    wrapper.write("world", 5);
    EXPECT_EQ(ss.str(), "hello world");
    EXPECT_EQ(wrapper.pos(), 11u);
}

// Test writing only newline
TEST(OstreamWrapperTest_587, WriteOnlyNewline_587) {
    ostream_wrapper wrapper;
    wrapper.write("\n", 1);
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 1u);
}

// Test writing string with newline at end
TEST(OstreamWrapperTest_587, WriteStringEndingWithNewline_587) {
    ostream_wrapper wrapper;
    wrapper.write("abc\n");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 4u);
}

// Test consecutive newlines
TEST(OstreamWrapperTest_587, ConsecutiveNewlines_587) {
    ostream_wrapper wrapper;
    wrapper.write("\n\n\n", 3);
    EXPECT_EQ(wrapper.row(), 3u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 3u);
}

// Test pos reflects total characters written
TEST(OstreamWrapperTest_587, PosReflectsTotalCharsWritten_587) {
    ostream_wrapper wrapper;
    wrapper.write("abc", 3);
    EXPECT_EQ(wrapper.pos(), 3u);
    wrapper.write("de", 2);
    EXPECT_EQ(wrapper.pos(), 5u);
    wrapper.write("f", 1);
    EXPECT_EQ(wrapper.pos(), 6u);
}

// Test col increments correctly without newlines
TEST(OstreamWrapperTest_587, ColIncrementsWithoutNewlines_587) {
    ostream_wrapper wrapper;
    wrapper.write("abcdef", 6);
    EXPECT_EQ(wrapper.col(), 6u);
    EXPECT_EQ(wrapper.row(), 0u);
}

// Test large write to buffer
TEST(OstreamWrapperTest_587, LargeWriteToBuffer_587) {
    ostream_wrapper wrapper;
    std::string large(10000, 'x');
    wrapper.write(large);
    EXPECT_EQ(wrapper.pos(), 10000u);
    EXPECT_EQ(wrapper.col(), 10000u);
    EXPECT_EQ(wrapper.row(), 0u);
    std::string result(wrapper.str(), wrapper.pos());
    EXPECT_EQ(result, large);
}

// Test large write to stream
TEST(OstreamWrapperTest_587, LargeWriteToStream_587) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    std::string large(10000, 'y');
    wrapper.write(large);
    EXPECT_EQ(ss.str(), large);
    EXPECT_EQ(wrapper.pos(), 10000u);
}

// Test comment persists across writes without newline
TEST(OstreamWrapperTest_587, CommentPersistsAcrossWritesWithoutNewline_587) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.write("abc", 3);
    EXPECT_TRUE(wrapper.comment());
    wrapper.write("def", 3);
    EXPECT_TRUE(wrapper.comment());
}

// Test str() returns correct content after multiple writes
TEST(OstreamWrapperTest_587, StrReturnsCorrectContent_587) {
    ostream_wrapper wrapper;
    wrapper.write("test", 4);
    const char* result = wrapper.str();
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(std::string(result, 4), "test");
}

// Test row and col after complex pattern
TEST(OstreamWrapperTest_587, RowColAfterComplexPattern_587) {
    ostream_wrapper wrapper;
    wrapper.write("line1\nline2\nline3");
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 5u);
    EXPECT_EQ(wrapper.pos(), 17u);
}

// Test writing partial size of a char array
TEST(OstreamWrapperTest_587, WritePartialCharArray_587) {
    ostream_wrapper wrapper;
    wrapper.write("hello world", 5);
    EXPECT_EQ(wrapper.pos(), 5u);
    std::string result(wrapper.str(), wrapper.pos());
    EXPECT_EQ(result, "hello");
}

// Test writing single character
TEST(OstreamWrapperTest_587, WriteSingleCharacter_587) {
    ostream_wrapper wrapper;
    wrapper.write("a", 1);
    EXPECT_EQ(wrapper.pos(), 1u);
    EXPECT_EQ(wrapper.col(), 1u);
    EXPECT_EQ(wrapper.row(), 0u);
}

}  // namespace YAML
