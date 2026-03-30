#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"

#include "catch2/interfaces/catch_interfaces_reporter.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::NiceMock;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, listTags, (std::vector<TagInfo> const& tags), (override));

};



class MultiReporterTest_809 : public ::testing::Test {

protected:

    MultiReporter multiReporter;

    NiceMock<MockIEventListener> mockListener1;

    NiceMock<MockIEventListener> mockListener2;



    void SetUp() override {

        multiReporter.addListener(IEventListenerPtr(new MockIEventListener(mockListener1)));

        multiReporter.addListener(IEventListenerPtr(new MockIEventListener(mockListener2)));

    }

};



TEST_F(MultiReporterTest_809, ListTags_DelegatesToAllListeners_809) {

    std::vector<TagInfo> tags = {TagInfo("tag1"), TagInfo("tag2")};

    

    EXPECT_CALL(mockListener1, listTags(tags)).Times(1);

    EXPECT_CALL(mockListener2, listTags(tags)).Times(1);



    multiReporter.listTags(tags);

}



TEST_F(MultiReporterTest_809, ListTags_HandlesEmptyTagsList_809) {

    std::vector<TagInfo> emptyTags;



    EXPECT_CALL(mockListener1, listTags(emptyTags)).Times(1);

    EXPECT_CALL(mockListener2, listTags(emptyTags)).Times(1);



    multiReporter.listTags(emptyTags);

}



TEST_F(MultiReporterTest_809, ListTags_NoListenersAdded_809) {

    std::vector<TagInfo> tags = {TagInfo("tag1")};

    MultiReporter emptyMultiReporter;



    EXPECT_CALL(mockListener1, listTags(tags)).Times(0);

    EXPECT_CALL(mockListener2, listTags(tags)).Times(0);



    emptyMultiReporter.listTags(tags);

}



TEST_F(MultiReporterTest_809, ListTags_SingleListener_809) {

    MultiReporter singleListenerReporter;

    NiceMock<MockIEventListener> mockSingleListener;

    

    std::vector<TagInfo> tags = {TagInfo("tag1")};

    singleListenerReporter.addListener(IEventListenerPtr(new MockIEventListener(mockSingleListener)));



    EXPECT_CALL(mockSingleListener, listTags(tags)).Times(1);

    EXPECT_CALL(mockListener1, listTags(tags)).Times(0);

    EXPECT_CALL(mockListener2, listTags(tags)).Times(0);



    singleListenerReporter.listTags(tags);

}
