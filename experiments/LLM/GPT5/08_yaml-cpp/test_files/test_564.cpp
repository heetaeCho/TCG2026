// TEST_ID: 564
// File: node_operator_assign_test_564.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/yaml.h"  // Prefer top-level include if available in your codebase.

namespace {

class NodeAssignmentTest_564 : public ::testing::Test {
protected:
  static YAML::Node MakeSeq_564(std::initializer_list<int> values) {
    YAML::Node n(YAML::NodeType::Sequence);
    for (int v : values) n.push_back(v);
    return n;
  }

  static YAML::Node MakeMap_564(std::initializer_list<std::pair<std::string, int>> kvs) {
    YAML::Node n(YAML::NodeType::Map);
    for (const auto& kv : kvs) n.force_insert(kv.first, kv.second);
    return n;
  }
};

TEST_F(NodeAssignmentTest_564, AssignReturnsLhsReference_564) {
  YAML::Node lhs("lhs");
  YAML::Node rhs("rhs");

  YAML::Node& ret = (lhs = rhs);

  EXPECT_EQ(&ret, &lhs);
}

TEST_F(NodeAssignmentTest_564, AssignCopiesScalarAndMetadata_564) {
  YAML::Node rhs("hello");
  rhs.SetTag("!customTag");
  rhs.SetStyle(YAML::EmitterStyle::Flow);

  YAML::Node lhs("world");
  lhs.SetTag("!otherTag");
  lhs.SetStyle(YAML::EmitterStyle::Block);

  lhs = rhs;

  EXPECT_EQ(lhs.IsDefined(), rhs.IsDefined());
  EXPECT_EQ(lhs.Type(), rhs.Type());
  EXPECT_TRUE(lhs.IsScalar());
  EXPECT_EQ(lhs.Scalar(), rhs.Scalar());
  EXPECT_EQ(lhs.Tag(), rhs.Tag());
  EXPECT_EQ(lhs.Style(), rhs.Style());
}

TEST_F(NodeAssignmentTest_564, AssignCopiesSequenceContents_564) {
  YAML::Node rhs = MakeSeq_564({1, 2, 3});

  YAML::Node lhs = MakeMap_564({{"k", 9}});
  ASSERT_TRUE(lhs.IsMap());

  lhs = rhs;

  EXPECT_TRUE(lhs.IsSequence());
  EXPECT_EQ(lhs.size(), rhs.size());
  ASSERT_EQ(lhs.size(), 3u);

  EXPECT_EQ(lhs[0].as<int>(), 1);
  EXPECT_EQ(lhs[1].as<int>(), 2);
  EXPECT_EQ(lhs[2].as<int>(), 3);
}

TEST_F(NodeAssignmentTest_564, AssignCopiesMapContents_564) {
  YAML::Node rhs = MakeMap_564({{"a", 1}, {"b", 2}});
  rhs.SetTag("!mapTag");
  rhs.SetStyle(YAML::EmitterStyle::Block);

  YAML::Node lhs = MakeSeq_564({7, 8});
  ASSERT_TRUE(lhs.IsSequence());

  lhs = rhs;

  EXPECT_TRUE(lhs.IsMap());
  EXPECT_EQ(lhs.size(), rhs.size());
  ASSERT_EQ(lhs.size(), 2u);

  EXPECT_EQ(lhs["a"].as<int>(), 1);
  EXPECT_EQ(lhs["b"].as<int>(), 2);
  EXPECT_EQ(lhs.Tag(), rhs.Tag());
  EXPECT_EQ(lhs.Style(), rhs.Style());
}

TEST_F(NodeAssignmentTest_564, SelfAssignmentKeepsObservableState_564) {
  YAML::Node n = MakeMap_564({{"x", 10}, {"y", 20}});
  n.SetTag("!self");
  n.SetStyle(YAML::EmitterStyle::Flow);

  const bool was_defined = n.IsDefined();
  const auto was_type = n.Type();
  const std::string was_tag = n.Tag();
  const auto was_style = n.Style();
  const std::size_t was_size = n.size();
  const int x_before = n["x"].as<int>();
  const int y_before = n["y"].as<int>();

  YAML::Node& ret = (n = n);

  EXPECT_EQ(&ret, &n);
  EXPECT_EQ(n.IsDefined(), was_defined);
  EXPECT_EQ(n.Type(), was_type);
  EXPECT_EQ(n.Tag(), was_tag);
  EXPECT_EQ(n.Style(), was_style);
  EXPECT_EQ(n.size(), was_size);
  EXPECT_EQ(n["x"].as<int>(), x_before);
  EXPECT_EQ(n["y"].as<int>(), y_before);
}

TEST_F(NodeAssignmentTest_564, AssignFromDefaultNodeMatchesRhsObservables_564) {
  YAML::Node rhs;  // default-constructed
  YAML::Node lhs("not default");

  lhs = rhs;

  // Avoid assuming what "default" means in this codebase; just require lhs matches rhs.
  EXPECT_EQ(lhs.IsDefined(), rhs.IsDefined());
  EXPECT_EQ(static_cast<bool>(lhs), static_cast<bool>(rhs));
  EXPECT_EQ(lhs.Type(), rhs.Type());

  // If both are scalar, their scalar values should match; otherwise we don't force it.
  if (lhs.IsScalar() && rhs.IsScalar()) {
    EXPECT_EQ(lhs.Scalar(), rhs.Scalar());
  }
}

TEST_F(NodeAssignmentTest_564, ChainedAssignmentWorksAndReturnsLeftmost_564) {
  YAML::Node a("a");
  YAML::Node b("b");
  YAML::Node c("c");

  YAML::Node& ret = (a = (b = c));

  EXPECT_EQ(&ret, &a);
  EXPECT_TRUE(a.IsScalar());
  EXPECT_TRUE(b.IsScalar());
  EXPECT_EQ(a.Scalar(), "c");
  EXPECT_EQ(b.Scalar(), "c");
  EXPECT_EQ(c.Scalar(), "c");
}

}  // namespace