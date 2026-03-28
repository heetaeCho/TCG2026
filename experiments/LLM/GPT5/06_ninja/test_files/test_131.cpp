// File: util_error_test_131.cc

#include <gtest/gtest.h>

#include <cstdarg>
#include <cstdio>
#include <string>
#include <vector>

// Forward declaration of the function under test.
// This matches the interface from util.cc.
void Error(const char* msg, ...);

// -----------------------------------------------------------------------------
// Test double for the va_list-based overload
// -----------------------------------------------------------------------------

namespace {

// Global state to observe calls to the va_list-based Error overload.
int g_error_call_count = 0;
std::string g_last_formatted_message;

// Test-only definition of the va_list-based collaborator that the variadic
// Error(...) is expected to call. We do NOT reimplement the logic of the
// variadic overload; we only implement this collaborator to observe how
// arguments are forwarded.
void Error(const char* msg, va_list ap) {
  ++g_error_call_count;

  // Format the message using the provided va_list, so we can verify that
  // all arguments were forwarded correctly from the variadic Error(...).
  va_list ap_copy;
  va_copy(ap_copy, ap);
  int len = std::vsnprintf(nullptr, 0, msg, ap_copy);
  va_end(ap_copy);

  if (len < 0) {
    g_last_formatted_message.clear();
    return;
  }

  std::vector<char> buffer(static_cast<std::size_t>(len) + 1);
  std::vsnprintf(buffer.data(), buffer.size(), msg, ap);
  g_last_formatted_message.assign(buffer.data(), static_cast<std::size_t>(len));
}

}  // namespace

// -----------------------------------------------------------------------------
// Test fixture
// -----------------------------------------------------------------------------

class ErrorTest_131 : public ::testing::Test {
 protected:
  void SetUp() override {
    g_error_call_count = 0;
    g_last_formatted_message.clear();
  }
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// Verifies that calling Error with only a format string (no extra arguments)
// results in exactly one call to the va_list-based overload and that the
// format string is forwarded correctly.
TEST_F(ErrorTest_131, ForwardsFormatStringWithoutArgs_131) {
  Error("simple message");

  EXPECT_EQ(1, g_error_call_count);
  EXPECT_EQ("simple message", g_last_formatted_message);
}

// Verifies that calling Error with an integer and string argument forwards all
// arguments correctly to the va_list-based overload (observable via formatting).
TEST_F(ErrorTest_131, ForwardsIntegerAndStringArgs_131) {
  Error("value=%d, name=%s", 42, "ninja");

  EXPECT_EQ(1, g_error_call_count);
  EXPECT_EQ("value=42, name=ninja", g_last_formatted_message);
}

// Verifies behavior across multiple calls: the collaborator is invoked on each
// call, and the last formatted message reflects the last invocation.
TEST_F(ErrorTest_131, MultipleCallsUpdateCallCountAndLastMessage_131) {
  Error("first call");
  Error("second %d", 7);

  EXPECT_EQ(2, g_error_call_count);
  EXPECT_EQ("second 7", g_last_formatted_message);
}

// Verifies that Error correctly forwards a longer formatted message with
// multiple arguments (boundary-ish case with longer string content).
TEST_F(ErrorTest_131, ForwardsLongFormattedMessage_131) {
  const char* long_prefix =
      "This is a somewhat longer error message with details: code=%d, "
      "user=%s, path=%s";

  Error(long_prefix, 404, "tester", "/some/very/long/path/to/file.txt");

  EXPECT_EQ(1, g_error_call_count);
  EXPECT_EQ(
      "This is a somewhat longer error message with details: code=404, "
      "user=tester, path=/some/very/long/path/to/file.txt",
      g_last_formatted_message);
}
