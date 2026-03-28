#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/internal/catch_stringref.hpp"

// Mock for IEventListener
class MockEventListener : public Catch::IEventListener {
public:
    MockEventListener() : Catch::IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (Catch::StringRef), (override));
    MOCK_METHOD(void, reportInvalidTestSpec, (Catch::StringRef), (override));
    MOCK_METHOD(void, fatalErrorEncountered, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const Catch::BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const Catch::BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
    MOCK_METHOD(void, testRunStarting, (const Catch::TestRunInfo&), (override));
    MOCK_METHOD(void, testCaseStarting, (const Catch::TestCaseInfo&), (override));
    MOCK_METHOD(void, testCasePartialStarting, (const Catch::TestCaseInfo&, uint64_t), (override));
    MOCK_METHOD(void, sectionStarting, (const Catch::SectionInfo&), (override));
    MOCK_METHOD(void, assertionStarting, (const Catch::AssertionInfo&), (override));
    MOCK_METHOD(void, assertionEnded, (const Catch::AssertionStats&), (override));
    MOCK_METHOD(void, sectionEnded, (const Catch::SectionStats&), (override));
    MOCK_METHOD(void, testCasePartialEnded, (const Catch::TestCaseStats&, uint64_t), (override));
    MOCK_METHOD(void, testCaseEnded, (const Catch::TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const Catch::TestRunStats&), (override));
    MOCK_METHOD(void, skipTest, (const Catch::TestCaseInfo&), (override));
    MOCK_METHOD(void, listReporters, (const std::vector<Catch::ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners, (const std::vector<Catch::ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests, (const std::vector<Catch::TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags, (const std::vector<Catch::TagInfo>&), (override));
};

class MultiReporterTest_790 : public ::testing::Test {
protected:
    Catch::MultiReporter multiReporter{nullptr};
};

// ========== reportInvalidTestSpec Tests ==========

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecNoListeners_790) {
    // No listeners/reporters added. Should not crash.
    EXPECT_NO_THROW(multiReporter.reportInvalidTestSpec("bad spec"));
}

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecSingleReporter_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.reportInvalidTestSpec("invalid_spec");
}

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecMultipleReporters_790) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, reportInvalidTestSpec(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, reportInvalidTestSpec(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock1));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock2));
    multiReporter.reportInvalidTestSpec("bad");
}

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecSingleListener_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(::testing::_)).Times(1);

    multiReporter.addListener(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.reportInvalidTestSpec("spec");
}

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecListenersAndReporters_790) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    EXPECT_CALL(*listener, reportInvalidTestSpec(::testing::_)).Times(1);
    EXPECT_CALL(*reporter, reportInvalidTestSpec(::testing::_)).Times(1);

    multiReporter.addListener(Catch::Detail::unique_ptr<Catch::IEventListener>(listener));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(reporter));
    multiReporter.reportInvalidTestSpec("arg");
}

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecEmptyString_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.reportInvalidTestSpec("");
}

// ========== noMatchingTestCases Tests ==========

TEST_F(MultiReporterTest_790, NoMatchingTestCasesNoListeners_790) {
    EXPECT_NO_THROW(multiReporter.noMatchingTestCases("spec"));
}

TEST_F(MultiReporterTest_790, NoMatchingTestCasesSingleReporter_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, noMatchingTestCases(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.noMatchingTestCases("unmatched");
}

TEST_F(MultiReporterTest_790, NoMatchingTestCasesMultipleReporters_790) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();
    auto* mock3 = new MockEventListener();

    EXPECT_CALL(*mock1, noMatchingTestCases(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, noMatchingTestCases(::testing::_)).Times(1);
    EXPECT_CALL(*mock3, noMatchingTestCases(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock1));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock2));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock3));
    multiReporter.noMatchingTestCases("spec");
}

// ========== fatalErrorEncountered Tests ==========

TEST_F(MultiReporterTest_790, FatalErrorEncounteredNoListeners_790) {
    EXPECT_NO_THROW(multiReporter.fatalErrorEncountered("fatal"));
}

TEST_F(MultiReporterTest_790, FatalErrorEncounteredSingleReporter_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, fatalErrorEncountered(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.fatalErrorEncountered("error");
}

TEST_F(MultiReporterTest_790, FatalErrorEncounteredMultipleReporters_790) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, fatalErrorEncountered(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, fatalErrorEncountered(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock1));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock2));
    multiReporter.fatalErrorEncountered("fatal error");
}

// ========== benchmarkPreparing Tests ==========

TEST_F(MultiReporterTest_790, BenchmarkPreparingNoListeners_790) {
    EXPECT_NO_THROW(multiReporter.benchmarkPreparing("bench"));
}

TEST_F(MultiReporterTest_790, BenchmarkPreparingSingleReporter_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, benchmarkPreparing(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.benchmarkPreparing("benchmark1");
}

TEST_F(MultiReporterTest_790, BenchmarkPreparingMultipleReporters_790) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkPreparing(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkPreparing(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock1));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock2));
    multiReporter.benchmarkPreparing("bench");
}

// ========== benchmarkFailed Tests ==========

TEST_F(MultiReporterTest_790, BenchmarkFailedNoListeners_790) {
    EXPECT_NO_THROW(multiReporter.benchmarkFailed("error"));
}

TEST_F(MultiReporterTest_790, BenchmarkFailedMultipleReporters_790) {
    auto* mock1 = new MockEventListener();
    auto* mock2 = new MockEventListener();

    EXPECT_CALL(*mock1, benchmarkFailed(::testing::_)).Times(1);
    EXPECT_CALL(*mock2, benchmarkFailed(::testing::_)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock1));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock2));
    multiReporter.benchmarkFailed("bench failed");
}

// ========== addListener and addReporter ordering Tests ==========

TEST_F(MultiReporterTest_790, ListenersCalledBeforeReporters_790) {
    auto* listener = new MockEventListener();
    auto* reporter = new MockEventListener();

    {
        ::testing::InSequence seq;
        EXPECT_CALL(*listener, reportInvalidTestSpec(::testing::_)).Times(1);
        EXPECT_CALL(*reporter, reportInvalidTestSpec(::testing::_)).Times(1);
    }

    multiReporter.addListener(Catch::Detail::unique_ptr<Catch::IEventListener>(listener));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(reporter));
    multiReporter.reportInvalidTestSpec("test");
}

TEST_F(MultiReporterTest_790, MultipleListenersBeforeReporter_790) {
    auto* listener1 = new MockEventListener();
    auto* listener2 = new MockEventListener();
    auto* reporter = new MockEventListener();

    {
        ::testing::InSequence seq;
        EXPECT_CALL(*listener1, noMatchingTestCases(::testing::_)).Times(1);
        EXPECT_CALL(*listener2, noMatchingTestCases(::testing::_)).Times(1);
        EXPECT_CALL(*reporter, noMatchingTestCases(::testing::_)).Times(1);
    }

    multiReporter.addListener(Catch::Detail::unique_ptr<Catch::IEventListener>(listener1));
    multiReporter.addListener(Catch::Detail::unique_ptr<Catch::IEventListener>(listener2));
    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(reporter));
    multiReporter.noMatchingTestCases("spec");
}

// ========== Multiple calls Tests ==========

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecCalledMultipleTimes_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, reportInvalidTestSpec(::testing::_)).Times(3);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.reportInvalidTestSpec("arg1");
    multiReporter.reportInvalidTestSpec("arg2");
    multiReporter.reportInvalidTestSpec("arg3");
}

TEST_F(MultiReporterTest_790, NoMatchingTestCasesCalledMultipleTimes_790) {
    auto* mock = new MockEventListener();
    EXPECT_CALL(*mock, noMatchingTestCases(::testing::_)).Times(2);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.noMatchingTestCases("spec1");
    multiReporter.noMatchingTestCases("spec2");
}

// ========== Add listener after reporter ==========

TEST_F(MultiReporterTest_790, AddListenerAfterReporter_790) {
    auto* reporter = new MockEventListener();
    auto* listener = new MockEventListener();

    // Listeners should still be called before reporters even if added after
    {
        ::testing::InSequence seq;
        EXPECT_CALL(*listener, fatalErrorEncountered(::testing::_)).Times(1);
        EXPECT_CALL(*reporter, fatalErrorEncountered(::testing::_)).Times(1);
    }

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(reporter));
    multiReporter.addListener(Catch::Detail::unique_ptr<Catch::IEventListener>(listener));
    multiReporter.fatalErrorEncountered("error");
}

// ========== Verify argument forwarding ==========

TEST_F(MultiReporterTest_790, ReportInvalidTestSpecForwardsArgument_790) {
    auto* mock = new MockEventListener();

    Catch::StringRef expected("specific_invalid_arg");
    EXPECT_CALL(*mock, reportInvalidTestSpec(expected)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.reportInvalidTestSpec("specific_invalid_arg");
}

TEST_F(MultiReporterTest_790, NoMatchingTestCasesForwardsArgument_790) {
    auto* mock = new MockEventListener();

    Catch::StringRef expected("my_unmatched_spec");
    EXPECT_CALL(*mock, noMatchingTestCases(expected)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.noMatchingTestCases("my_unmatched_spec");
}

TEST_F(MultiReporterTest_790, FatalErrorForwardsArgument_790) {
    auto* mock = new MockEventListener();

    Catch::StringRef expected("critical_error");
    EXPECT_CALL(*mock, fatalErrorEncountered(expected)).Times(1);

    multiReporter.addReporter(Catch::Detail::unique_ptr<Catch::IEventListener>(mock));
    multiReporter.fatalErrorEncountered("critical_error");
}
