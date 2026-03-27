// Dict_getVal_tests_115.cpp
#include <gtest/gtest.h>

#include "poppler/Dict.h"
#include "poppler/Object.h"

#include <string>
#include <utility>

namespace {

class DictTest_115 : public ::testing::Test {
protected:
  DictTest_115() : dict_(nullptr) {} // XRef* is not needed for non-ref Objects in these tests.

  // Helper: find the index for a given key using only the public interface.
  int FindIndexByKey(const std::string &key) const {
    const int n = dict_.getLength();
    for (int i = 0; i < n; ++i) {
      const char *k = dict_.getKey(i);
      if (k && key == k) {
        return i;
      }
    }
    return -1;
  }

  Dict dict_;
};

TEST_F(DictTest_115, EmptyDictHasZeroLength_115) {
  EXPECT_EQ(dict_.getLength(), 0);
}

TEST_F(DictTest_115, GetValReturnsAddedValuesByIndex_115) {
  dict_.add("A", Object(123));
  dict_.add("B", Object(true));
  dict_.add("C", Object(std::string("hello")));

  ASSERT_EQ(dict_.getLength(), 3);

  Object v0 = dict_.getVal(0);
  Object v1 = dict_.getVal(1);
  Object v2 = dict_.getVal(2);

  EXPECT_TRUE(v0.isInt());
  EXPECT_EQ(v0.getInt(), 123);

  EXPECT_TRUE(v1.isBool());
  EXPECT_EQ(v1.getBool(), true);

  EXPECT_TRUE(v2.isString());
  ASSERT_NE(v2.getString(), nullptr);
  // We intentionally avoid depending on GooString's API; just validate it's a string object.
}

TEST_F(DictTest_115, GetValWorksForFirstAndLastIndex_115) {
  dict_.add("First", Object(1));
  dict_.add("Second", Object(2));

  const int n = dict_.getLength();
  ASSERT_EQ(n, 2);

  Object first = dict_.getVal(0);
  Object last = dict_.getVal(n - 1);

  EXPECT_TRUE(first.isInt());
  EXPECT_TRUE(last.isInt());
  EXPECT_EQ(first.getInt(), 1);
  EXPECT_EQ(last.getInt(), 2);
}

TEST_F(DictTest_115, GetValReflectsSetOnExistingKey_115) {
  dict_.add("K", Object(10));
  dict_.add("Other", Object(99));
  ASSERT_EQ(dict_.getLength(), 2);

  dict_.set("K", Object(42));

  const int idx = FindIndexByKey("K");
  ASSERT_GE(idx, 0);

  Object v = dict_.getVal(idx);
  EXPECT_TRUE(v.isInt());
  EXPECT_EQ(v.getInt(), 42);
}

TEST_F(DictTest_115, GetValMatchesKeysAfterRemove_115) {
  dict_.add("A", Object(1));
  dict_.add("B", Object(2));
  dict_.add("C", Object(3));
  ASSERT_EQ(dict_.getLength(), 3);

  dict_.remove("B");
  ASSERT_EQ(dict_.getLength(), 2);

  // Verify remaining entries via key->value mapping, using only public API.
  for (int i = 0; i < dict_.getLength(); ++i) {
    const char *k = dict_.getKey(i);
    ASSERT_NE(k, nullptr);

    Object v = dict_.getVal(i);
    ASSERT_TRUE(v.isInt());

    const std::string key(k);
    if (key == "A") {
      EXPECT_EQ(v.getInt(), 1);
    } else if (key == "C") {
      EXPECT_EQ(v.getInt(), 3);
    } else {
      FAIL() << "Unexpected key after removal: " << key;
    }
  }
}

TEST_F(DictTest_115, GetValDoesNotChangeLengthOrKeys_115) {
  dict_.add("X", Object(7));
  dict_.add("Y", Object(8));
  ASSERT_EQ(dict_.getLength(), 2);

  const std::string k0_before = dict_.getKey(0) ? dict_.getKey(0) : "";
  const std::string k1_before = dict_.getKey(1) ? dict_.getKey(1) : "";

  (void)dict_.getVal(0);
  (void)dict_.getVal(1);

  EXPECT_EQ(dict_.getLength(), 2);
  const std::string k0_after = dict_.getKey(0) ? dict_.getKey(0) : "";
  const std::string k1_after = dict_.getKey(1) ? dict_.getKey(1) : "";

  EXPECT_EQ(k0_after, k0_before);
  EXPECT_EQ(k1_after, k1_before);
}

} // namespace