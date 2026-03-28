#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"

#include "./TestProjects/Catch2/src/catch2/catch_config.hpp"



using namespace Catch;



class MockIEventListener : public IEventListener {

public:

    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));

    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));

    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));

    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));



    MockIEventListener(IConfig const* config) : IEventListener(config) {}

};



class ConfigMock : public Config {

public:

    MOCK_CONST_METHOD0(listTests, bool());

    MOCK_CONST_METHOD0(listTags, bool());

    MOCK_CONST_METHOD0(listReporters, bool());

    MOCK_CONST_METHOD0(listListeners, bool());

};



class ListFunctionTest_604 : public ::testing::Test {

protected:

    std::unique_ptr<MockIEventListener> reporter;

    ConfigMock config;



    void SetUp() override {

        reporter = std::make_unique<MockIEventListener>(&config);

    }

};



TEST_F(ListFunctionTest_604, ListTestsCalledWhenConfigListsTests_604) {

    EXPECT_CALL(config, listTests()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*reporter, listTests(::testing::_)).Times(1);



    bool listed = list(*reporter, config);

    EXPECT_TRUE(listed);

}



TEST_F(ListFunctionTest_604, ListTagsCalledWhenConfigListsTags_604) {

    EXPECT_CALL(config, listTags()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*reporter, listTags(::testing::_)).Times(1);



    bool listed = list(*reporter, config);

    EXPECT_TRUE(listed);

}



TEST_F(ListFunctionTest_604, ListReportersCalledWhenConfigListsReporters_604) {

    EXPECT_CALL(config, listReporters()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*reporter, listReporters(::testing::_)).Times(1);



    bool listed = list(*reporter, config);

    EXPECT_TRUE(listed);

}



TEST_F(ListFunctionTest_604, ListListenersCalledWhenConfigListsListeners_604) {

    EXPECT_CALL(config, listListeners()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*reporter, listListeners(::testing::_)).Times(1);



    bool listed = list(*reporter, config);

    EXPECT_TRUE(listed);

}



TEST_F(ListFunctionTest_604, NoFunctionsCalledWhenConfigListsNothing_604) {

    EXPECT_CALL(config, listTests()).WillOnce(::testing::Return(false));

    EXPECT_CALL(config, listTags()).WillOnce(::testing::Return(false));

    EXPECT_CALL(config, listReporters()).WillOnce(::testing::Return(false));

    EXPECT_CALL(config, listListeners()).WillOnce(::testing::Return(false));



    bool listed = list(*reporter, config);

    EXPECT_FALSE(listed);

}



TEST_F(ListFunctionTest_604, MultipleFunctionsCalledWhenConfigListsMultipleItems_604) {

    EXPECT_CALL(config, listTests()).WillOnce(::testing::Return(true));

    EXPECT_CALL(config, listTags()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*reporter, listTests(::testing::_)).Times(1);

    EXPECT_CALL(*reporter, listTags(::testing::_)).Times(1);



    bool listed = list(*reporter, config);

    EXPECT_TRUE(listed);

}



TEST_F(ListFunctionTest_604, AllFunctionsCalledWhenConfigListsAllItems_604) {

    EXPECT_CALL(config, listTests()).WillOnce(::testing::Return(true));

    EXPECT_CALL(config, listTags()).WillOnce(::testing::Return(true));

    EXPECT_CALL(config, listReporters()).WillOnce(::testing::Return(true));

    EXPECT_CALL(config, listListeners()).WillOnce(::testing::Return(true));

    EXPECT_CALL(*reporter, listTests(::testing::_)).Times(1);

    EXPECT_CALL(*reporter, listTags(::testing::_)).Times(1);

    EXPECT_CALL(*reporter, listReporters(::testing::_)).Times(1);

    EXPECT_CALL(*reporter, listListeners(::testing::_)).Times(1);



    bool listed = list(*reporter, config);

    EXPECT_TRUE(listed);

}
