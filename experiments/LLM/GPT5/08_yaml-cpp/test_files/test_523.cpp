// File: ./TestProjects/yaml-cpp/test/emitter_setmapformat_test_523.cpp

#include <gtest/gtest.h>

#include <string>

#include <yaml-cpp/yaml.h>  // Brings in YAML::Emitter and manipulators like Flow/Block/BeginMap/etc.

namespace {

class SetMapFormatTest_523 : public ::testing::Test {
 protected:
  static std::string EmitSimpleMapToString(YAML::Emitter& out) {
    out << YAML::BeginMap;
    out << YAML::Key << "a" << YAML::Value << 1;
    out << YAML::Key << "b" << YAML::Value << 2;
    out << YAML::EndMap;

    // Prefer size()+c_str() to avoid relying on null-termination details.
    return std::string(out.c_str(), out.size());
  }
};

TEST_F(SetMapFormatTest_523, ReturnsTrueForCommonManipulators_523) {
  YAML::Emitter out;

  // These are the common map flow-type manipulators in yaml-cpp.
  EXPECT_TRUE(out.SetMapFormat(YAML::Flow));
  EXPECT_TRUE(out.SetMapFormat(YAML::Block));
}

TEST_F(SetMapFormatTest_523, FlowFormatEmitsBracedInlineMap_523) {
  YAML::Emitter out;

  ASSERT_TRUE(out.SetMapFormat(YAML::Flow));

  const std::string s = EmitSimpleMapToString(out);

  // Flow maps are typically emitted in braces and inline.
  EXPECT_NE(s.find('{'), std::string::npos);
  EXPECT_NE(s.find('}'), std::string::npos);

  // Should contain both keys and values in some inline form.
  EXPECT_NE(s.find("a"), std::string::npos);
  EXPECT_NE(s.find("1"), std::string::npos);
  EXPECT_NE(s.find("b"), std::string::npos);
  EXPECT_NE(s.find("2"), std::string::npos);
}

TEST_F(SetMapFormatTest_523, BlockFormatEmitsMultiLineMapWithoutBraces_523) {
  YAML::Emitter out;

  ASSERT_TRUE(out.SetMapFormat(YAML::Block));

  const std::string s = EmitSimpleMapToString(out);

  // Block maps are typically emitted without braces and with newlines.
  EXPECT_EQ(s.find('{'), std::string::npos);
  EXPECT_EQ(s.find('}'), std::string::npos);

  // Expect at least one newline for block-style output.
  EXPECT_NE(s.find('\n'), std::string::npos);

  // Should still contain keys and values.
  EXPECT_NE(s.find("a"), std::string::npos);
  EXPECT_NE(s.find("1"), std::string::npos);
  EXPECT_NE(s.find("b"), std::string::npos);
  EXPECT_NE(s.find("2"), std::string::npos);
}

TEST_F(SetMapFormatTest_523, RepeatedCallsAreSupportedAndAffectSubsequentOutput_523) {
  YAML::Emitter out;

  ASSERT_TRUE(out.SetMapFormat(YAML::Block));
  const std::string block_s = EmitSimpleMapToString(out);

  // Reset emitter by using a fresh instance for the second emission to avoid
  // depending on any internal buffering/stream state across multiple writes.
  YAML::Emitter out2;
  ASSERT_TRUE(out2.SetMapFormat(YAML::Flow));
  const std::string flow_s = EmitSimpleMapToString(out2);

  // The two styles should look observably different.
  EXPECT_NE(block_s, flow_s);

  // Sanity checks for distinguishing markers.
  EXPECT_NE(flow_s.find('{'), std::string::npos);
  EXPECT_EQ(block_s.find('{'), std::string::npos);
}

TEST_F(SetMapFormatTest_523, InvalidManipulatorReturnsFalseOrKeepsEmitterUsable_523) {
  YAML::Emitter out;

  // Use an out-of-range value without assuming internal enum layout beyond "some value".
  const auto invalid = static_cast<YAML::EMITTER_MANIP>(-1);

  const bool ok = out.SetMapFormat(invalid);

  // Observable error behavior: if it says it failed, it should be false.
  // If it says it succeeded, emitter should remain usable.
  if (!ok) {
    // If there is an exposed error channel, it should be consistent with failure.
    // We only assert minimal observables (no crash, and good() is a public query).
    EXPECT_TRUE(out.good() || !out.GetLastError().empty());
  } else {
    // Still should be able to emit something after the call.
    const std::string s = EmitSimpleMapToString(out);
    EXPECT_FALSE(s.empty());
  }
}

}  // namespace