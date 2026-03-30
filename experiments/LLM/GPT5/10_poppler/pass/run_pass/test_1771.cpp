// TEST_ID: 1771
#include <gtest/gtest.h>

#include "Object.h"

// There is no public header for isNatural() (it is a file-scope static in StructElement.cc).
// To test the real implementation as a black box, we include the .cc directly into this TU.
#include "StructElement.cc"

namespace {

TEST(IsNaturalTest_1771, PositiveIntReturnsTrue_1771)
{
  Object v(1);
  EXPECT_TRUE(isNatural(&v));
}

TEST(IsNaturalTest_1771, ZeroIntReturnsFalse_1771)
{
  Object v(0);
  EXPECT_FALSE(isNatural(&v));
}

TEST(IsNaturalTest_1771, NegativeIntReturnsFalse_1771)
{
  Object v(-1);
  EXPECT_FALSE(isNatural(&v));
}

TEST(IsNaturalTest_1771, PositiveInt64ReturnsTrue_1771)
{
  Object v(static_cast<long long>(1));
  EXPECT_TRUE(isNatural(&v));
}

TEST(IsNaturalTest_1771, ZeroInt64ReturnsFalse_1771)
{
  Object v(static_cast<long long>(0));
  EXPECT_FALSE(isNatural(&v));
}

TEST(IsNaturalTest_1771, NegativeInt64ReturnsFalse_1771)
{
  Object v(static_cast<long long>(-1));
  EXPECT_FALSE(isNatural(&v));
}

TEST(IsNaturalTest_1771, LargePositiveInt64ReturnsTrue_1771)
{
  Object v(static_cast<long long>(9223372036854775807LL)); // LLONG_MAX
  EXPECT_TRUE(isNatural(&v));
}

TEST(IsNaturalTest_1771, NonIntegerTypesReturnFalse_1771)
{
  Object btrue(true);
  Object bfalse(false);
  Object realv(1.0);
  Object strv(std::string("123"));
  Object nullv = Object::null();
  Object errv = Object::error();
  Object eofv = Object::eof();

  EXPECT_FALSE(isNatural(&btrue));
  EXPECT_FALSE(isNatural(&bfalse));
  EXPECT_FALSE(isNatural(&realv));
  EXPECT_FALSE(isNatural(&strv));
  EXPECT_FALSE(isNatural(&nullv));
  EXPECT_FALSE(isNatural(&errv));
  EXPECT_FALSE(isNatural(&eofv));
}

TEST(IsNaturalDeathTest_1771, NullPointerDies_1771)
{
  // Exceptional/error case: passing nullptr is observable as a crash (if supported).
  ASSERT_DEATH_IF_SUPPORTED({ (void)isNatural(nullptr); }, "");
}

} // namespace