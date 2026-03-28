// File: test_xmpdata_add_key_value_1303.cpp
// TEST_ID: 1303

#include <gtest/gtest.h>

#include <exiv2/xmp_exiv2.hpp>
#include <exiv2/properties.hpp>
#include <exiv2/value.hpp>

#include <cstddef>
#include <memory>
#include <string>

namespace {

class XmpDataAddKeyValueTest_1303 : public ::testing::Test {
 protected:
  static Exiv2::Value::UniquePtr MakeStringValue(const std::string& s) {
    // Treat as a black box: create a Value via the public factory and populate it using public API.
    auto v = Exiv2::Value::create(Exiv2::asciiString);
    EXPECT_NE(v.get(), nullptr);
    EXPECT_NO_THROW(v->read(s));
    return v;
  }
};

TEST_F(XmpDataAddKeyValueTest_1303, AddSingleKeyIncreasesCountAndFindsKey_1303) {
  Exiv2::XmpData xmp;
  EXPECT_TRUE(xmp.empty());
  const long before = xmp.count();

  Exiv2::XmpKey key("Xmp.dc.title");
  auto v = MakeStringValue("hello");

  EXPECT_NO_THROW({
    (void)xmp.add(key, v.get());
  });

  EXPECT_FALSE(xmp.empty());
  EXPECT_EQ(xmp.count(), before + 1);

  const auto it = xmp.findKey(key);
  EXPECT_NE(it, xmp.end());
}

TEST_F(XmpDataAddKeyValueTest_1303, AddTwoDifferentKeysCountIncreasesByTwo_1303) {
  Exiv2::XmpData xmp;
  const long before = xmp.count();

  Exiv2::XmpKey key1("Xmp.dc.title");
  Exiv2::XmpKey key2("Xmp.xmp.CreatorTool");

  auto v1 = MakeStringValue("title");
  auto v2 = MakeStringValue("tool");

  EXPECT_NO_THROW({
    (void)xmp.add(key1, v1.get());
    (void)xmp.add(key2, v2.get());
  });

  EXPECT_EQ(xmp.count(), before + 2);
  EXPECT_NE(xmp.findKey(key1), xmp.end());
  EXPECT_NE(xmp.findKey(key2), xmp.end());
}

TEST_F(XmpDataAddKeyValueTest_1303, AddThenEraseRemovesOneEntryAndKeyNotFound_1303) {
  Exiv2::XmpData xmp;

  Exiv2::XmpKey key("Xmp.dc.title");
  auto v = MakeStringValue("erase-me");

  ASSERT_NO_THROW({ (void)xmp.add(key, v.get()); });
  ASSERT_FALSE(xmp.empty());
  const long afterAdd = xmp.count();
  ASSERT_GE(afterAdd, 1);

  auto it = xmp.findKey(key);
  ASSERT_NE(it, xmp.end());

  Exiv2::XmpData::iterator erasePos = xmp.erase(it);
  (void)erasePos;  // Return value is observable but not required for this behavior test.

  EXPECT_EQ(xmp.count(), afterAdd - 1);
  EXPECT_EQ(xmp.findKey(key), xmp.end());
}

TEST_F(XmpDataAddKeyValueTest_1303, AddThenClearMakesEmptyAndBeginEqualsEnd_1303) {
  Exiv2::XmpData xmp;

  Exiv2::XmpKey key("Xmp.dc.title");
  auto v = MakeStringValue("clear-me");

  ASSERT_NO_THROW({ (void)xmp.add(key, v.get()); });
  ASSERT_FALSE(xmp.empty());
  ASSERT_GT(xmp.count(), 0);

  EXPECT_NO_THROW(xmp.clear());

  EXPECT_TRUE(xmp.empty());
  EXPECT_EQ(xmp.count(), 0);
  EXPECT_EQ(xmp.begin(), xmp.end());
  EXPECT_EQ(xmp.findKey(key), xmp.end());
}

TEST_F(XmpDataAddKeyValueTest_1303, AddWithNullValueEitherThrowsOrDoesNotChangeCount_1303) {
  Exiv2::XmpData xmp;
  const long before = xmp.count();

  Exiv2::XmpKey key("Xmp.dc.title");

  bool threw = false;
  try {
    (void)xmp.add(key, nullptr);
  } catch (...) {
    threw = true;
  }

  // Black-box friendly: accept either behavior, but if it *doesn't* throw,
  // the observable container state should remain well-defined.
  if (!threw) {
    EXPECT_EQ(xmp.count(), before);
    // If no throw, the key may or may not exist depending on implementation;
    // we only assert that the call didn't silently corrupt iteration invariants.
    EXPECT_NO_THROW({
      (void)xmp.begin();
      (void)xmp.end();
    });
  } else {
    EXPECT_EQ(xmp.count(), before);
  }
}

}  // namespace