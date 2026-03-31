#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <list>
#include <sstream>
#include "yaml-cpp/yaml.h"

// Test fixture
class StlEmitterTest_655 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// Test: Emitting an empty vector produces an empty sequence
TEST_F(StlEmitterTest_655, EmptyVectorProducesEmptySequence_655) {
  std::vector<int> v;
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // An empty sequence should produce "[]" in flow or an empty block sequence
  EXPECT_FALSE(output.empty());
}

// Test: Emitting a vector of integers
TEST_F(StlEmitterTest_655, VectorOfIntegers_655) {
  std::vector<int> v = {1, 2, 3};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // The output should contain all three numbers
  EXPECT_NE(std::string::npos, output.find("1"));
  EXPECT_NE(std::string::npos, output.find("2"));
  EXPECT_NE(std::string::npos, output.find("3"));
}

// Test: Emitting a vector of strings
TEST_F(StlEmitterTest_655, VectorOfStrings_655) {
  std::vector<std::string> v = {"hello", "world"};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("hello"));
  EXPECT_NE(std::string::npos, output.find("world"));
}

// Test: Emitting a single element vector
TEST_F(StlEmitterTest_655, SingleElementVector_655) {
  std::vector<int> v = {42};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("42"));
}

// Test: Emitting a vector of doubles
TEST_F(StlEmitterTest_655, VectorOfDoubles_655) {
  std::vector<double> v = {1.5, 2.5, 3.5};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("1.5"));
  EXPECT_NE(std::string::npos, output.find("2.5"));
  EXPECT_NE(std::string::npos, output.find("3.5"));
}

// Test: Emitting a vector of booleans
TEST_F(StlEmitterTest_655, VectorOfBooleans_655) {
  std::vector<bool> v = {true, false, true};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test: Emitting nested vectors (vector of vectors)
TEST_F(StlEmitterTest_655, NestedVectors_655) {
  std::vector<std::vector<int>> v = {{1, 2}, {3, 4}};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_NE(std::string::npos, output.find("1"));
  EXPECT_NE(std::string::npos, output.find("2"));
  EXPECT_NE(std::string::npos, output.find("3"));
  EXPECT_NE(std::string::npos, output.find("4"));
}

// Test: Emitting a vector with flow sequence format
TEST_F(StlEmitterTest_655, VectorWithFlowSeqFormat_655) {
  emitter << YAML::Flow;
  std::vector<int> v = {1, 2, 3};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Flow format uses brackets
  EXPECT_NE(std::string::npos, output.find("["));
  EXPECT_NE(std::string::npos, output.find("]"));
}

// Test: Emitting a vector with block sequence format
TEST_F(StlEmitterTest_655, VectorWithBlockSeqFormat_655) {
  emitter << YAML::Block;
  std::vector<int> v = {1, 2, 3};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  // Block format uses dashes
  EXPECT_NE(std::string::npos, output.find("-"));
}

// Test: Emitting to an output stream via constructor
TEST_F(StlEmitterTest_655, VectorToOutputStream_655) {
  std::stringstream ss;
  YAML::Emitter streamEmitter(ss);
  std::vector<int> v = {10, 20, 30};
  streamEmitter << v;
  EXPECT_TRUE(streamEmitter.good());
  std::string output = ss.str();
  EXPECT_NE(std::string::npos, output.find("10"));
  EXPECT_NE(std::string::npos, output.find("20"));
  EXPECT_NE(std::string::npos, output.find("30"));
}

// Test: Output is valid YAML that can be parsed back
TEST_F(StlEmitterTest_655, VectorOutputIsParseable_655) {
  std::vector<int> v = {1, 2, 3};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(3u, node.size());
  EXPECT_EQ(1, node[0].as<int>());
  EXPECT_EQ(2, node[1].as<int>());
  EXPECT_EQ(3, node[2].as<int>());
}

// Test: Empty vector output is parseable
TEST_F(StlEmitterTest_655, EmptyVectorOutputIsParseable_655) {
  std::vector<int> v;
  emitter << YAML::Flow << v;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsSequence());
  EXPECT_EQ(0u, node.size());
}

// Test: Large vector
TEST_F(StlEmitterTest_655, LargeVector_655) {
  std::vector<int> v;
  for (int i = 0; i < 1000; ++i) {
    v.push_back(i);
  }
  emitter << v;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsSequence());
  EXPECT_EQ(1000u, node.size());
  EXPECT_EQ(0, node[0].as<int>());
  EXPECT_EQ(999, node[999].as<int>());
}

// Test: Vector of strings with special characters
TEST_F(StlEmitterTest_655, VectorOfStringsWithSpecialChars_655) {
  std::vector<std::string> v = {"hello: world", "foo\nbar", "with \"quotes\""};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(3u, node.size());
  EXPECT_EQ("hello: world", node[0].as<std::string>());
  EXPECT_EQ("foo\nbar", node[1].as<std::string>());
  EXPECT_EQ("with \"quotes\"", node[2].as<std::string>());
}

// Test: size() returns non-zero after emitting vector
TEST_F(StlEmitterTest_655, SizeAfterEmittingVector_655) {
  std::vector<int> v = {1, 2, 3};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test: c_str() returns non-null after emitting vector
TEST_F(StlEmitterTest_655, CStrAfterEmittingVector_655) {
  std::vector<int> v = {1};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  EXPECT_NE(nullptr, emitter.c_str());
}

// Test: Vector of negative integers
TEST_F(StlEmitterTest_655, VectorOfNegativeIntegers_655) {
  std::vector<int> v = {-1, -2, -3};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(3u, node.size());
  EXPECT_EQ(-1, node[0].as<int>());
  EXPECT_EQ(-2, node[1].as<int>());
  EXPECT_EQ(-3, node[2].as<int>());
}

// Test: Nested vector of strings
TEST_F(StlEmitterTest_655, NestedVectorOfStrings_655) {
  std::vector<std::vector<std::string>> v = {{"a", "b"}, {"c", "d"}};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(2u, node.size());
  ASSERT_TRUE(node[0].IsSequence());
  ASSERT_TRUE(node[1].IsSequence());
  EXPECT_EQ("a", node[0][0].as<std::string>());
  EXPECT_EQ("d", node[1][1].as<std::string>());
}

// Test: Multiple vectors emitted in sequence context
TEST_F(StlEmitterTest_655, MultipleVectorsInDocument_655) {
  emitter << YAML::BeginSeq;
  std::vector<int> v1 = {1, 2};
  std::vector<int> v2 = {3, 4};
  emitter << v1 << v2;
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsSequence());
  ASSERT_EQ(2u, node.size());
}

// Test: Vector emitted as map value
TEST_F(StlEmitterTest_655, VectorAsMapValue_655) {
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "items" << YAML::Value;
  std::vector<int> v = {10, 20, 30};
  emitter << v;
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good());
  
  YAML::Node node = YAML::Load(emitter.c_str());
  ASSERT_TRUE(node.IsMap());
  ASSERT_TRUE(node["items"].IsSequence());
  EXPECT_EQ(3u, node["items"].size());
  EXPECT_EQ(10, node["items"][0].as<int>());
}

// Test: Vector of floats
TEST_F(StlEmitterTest_655, VectorOfFloats_655) {
  std::vector<float> v = {1.0f, 2.5f, 3.75f};
  emitter << v;
  EXPECT_TRUE(emitter.good());
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}
