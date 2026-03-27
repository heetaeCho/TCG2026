// File: SplashBitmapCMYKEncoder_test_251.cpp
// TEST_ID: 251

#include <gtest/gtest.h>

#include "Stream.h" // ./TestProjects/poppler/poppler/Stream.h

namespace {

class SplashBitmapCMYKEncoderTest_251 : public ::testing::Test {
 protected:
  // Constructing with nullptr keeps the test independent from SplashBitmap creation details.
  SplashBitmapCMYKEncoder makeEncoderWithNullBitmap() {
    return SplashBitmapCMYKEncoder(nullptr);
  }
};

TEST_F(SplashBitmapCMYKEncoderTest_251, GetDictObjectReturnsNull_251) {
  auto enc = makeEncoderWithNullBitmap();

  Object* obj = enc.getDictObject();
  EXPECT_EQ(obj, nullptr);

  // Repeated calls should remain stable/consistent via observable behavior.
  EXPECT_EQ(enc.getDictObject(), nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_251, GetDictObjectViaBasePointerReturnsNull_251) {
  auto enc = makeEncoderWithNullBitmap();

  Stream* asStream = &enc;
  ASSERT_NE(asStream, nullptr);

  EXPECT_EQ(asStream->getDictObject(), nullptr);
}

TEST_F(SplashBitmapCMYKEncoderTest_251, GetDictObjectRemainsNullAfterOtherCalls_251) {
  auto enc = makeEncoderWithNullBitmap();

  // These calls are not asserted for specific return values (black-box),
  // but should be safe to invoke and must not affect getDictObject()'s contract.
  (void)enc.rewind();
  (void)enc.lookChar();
  (void)enc.getChar();
  (void)enc.getPos();
  enc.setPos(0, 0);

  EXPECT_EQ(enc.getDictObject(), nullptr);
}

}  // namespace