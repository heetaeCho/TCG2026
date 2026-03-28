#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_section.hpp"

#include "catch2/interfaces/catch_interfaces_capture.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class MockResultCapture : public IResultCapture {

public:

    MOCK_METHOD3(sectionStarted, bool(StringRef, const SourceLineInfo&, Counts&));

};



TEST_F(SectionTest_1089, SectionConstructorCallsSectionStarted_1089) {

    MockResultCapture mockResultCapture;

    auto originalGetResultCapture = getResultCapture;

    ON_CALL(mockResultCapture, sectionStarted(_, _, _)).WillByDefault(Return(true));



    EXPECT_CALL(mockResultCapture, sectionStarted("TestSection", SourceLineInfo(), testing::_))

        .Times(1);



    getResultCapture = [&]() -> IResultCapture& {

        return mockResultCapture;

    };



    Section section(SourceLineInfo(), "TestSection");



    getResultCapture = originalGetResultCapture;

}



TEST_F(SectionTest_1089, SectionConstructorDoesNotStartTimerIfSectionNotIncluded_1089) {

    MockResultCapture mockResultCapture;

    auto originalGetResultCapture = getResultCapture;

    ON_CALL(mockResultCapture, sectionStarted(_, _, _)).WillByDefault(Return(false));



    EXPECT_CALL(mockResultCapture, sectionStarted("TestSection", SourceLineInfo(), testing::_))

        .Times(1);



    getResultCapture = [&]() -> IResultCapture& {

        return mockResultCapture;

    };



    Section section(SourceLineInfo(), "TestSection");



    // Assuming Timer::start is not called when m_sectionIncluded is false

    EXPECT_FALSE(section);



    getResultCapture = originalGetResultCapture;

}



TEST_F(SectionTest_1089, OperatorBoolReturnsTrueIfSectionStarted_1089) {

    MockResultCapture mockResultCapture;

    auto originalGetResultCapture = getResultCapture;

    ON_CALL(mockResultCapture, sectionStarted(_, _, _)).WillByDefault(Return(true));



    EXPECT_CALL(mockResultCapture, sectionStarted("TestSection", SourceLineInfo(), testing::_))

        .Times(1);



    getResultCapture = [&]() -> IResultCapture& {

        return mockResultCapture;

    };



    Section section(SourceLineInfo(), "TestSection");



    EXPECT_TRUE(section);



    getResultCapture = originalGetResultCapture;

}



TEST_F(SectionTest_1089, OperatorBoolReturnsFalseIfSectionNotStarted_1089) {

    MockResultCapture mockResultCapture;

    auto originalGetResultCapture = getResultCapture;

    ON_CALL(mockResultCapture, sectionStarted(_, _, _)).WillByDefault(Return(false));



    EXPECT_CALL(mockResultCapture, sectionStarted("TestSection", SourceLineInfo(), testing::_))

        .Times(1);



    getResultCapture = [&]() -> IResultCapture& {

        return mockResultCapture;

    };



    Section section(SourceLineInfo(), "TestSection");



    EXPECT_FALSE(section);



    getResultCapture = originalGetResultCapture;

}
