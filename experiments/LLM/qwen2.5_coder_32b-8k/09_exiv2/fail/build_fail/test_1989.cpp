#include <gtest/gtest.h>

#include "XMPMeta.hpp"



class XMPMetaTest_1989 : public ::testing::Test {

protected:

    virtual void SetUp() override {

        // Initialize the library if needed before each test

        XMPMeta::Initialize();

    }



    virtual void TearDown() override {

        // Terminate the library after each test

        WXMPMeta_Terminate_1();

    }

};



// Test normal operation of Terminate function

TEST_F(XMPMetaTest_1989, TerminateNormalOperation_1989) {

    // Simply call the terminate function and expect no crash or exception

    WXMPMeta_Terminate_1();

}



// Test boundary condition where Terminate is called multiple times consecutively

TEST_F(XMPMetaTest_1989, TerminateMultipleTimes_1989) {

    WXMPMeta_Terminate_1();

    WXMPMeta_Terminate_1(); // Ensure no crash on repeated calls

}



// Test if Initialize and Terminate can be called in sequence multiple times

TEST_F(XMPMetaTest_1989, InitializeAndTerminateSequence_1989) {

    XMPMeta::Initialize();

    WXMPMeta_Terminate_1();

    XMPMeta::Initialize(); // Ensure re-initialization works after termination

    WXMPMeta_Terminate_1();

}



// Test if GetVersionInfo provides consistent results

TEST_F(XMPMetaTest_1989, GetVersionInfoConsistency_1989) {

    XMP_VersionInfo info1, info2;

    XMPMeta::GetVersionInfo(&info1);

    WXMPMeta_Terminate_1();

    XMPMeta::Initialize(); // Reinitialize

    XMPMeta::GetVersionInfo(&info2);



    EXPECT_EQ(info1.major, info2.major);

    EXPECT_EQ(info1.minor, info2.minor);

    EXPECT_EQ(info1.micro, info2.micro);

}



// Test if Initialize returns true indicating success

TEST_F(XMPMetaTest_1989, InitializeReturnsTrue_1989) {

    bool result = XMPMeta::Initialize();

    EXPECT_TRUE(result);

}
