#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch_assertion_handler.hpp"

#include "catch_interfaces_capture.hpp"



using namespace Catch;

using testing::NiceMock;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo & info, std::string && message, AssertionReaction & reaction), (override));

};



class AssertionHandlerTest_555 : public ::testing::Test {

protected:

    NiceMock<MockResultCapture> mockResultCapture;

    AssertionInfo assertionInfo{"", SourceLineInfo{}, ""};

    AssertionReaction reaction{};

    AssertionHandler handler{"", SourceLineInfo{}, "", ResultDisposition::Normal};



    void SetUp() override {

        handler.m_assertionInfo = assertionInfo;

        handler.m_reaction = reaction;

    }

};



TEST_F(AssertionHandlerTest_555, HandleUnexpectedInflightException_CallsResultCaptureWithCorrectParams_555) {

    EXPECT_CALL(mockResultCapture, handleUnexpectedInflightException(testing::Ref(assertionInfo), testing::_, testing::Ref(reaction)));



    handler.handleUnexpectedInflightException();

}
