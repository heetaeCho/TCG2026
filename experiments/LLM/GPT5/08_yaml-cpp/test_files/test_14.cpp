// File: test/emittermanip_anchor_test_14.cpp
#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/emitter.h>
#include <yaml-cpp/emittermanip.h>

namespace {

class AnchorManipulatorTest_14 : public ::testing::Test {};

TEST_F(AnchorManipulatorTest_14, AnchorAppliedToScalarEmitsAnchorToken_14) {
  YAML::Emitter out;
  out << YAML::Anchor("id14") << "value";

  ASSERT_TRUE(out.good());
  const std::string s = out.c_str();

  // Observable behavior through the emitter output: anchor token should appear.
  EXPECT_NE(s.find("&id14"), std::string::npos);
  EXPECT_NE(s.find("value"), std::string::npos);
}

TEST_F(AnchorManipulatorTest_14, AnchorAppliedInsideMapDoesNotBreakEmission_14) {
  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << YAML::Anchor("k14") << "key";
  out << YAML::Value << "val";
  out << YAML::EndMap;

  ASSERT_TRUE(out.good());
  const std::string s = out.c_str();

  EXPECT_NE(s.find("&k14"), std::string::npos);
  EXPECT_NE(s.find("key"), std::string::npos);
  EXPECT_NE(s.find("val"), std::string::npos);
}

TEST_F(AnchorManipulatorTest_14, EmptyAnchorStringIsHandledGracefully_14) {
  YAML::Emitter out;
  out << YAML::Anchor("") << "v";

  // Do not assume formatting rules for empty anchors; just ensure observable success.
  EXPECT_TRUE(out.good());
  const std::string s = out.c_str();
  EXPECT_FALSE(s.empty());
  EXPECT_NE(s.find("v"), std::string::npos);
}

TEST_F(AnchorManipulatorTest_14, NonAsciiAnchorStringDoesNotCrashAndEmitsSomething_14) {
  YAML::Emitter out;
  const std::string anchor = u8"한글14";
  out << YAML::Anchor(anchor) << "v";

  EXPECT_TRUE(out.good());
  const std::string s = out.c_str();
  EXPECT_FALSE(s.empty());
  EXPECT_NE(s.find("v"), std::string::npos);

  // If the library preserves the anchor text, it should be visible. If it normalizes it,
  // this expectation may fail in some implementations, so keep it non-fatal.
  EXPECT_NE(s.find("&"), std::string::npos);
}

TEST_F(AnchorManipulatorTest_14, VeryLongAnchorStringDoesNotBreakEmitter_14) {
  YAML::Emitter out;
  const std::string long_anchor(1024, 'a');
  out << YAML::Anchor(long_anchor) << "v";

  EXPECT_TRUE(out.good());
  const std::string s = out.c_str();
  EXPECT_FALSE(s.empty());
  EXPECT_NE(s.find("v"), std::string::npos);

  // Avoid assuming full anchor serialization; check for an anchor marker at least.
  EXPECT_NE(s.find("&"), std::string::npos);
}

}  // namespace
