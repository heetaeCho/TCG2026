// TEST_ID: 569
#include <gtest/gtest.h>

#include <string>
#include <yaml-cpp/yaml.h>

namespace {

class NodePushBackTemplateTest_569 : public ::testing::Test {
protected:
  // Helper: create an "invalid" (Zombie) node through observable public API.
  // In yaml-cpp, indexing a missing key on an undefined/missing map entry
  // commonly yields an invalid node that throws InvalidNode on mutations.
  static YAML::Node MakeInvalidNode_569() {
    YAML::Node root;                 // default-constructed
    YAML::Node missing = root["no_such_key_569"];  // typically invalid (zombie)
    return missing;
  }
};

TEST_F(NodePushBackTemplateTest_569, PushBackOnSequenceAppendsScalarInt_569) {
  YAML::Node seq(YAML::NodeType::Sequence);

  EXPECT_EQ(seq.size(), 0u);
  EXPECT_NO_THROW(seq.push_back(42));  // exercises template push_back<T>

  EXPECT_EQ(seq.size(), 1u);
  EXPECT_TRUE(seq.IsSequence());

  // Verify the appended value is observable through public API.
  ASSERT_NO_THROW(seq[0].as<int>());
  EXPECT_EQ(seq[0].as<int>(), 42);
}

TEST_F(NodePushBackTemplateTest_569, PushBackOnNullNodeCreatesSequenceAndAppends_569) {
  YAML::Node n;  // default node (commonly Null/Undefined depending on yaml-cpp usage)

  // We only assert observable post-conditions after push_back.
  EXPECT_NO_THROW(n.push_back(1));  // template push_back<T>

  EXPECT_TRUE(n.IsSequence());
  EXPECT_EQ(n.size(), 1u);
  EXPECT_EQ(n[0].as<int>(), 1);
}

TEST_F(NodePushBackTemplateTest_569, PushBackStdStringAppendsScalarString_569) {
  YAML::Node seq(YAML::NodeType::Sequence);

  const std::string s = "hello_569";
  EXPECT_NO_THROW(seq.push_back(s));  // template push_back<T>

  EXPECT_EQ(seq.size(), 1u);
  EXPECT_EQ(seq[0].as<std::string>(), "hello_569");
}

TEST_F(NodePushBackTemplateTest_569, PushBackCStringAppendsScalarString_569) {
  YAML::Node seq(YAML::NodeType::Sequence);

  EXPECT_NO_THROW(seq.push_back("cstr_569"));  // template push_back<T> with const char*

  EXPECT_EQ(seq.size(), 1u);
  EXPECT_EQ(seq[0].as<std::string>(), "cstr_569");
}

TEST_F(NodePushBackTemplateTest_569, PushBackMultipleValuesPreservesOrder_569) {
  YAML::Node seq(YAML::NodeType::Sequence);

  EXPECT_NO_THROW(seq.push_back(1));
  EXPECT_NO_THROW(seq.push_back(2));
  EXPECT_NO_THROW(seq.push_back(3));

  EXPECT_EQ(seq.size(), 3u);
  EXPECT_EQ(seq[0].as<int>(), 1);
  EXPECT_EQ(seq[1].as<int>(), 2);
  EXPECT_EQ(seq[2].as<int>(), 3);
}

TEST_F(NodePushBackTemplateTest_569, PushBackOnInvalidNodeThrowsInvalidNode_569) {
  YAML::Node invalid = MakeInvalidNode_569();

  // The template implementation explicitly throws InvalidNode when !m_isValid.
  EXPECT_THROW(invalid.push_back(1), YAML::InvalidNode);
}

TEST_F(NodePushBackTemplateTest_569, PushBackOnInvalidNodeThrowsForDifferentTypes_569) {
  YAML::Node invalid = MakeInvalidNode_569();

  EXPECT_THROW(invalid.push_back(std::string("x_569")), YAML::InvalidNode);
  EXPECT_THROW(invalid.push_back("y_569"), YAML::InvalidNode);
}

}  // namespace