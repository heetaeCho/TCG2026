#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {

// Test fixture for ostream_wrapper with internal buffer (default constructor)
class OstreamWrapperBufferTest_31 : public ::testing::Test {
protected:
    ostream_wrapper wrapper;
};

// Test fixture for ostream_wrapper with external stream
class OstreamWrapperStreamTest_31 : public ::testing::Test {
protected:
    std::stringstream ss;
};

// ==================== Default Constructor Tests ====================

TEST_F(OstreamWrapperBufferTest_31, DefaultConstructor_InitialPositionIsZero_31) {
    EXPECT_EQ(0u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_31, DefaultConstructor_InitialRowIsZero_31) {
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_31, DefaultConstructor_InitialColIsZero_31) {
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_31, DefaultConstructor_InitialCommentIsFalse_31) {
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_31, DefaultConstructor_StrReturnsEmptyString_31) {
    const char* result = wrapper.str();
    ASSERT_NE(nullptr, result);
    EXPECT_STREQ("", result);
}

// ==================== Write String Tests ====================

TEST_F(OstreamWrapperBufferTest_31, WriteString_SingleCharacter_31) {
    wrapper.write(std::string("a"));
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_STREQ("a", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, WriteString_MultipleCharacters_31) {
    wrapper.write(std::string("hello"));
    EXPECT_EQ(5u, wrapper.pos());
    EXPECT_STREQ("hello", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, WriteString_EmptyString_31) {
    wrapper.write(std::string(""));
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_STREQ("", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, WriteString_MultipleWrites_31) {
    wrapper.write(std::string("hello"));
    wrapper.write(std::string(" world"));
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_STREQ("hello world", wrapper.str());
}

// ==================== Write char* Tests ====================

TEST_F(OstreamWrapperBufferTest_31, WriteCharPtr_SingleCharacter_31) {
    wrapper.write("a", 1);
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_STREQ("a", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, WriteCharPtr_MultipleCharacters_31) {
    wrapper.write("hello", 5);
    EXPECT_EQ(5u, wrapper.pos());
    EXPECT_STREQ("hello", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, WriteCharPtr_ZeroSize_31) {
    wrapper.write("hello", 0);
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_STREQ("", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, WriteCharPtr_PartialString_31) {
    wrapper.write("hello", 3);
    EXPECT_EQ(3u, wrapper.pos());
    EXPECT_STREQ("hel", wrapper.str());
}

// ==================== Operator<< with char array Tests ====================

TEST_F(OstreamWrapperBufferTest_31, OperatorShift_CharArrayLiteral_31) {
    wrapper << "test";
    EXPECT_EQ(4u, wrapper.pos());
    EXPECT_STREQ("test", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, OperatorShift_EmptyCharArray_31) {
    wrapper << "";
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_STREQ("", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, OperatorShift_ChainingMultiple_31) {
    wrapper << "hello" << " " << "world";
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_STREQ("hello world", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, OperatorShift_SingleChar_31) {
    wrapper << "x";
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_STREQ("x", wrapper.str());
}

// ==================== Row and Col tracking Tests ====================

TEST_F(OstreamWrapperBufferTest_31, RowCol_NewlineIncrementsRow_31) {
    wrapper.write(std::string("a\n"));
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_31, RowCol_MultipleNewlines_31) {
    wrapper.write(std::string("a\nb\nc"));
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(1u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_31, RowCol_NoNewline_31) {
    wrapper.write(std::string("abc"));
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_EQ(3u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_31, RowCol_NewlineAtEnd_31) {
    wrapper.write(std::string("abc\n"));
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_31, RowCol_OnlyNewlines_31) {
    wrapper.write(std::string("\n\n\n"));
    EXPECT_EQ(3u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_31, RowCol_TextAfterNewline_31) {
    wrapper.write(std::string("\nhello"));
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(5u, wrapper.col());
}

// ==================== Comment Tests ====================

TEST_F(OstreamWrapperBufferTest_31, SetComment_SetsCommentTrue_31) {
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_31, Comment_NewlineResetsComment_31) {
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write(std::string("\n"));
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_31, Comment_NonNewlineDoesNotResetComment_31) {
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write(std::string("abc"));
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_31, Comment_SetCommentMultipleTimes_31) {
    wrapper.set_comment();
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// ==================== External Stream Constructor Tests ====================

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_WritesToStream_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write(std::string("hello"));
    EXPECT_EQ("hello", ss.str());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_InitialPositionIsZero_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(0u, wrapper.pos());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_InitialRowIsZero_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(0u, wrapper.row());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_InitialColIsZero_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_EQ(0u, wrapper.col());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_CommentIsFalse_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    EXPECT_FALSE(wrapper.comment());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_MultipleWrites_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write(std::string("hello"));
    wrapper.write(std::string(" "));
    wrapper.write(std::string("world"));
    EXPECT_EQ("hello world", ss.str());
    EXPECT_EQ(11u, wrapper.pos());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_OperatorShift_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper << "test";
    EXPECT_EQ("test", ss.str());
    EXPECT_EQ(4u, wrapper.pos());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_RowColTracking_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.write(std::string("ab\ncd\ne"));
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(1u, wrapper.col());
    EXPECT_EQ(7u, wrapper.pos());
}

TEST(OstreamWrapperExternalStreamTest_31, StreamConstructor_CommentResetOnNewline_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write(std::string("text\n"));
    EXPECT_FALSE(wrapper.comment());
}

// ==================== Pos tracking ====================

TEST_F(OstreamWrapperBufferTest_31, Pos_IncrementsByWrittenCharacters_31) {
    wrapper.write(std::string("abc"));
    EXPECT_EQ(3u, wrapper.pos());
    wrapper.write(std::string("de"));
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_31, Pos_IncludesNewlines_31) {
    wrapper.write(std::string("a\nb"));
    EXPECT_EQ(3u, wrapper.pos());
}

// ==================== Large data Tests ====================

TEST_F(OstreamWrapperBufferTest_31, LargeWrite_HandlesLargeData_31) {
    std::string large(10000, 'x');
    wrapper.write(large);
    EXPECT_EQ(10000u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_EQ(10000u, wrapper.col());
    EXPECT_STREQ(large.c_str(), wrapper.str());
}

TEST(OstreamWrapperExternalStreamTest_31, LargeWrite_StreamHandlesLargeData_31) {
    std::stringstream ss;
    ostream_wrapper wrapper(ss);
    std::string large(10000, 'y');
    wrapper.write(large);
    EXPECT_EQ(large, ss.str());
    EXPECT_EQ(10000u, wrapper.pos());
}

// ==================== Mixed operations ====================

TEST_F(OstreamWrapperBufferTest_31, MixedOperations_WriteAndOperatorShift_31) {
    wrapper.write(std::string("hello"));
    wrapper << " ";
    wrapper.write("world", 5);
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_STREQ("hello world", wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_31, MixedOperations_WriteCommentNewlineWrite_31) {
    wrapper.write(std::string("# comment"));
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
    wrapper.write(std::string("\n"));
    EXPECT_FALSE(wrapper.comment());
    wrapper.write(std::string("next line"));
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(9u, wrapper.col());
}

// ==================== str() returns null-terminated string ====================

TEST_F(OstreamWrapperBufferTest_31, Str_ReturnsNullTerminatedString_31) {
    wrapper.write(std::string("test"));
    const char* result = wrapper.str();
    ASSERT_NE(nullptr, result);
    EXPECT_EQ(4u, std::strlen(result));
    EXPECT_STREQ("test", result);
}

// ==================== Boundary: single newline ====================

TEST_F(OstreamWrapperBufferTest_31, Boundary_SingleNewline_31) {
    wrapper.write(std::string("\n"));
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

// ==================== Boundary: single character ====================

TEST_F(OstreamWrapperBufferTest_31, Boundary_SingleNonNewlineChar_31) {
    wrapper.write(std::string("x"));
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_EQ(1u, wrapper.col());
}

}  // namespace YAML
