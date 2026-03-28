// Dict_getKey_114_test.cpp
#include <gtest/gtest.h>

#include <algorithm>
#include <set>
#include <string>
#include <vector>

#include "Dict.h"
#include "Object.h"

namespace {

class DictGetKeyTest_114 : public ::testing::Test {
protected:
  static Object MakeDefaultObject() {
    // Treat Object as a black box: rely only on it being movable.
    // In Poppler, Object is typically default-constructible to a null/empty object.
    return Object();
  }

  static void AddKey(Dict& dict, const std::string& key) {
    Object v = MakeDefaultObject();
    dict.add(key, std::move(v));
  }

  static std::multiset<std::string> CollectKeys(const Dict& dict) {
    std::multiset<std::string> out;
    const int n = dict.getLength();
    for (int i = 0; i < n; ++i) {
      const char* k = dict.getKey(i);
      ASSERT_NE(k, nullptr);
      out.insert(std::string(k));
    }
    return out;
  }
};

TEST_F(DictGetKeyTest_114, EmptyDict_HasZeroLength_114) {
  Dict dict(nullptr);
  EXPECT_EQ(dict.getLength(), 0);
}

TEST_F(DictGetKeyTest_114, AfterAddingUniqueKeys_GetKeyReturnsAllKeys_114) {
  Dict dict(nullptr);

  const std::vector<std::string> keys = {"A", "B", "C"};
  for (const auto& k : keys) AddKey(dict, k);

  EXPECT_EQ(dict.getLength(), static_cast<int>(keys.size()));

  const auto got = CollectKeys(dict);
  const std::multiset<std::string> expected(keys.begin(), keys.end());
  EXPECT_EQ(got, expected);
}

TEST_F(DictGetKeyTest_114, Boundary_FirstAndLastIndex_ReturnNonNullKeys_114) {
  Dict dict(nullptr);
  AddKey(dict, "first");
  AddKey(dict, "middle");
  AddKey(dict, "last");

  ASSERT_EQ(dict.getLength(), 3);

  const char* k0 = dict.getKey(0);
  const char* k2 = dict.getKey(2);

  ASSERT_NE(k0, nullptr);
  ASSERT_NE(k2, nullptr);

  // We don't assume ordering; just that returned keys are among those inserted.
  const std::set<std::string> expected = {"first", "middle", "last"};
  EXPECT_TRUE(expected.count(std::string(k0)) > 0);
  EXPECT_TRUE(expected.count(std::string(k2)) > 0);
}

TEST_F(DictGetKeyTest_114, RemoveKey_ThenGetKeyDoesNotReturnRemovedKey_114) {
  Dict dict(nullptr);
  AddKey(dict, "keep1");
  AddKey(dict, "remove_me");
  AddKey(dict, "keep2");

  ASSERT_EQ(dict.getLength(), 3);

  dict.remove("remove_me");

  EXPECT_EQ(dict.getLength(), 2);

  const auto got = CollectKeys(dict);
  EXPECT_EQ(got.count("remove_me"), 0);
  EXPECT_EQ(got.count("keep1"), 1);
  EXPECT_EQ(got.count("keep2"), 1);
}

TEST_F(DictGetKeyTest_114, SetExistingKey_DoesNotIncreaseLength_114) {
  Dict dict(nullptr);
  AddKey(dict, "K");

  ASSERT_EQ(dict.getLength(), 1);
  ASSERT_TRUE(dict.hasKey("K"));

  // Replace value for existing key (observable expectation: key set remains same, length unchanged).
  Object v = MakeDefaultObject();
  dict.set("K", std::move(v));

  EXPECT_EQ(dict.getLength(), 1);

  const auto got = CollectKeys(dict);
  EXPECT_EQ(got.size(), 1u);
  EXPECT_EQ(*got.begin(), "K");
}

TEST_F(DictGetKeyTest_114, AddEmptyStringKey_GetKeyCanReturnEmptyString_114) {
  Dict dict(nullptr);
  AddKey(dict, "");
  AddKey(dict, "nonempty");

  ASSERT_EQ(dict.getLength(), 2);

  const auto got = CollectKeys(dict);
  EXPECT_EQ(got.count(""), 1);
  EXPECT_EQ(got.count("nonempty"), 1);
}

TEST_F(DictGetKeyTest_114, AddVeryLongKey_GetKeyReturnsSameContents_114) {
  Dict dict(nullptr);

  std::string longKey(4096, 'x');
  AddKey(dict, longKey);
  AddKey(dict, "short");

  ASSERT_EQ(dict.getLength(), 2);

  const auto got = CollectKeys(dict);
  EXPECT_EQ(got.count(longKey), 1);
  EXPECT_EQ(got.count("short"), 1);
}

}  // namespace