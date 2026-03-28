// TEST_ID: 62
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <yaml-cpp/emitfromevents.h>
#include <yaml-cpp/emitter.h>
#include <yaml-cpp/mark.h>

using ::testing::AllOf;
using ::testing::EndsWith;
using ::testing::HasSubstr;
using ::testing::StartsWith;

namespace {

class EmitFromEventsTest_62 : public ::testing::Test {
protected:
  YAML::Emitter emitter;
  YAML::EmitFromEvents handler{emitter};

  static YAML::Mark AnyMark() { return YAML::Mark(); }
  static YAML::anchor_t NoAnchor() { return YAML::anchor_t(); }
};

TEST_F(EmitFromEventsTest_62, OnMapEndClosesAnEmptyFlowMap_62) {
  const auto mark = AnyMark();

  handler.OnMapStart(mark, /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler.OnMapEnd();

  const std::string out = emitter.c_str();
  EXPECT_THAT(out, AllOf(StartsWith("{"), EndsWith("}")));
}

TEST_F(EmitFromEventsTest_62, OnMapEndClosesFlowMapAfterOneKeyValuePair_62) {
  const auto mark = AnyMark();

  handler.OnMapStart(mark, /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler.OnScalar(mark, /*tag=*/"", NoAnchor(), "k");
  handler.OnScalar(mark, /*tag=*/"", NoAnchor(), "v");
  handler.OnMapEnd();

  const std::string out = emitter.c_str();
  EXPECT_THAT(out, AllOf(StartsWith("{"), EndsWith("}")));
  EXPECT_THAT(out, HasSubstr("k"));
  EXPECT_THAT(out, HasSubstr("v"));
}

#ifndef NDEBUG
TEST_F(EmitFromEventsTest_62, OnMapEndWithoutMapStartDiesInDebug_62) {
  // Observable error behavior: implementation uses assert on internal state/stack.
  ASSERT_DEATH({ handler.OnMapEnd(); }, ".*");
}

TEST_F(EmitFromEventsTest_62, OnMapEndTwiceForSingleMapDiesInDebug_62) {
  const auto mark = AnyMark();

  handler.OnMapStart(mark, /*tag=*/"", NoAnchor(), YAML::EmitterStyle::Flow);
  handler.OnMapEnd();

  ASSERT_DEATH({ handler.OnMapEnd(); }, ".*");
}
#endif  // NDEBUG

}  // namespace
