// File: yaml_convert_list_decode_test_614.cpp

#include <gtest/gtest.h>

#include <list>
#include <string>

#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/convert.h>

// If your project uses <yaml-cpp/yaml.h> as the public include, you can replace the
// two includes above with:
//   #include <yaml-cpp/yaml.h>

namespace {

class ConvertListDecodeTest_614 : public ::testing::Test {};

TEST_F(ConvertListDecodeTest_614, ReturnsFalseAndDoesNotModifyOutputWhenNodeIsNotSequence_614) {
  YAML::Node scalar("not-a-sequence");

  std::list<int> out = {1, 2, 3};

  // decode for std::list should return false for non-sequence nodes.
  const bool ok = YAML::convert<std::list<int>>::decode(scalar, out);

  EXPECT_FALSE(ok);
  // Observable behavior: output should remain unchanged when decode returns false.
  EXPECT_EQ((std::list<int>{1, 2, 3}), out);
}

TEST_F(ConvertListDecodeTest_614, DecodesEmptySequenceClearsExistingContents_614) {
  YAML::Node seq(YAML::NodeType::Sequence);

  std::list<int> out = {9, 8, 7};

  const bool ok = YAML::convert<std::list<int>>::decode(seq, out);

  EXPECT_TRUE(ok);
  EXPECT_TRUE(out.empty());
}

TEST_F(ConvertListDecodeTest_614, DecodesSequencePreservesOrder_614) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(10);
  seq.push_back(20);
  seq.push_back(30);

  std::list<int> out;

  const bool ok = YAML::convert<std::list<int>>::decode(seq, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ((std::list<int>{10, 20, 30}), out);
}

TEST_F(ConvertListDecodeTest_614, DecodingSequenceReplacesExistingListContents_614) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back(1);
  seq.push_back(2);

  std::list<int> out = {100, 200, 300};

  const bool ok = YAML::convert<std::list<int>>::decode(seq, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ((std::list<int>{1, 2}), out);
}

TEST_F(ConvertListDecodeTest_614, ThrowsWhenElementCannotBeConvertedToTargetType_614) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back("abc");  // commonly not convertible to int
  seq.push_back("123");

  std::list<int> out;

  // Observable error behavior: YAML::Node::as<int>() may throw on bad conversion.
  EXPECT_THROW((void)YAML::convert<std::list<int>>::decode(seq, out), YAML::BadConversion);
}

TEST_F(ConvertListDecodeTest_614, DecodesListOfStrings_614) {
  YAML::Node seq(YAML::NodeType::Sequence);
  seq.push_back("one");
  seq.push_back("two");
  seq.push_back("three");

  std::list<std::string> out;

  const bool ok = YAML::convert<std::list<std::string>>::decode(seq, out);

  EXPECT_TRUE(ok);
  EXPECT_EQ((std::list<std::string>{"one", "two", "three"}), out);
}

TEST_F(ConvertListDecodeTest_614, ReturnsFalseForMapNodeAndDoesNotModifyOutput_614) {
  YAML::Node map(YAML::NodeType::Map);
  map["k"] = "v";

  std::list<std::string> out = {"keep"};

  const bool ok = YAML::convert<std::list<std::string>>::decode(map, out);

  EXPECT_FALSE(ok);
  EXPECT_EQ((std::list<std::string>{"keep"}), out);
}

}  // namespace