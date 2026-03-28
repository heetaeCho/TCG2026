#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"

#include "catch2/internal/catch_stringref.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, fatalErrorEncountered, (StringRef error), (override));

};



class MultiReporterTest_789 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockEventListener> mockListener1;

    NiceMock<MockEventListener> mockListener2;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(new MockEventListener(mockListener1)));

        multiReporter.addListener(IEventListenerPtr(new MockEventListener(mockListener2)));

    }

};



TEST_F(MultiReporterTest_789, FatalErrorEncountered_NotifyAllListeners_789) {

    StringRef error("Test error");

    EXPECT_CALL(mockListener1, fatalErrorEncountered(error));

    EXPECT_CALL(mockListener2, fatalErrorEncountered(error));



    multiReporter.fatalErrorEncountered(error);

}



TEST_F(MultiReporterTest_789, FatalErrorEncountered_EmptyString_789) {

    StringRef error("");

    EXPECT_CALL(mockListener1, fatalErrorEncountered(error));

    EXPECT_CALL(mockListener2, fatalErrorEncountered(error));



    multiReporter.fatalErrorEncountered(error);

}



TEST_F(MultiReporterTest_789, FatalErrorEncountered_LongString_789) {

    std::string longErrorMessage(1024, 'a');

    StringRef error(longErrorMessage);

    EXPECT_CALL(mockListener1, fatalErrorEncountered(error));

    EXPECT_CALL(mockListener2, fatalErrorEncountered(error));



    multiReporter.fatalErrorEncountered(error);

}



TEST_F(MultiReporterTest_789, NoListeners_NoCrash_789) {

    MultiReporter emptyMultiReporter;

    StringRef error("Test error");



    EXPECT_NO_THROW(emptyMultiReporter.fatalErrorEncountered(error));

}
