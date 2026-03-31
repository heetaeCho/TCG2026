#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Declaration of the function under test
std::string string_from_unterminated(const char* data, size_t data_length);

// Test normal operation: a regular null-terminated string within the buffer
TEST(StringFromUnterminatedTest_115, NormalNullTerminatedString_115) {
  const char data[] = "hello";
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "hello");
}

// Test normal operation: string that fills the entire buffer without null terminator
TEST(StringFromUnterminatedTest_115, UnterminatedStringFullBuffer_115) {
  const char data[] = {'h', 'e', 'l', 'l', 'o'};
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "hello");
  EXPECT_EQ(result.size(), 5u);
}

// Test boundary condition: data_length is 0
TEST(StringFromUnterminatedTest_115, ZeroLengthReturnsEmpty_115) {
  const char data[] = "hello";
  std::string result = string_from_unterminated(data, 0);
  EXPECT_TRUE(result.empty());
  EXPECT_EQ(result, "");
}

// Test boundary condition: single character, no null terminator
TEST(StringFromUnterminatedTest_115, SingleCharNoNull_115) {
  const char data[] = {'A'};
  std::string result = string_from_unterminated(data, 1);
  EXPECT_EQ(result, "A");
  EXPECT_EQ(result.size(), 1u);
}

// Test boundary condition: single null character
TEST(StringFromUnterminatedTest_115, SingleNullChar_115) {
  const char data[] = {'\0'};
  std::string result = string_from_unterminated(data, 1);
  EXPECT_EQ(result, "");
  EXPECT_EQ(result.size(), 0u);
}

// Test: null terminator at the beginning of a longer buffer
TEST(StringFromUnterminatedTest_115, NullTerminatorAtBeginning_115) {
  const char data[] = {'\0', 'h', 'e', 'l', 'l', 'o'};
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "");
  EXPECT_EQ(result.size(), 0u);
}

// Test: null terminator in the middle of the buffer
TEST(StringFromUnterminatedTest_115, NullTerminatorInMiddle_115) {
  const char data[] = {'h', 'e', '\0', 'l', 'o'};
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "he");
  EXPECT_EQ(result.size(), 2u);
}

// Test: data_length is smaller than the actual string length (truncation)
TEST(StringFromUnterminatedTest_115, DataLengthSmallerThanString_115) {
  const char data[] = "hello world";
  std::string result = string_from_unterminated(data, 5);
  EXPECT_EQ(result, "hello");
  EXPECT_EQ(result.size(), 5u);
}

// Test: buffer full of null characters
TEST(StringFromUnterminatedTest_115, AllNullCharacters_115) {
  const char data[] = {'\0', '\0', '\0', '\0'};
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "");
  EXPECT_EQ(result.size(), 0u);
}

// Test: string with spaces
TEST(StringFromUnterminatedTest_115, StringWithSpaces_115) {
  const char data[] = "hello world";
  std::string result = string_from_unterminated(data, sizeof(data) - 1);  // exclude the trailing null from data_length perspective
  EXPECT_EQ(result, "hello world");
}

// Test: string with trailing padding after null terminator
TEST(StringFromUnterminatedTest_115, StringWithTrailingPadding_115) {
  const char data[] = {'t', 'e', 's', 't', '\0', 'X', 'X', 'X'};
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "test");
  EXPECT_EQ(result.size(), 4u);
}

// Test: large data_length with short null-terminated string
TEST(StringFromUnterminatedTest_115, LargeBufferShortString_115) {
  char data[1024];
  std::memset(data, 'A', sizeof(data));
  data[3] = '\0';  // "AAA\0" followed by 'A's
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "AAA");
  EXPECT_EQ(result.size(), 3u);
}

// Test: data_length of 1 with a non-null character
TEST(StringFromUnterminatedTest_115, LengthOneNonNull_115) {
  const char data[] = {'Z'};
  std::string result = string_from_unterminated(data, 1);
  EXPECT_EQ(result, "Z");
}

// Test: exact match where data_length equals string length (null terminated right at boundary)
TEST(StringFromUnterminatedTest_115, NullTerminatorExactlyAtDataLength_115) {
  const char data[] = {'a', 'b', 'c', '\0'};
  std::string result = string_from_unterminated(data, 4);
  EXPECT_EQ(result, "abc");
  EXPECT_EQ(result.size(), 3u);
}

// Test: binary data with embedded high bytes (non-ASCII)
TEST(StringFromUnterminatedTest_115, BinaryDataNonAscii_115) {
  const char data[] = {'\x80', '\xFF', '\x01', '\x7F'};
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result.size(), 4u);
}

// Test: multiple null terminators - should stop at first
TEST(StringFromUnterminatedTest_115, MultipleNullTerminators_115) {
  const char data[] = {'a', '\0', 'b', '\0', 'c'};
  std::string result = string_from_unterminated(data, sizeof(data));
  EXPECT_EQ(result, "a");
  EXPECT_EQ(result.size(), 1u);
}
