#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking the XMP_TextOutputProc to verify its interaction

class MockXMP_TextOutputProc {

public:

    MOCK_METHOD3(Call, XMP_Status(void*, XMP_StringPtr, XMP_StringLen));

};



// Test fixture for TextOutputProcWrapper tests

class TextOutputProcWrapperTest_1275 : public ::testing::Test {

protected:

    void SetUp() override {

        mockProc = new MockXMP_TextOutputProc();

        info = new TOPW_Info(MockXMP_TextOutputProc_Call, mockProc);

    }



    void TearDown() override {

        delete info;

        delete mockProc;

    }



    static XMP_Status MockXMP_TextOutputProc_Call(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {

        return static_cast<MockXMP_TextOutputProc*>(refCon)->Call(refCon, buffer, bufferSize);

    }



    MockXMP_TextOutputProc* mockProc;

    TOPW_Info* info;

};



// Test normal operation

TEST_F(TextOutputProcWrapperTest_1275, NormalOperation_ReturnsSuccess_1275) {

    const char* testBuffer = "test";

    XMP_StringLen bufferSize = 4;



    EXPECT_CALL(*mockProc, Call(::testing::_, ::testing::StrEq(testBuffer), bufferSize))

        .WillOnce(::testing::Return(kXMPErr_NoError));



    XMP_Status result = TextOutputProcWrapper(info, testBuffer, bufferSize);

    EXPECT_EQ(result, kXMPErr_NoError);

}



// Test boundary condition with empty buffer

TEST_F(TextOutputProcWrapperTest_1275, EmptyBuffer_ReturnsSuccess_1275) {

    const char* testBuffer = "";

    XMP_StringLen bufferSize = 0;



    EXPECT_CALL(*mockProc, Call(::testing::_, ::testing::StrEq(testBuffer), bufferSize))

        .WillOnce(::testing::Return(kXMPErr_NoError));



    XMP_Status result = TextOutputProcWrapper(info, testBuffer, bufferSize);

    EXPECT_EQ(result, kXMPErr_NoError);

}



// Test exceptional case where the client callback throws an exception

TEST_F(TextOutputProcWrapperTest_1275, ExceptionInClientCallback_ReturnsFailure_1275) {

    const char* testBuffer = "test";

    XMP_StringLen bufferSize = 4;



    EXPECT_CALL(*mockProc, Call(::testing::_, ::testing::StrEq(testBuffer), bufferSize))

        .WillOnce([](void*, XMP_StringPtr, XMP_StringLen) -> XMP_Status {

            throw std::runtime_error("Test exception");

            return kXMPErr_NoError; // Unreachable

        });



    XMP_Status result = TextOutputProcWrapper(info, testBuffer, bufferSize);

    EXPECT_EQ(result, -1);

}
