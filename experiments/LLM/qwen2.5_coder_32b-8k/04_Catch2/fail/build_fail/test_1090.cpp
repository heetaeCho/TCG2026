#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_section.hpp"

#include "catch2/internal/catch_result_capture.hpp"

#include "catch2/internal/catch_timer.hpp"



using namespace Catch;

using namespace testing;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD(bool, sectionStarted, (StringRef, SourceLineInfo, std::vector<AssertionInfo>&), (override));

};



TEST_F(MockResultCaptureTest_1090, SectionStartedCalledWithCorrectParameters_1090) {

    MockResultCapture mock;

    StringRef name("test_section");

    SourceLineInfo lineInfo("file.cpp", 42);

    std::vector<AssertionInfo> assertions;



    EXPECT_CALL(mock, sectionStarted(name, lineInfo, Ref(assertions))).WillOnce(Return(true));



    Section section(lineInfo, name, "");

}



TEST_F(MockResultCaptureTest_1090, SectionNotIncludedIfSectionStartedReturnsFalse_1090) {

    MockResultCapture mock;

    StringRef name("test_section");

    SourceLineInfo lineInfo("file.cpp", 42);

    std::vector<AssertionInfo> assertions;



    EXPECT_CALL(mock, sectionStarted(name, lineInfo, Ref(assertions))).WillOnce(Return(false));



    Section section(lineInfo, name, "");



    EXPECT_EQ(section.m_sectionIncluded, false);

}



TEST_F(MockResultCaptureTest_1090, InfoNameSetIfSectionIncluded_1090) {

    MockResultCapture mock;

    StringRef name("test_section");

    SourceLineInfo lineInfo("file.cpp", 42);

    std::vector<AssertionInfo> assertions;



    EXPECT_CALL(mock, sectionStarted(name, lineInfo, Ref(assertions))).WillOnce(Return(true));



    Section section(lineInfo, name, "");



    EXPECT_EQ(section.m_info.name, "test_section");

}



TEST_F(MockResultCaptureTest_1090, InfoLineInfoSetIfSectionIncluded_1090) {

    MockResultCapture mock;

    StringRef name("test_section");

    SourceLineInfo lineInfo("file.cpp", 42);

    std::vector<AssertionInfo> assertions;



    EXPECT_CALL(mock, sectionStarted(name, lineInfo, Ref(assertions))).WillOnce(Return(true));



    Section section(lineInfo, name, "");



    EXPECT_EQ(section.m_info.lineInfo.file, "file.cpp");

    EXPECT_EQ(section.m_info.lineInfo.line, 42);

}



TEST_F(MockResultCaptureTest_1090, TimerStartedIfSectionIncluded_1090) {

    MockResultCapture mock;

    StringRef name("test_section");

    SourceLineInfo lineInfo("file.cpp", 42);

    std::vector<AssertionInfo> assertions;



    EXPECT_CALL(mock, sectionStarted(name, lineInfo, Ref(assertions))).WillOnce(Return(true));



    Section section(lineInfo, name, "");



    EXPECT_TRUE(section.m_timer.isRunning());

}
