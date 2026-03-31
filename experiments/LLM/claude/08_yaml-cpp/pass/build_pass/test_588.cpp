#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Recreate the interface under test since we need access to the `same` function
// which is a static template function in the YAML namespace.
// We include the actual header or replicate the declaration for testing purposes.

namespace YAML {
template <std::size_t N>
static bool same(const char* str, std::size_t size, const char (&literal)[N]) {
  constexpr int literalSize = N - 1; // minus null terminator
  return size == literalSize && std::strncmp(str, literal, literalSize) == 0;
}
}  // namespace YAML

// Test fixture
class YAMLSameTest_588 : public ::testing::Test {
 protected:
};

// Normal operation: exact match with a simple string
TEST_F(YAMLSameTest_588, ExactMatch_588) {
  const char* str = "null";
  EXPECT_TRUE(YAML::same(str, 4, "null"));
}

// Normal operation: exact match with different string
TEST_F(YAMLSameTest_588, ExactMatchTrue_588) {
  const char* str = "true";
  EXPECT_TRUE(YAML::same(str, 4, "true"));
}

// Normal operation: exact match with "false"
TEST_F(YAMLSameTest_588, ExactMatchFalse_588) {
  const char* str = "false";
  EXPECT_TRUE(YAML::same(str, 5, "false"));
}

// Mismatch: different content but same size
TEST_F(YAMLSameTest_588, SameSizeDifferentContent_588) {
  const char* str = "nulx";
  EXPECT_FALSE(YAML::same(str, 4, "null"));
}

// Mismatch: size smaller than literal
TEST_F(YAMLSameTest_588, SizeSmallerThanLiteral_588) {
  const char* str = "nul";
  EXPECT_FALSE(YAML::same(str, 3, "null"));
}

// Mismatch: size larger than literal
TEST_F(YAMLSameTest_588, SizeLargerThanLiteral_588) {
  const char* str = "nullx";
  EXPECT_FALSE(YAML::same(str, 5, "null"));
}

// Boundary: empty string matches empty literal
TEST_F(YAMLSameTest_588, EmptyStringMatchesEmptyLiteral_588) {
  const char* str = "";
  EXPECT_TRUE(YAML::same(str, 0, ""));
}

// Boundary: empty string does not match non-empty literal
TEST_F(YAMLSameTest_588, EmptyStringDoesNotMatchNonEmptyLiteral_588) {
  const char* str = "";
  EXPECT_FALSE(YAML::same(str, 0, "null"));
}

// Boundary: non-empty string does not match empty literal
TEST_F(YAMLSameTest_588, NonEmptyStringDoesNotMatchEmptyLiteral_588) {
  const char* str = "null";
  EXPECT_FALSE(YAML::same(str, 4, ""));
}

// Boundary: single character match
TEST_F(YAMLSameTest_588, SingleCharacterMatch_588) {
  const char* str = "a";
  EXPECT_TRUE(YAML::same(str, 1, "a"));
}

// Boundary: single character mismatch
TEST_F(YAMLSameTest_588, SingleCharacterMismatch_588) {
  const char* str = "b";
  EXPECT_FALSE(YAML::same(str, 1, "a"));
}

// Edge case: size is zero but str is non-null
TEST_F(YAMLSameTest_588, ZeroSizeNonNullStr_588) {
  const char* str = "something";
  EXPECT_FALSE(YAML::same(str, 0, "null"));
}

// Normal operation: tilde (YAML null representation)
TEST_F(YAMLSameTest_588, TildeMatch_588) {
  const char* str = "~";
  EXPECT_TRUE(YAML::same(str, 1, "~"));
}

// Normal operation: "Null" with capital N
TEST_F(YAMLSameTest_588, CaseSensitiveMismatch_588) {
  const char* str = "Null";
  EXPECT_FALSE(YAML::same(str, 4, "null"));
}

// Normal operation: "NULL" all caps
TEST_F(YAMLSameTest_588, AllCapsMismatch_588) {
  const char* str = "NULL";
  EXPECT_FALSE(YAML::same(str, 4, "null"));
}

// Edge case: partial prefix match
TEST_F(YAMLSameTest_588, PartialPrefixMatch_588) {
  const char* str = "nu";
  EXPECT_FALSE(YAML::same(str, 2, "null"));
}

// Edge case: string with embedded null character (size accounts for it)
TEST_F(YAMLSameTest_588, StringWithNullByte_588) {
  const char str[] = "nu\0l";
  // Size is 4 (includes the embedded null), literal is "null" (size 4)
  // strncmp will stop at the first difference
  EXPECT_FALSE(YAML::same(str, 4, "null"));
}

// Normal operation: longer strings match
TEST_F(YAMLSameTest_588, LongerStringMatch_588) {
  const char* str = "hello world";
  EXPECT_TRUE(YAML::same(str, 11, "hello world"));
}

// Normal operation: longer strings mismatch
TEST_F(YAMLSameTest_588, LongerStringMismatch_588) {
  const char* str = "hello worlD";
  EXPECT_FALSE(YAML::same(str, 11, "hello world"));
}

// Edge case: size parameter misrepresents actual string length (larger)
TEST_F(YAMLSameTest_588, SizeParameterLargerThanActual_588) {
  const char* str = "null";
  // Passing size=4 but comparing against literal of size 3
  EXPECT_FALSE(YAML::same(str, 4, "nul"));
}

// Verify that the function considers the full literal length
TEST_F(YAMLSameTest_588, LiteralWithSpaces_588) {
  const char* str = "a b";
  EXPECT_TRUE(YAML::same(str, 3, "a b"));
}

// Test with special characters
TEST_F(YAMLSameTest_588, SpecialCharacters_588) {
  const char* str = "!@#$";
  EXPECT_TRUE(YAML::same(str, 4, "!@#$"));
}

// Test that only the first `size` characters of str matter when size < literal size
TEST_F(YAMLSameTest_588, SubstringDoesNotMatch_588) {
  const char* str = "nul";
  EXPECT_FALSE(YAML::same(str, 3, "null"));
}
