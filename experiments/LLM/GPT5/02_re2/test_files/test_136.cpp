// File: ./TestProjects/re2/re2/tests/regexp_status_set_code_test_136.cc

#include "gtest/gtest.h"
#include "./TestProjects/re2/re2/regexp.h"

namespace re2 {

class RegexpStatusTest_136 : public ::testing::Test {};

TEST_F(RegexpStatusTest_136, DefaultIsSuccess_136) {
  RegexpStatus st;
  // Observable behavior via public API only.
  // Default-constructed status should indicate success.
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(st.code(), kRegexpSuccess);
}

TEST_F(RegexpStatusTest_136, SetCode_ChangesCode_136) {
  RegexpStatus st;
  // Choose a known non-success code from the public enum to observe change.
  st.set_code(kRegexpInternalError);
  EXPECT_EQ(st.code(), kRegexpInternalError);
  EXPECT_FALSE(st.ok());
}

TEST_F(RegexpStatusTest_136, SetCode_Idempotent_136) {
  RegexpStatus st;
  st.set_code(kRegexpInternalError);
  // Setting the same code again shouldn't change the observable state.
  st.set_code(kRegexpInternalError);
  EXPECT_EQ(st.code(), kRegexpInternalError);
  EXPECT_FALSE(st.ok());
}

TEST_F(RegexpStatusTest_136, SetCode_CanResetToSuccess_136) {
  RegexpStatus st;
  st.set_code(kRegexpInternalError);
  ASSERT_FALSE(st.ok());

  // Boundary/transition: recover by setting back to success.
  st.set_code(kRegexpSuccess);
  EXPECT_TRUE(st.ok());
  EXPECT_EQ(st.code(), kRegexpSuccess);
}

}  // namespace re2
