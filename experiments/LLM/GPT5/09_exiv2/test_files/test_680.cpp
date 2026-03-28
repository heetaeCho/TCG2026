// =================================================================================================
// TEST_ID: 680
// File: test_iptcdatum_toString_680.cpp
// Unit tests for Exiv2::Iptcdatum::toString(size_t)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <limits>
#include <memory>
#include <string>

namespace {

class IptcdatumToStringTest_680 : public ::testing::Test {
 protected:
  // A commonly-used IPTC key string in Exiv2 examples/tests.
  Exiv2::IptcKey MakeKey() { return Exiv2::IptcKey("Iptc.Application2.Caption"); }
};

// Normal / boundary: if constructed with no value, toString(n) should be empty.
TEST_F(IptcdatumToStringTest_680, ToStringReturnsEmptyWhenNoValue_680) {
  const Exiv2::IptcKey key = MakeKey();

  // Construct with nullptr Value (observable behavior: toString(n) should return "").
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ("", datum.toString(0));
}

TEST_F(IptcdatumToStringTest_680, ToStringReturnsEmptyForVariousNWhenNoValue_680) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_EQ("", datum.toString(0));
  EXPECT_EQ("", datum.toString(1));
  EXPECT_EQ("", datum.toString(999));
  EXPECT_EQ("", datum.toString(std::numeric_limits<size_t>::max()));
}

// Normal operation: when a Value is provided, Iptcdatum::toString(n) should match
// what the provided Value reports for the same n (black-box forwarding behavior).
TEST_F(IptcdatumToStringTest_680, ToStringMatchesUnderlyingValueToStringForN0_680) {
  const Exiv2::IptcKey key = MakeKey();

  // Create a value of a string-like type and populate it through its public API.
  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(nullptr, v);
  ASSERT_EQ(0, v->read(std::string("hello")));

  Exiv2::Iptcdatum datum(key, v.get());

  // Compare against the dependency's observable output (no internal inference).
  EXPECT_EQ(v->toString(0), datum.toString(0));
}

// Boundary: larger n should behave consistently with Value::toString(n).
TEST_F(IptcdatumToStringTest_680, ToStringMatchesUnderlyingValueToStringForVariousN_680) {
  const Exiv2::IptcKey key = MakeKey();

  auto v = Exiv2::Value::create(Exiv2::asciiString);
  ASSERT_NE(nullptr, v);
  ASSERT_EQ(0, v->read(std::string("single")));

  Exiv2::Iptcdatum datum(key, v.get());

  // We don't assume what out-of-range means; we only assert Iptcdatum mirrors Value.
  for (size_t n : {size_t{0}, size_t{1}, size_t{2}, size_t{100}}) {
    EXPECT_EQ(v->toString(n), datum.toString(n)) << "n=" << n;
  }
}

// Exceptional/error case (observable): toString(n) should not throw for null Value path.
TEST_F(IptcdatumToStringTest_680, ToStringDoesNotThrowWhenNoValue_680) {
  const Exiv2::IptcKey key = MakeKey();
  Exiv2::Iptcdatum datum(key, nullptr);

  EXPECT_NO_THROW((void)datum.toString(0));
  EXPECT_NO_THROW((void)datum.toString(std::numeric_limits<size_t>::max()));
}

}  // namespace