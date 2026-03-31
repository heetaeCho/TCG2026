#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// Test fixture for ostream_wrapper without a stream (buffer mode)
class OstreamWrapperBufferTest_29 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ostream_wrapper with a stream
class OstreamWrapperStreamTest_29 : public ::testing::Test {
protected:
    std::ostringstream oss;
    void SetUp() override {}
    void TearDown() override {}
};

// === Default constructor tests ===

TEST_F(OstreamWrapperBufferTest_29, DefaultConstructor_InitialPosIsZero_29) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_29, DefaultConstructor_InitialRowIsZero_29) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_29, DefaultConstructor_InitialColIsZero_29) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_29, DefaultConstructor_InitialCommentIsFalse_29) {
    YAML::ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_29, DefaultConstructor_StrIsNotNull_29) {
    YAML::ostream_wrapper wrapper;
    EXPECT_NE(nullptr, wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_29, DefaultConstructor_StrIsEmptyString_29) {
    YAML::ostream_wrapper wrapper;
    EXPECT_STREQ("", wrapper.str());
}

// === Stream constructor tests ===

TEST_F(OstreamWrapperStreamTest_29, StreamConstructor_InitialPosIsZero_29) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_29, StreamConstructor_InitialRowIsZero_29) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperStreamTest_29, StreamConstructor_InitialColIsZero_29) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperStreamTest_29, StreamConstructor_InitialCommentIsFalse_29) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_FALSE(wrapper.comment());
}

// === Write string tests (buffer mode) ===

TEST_F(OstreamWrapperBufferTest_29, WriteString_IncrementsPos_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "hello";
    wrapper.write(text);
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_UpdatesStr_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "hello";
    wrapper.write(text);
    EXPECT_STREQ("hello", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_UpdatesCol_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "hello";
    wrapper.write(text);
    EXPECT_EQ(5u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_RowRemainsZeroWithoutNewline_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "hello";
    wrapper.write(text);
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_NewlineIncrementsRow_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "hello\nworld";
    wrapper.write(text);
    EXPECT_EQ(1u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_NewlineResetsCol_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "hello\nworld";
    wrapper.write(text);
    EXPECT_EQ(5u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_MultipleNewlines_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "a\nb\nc";
    wrapper.write(text);
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(1u, wrapper.col());
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_EmptyString_29) {
    YAML::ostream_wrapper wrapper;
    std::string text = "";
    wrapper.write(text);
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_STREQ("", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_29, WriteString_MultipleWrites_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.write(std::string("hello"));
    wrapper.write(std::string(" world"));
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_STREQ("hello world", wrapper.str());
}

// === Write char* with size tests (buffer mode) ===

TEST_F(OstreamWrapperBufferTest_29, WriteCharPtr_IncrementsPos_29) {
    YAML::ostream_wrapper wrapper;
    const char* text = "hello";
    wrapper.write(text, 5);
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_29, WriteCharPtr_UpdatesStr_29) {
    YAML::ostream_wrapper wrapper;
    const char* text = "hello";
    wrapper.write(text, 5);
    EXPECT_STREQ("hello", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_29, WriteCharPtr_PartialWrite_29) {
    YAML::ostream_wrapper wrapper;
    const char* text = "hello";
    wrapper.write(text, 3);
    EXPECT_EQ(3u, wrapper.pos());
    EXPECT_STREQ("hel", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_29, WriteCharPtr_ZeroSize_29) {
    YAML::ostream_wrapper wrapper;
    const char* text = "hello";
    wrapper.write(text, 0);
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_STREQ("", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_29, WriteCharPtr_WithNewline_29) {
    YAML::ostream_wrapper wrapper;
    const char* text = "hi\nbye";
    wrapper.write(text, 6);
    EXPECT_EQ(6u, wrapper.pos());
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(3u, wrapper.col());
}

// === Stream mode write tests ===

TEST_F(OstreamWrapperStreamTest_29, WriteString_WritesToStream_29) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write(std::string("hello"));
    EXPECT_EQ("hello", oss.str());
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_29, WriteCharPtr_WritesToStream_29) {
    YAML::ostream_wrapper wrapper(oss);
    const char* text = "world";
    wrapper.write(text, 5);
    EXPECT_EQ("world", oss.str());
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_29, WriteString_MultipleWritesToStream_29) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write(std::string("hello"));
    wrapper.write(std::string(" world"));
    EXPECT_EQ("hello world", oss.str());
    EXPECT_EQ(11u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_29, WriteString_NewlineUpdatesRowAndCol_29) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write(std::string("line1\nline2"));
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(5u, wrapper.col());
}

// === set_comment tests ===

TEST_F(OstreamWrapperBufferTest_29, SetComment_SetsCommentTrue_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_29, SetComment_CommentResetAfterNewline_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write(std::string("\n"));
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_29, Comment_DefaultIsFalse_29) {
    YAML::ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
}

// === Boundary: newline only ===

TEST_F(OstreamWrapperBufferTest_29, WriteNewlineOnly_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.write(std::string("\n"));
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_29, WriteMultipleNewlines_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.write(std::string("\n\n\n"));
    EXPECT_EQ(3u, wrapper.pos());
    EXPECT_EQ(3u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

// === Large write ===

TEST_F(OstreamWrapperBufferTest_29, WriteLargeString_29) {
    YAML::ostream_wrapper wrapper;
    std::string large(10000, 'a');
    wrapper.write(large);
    EXPECT_EQ(10000u, wrapper.pos());
    EXPECT_EQ(10000u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

// === Copy and move are deleted ===

TEST_F(OstreamWrapperBufferTest_29, NonCopyableNonMovable_29) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::ostream_wrapper>::value);
    EXPECT_FALSE(std::is_copy_assignable<YAML::ostream_wrapper>::value);
    EXPECT_FALSE(std::is_move_constructible<YAML::ostream_wrapper>::value);
    EXPECT_FALSE(std::is_move_assignable<YAML::ostream_wrapper>::value);
}

// === Trailing newline ===

TEST_F(OstreamWrapperBufferTest_29, WriteTrailingNewline_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.write(std::string("abc\n"));
    EXPECT_EQ(4u, wrapper.pos());
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

// === Single character write ===

TEST_F(OstreamWrapperBufferTest_29, WriteSingleChar_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("x", 1);
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_EQ(1u, wrapper.col());
    EXPECT_STREQ("x", wrapper.str());
}

// === Interleaved string and char* writes ===

TEST_F(OstreamWrapperBufferTest_29, InterleavedWrites_29) {
    YAML::ostream_wrapper wrapper;
    wrapper.write(std::string("ab"));
    wrapper.write("cd", 2);
    wrapper.write(std::string("ef"));
    EXPECT_EQ(6u, wrapper.pos());
    EXPECT_STREQ("abcdef", wrapper.str());
}

// === Stream mode: pos, row, col consistency ===

TEST_F(OstreamWrapperStreamTest_29, PosRowColConsistency_29) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write(std::string("abc\ndef\nghi"));
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(3u, wrapper.col());
}
