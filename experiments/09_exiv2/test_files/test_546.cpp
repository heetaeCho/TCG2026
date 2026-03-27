#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "basicio.cpp"



using namespace Exiv2;



// Mock class for testing FileIo::Impl

class MockFileIoImpl : public FileIo::Impl {

public:

    MOCK_METHOD(int, switchMode, (OpMode opMode), (override));

};



TEST_F(MockFileIoImplTest_546, SwitchModeSameOpModeNoReopen_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opRead;

    EXPECT_CALL(mockImpl, switchMode(OpMode::opRead)).WillOnce(::testing::Return(0));



    int result = mockImpl.switchMode(OpMode::opRead);

    EXPECT_EQ(result, 0);

}



TEST_F(MockFileIoImplTest_546, SwitchModeOpReadNoReopen_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opSeek;

    mockImpl.openMode_ = "r+";

    EXPECT_CALL(mockImpl, switchMode(OpMode::opRead)).WillOnce(::testing::Return(0));



    int result = mockImpl.switchMode(OpMode::opRead);

    EXPECT_EQ(result, 0);

}



TEST_F(MockFileIoImplTest_546, SwitchModeOpWriteNoReopen_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opSeek;

    mockImpl.openMode_ = "w+";

    EXPECT_CALL(mockImpl, switchMode(OpMode::opWrite)).WillOnce(::testing::Return(0));



    int result = mockImpl.switchMode(OpMode::opWrite);

    EXPECT_EQ(result, 0);

}



TEST_F(MockFileIoImplTest_546, SwitchModeOpSeekNoReopenFromOpRead_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opRead;

    EXPECT_CALL(mockImpl, switchMode(OpMode::opSeek)).WillOnce(::testing::Return(0));



    int result = mockImpl.switchMode(OpMode::opSeek);

    EXPECT_EQ(result, 0);

}



TEST_F(MockFileIoImplTest_546, SwitchModeOpSeekNoReopenFromOpWrite_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opWrite;

    EXPECT_CALL(mockImpl, switchMode(OpMode::opSeek)).WillOnce(::testing::Return(0));



    int result = mockImpl.switchMode(OpMode::opSeek);

    EXPECT_EQ(result, 0);

}



TEST_F(MockFileIoImplTest_546, SwitchModeOpReadReopenFailure_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opWrite;

    mockImpl.openMode_ = "w";

    EXPECT_CALL(mockImpl, switchMode(OpMode::opRead)).WillOnce(::testing::Return(-1));



    int result = mockImpl.switchMode(OpMode::opRead);

    EXPECT_EQ(result, -1);

}



TEST_F(MockFileIoImplTest_546, SwitchModeOpWriteReopenFailure_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opRead;

    mockImpl.openMode_ = "r";

    EXPECT_CALL(mockImpl, switchMode(OpMode::opWrite)).WillOnce(::testing::Return(-1));



    int result = mockImpl.switchMode(OpMode::opWrite);

    EXPECT_EQ(result, -1);

}



TEST_F(MockFileIoImplTest_546, SwitchModeOpSeekReopenFailure_546) {

    MockFileIoImpl mockImpl("dummy_path");

    mockImpl.opMode_ = OpMode::opRead;

    mockImpl.openMode_ = "r";

    EXPECT_CALL(mockImpl, switchMode(OpMode::opSeek)).WillOnce(::testing::Return(-1));



    int result = mockImpl.switchMode(OpMode::opSeek);

    EXPECT_EQ(result, -1);

}
