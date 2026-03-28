#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// Test fixture for ostream_wrapper using internal buffer (default constructor)
class OstreamWrapperBufferTest_27 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ostream_wrapper using external stream
class OstreamWrapperStreamTest_27 : public ::testing::Test {
protected:
    std::ostringstream oss;
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(OstreamWrapperBufferTest_27, DefaultConstructorInitialRow_27) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_27, DefaultConstructorInitialCol_27) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_27, DefaultConstructorInitialPos_27) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_27, DefaultConstructorInitialComment_27) {
    YAML::ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_27, DefaultConstructorStrNotNull_27) {
    YAML::ostream_wrapper wrapper;
    EXPECT_NE(nullptr, wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_27, DefaultConstructorStrIsEmptyString_27) {
    YAML::ostream_wrapper wrapper;
    // The buffer starts with a null terminator, so str() should be empty string
    EXPECT_STREQ("", wrapper.str());
}

// ==================== Stream Constructor Tests ====================

TEST_F(OstreamWrapperStreamTest_27, StreamConstructorInitialRow_27) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperStreamTest_27, StreamConstructorInitialCol_27) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperStreamTest_27, StreamConstructorInitialPos_27) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_27, StreamConstructorInitialComment_27) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_FALSE(wrapper.comment());
}

// ==================== Write (string) Tests ====================

TEST_F(OstreamWrapperBufferTest_27, WriteStringUpdatesPos_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_27, WriteStringUpdatesCol_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(5u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_27, WriteStringRowUnchangedNoNewline_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_27, WriteStringContent_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_STREQ("hello", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_27, WriteEmptyString_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("");
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_27, WriteStringWithNewline_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello\nworld");
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(5u, wrapper.col()); // "world" is 5 chars after newline
    EXPECT_EQ(11u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_27, WriteStringMultipleNewlines_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("a\nb\nc");
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(1u, wrapper.col());
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_27, WriteStringOnlyNewlines_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("\n\n\n");
    EXPECT_EQ(3u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(3u, wrapper.pos());
}

// ==================== Write (char*, size) Tests ====================

TEST_F(OstreamWrapperBufferTest_27, WriteCharPtrUpdatesPos_27) {
    YAML::ostream_wrapper wrapper;
    const char* data = "test";
    wrapper.write(data, 4);
    EXPECT_EQ(4u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_27, WriteCharPtrUpdatesCol_27) {
    YAML::ostream_wrapper wrapper;
    const char* data = "test";
    wrapper.write(data, 4);
    EXPECT_EQ(4u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_27, WriteCharPtrContent_27) {
    YAML::ostream_wrapper wrapper;
    const char* data = "test";
    wrapper.write(data, 4);
    EXPECT_STREQ("test", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_27, WriteCharPtrPartialString_27) {
    YAML::ostream_wrapper wrapper;
    const char* data = "testing";
    wrapper.write(data, 4);
    EXPECT_EQ(4u, wrapper.pos());
    EXPECT_STREQ("test", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_27, WriteCharPtrZeroSize_27) {
    YAML::ostream_wrapper wrapper;
    const char* data = "test";
    wrapper.write(data, 0);
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_27, WriteCharPtrWithNewline_27) {
    YAML::ostream_wrapper wrapper;
    const char* data = "ab\ncd";
    wrapper.write(data, 5);
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(2u, wrapper.col());
    EXPECT_EQ(5u, wrapper.pos());
}

// ==================== Multiple Writes Tests ====================

TEST_F(OstreamWrapperBufferTest_27, MultipleWritesConcatenate_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    wrapper.write(" ");
    wrapper.write("world");
    EXPECT_STREQ("hello world", wrapper.str());
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_EQ(11u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_27, MultipleWritesWithNewlines_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("line1\n");
    wrapper.write("line2\n");
    wrapper.write("line3");
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(5u, wrapper.col());
    EXPECT_EQ(17u, wrapper.pos());
}

// ==================== set_comment Tests ====================

TEST_F(OstreamWrapperBufferTest_27, SetCommentSetsFlag_27) {
    YAML::ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_27, CommentResetAfterNewline_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write("\n");
    // After newline, comment should be reset
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_27, SetCommentMultipleTimes_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_27, CommentNotResetByNonNewline_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    wrapper.write("abc");
    EXPECT_TRUE(wrapper.comment());
}

// ==================== Stream Output Tests ====================

TEST_F(OstreamWrapperStreamTest_27, WriteToStreamUpdatesPos_27) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("hello");
    EXPECT_EQ(5u, wrapper.pos());
    EXPECT_EQ(5u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperStreamTest_27, WriteToStreamOutputsCorrectly_27) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("hello world");
    EXPECT_EQ("hello world", oss.str());
}

TEST_F(OstreamWrapperStreamTest_27, WriteToStreamWithNewline_27) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("line1\nline2");
    EXPECT_EQ("line1\nline2", oss.str());
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(5u, wrapper.col());
}

TEST_F(OstreamWrapperStreamTest_27, MultipleWritesToStream_27) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("foo");
    wrapper.write("bar");
    EXPECT_EQ("foobar", oss.str());
    EXPECT_EQ(6u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_27, WriteCharPtrToStream_27) {
    YAML::ostream_wrapper wrapper(oss);
    const char* data = "testing123";
    wrapper.write(data, 7);
    EXPECT_EQ("testing", oss.str());
    EXPECT_EQ(7u, wrapper.pos());
}

// ==================== Boundary Tests ====================

TEST_F(OstreamWrapperBufferTest_27, WriteSingleCharacter_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("x");
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(1u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_STREQ("x", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_27, WriteSingleNewline_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("\n");
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(1u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_27, WriteLargeString_27) {
    YAML::ostream_wrapper wrapper;
    std::string largeStr(10000, 'a');
    wrapper.write(largeStr);
    EXPECT_EQ(10000u, wrapper.pos());
    EXPECT_EQ(10000u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_27, WriteLargeStringWithNewlines_27) {
    YAML::ostream_wrapper wrapper;
    std::string str;
    for (int i = 0; i < 100; ++i) {
        str += "line" + std::to_string(i) + "\n";
    }
    wrapper.write(str);
    EXPECT_EQ(100u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col()); // last char is newline
}

TEST_F(OstreamWrapperBufferTest_27, NewlineAtEndResetsCol_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello\n");
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(6u, wrapper.pos());
}

// ==================== Copy/Move Prevention Tests ====================
// These are compile-time checks; we verify the class is non-copyable and non-movable
// by checking that the delete declarations exist (verified by the interface).

// ==================== Row/Col Tracking Across Multiple Writes ====================

TEST_F(OstreamWrapperBufferTest_27, RowColTrackingAcrossWrites_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("abc");
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_EQ(3u, wrapper.col());

    wrapper.write("\n");
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());

    wrapper.write("de");
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(2u, wrapper.col());

    wrapper.write("\nfgh");
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(3u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_27, PosIsAlwaysCumulative_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("abc");
    EXPECT_EQ(3u, wrapper.pos());
    wrapper.write("\n");
    EXPECT_EQ(4u, wrapper.pos());
    wrapper.write("de");
    EXPECT_EQ(6u, wrapper.pos());
}

// ==================== Mixed write overloads ====================

TEST_F(OstreamWrapperBufferTest_27, MixedWriteOverloads_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    const char* data = " world";
    wrapper.write(data, 6);
    EXPECT_STREQ("hello world", wrapper.str());
    EXPECT_EQ(11u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_27, SetCommentOnStreamWrapper_27) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write("\n");
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_27, ConsecutiveNewlines_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("\n\n\n\n\n");
    EXPECT_EQ(5u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_27, CarriageReturnHandling_27) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("abc\rdef");
    // \r is not \n, so behavior depends on implementation
    // We just verify it doesn't crash and pos is updated
    EXPECT_EQ(7u, wrapper.pos());
}
