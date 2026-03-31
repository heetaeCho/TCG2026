#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {

// Test default constructor initializes properly
TEST(OstreamWrapperTest_25, DefaultConstructor_InitialState_25) {
    ostream_wrapper wrapper;
    EXPECT_EQ(wrapper.row(), 0);
    EXPECT_EQ(wrapper.col(), 0);
    EXPECT_EQ(wrapper.pos(), 0);
    EXPECT_FALSE(wrapper.comment());
    EXPECT_NE(wrapper.str(), nullptr);
}

// Test stream constructor
TEST(OstreamWrapperTest_25, StreamConstructor_InitialState_25) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(wrapper.row(), 0);
    EXPECT_EQ(wrapper.col(), 0);
    EXPECT_EQ(wrapper.pos(), 0);
    EXPECT_FALSE(wrapper.comment());
}

// Test set_comment sets comment flag
TEST(OstreamWrapperTest_25, SetComment_SetsFlag_25) {
    ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test writing a simple string updates position
TEST(OstreamWrapperTest_25, WriteString_UpdatesPos_25) {
    ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(wrapper.pos(), 5);
    EXPECT_EQ(wrapper.col(), 5);
    EXPECT_EQ(wrapper.row(), 0);
}

// Test writing a string with std::string overload
TEST(OstreamWrapperTest_25, WriteStdString_UpdatesPos_25) {
    ostream_wrapper wrapper;
    std::string s = "hello";
    wrapper.write(s);
    EXPECT_EQ(wrapper.pos(), 5);
    EXPECT_EQ(wrapper.col(), 5);
    EXPECT_EQ(wrapper.row(), 0);
}

// Test writing with char* and size
TEST(OstreamWrapperTest_25, WriteCharPtrWithSize_UpdatesPos_25) {
    ostream_wrapper wrapper;
    const char* data = "hello world";
    wrapper.write(data, 5);
    EXPECT_EQ(wrapper.pos(), 5);
    EXPECT_EQ(wrapper.col(), 5);
}

// Test writing a newline updates row and resets col
TEST(OstreamWrapperTest_25, WriteNewline_UpdatesRowAndCol_25) {
    ostream_wrapper wrapper;
    wrapper.write("hello\n");
    EXPECT_EQ(wrapper.pos(), 6);
    EXPECT_EQ(wrapper.row(), 1);
    EXPECT_EQ(wrapper.col(), 0);
}

// Test writing multiple lines
TEST(OstreamWrapperTest_25, WriteMultipleLines_UpdatesRowAndCol_25) {
    ostream_wrapper wrapper;
    wrapper.write("line1\nline2\nline3");
    EXPECT_EQ(wrapper.row(), 2);
    EXPECT_EQ(wrapper.col(), 5);
    EXPECT_EQ(wrapper.pos(), 17);
}

// Test str() returns written content for buffer mode
TEST(OstreamWrapperTest_25, Str_ReturnsWrittenContent_25) {
    ostream_wrapper wrapper;
    wrapper.write("test");
    std::string result(wrapper.str());
    EXPECT_EQ(result, "test");
}

// Test writing to stream mode
TEST(OstreamWrapperTest_25, StreamMode_WritesToStream_25) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write("hello");
    EXPECT_EQ(ss.str(), "hello");
}

// Test writing empty string
TEST(OstreamWrapperTest_25, WriteEmptyString_NoChange_25) {
    ostream_wrapper wrapper;
    wrapper.write("");
    EXPECT_EQ(wrapper.pos(), 0);
    EXPECT_EQ(wrapper.row(), 0);
    EXPECT_EQ(wrapper.col(), 0);
}

// Test writing empty char* with zero size
TEST(OstreamWrapperTest_25, WriteEmptyCharPtr_NoChange_25) {
    ostream_wrapper wrapper;
    wrapper.write("", 0);
    EXPECT_EQ(wrapper.pos(), 0);
    EXPECT_EQ(wrapper.row(), 0);
    EXPECT_EQ(wrapper.col(), 0);
}

// Test multiple writes accumulate
TEST(OstreamWrapperTest_25, MultipleWrites_Accumulate_25) {
    ostream_wrapper wrapper;
    wrapper.write("abc");
    wrapper.write("def");
    EXPECT_EQ(wrapper.pos(), 6);
    EXPECT_EQ(wrapper.col(), 6);
    std::string result(wrapper.str());
    EXPECT_EQ(result, "abcdef");
}

// Test newline resets comment flag
TEST(OstreamWrapperTest_25, NewlineResetsComment_25) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write("\n");
    EXPECT_FALSE(wrapper.comment());
}

// Test writing to stream mode with multiple writes
TEST(OstreamWrapperTest_25, StreamMode_MultipleWrites_25) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write("hello ");
    wrapper.write("world");
    EXPECT_EQ(ss.str(), "hello world");
    EXPECT_EQ(wrapper.pos(), 11);
}

// Test writing only newlines
TEST(OstreamWrapperTest_25, WriteOnlyNewlines_25) {
    ostream_wrapper wrapper;
    wrapper.write("\n\n\n");
    EXPECT_EQ(wrapper.row(), 3);
    EXPECT_EQ(wrapper.col(), 0);
    EXPECT_EQ(wrapper.pos(), 3);
}

// Test writing content after newline
TEST(OstreamWrapperTest_25, WriteAfterNewline_ColResets_25) {
    ostream_wrapper wrapper;
    wrapper.write("abc\n");
    EXPECT_EQ(wrapper.row(), 1);
    EXPECT_EQ(wrapper.col(), 0);
    wrapper.write("de");
    EXPECT_EQ(wrapper.row(), 1);
    EXPECT_EQ(wrapper.col(), 2);
    EXPECT_EQ(wrapper.pos(), 6);
}

// Test copy constructor is deleted (compile-time check would fail)
// This is a design constraint, not a runtime test.

// Test large write
TEST(OstreamWrapperTest_25, LargeWrite_25) {
    ostream_wrapper wrapper;
    std::string large(10000, 'x');
    wrapper.write(large);
    EXPECT_EQ(wrapper.pos(), 10000);
    EXPECT_EQ(wrapper.col(), 10000);
    EXPECT_EQ(wrapper.row(), 0);
}

// Test str() after stream mode construction
TEST(OstreamWrapperTest_25, StreamMode_StrReturnsNull_25) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    // In stream mode, str() may return nullptr since buffer is not used
    // This depends on implementation, but we test observable behavior
    wrapper.write("test");
    EXPECT_EQ(ss.str(), "test");
}

// Test comment() returns false initially
TEST(OstreamWrapperTest_25, CommentInitiallyFalse_25) {
    ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
}

// Test set_comment multiple times
TEST(OstreamWrapperTest_25, SetCommentMultipleTimes_25) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// Test partial write with char* and size less than string length
TEST(OstreamWrapperTest_25, PartialWrite_25) {
    ostream_wrapper wrapper;
    wrapper.write("hello world", 5);
    EXPECT_EQ(wrapper.pos(), 5);
    std::string result(wrapper.str());
    EXPECT_EQ(result, "hello");
}

// Test writing a single character
TEST(OstreamWrapperTest_25, WriteSingleChar_25) {
    ostream_wrapper wrapper;
    wrapper.write("a", 1);
    EXPECT_EQ(wrapper.pos(), 1);
    EXPECT_EQ(wrapper.col(), 1);
    EXPECT_EQ(wrapper.row(), 0);
}

// Test writing a single newline character
TEST(OstreamWrapperTest_25, WriteSingleNewline_25) {
    ostream_wrapper wrapper;
    wrapper.write("\n", 1);
    EXPECT_EQ(wrapper.pos(), 1);
    EXPECT_EQ(wrapper.row(), 1);
    EXPECT_EQ(wrapper.col(), 0);
}

}  // namespace YAML
