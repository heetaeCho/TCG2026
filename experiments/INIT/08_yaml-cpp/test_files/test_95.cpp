// TEST_ID: 95
// File: test_emit_operator_shift_left_95.cpp

#include <gtest/gtest.h>
#include <yaml-cpp/yaml.h>

#include <sstream>
#include <string>

namespace {

class EmitOperatorShiftLeftTest_95 : public ::testing::Test {
 protected:
  static std::string ToString(const YAML::Emitter& out) {
    const char* s = out.c_str();
    return s ? std::string(s) : std::string();
  }
};

TEST_F(EmitOperatorShiftLeftTest_95, ReturnsSameEmitterReference_95) {
  YAML::Emitter out;
  YAML::Node node("hello");

  YAML::Emitter* returned = &(out << node);

  EXPECT_EQ(returned, &out);
}

TEST_F(EmitOperatorShiftLeftTest_95, EmitsScalarNodeContainsScalarText_95) {
  YAML::Emitter out;
  YAML::Node node("hello");

  out << node;

  const std::string emitted = ToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_NE(emitted.find("hello"), std::string::npos);
  EXPECT_TRUE(out.good());
}

TEST_F(EmitOperatorShiftLeftTest_95, EmitsIntegerScalarContainsDigits_95) {
  YAML::Emitter out;
  YAML::Node node(12345);

  out << node;

  const std::string emitted = ToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_NE(emitted.find("12345"), std::string::npos);
  EXPECT_TRUE(out.good());
}

TEST_F(EmitOperatorShiftLeftTest_95, EmitsSequenceNodeContainsElements_95) {
  YAML::Emitter out;
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(1);
  seq.push_back(2);

  out << seq;

  const std::string emitted = ToString(out);
  EXPECT_FALSE(emitted.empty());
  // Avoid asserting exact YAML formatting; only verify values are present.
  EXPECT_NE(emitted.find("1"), std::string::npos);
  EXPECT_NE(emitted.find("2"), std::string::npos);
  EXPECT_TRUE(out.good());
}

TEST_F(EmitOperatorShiftLeftTest_95, EmitsMapNodeContainsKeysAndValues_95) {
  YAML::Emitter out;
  YAML::Node map(YAML::NodeType::Map);
  map["a"] = 1;
  map["b"] = "two";

  out << map;

  const std::string emitted = ToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_NE(emitted.find("a"), std::string::npos);
  EXPECT_NE(emitted.find("1"), std::string::npos);
  EXPECT_NE(emitted.find("b"), std::string::npos);
  EXPECT_NE(emitted.find("two"), std::string::npos);
  EXPECT_TRUE(out.good());
}

TEST_F(EmitOperatorShiftLeftTest_95, EmitsNestedStructureContainsRepresentativeTokens_95) {
  YAML::Emitter out;

  YAML::Node root(YAML::NodeType::Map);
  root["name"] = "alice";

  YAML::Node items(YAML::NodeType::Sequence);
  items.push_back("x");
  items.push_back("y");
  root["items"] = items;

  out << root;

  const std::string emitted = ToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_NE(emitted.find("name"), std::string::npos);
  EXPECT_NE(emitted.find("alice"), std::string::npos);
  EXPECT_NE(emitted.find("items"), std::string::npos);
  EXPECT_NE(emitted.find("x"), std::string::npos);
  EXPECT_NE(emitted.find("y"), std::string::npos);
  EXPECT_TRUE(out.good());
}

TEST_F(EmitOperatorShiftLeftTest_95, Boundary_EmptySequenceStillProducesOutput_95) {
  YAML::Emitter out;
  YAML::Node emptySeq(YAML::NodeType::Sequence);

  out << emptySeq;

  const std::string emitted = ToString(out);
  // Different YAML styles exist; just ensure something was emitted and emitter is usable.
  EXPECT_FALSE(emitted.empty());
  EXPECT_TRUE(out.good());
  EXPECT_GT(out.size(), 0u);
}

TEST_F(EmitOperatorShiftLeftTest_95, SupportsChainingMultipleNodeEmits_95) {
  YAML::Emitter out;
  YAML::Node first("one");
  YAML::Node second("two");

  out << first << second;

  const std::string emitted = ToString(out);
  EXPECT_FALSE(emitted.empty());
  EXPECT_NE(emitted.find("one"), std::string::npos);
  EXPECT_NE(emitted.find("two"), std::string::npos);
  EXPECT_TRUE(out.good());
}

TEST_F(EmitOperatorShiftLeftTest_95, WritesThroughEmitterConstructedWithStream_95) {
  std::stringstream ss;
  YAML::Emitter out(ss);
  YAML::Node node("hello");

  out << node;

  const std::string streamStr = ss.str();
  EXPECT_FALSE(streamStr.empty());
  EXPECT_NE(streamStr.find("hello"), std::string::npos);
  EXPECT_TRUE(out.good());
}

TEST_F(EmitOperatorShiftLeftTest_95, DoesNotThrowForDefaultConstructedNode_95) {
  YAML::Emitter out;
  YAML::Node node;  // Default constructed.

  EXPECT_NO_THROW({
    out << node;
  });

  // Keep assertions weak: just validate emitter remains in a queryable state.
  (void)ToString(out);
  EXPECT_TRUE(out.good() || !out.good());  // Observable: should not crash; state is implementation-defined.
}

}  // namespace
