#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// Test default constructor initial state
TEST(OstreamWrapperTest_30, DefaultConstructor_InitialState_30) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

// Test stream constructor initial state
TEST(OstreamWrapperTest_30, StreamConstructor_InitialState_30) {
    std::stringstream ss;
    YAML::ostream_wrapper wrapper(ss);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

// Test str() returns non-null for default constructor
TEST(OstreamWrapperTest_30, DefaultConstructor_StrReturnsNonNull_30) {
    YAML::ostream_wrapper wrapper;
    EXPECT_NE(wrapper.str(), nullptr);
}

// Test writing a simple string updates pos and col
TEST(OstreamWrapperTest_30, WriteString_UpdatesPosAndCol_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(wrapper.pos(), 5u);
    EXPECT_EQ(wrapper.col(), 5u);
    EXPECT_EQ(wrapper.row(), 0u);
}

// Test writing string with newline updates row
TEST(OstreamWrapperTest_30, WriteStringWithNewline_UpdatesRow_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello\nworld");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 5u); // "world" has 5 chars after newline
    EXPECT_EQ(wrapper.pos(), 11u);
}

// Test writing with char pointer and size
TEST(OstreamWrapperTest_30, WriteCharPtrWithSize_30) {
    YAML::ostream_wrapper wrapper;
    const char* text = "abcdef";
    wrapper.write(text, 3);
    EXPECT_EQ(wrapper.pos(), 3u);
    EXPECT_EQ(wrapper.col(), 3u);
    EXPECT_EQ(wrapper.row(), 0u);
}

// Test set_comment sets comment flag
TEST(OstreamWrapperTest_30, SetComment_SetsFlag_30) {
    YAML::ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test comment is cleared after newline write
TEST(OstreamWrapperTest_30, CommentClearedAfterNewline_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write("\n");
    EXPECT_FALSE(wrapper.comment());
}

// Test writing empty string doesn't change state
TEST(OstreamWrapperTest_30, WriteEmptyString_NoChange_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("");
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test writing empty char ptr with zero size
TEST(OstreamWrapperTest_30, WriteEmptyCharPtr_NoChange_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("", 0);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
}

// Test str() returns correct content after write (default constructor)
TEST(OstreamWrapperTest_30, StrReturnsWrittenContent_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("test");
    const char* result = wrapper.str();
    EXPECT_STREQ(result, "test");
}

// Test multiple writes accumulate content
TEST(OstreamWrapperTest_30, MultipleWrites_AccumulateContent_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    wrapper.write(" ");
    wrapper.write("world");
    EXPECT_EQ(wrapper.pos(), 11u);
    EXPECT_STREQ(wrapper.str(), "hello world");
}

// Test stream constructor writes to stream
TEST(OstreamWrapperTest_30, StreamConstructor_WritesToStream_30) {
    std::stringstream ss;
    YAML::ostream_wrapper wrapper(ss);
    wrapper.write("output");
    EXPECT_EQ(ss.str(), "output");
}

// Test multiple newlines update row correctly
TEST(OstreamWrapperTest_30, MultipleNewlines_UpdateRowCorrectly_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("a\nb\nc");
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 1u);
    EXPECT_EQ(wrapper.pos(), 5u);
}

// Test col resets after newline
TEST(OstreamWrapperTest_30, ColResetsAfterNewline_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("abcde");
    EXPECT_EQ(wrapper.col(), 5u);
    wrapper.write("\n");
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.row(), 1u);
}

// Test writing only newlines
TEST(OstreamWrapperTest_30, WriteOnlyNewlines_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("\n\n\n");
    EXPECT_EQ(wrapper.row(), 3u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 3u);
}

// Test set_comment multiple times
TEST(OstreamWrapperTest_30, SetCommentMultipleTimes_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test comment persists without newline
TEST(OstreamWrapperTest_30, CommentPersistsWithoutNewline_30) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.write("some text");
    EXPECT_TRUE(wrapper.comment());
}

// Test writing via char pointer with size for partial string
TEST(OstreamWrapperTest_30, WritePartialCharPtr_30) {
    YAML::ostream_wrapper wrapper;
    const char* data = "hello world";
    wrapper.write(data, 5);
    EXPECT_EQ(wrapper.pos(), 5u);
    EXPECT_STREQ(wrapper.str(), "hello");
}

// Test stream constructor with multiple writes
TEST(OstreamWrapperTest_30, StreamConstructor_MultipleWrites_30) {
    std::stringstream ss;
    YAML::ostream_wrapper wrapper(ss);
    wrapper.write("foo");
    wrapper.write("bar");
    EXPECT_EQ(ss.str(), "foobar");
    EXPECT_EQ(wrapper.pos(), 6u);
}

// Test large write
TEST(OstreamWrapperTest_30, LargeWrite_30) {
    YAML::ostream_wrapper wrapper;
    std::string large(10000, 'x');
    wrapper.write(large);
    EXPECT_EQ(wrapper.pos(), 10000u);
    EXPECT_EQ(wrapper.col(), 10000u);
    EXPECT_EQ(wrapper.row(), 0u);
}

// Test writing std::string version
TEST(OstreamWrapperTest_30, WriteStdString_30) {
    YAML::ostream_wrapper wrapper;
    std::string s = "test string";
    wrapper.write(s);
    EXPECT_EQ(wrapper.pos(), s.size());
    EXPECT_STREQ(wrapper.str(), "test string");
}

// Test copy constructor is deleted (compile-time, but we verify move too)
// This is a compile-time check; we just verify the object works correctly after construction
TEST(OstreamWrapperTest_30, NonCopyableNonMovable_30) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::ostream_wrapper>::value);
    EXPECT_FALSE(std::is_move_constructible<YAML::ostream_wrapper>::value);
    EXPECT_FALSE(std::is_copy_assignable<YAML::ostream_wrapper>::value);
    EXPECT_FALSE(std::is_move_assignable<YAML::ostream_wrapper>::value);
}
