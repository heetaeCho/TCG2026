// File: regexp_status_code_test_139.cc

#include <gtest/gtest.h>
#include "re2/regexp.h"

namespace re2 {

class RegexpStatusTest_139 : public ::testing::Test {};

// Verifies that code() reflects whatever value was most recently assigned via set_code().
TEST_F(RegexpStatusTest_139, CodeReflectsSetValue_139) {
  RegexpStatus s;

  // Use arbitrary enum values via static_cast without assuming specific enumerators.
  RegexpStatusCode v1 = static_cast<RegexpStatusCode>(5);
  RegexpStatusCode v2 = static_cast<RegexpStatusCode>(7);

  s.set_code(v1);
  EXPECT_EQ(s.code(), v1);

  s.set_code(v2);
  EXPECT_EQ(s.code(), v2);
}

// Setting code multiple times should result in code() returning the last value set.
TEST_F(RegexpStatusTest_139, MultipleSetCode_LastWins_139) {
  RegexpStatus s;

  s.set_code(static_cast<RegexpStatusCode>(1));
  s.set_code(static_cast<RegexpStatusCode>(2));
  s.set_code(static_cast<RegexpStatusCode>(3));

  EXPECT_EQ(s.code(), static_cast<RegexpStatusCode>(3));
}

// code() must be callable on a const instance (const-correct accessor).
TEST_F(RegexpStatusTest_139, CodeIsConstCorrect_139) {
  RegexpStatus s;
  s.set_code(static_cast<RegexpStatusCode>(42));

  const RegexpStatus& cs = s;  // bind to const
  EXPECT_EQ(cs.code(), static_cast<RegexpStatusCode>(42));
}

// Independent instances should not affect each other’s code() values.
TEST_F(RegexpStatusTest_139, IndependentInstances_139) {
  RegexpStatus a;
  RegexpStatus b;

  a.set_code(static_cast<RegexpStatusCode>(10));
  b.set_code(static_cast<RegexpStatusCode>(20));

  EXPECT_EQ(a.code(), static_cast<RegexpStatusCode>(10));
  EXPECT_EQ(b.code(), static_cast<RegexpStatusCode>(20));
}

}  // namespace re2
