#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "PSOutputDev.cc"



using namespace testing;



class DeviceNRecoderTest_1670 : public ::testing::Test {

protected:

    class MockStream : public Stream {

    public:

        MOCK_METHOD(bool, rewind, (), (override));

        MOCK_METHOD(StreamKind, getKind, () const, (override));

        MOCK_METHOD(int, getChar, (), (override));

        MOCK_METHOD(int, lookChar, (), (override));

        MOCK_METHOD(std::optional<std::string>, getPSFilter, (int psLevel, const char * indent), (override));

        MOCK_METHOD(bool, isBinary, (bool last), (const, override));

    };



    MockStream mockStream;

    DeviceNRecoder deviceNRecoder{&mockStream, 10, 10, nullptr};



    void SetUp() override {

        // Setup can be used for any common initialization

    }



    void TearDown() override {

        // Teardown can be used for any common cleanup

    }

};



TEST_F(DeviceNRecoderTest_1670, IsEncoderReturnsTrue_1670) {

    EXPECT_TRUE(deviceNRecoder.isEncoder());

}



TEST_F(DeviceNRecoderTest_1670, RewindCallsStreamRewind_1670) {

    EXPECT_CALL(mockStream, rewind()).WillOnce(Return(true));

    EXPECT_TRUE(deviceNRecoder.rewind());

}
