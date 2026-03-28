#include "re2/re2.h"
#include <gtest/gtest.h>
#include <string>
#include <cstdint>

namespace {

// A custom parser function for testing
bool CustomParserSuccess(const char* str, size_t n, void* dest) {
  if (dest != nullptr && n > 0) {
    *static_cast<std::string*>(dest) = std::string(str, n);
  }
  return true;
}

bool CustomParserFailure(const char* str, size_t n, void* dest) {
  return false;
}

bool CustomParserCheckNull(const char* str, size_t n, void* dest) {
  return dest == nullptr;
}

// Test fixture
class ArgTest_42 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test default constructor - Parse should succeed (DoNothing returns true)
TEST_F(ArgTest_42, DefaultConstructor_ParseSucceeds_42) {
  re2::RE2::Arg arg;
  EXPECT_TRUE(arg.Parse("hello", 5));
}

// Test nullptr constructor - Parse should succeed (DoNothing returns true)
TEST_F(ArgTest_42, NullptrConstructor_ParseSucceeds_42) {
  re2::RE2::Arg arg(nullptr);
  EXPECT_TRUE(arg.Parse("test", 4));
}

// Test nullptr constructor with empty string
TEST_F(ArgTest_42, NullptrConstructor_EmptyString_42) {
  re2::RE2::Arg arg(nullptr);
  EXPECT_TRUE(arg.Parse("", 0));
}

// Test with int pointer - DoParse3ary<int> should be used
TEST_F(ArgTest_42, IntPointer_ParsesInteger_42) {
  int value = 0;
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("123", 3));
  EXPECT_EQ(value, 123);
}

// Test with int pointer - invalid integer string
TEST_F(ArgTest_42, IntPointer_InvalidInteger_42) {
  int value = 0;
  re2::RE2::Arg arg(&value);
  EXPECT_FALSE(arg.Parse("abc", 3));
}

// Test with string pointer
TEST_F(ArgTest_42, StringPointer_ParsesString_42) {
  std::string value;
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("hello", 5));
  EXPECT_EQ(value, "hello");
}

// Test with string pointer - empty string
TEST_F(ArgTest_42, StringPointer_EmptyString_42) {
  std::string value = "initial";
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("", 0));
  EXPECT_EQ(value, "");
}

// Test with custom parser that succeeds
TEST_F(ArgTest_42, CustomParser_Success_42) {
  std::string dest;
  re2::RE2::Arg arg(&dest, CustomParserSuccess);
  EXPECT_TRUE(arg.Parse("custom", 6));
  EXPECT_EQ(dest, "custom");
}

// Test with custom parser that fails
TEST_F(ArgTest_42, CustomParser_Failure_42) {
  std::string dest;
  re2::RE2::Arg arg(&dest, CustomParserFailure);
  EXPECT_FALSE(arg.Parse("anything", 8));
}

// Test with custom parser and null dest
TEST_F(ArgTest_42, CustomParser_NullDest_42) {
  re2::RE2::Arg arg(static_cast<std::string*>(nullptr), CustomParserCheckNull);
  EXPECT_TRUE(arg.Parse("test", 4));
}

// Test with long pointer
TEST_F(ArgTest_42, LongPointer_ParsesLong_42) {
  long value = 0;
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("999999", 6));
  EXPECT_EQ(value, 999999L);
}

// Test with float pointer
TEST_F(ArgTest_42, FloatPointer_ParsesFloat_42) {
  float value = 0.0f;
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("3.14", 4));
  EXPECT_NEAR(value, 3.14f, 0.01f);
}

// Test with double pointer
TEST_F(ArgTest_42, DoublePointer_ParsesDouble_42) {
  double value = 0.0;
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("2.71828", 7));
  EXPECT_NEAR(value, 2.71828, 0.00001);
}

// Test Parse with partial length
TEST_F(ArgTest_42, IntPointer_PartialLength_42) {
  int value = 0;
  re2::RE2::Arg arg(&value);
  // Parse only first 2 chars of "123"
  EXPECT_TRUE(arg.Parse("123", 2));
  EXPECT_EQ(value, 12);
}

// Test with negative integer
TEST_F(ArgTest_42, IntPointer_NegativeInteger_42) {
  int value = 0;
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("-42", 3));
  EXPECT_EQ(value, -42);
}

// Test default arg with various input sizes
TEST_F(ArgTest_42, DefaultArg_LargeInput_42) {
  re2::RE2::Arg arg;
  std::string large(10000, 'x');
  EXPECT_TRUE(arg.Parse(large.c_str(), large.size()));
}

// Test with int32_t overflow
TEST_F(ArgTest_42, IntPointer_Overflow_42) {
  int32_t value = 0;
  re2::RE2::Arg arg(&value);
  // A number larger than INT32_MAX
  EXPECT_FALSE(arg.Parse("99999999999999999", 17));
}

// Test string with embedded content
TEST_F(ArgTest_42, StringPointer_BinaryContent_42) {
  std::string value;
  re2::RE2::Arg arg(&value);
  const char data[] = "hel\0lo";
  EXPECT_TRUE(arg.Parse(data, 6));
  EXPECT_EQ(value.size(), 6u);
}

// Test with unsigned int
TEST_F(ArgTest_42, UnsignedIntPointer_42) {
  unsigned int value = 0;
  re2::RE2::Arg arg(&value);
  EXPECT_TRUE(arg.Parse("42", 2));
  EXPECT_EQ(value, 42u);
}

// Test unsigned int with negative value
TEST_F(ArgTest_42, UnsignedIntPointer_NegativeValue_42) {
  unsigned int value = 0;
  re2::RE2::Arg arg(&value);
  EXPECT_FALSE(arg.Parse("-1", 2));
}

}  // namespace
