// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmpdata_empty_1310.cpp

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/value.hpp>

namespace {

class XmpDataTest_1310 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr makeAsciiValue(const std::string& s) {
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    v->read(s);
    return v;
  }
};

TEST_F(XmpDataTest_1310, DefaultConstructedIsEmpty_1310) {
  Exiv2::XmpData xmp;
  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
}

TEST_F(XmpDataTest_1310, ClearOnEmptyRemainsEmpty_1310) {
  Exiv2::XmpData xmp;

  EXPECT_TRUE(xmp.empty());
  EXPECT_NO_THROW(xmp.clear());

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
}

TEST_F(XmpDataTest_1310, AddMakesNotEmpty_1310) {
  Exiv2::XmpData xmp;
  ASSERT_TRUE(xmp.empty());

  Exiv2::XmpKey key("Xmp.dc.title");
  auto v = makeAsciiValue("hello");

  EXPECT_NO_THROW({
    (void)xmp.add(key, v.get());
  });

  EXPECT_FALSE(xmp.empty());
  EXPECT_GE(xmp.count(), 1L);
}

TEST_F(XmpDataTest_1310, ClearAfterAddBecomesEmpty_1310) {
  Exiv2::XmpData xmp;

  Exiv2::XmpKey key("Xmp.dc.title");
  auto v = makeAsciiValue("hello");
  (void)xmp.add(key, v.get());

  ASSERT_FALSE(xmp.empty());
  ASSERT_GE(xmp.count(), 1L);

  EXPECT_NO_THROW(xmp.clear());

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
}

TEST_F(XmpDataTest_1310, EraseSingleElementMakesEmpty_1310) {
  Exiv2::XmpData xmp;

  Exiv2::XmpKey key("Xmp.dc.title");
  auto v = makeAsciiValue("hello");
  (void)xmp.add(key, v.get());

  ASSERT_FALSE(xmp.empty());
  ASSERT_GE(xmp.count(), 1L);

  auto it = xmp.begin();
  ASSERT_NE(it, xmp.end());

  EXPECT_NO_THROW({
    (void)xmp.erase(it);
  });

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
}

TEST_F(XmpDataTest_1310, EraseAllElementsBecomesEmpty_1310) {
  Exiv2::XmpData xmp;

  // Add two different keys so we can remove multiple entries.
  {
    Exiv2::XmpKey k1("Xmp.dc.title");
    auto v1 = makeAsciiValue("t");
    (void)xmp.add(k1, v1.get());
  }
  {
    Exiv2::XmpKey k2("Xmp.dc.description");
    auto v2 = makeAsciiValue("d");
    (void)xmp.add(k2, v2.get());
  }

  ASSERT_FALSE(xmp.empty());
  ASSERT_GE(xmp.count(), 1L);

  EXPECT_NO_THROW({
    while (!xmp.empty()) {
      auto it = xmp.begin();
      if (it == xmp.end()) break;  // Defensive: rely only on observable interface.
      (void)xmp.erase(it);
    }
  });

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
}

TEST_F(XmpDataTest_1310, EmptyReflectsStateAfterSortByKey_1310) {
  Exiv2::XmpData xmp;
  ASSERT_TRUE(xmp.empty());

  EXPECT_NO_THROW(xmp.sortByKey());
  EXPECT_TRUE(xmp.empty());

  Exiv2::XmpKey key("Xmp.dc.title");
  auto v = makeAsciiValue("hello");
  (void)xmp.add(key, v.get());

  ASSERT_FALSE(xmp.empty());
  EXPECT_NO_THROW(xmp.sortByKey());
  EXPECT_FALSE(xmp.empty());
  EXPECT_GE(xmp.count(), 1L);
}

TEST_F(XmpDataTest_1310, AddWithNullValueDoesNotMakeNonEmpty_1310) {
  Exiv2::XmpData xmp;
  ASSERT_TRUE(xmp.empty());

  Exiv2::XmpKey key("Xmp.dc.title");

  // We do not assume specific return codes or exception behavior;
  // only verify "empty()" remains unchanged if the call is accepted.
  EXPECT_NO_THROW({
    (void)xmp.add(key, nullptr);
  });

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
}

}  // namespace