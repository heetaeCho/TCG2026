#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class RemoteIoTest : public ::testing::Test {

protected:

    RemoteIo* remoteIo;



    void SetUp() override {

        remoteIo = new RemoteIo();

    }



    void TearDown() override {

        delete remoteIo;

    }

};



TEST_F(RemoteIoTest_601, CloseReturnsZero_601) {

    EXPECT_EQ(remoteIo->close(), 0);

}



TEST_F(RemoteIoTest_601, CloseResetsEofAndIdxIfBlocksMapExists_601) {

    remoteIo->p_->blocksMap_ = true;

    remoteIo->p_->eof_ = true;

    remoteIo->p_->idx_ = 5;



    remoteIo->close();



    EXPECT_FALSE(remoteIo->p_->eof_);

    EXPECT_EQ(remoteIo->p_->idx_, 0);

}



TEST_F(RemoteIoTest_601, CloseDoesNotResetEofAndIdxIfBlocksMapDoesNotExist_601) {

    remoteIo->p_->blocksMap_ = false;

    remoteIo->p_->eof_ = true;

    remoteIo->p_->idx_ = 5;



    remoteIo->close();



    EXPECT_TRUE(remoteIo->p_->eof_);

    EXPECT_EQ(remoteIo->p_->idx_, 5);

}



TEST_F(RemoteIoTest_601, CloseDeletesBigBlockIfNotNull_601) {

    remoteIo->bigBlock_ = new byte[10];

    remoteIo->close();

    EXPECT_EQ(remoteIo->bigBlock_, nullptr);

}



TEST_F(RemoteIoTest_601, CloseDoesNotCrashIfBigBlockIsNull_601) {

    remoteIo->bigBlock_ = nullptr;

    EXPECT_NO_THROW(remoteIo->close());

}



// Assuming open is supposed to return 0 on success as a placeholder test

TEST_F(RemoteIoTest_601, OpenReturnsZeroOnSuccess_601) {

    EXPECT_EQ(remoteIo->open(), 0);

}
