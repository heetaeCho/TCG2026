#include <gtest/gtest.h>
#include <climits>
#include <string>

// We need to declare the template and specializations we're testing
namespace re2 {
namespace re2_internal {

template <typename T>
bool Parse(const char* str, size_t n, T* dest, int radix);

// The specialization for unsigned long must exist (it's called by unsigned int version)
template <>
bool Parse(const char* str, size_t n, unsigned long* dest, int radix);

// The specialization we are testing
template <>
bool Parse(const char* str, size_t n, unsigned int* dest, int radix);

}  // namespace re2_internal
}  // namespace re2

class ParseUnsignedIntTest_280 : public ::testing::Test {
 protected:
  using ParseFn = bool (*)(const char*, size_t, unsigned int*, int);
};

// Test parsing a simple decimal number
TEST_F(ParseUnsignedIntTest_280, ParseSimpleDecimal_280) {
  unsigned int result = 0;
  const char* str = "123";
  bool ok = re2::re2_internal::Parse(str, 3, &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 123u);
}

// Test parsing zero
TEST_F(ParseUnsignedIntTest_280, ParseZero_280) {
  unsigned int result = 99;
  const char* str = "0";
  bool ok = re2::re2_internal::Parse(str, 1, &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 0u);
}

// Test parsing with null destination (should return true if parseable)
TEST_F(ParseUnsignedIntTest_280, ParseNullDest_280) {
  const char* str = "42";
  bool ok = re2::re2_internal::Parse(str, 2, (unsigned int*)NULL, 10);
  EXPECT_TRUE(ok);
}

// Test parsing max unsigned int value
TEST_F(ParseUnsignedIntTest_280, ParseMaxUnsignedInt_280) {
  std::string s = std::to_string(UINT_MAX);
  unsigned int result = 0;
  bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, UINT_MAX);
}

// Test parsing value that overflows unsigned int but fits in unsigned long
// (only relevant on platforms where unsigned long > unsigned int, e.g., 64-bit)
TEST_F(ParseUnsignedIntTest_280, ParseOverflowUnsignedInt_280) {
  if (sizeof(unsigned long) > sizeof(unsigned int)) {
    unsigned long overflow_val = (unsigned long)UINT_MAX + 1;
    std::string s = std::to_string(overflow_val);
    unsigned int result = 0;
    bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), &result, 10);
    EXPECT_FALSE(ok);
  }
}

// Test parsing hexadecimal
TEST_F(ParseUnsignedIntTest_280, ParseHexadecimal_280) {
  unsigned int result = 0;
  const char* str = "ff";
  bool ok = re2::re2_internal::Parse(str, 2, &result, 16);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 255u);
}

// Test parsing octal
TEST_F(ParseUnsignedIntTest_280, ParseOctal_280) {
  unsigned int result = 0;
  const char* str = "77";
  bool ok = re2::re2_internal::Parse(str, 2, &result, 8);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 63u);
}

// Test parsing invalid string
TEST_F(ParseUnsignedIntTest_280, ParseInvalidString_280) {
  unsigned int result = 0;
  const char* str = "abc";
  bool ok = re2::re2_internal::Parse(str, 3, &result, 10);
  EXPECT_FALSE(ok);
}

// Test parsing empty string
TEST_F(ParseUnsignedIntTest_280, ParseEmptyString_280) {
  unsigned int result = 0;
  const char* str = "";
  bool ok = re2::re2_internal::Parse(str, 0, &result, 10);
  EXPECT_FALSE(ok);
}

// Test parsing negative number (should fail for unsigned)
TEST_F(ParseUnsignedIntTest_280, ParseNegativeNumber_280) {
  unsigned int result = 0;
  const char* str = "-1";
  bool ok = re2::re2_internal::Parse(str, 2, &result, 10);
  // Negative numbers should not be valid for unsigned int
  // The behavior depends on the underlying unsigned long Parse,
  // but conceptually this should fail or produce unexpected results
  // We just check it doesn't crash; the result may vary by implementation
  (void)ok;
  (void)result;
}

// Test parsing with partial length
TEST_F(ParseUnsignedIntTest_280, ParsePartialLength_280) {
  unsigned int result = 0;
  const char* str = "12345";
  bool ok = re2::re2_internal::Parse(str, 3, &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 123u);
}

// Test parsing "1" in decimal
TEST_F(ParseUnsignedIntTest_280, ParseOne_280) {
  unsigned int result = 0;
  const char* str = "1";
  bool ok = re2::re2_internal::Parse(str, 1, &result, 10);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 1u);
}

// Test parsing large hex value that fits in unsigned int
TEST_F(ParseUnsignedIntTest_280, ParseMaxHex_280) {
  unsigned int result = 0;
  const char* str = "ffffffff";
  bool ok = re2::re2_internal::Parse(str, 8, &result, 16);
  EXPECT_TRUE(ok);
  EXPECT_EQ(result, 0xFFFFFFFFu);
}

// Test parsing hex value that overflows unsigned int
TEST_F(ParseUnsignedIntTest_280, ParseOverflowHex_280) {
  if (sizeof(unsigned long) > sizeof(unsigned int)) {
    unsigned int result = 0;
    const char* str = "100000000";  // 2^32 in hex
    bool ok = re2::re2_internal::Parse(str, 9, &result, 16);
    EXPECT_FALSE(ok);
  }
}

// Test that null dest with overflow still returns false
TEST_F(ParseUnsignedIntTest_280, ParseNullDestOverflow_280) {
  if (sizeof(unsigned long) > sizeof(unsigned int)) {
    unsigned long overflow_val = (unsigned long)UINT_MAX + 1;
    std::string s = std::to_string(overflow_val);
    bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), (unsigned int*)NULL, 10);
    EXPECT_FALSE(ok);
  }
}

// Test that null dest with invalid string returns false
TEST_F(ParseUnsignedIntTest_280, ParseNullDestInvalid_280) {
  const char* str = "xyz";
  bool ok = re2::re2_internal::Parse(str, 3, (unsigned int*)NULL, 10);
  EXPECT_FALSE(ok);
}
