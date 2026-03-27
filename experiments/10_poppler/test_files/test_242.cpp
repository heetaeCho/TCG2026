#include <gtest/gtest.h>

#include "Stream.h"



class SplashBitmapCMYKEncoderTest_242 : public ::testing::Test {

protected:

    SplashBitmap *bitmap;

    SplashBitmapCMYKEncoder *encoder;



    void SetUp() override {

        bitmap = new SplashBitmap(100, 100, false);

        encoder = new SplashBitmapCMYKEncoder(bitmap);

    }



    void TearDown() override {

        delete encoder;

        delete bitmap;

    }

};



TEST_F(SplashBitmapCMYKEncoderTest_242, GetKindReturnsWeird_242) {

    EXPECT_EQ(encoder->getKind(), strWeird);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, RewindReturnsFalse_242) {

    EXPECT_FALSE(encoder->rewind());

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetCharReturnsEOF_242) {

    EXPECT_EQ(encoder->getChar(), EOF);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, LookCharReturnsEOF_242) {

    EXPECT_EQ(encoder->lookChar(), EOF);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetPosReturnsZero_242) {

    EXPECT_EQ(encoder->getPos(), 0);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, SetPosDoesNothing_242) {

    encoder->setPos(10, 0);

    EXPECT_EQ(encoder->getPos(), 0);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetPSFilterReturnsEmpty_242) {

    EXPECT_FALSE(encoder->getPSFilter(1, "").has_value());

}



TEST_F(SplashBitmapCMYKEncoderTest_242, IsBinaryReturnsTrue_242) {

    EXPECT_TRUE(encoder->isBinary(true));

}



TEST_F(SplashBitmapCMYKEncoderTest_242, IsEncoderReturnsTrue_242) {

    EXPECT_TRUE(encoder->isEncoder());

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetUnfilteredCharReturnsEOF_242) {

    EXPECT_EQ(encoder->getUnfilteredChar(), EOF);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, UnfilteredRewindReturnsFalse_242) {

    EXPECT_FALSE(encoder->unfilteredRewind());

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetBaseStreamReturnsNullptr_242) {

    EXPECT_EQ(encoder->getBaseStream(), nullptr);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetUndecodedStreamReturnsThis_242) {

    EXPECT_EQ(encoder->getUndecodedStream(), encoder);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetDictReturnsNullptr_242) {

    EXPECT_EQ(encoder->getDict(), nullptr);

}



TEST_F(SplashBitmapCMYKEncoderTest_242, GetDictObjectReturnsNullptr_242) {

    EXPECT_EQ(encoder->getDictObject(), nullptr);

}
