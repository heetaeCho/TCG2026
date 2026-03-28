// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptcdatum_uint16_assignment_687.cpp
//
// Unit tests for Exiv2::Iptcdatum::operator=(const uint16_t&)
// Based strictly on observable behavior through the public interface.

#include <gtest/gtest.h>

#include <cstdint>
#include <limits>

#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>

namespace {

Exiv2::Iptcdatum MakeDatum_687() {
  // Use a commonly-available IPTC key string. The specific key should not
  // affect assignment-to-value behavior under test.
  Exiv2::IptcKey key("Iptc.Application2.RecordVersion");
  return Exiv2::Iptcdatum(key, nullptr);
}

}  // namespace

class IptcdatumTest_687 : public ::testing::Test {};

TEST_F(IptcdatumTest_687, AssignUint16_SetsSingleValueAndIsChainable_687) {
  auto d = MakeDatum_687();

  const uint16_t v = 12345;
  Exiv2::Iptcdatum* ret = nullptr;

  EXPECT_NO_THROW({
    ret = &(d = v);
  });

  ASSERT_NE(ret, nullptr);
  EXPECT_EQ(ret, &d);

  // Observable effects through public API.
  EXPECT_EQ(d.count(), 1u);
  EXPECT_EQ(d.toInt64(0), static_cast<int64_t>(v));
  EXPECT_EQ(d.toString(), d.toString(0));  // Single element should match element(0)
}

TEST_F(IptcdatumTest_687, AssignUint16_OverwriteReplacesValue_687) {
  auto d = MakeDatum_687();

  const uint16_t first = 1;
  const uint16_t second = 65000;

  ASSERT_NO_THROW(d = first);
  EXPECT_EQ(d.count(), 1u);
  EXPECT_EQ(d.toInt64(0), static_cast<int64_t>(first));

  ASSERT_NO_THROW(d = second);
  EXPECT_EQ(d.count(), 1u) << "Overwriting should still result in a single stored value";
  EXPECT_EQ(d.toInt64(0), static_cast<int64_t>(second));
}

TEST_F(IptcdatumTest_687, AssignUint16_BoundaryZero_687) {
  auto d = MakeDatum_687();

  const uint16_t v = 0;
  EXPECT_NO_THROW(d = v);

  EXPECT_EQ(d.count(), 1u);
  EXPECT_EQ(d.toInt64(0), 0);
  EXPECT_EQ(d.toString(0), "0");
}

TEST_F(IptcdatumTest_687, AssignUint16_BoundaryMaxUint16_687) {
  auto d = MakeDatum_687();

  const uint16_t v = std::numeric_limits<uint16_t>::max();
  EXPECT_NO_THROW(d = v);

  EXPECT_EQ(d.count(), 1u);
  EXPECT_EQ(d.toInt64(0), static_cast<int64_t>(v));
  EXPECT_EQ(d.toString(0), std::to_string(static_cast<unsigned>(v)));
}

TEST_F(IptcdatumTest_687, AssignUint16_TypeInformationIsConsistent_687) {
  auto d = MakeDatum_687();

  const uint16_t v = 42;
  ASSERT_NO_THROW(d = v);

  // Only check broadly observable type traits that should be stable.
  // A uint16_t value is expected to occupy 2 bytes per element.
  EXPECT_EQ(d.typeSize(), sizeof(uint16_t));
  EXPECT_EQ(d.size(), sizeof(uint16_t) * d.count());

  // If TypeId is exposed, it should reflect an unsigned short after assignment.
  // (This is an observable public contract through typeId().)
  EXPECT_EQ(d.typeId(), Exiv2::unsignedShort);
}