// File: re2_parse_optional_test.cc

#include <string>
#include "gtest/gtest.h"
#include "absl/types/optional.h"

// Include the header under test (as given).
// Adjust include path if needed in your project layout.
#include "re2/re2.h"

namespace re2 {
namespace re2_internal {

// ---- Test double & call tracking for the underlying overload ----

// A simple dummy type parsed by our test double.
struct Dummy {
  int value = 0;
};

// Global tracking to verify external interactions.
static bool g_parse_called = false;
static size_t g_last_n = 0;
static std::string g_last_str;

// Test double for the underlying overload that the function under test calls.
// NOTE: We do not re-implement logic of the function under test; we only
// supply a collaborator with simple, observable behavior to control outcomes.
bool Parse(const char* str, size_t n, Dummy* out) {
  g_parse_called = true;
  g_last_n = n;
  g_last_str = (str ? std::string(str, n) : std::string());

  // "OK" (length 2) => parse success and set a known value.
  if (str != nullptr && n == 2 && std::string(str, n) == "OK") {
    if (out) out->value = 123;
    return true;
  }
  // "NO" (length 2) => parse failure.
  if (str != nullptr && n == 2 && std::string(str, n) == "NO") {
    return false;
  }

  // Any other input => failure by default in this collaborator.
  return false;
}

class Re2InternalParseOptionalTest_40 : public ::testing::Test {
protected:
  void SetUp() override {
    // Reset tracking before each test.
    g_parse_called = false;
    g_last_n = 0;
    g_last_str.clear();
  }
};

//
// Tests
//

// 1) Null input resets optional (if non-null) and returns true.
// Also verify the underlying overload is NOT called.
TEST_F(Re2InternalParseOptionalTest_40, NullStr_ResetsDestAndReturnsTrue_40) {
  absl::optional<Dummy> dest;
  dest.emplace();      // ensure it currently has a value
  EXPECT_TRUE(dest.has_value());

  const char* str = nullptr;
  const size_t n = 0;  // n is irrelevant when str == nullptr

  bool ok = Parse(str, n, &dest);  // function under test
  EXPECT_TRUE(ok);
  EXPECT_FALSE(dest.has_value());  // observable: dest reset
  EXPECT_FALSE(g_parse_called);    // external interaction: not called
}

// 2) Null input with null destination returns true and does not call underlying.
TEST_F(Re2InternalParseOptionalTest_40, NullStr_NullDest_ReturnsTrue_NoCall_40) {
  const char* str = nullptr;
  const size_t n = 0;

  bool ok = Parse(str, n, static_cast<absl::optional<Dummy>*>(nullptr));
  EXPECT_TRUE(ok);
  EXPECT_FALSE(g_parse_called);  // external interaction: not called
}

// 3) Successful parse sets the optional and returns true.
// Also verify length forwarding to the underlying overload.
TEST_F(Re2InternalParseOptionalTest_40, UnderlyingSuccess_SetsDestAndReturnsTrue_40) {
  absl::optional<Dummy> dest;  // empty to start
  const char* str = "OK";      // our test double treats "OK" (n=2) as success
  const size_t n = 2;

  bool ok = Parse(str, n, &dest);
  EXPECT_TRUE(ok);
  ASSERT_TRUE(dest.has_value());
  EXPECT_EQ(dest->value, 123);        // set by the collaborator
  EXPECT_TRUE(g_parse_called);         // collaborator should be invoked
  EXPECT_EQ(g_last_n, n);              // verify length was forwarded
  EXPECT_EQ(g_last_str, std::string("OK", 2));  // verify bytes forwarded
}

// 4) Failed parse returns false and leaves existing dest unchanged.
TEST_F(Re2InternalParseOptionalTest_40, UnderlyingFailure_DestUnchanged_ReturnsFalse_40) {
  absl::optional<Dummy> dest;
  dest.emplace();
  dest->value = 999;  // sentinel value to detect unintended modification

  const char* str = "NO";  // our test double treats "NO" (n=2) as failure
  const size_t n = 2;

  bool ok = Parse(str, n, &dest);
  EXPECT_FALSE(ok);
  EXPECT_TRUE(dest.has_value());   // should remain engaged
  EXPECT_EQ(dest->value, 999);     // should remain unchanged
  EXPECT_TRUE(g_parse_called);     // collaborator was invoked
}

// 5) Successful parse with null destination pointer still returns true
// (we can't observe writes, but we verify it doesn't crash and signals success).
TEST_F(Re2InternalParseOptionalTest_40, UnderlyingSuccess_NullDest_ReturnsTrue_40) {
  const char* str = "OK";
  const size_t n = 2;

  bool ok = Parse(str, n, static_cast<absl::optional<Dummy>*>(nullptr));
  EXPECT_TRUE(ok);
  EXPECT_TRUE(g_parse_called);
  EXPECT_EQ(g_last_n, n);
  EXPECT_EQ(g_last_str, std::string("OK", 2));
}

// 6) Boundary: Large n is forwarded as-is to the collaborator.
TEST_F(Re2InternalParseOptionalTest_40, LargeN_IsForwardedToUnderlying_40) {
  absl::optional<Dummy> dest;

  // We won't match "OK" or "NO", so parse will fail, but we can still
  // observe that 'n' is forwarded correctly.
  const char* str = "XXXXXXXXXXXXXXXX";
  const size_t n = 16;  // treat as a "large" length for this test context

  bool ok = Parse(str, n, &dest);
  EXPECT_FALSE(ok);
  EXPECT_TRUE(g_parse_called);
  EXPECT_EQ(g_last_n, n);
  EXPECT_EQ(g_last_str, std::string(str, n));
}

}  // namespace re2_internal
}  // namespace re2
