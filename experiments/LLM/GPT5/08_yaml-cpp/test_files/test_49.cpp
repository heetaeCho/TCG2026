// test_emitter_operator_unsigned_int_49.cpp

#include <gtest/gtest.h>

#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

std::string EmitToString(const YAML::Emitter& e) {
  const char* p = e.c_str();
  if (!p) return std::string();
  return std::string(p, e.size());
}

class OperatorUnsignedIntTest_49 : public ::testing::Test {};

}  // namespace

TEST_F(OperatorUnsignedIntTest_49, ReturnsSameReference_49) {
  YAML::Emitter emitter;
  YAML::Emitter& ret = (emitter << 1u);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(OperatorUnsignedIntTest_49, MatchesWriteIntegralTypeForTypicalValue_49) {
  constexpr unsigned int kValue = 123u;

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  via_op << kValue;
  via_direct.WriteIntegralType(kValue);

  EXPECT_EQ(via_op.size(), via_direct.size());
  EXPECT_EQ(EmitToString(via_op), EmitToString(via_direct));
}

TEST_F(OperatorUnsignedIntTest_49, ChainingMatchesSequentialWriteIntegralType_49) {
  constexpr unsigned int a = 7u;
  constexpr unsigned int b = 42u;

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  via_op << a << b;
  via_direct.WriteIntegralType(a).WriteIntegralType(b);

  EXPECT_EQ(via_op.size(), via_direct.size());
  EXPECT_EQ(EmitToString(via_op), EmitToString(via_direct));
}

TEST_F(OperatorUnsignedIntTest_49, BoundaryZeroMatchesWriteIntegralType_49) {
  constexpr unsigned int kValue = 0u;

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  via_op << kValue;
  via_direct.WriteIntegralType(kValue);

  EXPECT_EQ(via_op.size(), via_direct.size());
  EXPECT_EQ(EmitToString(via_op), EmitToString(via_direct));
}

TEST_F(OperatorUnsignedIntTest_49, BoundaryMaxMatchesWriteIntegralType_49) {
  const unsigned int kValue = (std::numeric_limits<unsigned int>::max)();

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  via_op << kValue;
  via_direct.WriteIntegralType(kValue);

  EXPECT_EQ(via_op.size(), via_direct.size());
  EXPECT_EQ(EmitToString(via_op), EmitToString(via_direct));
}

TEST_F(OperatorUnsignedIntTest_49, WithExternalStreamMatchesWriteIntegralType_49) {
  constexpr unsigned int kValue = 999u;

  std::ostringstream oss_op;
  std::ostringstream oss_direct;

  YAML::Emitter via_op(oss_op);
  YAML::Emitter via_direct(oss_direct);

  via_op << kValue;
  via_direct.WriteIntegralType(kValue);

  EXPECT_EQ(oss_op.str(), oss_direct.str());
}

TEST_F(OperatorUnsignedIntTest_49, DoesNotThrowForValidInput_49) {
  YAML::Emitter emitter;
  EXPECT_NO_THROW({ emitter << 321u; });
}
