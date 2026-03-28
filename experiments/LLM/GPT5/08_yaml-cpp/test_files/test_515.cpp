// File: ./TestProjects/yaml-cpp/test/emitter_good_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterGoodTest_515 : public ::testing::Test {};

TEST_F(EmitterGoodTest_515, DefaultConstructedEmitterIsGood_515) {
  YAML::Emitter emitter;
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterGoodTest_515, StreamConstructedEmitterIsGood_515) {
  std::ostringstream oss;
  YAML::Emitter emitter(oss);
  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterGoodTest_515, GoodIsCallableOnConstEmitter_515) {
  const YAML::Emitter emitter;
  const bool g = emitter.good();
  // Primary purpose: const-correctness and callable API. Still assert something.
  EXPECT_TRUE(g);
}

TEST_F(EmitterGoodTest_515, GoodRemainsTrueAfterNoopWrites_515) {
  YAML::Emitter emitter;

  EXPECT_NO_THROW(emitter.Write(std::string()));
  EXPECT_NO_THROW(emitter.Write("", 0));
  EXPECT_NO_THROW(emitter.Write(true));
  EXPECT_NO_THROW(emitter.Write('x'));

  EXPECT_TRUE(emitter.good());
}

TEST_F(EmitterGoodTest_515, SettingsCallsDoNotThrowAndGoodMatchesErrorReporting_515) {
  YAML::Emitter emitter;

  // Boundary-ish values; we avoid assuming which are "valid", but calls must be safe.
  EXPECT_NO_THROW((void)emitter.SetIndent(0));
  EXPECT_NO_THROW((void)emitter.SetPreCommentIndent(0));
  EXPECT_NO_THROW((void)emitter.SetPostCommentIndent(0));
  EXPECT_NO_THROW((void)emitter.SetFloatPrecision(0));
  EXPECT_NO_THROW((void)emitter.SetDoublePrecision(0));

  // Observable consistency check without inferring exact internal rules:
  // if the emitter reports not-good, it should have some error text.
  if (!emitter.good()) {
    EXPECT_FALSE(emitter.GetLastError().empty());
  } else {
    SUCCEED();
  }
}

TEST_F(EmitterGoodTest_515, GoodCanBePolledRepeatedly_515) {
  YAML::Emitter emitter;

  const bool g1 = emitter.good();
  const bool g2 = emitter.good();
  const bool g3 = emitter.good();

  // Polling should be stable in the absence of other actions.
  EXPECT_EQ(g1, g2);
  EXPECT_EQ(g2, g3);
}

}  // namespace