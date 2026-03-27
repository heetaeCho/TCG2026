// TEST_ID: 248
// File: SplashBitmapCMYKEncoder_test_248.cpp

#include <gtest/gtest.h>

#include "Stream.h" // Provides SplashBitmapCMYKEncoder, Stream, BaseStream

namespace {

class SplashBitmapCMYKEncoderTest_248 : public ::testing::Test {};

TEST_F(SplashBitmapCMYKEncoderTest_248, GetBaseStreamReturnsNull_248) {
  // Construct with a null bitmap pointer (pointer type only; no private access).
  SplashBitmapCMYKEncoder enc(nullptr);

  BaseStream* bs = enc.getBaseStream();
  EXPECT_EQ(bs, nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_248, GetBaseStreamIsIdempotent_248) {
  SplashBitmapCMYKEncoder enc(nullptr);

  BaseStream* bs1 = enc.getBaseStream();
  BaseStream* bs2 = enc.getBaseStream();

  EXPECT_EQ(bs1, nullptr);
  EXPECT_EQ(bs2, nullptr);
  EXPECT_EQ(bs1, bs2);
}

TEST_F(SplashBitmapCMYKEncoderTest_248, GetBaseStreamViaStreamPointerReturnsNull_248) {
  SplashBitmapCMYKEncoder enc(nullptr);

  Stream* s = &enc;
  ASSERT_NE(s, nullptr);

  BaseStream* bs = s->getBaseStream();
  EXPECT_EQ(bs, nullptr);
}

}  // namespace