#include <catch2/catch_config.hpp>
#include <catch2/internal/catch_list.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_session.hpp>
#include <catch2/internal/catch_context.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace Catch;

class MockEventListener : public IEventListener {
public:
    MockEventListener(IConfig const* config = nullptr) : IEventListener(config) {}

    MOCK_METHOD(void, noMatchingTestCases, (StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, assertionStarting, (const AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const TestCaseInfo&), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<TagInfo>&), (override));
};

class ListTest_604 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ListTest_604, NothingListed_ReturnsFalse_604) {
    ConfigData data;
    data.listTests = false;
    data.listTags = false;
    data.listReporters = false;
    data.listListeners = false;
    Config config(data);
    MockEventListener reporter(&config);

    bool result = list(reporter, config);
    EXPECT_FALSE(result);
}

TEST_F(ListTest_604, ListTestsOnly_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = true;
    data.listTags = false;
    data.listReporters = false;
    data.listListeners = false;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listTests(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, ListTagsOnly_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = false;
    data.listTags = true;
    data.listReporters = false;
    data.listListeners = false;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listTags(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, ListReportersOnly_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = false;
    data.listTags = false;
    data.listReporters = true;
    data.listListeners = false;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listReporters(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, ListListenersOnly_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = false;
    data.listTags = false;
    data.listReporters = false;
    data.listListeners = true;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listListeners(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, AllListOptionsEnabled_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = true;
    data.listTags = true;
    data.listReporters = true;
    data.listListeners = true;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listTests(::testing::_)).Times(1);
    EXPECT_CALL(reporter, listTags(::testing::_)).Times(1);
    EXPECT_CALL(reporter, listReporters(::testing::_)).Times(1);
    EXPECT_CALL(reporter, listListeners(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, ListTestsAndTags_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = true;
    data.listTags = true;
    data.listReporters = false;
    data.listListeners = false;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listTests(::testing::_)).Times(1);
    EXPECT_CALL(reporter, listTags(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, ListReportersAndListeners_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = false;
    data.listTags = false;
    data.listReporters = true;
    data.listListeners = true;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listReporters(::testing::_)).Times(1);
    EXPECT_CALL(reporter, listListeners(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, ListTestsAndReporters_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = true;
    data.listTags = false;
    data.listReporters = true;
    data.listListeners = false;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listTests(::testing::_)).Times(1);
    EXPECT_CALL(reporter, listReporters(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}

TEST_F(ListTest_604, NoListFlags_ReporterNotCalled_604) {
    ConfigData data;
    data.listTests = false;
    data.listTags = false;
    data.listReporters = false;
    data.listListeners = false;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listTests(::testing::_)).Times(0);
    EXPECT_CALL(reporter, listTags(::testing::_)).Times(0);
    EXPECT_CALL(reporter, listReporters(::testing::_)).Times(0);
    EXPECT_CALL(reporter, listListeners(::testing::_)).Times(0);

    bool result = list(reporter, config);
    EXPECT_FALSE(result);
}

TEST_F(ListTest_604, ListTagsAndListeners_ReturnsTrue_604) {
    ConfigData data;
    data.listTests = false;
    data.listTags = true;
    data.listReporters = false;
    data.listListeners = true;
    Config config(data);
    MockEventListener reporter(&config);

    EXPECT_CALL(reporter, listTags(::testing::_)).Times(1);
    EXPECT_CALL(reporter, listListeners(::testing::_)).Times(1);

    bool result = list(reporter, config);
    EXPECT_TRUE(result);
}
