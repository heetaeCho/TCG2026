#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Include the header under test
#include "yaml-cpp/node/impl.h"

namespace {

// Simple non-streamable type (no operator<< overload)
struct NonStreamable_571 {
  int v{};
};

// Streamable type (has operator<< overload)
struct Streamable_571 {
  int v{};
};

std::ostream& operator<<(std::ostream& os, const Streamable_571& s) {
  os << "Streamable_571(" << s.v << ")";
  return os;
}

}  // namespace

// TEST_ID is 571
class KeyToStringTest_571 : public ::testing::Test {};

TEST_F(KeyToStringTest_571, IntKeyConvertsToString_571) {
  const int key = 12345;
  const std::string out = YAML::key_to_string(key);
  EXPECT_EQ(out, "12345");
}

TEST_F(KeyToStringTest_571, StringKeyReturnsSameContent_571) {
  const std::string key = "abcXYZ";
  const std::string out = YAML::key_to_string(key);
  EXPECT_EQ(out, "abcXYZ");
}

TEST_F(KeyToStringTest_571, CStrKeyConvertsToString_571) {
  const char* key = "hello";
  const std::string out = YAML::key_to_string(key);
  EXPECT_EQ(out, "hello");
}

TEST_F(KeyToStringTest_571, BoolKeyUsesStreamFormatting_571) {
  // Default iostream formatting for bool without boolalpha is "0"/"1".
  const bool key_true = true;
  const bool key_false = false;

  EXPECT_EQ(YAML::key_to_string(key_true), "1");
  EXPECT_EQ(YAML::key_to_string(key_false), "0");
}

TEST_F(KeyToStringTest_571, StreamableCustomTypeUsesOperatorInsertion_571) {
  const Streamable_571 key{7};
  const std::string out = YAML::key_to_string(key);
  EXPECT_EQ(out, "Streamable_571(7)");
}

TEST_F(KeyToStringTest_571, EmptyStringBoundaryCase_571) {
  const std::string key;
  const std::string out = YAML::key_to_string(key);
  EXPECT_TRUE(out.empty());
}

TEST_F(KeyToStringTest_571, LargeNumberBoundaryCase_571) {
  // Use a large 64-bit value to ensure no truncation/formatting surprises.
  const long long key = 9223372036854775807LL;
  const std::string out = YAML::key_to_string(key);
  EXPECT_EQ(out, "9223372036854775807");
}

// Exceptional/error case (observable): compilation must fail for non-streamable types.
// This is a "negative" compile-time test; keep it as a non-buildable snippet behind #if 0.
// It documents expected usage constraints without inferring internals.
TEST_F(KeyToStringTest_571, NonStreamableTypeIsNotSupported_571) {
#if 0
  NonStreamable_571 key{1};
  // Expected: does not compile because NonStreamable_571 is not stream-insertable.
  auto out = YAML::key_to_string(key);
  (void)out;
#endif
  SUCCEED();
}