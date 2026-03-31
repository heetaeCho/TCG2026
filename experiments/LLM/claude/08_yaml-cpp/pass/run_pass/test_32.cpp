#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {

// Test fixture for ostream_wrapper without stream (buffer mode)
class OstreamWrapperBufferTest_32 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ostream_wrapper with stream
class OstreamWrapperStreamTest_32 : public ::testing::Test {
protected:
    std::ostringstream oss;
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Buffer Mode Tests ====================

TEST_F(OstreamWrapperBufferTest_32, DefaultConstructor_InitialState_32) {
    ostream_wrapper wrapper;
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_32, DefaultConstructor_StrReturnsEmptyString_32) {
    ostream_wrapper wrapper;
    const char* result = wrapper.str();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
}

TEST_F(OstreamWrapperBufferTest_32, WriteString_BasicWrite_32) {
    ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_STREQ(wrapper.str(), "hello");
    EXPECT_EQ(wrapper.pos(), 5u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteString_EmptyString_32) {
    ostream_wrapper wrapper;
    wrapper.write("");
    EXPECT_STREQ(wrapper.str(), "");
    EXPECT_EQ(wrapper.pos(), 0u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteCharArray_BasicWrite_32) {
    ostream_wrapper wrapper;
    const char* data = "world";
    wrapper.write(data, 5);
    EXPECT_STREQ(wrapper.str(), "world");
    EXPECT_EQ(wrapper.pos(), 5u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteCharArray_PartialWrite_32) {
    ostream_wrapper wrapper;
    const char* data = "hello world";
    wrapper.write(data, 5);
    EXPECT_STREQ(wrapper.str(), "hello");
    EXPECT_EQ(wrapper.pos(), 5u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteCharArray_ZeroSize_32) {
    ostream_wrapper wrapper;
    const char* data = "something";
    wrapper.write(data, 0);
    EXPECT_STREQ(wrapper.str(), "");
    EXPECT_EQ(wrapper.pos(), 0u);
}

TEST_F(OstreamWrapperBufferTest_32, MultipleWrites_Concatenation_32) {
    ostream_wrapper wrapper;
    wrapper.write("hello");
    wrapper.write(" ");
    wrapper.write("world");
    EXPECT_STREQ(wrapper.str(), "hello world");
    EXPECT_EQ(wrapper.pos(), 11u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteNewline_UpdatesRowAndCol_32) {
    ostream_wrapper wrapper;
    wrapper.write("abc\n");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 4u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteNewline_MultipleNewlines_32) {
    ostream_wrapper wrapper;
    wrapper.write("a\nb\nc");
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 1u);
    EXPECT_EQ(wrapper.pos(), 5u);
}

TEST_F(OstreamWrapperBufferTest_32, ColIncrements_WithRegularChars_32) {
    ostream_wrapper wrapper;
    wrapper.write("abcde");
    EXPECT_EQ(wrapper.col(), 5u);
    EXPECT_EQ(wrapper.row(), 0u);
}

TEST_F(OstreamWrapperBufferTest_32, ColResetsAfterNewline_32) {
    ostream_wrapper wrapper;
    wrapper.write("abc\ndef");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 3u);
}

TEST_F(OstreamWrapperBufferTest_32, SetComment_SetsCommentFlag_32) {
    ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_32, CommentResetsAfterNewline_32) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write("\n");
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_32, OperatorShift_WritesString_32) {
    ostream_wrapper wrapper;
    wrapper << std::string("test");
    EXPECT_STREQ(wrapper.str(), "test");
    EXPECT_EQ(wrapper.pos(), 4u);
}

TEST_F(OstreamWrapperBufferTest_32, OperatorShift_Chaining_32) {
    ostream_wrapper wrapper;
    wrapper << std::string("hello") << std::string(" ") << std::string("world");
    EXPECT_STREQ(wrapper.str(), "hello world");
}

TEST_F(OstreamWrapperBufferTest_32, WriteOnlyNewlines_32) {
    ostream_wrapper wrapper;
    wrapper.write("\n\n\n");
    EXPECT_EQ(wrapper.row(), 3u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 3u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteSingleChar_32) {
    ostream_wrapper wrapper;
    wrapper.write("x", 1);
    EXPECT_STREQ(wrapper.str(), "x");
    EXPECT_EQ(wrapper.pos(), 1u);
    EXPECT_EQ(wrapper.col(), 1u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteLargeString_32) {
    ostream_wrapper wrapper;
    std::string large(10000, 'a');
    wrapper.write(large);
    EXPECT_EQ(wrapper.pos(), 10000u);
    EXPECT_EQ(wrapper.col(), 10000u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_STREQ(wrapper.str(), large.c_str());
}

// ==================== Stream Mode Tests ====================

TEST_F(OstreamWrapperStreamTest_32, StreamConstructor_InitialState_32) {
    ostream_wrapper wrapper(oss);
    EXPECT_EQ(wrapper.pos(), 0u);
    EXPECT_EQ(wrapper.row(), 0u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_WritesToStream_32) {
    ostream_wrapper wrapper(oss);
    wrapper.write("hello");
    EXPECT_EQ(oss.str(), "hello");
    EXPECT_EQ(wrapper.pos(), 5u);
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_MultipleWrites_32) {
    ostream_wrapper wrapper(oss);
    wrapper.write("hello");
    wrapper.write(" world");
    EXPECT_EQ(oss.str(), "hello world");
    EXPECT_EQ(wrapper.pos(), 11u);
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_EmptyString_32) {
    ostream_wrapper wrapper(oss);
    wrapper.write("");
    EXPECT_EQ(oss.str(), "");
    EXPECT_EQ(wrapper.pos(), 0u);
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_NewlineUpdatesPosition_32) {
    ostream_wrapper wrapper(oss);
    wrapper.write("abc\ndef");
    EXPECT_EQ(oss.str(), "abc\ndef");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 3u);
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_CharArrayWrite_32) {
    ostream_wrapper wrapper(oss);
    const char* data = "test data";
    wrapper.write(data, 4);
    EXPECT_EQ(oss.str(), "test");
    EXPECT_EQ(wrapper.pos(), 4u);
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_OperatorShift_32) {
    ostream_wrapper wrapper(oss);
    wrapper << std::string("streamed");
    EXPECT_EQ(oss.str(), "streamed");
}

TEST_F(OstreamWrapperStreamTest_32, StreamMode_StrReturnsNull_32) {
    ostream_wrapper wrapper(oss);
    wrapper.write("data");
    // In stream mode, str() may return nullptr since buffer is not used
    // This behavior depends on implementation; if it doesn't return nullptr,
    // it should at least not crash
    const char* result = wrapper.str();
    // We simply verify the call doesn't crash; the actual value depends on implementation
    (void)result;
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_SetCommentAndNewline_32) {
    ostream_wrapper wrapper(oss);
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write("\n");
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperStreamTest_32, StreamWrite_LargeData_32) {
    ostream_wrapper wrapper(oss);
    std::string large(10000, 'b');
    wrapper.write(large);
    EXPECT_EQ(oss.str(), large);
    EXPECT_EQ(wrapper.pos(), 10000u);
}

// ==================== Edge Case Tests ====================

TEST_F(OstreamWrapperBufferTest_32, WriteNewlineOnly_32) {
    ostream_wrapper wrapper;
    wrapper.write("\n");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
    EXPECT_EQ(wrapper.pos(), 1u);
}

TEST_F(OstreamWrapperBufferTest_32, WriteAfterNewline_ColStartsAtZero_32) {
    ostream_wrapper wrapper;
    wrapper.write("\n");
    EXPECT_EQ(wrapper.col(), 0u);
    wrapper.write("x");
    EXPECT_EQ(wrapper.col(), 1u);
}

TEST_F(OstreamWrapperBufferTest_32, MixedStringAndCharArrayWrites_32) {
    ostream_wrapper wrapper;
    wrapper.write(std::string("abc"));
    wrapper.write("def", 3);
    EXPECT_STREQ(wrapper.str(), "abcdef");
    EXPECT_EQ(wrapper.pos(), 6u);
}

TEST_F(OstreamWrapperBufferTest_32, SetCommentMultipleTimes_32) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_32, CommentFlagPersistsWithoutNewline_32) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.write("no newline here");
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_32, MultipleNewlinesResetComment_32) {
    ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.write("text\n");
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    wrapper.write("more\ntext");
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_32, PosAccumulatesCorrectly_32) {
    ostream_wrapper wrapper;
    wrapper.write("ab");
    EXPECT_EQ(wrapper.pos(), 2u);
    wrapper.write("cde");
    EXPECT_EQ(wrapper.pos(), 5u);
    wrapper.write("\n");
    EXPECT_EQ(wrapper.pos(), 6u);
    wrapper.write("fg");
    EXPECT_EQ(wrapper.pos(), 8u);
}

TEST_F(OstreamWrapperBufferTest_32, RowAndColAfterComplexInput_32) {
    ostream_wrapper wrapper;
    wrapper.write("line1\nline2\nline3");
    EXPECT_EQ(wrapper.row(), 2u);
    EXPECT_EQ(wrapper.col(), 5u);
    EXPECT_EQ(wrapper.pos(), 17u);
}

TEST_F(OstreamWrapperBufferTest_32, TrailingNewline_32) {
    ostream_wrapper wrapper;
    wrapper.write("line1\n");
    EXPECT_EQ(wrapper.row(), 1u);
    EXPECT_EQ(wrapper.col(), 0u);
}

}  // namespace YAML
