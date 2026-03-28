// File: regexp_status_copy_test_352.cc
#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"

namespace re2 {

class RegexpStatusTest_352 : public ::testing::Test {
 protected:
  RegexpStatus src_;
  RegexpStatus dst_;
};

// Verifies that Copy transfers observable fields from source to destination.
// We set distinct error_arg() values first, then ensure dst matches src after Copy.
TEST_F(RegexpStatusTest_352, Copy_OverwritesDestinationFields_352) {
  src_.set_error_arg("source-err");
  dst_.set_error_arg("dest-err-different");

  // Precondition: they differ
  EXPECT_NE(dst_.error_arg(), src_.error_arg());

  dst_.Copy(src_);

  // Observable behaviors: error_arg() must match; code() must match.
  EXPECT_EQ(dst_.error_arg(), src_.error_arg());
  EXPECT_EQ(dst_.code(), src_.code());
}

// Self-copy should be safe and leave observable state unchanged.
TEST_F(RegexpStatusTest_352, Copy_SelfCopyIsNoop_352) {
  src_.set_error_arg("self-copy");

  const auto before_arg = src_.error_arg();
  const auto before_code = src_.code();

  src_.Copy(src_);

  EXPECT_EQ(src_.error_arg(), before_arg);
  EXPECT_EQ(src_.code(), before_code);
}

// Multiple copies reflect the latest source observable state.
TEST_F(RegexpStatusTest_352, Copy_MultipleCallsReflectLatestSource_352) {
  dst_.set_error_arg("initial-dst");

  src_.set_error_arg("first");
  dst_.Copy(src_);
  EXPECT_EQ(dst_.error_arg(), absl::string_view("first"));
  EXPECT_EQ(dst_.code(), src_.code());

  src_.set_error_arg("second");
  dst_.Copy(src_);
  EXPECT_EQ(dst_.error_arg(), absl::string_view("second"));
  EXPECT_EQ(dst_.code(), src_.code());
}

// Boundary cases for error_arg(): empty and strings with embedded NULs should copy correctly.
TEST_F(RegexpStatusTest_352, Copy_HandlesEmptyAndEmbeddedNull_352) {
  // Empty
  src_.set_error_arg("");
  dst_.set_error_arg("non-empty-before");
  dst_.Copy(src_);
  EXPECT_TRUE(dst_.error_arg().empty());
  EXPECT_EQ(dst_.code(), src_.code());

  // Embedded NUL
  const std::string with_nul = std::string("a\0b\0c", 5);  // 'a',0,'b',0,'c'
  src_.set_error_arg(with_nul);
  dst_.set_error_arg("other");
  dst_.Copy(src_);

  absl::string_view copied = dst_.error_arg();
  EXPECT_EQ(copied.size(), with_nul.size());
  // Compare byte-wise equality using std::string constructed from the view.
  EXPECT_EQ(std::string(copied.data(), copied.size()), with_nul);
  EXPECT_EQ(dst_.code(), src_.code());
}

}  // namespace re2
