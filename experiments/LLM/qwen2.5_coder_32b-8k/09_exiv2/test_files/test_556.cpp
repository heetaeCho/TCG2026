#include <gtest/gtest.h>

#include "exiv2/basicio.hpp"



using namespace Exiv2;



class FileIoTest_556 : public ::testing::Test {

protected:

    FileIo* fileIo;



    void SetUp() override {

        fileIo = new FileIo("dummy_path");

    }



    void TearDown() override {

        delete fileIo;

    }

};



TEST_F(FileIoTest_556, SeekFromBeginning_556) {

    EXPECT_EQ(fileIo->seek(10, BasicIo::beg), 0);

}



TEST_F(FileIoTest_556, SeekFromCurrent_556) {

    EXPECT_EQ(fileIo->seek(10, BasicIo::cur), 0);

}



TEST_F(FileIoTest_556, SeekFromEnd_556) {

    EXPECT_EQ(fileIo->seek(-10, BasicIo::end), 0);

}



TEST_F(FileIoTest_556, SeekInvalidPosition_556) {

    EXPECT_NE(fileIo->seek(10, static_cast<BasicIo::Position>(3)), 0);

}



TEST_F(FileIoTest_556, SeekSwitchModeFailure_556) {

    // Assuming switchMode returns non-zero on failure

    fileIo->p_->opMode_ = FileIo::Impl::opRead; // Force a mode change to simulate failure

    EXPECT_EQ(fileIo->seek(10, BasicIo::beg), 1);

}
