// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_exifdatum_toString_759.cpp
//
// Unit tests for Exiv2::Exifdatum::toString(size_t n)
// Black-box tests based only on public interface / observable behavior.

#include <gtest/gtest.h>

#include <exiv2/exif.hpp>

#include <limits>
#include <memory>
#include <string>

namespace {

// A Value test-double that lets us observe delegation from Exifdatum::toString(size_t)
// without depending on Exiv2 internals. This is an external collaborator passed in via
// Exifdatum's public constructor.
class CountingValue final : public Exiv2::Value {
 public:
  struct State {
    size_t calls = 0;
    size_t last_n = 0;
  };

  CountingValue()
      : Exiv2::Value(Exiv2::invalidTypeId), state_(std::make_shared<State>()) {}

  CountingValue(const CountingValue& rhs) = default;

  std::shared_ptr<State> state() const { return state_; }

  std::string toString(size_t n) const override {
    state_->calls += 1;
    state_->last_n = n;
    return "value(" + std::to_string(n) + ")";
  }

 private:
  // Exiv2::Value uses a virtual clone_() hook internally for clone().
  // We implement it so Exifdatum can safely take/copy the provided Value*.
  const Exiv2::Value* clone_() const override { return new CountingValue(*this); }

  std::shared_ptr<State> state_;
};

class ExifdatumTest_759 : public ::testing::Test {
 protected:
  static Exiv2::ExifKey MakeKey() {
    // Use a commonly valid Exif key string. This is part of Exiv2's public API.
    return Exiv2::ExifKey("Exif.Image.Make");
  }
};

}  // namespace

TEST_F(ExifdatumTest_759, ToStringWithNullValueReturnsEmptyString_759) {
  const Exiv2::ExifKey key = MakeKey();
  Exiv2::Exifdatum datum(key, /*pValue=*/nullptr);

  EXPECT_EQ("", datum.toString(0));
  EXPECT_EQ("", datum.toString(1));
  EXPECT_EQ("", datum.toString(std::numeric_limits<size_t>::max()));
}

TEST_F(ExifdatumTest_759, ToStringDelegatesToValueAndReturnsItsString_759) {
  const Exiv2::ExifKey key = MakeKey();

  CountingValue value;
  auto st = value.state();
  ASSERT_TRUE(st);

  Exiv2::Exifdatum datum(key, &value);

  const size_t n = 7;
  EXPECT_EQ("value(7)", datum.toString(n));

  // Verify observable external interaction: Value::toString(size_t) was called with n.
  EXPECT_EQ(1u, st->calls);
  EXPECT_EQ(n, st->last_n);
}

TEST_F(ExifdatumTest_759, ToStringMultipleCallsForwardEachIndex_759) {
  const Exiv2::ExifKey key = MakeKey();

  CountingValue value;
  auto st = value.state();
  ASSERT_TRUE(st);

  Exiv2::Exifdatum datum(key, &value);

  EXPECT_EQ("value(0)", datum.toString(0));
  EXPECT_EQ(1u, st->calls);
  EXPECT_EQ(0u, st->last_n);

  EXPECT_EQ("value(1)", datum.toString(1));
  EXPECT_EQ(2u, st->calls);
  EXPECT_EQ(1u, st->last_n);

  const size_t big = std::numeric_limits<size_t>::max();
  EXPECT_EQ("value(" + std::to_string(big) + ")", datum.toString(big));
  EXPECT_EQ(3u, st->calls);
  EXPECT_EQ(big, st->last_n);
}

TEST_F(ExifdatumTest_759, ToStringDoesNotThrowEvenForLargeIndex_759) {
  const Exiv2::ExifKey key = MakeKey();

  CountingValue value;
  Exiv2::Exifdatum datum(key, &value);

  const size_t big = std::numeric_limits<size_t>::max();
  EXPECT_NO_THROW({
    const std::string s = datum.toString(big);
    (void)s;
  });
}