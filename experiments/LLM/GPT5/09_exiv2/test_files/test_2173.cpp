// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_timevalue_2173.cpp

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstdint>
#include <memory>
#include <ostream>
#include <sstream>
#include <vector>

namespace {

class TimeValueTest_2173 : public ::testing::Test {};

TEST_F(TimeValueTest_2173, DefaultConstructor_ZeroTimeFields_2173) {
  Exiv2::TimeValue v;

  const auto& t = v.getTime();
  EXPECT_EQ(0, t.hour);
  EXPECT_EQ(0, t.minute);
  EXPECT_EQ(0, t.second);
  EXPECT_EQ(0, t.tzHour);
  EXPECT_EQ(0, t.tzMinute);
}

TEST_F(TimeValueTest_2173, DefaultConstructor_TypeIdAndOkAreObservable_2173) {
  Exiv2::TimeValue v;

  // Observable via Value public API.
  EXPECT_TRUE(v.ok());
  EXPECT_EQ(Exiv2::time, v.typeId());
}

TEST_F(TimeValueTest_2173, Clone_PreservesObservableOutputs_2173) {
  Exiv2::TimeValue v;

  // Exercise a public mutator to ensure clone reflects it.
  Exiv2::TimeValue::Time src{};
  src.hour = 12;
  src.minute = 34;
  src.second = 56;
  src.tzHour = 9;
  src.tzMinute = 0;
  v.setTime(src);

  std::unique_ptr<Exiv2::Value> baseClone;
  ASSERT_NO_THROW(baseClone = v.clone());
  ASSERT_NE(nullptr, baseClone.get());

  // Type should be preserved across cloning.
  EXPECT_EQ(v.typeId(), baseClone->typeId());

  // If it is a TimeValue, time fields must match what is observable via getTime().
  const auto* tvClone = dynamic_cast<const Exiv2::TimeValue*>(baseClone.get());
  ASSERT_NE(nullptr, tvClone);

  const auto& t1 = v.getTime();
  const auto& t2 = tvClone->getTime();
  EXPECT_EQ(t1.hour, t2.hour);
  EXPECT_EQ(t1.minute, t2.minute);
  EXPECT_EQ(t1.second, t2.second);
  EXPECT_EQ(t1.tzHour, t2.tzHour);
  EXPECT_EQ(t1.tzMinute, t2.tzMinute);

  // Other observable aspects should be stable as well.
  EXPECT_EQ(v.count(), tvClone->count());
  EXPECT_EQ(v.size(), tvClone->size());
  EXPECT_EQ(v.toString(), tvClone->toString());
}

TEST_F(TimeValueTest_2173, SetTime_ChangesGetTimeObservably_2173) {
  Exiv2::TimeValue v;

  Exiv2::TimeValue::Time src{};
  src.hour = 1;
  src.minute = 2;
  src.second = 3;
  src.tzHour = -5;
  src.tzMinute = 30;

  ASSERT_NO_THROW(v.setTime(src));

  const auto& t = v.getTime();
  EXPECT_EQ(src.hour, t.hour);
  EXPECT_EQ(src.minute, t.minute);
  EXPECT_EQ(src.second, t.second);
  EXPECT_EQ(src.tzHour, t.tzHour);
  EXPECT_EQ(src.tzMinute, t.tzMinute);
}

TEST_F(TimeValueTest_2173, Copy_ReturnsConsistentSizeWithSizeMethod_2173) {
  Exiv2::TimeValue v;

  // Allocate exactly size() bytes and ensure copy returns a value that is not
  // larger than the advertised size. (No assumptions on exact encoding.)
  const size_t sz = v.size();
  std::vector<Exiv2::byte> buf(sz == 0 ? 1 : sz);  // avoid zero-sized .data() pitfalls

  const size_t copied = v.copy(buf.data(), Exiv2::invalidByteOrder);
  EXPECT_LE(copied, sz);

  // Calling size() again should be stable for the same object.
  EXPECT_EQ(sz, v.size());
}

TEST_F(TimeValueTest_2173, Write_DoesNotThrowAndIsStreamable_2173) {
  Exiv2::TimeValue v;

  std::ostringstream oss;
  EXPECT_NO_THROW(v.write(oss));

  // No strict assumptions about formatting; just ensure the stream is usable.
  EXPECT_TRUE(oss.good());
}

}  // namespace