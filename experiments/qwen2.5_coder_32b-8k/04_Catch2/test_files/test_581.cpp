#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_section.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&&), (override));

    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&&), (override));

};



class SectionTest_581 : public ::testing::Test {

protected:

    SourceLineInfo lineInfo{"test_file.cpp", 42};

    StringRef name = "TestSection";

    Counts initialAssertions;

    MockResultCapture mockResultCapture;



    void SetUp() override {

        // Redirect getResultCapture to return our mock

        setResultCapture(&mockResultCapture);

    }



    void TearDown() override {

        // Reset result capture to default after tests

        setResultCapture(nullptr);

    }

};



TEST_F(SectionTest_581, SectionIncluded_NotifySectionEnded_581) {

    EXPECT_CALL(mockResultCapture, sectionStarted(_, _, _)).WillOnce(Return(true));

    EXPECT_CALL(mockResultCapture, sectionEnded(_));



    Section section(lineInfo, name, nullptr);

}



TEST_F(SectionTest_581, SectionNotIncluded_NoNotification_581) {

    EXPECT_CALL(mockResultCapture, sectionStarted(_, _, _)).WillOnce(Return(false));



    Section section(lineInfo, name, nullptr);

}



TEST_F(SectionTest_581, ExceptionOccurred_NotifySectionEndedEarly_581) {

    EXPECT_CALL(mockResultCapture, sectionStarted(_, _, _)).WillOnce(Return(true));

    EXPECT_CALL(mockResultCapture, sectionEndedEarly(_));



    try {

        Section section(lineInfo, name, nullptr);

        throw std::runtime_error("Test exception");

    } catch (...) {

        // Exception handling

    }

}
