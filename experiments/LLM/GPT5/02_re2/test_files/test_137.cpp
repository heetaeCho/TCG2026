// File: ./TestProjects/re2/tests/regexp_set_error_arg_test.cc
#include "gtest/gtest.h"
#include "re2/regexp.h"
#include "absl/strings/string_view.h"

namespace {

using re2::RegexpStatus;

class RegexpStatusTest_137 : public ::testing::Test {
protected:
  RegexpStatus s_;
};

// Normal operation: setting a typical value via string literal.
TEST_F(RegexpStatusTest_137, SetErrorArgStoresValue_137) {
  const char* msg = "invalid repetition";
  s_.set_error_arg(msg);

  absl::string_view got = s_.error_arg();
  EXPECT_EQ(got, absl::string_view(msg));
}

// Boundary: empty string should be preserved exactly.
TEST_F(RegexpStatusTest_137, SetErrorArgEmpty_137) {
  absl::string_view empty = "";
  s_.set_error_arg(empty);

  EXPECT_TRUE(s_.error_arg().empty());
  EXPECT_EQ(s_.error_arg().size(), 0u);
}

// Normal operation: setting from a std::string that stays in scope.
TEST_F(RegexpStatusTest_137, SetErrorArgFromStdString_137) {
  std::string buf = "unterminated group";
  s_.set_error_arg(buf);

  EXPECT_EQ(s_.error_arg(), absl::string_view(buf));
}

// Unicode / non-ASCII input should be accepted and preserved byte-for-byte.
TEST_F(RegexpStatusTest_137, SetErrorArgUnicode_137) {
  // "잘못된 유니코드" (Korean for "invalid Unicode")
  std::string utf8 = u8"잘못된 유니코드";
  s_.set_error_arg(utf8);

  absl::string_view got = s_.error_arg();
  EXPECT_EQ(got.size(), utf8.size());
  EXPECT_EQ(got, absl::string_view(utf8));
}

// Contract check: setting error_arg should not alter the status code value.
TEST_F(RegexpStatusTest_137, SetErrorArgDoesNotChangeCode_137) {
  // Capture initial observable code value via the public accessor.
  auto before = s_.code();

  s_.set_error_arg("some arg");
  auto after = s_.code();

  EXPECT_EQ(after, before);
}

}  // namespace
