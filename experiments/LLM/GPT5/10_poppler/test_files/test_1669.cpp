// DeviceNRecoder_isBinary_test_1669.cc
#include <gtest/gtest.h>

// The class under test is implemented in PSOutputDev.cc (per prompt).
// We include the .cc directly to access the implementation-defined type.
#include "PSOutputDev.cc"

namespace {

class DeviceNRecoderTest_1669 : public ::testing::Test {};

TEST_F(DeviceNRecoderTest_1669, DefaultArgumentReturnsTrue_1669) {
  DeviceNRecoder recoder;
  EXPECT_TRUE(recoder.isBinary());
}

TEST_F(DeviceNRecoderTest_1669, ExplicitTrueReturnsTrue_1669) {
  DeviceNRecoder recoder;
  EXPECT_TRUE(recoder.isBinary(true));
}

TEST_F(DeviceNRecoderTest_1669, ExplicitFalseReturnsTrue_1669) {
  DeviceNRecoder recoder;
  EXPECT_TRUE(recoder.isBinary(false));
}

TEST_F(DeviceNRecoderTest_1669, ConstObjectCanCallIsBinary_1669) {
  const DeviceNRecoder recoder;
  EXPECT_TRUE(recoder.isBinary());
  EXPECT_TRUE(recoder.isBinary(false));
}

}  // namespace