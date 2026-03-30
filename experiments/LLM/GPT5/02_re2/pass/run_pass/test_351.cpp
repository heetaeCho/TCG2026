// File: re2_regexpstatus_text_test_351.cc

#include <string>
#include "gtest/gtest.h"
#include "re2/regexp.h"

using re2::RegexpStatus;

class RegexpStatusTest_351 : public ::testing::Test {};

TEST_F(RegexpStatusTest_351, Text_NoErrorArg_ReturnsCodeText_351) {
  RegexpStatus st;  // default-constructed
  // Observable contract: when error_arg is empty, Text() == CodeText(code()).
  const std::string expected = RegexpStatus::CodeText(st.code());
  EXPECT_EQ(st.Text(), expected);
}

TEST_F(RegexpStatusTest_351, Text_WithErrorArg_AppendsColonAndArg_351) {
  RegexpStatus st;  // keep default code()
  st.set_error_arg("bad pattern");

  const std::string expected =
      RegexpStatus::CodeText(st.code()) + ": " + std::string(st.error_arg());
  EXPECT_EQ(st.Text(), expected);
}

TEST_F(RegexpStatusTest_351, Text_WithEmptyStringView_TreatedAsEmpty_351) {
  RegexpStatus st;
  // Explicitly set an empty error_arg; should behave like no error_arg.
  st.set_error_arg(absl::string_view());  // empty

  const std::string expected = RegexpStatus::CodeText(st.code());
  EXPECT_EQ(st.Text(), expected);
}

TEST_F(RegexpStatusTest_351, Text_WithErrorArgContainingColon_KeepsSeparator_351) {
  RegexpStatus st;
  st.set_error_arg(":details");

  const std::string expected =
      RegexpStatus::CodeText(st.code()) + ": " + std::string(st.error_arg());
  EXPECT_EQ(st.Text(), expected);
}

TEST_F(RegexpStatusTest_351, Copy_CopiesFields_TextMatchesSource_351) {
  RegexpStatus src;
  src.set_error_arg("copy me");

  RegexpStatus dst;
  dst.Copy(src);

  // Observable behavior: after Copy, the derived Text() values should match.
  EXPECT_EQ(dst.Text(), src.Text());
}

TEST_F(RegexpStatusTest_351, Text_LongErrorArg_AppendsVerbatim_351) {
  RegexpStatus st;
  const std::string long_arg(1024, 'x');  // large but simple payload
  st.set_error_arg(long_arg);

  const std::string expected =
      RegexpStatus::CodeText(st.code()) + ": " + long_arg;
  EXPECT_EQ(st.Text(), expected);
}
