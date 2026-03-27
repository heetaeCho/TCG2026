// File: parse_unsigned_int_test_280.cc
#include <gtest/gtest.h>
#include <limits>
#include <string>
#include <cstddef>
#include <cstdint>
#include <sstream>

namespace re2 { namespace re2_internal {
// Declaration for the tested specialization.
// (Definition is provided in the library under test and linked in.)
bool Parse(const char* str, size_t n, unsigned int* dest, int radix);
}}

// ---------- Normal operation ----------

TEST(ParseUnsignedIntTest_280, ParsesDecimalSimple_280) {
  unsigned int out = 0;
  const std::string s = "12345";
  const bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), &out, /*radix=*/10);
  ASSERT_TRUE(ok);
  EXPECT_EQ(out, 12345u);
}

TEST(ParseUnsignedIntTest_280, ParsesZero_280) {
  unsigned int out = 999u;
  const std::string s = "0";
  const bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), &out, /*radix=*/10);
  ASSERT_TRUE(ok);
  EXPECT_EQ(out, 0u);
}

TEST(ParseUnsignedIntTest_280, ParsesHexLowercase_280) {
  unsigned int out = 0;
  const std::string s = "ff"; // 255 in hex
  const bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), &out, /*radix=*/16);
  ASSERT_TRUE(ok);
  EXPECT_EQ(out, 255u);
}

// ---------- Boundary & length handling ----------

TEST(ParseUnsignedIntTest_280, UsesLengthParameter_ParsesPrefix_280) {
  unsigned int out = 0;
  const std::string s = "12345"; // we will only pass first 3 chars via n
  const size_t n = 3;            // effectively "123"
  const bool ok = re2::re2_internal::Parse(s.c_str(), n, &out, /*radix=*/10);
  ASSERT_TRUE(ok);
  EXPECT_EQ(out, 123u);
}

// ---------- Exceptional / error cases ----------

TEST(ParseUnsignedIntTest_280, ReturnsFalseOnInvalid_280) {
  unsigned int out = 777u;
  const std::string s = "xyz";
  const bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), &out, /*radix=*/10);
  EXPECT_FALSE(ok);
  // When parsing fails, output value is unspecified; we only assert the return.
}

TEST(ParseUnsignedIntTest_280, ReturnsFalseOnOverflowDecimal_280) {
  // Build (max_uint + 1) in base-10 to ensure out-of-range for unsigned int.
  const unsigned long long overflow_val =
      static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) + 1ull;
  const std::string s = std::to_string(overflow_val);

  unsigned int out = 0;
  const bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), &out, /*radix=*/10);
  EXPECT_FALSE(ok);  // Should report out-of-range
}

// ---------- Interactions with nullptr destination ----------

TEST(ParseUnsignedIntTest_280, ReturnsTrueWithNullDest_280) {
  const std::string s = "1234";
  const bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), /*dest=*/nullptr, /*radix=*/10);
  EXPECT_TRUE(ok);  // Valid parse; function should succeed even when dest == nullptr
}

TEST(ParseUnsignedIntTest_280, ReturnsFalseOnOverflowWithNullDest_280) {
  const unsigned long long overflow_val =
      static_cast<unsigned long long>(std::numeric_limits<unsigned int>::max()) + 1ull;
  const std::string s = std::to_string(overflow_val);

  const bool ok = re2::re2_internal::Parse(s.c_str(), s.size(), /*dest=*/nullptr, /*radix=*/10);
  EXPECT_FALSE(ok); // Out-of-range must still be reported even if dest == nullptr
}
