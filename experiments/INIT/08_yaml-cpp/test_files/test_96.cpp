// TEST_ID: 96
#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include <yaml-cpp/yaml.h>

namespace {

class EmitOperatorTest_96 : public ::testing::Test {
protected:
  static std::string EmitViaStreamOperator(const YAML::Node& node) {
    std::stringstream ss;
    // Under test: YAML::operator<<(std::ostream&, const Node&)
    ss << node;
    return ss.str();
  }

  static std::string EmitViaEmitterToStream(const YAML::Node& node) {
    std::stringstream ss;
    YAML::Emitter emitter(ss);
    emitter << node;
    return ss.str();
  }
};

TEST_F(EmitOperatorTest_96, ReturnsSameStreamReference_96) {
  std::stringstream ss;
  YAML::Node n("hello");

  std::ostream& ret = (ss << n);

  EXPECT_EQ(&ret, static_cast<std::ostream*>(&ss));
}

TEST_F(EmitOperatorTest_96, ScalarNodeMatchesDirectEmitterOutput_96) {
  YAML::Node n("hello");

  const std::string via_op = EmitViaStreamOperator(n);
  const std::string via_emitter = EmitViaEmitterToStream(n);

  EXPECT_EQ(via_op, via_emitter);
  EXPECT_FALSE(via_op.empty());
}

TEST_F(EmitOperatorTest_96, NullNodeMatchesDirectEmitterOutput_96) {
  YAML::Node n(YAML::NodeType::Null);

  const std::string via_op = EmitViaStreamOperator(n);
  const std::string via_emitter = EmitViaEmitterToStream(n);

  EXPECT_EQ(via_op, via_emitter);
}

TEST_F(EmitOperatorTest_96, SequenceNodeMatchesDirectEmitterOutput_96) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(1);
  seq.push_back("two");
  seq.push_back(true);

  const std::string via_op = EmitViaStreamOperator(seq);
  const std::string via_emitter = EmitViaEmitterToStream(seq);

  EXPECT_EQ(via_op, via_emitter);
  EXPECT_FALSE(via_op.empty());
}

TEST_F(EmitOperatorTest_96, MapNodeMatchesDirectEmitterOutput_96) {
  YAML::Node map(YAML::NodeType::Map);
  map["a"] = 1;
  map["b"] = "two";

  const std::string via_op = EmitViaStreamOperator(map);
  const std::string via_emitter = EmitViaEmitterToStream(map);

  EXPECT_EQ(via_op, via_emitter);
  EXPECT_FALSE(via_op.empty());
}

TEST_F(EmitOperatorTest_96, UndefinedOrMissingChildNodeDoesNotThrowAndMatchesEmitter_96) {
  YAML::Node map(YAML::NodeType::Map);
  map["present"] = 123;

  // Accessing a missing key yields some Node object; behavior is defined by yaml-cpp.
  const YAML::Node missing = map["missing_key"];

  EXPECT_NO_THROW({
    const std::string via_op = EmitViaStreamOperator(missing);
    const std::string via_emitter = EmitViaEmitterToStream(missing);
    EXPECT_EQ(via_op, via_emitter);
  });
}

TEST_F(EmitOperatorTest_96, MultipleEmitsAppendToStreamAndMatchEmitter_96) {
  YAML::Node a("first");
  YAML::Node b("second");

  std::stringstream ss_op;
  std::stringstream ss_em;

  ss_op << a << b;

  YAML::Emitter emitter(ss_em);
  emitter << a << b;

  EXPECT_EQ(ss_op.str(), ss_em.str());
  EXPECT_FALSE(ss_op.str().empty());
}

}  // namespace
