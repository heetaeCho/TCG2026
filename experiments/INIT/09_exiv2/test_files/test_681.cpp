// SPDX-License-Identifier: GPL-2.0-or-later
// The TEST_ID is 681
//
// Unit tests for Exiv2::Iptcdatum::toInt64(size_t)
//
// Constraints honored:
// - Treat implementation as black box (test observable behavior only).
// - No access to private/internal state.
// - No re-implementation of internal logic beyond what is observable via interface.

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <cstdint>
#include <limits>
#include <memory>
#include <string>

namespace {

// A small deterministic Value implementation that supports cloning.
// It returns (base_ + n) for any n that safely fits into int64_t;
// for larger n, it returns base_ (keeps behavior deterministic without UB).
class TestInt64Value final : public Exiv2::Value {
 public:
  explicit TestInt64Value(int64_t base)
      : Exiv2::Value(static_cast<Exiv2::TypeId>(0)), base_(base) {}

  int64_t toInt64(size_t n) const override {
    // Avoid UB or implementation-defined surprises in tests.
    if (n > static_cast<size_t>(std::numeric_limits<int64_t>::max())) {
      return base_;
    }
    const int64_t nn = static_cast<int64_t>(n);
    if (nn > 0 && base_ > (std::numeric_limits<int64_t>::max() - nn)) {
      return base_;
    }
    if (nn < 0 && base_ < (std::numeric_limits<int64_t>::min() - nn)) {
      return base_;
    }
    return base_ + nn;
  }

 private:
  const Exiv2::Value* clone_() override { return new TestInt64Value(*this); }

  int64_t base_;
};

Exiv2::IptcKey MakeSomeIptcKey() {
  // Use a common, valid-looking IPTC key string. Tests rely only on public API.
  return Exiv2::IptcKey("Iptc.Application2.ObjectName");
}

}  // namespace

class IptcdatumToInt64Test_681 : public ::testing::Test {};

TEST_F(IptcdatumToInt64Test_681, ReturnsMinusOneWhenNoValue_681) {
  const Exiv2::IptcKey key = MakeSomeIptcKey();

  // Construct with null Value pointer.
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ(-1, datum.toInt64(0));
  EXPECT_EQ(-1, datum.toInt64(1));
  EXPECT_EQ(-1, datum.toInt64(999));
}

TEST_F(IptcdatumToInt64Test_681, ReturnsUnderlyingValueForZeroIndex_681) {
  const Exiv2::IptcKey key = MakeSomeIptcKey();

  auto v = std::make_unique<TestInt64Value>(42);
  Exiv2::Iptcdatum datum(key, v.get());

  EXPECT_EQ(42, datum.toInt64(0));
}

TEST_F(IptcdatumToInt64Test_681, ReturnsUnderlyingValueForNonZeroIndex_681) {
  const Exiv2::IptcKey key = MakeSomeIptcKey();

  auto v = std::make_unique<TestInt64Value>(10);
  Exiv2::Iptcdatum datum(key, v.get());

  EXPECT_EQ(11, datum.toInt64(1));
  EXPECT_EQ(13, datum.toInt64(3));
  EXPECT_EQ(10 + 123456, datum.toInt64(123456));
}

TEST_F(IptcdatumToInt64Test_681, LargeIndexStillProducesDeterministicResult_681) {
  const Exiv2::IptcKey key = MakeSomeIptcKey();

  auto v = std::make_unique<TestInt64Value>(-7);
  Exiv2::Iptcdatum datum(key, v.get());

  // Boundary-ish: large but safely within int64_t range.
  const size_t n = static_cast<size_t>(std::numeric_limits<int32_t>::max());
  EXPECT_EQ(-7 + static_cast<int64_t>(n), datum.toInt64(n));
}