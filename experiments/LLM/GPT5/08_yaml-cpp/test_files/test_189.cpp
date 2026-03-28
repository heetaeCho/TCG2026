// test_node_iterator_increment_until_defined_189.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

TEST(NodeIteratorIncrementUntilDefinedTest_189, MixedDefinedAndUndefinedValues_IteratesOnlyDefinedValues_189) {
  YAML::Node m(YAML::NodeType::Map);

  // Create keys with a mix of defined/undefined values.
  m["a"] = YAML::Node();               // Undefined
  m["b"] = 123;                        // Defined scalar
  m["c"] = YAML::Node();               // Undefined

  // Sanity: the nodes we intended to be undefined should be observable as such.
  EXPECT_FALSE(m["a"].IsDefined());
  EXPECT_TRUE(m["b"].IsDefined());
  EXPECT_FALSE(m["c"].IsDefined());

  std::vector<std::string> keys_seen;
  for (auto it = m.begin(); it != m.end(); ++it) {
    // Observable behavior expected from the iterator: it should not yield
    // entries whose value is not defined.
    EXPECT_TRUE(it->second.IsDefined());

    // Record which keys are yielded.
    keys_seen.push_back(it->first.as<std::string>());
  }

  // Only the defined entry should be visited.
  ASSERT_EQ(keys_seen.size(), 1u);
  EXPECT_EQ(keys_seen[0], "b");
}

TEST(NodeIteratorIncrementUntilDefinedTest_189, AllUndefinedValues_BeginEqualsEnd_189) {
  YAML::Node m(YAML::NodeType::Map);

  m["x"] = YAML::Node();
  m["y"] = YAML::Node();
  m["z"] = YAML::Node();

  EXPECT_FALSE(m["x"].IsDefined());
  EXPECT_FALSE(m["y"].IsDefined());
  EXPECT_FALSE(m["z"].IsDefined());

  // If all entries are undefined, iteration should yield nothing.
  EXPECT_TRUE(m.begin() == m.end());
}

TEST(NodeIteratorIncrementUntilDefinedTest_189, NoUndefinedValues_IteratesAllEntries_189) {
  YAML::Node m(YAML::NodeType::Map);

  m["k1"] = 1;
  m["k2"] = "v2";
  m["k3"] = 3.14;

  EXPECT_TRUE(m["k1"].IsDefined());
  EXPECT_TRUE(m["k2"].IsDefined());
  EXPECT_TRUE(m["k3"].IsDefined());

  std::vector<std::string> keys_seen;
  size_t count = 0;
  for (auto it = m.begin(); it != m.end(); ++it) {
    EXPECT_TRUE(it->second.IsDefined());
    keys_seen.push_back(it->first.as<std::string>());
    ++count;
  }

  EXPECT_EQ(count, 3u);

  // Order is not specified for YAML::Node iteration in a black-box sense,
  // so just verify that all expected keys are present.
  auto has = [&](const std::string& k) {
    return std::find(keys_seen.begin(), keys_seen.end(), k) != keys_seen.end();
  };
  EXPECT_TRUE(has("k1"));
  EXPECT_TRUE(has("k2"));
  EXPECT_TRUE(has("k3"));
}

TEST(NodeIteratorIncrementUntilDefinedTest_189, SingleUndefinedEntry_BeginEqualsEnd_189) {
  YAML::Node m(YAML::NodeType::Map);

  m["only"] = YAML::Node();
  EXPECT_FALSE(m["only"].IsDefined());

  EXPECT_TRUE(m.begin() == m.end());
}

}  // namespace