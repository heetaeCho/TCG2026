// File: test_canonEv_966.cpp

#include <gtest/gtest.h>

#include <cstdint>

namespace Exiv2 {
namespace Internal {
// Function under test (implemented in the production codebase).
float canonEv(int64_t val);
}  // namespace Internal
}  // namespace Exiv2

namespace {

class CanonEvTest_966 : public ::testing::Test {};

TEST_F(CanonEvTest_966, ZeroReturnsZero_966) {
  EXPECT_FLOAT_EQ(Exiv2::Internal::canonEv(0), 0.0f);
}

TEST_F(CanonEvTest_966, PositiveNoRemainderIsDivBy32_966) {
  // 64 is divisible by 32 -> expected 2.0
  EXPECT_FLOAT_EQ(Exiv2::Internal::canonEv(64), 2.0f);
}

TEST_F(CanonEvTest_966, PositiveWithSimpleRemainder_966) {
  // 65 -> expected (64 + 1) / 32 = 2.03125
  EXPECT_FLOAT_EQ(Exiv2::Internal::canonEv(65), 2.03125f);
}

TEST_F(CanonEvTest_966, NegativeMirrorsPositive_966) {
  // -65 -> expected -2.03125
  EXPECT_FLOAT_EQ(Exiv2::Internal::canonEv(-65), -2.03125f);
}

TEST_F(CanonEvTest_966, SpecialRemainder0x0cIsOneThird_966) {
  // Choose value with remainder 0x0c (12): 64 + 12 = 76
  // Expected: (64 + (32/3)) / 32 = 2 + 1/3 = 2.3333333...
  EXPECT_NEAR(Exiv2::Internal::canonEv(76), 2.3333333f, 1e-6f);
}

TEST_F(CanonEvTest_966, SpecialRemainder0x14IsTwoThirds_966) {
  // Choose value with remainder 0x14 (20): 64 + 20 = 84
  // Expected: (64 + (64/3)) / 32 = 2 + 2/3 = 2.6666667...
  EXPECT_NEAR(Exiv2::Internal::canonEv(84), 2.6666667f, 1e-6f);
}

TEST_F(CanonEvTest_966, SpecialSigmaCaseVal160AndRemainder0x08_966) {
  // Use input 168 -> remainder is 8, base becomes 160.
  // Expected: (160 + (30/3)) / 32 = (160 + 10) / 32 = 5.3125
  EXPECT_FLOAT_EQ(Exiv2::Internal::canonEv(168), 5.3125f);
}

TEST_F(CanonEvTest_966, BoundaryRemainderMax31_966) {
  // 63 -> remainder 31, base 32 -> expected (32 + 31)/32 = 1.96875
  EXPECT_FLOAT_EQ(Exiv2::Internal::canonEv(63), 1.96875f);
}

TEST_F(CanonEvTest_966, LargerExactMultipleOf32_966) {
  // 1,048,576 is divisible by 32 -> expected 32,768.0 (exactly representable in float)
  EXPECT_FLOAT_EQ(Exiv2::Internal::canonEv(1048576), 32768.0f);
}

}  // namespace