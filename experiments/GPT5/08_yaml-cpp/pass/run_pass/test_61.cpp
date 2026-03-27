// File: ./TestProjects/yaml-cpp/test/emitfromevents_onsequenceend_test.cpp

#include <gtest/gtest.h>

#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emitfromevents.h"
#include "yaml-cpp/mark.h"

namespace {

class EmitFromEventsOnSequenceEndTest_61 : public ::testing::Test {
 protected:
  YAML::Emitter emitter_;
  YAML::EmitFromEvents handler_{emitter_};

  static YAML::Mark Mark() { return YAML::Mark(); }

  // Use a conservative anchor value that should be valid for "no anchor".
  // yaml-cpp commonly uses 0 for "no anchor" in older versions; this keeps the
  // test black-box and interface-driven.
  static YAML::anchor_t NoAnchor() { return static_cast<YAML::anchor_t>(0); }
};

TEST_F(EmitFromEventsOnSequenceEndTest_61, EmptyFlowSequenceEmitsBrackets_61) {
  handler_.OnSequenceStart(Mark(), /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler_.OnSequenceEnd();

  // Using Flow style should yield a stable representation for an empty sequence.
  EXPECT_EQ(std::string(emitter_.c_str()), "[]");
}

TEST_F(EmitFromEventsOnSequenceEndTest_61, NestedEmptyFlowSequencesEmitNestedBrackets_61) {
  handler_.OnSequenceStart(Mark(), /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler_.OnSequenceStart(Mark(), /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler_.OnSequenceEnd();
  handler_.OnSequenceEnd();

  EXPECT_EQ(std::string(emitter_.c_str()), "[[]]");
}

TEST_F(EmitFromEventsOnSequenceEndTest_61, MultipleSiblingSequencesEmitConcatenatedContent_61) {
  handler_.OnSequenceStart(Mark(), /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler_.OnSequenceEnd();
  const std::string first = emitter_.c_str();

  handler_.OnSequenceStart(Mark(), /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler_.OnSequenceEnd();
  const std::string second = emitter_.c_str();

  // Observable behavior: each end should write EndSeq to the underlying emitter.
  EXPECT_EQ(first, "[]");
  EXPECT_EQ(second, "[][]");
}

#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST_F(EmitFromEventsOnSequenceEndTest_61, OnSequenceEndWithoutSequenceStartDiesInDebug_61) {
  // Observable error behavior: OnSequenceEnd asserts on internal state.
  EXPECT_DEATH(
      {
        // No OnSequenceStart() -> should violate internal state precondition in debug.
        handler_.OnSequenceEnd();
      },
      "");
}
#endif

}  // namespace
