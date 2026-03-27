// TEST_ID: 681
// File: ./TestProjects/yaml-cpp/test/nodeevents_test_681.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <string>

#include "yaml-cpp/yaml.h"          // YAML::Node, YAML::Emitter, YAML::Dump
#include "yaml-cpp/nodeevents.h"    // YAML::NodeEvents

namespace {

class NodeEventsTest_681 : public ::testing::Test {
 protected:
  static std::string EmitViaNodeEvents(const YAML::Node& node) {
    YAML::NodeEvents events(node);
    YAML::Emitter out;
    events.Emit(out);
    return std::string(out.c_str());
  }
};

TEST_F(NodeEventsTest_681, NonCopyableNonMovable_681) {
  static_assert(!std::is_copy_constructible<YAML::NodeEvents>::value,
                "NodeEvents must not be copy constructible");
  static_assert(!std::is_copy_assignable<YAML::NodeEvents>::value,
                "NodeEvents must not be copy assignable");
  static_assert(!std::is_move_constructible<YAML::NodeEvents>::value,
                "NodeEvents must not be move constructible");
  static_assert(!std::is_move_assignable<YAML::NodeEvents>::value,
                "NodeEvents must not be move assignable");
}

TEST_F(NodeEventsTest_681, DefaultNodeEmitMatchesDump_681) {
  const YAML::Node node;  // default constructed
  EXPECT_NO_THROW({
    const std::string emitted = EmitViaNodeEvents(node);
    const std::string dumped = YAML::Dump(node);
    EXPECT_EQ(emitted, dumped);
  });
}

TEST_F(NodeEventsTest_681, ScalarNodeEmitMatchesDump_681) {
  YAML::Node node("hello");
  EXPECT_NO_THROW({
    const std::string emitted = EmitViaNodeEvents(node);
    const std::string dumped = YAML::Dump(node);
    EXPECT_EQ(emitted, dumped);
  });
}

TEST_F(NodeEventsTest_681, SequenceNodeEmitMatchesDump_681) {
  YAML::Node node(YAML::NodeType::Sequence);
  node.push_back(1);
  node.push_back(2);
  node.push_back(3);

  EXPECT_NO_THROW({
    const std::string emitted = EmitViaNodeEvents(node);
    const std::string dumped = YAML::Dump(node);
    EXPECT_EQ(emitted, dumped);
  });
}

TEST_F(NodeEventsTest_681, MapNodeEmitMatchesDump_681) {
  YAML::Node node(YAML::NodeType::Map);
  node["a"] = 1;
  node["b"] = "two";
  node["c"] = true;

  EXPECT_NO_THROW({
    const std::string emitted = EmitViaNodeEvents(node);
    const std::string dumped = YAML::Dump(node);
    EXPECT_EQ(emitted, dumped);
  });
}

TEST_F(NodeEventsTest_681, NestedNodeEmitMatchesDump_681) {
  YAML::Node node(YAML::NodeType::Map);
  node["name"] = "test";
  node["items"] = YAML::Node(YAML::NodeType::Sequence);
  node["items"].push_back("x");
  node["items"].push_back("y");

  YAML::Node inner(YAML::NodeType::Map);
  inner["k"] = "v";
  node["inner"] = inner;

  EXPECT_NO_THROW({
    const std::string emitted = EmitViaNodeEvents(node);
    const std::string dumped = YAML::Dump(node);
    EXPECT_EQ(emitted, dumped);
  });
}

TEST_F(NodeEventsTest_681, AliasedNodeEmitMatchesDump_681) {
  // Create a structure that is likely to trigger alias/anchor emission if supported.
  YAML::Node shared(YAML::NodeType::Map);
  shared["value"] = 42;

  YAML::Node root(YAML::NodeType::Map);
  root["first"] = shared;
  root["second"] = shared;

  EXPECT_NO_THROW({
    const std::string emitted = EmitViaNodeEvents(root);
    const std::string dumped = YAML::Dump(root);
    EXPECT_EQ(emitted, dumped);
  });
}

}  // namespace