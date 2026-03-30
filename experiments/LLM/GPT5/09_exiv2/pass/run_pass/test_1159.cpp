// File: test_types_parsefloat_1159.cpp

#include <gtest/gtest.h>

#include <cmath>
#include <string>

// Exiv2 header expected to declare Exiv2::parseFloat.
// Adjust include if your project uses a different include path.
#include "types.hpp"

namespace {

class ParseFloatTest_1159 : public ::testing::Test {
 protected:
  static float Call(const std::string& s, bool& ok) { return Exiv2::parseFloat(s, ok); }
};

TEST_F(ParseFloatTest_1159, ParsesSimpleFloatString_1159) {
  bool ok = false;
  const float v = Call("3.5", ok);

  EXPECT_TRUE(ok);
  EXPECT_FLOAT_EQ(v, 3.5f);
}

TEST_F(ParseFloatTest_1159, ParsesScientificNotationFloat_1159) {
  bool ok = false;
  const float v = Call("-1.25e2", ok);

  EXPECT_TRUE(ok);
  EXPECT_FLOAT_EQ(v, -125.0f);
}

TEST_F(ParseFloatTest_1159, ParsesRationalStringToFloat_1159) {
  bool ok = false;
  const float v = Call("1/2", ok);

  EXPECT_TRUE(ok);
  EXPECT_NEAR(v, 0.5f, 1e-6f);
}

TEST_F(ParseFloatTest_1159, RationalWithZeroDenominatorFailsAndReturnsZero_1159) {
  bool ok = true;  // start true to ensure it changes on failure
  const float v = Call("1/0", ok);

  EXPECT_FALSE(ok);
  EXPECT_FLOAT_EQ(v, 0.0f);
}

TEST_F(ParseFloatTest_1159, ParsesBooleanTrueAsOne_1159) {
  bool ok = false;
  const float v = Call("true", ok);

  EXPECT_TRUE(ok);
  EXPECT_FLOAT_EQ(v, 1.0f);
}

TEST_F(ParseFloatTest_1159, ParsesBooleanFalseAsZero_1159) {
  bool ok = false;
  const float v = Call("false", ok);

  EXPECT_TRUE(ok);
  EXPECT_FLOAT_EQ(v, 0.0f);
}

TEST_F(ParseFloatTest_1159, InvalidStringSetsOkFalse_1159) {
  bool ok = true;  // start true to ensure it changes on failure
  const float v = Call("not_a_number", ok);

  EXPECT_FALSE(ok);
  // Return value on failure is not asserted (black-box behavior), but it should be a float.
  (void)v;
}

TEST_F(ParseFloatTest_1159, EmptyStringSetsOkFalse_1159) {
  bool ok = true;  // start true to ensure it changes on failure
  const float v = Call("", ok);

  EXPECT_FALSE(ok);
  (void)v;
}

}  // namespace