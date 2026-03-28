// TEST_ID: 593
#include <gtest/gtest.h>

#include "yaml-cpp/node/convert.h"
#include "yaml-cpp/node/node.h"

namespace {

class EncodeTest_593 : public ::testing::Test {};

TEST_F(EncodeTest_593, DefaultNode_PreservesObservableState_593) {
  YAML::Node n;
  YAML::Node encoded = YAML::encode(n);

  EXPECT_EQ(encoded.IsDefined(), n.IsDefined());
  EXPECT_EQ(static_cast<bool>(encoded), static_cast<bool>(n));
  EXPECT_EQ(encoded.IsNull(), n.IsNull());
  EXPECT_EQ(encoded.IsScalar(), n.IsScalar());
  EXPECT_EQ(encoded.IsSequence(), n.IsSequence());
  EXPECT_EQ(encoded.IsMap(), n.IsMap());

  // size() should be safe to call if the original was safe to call.
  EXPECT_EQ(encoded.size(), n.size());
}

TEST_F(EncodeTest_593, ScalarInt_RoundTripsThroughAsInt_593) {
  YAML::Node n(42);
  YAML::Node encoded = YAML::encode(n);

  EXPECT_TRUE(encoded.IsDefined());
  EXPECT_TRUE(encoded.IsScalar());
  EXPECT_EQ(encoded.as<int>(), n.as<int>());
}

TEST_F(EncodeTest_593, ScalarString_PreservesTagAndValue_593) {
  YAML::Node n(std::string("hello"));
  n.SetTag("!mytag");

  YAML::Node encoded = YAML::encode(n);

  EXPECT_TRUE(encoded.IsDefined());
  EXPECT_TRUE(encoded.IsScalar());
  EXPECT_EQ(encoded.as<std::string>(), n.as<std::string>());
  EXPECT_EQ(encoded.Tag(), n.Tag());
}

TEST_F(EncodeTest_593, Sequence_PreservesSizeAndElements_593) {
  YAML::Node seq;
  seq.push_back(1);
  seq.push_back(2);
  seq.push_back(3);

  YAML::Node encoded = YAML::encode(seq);

  EXPECT_TRUE(encoded.IsDefined());
  EXPECT_TRUE(encoded.IsSequence());
  EXPECT_EQ(encoded.size(), seq.size());
  ASSERT_EQ(encoded.size(), 3u);

  EXPECT_EQ(encoded[0].as<int>(), 1);
  EXPECT_EQ(encoded[1].as<int>(), 2);
  EXPECT_EQ(encoded[2].as<int>(), 3);
}

TEST_F(EncodeTest_593, Map_PreservesSizeAndLookupResults_593) {
  YAML::Node m;
  m.force_insert("a", 1);
  m.force_insert("b", std::string("x"));

  YAML::Node encoded = YAML::encode(m);

  EXPECT_TRUE(encoded.IsDefined());
  EXPECT_TRUE(encoded.IsMap());
  EXPECT_EQ(encoded.size(), m.size());
  ASSERT_EQ(encoded.size(), 2u);

  EXPECT_EQ(encoded["a"].as<int>(), 1);
  EXPECT_EQ(encoded["b"].as<std::string>(), "x");
}

TEST_F(EncodeTest_593, NestedStructure_PreservesNestedAccess_593) {
  YAML::Node seq;
  seq.push_back("first");
  seq.push_back("second");

  YAML::Node m;
  m.force_insert("seq", seq);
  m.force_insert("n", 99);

  YAML::Node encoded = YAML::encode(m);

  EXPECT_TRUE(encoded.IsMap());
  EXPECT_EQ(encoded["n"].as<int>(), 99);

  YAML::Node encodedSeq = encoded["seq"];
  EXPECT_TRUE(encodedSeq.IsSequence());
  ASSERT_EQ(encodedSeq.size(), 2u);
  EXPECT_EQ(encodedSeq[0].as<std::string>(), "first");
  EXPECT_EQ(encodedSeq[1].as<std::string>(), "second");
}

TEST_F(EncodeTest_593, EncodeDoesNotChangeOriginalObservableState_593) {
  YAML::Node n;
  n.force_insert("k", "v");

  const bool beforeDefined = n.IsDefined();
  const bool beforeBool = static_cast<bool>(n);
  const bool beforeIsMap = n.IsMap();
  const std::size_t beforeSize = n.size();
  const std::string beforeValue = n["k"].as<std::string>();

  (void)YAML::encode(n);

  EXPECT_EQ(n.IsDefined(), beforeDefined);
  EXPECT_EQ(static_cast<bool>(n), beforeBool);
  EXPECT_EQ(n.IsMap(), beforeIsMap);
  EXPECT_EQ(n.size(), beforeSize);
  EXPECT_EQ(n["k"].as<std::string>(), beforeValue);
}

TEST_F(EncodeTest_593, EncodingMissingLookupNode_IsSafeAndPreservesDefinedness_593) {
  YAML::Node m;
  m.force_insert("present", 1);

  YAML::Node missing = m["absent"];  // Observable behavior: may be undefined/zombie-like.
  YAML::Node encodedMissing = YAML::encode(missing);

  EXPECT_EQ(encodedMissing.IsDefined(), missing.IsDefined());
  EXPECT_EQ(static_cast<bool>(encodedMissing), static_cast<bool>(missing));
  EXPECT_EQ(encodedMissing.IsNull(), missing.IsNull());
  EXPECT_EQ(encodedMissing.IsScalar(), missing.IsScalar());
  EXPECT_EQ(encodedMissing.IsSequence(), missing.IsSequence());
  EXPECT_EQ(encodedMissing.IsMap(), missing.IsMap());
}

}  // namespace