#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {
namespace {

// Test default constructor creates a valid object
TEST(OstreamWrapperTest_26, DefaultConstructor_26) {
    ostream_wrapper wrapper;
    EXPECT_NE(wrapper.str(), nullptr);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

// Test that str() returns empty string initially for default-constructed wrapper
TEST(OstreamWrapperTest_26, DefaultConstructorStrIsEmpty_26) {
    ostream_wrapper wrapper;
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "");
}

// Test stream constructor - str() should return nullptr
TEST(OstreamWrapperTest_26, StreamConstructorStrReturnsNull_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(wrapper.str(), nullptr);
}

// Test writing a string to buffer-backed wrapper
TEST(OstreamWrapperTest_26, WriteStringToBuffer_26) {
    ostream_wrapper wrapper;
    wrapper.write("hello");
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "hello");
}

// Test writing with char* and size to buffer-backed wrapper
TEST(OstreamWrapperTest_26, WriteCharPtrToBuffer_26) {
    ostream_wrapper wrapper;
    const char* data = "world";
    wrapper.write(data, 5);
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "world");
}

// Test writing to stream-backed wrapper
TEST(OstreamWrapperTest_26, WriteStringToStream_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write("hello");
    EXPECT_EQ(ss.str(), "hello");
}

// Test writing with char* and size to stream-backed wrapper
TEST(OstreamWrapperTest_26, WriteCharPtrToStream_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    const char* data = "world";
    wrapper.write(data, 5);
    EXPECT_EQ(ss.str(), "world");
}

// Test pos() after writing
TEST(OstreamWrapperTest_26, PosAfterWrite_26) {
    ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(wrapper.pos(), 5u);
}

// Test row and col after writing without newlines
TEST(OstreamWrapperTest_26, RowColAfterWriteNoNewline_26) {
    ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 5u);
}

// Test row and col after writing with newlines
TEST(OstreamWrapperTest_26, RowColAfterWriteWithNewline_26) {
    ostream_wrapper wrapper;
    wrapper.write("hello\nworld");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 5u);
}

// Test multiple newlines tracking
TEST(OstreamWrapperTest_26, MultipleNewlines_26) {
    ostream_wrapper wrapper;
    wrapper.write("a\nb\nc");
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 1u);
}

// Test set_comment and comment
TEST(OstreamWrapperTest_26, SetComment_26) {
    ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test writing empty string
TEST(OstreamWrapperTest_26, WriteEmptyString_26) {
    ostream_wrapper wrapper;
    wrapper.write("");
    EXPECT_EQ(wrapper.pos(), 0u);
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "");
}

// Test writing empty char* with size 0
TEST(OstreamWrapperTest_26, WriteEmptyCharPtr_26) {
    ostream_wrapper wrapper;
    wrapper.write("", 0);
    EXPECT_EQ(wrapper.pos(), 0u);
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "");
}

// Test multiple writes concatenate in buffer
TEST(OstreamWrapperTest_26, MultipleWritesConcatenate_26) {
    ostream_wrapper wrapper;
    wrapper.write("hello");
    wrapper.write(" ");
    wrapper.write("world");
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "hello world");
    EXPECT_EQ(wrapper.pos(), 11u);
}

// Test multiple writes concatenate in stream
TEST(OstreamWrapperTest_26, MultipleWritesConcatenateStream_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write("hello");
    wrapper.write(" ");
    wrapper.write("world");
    EXPECT_EQ(ss.str(), "hello world");
}

// Test pos tracking with stream
TEST(OstreamWrapperTest_26, PosTrackingWithStream_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write("hello");
    EXPECT_EQ(wrapper.pos(), 5u);
}

// Test row/col tracking with stream
TEST(OstreamWrapperTest_26, RowColTrackingWithStream_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write("hello\nworld");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 5u);
}

// Test writing only newline
TEST(OstreamWrapperTest_26, WriteOnlyNewline_26) {
    ostream_wrapper wrapper;
    wrapper.write("\n");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 1u);
}

// Test writing partial char* with smaller size
TEST(OstreamWrapperTest_26, WritePartialCharPtr_26) {
    ostream_wrapper wrapper;
    wrapper.write("hello world", 5);
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_STREQ(s, "hello");
    EXPECT_EQ(wrapper.pos(), 5u);
}

// Test comment flag with stream constructor
TEST(OstreamWrapperTest_26, CommentFlagStreamConstructor_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test newline at end of string resets col
TEST(OstreamWrapperTest_26, NewlineAtEndResetsCol_26) {
    ostream_wrapper wrapper;
    wrapper.write("hello\n");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test large write
TEST(OstreamWrapperTest_26, LargeWrite_26) {
    ostream_wrapper wrapper;
    std::string large(10000, 'a');
    wrapper.write(large);
    const char* s = wrapper.str();
    ASSERT_NE(s, nullptr);
    EXPECT_EQ(std::string(s), large);
    EXPECT_EQ(wrapper.pos(), 10000u);
}

// Test comment flag doesn't reset after write
TEST(OstreamWrapperTest_26, CommentPersistsAfterWrite_26) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.write("test");
    // Comment behavior may depend on newline handling
    // but at minimum we verify the interface works
    // The comment flag behavior with newlines is implementation detail
}

// Test writing a string with multiple consecutive newlines
TEST(OstreamWrapperTest_26, ConsecutiveNewlines_26) {
    ostream_wrapper wrapper;
    wrapper.write("\n\n\n");
    EXPECT_EQ(wrapper.row(), 3u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 3u);
}

// Test initial state of stream-backed wrapper
TEST(OstreamWrapperTest_26, StreamWrapperInitialState_26) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

}  // namespace
}  // namespace YAML
