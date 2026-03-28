// File: regexp_status_error_arg_test.cc

#include <gtest/gtest.h>
#include <string>
#include "re2/regexp.h"  // Adjust include path if needed

namespace re2 {

class RegexpStatusTest_140 : public ::testing::Test {
protected:
  RegexpStatus status_;
};

// Normal operation: set a non-empty argument and read it back via accessor.
TEST_F(RegexpStatusTest_140, SetAndGetNonEmpty_140) {
  std::string backing = "invalid escape at position 3";
  status_.set_error_arg(backing);
  EXPECT_EQ(status_.error_arg(), backing);
}

// Boundary: set an empty string and verify accessor returns empty.
TEST_F(RegexpStatusTest_140, SetEmptyString_140) {
  std::string empty;
  status_.set_error_arg(empty);
  EXPECT_TRUE(status_.error_arg().empty());
  EXPECT_EQ(status_.error_arg().size(), 0u);
}

// Normal operation: multiple updates should reflect the most recent value.
TEST_F(RegexpStatusTest_140, MultipleUpdatesReflectLatest_140) {
  std::string first = "first message";
  std::string second = "second message";
  status_.set_error_arg(first);
  EXPECT_EQ(status_.error_arg(), first);

  status_.set_error_arg(second);
  EXPECT_EQ(status_.error_arg(), second);
}

// Boundary: set from a string literal (lifetime managed by program), read back.
TEST_F(RegexpStatusTest_140, SetFromLiteral_140) {
  status_.set_error_arg("literal error arg");
  EXPECT_EQ(status_.error_arg(), absl::string_view("literal error arg"));
}

// Boundary / size stress: large input should be exposed fully via accessor.
TEST_F(RegexpStatusTest_140, LargeInput_140) {
  std::string big(100000, 'x');  // 100k chars
  status_.set_error_arg(big);
  EXPECT_EQ(status_.error_arg().size(), big.size());
  // Spot-check a couple positions without assuming internal storage.
  EXPECT_EQ(status_.error_arg().front(), 'x');
  EXPECT_EQ(status_.error_arg().back(), 'x');
}

// Const-correctness: accessor usable on const reference and returns same view.
TEST_F(RegexpStatusTest_140, ConstAccessor_140) {
  std::string msg = "const access check";
  status_.set_error_arg(msg);

  const RegexpStatus& cref = status_;
  EXPECT_EQ(cref.error_arg(), msg);
}

}  // namespace re2
