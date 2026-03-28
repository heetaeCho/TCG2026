// TEST_ID: 60
// File: yaml-cpp/test/emitter_precision_operator_test.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

class EmitterPrecisionOperatorTest_60 : public ::testing::Test {
protected:
  std::ostringstream out_;
  YAML::Emitter emitter_{out_};
};

TEST_F(EmitterPrecisionOperatorTest_60, ReturnsSameEmitterReference_60) {
  YAML::_Precision prec(3, 6);

  YAML::Emitter& ret = (emitter_ << prec);

  EXPECT_EQ(&ret, &emitter_);
  EXPECT_TRUE(emitter_.good()) << emitter_.GetLastError();
}

TEST_F(EmitterPrecisionOperatorTest_60, AllowsChainingAfterPrecisionManip_60) {
  YAML::_Precision prec(2, 4);

  YAML::Emitter& ret = (emitter_ << prec).Write("test");

  EXPECT_EQ(&ret, &emitter_);
  EXPECT_TRUE(emitter_.good()) << emitter_.GetLastError();

  const std::string s(emitter_.c_str(), emitter_.size());
  EXPECT_NE(s.find("test"), std::string::npos);
}

TEST_F(EmitterPrecisionOperatorTest_60, AcceptsTemporaryPrecisionObject_60) {
  YAML::Emitter& ret = (emitter_ << YAML::_Precision(1, 2)).Write("x");

  EXPECT_EQ(&ret, &emitter_);
  EXPECT_TRUE(emitter_.good()) << emitter_.GetLastError();

  const std::string s(emitter_.c_str(), emitter_.size());
  EXPECT_NE(s.find("x"), std::string::npos);
}

TEST_F(EmitterPrecisionOperatorTest_60, BoundaryPrecisionValuesDoNotBreakEmitter_60) {
  // Boundary-ish values (including negative) should be handled without crashing.
  // We only assert observable behavior: chaining works and emitter remains usable.
  YAML::Emitter& ret1 = (emitter_ << YAML::_Precision(0, 0)).Write("a");
  EXPECT_EQ(&ret1, &emitter_);
  EXPECT_TRUE(emitter_.good()) << emitter_.GetLastError();

  YAML::Emitter& ret2 = (emitter_ << YAML::_Precision(1000, 1000)).Write("b");
  EXPECT_EQ(&ret2, &emitter_);
  EXPECT_TRUE(emitter_.good()) << emitter_.GetLastError();

  YAML::Emitter& ret3 = (emitter_ << YAML::_Precision(-1, -1)).Write("c");
  EXPECT_EQ(&ret3, &emitter_);
  EXPECT_TRUE(emitter_.good()) << emitter_.GetLastError();

  const std::string s(emitter_.c_str(), emitter_.size());
  EXPECT_NE(s.find("a"), std::string::npos);
  EXPECT_NE(s.find("b"), std::string::npos);
  EXPECT_NE(s.find("c"), std::string::npos);
}

TEST_F(EmitterPrecisionOperatorTest_60, MultiplePrecisionManipulationsRemainChainable_60) {
  YAML::Emitter& ret =
      (emitter_ << YAML::_Precision(3, 6) << YAML::_Precision(4, 8)).Write("done");

  EXPECT_EQ(&ret, &emitter_);
  EXPECT_TRUE(emitter_.good()) << emitter_.GetLastError();

  const std::string s(emitter_.c_str(), emitter_.size());
  EXPECT_NE(s.find("done"), std::string::npos);
}

}  // namespace
