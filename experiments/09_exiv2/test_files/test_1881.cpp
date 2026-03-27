#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/xmpsdk/src/XMPCore_Impl.cpp"



class XMPCore_InitMutexTest : public ::testing::Test {

protected:

    XMP_Mutex mutex;

};



TEST_F(XMPCore_InitMutexTest, InitializeMutex_Success_1881) {

    EXPECT_TRUE(XMP_InitMutex(&mutex));

}



TEST_F(XMPCore_InitMutexTest, InitializeMutex_Failure_1881) {

    // Assuming a scenario where initialization would fail, such as invalid mutex pointer

    XMP_Mutex* nullMutex = nullptr;

    EXPECT_FALSE(XMP_InitMutex(nullMutex));

}
