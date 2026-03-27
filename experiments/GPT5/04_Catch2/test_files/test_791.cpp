// File: tests/MultiReporter_benchmarkPreparing_791_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using ::testing::_;
using ::testing::Times;
using ::testing::NiceMock;

namespace {

class MockEventListener_791 : public Catch::IEventListener {
public:
    // IEventListener requires a config in ctor; for this test it is unused.
    MockEventListener_791() : Catch::IEventListener(nullptr) {}
    ~MockEventListener_791() override = default;

    // We only mock what we verify here.
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
};

// Helper to wrap raw pointer into Catch's unique_ptr type used by MultiReporter.
static Catch::Detail::unique_ptr<Catch::IEventListener>
MakePtr_791(MockEventListener_791* p) {
    return Catch::Detail::unique_ptr<Catch::IEventListener>(p);
}

// Matcher that compares StringRef contents with a std::string.
MATCHER_P(StringRefEq_791, expected, "StringRef content equals expected") {
    return static_cast<std::string>(arg) == expected;
}

} // namespace

class MultiReporterTest_791 : public ::testing::Test {};

// Normal operation: forwards to ALL reporter-likes (mix of listener + reporter)
TEST_F(MultiReporterTest_791, ForwardsToAllReporterLikes_791) {
    Catch::MultiReporter mr(nullptr);

    // Add one via addListener
    auto* l1 = new NiceMock<MockEventListener_791>();
    EXPECT_CALL(*l1, benchmarkPreparing(StringRefEq_791("bm_run"))).Times(1);
    mr.addListener(MakePtr_791(l1));

    // Add one via addReporter
    auto* r1 = new NiceMock<MockEventListener_791>();
    EXPECT_CALL(*r1, benchmarkPreparing(StringRefEq_791("bm_run"))).Times(1);
    mr.addReporter(MakePtr_791(r1));

    mr.benchmarkPreparing(Catch::StringRef("bm_run"));
}

// Boundary case: no children — calling benchmarkPreparing should be a no-op (no crash)
TEST_F(MultiReporterTest_791, NoChildrenIsSafe_791) {
    Catch::MultiReporter mr(nullptr);
    // Should not throw or crash; nothing to verify besides successful call.
    mr.benchmarkPreparing(Catch::StringRef("anything"));
    SUCCEED();
}

// Boundary case: empty name should be forwarded as empty StringRef
TEST_F(MultiReporterTest_791, ForwardsEmptyName_791) {
    Catch::MultiReporter mr(nullptr);

    auto* m = new NiceMock<MockEventListener_791>();
    EXPECT_CALL(*m, benchmarkPreparing(StringRefEq_791(std::string()))).Times(1);
    mr.addReporter(MakePtr_791(m));

    Catch::StringRef empty; // default-constructed => empty
    mr.benchmarkPreparing(empty);
}

// Normal-ish edge: long / non-ASCII content should be forwarded intact
TEST_F(MultiReporterTest_791, ForwardsLongUnicodeName_791) {
    Catch::MultiReporter mr(nullptr);

    const std::string longName =
        "very-long-benchmark-name-Δ-測試-🚀-0123456789-abcdefghijklmnopqrstuvwxyz";

    auto* m1 = new NiceMock<MockEventListener_791>();
    EXPECT_CALL(*m1, benchmarkPreparing(StringRefEq_791(longName))).Times(1);
    mr.addListener(MakePtr_791(m1));

    mr.benchmarkPreparing(Catch::StringRef(longName.c_str(), longName.size()));
}
