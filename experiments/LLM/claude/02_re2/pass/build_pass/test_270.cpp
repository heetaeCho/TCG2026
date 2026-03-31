#include <gtest/gtest.h>
#include <climits>

// We need to declare the template and specialization to test it
namespace re2 {
namespace re2_internal {

template <typename T>
bool Parse(const char* str, size_t n, T* dest);

template <>
bool Parse(const char* str, size_t n, signed char* dest);

}  // namespace re2_internal
}  // namespace re2

// Test fixture
class ParseSignedCharTest_270 : public ::testing::Test {
 protected:
  using ParseFn = decltype(&re2::re2_internal::Parse<signed char>);
};

// Normal operation: single character with valid destination
TEST_F(ParseSignedCharTest_270, SingleCharacterParsesSuccessfully_270) {
  signed char dest = 0;
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ('A', dest);
}

// Normal operation: single character 'a'
TEST_F(ParseSignedCharTest_270, SingleLowercaseCharacter_270) {
  signed char dest = 0;
  const char* str = "a";
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ('a', dest);
}

// Normal operation: single digit character
TEST_F(ParseSignedCharTest_270, SingleDigitCharacter_270) {
  signed char dest = 0;
  const char* str = "5";
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ('5', dest);
}

// Normal operation: null byte character
TEST_F(ParseSignedCharTest_270, NullByteCharacter_270) {
  signed char dest = 42;
  const char str[] = {'\0', '\0'};
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ('\0', dest);
}

// Normal operation: space character
TEST_F(ParseSignedCharTest_270, SpaceCharacter_270) {
  signed char dest = 0;
  const char* str = " ";
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(' ', dest);
}

// Normal operation: negative value character (high bit set)
TEST_F(ParseSignedCharTest_270, HighBitSetCharacter_270) {
  signed char dest = 0;
  const char str[] = {static_cast<char>(0xFF)};
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(static_cast<signed char>(0xFF), dest);
}

// Boundary: n == 0 returns false
TEST_F(ParseSignedCharTest_270, ZeroLengthReturnsFalse_270) {
  signed char dest = 42;
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, 0, &dest);
  EXPECT_FALSE(result);
  // dest should remain unchanged since parse failed
  EXPECT_EQ(42, dest);
}

// Boundary: n == 2 returns false
TEST_F(ParseSignedCharTest_270, LengthTwoReturnsFalse_270) {
  signed char dest = 42;
  const char* str = "AB";
  bool result = re2::re2_internal::Parse(str, 2, &dest);
  EXPECT_FALSE(result);
  EXPECT_EQ(42, dest);
}

// Boundary: n == 3 returns false
TEST_F(ParseSignedCharTest_270, LengthThreeReturnsFalse_270) {
  signed char dest = 42;
  const char* str = "ABC";
  bool result = re2::re2_internal::Parse(str, 3, &dest);
  EXPECT_FALSE(result);
  EXPECT_EQ(42, dest);
}

// Boundary: very large n returns false
TEST_F(ParseSignedCharTest_270, VeryLargeLengthReturnsFalse_270) {
  signed char dest = 42;
  const char* str = "ABCDEFGHIJ";
  bool result = re2::re2_internal::Parse(str, 10, &dest);
  EXPECT_FALSE(result);
  EXPECT_EQ(42, dest);
}

// NULL destination with n == 1 returns true
TEST_F(ParseSignedCharTest_270, NullDestWithLengthOneReturnsTrue_270) {
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, 1, static_cast<signed char*>(nullptr));
  EXPECT_TRUE(result);
}

// NULL destination with n != 1 returns false
TEST_F(ParseSignedCharTest_270, NullDestWithLengthZeroReturnsFalse_270) {
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, 0, static_cast<signed char*>(nullptr));
  EXPECT_FALSE(result);
}

// NULL destination with n == 2 returns false
TEST_F(ParseSignedCharTest_270, NullDestWithLengthTwoReturnsFalse_270) {
  const char* str = "AB";
  bool result = re2::re2_internal::Parse(str, 2, static_cast<signed char*>(nullptr));
  EXPECT_FALSE(result);
}

// Verify the first character is stored (not any other)
TEST_F(ParseSignedCharTest_270, StoresFirstCharacter_270) {
  signed char dest = 0;
  const char* str = "XYZ";
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ('X', dest);
}

// Test with special characters
TEST_F(ParseSignedCharTest_270, SpecialCharacterNewline_270) {
  signed char dest = 0;
  const char* str = "\n";
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ('\n', dest);
}

TEST_F(ParseSignedCharTest_270, SpecialCharacterTab_270) {
  signed char dest = 0;
  const char* str = "\t";
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ('\t', dest);
}

// Boundary: max size_t value
TEST_F(ParseSignedCharTest_270, MaxSizeTReturnsFalse_270) {
  signed char dest = 42;
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, SIZE_MAX, &dest);
  EXPECT_FALSE(result);
  EXPECT_EQ(42, dest);
}

// Verify value 127 (max signed char)
TEST_F(ParseSignedCharTest_270, MaxSignedCharValue_270) {
  signed char dest = 0;
  const char str[] = {static_cast<char>(127)};
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(127, dest);
}

// Verify value -128 (min signed char) via char representation
TEST_F(ParseSignedCharTest_270, MinSignedCharValue_270) {
  signed char dest = 0;
  const char str[] = {static_cast<char>(-128)};
  bool result = re2::re2_internal::Parse(str, 1, &dest);
  EXPECT_TRUE(result);
  EXPECT_EQ(-128, dest);
}
