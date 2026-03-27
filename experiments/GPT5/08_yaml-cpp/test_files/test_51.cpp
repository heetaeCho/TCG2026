// TEST_ID: 51
#include <gtest/gtest.h>

#include <limits>
#include <string>

#include <yaml-cpp/emitter.h>

namespace {

class OperatorUnsignedShortTest_51 : public ::testing::Test {};

TEST_F(OperatorUnsignedShortTest_51, ReturnsSameEmitterReference_51) {
  YAML::Emitter emitter;
  unsigned short v = 7;

  YAML::Emitter& ret = (emitter << v);

  // operator<< should return the same emitter object by reference.
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(OperatorUnsignedShortTest_51, MatchesWriteIntegralTypeOutput_51) {
  const unsigned short values[] = {
      static_cast<unsigned short>(0),
      static_cast<unsigned short>(1),
      static_cast<unsigned short>(42),
      std::numeric_limits<unsigned short>::max(),
  };

  for (unsigned short v : values) {
    YAML::Emitter via_op;
    YAML::Emitter via_direct;

    via_op << v;
    via_direct.WriteIntegralType(v);

    EXPECT_STREQ(via_op.c_str(), via_direct.c_str()) << "value=" << v;
    EXPECT_EQ(via_op.size(), via_direct.size()) << "value=" << v;
    EXPECT_EQ(via_op.good(), via_direct.good()) << "value=" << v;

    if (!via_op.good() || !via_direct.good()) {
      EXPECT_EQ(via_op.GetLastError(), via_direct.GetLastError()) << "value=" << v;
    }
  }
}

TEST_F(OperatorUnsignedShortTest_51, SupportsChainingAndPreservesOrder_51) {
  const unsigned short a = 1;
  const unsigned short b = 2;
  const unsigned short c = 3;

  YAML::Emitter via_op;
  YAML::Emitter via_direct;

  via_op << a << b << c;
  via_direct.WriteIntegralType(a).WriteIntegralType(b).WriteIntegralType(c);

  EXPECT_STREQ(via_op.c_str(), via_direct.c_str());
  EXPECT_EQ(via_op.size(), via_direct.size());
  EXPECT_EQ(via_op.good(), via_direct.good());

  if (!via_op.good() || !via_direct.good()) {
    EXPECT_EQ(via_op.GetLastError(), via_direct.GetLastError());
  }
}

}  // namespace
