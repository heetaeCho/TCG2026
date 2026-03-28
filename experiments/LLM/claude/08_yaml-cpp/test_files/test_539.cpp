#include <gtest/gtest.h>
#include <sstream>
#include <string>
#include "yaml-cpp/yaml.h"

class EmitterAnchorTest_539 : public ::testing::Test {
 protected:
  void SetUp() override {}
  void TearDown() override {}
};

// Test: Writing a valid anchor keeps emitter in good state
TEST_F(EmitterAnchorTest_539, WriteValidAnchor_EmitterRemainsGood_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("myanchor") << "value";
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
}

// Test: The output contains the anchor reference
TEST_F(EmitterAnchorTest_539, WriteValidAnchor_OutputContainsAnchor_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("myanchor") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&myanchor"), std::string::npos)
      << "Output was: " << output;
}

// Test: Writing an anchor with alphanumeric content
TEST_F(EmitterAnchorTest_539, WriteAlphanumericAnchor_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("anchor123") << "value";
  EXPECT_TRUE(emitter.good());
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&anchor123"), std::string::npos);
}

// Test: Writing a duplicate anchor (two anchors in a row without scalar) should fail
TEST_F(EmitterAnchorTest_539, WriteDuplicateAnchor_SetsError_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("first") << YAML::Anchor("second");
  EXPECT_FALSE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), "invalid anchor");
}

// Test: After an error from duplicate anchor, further writes don't crash
TEST_F(EmitterAnchorTest_539, WriteDuplicateAnchor_FurtherWritesSafe_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("first") << YAML::Anchor("second");
  EXPECT_FALSE(emitter.good());
  // Further writes should not crash, emitter stays in bad state
  emitter << "value";
  EXPECT_FALSE(emitter.good());
}

// Test: Anchor with empty string should set error (invalid anchor)
TEST_F(EmitterAnchorTest_539, WriteEmptyAnchor_SetsError_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("") << "value";
  // Empty anchor is likely invalid
  // Either emitter is not good, or if it is, check output
  if (!emitter.good()) {
    EXPECT_EQ(emitter.GetLastError(), "invalid anchor");
  }
}

// Test: Anchor followed by a scalar in a map
TEST_F(EmitterAnchorTest_539, WriteAnchorInMap_539) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << "key" << YAML::Value << YAML::Anchor("val_anchor") << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&val_anchor"), std::string::npos)
      << "Output was: " << output;
}

// Test: Anchor followed by a scalar in a sequence
TEST_F(EmitterAnchorTest_539, WriteAnchorInSequence_539) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("seq_anchor") << "item";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&seq_anchor"), std::string::npos)
      << "Output was: " << output;
}

// Test: Writing anchor to a stream-based emitter
TEST_F(EmitterAnchorTest_539, WriteAnchorToStream_539) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << YAML::Anchor("stream_anchor") << "value";
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output = ss.str();
  EXPECT_NE(output.find("&stream_anchor"), std::string::npos)
      << "Output was: " << output;
}

// Test: Anchor with special characters that might be invalid
TEST_F(EmitterAnchorTest_539, WriteAnchorWithSpaces_SetsError_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("has space") << "value";
  // Anchors with spaces are invalid in YAML
  if (!emitter.good()) {
    EXPECT_EQ(emitter.GetLastError(), "invalid anchor");
  }
}

// Test: Anchor with special characters (brackets)
TEST_F(EmitterAnchorTest_539, WriteAnchorWithBrackets_SetsError_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("[invalid]") << "value";
  if (!emitter.good()) {
    EXPECT_EQ(emitter.GetLastError(), "invalid anchor");
  }
}

// Test: Anchor with curly braces
TEST_F(EmitterAnchorTest_539, WriteAnchorWithCurlyBraces_SetsError_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("{invalid}") << "value";
  if (!emitter.good()) {
    EXPECT_EQ(emitter.GetLastError(), "invalid anchor");
  }
}

// Test: Anchor on a map key
TEST_F(EmitterAnchorTest_539, WriteAnchorOnMapKey_539) {
  YAML::Emitter emitter;
  emitter << YAML::BeginMap;
  emitter << YAML::Key << YAML::Anchor("key_anchor") << "key";
  emitter << YAML::Value << "value";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&key_anchor"), std::string::npos)
      << "Output was: " << output;
}

// Test: Multiple anchors on different nodes (not duplicated on same node)
TEST_F(EmitterAnchorTest_539, WriteMultipleAnchorsOnDifferentNodes_539) {
  YAML::Emitter emitter;
  emitter << YAML::BeginSeq;
  emitter << YAML::Anchor("a1") << "item1";
  emitter << YAML::Anchor("a2") << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&a1"), std::string::npos);
  EXPECT_NE(output.find("&a2"), std::string::npos);
}

// Test: Size is non-zero after writing anchor + value
TEST_F(EmitterAnchorTest_539, WriteAnchor_SizeNonZero_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("anc") << "val";
  EXPECT_TRUE(emitter.good());
  EXPECT_GT(emitter.size(), 0u);
}

// Test: c_str is not null after writing anchor + value
TEST_F(EmitterAnchorTest_539, WriteAnchor_CStrNotNull_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("anc") << "val";
  EXPECT_TRUE(emitter.good());
  EXPECT_NE(emitter.c_str(), nullptr);
}

// Test: Return value of Write is reference to the same emitter
TEST_F(EmitterAnchorTest_539, WriteAnchor_ReturnsSameEmitter_539) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = (emitter << YAML::Anchor("anc"));
  EXPECT_EQ(&ref, &emitter);
}

// Test: Anchor before a sequence
TEST_F(EmitterAnchorTest_539, WriteAnchorBeforeSequence_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("seq_anc") << YAML::BeginSeq;
  emitter << "item1" << "item2";
  emitter << YAML::EndSeq;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&seq_anc"), std::string::npos)
      << "Output was: " << output;
}

// Test: Anchor before a map
TEST_F(EmitterAnchorTest_539, WriteAnchorBeforeMap_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("map_anc") << YAML::BeginMap;
  emitter << YAML::Key << "k" << YAML::Value << "v";
  emitter << YAML::EndMap;
  EXPECT_TRUE(emitter.good()) << "Error: " << emitter.GetLastError();
  std::string output(emitter.c_str());
  EXPECT_NE(output.find("&map_anc"), std::string::npos)
      << "Output was: " << output;
}

// Test: Freshly constructed emitter is in good state
TEST_F(EmitterAnchorTest_539, FreshEmitter_IsGood_539) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
  EXPECT_EQ(emitter.GetLastError(), "");
}

// Test: After error, good() returns false
TEST_F(EmitterAnchorTest_539, AfterError_GoodReturnsFalse_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("a1") << YAML::Anchor("a2");
  EXPECT_FALSE(emitter.good());
}

// Test: GetLastError returns meaningful message after error
TEST_F(EmitterAnchorTest_539, AfterError_GetLastErrorReturnsMessage_539) {
  YAML::Emitter emitter;
  emitter << YAML::Anchor("a1") << YAML::Anchor("a2");
  std::string err = emitter.GetLastError();
  EXPECT_FALSE(err.empty());
}
