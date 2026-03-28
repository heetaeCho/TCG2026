#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include <vector>
#include "image_int.hpp"

using namespace Exiv2::Internal;

// Helper to get the string output from the binaryToStringHelper
template <typename T>
std::string toString(const binaryToStringHelper<T>& helper) {
  std::ostringstream oss;
  oss << helper;
  return oss.str();
}

// Test fixture
class BinaryToStringHelperTest_62 : public ::testing::Test {
 protected:
};

// Test with a simple printable ASCII string (no null terminator issues)
TEST_F(BinaryToStringHelperTest_62, PrintableAsciiString_62) {
  std::string input = "Hello";
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "Hello");
}

// Test with non-printable characters replaced by dots
TEST_F(BinaryToStringHelperTest_62, NonPrintableCharactersReplacedByDots_62) {
  std::vector<char> input = {'\x01', '\x02', '\x03'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "...");
}

// Test with a null terminator at the end (last byte is 0, should be skipped)
TEST_F(BinaryToStringHelperTest_62, NullTerminatorAtEndIsSkipped_62) {
  std::vector<char> input = {'A', 'B', '\0'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "AB");
}

// Test with null byte NOT at the end (should be printed as dot)
TEST_F(BinaryToStringHelperTest_62, NullByteInMiddleIsDot_62) {
  std::vector<char> input = {'A', '\0', 'B'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "A.B");
}

// Test with empty buffer
TEST_F(BinaryToStringHelperTest_62, EmptyBuffer_62) {
  std::vector<char> input = {};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "");
}

// Test with single printable character
TEST_F(BinaryToStringHelperTest_62, SinglePrintableCharacter_62) {
  std::vector<char> input = {'Z'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "Z");
}

// Test with single null character (last byte is 0, should be skipped)
TEST_F(BinaryToStringHelperTest_62, SingleNullCharacter_62) {
  std::vector<char> input = {'\0'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "");
}

// Test boundary: character with value 31 (non-printable, should be dot)
TEST_F(BinaryToStringHelperTest_62, CharValue31IsDot_62) {
  std::vector<char> input = {static_cast<char>(31), 'A'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, ".A");
}

// Test boundary: character with value 32 (space, printable)
TEST_F(BinaryToStringHelperTest_62, CharValue32IsSpace_62) {
  std::vector<char> input = {static_cast<char>(32), 'A'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, " A");
}

// Test boundary: character with value 126 (tilde, printable)
TEST_F(BinaryToStringHelperTest_62, CharValue126IsPrintable_62) {
  std::vector<char> input = {static_cast<char>(126)};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "~");
}

// Test boundary: character with value 127 (DEL, non-printable, should be dot)
TEST_F(BinaryToStringHelperTest_62, CharValue127IsDot_62) {
  std::vector<char> input = {static_cast<char>(127)};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, ".");
}

// Test with high byte values (above 127, non-printable)
TEST_F(BinaryToStringHelperTest_62, HighByteValuesAreDots_62) {
  std::vector<char> input = {static_cast<char>(0xFF), static_cast<char>(0x80), 'A'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "..A");
}

// Test mix of printable and non-printable with null terminator at end
TEST_F(BinaryToStringHelperTest_62, MixedWithNullTerminator_62) {
  std::vector<char> input = {'H', 'i', '\x01', '!', '\0'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "Hi.!");
}

// Test multiple null bytes, only the last one is skipped
TEST_F(BinaryToStringHelperTest_62, MultipleNullBytesOnlyLastSkipped_62) {
  std::vector<char> input = {'\0', '\0', '\0'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "..");
}

// Test all printable characters in the range [32, 126]
TEST_F(BinaryToStringHelperTest_62, AllPrintableRange_62) {
  std::vector<char> input;
  std::string expected;
  for (int c = 32; c <= 126; ++c) {
    input.push_back(static_cast<char>(c));
    expected.push_back(static_cast<char>(c));
  }
  // Add a non-null terminator to avoid skipping
  input.push_back('X');
  expected.push_back('X');
  
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, expected);
}

// Test that the stream is returned correctly for chaining
TEST_F(BinaryToStringHelperTest_62, StreamChainingWorks_62) {
  std::vector<char> input = {'A', 'B'};
  auto helper = binaryToString(input.data(), input.size());
  std::ostringstream oss;
  oss << "prefix_" << helper << "_suffix";
  EXPECT_EQ(oss.str(), "prefix_AB_suffix");
}

// Test with only null byte at the beginning and printable chars after
TEST_F(BinaryToStringHelperTest_62, NullAtBeginning_62) {
  std::vector<char> input = {'\0', 'A', 'B', 'C'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, ".ABC");
}

// Test two-character buffer with null at end
TEST_F(BinaryToStringHelperTest_62, TwoCharNullAtEnd_62) {
  std::vector<char> input = {'X', '\0'};
  auto helper = binaryToString(input.data(), input.size());
  std::string result = toString(helper);
  EXPECT_EQ(result, "X");
}
