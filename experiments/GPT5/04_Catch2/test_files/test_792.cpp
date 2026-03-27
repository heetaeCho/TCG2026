// File: tests/Reporter/MultiReporter_benchmarkStarting_792.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_multi.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/benchmark/detail/catch_benchmark_stats.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

using ::testing::_;
using ::testing::Ref;
using ::testing::StrictMock;

namespace {

class MockEventListener : public Catch::IEventListener {
public:
    // MultiReporter and IEventListener accept a config ptr; we treat it as a black box.
    MockEventListener() : Catch::IEventListener(nullptr) {}

    MOCK_METHOD(void, benchmarkStarting,
                (Catch::BenchmarkInfo const&), (override));
};

class MultiReporterBenchmarkStartingTest_792 : public ::testing::Test {
protected:
    // MultiReporter is treated as a black box. We assume it is constructible with a config pointer.
    // If your codebase requires a different constructor, adjust here accordingly.
    Catch::MultiReporter mr_{ nullptr };

    static Catch::BenchmarkInfo sampleInfo(double est = 1.23,
                                           int iterations = 10,
                                           unsigned samples = 3,
                                           unsigned resamples = 7,
                                           double clockRes = 0.000001,
                                           double clockCost = 0.00001) {
        Catch::BenchmarkInfo bi{};
        bi.estimatedDuration = est;
        bi.iterations = iterations;
        bi.samples = samples;
        bi.resamples = resamples;
        bi.clockResolution = clockRes;
        bi.clockCost = clockCost;
        return bi;
    }

    // Helper to hand ownership of a mock to MultiReporter via Catch's unique_ptr
    static Catch::Detail::unique_ptr<Catch::IEventListener>
    makePtr(MockEventListener* raw) {
        return Catch::Detail::unique_ptr<Catch::IEventListener>(raw);
    }
};

// [Boundary] No listeners/reporters added: calling benchmarkStarting should not crash or call anything.
TEST_F(MultiReporterBenchmarkStartingTest_792, NoReporterLikes_NoCrash_792) {
    auto bi = sampleInfo();
    // Just exercise the method. With no listeners/reporters, there are no observable calls.
    mr_.benchmarkStarting(bi);
    SUCCEED();
}

// [Normal] A single listener added via addListener receives the call with the exact same reference.
TEST_F(MultiReporterBenchmarkStartingTest_792, SingleListener_ForwardsExactReference_792) {
    auto* listener = new StrictMock<MockEventListener>();
    mr_.addListener( makePtr(listener) );

    auto bi = sampleInfo();

    // Verify the exact same object reference is forwarded.
    EXPECT_CALL(*listener, benchmarkStarting(Ref(bi))).Times(1);

    mr_.benchmarkStarting(bi);
}

// [Normal] One reporter and one listener: both receive exactly one call.
// This does not assert any ordering, only that both collaborators are invoked.
TEST_F(MultiReporterBenchmarkStartingTest_792, ReporterAndListener_BothReceiveCall_792) {
    auto* reporter = new StrictMock<MockEventListener>();
    auto* listener = new StrictMock<MockEventListener>();

    mr_.addReporter( makePtr(reporter) );
    mr_.addListener( makePtr(listener) );

    auto bi = sampleInfo(2.5, 42, 5, 9, 1e-6, 1e-5);

    EXPECT_CALL(*reporter, benchmarkStarting(Ref(bi))).Times(1);
    EXPECT_CALL(*listener, benchmarkStarting(Ref(bi))).Times(1);

    mr_.benchmarkStarting(bi);
}

// [Normal + Light Boundary] Multiple collaborators (3 total) all receive exactly one call.
TEST_F(MultiReporterBenchmarkStartingTest_792, MultipleListeners_AllReceiveOnce_792) {
    auto* a = new StrictMock<MockEventListener>();
    auto* b = new StrictMock<MockEventListener>();
    auto* c = new StrictMock<MockEventListener>();

    mr_.addListener( makePtr(a) );
    mr_.addReporter( makePtr(b) );
    mr_.addListener( makePtr(c) );

    auto bi = sampleInfo(0.0, 0, 0, 0, 0.0, 0.0); // edge-ish values, still valid inputs

    EXPECT_CALL(*a, benchmarkStarting(Ref(bi))).Times(1);
    EXPECT_CALL(*b, benchmarkStarting(Ref(bi))).Times(1);
    EXPECT_CALL(*c, benchmarkStarting(Ref(bi))).Times(1);

    mr_.benchmarkStarting(bi);
}

} // namespace
