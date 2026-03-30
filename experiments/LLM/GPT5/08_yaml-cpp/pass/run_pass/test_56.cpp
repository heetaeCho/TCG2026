// TEST_ID: 56
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class OperatorFloatTest_56 : public ::testing::Test {
protected:
  static std::string EmitterToString(const YAML::Emitter& e) {
    const char* p = e.c_str();
    if (!p) return {};
    return std::string(p, p + e.size());
  }
};

TEST_F(OperatorFloatTest_56, ReturnsSameEmitterReference_56) {
  YAML::Emitter emitter;
  YAML::Emitter& ref = (emitter << 1.0f);
  EXPECT_EQ(&ref, &emitter);
}

TEST_F(OperatorFloatTest_56, MatchesWriteStreamableForNormalFloat_56) {
  const float v = 3.1415926f;

  YAML::Emitter via_op;
  YAML::Emitter via_api;

  via_op << v;
  via_api.WriteStreamable(v);

  EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_api));
  EXPECT_EQ(via_op.good(), via_api.good());
  EXPECT_EQ(via_op.GetLastError(), via_api.GetLastError());
}

TEST_F(OperatorFloatTest_56, MatchesWriteStreamableWhenChained_56) {
  const float a = 1.0f;
  const float b = -2.5f;
  const float c = 0.125f;

  YAML::Emitter via_op;
  YAML::Emitter via_api;

  via_op << a << b << c;
  via_api.WriteStreamable(a).WriteStreamable(b).WriteStreamable(c);

  EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_api));
  EXPECT_EQ(via_op.good(), via_api.good());
  EXPECT_EQ(via_op.GetLastError(), via_api.GetLastError());
}

TEST_F(OperatorFloatTest_56, MatchesWriteStreamableForZeroAndNegativeZero_56) {
  const float pos_zero = 0.0f;
  const float neg_zero = -0.0f;

  YAML::Emitter op_pos, api_pos;
  op_pos << pos_zero;
  api_pos.WriteStreamable(pos_zero);

  EXPECT_EQ(EmitterToString(op_pos), EmitterToString(api_pos));
  EXPECT_EQ(op_pos.good(), api_pos.good());
  EXPECT_EQ(op_pos.GetLastError(), api_pos.GetLastError());

  YAML::Emitter op_neg, api_neg;
  op_neg << neg_zero;
  api_neg.WriteStreamable(neg_zero);

  EXPECT_EQ(EmitterToString(op_neg), EmitterToString(api_neg));
  EXPECT_EQ(op_neg.good(), api_neg.good());
  EXPECT_EQ(op_neg.GetLastError(), api_neg.GetLastError());
}

TEST_F(OperatorFloatTest_56, MatchesWriteStreamableForInfinityAndNaN_56) {
  const float inf = std::numeric_limits<float>::infinity();
  const float nan = std::numeric_limits<float>::quiet_NaN();

  // +infinity
  {
    YAML::Emitter via_op;
    YAML::Emitter via_api;

    via_op << inf;
    via_api.WriteStreamable(inf);

    EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_api));
    EXPECT_EQ(via_op.good(), via_api.good());
    EXPECT_EQ(via_op.GetLastError(), via_api.GetLastError());
  }

  // NaN
  {
    // sanity: ensure it's actually NaN on this platform
    ASSERT_TRUE(std::isnan(nan));

    YAML::Emitter via_op;
    YAML::Emitter via_api;

    via_op << nan;
    via_api.WriteStreamable(nan);

    EXPECT_EQ(EmitterToString(via_op), EmitterToString(via_api));
    EXPECT_EQ(via_op.good(), via_api.good());
    EXPECT_EQ(via_op.GetLastError(), via_api.GetLastError());
  }
}

TEST_F(OperatorFloatTest_56, WritesToProvidedOstream_56) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  emitter << 2.75f;

  const std::string emitter_out = EmitterToString(emitter);
  const std::string stream_out = ss.str();

  // Observable behavior: something should be written.
  EXPECT_FALSE(emitter_out.empty());
  EXPECT_FALSE(stream_out.empty());

  // If the emitter is backed by the provided stream, they should match.
  EXPECT_EQ(stream_out, emitter_out);
}

TEST_F(OperatorFloatTest_56, ErrorStateIsObservableIfNotGood_56) {
  // We don't assume an error will happen. We only assert that if it does,
  // it's observable via GetLastError() and consistent with WriteStreamable.
  const float v = 42.0f;

  YAML::Emitter via_op;
  YAML::Emitter via_api;

  via_op << v;
  via_api.WriteStreamable(v);

  ASSERT_EQ(via_op.good(), via_api.good());
  ASSERT_EQ(via_op.GetLastError(), via_api.GetLastError());

  if (!via_op.good()) {
    EXPECT_FALSE(via_op.GetLastError().empty());
  }
}

}  // namespace
