// File: test_xmpdatum_tostring_n_1292.cpp
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include <exiv2/value.hpp>
#include <exiv2/xmp_exiv2.hpp>

namespace {

// A small test Value implementation that is safe to pass into Xmpdatum.
// It provides a deterministic toString(n) and supports cloning.
class TestValue final : public Exiv2::Value {
 public:
  explicit TestValue(const std::string& base)
      : Exiv2::Value(Exiv2::TypeId::string), base_(base) {}

  // Match the signature from the included Exiv2 headers.
  const std::string toString(size_t n) override {
    return base_ + "#" + std::to_string(n);
  }

 private:
  // Value::clone() calls the private virtual clone_(), which we override here.
  const Exiv2::Value* clone_() override { return new TestValue(*this); }

  std::string base_;
};

class XmpdatumToStringNTest_1292 : public ::testing::Test {
 protected:
  static Exiv2::XmpKey MakeKey() {
    // Use a common, valid-looking XMP key string. We rely only on public API.
    return Exiv2::XmpKey("Xmp.dc.title");
  }
};

}  // namespace

TEST_F(XmpdatumToStringNTest_1292, ReturnsEmptyStringWhenValueIsNull_1292) {
  const Exiv2::XmpKey key = MakeKey();

  Exiv2::Xmpdatum datum(key, /*pValue=*/nullptr);

  EXPECT_EQ(datum.toString(0), "");
  EXPECT_EQ(datum.toString(1), "");
  EXPECT_EQ(datum.toString(std::numeric_limits<size_t>::max()), "");
}

TEST_F(XmpdatumToStringNTest_1292, ForwardsToUnderlyingValueForN0_1292) {
  const Exiv2::XmpKey key = MakeKey();

  const TestValue tv("base");
  Exiv2::Xmpdatum datum(key, &tv);

  EXPECT_EQ(datum.toString(0), "base#0");
}

TEST_F(XmpdatumToStringNTest_1292, ForwardsToUnderlyingValueForTypicalN_1292) {
  const Exiv2::XmpKey key = MakeKey();

  const TestValue tv("v");
  Exiv2::Xmpdatum datum(key, &tv);

  EXPECT_EQ(datum.toString(1), "v#1");
  EXPECT_EQ(datum.toString(5), "v#5");
  EXPECT_EQ(datum.toString(123), "v#123");
}

TEST_F(XmpdatumToStringNTest_1292, HandlesVeryLargeNWithoutCrashing_1292) {
  const Exiv2::XmpKey key = MakeKey();

  const TestValue tv("big");
  Exiv2::Xmpdatum datum(key, &tv);

  const size_t n = std::numeric_limits<size_t>::max();
  EXPECT_EQ(datum.toString(n), std::string("big#") + std::to_string(n));
}

TEST_F(XmpdatumToStringNTest_1292, IndependentInstancesProduceIndependentStrings_1292) {
  const Exiv2::XmpKey key = MakeKey();

  const TestValue tvA("A");
  const TestValue tvB("B");
  Exiv2::Xmpdatum datumA(key, &tvA);
  Exiv2::Xmpdatum datumB(key, &tvB);

  EXPECT_EQ(datumA.toString(7), "A#7");
  EXPECT_EQ(datumB.toString(7), "B#7");
}