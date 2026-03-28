// File: test/emitter_operator_bool_test_38.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterOperatorBoolTest_38 : public ::testing::Test {
protected:
  static std::string EmitViaWrite(bool v) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out.Write(v);
    return ss.str();
  }

  static std::string EmitViaOperator(bool v) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out << v;
    return ss.str();
  }

  static std::string EmitViaWriteChain(bool a, bool b) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out.Write(a).Write(b);
    return ss.str();
  }

  static std::string EmitViaOperatorChain(bool a, bool b) {
    std::stringstream ss;
    YAML::Emitter out(ss);
    out << a << b;
    return ss.str();
  }
};

TEST_F(EmitterOperatorBoolTest_38, TrueMatchesWriteOutput_38) {
  EXPECT_EQ(EmitViaOperator(true), EmitViaWrite(true));
}

TEST_F(EmitterOperatorBoolTest_38, FalseMatchesWriteOutput_38) {
  EXPECT_EQ(EmitViaOperator(false), EmitViaWrite(false));
}

TEST_F(EmitterOperatorBoolTest_38, ReturnsSameEmitterReference_38) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  YAML::Emitter& ref = (out << true);
  EXPECT_EQ(&ref, &out);

  // Also ensure chaining compiles and uses the same object reference.
  YAML::Emitter& ref2 = (out << false);
  EXPECT_EQ(&ref2, &out);
}

TEST_F(EmitterOperatorBoolTest_38, ChainingMatchesWriteChaining_38) {
  EXPECT_EQ(EmitViaOperatorChain(true, false), EmitViaWriteChain(true, false));
  EXPECT_EQ(EmitViaOperatorChain(false, true), EmitViaWriteChain(false, true));
}

TEST_F(EmitterOperatorBoolTest_38, DoesNotThrowAndKeepsGoodStateIfInitiallyGood_38) {
  std::stringstream ss;
  YAML::Emitter out(ss);

  ASSERT_TRUE(out.good());
  EXPECT_NO_THROW(out << true);
  EXPECT_NO_THROW(out << false);
  EXPECT_TRUE(out.good());
}

}  // namespace
