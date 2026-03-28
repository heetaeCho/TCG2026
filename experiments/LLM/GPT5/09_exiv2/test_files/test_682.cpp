// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptcdatum_toFloat_682.cpp
//
// Unit tests for Exiv2::Iptcdatum::toFloat(size_t)
//
// Constraints respected:
// - Treat implementation as black box.
// - Only test observable behavior via public interface.
// - No access to private/internal state.

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <limits>
#include <memory>

namespace {

class IptcdatumToFloatTest_682 : public ::testing::Test {
 protected:
  // Use a commonly available IPTC key string (widely used in Exiv2 examples/tests).
  // If your codebase prefers a different canonical tag string, adjust here.
  static Exiv2::IptcKey MakeKey() { return Exiv2::IptcKey("Iptc.Application2.ObjectName"); }
};

TEST_F(IptcdatumToFloatTest_682, ReturnsMinusOneWhenValueIsNull_682) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_FLOAT_EQ(datum.toFloat(0), -1.0f);
}

TEST_F(IptcdatumToFloatTest_682, ReturnsMinusOneForLargeIndexWhenValueIsNull_682) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  const size_t big = (std::numeric_limits<size_t>::max)();
  EXPECT_FLOAT_EQ(datum.toFloat(big), -1.0f);
}

TEST_F(IptcdatumToFloatTest_682, ForwardsToUnderlyingValueWhenPresent_682) {
  const Exiv2::IptcKey key = MakeKey();

  // Create a real Exiv2::Value instance (public factory) and populate it via public API.
  // We avoid mocking here because Iptcdatum may clone/copy the Value internally, which
  // can make direct mock-call verification non-observable through the public interface.
  Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_TRUE(v.get() != nullptr);

  ASSERT_EQ(0, v->read(std::string("3.5")));

  Exiv2::Iptcdatum datum(key, v.get());

  // Observable behavior: toFloat(0) matches what the stored Value represents.
  EXPECT_FLOAT_EQ(datum.toFloat(0), 3.5f);
}

}  // namespace