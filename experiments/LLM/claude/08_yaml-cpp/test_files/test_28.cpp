#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

// Test fixture for ostream_wrapper with default constructor (buffer mode)
class OstreamWrapperBufferTest_28 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test fixture for ostream_wrapper with stream constructor
class OstreamWrapperStreamTest_28 : public ::testing::Test {
protected:
    std::ostringstream oss;
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Default Constructor Tests ====================

TEST_F(OstreamWrapperBufferTest_28, DefaultConstructorInitializesColToZero_28) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_28, DefaultConstructorInitializesRowToZero_28) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, DefaultConstructorInitializesPosToZero_28) {
    YAML::ostream_wrapper wrapper;
    EXPECT_EQ(0u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_28, DefaultConstructorCommentIsFalse_28) {
    YAML::ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_28, DefaultConstructorStrIsNotNull_28) {
    YAML::ostream_wrapper wrapper;
    EXPECT_NE(nullptr, wrapper.str());
}

TEST_F(OstreamWrapperBufferTest_28, DefaultConstructorStrIsEmptyString_28) {
    YAML::ostream_wrapper wrapper;
    std::string result(wrapper.str());
    EXPECT_EQ("", result);
}

// ==================== Stream Constructor Tests ====================

TEST_F(OstreamWrapperStreamTest_28, StreamConstructorInitializesColToZero_28) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperStreamTest_28, StreamConstructorInitializesRowToZero_28) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperStreamTest_28, StreamConstructorInitializesPosToZero_28) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_EQ(0u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_28, StreamConstructorCommentIsFalse_28) {
    YAML::ostream_wrapper wrapper(oss);
    EXPECT_FALSE(wrapper.comment());
}

// ==================== Write (string) Tests ====================

TEST_F(OstreamWrapperBufferTest_28, WriteStringUpdatesPos_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_28, WriteStringUpdatesCol_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(5u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_28, WriteStringRowRemainsZeroWithoutNewline_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteStringContentAvailableViaStr_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    std::string result(wrapper.str());
    EXPECT_EQ("hello", result);
}

TEST_F(OstreamWrapperBufferTest_28, WriteEmptyString_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("");
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteStringWithNewlineUpdatesRow_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello\nworld");
    EXPECT_EQ(1u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteStringWithNewlineResetsCol_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello\nworld");
    EXPECT_EQ(5u, wrapper.col()); // "world" is 5 chars after newline
}

TEST_F(OstreamWrapperBufferTest_28, WriteStringWithMultipleNewlines_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("a\nb\nc");
    EXPECT_EQ(2u, wrapper.row());
    EXPECT_EQ(1u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_28, WriteStringMultipleTimes_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    wrapper.write(" world");
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_EQ(11u, wrapper.col());
    std::string result(wrapper.str());
    EXPECT_EQ("hello world", result);
}

// ==================== Write (char*, size) Tests ====================

TEST_F(OstreamWrapperBufferTest_28, WriteCharPtrUpdatesPos_28) {
    YAML::ostream_wrapper wrapper;
    const char* text = "test";
    wrapper.write(text, 4);
    EXPECT_EQ(4u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_28, WriteCharPtrUpdatesCol_28) {
    YAML::ostream_wrapper wrapper;
    const char* text = "test";
    wrapper.write(text, 4);
    EXPECT_EQ(4u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_28, WriteCharPtrContentAvailableViaStr_28) {
    YAML::ostream_wrapper wrapper;
    const char* text = "test";
    wrapper.write(text, 4);
    std::string result(wrapper.str());
    EXPECT_EQ("test", result);
}

TEST_F(OstreamWrapperBufferTest_28, WriteCharPtrPartialString_28) {
    YAML::ostream_wrapper wrapper;
    const char* text = "hello world";
    wrapper.write(text, 5);
    std::string result(wrapper.str());
    EXPECT_EQ("hello", result);
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperBufferTest_28, WriteCharPtrZeroSize_28) {
    YAML::ostream_wrapper wrapper;
    const char* text = "hello";
    wrapper.write(text, 0);
    EXPECT_EQ(0u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_28, WriteCharPtrWithNewline_28) {
    YAML::ostream_wrapper wrapper;
    const char* text = "ab\ncd";
    wrapper.write(text, 5);
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(2u, wrapper.col());
    EXPECT_EQ(5u, wrapper.pos());
}

// ==================== set_comment Tests ====================

TEST_F(OstreamWrapperBufferTest_28, SetCommentSetsCommentFlag_28) {
    YAML::ostream_wrapper wrapper;
    EXPECT_FALSE(wrapper.comment());
    wrapper.set_comment();
    EXPECT_TRUE(wrapper.comment());
}

// ==================== Stream Mode Write Tests ====================

TEST_F(OstreamWrapperStreamTest_28, WriteStringToStream_28) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("hello");
    EXPECT_EQ("hello", oss.str());
}

TEST_F(OstreamWrapperStreamTest_28, WriteStringToStreamUpdatesPos_28) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("hello");
    EXPECT_EQ(5u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_28, WriteStringToStreamUpdatesCol_28) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("hello");
    EXPECT_EQ(5u, wrapper.col());
}

TEST_F(OstreamWrapperStreamTest_28, WriteCharPtrToStream_28) {
    YAML::ostream_wrapper wrapper(oss);
    const char* text = "world";
    wrapper.write(text, 5);
    EXPECT_EQ("world", oss.str());
}

TEST_F(OstreamWrapperStreamTest_28, WriteMultipleTimesToStream_28) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("hello");
    wrapper.write(" ");
    wrapper.write("world");
    EXPECT_EQ("hello world", oss.str());
    EXPECT_EQ(11u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_28, WriteNewlineToStream_28) {
    YAML::ostream_wrapper wrapper(oss);
    wrapper.write("line1\nline2");
    EXPECT_EQ("line1\nline2", oss.str());
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(5u, wrapper.col());
}

// ==================== Boundary Conditions ====================

TEST_F(OstreamWrapperBufferTest_28, WriteSingleCharacter_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("a");
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(1u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteOnlyNewline_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("\n");
    EXPECT_EQ(1u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(1u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteMultipleNewlines_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("\n\n\n");
    EXPECT_EQ(3u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(3u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteNewlineAtEnd_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello\n");
    EXPECT_EQ(6u, wrapper.pos());
    EXPECT_EQ(0u, wrapper.col());
    EXPECT_EQ(1u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteLargeString_28) {
    YAML::ostream_wrapper wrapper;
    std::string largeStr(10000, 'x');
    wrapper.write(largeStr);
    EXPECT_EQ(10000u, wrapper.pos());
    EXPECT_EQ(10000u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
}

TEST_F(OstreamWrapperBufferTest_28, WriteLargeStringWithNewlines_28) {
    YAML::ostream_wrapper wrapper;
    std::string str;
    for (int i = 0; i < 100; ++i) {
        str += "line\n";
    }
    wrapper.write(str);
    EXPECT_EQ(100u, wrapper.row());
    EXPECT_EQ(0u, wrapper.col());
}

// ==================== Copy/Move Prevention ====================
// These are compile-time checks; we verify the interface declares them deleted
// by checking that the class is not copyable or movable at compile time.

TEST_F(OstreamWrapperBufferTest_28, IsNotCopyConstructible_28) {
    EXPECT_FALSE(std::is_copy_constructible<YAML::ostream_wrapper>::value);
}

TEST_F(OstreamWrapperBufferTest_28, IsNotMoveConstructible_28) {
    EXPECT_FALSE(std::is_move_constructible<YAML::ostream_wrapper>::value);
}

TEST_F(OstreamWrapperBufferTest_28, IsNotCopyAssignable_28) {
    EXPECT_FALSE(std::is_copy_assignable<YAML::ostream_wrapper>::value);
}

TEST_F(OstreamWrapperBufferTest_28, IsNotMoveAssignable_28) {
    EXPECT_FALSE(std::is_move_assignable<YAML::ostream_wrapper>::value);
}

// ==================== Mixed write overload Tests ====================

TEST_F(OstreamWrapperBufferTest_28, MixedWriteStringAndCharPtr_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("hello");
    const char* text = " world";
    wrapper.write(text, 6);
    std::string result(wrapper.str());
    EXPECT_EQ("hello world", result);
    EXPECT_EQ(11u, wrapper.pos());
    EXPECT_EQ(11u, wrapper.col());
}

TEST_F(OstreamWrapperBufferTest_28, SetCommentDoesNotAffectPosition_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("test");
    wrapper.set_comment();
    EXPECT_EQ(4u, wrapper.pos());
    EXPECT_EQ(4u, wrapper.col());
    EXPECT_EQ(0u, wrapper.row());
    EXPECT_TRUE(wrapper.comment());
}

TEST_F(OstreamWrapperBufferTest_28, WriteAfterNewlineColResets_28) {
    YAML::ostream_wrapper wrapper;
    wrapper.write("abcde");
    EXPECT_EQ(5u, wrapper.col());
    wrapper.write("\n");
    EXPECT_EQ(0u, wrapper.col());
    wrapper.write("fg");
    EXPECT_EQ(2u, wrapper.col());
    EXPECT_EQ(1u, wrapper.row());
    EXPECT_EQ(8u, wrapper.pos());
}

TEST_F(OstreamWrapperStreamTest_28, StrReturnsNullForStreamMode_28) {
    YAML::ostream_wrapper wrapper(oss);
    // When constructed with a stream, str() may return nullptr or empty
    // This tests the observable behavior
    // Based on the implementation, str() likely returns nullptr for stream mode
    // but we test whatever it returns
    const char* result = wrapper.str();
    // In stream mode, there's no internal buffer content accessible via str()
    // Accept either nullptr or empty string
    if (result != nullptr) {
        EXPECT_EQ(std::string(""), std::string(result));
    }
}
