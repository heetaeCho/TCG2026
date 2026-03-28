#include <gtest/gtest.h>
#include <cstring>

// We need to declare the template function we're testing
namespace re2 {
namespace re2_internal {
template <typename T>
bool Parse(const char* str, size_t n, T* dest);

// Explicit declaration for char specialization
template <>
bool Parse(const char* str, size_t n, char* dest);
}  // namespace re2_internal
}  // namespace re2

// Test fixture
class ParseCharTest_269 : public ::testing::Test {
 protected:
  char dest_;
  void SetUp() override {
    dest_ = '\0';
  }
};

// Normal operation: parsing a single character string
TEST_F(ParseCharTest_269, SingleCharParsesSuccessfully_269) {
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ('A', dest_);
}

// Normal operation: parsing different single characters
TEST_F(ParseCharTest_269, SingleCharDifferentChars_269) {
  const char* str = "z";
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ('z', dest_);
}

// Normal operation: parsing a digit character
TEST_F(ParseCharTest_269, SingleDigitChar_269) {
  const char* str = "5";
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ('5', dest_);
}

// Normal operation: parsing a space character
TEST_F(ParseCharTest_269, SpaceChar_269) {
  const char* str = " ";
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ(' ', dest_);
}

// Normal operation: parsing a null character
TEST_F(ParseCharTest_269, NullChar_269) {
  const char str[] = {'\0'};
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ('\0', dest_);
}

// Normal operation: parsing a special character
TEST_F(ParseCharTest_269, SpecialChar_269) {
  const char* str = "\n";
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ('\n', dest_);
}

// Boundary condition: n == 0 should return false
TEST_F(ParseCharTest_269, ZeroLengthReturnsFalse_269) {
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, 0, &dest_);
  EXPECT_FALSE(result);
}

// Boundary condition: n > 1 should return false
TEST_F(ParseCharTest_269, LengthGreaterThanOneReturnsFalse_269) {
  const char* str = "AB";
  bool result = re2::re2_internal::Parse(str, 2, &dest_);
  EXPECT_FALSE(result);
}

// Boundary condition: n == 3 should return false
TEST_F(ParseCharTest_269, LengthThreeReturnsFalse_269) {
  const char* str = "ABC";
  bool result = re2::re2_internal::Parse(str, 3, &dest_);
  EXPECT_FALSE(result);
}

// Boundary condition: very large n should return false
TEST_F(ParseCharTest_269, VeryLargeLengthReturnsFalse_269) {
  const char* str = "ABCDEF";
  bool result = re2::re2_internal::Parse(str, 100, &dest_);
  EXPECT_FALSE(result);
}

// NULL dest with n == 1 should return true without writing
TEST_F(ParseCharTest_269, NullDestWithValidLengthReturnsTrue_269) {
  const char* str = "A";
  bool result = re2::re2_internal::Parse<char>(str, 1, nullptr);
  EXPECT_TRUE(result);
}

// NULL dest with n != 1 should return false
TEST_F(ParseCharTest_269, NullDestWithInvalidLengthReturnsFalse_269) {
  const char* str = "AB";
  bool result = re2::re2_internal::Parse<char>(str, 2, nullptr);
  EXPECT_FALSE(result);
}

// NULL dest with n == 0 should return false
TEST_F(ParseCharTest_269, NullDestWithZeroLengthReturnsFalse_269) {
  const char* str = "";
  bool result = re2::re2_internal::Parse<char>(str, 0, nullptr);
  EXPECT_FALSE(result);
}

// Verify dest is not modified when n != 1
TEST_F(ParseCharTest_269, DestUnchangedOnFailure_269) {
  dest_ = 'X';
  const char* str = "AB";
  bool result = re2::re2_internal::Parse(str, 2, &dest_);
  EXPECT_FALSE(result);
  EXPECT_EQ('X', dest_);  // dest should remain unchanged
}

// Verify dest is not modified when n == 0
TEST_F(ParseCharTest_269, DestUnchangedOnZeroLength_269) {
  dest_ = 'Y';
  const char* str = "";
  bool result = re2::re2_internal::Parse(str, 0, &dest_);
  EXPECT_FALSE(result);
  EXPECT_EQ('Y', dest_);
}

// Test with high-bit character (binary value > 127)
TEST_F(ParseCharTest_269, HighBitChar_269) {
  const char str[] = {static_cast<char>(0xFF)};
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ(static_cast<char>(0xFF), dest_);
}

// Test that the first character of the string is used
TEST_F(ParseCharTest_269, FirstCharacterIsUsed_269) {
  const char* str = "Hello";
  bool result = re2::re2_internal::Parse(str, 1, &dest_);
  EXPECT_TRUE(result);
  EXPECT_EQ('H', dest_);
}

// Edge case: n == SIZE_MAX should return false
TEST_F(ParseCharTest_269, MaxSizeTReturnsFalse_269) {
  const char* str = "A";
  bool result = re2::re2_internal::Parse(str, static_cast<size_t>(-1), &dest_);
  EXPECT_FALSE(result);
}
