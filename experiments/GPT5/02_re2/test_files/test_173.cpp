// File: ./TestProjects/re2/util/pcre_pattern_test_173.cc
#include <gtest/gtest.h>
#include <string>
#include "TestProjects/re2/util/pcre.h"

using re2::PCRE;

class PCRETest_173 : public ::testing::Test {};

// [Normal] Construct with const char* and read back the same pattern.
TEST_F(PCRETest_173, PatternReturnsOriginalCString_173) {
  PCRE re("abc123");
  EXPECT_EQ(re.pattern(), std::string("abc123"));
}

// [Normal] Construct with std::string and read back the same pattern (special chars).
TEST_F(PCRETest_173, PatternReturnsOriginalStdStringWithMetaChars_173) {
  std::string pat = R"(a.*(b)\d+\s?)";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), pat);
}

// [Boundary] Empty pattern should be preserved exactly.
TEST_F(PCRETest_173, PatternEmptyString_173) {
  std::string empty;
  PCRE re(empty);
  EXPECT_TRUE(re.pattern().empty());
  EXPECT_EQ(re.pattern().size(), 0u);
}

// [Boundary] Large pattern: ensure full content preserved and length correct.
TEST_F(PCRETest_173, PatternLargeString_173) {
  std::string big(10000, 'x');  // 10k characters
  PCRE re(big);
  EXPECT_EQ(re.pattern().size(), big.size());
  EXPECT_EQ(re.pattern(), big);
}

// [International/UTF-8] Non-ASCII content should be preserved byte-for-byte.
TEST_F(PCRETest_173, PatternUnicode_173) {
  std::string pat = "한글-テスト-π";
  PCRE re(pat);
  EXPECT_EQ(re.pattern(), pat);
}

// [API contract] pattern() returns a const reference; type-check at compile time.
TEST_F(PCRETest_173, PatternAccessorTypeIsConstRef_173) {
  // This is a compile-time assertion on the accessor type.
  static_assert(std::is_same<decltype(std::declval<const PCRE>().pattern()),
                             const std::string&>::value,
                "pattern() must return const std::string&");
  SUCCEED();
}

// [API behavior] Reference stability: subsequent calls return the same underlying object.
TEST_F(PCRETest_173, PatternReferenceStability_173) {
  PCRE re("stable");
  const std::string& ref1 = re.pattern();
  const std::string& ref2 = re.pattern();
  // Both references should alias the same underlying std::string object.
  EXPECT_EQ(&ref1, &ref2);
  EXPECT_EQ(&ref1, &re.pattern());
  EXPECT_EQ(ref1, "stable");
  EXPECT_EQ(ref2, "stable");
}
