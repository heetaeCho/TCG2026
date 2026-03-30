#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::MockFunction;

using ::testing::ElementsAre;



class MockEventListener : public IEventListener {

public:

    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>& descriptions), (override));

};



class MultiReporterTest_807 : public ::testing::Test {

protected:

    MultiReporter multi_reporter_;

    NiceMock<MockEventListener> mock_listener1_;

    NiceMock<MockEventListener> mock_listener2_;



    void SetUp() override {

        multi_reporter_.addListener(std::make_unique<MockEventListener>(mock_listener1_));

        multi_reporter_.addListener(std::make_unique<MockEventListener>(mock_listener2_));

    }

};



TEST_F(MultiReporterTest_807, ListListenersCallsAllListeners_807) {

    std::vector<ListenerDescription> descriptions = {{"listener1"}, {"listener2"}};

    

    EXPECT_CALL(mock_listener1_, listListeners(descriptions));

    EXPECT_CALL(mock_listener2_, listListeners(descriptions));



    multi_reporter_.listListeners(descriptions);

}



TEST_F(MultiReporterTest_807, ListListenersWithEmptyDescriptions_807) {

    std::vector<ListenerDescription> descriptions = {};

    

    EXPECT_CALL(mock_listener1_, listListeners(descriptions));

    EXPECT_CALL(mock_listener2_, listListeners(descriptions));



    multi_reporter_.listListeners(descriptions);

}



TEST_F(MultiReporterTest_807, ListListenersWithSingleDescription_807) {

    std::vector<ListenerDescription> descriptions = {{"singleListener"}};

    

    EXPECT_CALL(mock_listener1_, listListeners(descriptions));

    EXPECT_CALL(mock_listener2_, listListeners(descriptions));



    multi_reporter_.listListeners(descriptions);

}



TEST_F(MultiReporterTest_807, NoListenersDoesNotCrash_807) {

    MultiReporter empty_multi_reporter;



    std::vector<ListenerDescription> descriptions = {{"listener1"}, {"listener2"}};



    EXPECT_NO_THROW(empty_multi_reporter.listListeners(descriptions));

}
