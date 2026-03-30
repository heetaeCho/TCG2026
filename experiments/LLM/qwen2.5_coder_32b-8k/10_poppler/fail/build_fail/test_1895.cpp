#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    #include "TestProjects/poppler/poppler/Error.h"

}



using ::testing::_;

using ::testing::Invoke;

using ::testing::Return;



// Mock class for ErrorCallback

class MockErrorCallback {

public:

    MOCK_METHOD3(call, void(ErrorCategory category, Goffset pos, const char* msg));

};



MockErrorCallback mockErrorCb;



void errorCbkWrapper(ErrorCategory category, Goffset pos, const char* msg) {

    mockErrorCb.call(category, pos, msg);

}



class ErrorTest_1895 : public ::testing::Test {

protected:

    void SetUp() override {

        globalParams->setErrQuiet(false);

        errorCbk = &errorCbkWrapper;

    }



    void TearDown() override {

        errorCbk = nullptr;

    }

};



TEST_F(ErrorTest_1895, NormalOperationWithValidMessage_1895) {

    EXPECT_CALL(mockErrorCb, call(kSyntaxWarning, 0, "Valid message")).Times(1);

    error(kSyntaxWarning, 0, "Valid message");

}



TEST_F(ErrorTest_1895, BoundaryConditionWithEmptyMessage_1895) {

    EXPECT_CALL(mockErrorCb, call(kSyntaxWarning, 0, "")).Times(1);

    error(kSyntaxWarning, 0, "");

}



TEST_F(ErrorTest_1895, NormalOperationWithPosition_1895) {

    EXPECT_CALL(mockErrorCb, call(kSyntaxWarning, 42, "Message at position 42")).Times(1);

    error(kSyntaxWarning, 42, "Message at position %d", 42);

}



TEST_F(ErrorTest_1895, BoundaryConditionWithNegativePosition_1895) {

    EXPECT_CALL(mockErrorCb, call(kSyntaxWarning, -1, "Negative position message")).Times(1);

    error(kSyntaxWarning, -1, "Negative position message");

}



TEST_F(ErrorTest_1895, MessageWithControlCharacters_1895) {

    EXPECT_CALL(mockErrorCb, call(kSyntaxWarning, 0, "<0a>Valid<20>message")).Times(1);

    error(kSyntaxWarning, 0, "\nValid message");

}



TEST_F(ErrorTest_1895, MessageWithExtendedASCIICharacters_1895) {

    EXPECT_CALL(mockErrorCb, call(kSyntaxWarning, 0, "<c3>a<e9>z")).Times(1);

    error(kSyntaxWarning, 0, "café");

}



TEST_F(ErrorTest_1895, MessageWithNonPrintableCharacters_1895) {

    EXPECT_CALL(mockErrorCb, call(kSyntaxWarning, 0, "<7f><80>Valid<ff>message")).Times(1);

    error(kSyntaxWarning, 0, "\x7f\x80Valid\xffMessage");

}



TEST_F(ErrorTest_1895, ErrQuietEnabledDoesNotInvokeCallback_1895) {

    globalParams->setErrQuiet(true);

    EXPECT_CALL(mockErrorCb, call(_, _, _)).Times(0);

    error(kSyntaxWarning, 0, "This should not be printed");

}



TEST_F(ErrorTest_1895, InvalidCategoryDoesNotInvokeCallback_1895) {

    EXPECT_CALL(mockErrorCb, call(static_cast<ErrorCategory>(10), 0, "Invalid category")).Times(0);

    error(static_cast<ErrorCategory>(10), 0, "Invalid category");

}
