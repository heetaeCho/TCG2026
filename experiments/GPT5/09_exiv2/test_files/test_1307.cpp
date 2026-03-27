// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmpdata_sortbykey_1307.cpp

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

#include <exiv2/value.hpp>
#include <exiv2/xmp_exiv2.hpp>

namespace {

class XmpDataSortByKeyTest_1307 : public ::testing::Test {
 protected:
  static void AddTextValue(Exiv2::XmpData& xmp, const std::string& keyStr, const std::string& valueStr) {
    const Exiv2::XmpKey key(keyStr);

    Exiv2::Value::UniquePtr v(Exiv2::Value::create(Exiv2::xmpText));
    ASSERT_TRUE(v.get() != nullptr);
    ASSERT_NO_THROW(v->read(valueStr));

    // Do not assume a specific success code; require "non-error" (commonly 0 in Exiv2).
    const int rc = xmp.add(key, v.get());
    EXPECT_GE(rc, 0);
  }

  static std::vector<std::string> KeysInOrder(const Exiv2::XmpData& xmp) {
    std::vector<std::string> keys;
    for (auto it = xmp.begin(); it != xmp.end(); ++it) {
      keys.push_back(it->key());
    }
    return keys;
  }

  static std::vector<std::string> ValuesInOrder(const Exiv2::XmpData& xmp) {
    std::vector<std::string> values;
    for (auto it = xmp.begin(); it != xmp.end(); ++it) {
      values.push_back(it->toString());
    }
    return values;
  }

  static bool IsNonDecreasing(const std::vector<std::string>& v) {
    return std::is_sorted(v.begin(), v.end());
  }
};

TEST_F(XmpDataSortByKeyTest_1307, SortByKey_Empty_NoCrashAndStillEmpty_1307) {
  Exiv2::XmpData xmp;
  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());

  EXPECT_NO_THROW(xmp.sortByKey());

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(0L, xmp.count());
  EXPECT_EQ(xmp.begin(), xmp.end());
}

TEST_F(XmpDataSortByKeyTest_1307, SortByKey_SingleElement_RemainsAccessible_1307) {
  Exiv2::XmpData xmp;
  AddTextValue(xmp, "Xmp.dc.title", "t");

  ASSERT_FALSE(xmp.empty());
  ASSERT_EQ(1L, xmp.count());

  const auto beforeKeys = KeysInOrder(xmp);
  const auto beforeVals = ValuesInOrder(xmp);

  ASSERT_EQ(1u, beforeKeys.size());
  ASSERT_EQ(1u, beforeVals.size());

  EXPECT_NO_THROW(xmp.sortByKey());

  EXPECT_EQ(1L, xmp.count());
  EXPECT_FALSE(xmp.empty());

  const auto afterKeys = KeysInOrder(xmp);
  const auto afterVals = ValuesInOrder(xmp);

  EXPECT_EQ(beforeKeys, afterKeys);
  EXPECT_EQ(beforeVals, afterVals);

  // Still findable after sort
  const auto it = xmp.findKey(Exiv2::XmpKey("Xmp.dc.title"));
  ASSERT_NE(it, xmp.end());
  EXPECT_EQ("Xmp.dc.title", it->key());
  EXPECT_EQ("t", it->toString());
}

TEST_F(XmpDataSortByKeyTest_1307, SortByKey_MultipleKeys_BecomesNonDecreasingByKey_1307) {
  Exiv2::XmpData xmp;

  // Intentionally add in reverse-ish / mixed order to make sorting observable.
  AddTextValue(xmp, "Xmp.z.zeta", "z");
  AddTextValue(xmp, "Xmp.a.alpha", "a");
  AddTextValue(xmp, "Xmp.m.mu", "m");
  AddTextValue(xmp, "Xmp.b.beta", "b");

  ASSERT_EQ(4L, xmp.count());

  const auto beforeKeys = KeysInOrder(xmp);
  ASSERT_EQ(4u, beforeKeys.size());

  EXPECT_NO_THROW(xmp.sortByKey());

  const auto afterKeys = KeysInOrder(xmp);
  ASSERT_EQ(4u, afterKeys.size());

  EXPECT_TRUE(IsNonDecreasing(afterKeys));

  // Sorting should not lose entries: all original keys must still be present and findable.
  for (const auto& k : beforeKeys) {
    const auto it = xmp.findKey(Exiv2::XmpKey(k));
    EXPECT_NE(it, xmp.end()) << "Key not found after sort: " << k;
    if (it != xmp.end()) {
      EXPECT_EQ(k, it->key());
    }
  }
}

TEST_F(XmpDataSortByKeyTest_1307, SortByKey_PreservesValuesAssociatedWithKeys_1307) {
  Exiv2::XmpData xmp;

  AddTextValue(xmp, "Xmp.dc.title", "TITLE");
  AddTextValue(xmp, "Xmp.dc.creator", "CREATOR");
  AddTextValue(xmp, "Xmp.dc.description", "DESCRIPTION");

  ASSERT_EQ(3L, xmp.count());

  // Snapshot key->stringified value via findKey (observable public interface).
  const struct KV {
    const char* key;
    const char* val;
  } expected[] = {
      {"Xmp.dc.title", "TITLE"},
      {"Xmp.dc.creator", "CREATOR"},
      {"Xmp.dc.description", "DESCRIPTION"},
  };

  for (const auto& e : expected) {
    auto it = xmp.findKey(Exiv2::XmpKey(e.key));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(std::string(e.key), it->key());
    EXPECT_EQ(std::string(e.val), it->toString());
  }

  EXPECT_NO_THROW(xmp.sortByKey());

  // Values for the same keys should remain the same after sorting.
  for (const auto& e : expected) {
    auto it = xmp.findKey(Exiv2::XmpKey(e.key));
    ASSERT_NE(it, xmp.end());
    EXPECT_EQ(std::string(e.key), it->key());
    EXPECT_EQ(std::string(e.val), it->toString());
  }

  // And iteration order should be sorted by key.
  const auto afterKeys = KeysInOrder(xmp);
  EXPECT_TRUE(IsNonDecreasing(afterKeys));
}

TEST_F(XmpDataSortByKeyTest_1307, SortByKey_Idempotent_WhenCalledTwice_OrderUnchanged_1307) {
  Exiv2::XmpData xmp;

  AddTextValue(xmp, "Xmp.z.zeta", "z");
  AddTextValue(xmp, "Xmp.a.alpha", "a");
  AddTextValue(xmp, "Xmp.m.mu", "m");

  ASSERT_EQ(3L, xmp.count());

  EXPECT_NO_THROW(xmp.sortByKey());
  const auto onceKeys = KeysInOrder(xmp);
  const auto onceVals = ValuesInOrder(xmp);

  EXPECT_TRUE(IsNonDecreasing(onceKeys));

  EXPECT_NO_THROW(xmp.sortByKey());
  const auto twiceKeys = KeysInOrder(xmp);
  const auto twiceVals = ValuesInOrder(xmp);

  EXPECT_EQ(onceKeys, twiceKeys);
  EXPECT_EQ(onceVals, twiceVals);
}

}  // namespace