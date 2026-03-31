#include <gtest/gtest.h>
#include <list>
#include <string>
#include <sstream>
#include "yaml-cpp/yaml.h"

// Test fixture for stlemitter tests (operator<< for std::list)
class StlEmitterTest_656 : public ::testing::Test {
 protected:
  YAML::Emitter emitter;
};

// Test emitting an empty list of integers
TEST_F(StlEmitterTest_656, EmitEmptyIntList_656) {
  std::list<int> empty_list;
  emitter << empty_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  // An empty sequence should produce valid YAML
  EXPECT_FALSE(output.empty());
}

// Test emitting a list with a single integer
TEST_F(StlEmitterTest_656, EmitSingleElementIntList_656) {
  std::list<int> single_list = {42};
  emitter << single_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("42"), std::string::npos);
}

// Test emitting a list of multiple integers
TEST_F(StlEmitterTest_656, EmitMultipleIntList_656) {
  std::list<int> int_list = {1, 2, 3, 4, 5};
  emitter << int_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("1"), std::string::npos);
  EXPECT_NE(output.find("2"), std::string::npos);
  EXPECT_NE(output.find("3"), std::string::npos);
  EXPECT_NE(output.find("4"), std::string::npos);
  EXPECT_NE(output.find("5"), std::string::npos);
}

// Test emitting a list of strings
TEST_F(StlEmitterTest_656, EmitStringList_656) {
  std::list<std::string> str_list = {"hello", "world", "foo"};
  emitter << str_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("hello"), std::string::npos);
  EXPECT_NE(output.find("world"), std::string::npos);
  EXPECT_NE(output.find("foo"), std::string::npos);
}

// Test emitting a list of doubles
TEST_F(StlEmitterTest_656, EmitDoubleList_656) {
  std::list<double> dbl_list = {1.5, 2.7, 3.14};
  emitter << dbl_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  EXPECT_NE(output.find("1.5"), std::string::npos);
  EXPECT_NE(output.find("2.7"), std::string::npos);
}

// Test emitting a list of booleans
TEST_F(StlEmitterTest_656, EmitBoolList_656) {
  std::list<bool> bool_list = {true, false, true};
  emitter << bool_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  EXPECT_FALSE(output.empty());
}

// Test that emitting a list produces parseable YAML
TEST_F(StlEmitterTest_656, EmitListProducesParseableYAML_656) {
  std::list<int> int_list = {10, 20, 30};
  emitter << int_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();

  YAML::Node node = YAML::Load(emitter.c_str());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 3u);
  EXPECT_EQ(node[0].as<int>(), 10);
  EXPECT_EQ(node[1].as<int>(), 20);
  EXPECT_EQ(node[2].as<int>(), 30);
}

// Test emitting a list with Flow sequence format
TEST_F(StlEmitterTest_656, EmitListFlowFormat_656) {
  std::list<int> int_list = {1, 2, 3};
  emitter << YAML::Flow << int_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  // Flow format should produce something like [1, 2, 3]
  EXPECT_NE(output.find("["), std::string::npos);
  EXPECT_NE(output.find("]"), std::string::npos);
}

// Test emitting a list with Block sequence format
TEST_F(StlEmitterTest_656, EmitListBlockFormat_656) {
  std::list<int> int_list = {1, 2, 3};
  emitter << YAML::Block << int_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = emitter.c_str();
  // Block format should produce lines like "- 1"
  EXPECT_NE(output.find("- "), std::string::npos);
}

// Test emitting to an output stream
TEST_F(StlEmitterTest_656, EmitListToOutputStream_656) {
  std::stringstream ss;
  YAML::Emitter stream_emitter(ss);
  std::list<int> int_list = {7, 8, 9};
  stream_emitter << int_list;
  EXPECT_TRUE(stream_emitter.good()) << "Error: " << stream_emitter.GetLastError();
  std::string output = ss.str();
  EXPECT_NE(output.find("7"), std::string::npos);
  EXPECT_NE(output.find("8"), std::string::npos);
  EXPECT_NE(output.find("9"), std::string::npos);
}

// Test emitting a list of strings that are parseable and maintain order
TEST_F(StlEmitterTest_656, EmitStringListParseableAndOrdered_656) {
  std::list<std::string> str_list = {"alpha", "beta", "gamma"};
  emitter << str_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();

  YAML::Node node = YAML::Load(emitter.c_str());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 3u);
  EXPECT_EQ(node[0].as<std::string>(), "alpha");
  EXPECT_EQ(node[1].as<std::string>(), "beta");
  EXPECT_EQ(node[2].as<std::string>(), "gamma");
}

// Test emitting a large list
TEST_F(StlEmitterTest_656, EmitLargeList_656) {
  std::list<int> large_list;
  for (int i = 0; i < 1000; ++i) {
    large_list.push_back(i);
  }
  emitter << large_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();

  YAML::Node node = YAML::Load(emitter.c_str());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 1000u);
  EXPECT_EQ(node[0].as<int>(), 0);
  EXPECT_EQ(node[999].as<int>(), 999);
}

// Test emitting a list with negative numbers
TEST_F(StlEmitterTest_656, EmitNegativeIntList_656) {
  std::list<int> neg_list = {-1, -100, 0, 50};
  emitter << neg_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();

  YAML::Node node = YAML::Load(emitter.c_str());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 4u);
  EXPECT_EQ(node[0].as<int>(), -1);
  EXPECT_EQ(node[1].as<int>(), -100);
  EXPECT_EQ(node[2].as<int>(), 0);
  EXPECT_EQ(node[3].as<int>(), 50);
}

// Test emitting an empty string list
TEST_F(StlEmitterTest_656, EmitEmptyStringList_656) {
  std::list<std::string> empty_str_list;
  emitter << empty_str_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();

  YAML::Node node = YAML::Load(emitter.c_str());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 0u);
}

// Test that the return value is the same emitter reference (chaining)
TEST_F(StlEmitterTest_656, OperatorReturnsSameEmitter_656) {
  std::list<int> int_list = {1};
  YAML::Emitter& result = (emitter << int_list);
  EXPECT_EQ(&result, &emitter);
}

// Test emitting list of strings with special characters
TEST_F(StlEmitterTest_656, EmitListWithSpecialCharStrings_656) {
  std::list<std::string> special_list = {"hello world", "foo: bar", "a\nb"};
  emitter << special_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();

  YAML::Node node = YAML::Load(emitter.c_str());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 3u);
  EXPECT_EQ(node[0].as<std::string>(), "hello world");
  EXPECT_EQ(node[1].as<std::string>(), "foo: bar");
  EXPECT_EQ(node[2].as<std::string>(), "a\nb");
}

// Test emitting list of float values
TEST_F(StlEmitterTest_656, EmitFloatList_656) {
  std::list<float> float_list = {1.0f, 2.5f, 3.75f};
  emitter << float_list;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();

  YAML::Node node = YAML::Load(emitter.c_str());
  EXPECT_TRUE(node.IsSequence());
  EXPECT_EQ(node.size(), 3u);
}

// Test size of emitter output is non-zero after emitting a list
TEST_F(StlEmitterTest_656, EmitListSizeNonZero_656) {
  std::list<int> int_list = {1, 2};
  emitter << int_list;
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}
