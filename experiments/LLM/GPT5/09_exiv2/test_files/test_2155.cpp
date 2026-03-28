// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_value_type_ctor_2155.cpp

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <memory>

namespace {

// NOTE: The constructor under test takes an explicit TypeId. We avoid depending on
// specific TypeId enumerators by using a casted integral value.
constexpr Exiv2::TypeId kTypeId0 = static_cast<Exiv2::TypeId>(0);
constexpr Exiv2::TypeId kTypeId1 = static_cast<Exiv2::TypeId>(1);

}  // namespace

// The TEST_ID is 2155

TEST(ValueTypeCtorTest_2155, Int32StoresSingleValueAndPreservesTypeId_2155) {
  const std::int32_t input = 123;

  Exiv2::ValueType<std::int32_t> v(input, kTypeId0);

  EXPECT_TRUE(v.ok());
  EXPECT_EQ(v.typeId(), kTypeId0);
  EXPECT_EQ(v.count(), 1u);

  // Observable value access via public interface.
  EXPECT_EQ(v.toInt64(0), static_cast<std::int64_t>(input));
  EXPECT_EQ(v.toUint32(0), static_cast<std::uint32_t>(input));
}

TEST(ValueTypeCtorTest_2155, NegativeInt32RoundTripsThroughToInt64_2155) {
  const std::int32_t input = -7;

  Exiv2::ValueType<std::int32_t> v(input, kTypeId1);

  EXPECT_TRUE(v.ok());
  EXPECT_EQ(v.typeId(), kTypeId1);
  EXPECT_EQ(v.count(), 1u);

  EXPECT_EQ(v.toInt64(0), static_cast<std::int64_t>(input));
}

TEST(ValueTypeCtorTest_2155, Int64MaxValueIsObservable_2155) {
  const std::int64_t input = (std::numeric_limits<std::int64_t>::max)();

  Exiv2::ValueType<std::int64_t> v(input, kTypeId0);

  EXPECT_TRUE(v.ok());
  EXPECT_EQ(v.typeId(), kTypeId0);
  EXPECT_EQ(v.count(), 1u);

  EXPECT_EQ(v.toInt64(0), input);
}

TEST(ValueTypeCtorTest_2155, FloatStoresSingleValueObservableViaToFloat_2155) {
  const float input = 3.5f;

  Exiv2::ValueType<float> v(input, kTypeId0);

  EXPECT_TRUE(v.ok());
  EXPECT_EQ(v.typeId(), kTypeId0);
  EXPECT_EQ(v.count(), 1u);

  EXPECT_FLOAT_EQ(v.toFloat(0), input);
}

TEST(ValueTypeCtorTest_2155, CloneProducesIndependentObjectWithSameObservableValue_2155) {
  const std::int32_t input = 42;

  Exiv2::ValueType<std::int32_t> v(input, kTypeId1);

  Exiv2::Value::UniquePtr cloned = v.clone();
  ASSERT_NE(cloned.get(), nullptr);

  // Verify observable behavior through the public virtual interface.
  EXPECT_TRUE(cloned->ok());
  EXPECT_EQ(cloned->typeId(), kTypeId1);
  EXPECT_EQ(cloned->count(), 1u);
  EXPECT_EQ(cloned->toInt64(0), static_cast<std::int64_t>(input));

  // Also ensure it is a different object instance.
  EXPECT_NE(cloned.get(), &v);
}