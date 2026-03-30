#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockReporter : public IEventListener {

public:

    MOCK_METHOD(void, sectionStarting, (const SectionInfo &sectionInfo), (override));

};



class RunContextTest_496 : public ::testing::Test {

protected:

    NiceMock<MockReporter> mockReporter;

    Totals totals;

    SourceLineInfo lineInfo{"filename.cpp", 123};

    Counts assertions;

    StringRef sectionName = "test_section";



    RunContext runContext{nullptr, IEventListenerPtr{&mockReporter}};

};



TEST_F(RunContextTest_496, SectionStarted_ReturnsTrueWhenSectionIsOpen_496) {

    EXPECT_CALL(mockReporter, sectionStarting(_)).Times(1);



    bool result = runContext.sectionStarted(sectionName, lineInfo, assertions);

    ASSERT_TRUE(result);

}



TEST_F(RunContextTest_496, SectionStarted_CallsReporterWithCorrectSectionInfo_496) {

    EXPECT_CALL(mockReporter, sectionStarting(SectionInfo({lineInfo, "test_section"}))).Times(1);



    runContext.sectionStarted(sectionName, lineInfo, assertions);

}



TEST_F(RunContextTest_496, SectionStarted_ReturnsFalseWhenSectionIsNotOpen_496) {

    // Assuming the first call opens the section and subsequent calls might not

    runContext.sectionStarted(sectionName, lineInfo, assertions);



    bool result = runContext.sectionStarted(sectionName, lineInfo, assertions);

    ASSERT_FALSE(result);

}



TEST_F(RunContextTest_496, SectionStarted_AssertionsUpdatedWithTotalsAssertions_496) {

    EXPECT_CALL(mockReporter, sectionStarting(_)).Times(1);



    runContext.sectionStarted(sectionName, lineInfo, assertions);

    ASSERT_EQ(assertions.total(), totals.assertions.total());

}



TEST_F(RunContextTest_496, SectionStarted_HandlesEmptySectionName_496) {

    StringRef emptySectionName = "";



    EXPECT_CALL(mockReporter, sectionStarting(SectionInfo({lineInfo, ""}))).Times(1);



    bool result = runContext.sectionStarted(emptySectionName, lineInfo, assertions);

    ASSERT_TRUE(result);

}



TEST_F(RunContextTest_496, SectionStarted_HandlesLargeSectionName_496) {

    std::string largeString(256, 'a');

    StringRef largeSectionName(largeString.c_str());



    EXPECT_CALL(mockReporter, sectionStarting(SectionInfo({lineInfo, largeString}))).Times(1);



    bool result = runContext.sectionStarted(largeSectionName, lineInfo, assertions);

    ASSERT_TRUE(result);

}
