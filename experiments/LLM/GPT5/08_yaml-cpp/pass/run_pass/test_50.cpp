// TEST_ID: 50
#include <gtest/gtest.h>

#include <climits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class OperatorLeftShiftShortTest_50 : public ::testing::Test {
 protected:
  static std::string EmitViaOperator(short v) {
    std::ostringstream oss;
    YAML::Emitter out(oss);
    out << v;
    return oss.str();
  }

  static std::string EmitViaWriteIntegralType(short v) {
    std::ostringstream oss;
    YAML::Emitter out(oss);
    out.WriteIntegralType(v);
    return oss.str();
  }
};

TEST_F(OperatorLeftShiftShortTest_50, ReturnsSameEmitterReferenceForChaining_50) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  YAML::Emitter* p_before = &out;
  YAML::Emitter* p_after = &(out << static_cast<short>(7));

  EXPECT_EQ(p_before, p_after);
}

TEST_F(OperatorLeftShiftShortTest_50, OutputMatchesWriteIntegralTypeForTypicalValues_50) {
  const short values[] = {static_cast<short>(0), static_cast<short>(1), static_cast<short>(-1),
                          static_cast<short>(42), static_cast<short>(-42)};

  for (short v : values) {
    EXPECT_EQ(EmitViaWriteIntegralType(v), EmitViaOperator(v)) << "v=" << v;
  }
}

TEST_F(OperatorLeftShiftShortTest_50, OutputMatchesWriteIntegralTypeForBoundaryValues_50) {
  const short values[] = {static_cast<short>(SHRT_MIN), static_cast<short>(SHRT_MAX)};

  for (short v : values) {
    EXPECT_EQ(EmitViaWriteIntegralType(v), EmitViaOperator(v)) << "v=" << v;
  }
}

TEST_F(OperatorLeftShiftShortTest_50, SupportsMultipleInsertionsAndChaining_50) {
  std::ostringstream oss_op;
  YAML::Emitter out_op(oss_op);
  out_op << static_cast<short>(1) << static_cast<short>(-2) << static_cast<short>(3);

  std::ostringstream oss_ref;
  YAML::Emitter out_ref(oss_ref);
  out_ref.WriteIntegralType(static_cast<short>(1))
      .WriteIntegralType(static_cast<short>(-2))
      .WriteIntegralType(static_cast<short>(3));

  EXPECT_EQ(oss_ref.str(), oss_op.str());
}

TEST_F(OperatorLeftShiftShortTest_50, DoesNotThrowEvenIfUnderlyingStreamIsBad_50) {
  std::ostringstream oss;
  oss.setstate(std::ios::badbit);  // simulate a stream already in an error state

  YAML::Emitter out(oss);
  EXPECT_NO_THROW({ out << static_cast<short>(123); });
}

}  // namespace
