// File: test_datevalue_2172.cpp
#include <gtest/gtest.h>

#include <cstdint>
#include <limits>
#include <sstream>
#include <vector>

#include <exiv2/value.hpp>

namespace {

// NOTE: This test suite treats Exiv2::DateValue as a black box and only verifies
// observable behavior through its public interface.

class DateValueTest_2172 : public ::testing::Test {};

TEST_F(DateValueTest_2172, DefaultConstructor_HasDateTypeId_2172) {
  Exiv2::DateValue dv;

  // Observable base-class behavior: type id should reflect DateValue's TypeId.
  EXPECT_EQ(dv.typeId(), Exiv2::date);

  // ok() is part of the public Value interface; it should be a valid boolean.
  // We don't assume more than that it is callable and returns consistently.
  EXPECT_TRUE(dv.ok());
}

TEST_F(DateValueTest_2172, YmdConstructor_StoresGivenFields_2172) {
  const int32_t year = 2026;
  const int32_t month = 2;
  const int32_t day = 11;

  Exiv2::DateValue dv(year, month, day);

  EXPECT_EQ(dv.typeId(), Exiv2::date);

  const Exiv2::DateValue::Date& d = dv.getDate();
  EXPECT_EQ(d.year, year);
  EXPECT_EQ(d.month, month);
  EXPECT_EQ(d.day, day);
}

TEST_F(DateValueTest_2172, YmdConstructor_AllowsBoundaryInt32Values_2172) {
  const int32_t year = std::numeric_limits<int32_t>::min();
  const int32_t month = std::numeric_limits<int32_t>::max();
  const int32_t day = 0;

  Exiv2::DateValue dv(year, month, day);

  const Exiv2::DateValue::Date& d = dv.getDate();
  EXPECT_EQ(d.year, year);
  EXPECT_EQ(d.month, month);
  EXPECT_EQ(d.day, day);
}

TEST_F(DateValueTest_2172, SetDate_UpdatesGetDate_2172) {
  Exiv2::DateValue dv(2000, 1, 1);

  Exiv2::DateValue::Date newDate{};
  newDate.year = 1999;
  newDate.month = 12;
  newDate.day = 31;

  dv.setDate(newDate);

  const Exiv2::DateValue::Date& d = dv.getDate();
  EXPECT_EQ(d.year, 1999);
  EXPECT_EQ(d.month, 12);
  EXPECT_EQ(d.day, 31);
}

TEST_F(DateValueTest_2172, Clone_CopiesValueAndIsIndependent_2172) {
  Exiv2::DateValue original(2020, 6, 30);

  Exiv2::Value::UniquePtr clonedBase = original.clone();
  ASSERT_NE(clonedBase.get(), nullptr);
  EXPECT_EQ(clonedBase->typeId(), Exiv2::date);

  // Downcast to DateValue via dynamic_cast (public polymorphic base).
  const auto* cloned = dynamic_cast<const Exiv2::DateValue*>(clonedBase.get());
  ASSERT_NE(cloned, nullptr);

  // Cloned date matches.
  {
    const auto& d = cloned->getDate();
    EXPECT_EQ(d.year, 2020);
    EXPECT_EQ(d.month, 6);
    EXPECT_EQ(d.day, 30);
  }

  // Mutate original and ensure clone stays unchanged (observable independence).
  Exiv2::DateValue::Date mutated{};
  mutated.year = 2021;
  mutated.month = 7;
  mutated.day = 1;
  original.setDate(mutated);

  {
    const auto& dOrig = original.getDate();
    EXPECT_EQ(dOrig.year, 2021);
    EXPECT_EQ(dOrig.month, 7);
    EXPECT_EQ(dOrig.day, 1);
  }
  {
    const auto& dClone = cloned->getDate();
    EXPECT_EQ(dClone.year, 2020);
    EXPECT_EQ(dClone.month, 6);
    EXPECT_EQ(dClone.day, 30);
  }
}

TEST_F(DateValueTest_2172, SizeAndCount_AreNonZeroAndConsistent_2172) {
  Exiv2::DateValue dv(2026, 2, 11);

  // We don't assume exact values; only that these are well-defined and stable.
  const size_t s1 = dv.size();
  const size_t c1 = dv.count();
  EXPECT_GT(s1, 0u);
  EXPECT_GT(c1, 0u);

  // Re-check for consistency across repeated calls.
  EXPECT_EQ(dv.size(), s1);
  EXPECT_EQ(dv.count(), c1);
}

TEST_F(DateValueTest_2172, Write_ProducesSomeOutputForSetDate_2172) {
  Exiv2::DateValue dv(2026, 2, 11);

  std::ostringstream oss;
  const std::ostream& ret = dv.write(oss);

  // Stream chaining should be valid (same stream object returned).
  EXPECT_EQ(&ret, &oss);

  // Don't assume exact formatting; just that something is emitted.
  EXPECT_FALSE(oss.str().empty());
}

}  // namespace