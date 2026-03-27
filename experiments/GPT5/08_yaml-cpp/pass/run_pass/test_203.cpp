// TEST_ID: 203
#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

namespace {

TEST(IteratorBaseOperatorStarTest_203, SequenceBeginDereferenceReturnsFirstElement_203) {
  YAML::Node seq = YAML::Load("[one, two, three]");
  auto it = seq.begin();

  // Normal operation: dereference a valid sequence iterator yields a Node element.
  EXPECT_NO_THROW({
    YAML::Node v = *it;
    EXPECT_TRUE(v.IsScalar());
    EXPECT_EQ(v.as<std::string>(), "one");
  });
}

TEST(IteratorBaseOperatorStarTest_203, SequenceIteratorAfterIncrementDereferenceReturnsNextElement_203) {
  YAML::Node seq = YAML::Load("[1, 2]");
  auto it = seq.begin();
  ++it;

  // Boundary-ish: small sequence, dereference after increment.
  EXPECT_NO_THROW({
    YAML::Node v = *it;
    EXPECT_TRUE(v.IsScalar());
    EXPECT_EQ(v.as<int>(), 2);
  });
}

TEST(IteratorBaseOperatorStarTest_203, MapBeginDereferenceReturnsKeyValuePairNodes_203) {
  YAML::Node mp = YAML::Load("{a: 10, b: 20}");
  auto it = mp.begin();

  // Normal operation: dereference a valid map iterator yields a key/value pair of Nodes.
  EXPECT_NO_THROW({
    auto kv = *it;  // pair<Node, Node>
    EXPECT_TRUE(kv.first.IsScalar());
    EXPECT_TRUE(kv.second.IsScalar());

    // Verify key and value are readable via public Node API.
    const std::string key = kv.first.as<std::string>();
    const int value = kv.second.as<int>();

    EXPECT_TRUE(key == "a" || key == "b");
    EXPECT_TRUE(value == 10 || value == 20);
  });
}

TEST(IteratorBaseOperatorStarTest_203, MapIteratorCopyPreservesDereferenceResult_203) {
  YAML::Node mp = YAML::Load("{k: v}");
  auto it1 = mp.begin();
  auto it2 = it1;  // copy

  EXPECT_NO_THROW({
    auto kv1 = *it1;
    auto kv2 = *it2;

    EXPECT_EQ(kv1.first.as<std::string>(), "k");
    EXPECT_EQ(kv1.second.as<std::string>(), "v");

    EXPECT_EQ(kv2.first.as<std::string>(), "k");
    EXPECT_EQ(kv2.second.as<std::string>(), "v");
  });
}

TEST(IteratorBaseOperatorStarTest_203, ConstIteratorDereferenceWorksForSequence_203) {
  const YAML::Node seq = YAML::Load("[x]");
  auto it = seq.begin();

  EXPECT_NO_THROW({
    YAML::Node v = *it;
    EXPECT_TRUE(v.IsScalar());
    EXPECT_EQ(v.as<std::string>(), "x");
  });
}

}  // namespace