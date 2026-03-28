#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Stream.h"



class SplashBitmapCMYKEncoderTest : public ::testing::Test {

protected:

    class MockSplashBitmap {};

    std::unique_ptr<SplashBitmap> mockBitmap;

    std::unique_ptr<SplashBitmapCMYKEncoder> encoder;



    void SetUp() override {

        mockBitmap = std::make_unique<MockSplashBitmap>();

        encoder = std::make_unique<SplashBitmapCMYKEncoder>(mockBitmap.get());

    }

};



TEST_F(SplashBitmapCMYKEncoderTest_251, RewindReturnsTrue_251) {

    EXPECT_TRUE(encoder->rewind());

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetCharReturnsEOFWhenBufferEmpty_251) {

    EXPECT_EQ(encoder->getChar(), EOF);

}



TEST_F(SplashBitmapCMYKEncoderTest_251, LookCharReturnsEOFWhenBufferEmpty_251) {

    EXPECT_EQ(encoder->lookChar(), EOF);

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetPosReturnsZeroInitially_251) {

    EXPECT_EQ(encoder->getPos(), 0);

}



TEST_F(SplashBitmapCMYKEncoderTest_251, SetPosDoesNotThrow_251) {

    EXPECT_NO_THROW(encoder->setPos(0, 0));

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetKindReturnsStreamKindUnknownByDefault_251) {

    EXPECT_EQ(encoder->getKind(), StreamKind::unknown);

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetPSFilterReturnsEmptyOptional_251) {

    EXPECT_FALSE(encoder->getPSFilter(0, "").has_value());

}



TEST_F(SplashBitmapCMYKEncoderTest_251, IsBinaryAlwaysReturnsTrue_251) {

    EXPECT_TRUE(encoder->isBinary(true));

}



TEST_F(SplashBitmapCMYKEncoderTest_251, IsEncoderAlwaysReturnsTrue_251) {

    EXPECT_TRUE(encoder->isEncoder());

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetUnfilteredCharReturnsEOFWhenBufferEmpty_251) {

    EXPECT_EQ(encoder->getUnfilteredChar(), EOF);

}



TEST_F(SplashBitmapCMYKEncoderTest_251, UnfilteredRewindReturnsTrue_251) {

    EXPECT_TRUE(encoder->unfilteredRewind());

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetBaseStreamReturnsNullptr_251) {

    EXPECT_EQ(encoder->getBaseStream(), nullptr);

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetUndecodedStreamReturnsSelf_251) {

    EXPECT_EQ(encoder->getUndecodedStream(), encoder.get());

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetDictReturnsNullptr_251) {

    EXPECT_EQ(encoder->getDict(), nullptr);

}



TEST_F(SplashBitmapCMYKEncoderTest_251, GetDictObjectReturnsNullptr_251) {

    EXPECT_EQ(encoder->getDictObject(), nullptr);

}
