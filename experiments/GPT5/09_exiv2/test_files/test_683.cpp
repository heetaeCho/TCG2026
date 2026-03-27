// TEST_ID 683
// File: test_iptcdatum_toRational_683.cpp

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <cstddef>
#include <cstdint>
#include <string>

namespace {

// A test Value implementation that:
// - returns a fixed Rational
// - records the last index passed to toRational()
// - supports cloning (so it can be safely stored/cloned by Iptcdatum)
class TrackingRationalValue final : public Exiv2::Value {
 public:
  explicit TrackingRationalValue(const Exiv2::Rational& r)
      : Exiv2::Value(Exiv2::signedRational), r_(r) {}

  TrackingRationalValue(const TrackingRationalValue&) = default;
  ~TrackingRationalValue() override = default;

  const Exiv2::Rational toRational(size_t n) override {
    ++call_count_;
    last_n_ = n;
    return r_;
  }

  int call_count() const { return call_count_; }
  size_t last_n() const { return last_n_; }

 private:
  // Value::clone() calls the virtual clone_() hook.
  const Exiv2::Value* clone_() override { return new TrackingRationalValue(*this); }

  Exiv2::Rational r_;
  int call_count_{0};
  size_t last_n_{static_cast<size_t>(-1)};
};

class IptcdatumTest_683 : public ::testing::Test {
 protected:
  // Use a commonly-valid IPTC key string used throughout Exiv2.
  // (This is only used to satisfy the public constructor interface.)
  static Exiv2::IptcKey MakeKey() { return Exiv2::IptcKey("Iptc.Application2.ObjectName"); }
};

TEST_F(IptcdatumTest_683, NullValueReturnsSentinelRational_683) {
  Exiv2::Iptcdatum datum(MakeKey(), nullptr);

  const Exiv2::Rational r0 = datum.toRational(0);
  EXPECT_EQ(-1, r0.first);
  EXPECT_EQ(1, r0.second);

  const Exiv2::Rational rBig = datum.toRational(static_cast<size_t>(123456));
  EXPECT_EQ(-1, rBig.first);
  EXPECT_EQ(1, rBig.second);
}

TEST_F(IptcdatumTest_683, NonNullValueIsForwardedAndReturned_683) {
  TrackingRationalValue tv(Exiv2::Rational(3, 2));
  Exiv2::Iptcdatum datum(MakeKey(), &tv);

  const Exiv2::Rational r = datum.toRational(0);
  EXPECT_EQ(3, r.first);
  EXPECT_EQ(2, r.second);
}

TEST_F(IptcdatumTest_683, ToRationalForwardsIndexParameter_683) {
  TrackingRationalValue tv(Exiv2::Rational(7, 5));
  Exiv2::Iptcdatum datum(MakeKey(), &tv);

  const size_t n = 42;
  (void)datum.toRational(n);

  // Observable behavior: the dependency's toRational should see the same index.
  EXPECT_EQ(1, tv.call_count());
  EXPECT_EQ(n, tv.last_n());
}

TEST_F(IptcdatumTest_683, SetValueToNullSwitchesBackToSentinel_683) {
  TrackingRationalValue tv(Exiv2::Rational(9, 4));
  Exiv2::Iptcdatum datum(MakeKey(), &tv);

  // Sanity: non-null path first.
  const Exiv2::Rational r1 = datum.toRational(1);
  EXPECT_EQ(9, r1.first);
  EXPECT_EQ(4, r1.second);

  // Now switch to null through the public interface.
  datum.setValue(nullptr);

  const Exiv2::Rational r2 = datum.toRational(1);
  EXPECT_EQ(-1, r2.first);
  EXPECT_EQ(1, r2.second);
}

TEST_F(IptcdatumTest_683, SetValueReplacesPreviousValue_683) {
  TrackingRationalValue tv1(Exiv2::Rational(1, 3));
  TrackingRationalValue tv2(Exiv2::Rational(8, 9));
  Exiv2::Iptcdatum datum(MakeKey(), &tv1);

  const Exiv2::Rational a = datum.toRational(0);
  EXPECT_EQ(1, a.first);
  EXPECT_EQ(3, a.second);
  EXPECT_EQ(1, tv1.call_count());

  datum.setValue(&tv2);

  const Exiv2::Rational b = datum.toRational(0);
  EXPECT_EQ(8, b.first);
  EXPECT_EQ(9, b.second);
  EXPECT_EQ(1, tv2.call_count());
}

}  // namespace