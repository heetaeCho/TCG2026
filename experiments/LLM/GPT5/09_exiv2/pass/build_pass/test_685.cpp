// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_iptcdatum_value_685.cpp
//
// Unit tests for Exiv2::Iptcdatum::value() const
//
// Constraints respected:
// - Treat implementation as a black box.
// - Use only public API / observable behavior.
// - Do not access private state.

#include <gtest/gtest.h>

#include <exiv2/error.hpp>
#include <exiv2/iptc.hpp>

namespace {

class IptcdatumTest_685 : public ::testing::Test {
 protected:
  static Exiv2::IptcKey MakeKey() {
    // Use a commonly valid IPTC key string in Exiv2.
    // (Exact internal tag/record mapping is not relied upon by these tests.)
    return Exiv2::IptcKey("Iptc.Application2.ObjectName");
  }
};

TEST_F(IptcdatumTest_685, ValueThrowsWhenNotSet_685) {
  const Exiv2::IptcKey key = MakeKey();

  // Construct with no value set.
  Exiv2::Iptcdatum datum(key, nullptr);

  try {
    (void)datum.value();
    FAIL() << "Expected Exiv2::Error to be thrown when value is not set";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerValueNotSet);
  } catch (...) {
    FAIL() << "Expected Exiv2::Error, but got a different exception type";
  }
}

TEST_F(IptcdatumTest_685, ValueDoesNotThrowAfterStringAssignment_685) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  // Use only public observable API to set a value.
  datum = std::string("hello");

  EXPECT_NO_THROW((void)datum.value());
}

TEST_F(IptcdatumTest_685, ValueDoesNotThrowAfterEmptyStringAssignment_685) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  // Boundary: empty string as a value.
  datum = std::string("");

  EXPECT_NO_THROW((void)datum.value());
}

TEST_F(IptcdatumTest_685, ValueThrowsOnFreshCopyIfConstructedWithoutValue_685) {
  const Exiv2::IptcKey key = MakeKey();

  Exiv2::Iptcdatum original(key, nullptr);
  Exiv2::Iptcdatum copy(original);

  // Observable behavior should be consistent on the copy.
  EXPECT_THROW((void)copy.value(), Exiv2::Error);
}

}  // namespace