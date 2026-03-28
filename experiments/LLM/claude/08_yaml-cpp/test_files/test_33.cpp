#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/ostream_wrapper.h"

namespace YAML {
namespace {

// Test default constructor creates a valid ostream_wrapper
TEST(OstreamWrapperTest_33, DefaultConstructor_33) {
  ostream_wrapper stream;
  EXPECT_EQ(stream.pos(), 0u);
  EXPECT_EQ(stream.row(), 0u);
  EXPECT_EQ(stream.col(), 0u);
  EXPECT_FALSE(stream.comment());
  EXPECT_NE(stream.str(), nullptr);
}

// Test constructor with ostream
TEST(OstreamWrapperTest_33, OstreamConstructor_33) {
  std::stringstream ss;
  ostream_wrapper stream(ss);
  EXPECT_EQ(stream.pos(), 0u);
  EXPECT_EQ(stream.row(), 0u);
  EXPECT_EQ(stream.col(), 0u);
  EXPECT_FALSE(stream.comment());
}

// Test writing a single character using operator<<
TEST(OstreamWrapperTest_33, WriteCharOperator_33) {
  ostream_wrapper stream;
  stream << 'A';
  EXPECT_EQ(stream.pos(), 1u);
  EXPECT_EQ(stream.col(), 1u);
  EXPECT_EQ(stream.row(), 0u);
  std::string result(stream.str());
  EXPECT_EQ(result, "A");
}

// Test writing a string using write(const std::string&)
TEST(OstreamWrapperTest_33, WriteString_33) {
  ostream_wrapper stream;
  stream.write("Hello");
  EXPECT_EQ(stream.pos(), 5u);
  EXPECT_EQ(stream.col(), 5u);
  EXPECT_EQ(stream.row(), 0u);
  std::string result(stream.str());
  EXPECT_EQ(result, "Hello");
}

// Test writing with char pointer and size
TEST(OstreamWrapperTest_33, WriteCharPtrWithSize_33) {
  ostream_wrapper stream;
  const char* text = "Hello, World!";
  stream.write(text, 5);
  EXPECT_EQ(stream.pos(), 5u);
  std::string result(stream.str());
  EXPECT_EQ(result, "Hello");
}

// Test writing newline updates row and col
TEST(OstreamWrapperTest_33, WriteNewlineUpdatesRowCol_33) {
  ostream_wrapper stream;
  stream.write("abc\ndef");
  EXPECT_EQ(stream.row(), 1u);
  EXPECT_EQ(stream.col(), 3u);
  EXPECT_EQ(stream.pos(), 7u);
}

// Test multiple newlines
TEST(OstreamWrapperTest_33, MultipleNewlines_33) {
  ostream_wrapper stream;
  stream.write("a\nb\nc");
  EXPECT_EQ(stream.row(), 2u);
  EXPECT_EQ(stream.col(), 1u);
  EXPECT_EQ(stream.pos(), 5u);
}

// Test set_comment and comment
TEST(OstreamWrapperTest_33, SetComment_33) {
  ostream_wrapper stream;
  EXPECT_FALSE(stream.comment());
  stream.set_comment();
  EXPECT_TRUE(stream.comment());
}

// Test that newline resets comment flag
TEST(OstreamWrapperTest_33, NewlineResetsComment_33) {
  ostream_wrapper stream;
  stream.set_comment();
  EXPECT_TRUE(stream.comment());
  stream << '\n';
  EXPECT_FALSE(stream.comment());
}

// Test writing empty string
TEST(OstreamWrapperTest_33, WriteEmptyString_33) {
  ostream_wrapper stream;
  stream.write("");
  EXPECT_EQ(stream.pos(), 0u);
  EXPECT_EQ(stream.row(), 0u);
  EXPECT_EQ(stream.col(), 0u);
}

// Test writing zero-length with char pointer
TEST(OstreamWrapperTest_33, WriteZeroLength_33) {
  ostream_wrapper stream;
  stream.write("something", 0);
  EXPECT_EQ(stream.pos(), 0u);
}

// Test str() returns null-terminated string
TEST(OstreamWrapperTest_33, StrReturnsNullTerminated_33) {
  ostream_wrapper stream;
  stream.write("test");
  const char* result = stream.str();
  EXPECT_STREQ(result, "test");
}

// Test sequential writes
TEST(OstreamWrapperTest_33, SequentialWrites_33) {
  ostream_wrapper stream;
  stream.write("Hello");
  stream.write(", ");
  stream.write("World!");
  EXPECT_EQ(stream.pos(), 13u);
  std::string result(stream.str());
  EXPECT_EQ(result, "Hello, World!");
}

// Test writing to ostream via constructor
TEST(OstreamWrapperTest_33, WriteToOstream_33) {
  std::stringstream ss;
  ostream_wrapper stream(ss);
  stream.write("Hello");
  EXPECT_EQ(ss.str(), "Hello");
  EXPECT_EQ(stream.pos(), 5u);
}

// Test operator<< chaining
TEST(OstreamWrapperTest_33, OperatorChaining_33) {
  ostream_wrapper stream;
  stream << 'A' << 'B' << 'C';
  EXPECT_EQ(stream.pos(), 3u);
  EXPECT_EQ(stream.col(), 3u);
  std::string result(stream.str());
  EXPECT_EQ(result, "ABC");
}

// Test row/col after complex input
TEST(OstreamWrapperTest_33, ComplexRowCol_33) {
  ostream_wrapper stream;
  stream.write("line1\nline2\nline3");
  EXPECT_EQ(stream.row(), 2u);
  EXPECT_EQ(stream.col(), 5u);
}

// Test newline at end
TEST(OstreamWrapperTest_33, NewlineAtEnd_33) {
  ostream_wrapper stream;
  stream.write("hello\n");
  EXPECT_EQ(stream.row(), 1u);
  EXPECT_EQ(stream.col(), 0u);
}

// Test only newlines
TEST(OstreamWrapperTest_33, OnlyNewlines_33) {
  ostream_wrapper stream;
  stream.write("\n\n\n");
  EXPECT_EQ(stream.row(), 3u);
  EXPECT_EQ(stream.col(), 0u);
  EXPECT_EQ(stream.pos(), 3u);
}

// Test writing to ostream with operator<<
TEST(OstreamWrapperTest_33, OperatorToOstream_33) {
  std::stringstream ss;
  ostream_wrapper stream(ss);
  stream << 'X';
  EXPECT_EQ(ss.str(), "X");
  EXPECT_EQ(stream.pos(), 1u);
}

// Test large write
TEST(OstreamWrapperTest_33, LargeWrite_33) {
  ostream_wrapper stream;
  std::string large(10000, 'a');
  stream.write(large);
  EXPECT_EQ(stream.pos(), 10000u);
  EXPECT_EQ(stream.col(), 10000u);
  EXPECT_EQ(stream.row(), 0u);
}

// Test comment persists across writes until newline
TEST(OstreamWrapperTest_33, CommentPersistsUntilNewline_33) {
  ostream_wrapper stream;
  stream.set_comment();
  stream.write("abc");
  EXPECT_TRUE(stream.comment());
  stream.write("def");
  EXPECT_TRUE(stream.comment());
  stream << '\n';
  EXPECT_FALSE(stream.comment());
}

// Test str() is nullptr for ostream-backed wrapper (or at least doesn't crash)
TEST(OstreamWrapperTest_33, StrWithOstreamBacked_33) {
  std::stringstream ss;
  ostream_wrapper stream(ss);
  stream.write("test");
  // str() may return nullptr for ostream-backed wrapper
  // Just ensure it doesn't crash
  stream.str();
}

// Test mixing write methods
TEST(OstreamWrapperTest_33, MixWriteMethods_33) {
  ostream_wrapper stream;
  stream.write("Hi");
  stream << ' ';
  stream.write("there", 5);
  EXPECT_EQ(stream.pos(), 8u);
  std::string result(stream.str());
  EXPECT_EQ(result, "Hi there");
}

// Test initial str() returns empty string
TEST(OstreamWrapperTest_33, InitialStrEmpty_33) {
  ostream_wrapper stream;
  const char* result = stream.str();
  EXPECT_NE(result, nullptr);
  EXPECT_STREQ(result, "");
}

}  // namespace
}  // namespace YAML
