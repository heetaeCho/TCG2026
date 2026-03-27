// File: pcre_error_test_174.cc

#include "gtest/gtest.h"
#include "TestProjects/re2/util/pcre.h"

using re2::PCRE;

// Test suite focused solely on the observable behavior of PCRE::error().
// We do NOT inspect or rely on any private state and treat implementation as a black box.

class PCREErrorTest_174 : public ::testing::Test {};

// [Normal operation] A clearly valid pattern should typically yield an empty (no-error) string.
// We do not assume any specific internal details beyond the observable result.
TEST_F(PCREErrorTest_174, ValidPattern_HasEmptyError_174) {
  PCRE re_valid("a");  // a simple, commonly valid pattern
  const std::string& err = re_valid.error();
  // Do not assert exact message contents—only observable emptiness.
  EXPECT_TRUE(err.empty());
}

// [Error case] A clearly invalid pattern should typically yield a non-empty error string.
// We only check that an error is reported; we do NOT assert any specific message text.
TEST_F(PCREErrorTest_174, InvalidPattern_HasNonEmptyError_174) {
  PCRE re_invalid("(");  // unbalanced parenthesis is commonly invalid
  const std::string& err = re_invalid.error();
  EXPECT_FALSE(err.empty());
}

// [Independence] Errors from separate instances should be independent and reflect the
// result of each instance's own construction, without cross-contamination.
TEST_F(PCREErrorTest_174, MultipleInstances_KeepIndependentErrors_174) {
  PCRE re_valid("a");
  PCRE re_invalid("(");

  const std::string& err_valid = re_valid.error();
  const std::string& err_invalid = re_invalid.error();

  EXPECT_TRUE(err_valid.empty());
  EXPECT_FALSE(err_invalid.empty());
}

// [Stability of returned reference] Calling error() multiple times should return a
// reference to the same string object (by observable address comparison). We do not
// assume anything about how that string is stored internally.
TEST_F(PCREErrorTest_174, ErrorReference_StableAcrossCalls_174) {
  PCRE re("(");  // invalid to ensure the string is non-empty (observable)
  const std::string& first = re.error();
  const std::string& second = re.error();

  // Compare addresses of the referenced strings to ensure stability.
  EXPECT_EQ(&first, &second);
}
