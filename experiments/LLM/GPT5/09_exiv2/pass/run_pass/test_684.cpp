// SPDX-License-Identifier: GPL-2.0-or-later
// Test file for Exiv2::Iptcdatum::getValue()
// The TEST_ID is 684

#include <gtest/gtest.h>

#include <exiv2/iptc.hpp>
#include <exiv2/value.hpp>

#include <string>

namespace {

class IptcdatumTest_684 : public ::testing::Test {
 protected:
  // Use a common, well-known IPTC key string.
  Exiv2::IptcKey MakeKey() { return Exiv2::IptcKey("Iptc.Application2.ObjectName"); }

  static Exiv2::Value::UniquePtr MakeStringValue(const std::string& s) {
    // Use a simple string-like TypeId. In Exiv2 this is typically asciiString.
    Exiv2::Value::UniquePtr v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v, nullptr);
    if (v) {
      // read() is observable; we only assert it reports success.
      EXPECT_EQ(0, v->read(s));
    }
    return v;
  }
};

TEST_F(IptcdatumTest_684, GetValueReturnsNullptrWhenConstructedWithNullValue_684) {
  const Exiv2::IptcKey key = MakeKey();

  // Construct with no Value. Observable behavior: getValue() should return nullptr.
  Exiv2::Iptcdatum datum(key, nullptr);

  Exiv2::Value::UniquePtr got = datum.getValue();
  EXPECT_EQ(got, nullptr);
}

TEST_F(IptcdatumTest_684, GetValueReturnsNonNullCloneWhenValuePresent_684) {
  const Exiv2::IptcKey key = MakeKey();
  auto v = MakeStringValue("hello");

  ASSERT_NE(v, nullptr);
  Exiv2::Iptcdatum datum(key, v.get());

  Exiv2::Value::UniquePtr got = datum.getValue();
  ASSERT_NE(got, nullptr);

  // Observable: returned value should be a different object than datum.value().
  EXPECT_NE(got.get(), &datum.value());

  // Observable: clone should represent the same content as the datum's public string view.
  EXPECT_EQ(got->toString(), datum.toString());
}

TEST_F(IptcdatumTest_684, GetValueCalledTwiceReturnsDistinctObjectsWithSameObservableContent_684) {
  const Exiv2::IptcKey key = MakeKey();
  auto v = MakeStringValue("repeatable");

  ASSERT_NE(v, nullptr);
  Exiv2::Iptcdatum datum(key, v.get());

  Exiv2::Value::UniquePtr a = datum.getValue();
  Exiv2::Value::UniquePtr b = datum.getValue();

  ASSERT_NE(a, nullptr);
  ASSERT_NE(b, nullptr);

  // Boundary-style: repeated calls should not hand out the same owning pointer.
  EXPECT_NE(a.get(), b.get());

  // Both should match the datum's observable representation.
  EXPECT_EQ(a->toString(), datum.toString());
  EXPECT_EQ(b->toString(), datum.toString());
}

TEST_F(IptcdatumTest_684, GetValueBecomesNullptrAfterSetValueNullptr_684) {
  const Exiv2::IptcKey key = MakeKey();
  auto v = MakeStringValue("will_be_cleared");

  ASSERT_NE(v, nullptr);
  Exiv2::Iptcdatum datum(key, v.get());

  // Precondition: value exists.
  ASSERT_NE(datum.getValue(), nullptr);

  // Observable: after setting nullptr, getValue should return nullptr.
  datum.setValue(nullptr);
  EXPECT_EQ(datum.getValue(), nullptr);
}

}  // namespace