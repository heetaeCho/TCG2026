#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_reporter_json.hpp"



using namespace Catch;



class JsonReporterTest_863 : public ::testing::Test {

protected:

    struct ReporterConfigMock : ReporterConfig {

        explicit ReporterConfigMock() : ReporterConfig(nullptr) {}

        Detail::unique_ptr<IStream> takeStream() override { return m_wrapped_stream; }

        void setWrappedStream(Detail::unique_ptr<IStream>&& stream) { m_wrapped_stream = std::move(stream); }

    };



    ReporterConfigMock config;

    JsonReporter reporter{std::move(config)};

};



TEST_F(JsonReporterTest_863, DestructorEndsListingAndObject_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(2); // Expect two writes for endListing and endObject



    // Exercise: Destructor is called automatically when reporter goes out of scope

}



TEST_F(JsonReporterTest_863, TestRunStartingCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for testRunStarting



    // Exercise: Call testRunStarting

    TestRunInfo runInfo{"Test Run", "Build Info"};

    reporter.testRunStarting(runInfo);

}



TEST_F(JsonReporterTest_863, TestRunEndedCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for testRunEnded



    // Exercise: Call testRunEnding

    TestRunStats runStats{};

    reporter.testRunEnded(runStats);

}



TEST_F(JsonReporterTest_863, TestCaseStartingCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for testCaseStarting



    // Exercise: Call testCaseStarting

    TestCaseInfo tcInfo{"Test Case", "Filename", 0};

    reporter.testCaseStarting(tcInfo);

}



TEST_F(JsonReporterTest_863, TestCaseEndedCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for testCaseEnded



    // Exercise: Call testCaseEnding

    TestCaseStats tcStats{};

    reporter.testCaseEnded(tcStats);

}



TEST_F(JsonReporterTest_863, SectionStartingCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for sectionStarting



    // Exercise: Call sectionStarting

    SectionInfo sectionInfo{"Section", "Filename", 0};

    reporter.sectionStarting(sectionInfo);

}



TEST_F(JsonReporterTest_863, SectionEndedCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for sectionEnded



    // Exercise: Call sectionEnding

    SectionStats sectionStats{};

    reporter.sectionEnded(sectionStats);

}



TEST_F(JsonReporterTest_863, AssertionStartingCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for assertionStarting



    // Exercise: Call assertionStarting

    AssertionInfo assertionInfo{"Expression", "Filename", 0};

    reporter.assertionStarting(assertionInfo);

}



TEST_F(JsonReporterTest_863, AssertionEndedCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for assertionEnded



    // Exercise: Call assertionEnding

    AssertionStats assertionStats{};

    reporter.assertionEnded(assertionStats);

}



TEST_F(JsonReporterTest_863, BenchmarkPreparingCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for benchmarkPreparing



    // Exercise: Call benchmarkPreparing

    reporter.benchmarkPreparing("Benchmark Name");

}



TEST_F(JsonReporterTest_863, BenchmarkStartingCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for benchmarkStarting



    // Exercise: Call benchmarkStarting

    BenchmarkInfo benchmarkInfo{"Benchmark Name"};

    reporter.benchmarkStarting(benchmarkInfo);

}



TEST_F(JsonReporterTest_863, BenchmarkEndedCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for benchmarkEnded



    // Exercise: Call benchmarkEnding

    BenchmarkStats<> benchmarkStats{};

    reporter.benchmarkEnded(benchmarkStats);

}



TEST_F(JsonReporterTest_863, BenchmarkFailedCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for benchmarkFailed



    // Exercise: Call benchmarkFailed

    reporter.benchmarkFailed("Error Message");

}



TEST_F(JsonReporterTest_863, ListReportersCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for listReporters



    // Exercise: Call listReporters

    std::vector<ReporterDescription> descriptions;

    reporter.listReporters(descriptions);

}



TEST_F(JsonReporterTest_863, ListListenersCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for listListeners



    // Exercise: Call listListeners

    std::vector<ListenerDescription> descriptions;

    reporter.listListeners(descriptions);

}



TEST_F(JsonReporterTest_863, ListTestsCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for listTests



    // Exercise: Call listTests

    std::vector<TestCaseHandle> tests;

    reporter.listTests(tests);

}



TEST_F(JsonReporterTest_863, ListTagsCalledOnce_863) {

    // Setup: Mock the IStream to capture output

    auto mockStream = Detail::unique_ptr<IStream>(new ::testing::NiceMock<MockIStream>());

    config.setWrappedStream(std::move(mockStream));



    EXPECT_CALL(*mockStream, write(::testing::_)).Times(1); // Expect one write for listTags



    // Exercise: Call listTags

    std::vector<TagInfo> tags;

    reporter.listTags(tags);

}
