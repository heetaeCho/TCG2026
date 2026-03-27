#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/catch_section_info.hpp"



using namespace Catch;

using testing::NiceMock;

using testing::_;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, sectionStarting, (const SectionInfo &sectionInfo), (override));

};



class MultiReporterTest_798 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(&mockListener1, [](IEventListener*){}));

        multiReporter.addListener(IEventListenerPtr(&mockListener2, [](IEventListener*){}));

    }

};



TEST_F(MultiReporterTest_798, SectionStarting_CallsAllListeners_798) {

    SectionInfo sectionInfo(SourceLineInfo("", 0), "testSection");

    

    EXPECT_CALL(mockListener1, sectionStarting(sectionInfo));

    EXPECT_CALL(mockListener2, sectionStarting(sectionInfo));



    multiReporter.sectionStarting(sectionInfo);

}



TEST_F(MultiReporterTest_798, NoListeners_NoCalls_798) {

    MultiReporter emptyMultiReporter;

    SectionInfo sectionInfo(SourceLineInfo("", 0), "testSection");



    EXPECT_CALL(mockListener1, sectionStarting(_)).Times(0);

    EXPECT_CALL(mockListener2, sectionStarting(_)).Times(0);



    emptyMultiReporter.sectionStarting(sectionInfo);

}



TEST_F(MultiReporterTest_798, SectionStarting_BoundaryConditions_798) {

    SectionInfo emptySectionInfo(SourceLineInfo("", 0), "");

    

    EXPECT_CALL(mockListener1, sectionStarting(emptySectionInfo));

    EXPECT_CALL(mockListener2, sectionStarting(emptySectionInfo));



    multiReporter.sectionStarting(emptySectionInfo);

}
