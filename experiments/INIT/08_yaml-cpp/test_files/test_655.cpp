// TEST_ID: 655
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/stlemitter.h"

// EmitSeq is the collaborator this operator<< delegates to.
// In yaml-cpp it is typically declared in emitterutils.h; include if available.
#include "yaml-cpp/emitterutils.h"

namespace {

class StdEmitterVectorOperatorTest_655 : public ::testing::Test {};

TEST_F(StdEmitterVectorOperatorTest_655, ReturnsSameEmitterReference_655) {
  YAML::Emitter out;
  std::vector<int> v{1, 2, 3};

  YAML::Emitter* const addr_before = &out;
  YAML::Emitter& ref = (out << v);

  EXPECT_EQ(&ref, addr_before);
}

TEST_F(StdEmitterVectorOperatorTest_655, MatchesEmitSeqForIntVector_655) {
  const std::vector<int> v{1, 2, 3, 4};

  YAML::Emitter via_operator;
  YAML::Emitter via_emitseq;

  via_operator << v;
  YAML::EmitSeq(via_emitseq, v);

  EXPECT_STREQ(via_operator.c_str(), via_emitseq.c_str());
  EXPECT_EQ(via_operator.size(), via_emitseq.size());
}

TEST_F(StdEmitterVectorOperatorTest_655, MatchesEmitSeqForStringVector_655) {
  const std::vector<std::string> v{"alpha", "beta", "gamma"};

  YAML::Emitter via_operator;
  YAML::Emitter via_emitseq;

  via_operator << v;
  YAML::EmitSeq(via_emitseq, v);

  EXPECT_STREQ(via_operator.c_str(), via_emitseq.c_str());
  EXPECT_EQ(via_operator.size(), via_emitseq.size());
}

TEST_F(StdEmitterVectorOperatorTest_655, MatchesEmitSeqForEmptyVector_655) {
  const std::vector<int> empty;

  YAML::Emitter via_operator;
  YAML::Emitter via_emitseq;

  via_operator << empty;
  YAML::EmitSeq(via_emitseq, empty);

  EXPECT_STREQ(via_operator.c_str(), via_emitseq.c_str());
  EXPECT_EQ(via_operator.size(), via_emitseq.size());
}

TEST_F(StdEmitterVectorOperatorTest_655, MatchesEmitSeqForNestedVector_655) {
  const std::vector<std::vector<int>> nested{{1, 2}, {}, {3}};

  YAML::Emitter via_operator;
  YAML::Emitter via_emitseq;

  via_operator << nested;
  YAML::EmitSeq(via_emitseq, nested);

  EXPECT_STREQ(via_operator.c_str(), via_emitseq.c_str());
  EXPECT_EQ(via_operator.size(), via_emitseq.size());
}

TEST_F(StdEmitterVectorOperatorTest_655, PreservesEmitterGoodStateOnBadStream_655) {
  // Create an ostream already in a bad state; we don't assume how YAML::Emitter reacts,
  // only that operator<< returns the same emitter and does not unexpectedly flip good().
  std::ostringstream oss;
  oss.setstate(std::ios::badbit);

  YAML::Emitter out(oss);
  const bool good_before = out.good();

  std::vector<int> v{1, 2, 3};
  YAML::Emitter& ref = (out << v);

  EXPECT_EQ(&ref, &out);
  EXPECT_EQ(out.good(), good_before);
}

TEST_F(StdEmitterVectorOperatorTest_655, WorksForLargerVector_655) {
  std::vector<int> v;
  v.reserve(200);
  for (int i = 0; i < 200; ++i) v.push_back(i);

  YAML::Emitter via_operator;
  YAML::Emitter via_emitseq;

  via_operator << v;
  YAML::EmitSeq(via_emitseq, v);

  EXPECT_STREQ(via_operator.c_str(), via_emitseq.c_str());
  EXPECT_EQ(via_operator.size(), via_emitseq.size());
}

}  // namespace