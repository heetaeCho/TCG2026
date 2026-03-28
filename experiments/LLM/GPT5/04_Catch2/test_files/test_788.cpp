// File: tests/MultiReporter_NoMatchingTestCases_788.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using ::testing::InSequence;
using ::testing::StrictMock;
using ::testing::Truly;

namespace {

class MockListener : public Catch::IEventListener {
public:
    // Base requires a config; nullptr is acceptable for these interaction tests.
    MockListener() : Catch::IEventListener(nullptr) {}

    MOCK_METHOD(void, noMatchingTestCases, (Catch::StringRef), (override));
};

// Helper matcher: compare StringRef content to expected std::string
inline auto StringRefEq(const std::string& expected) {
    return Truly([&](const Catch::StringRef& sr) {
        return std::string(sr) == expected;
    });
}

} // namespace

// TEST_ID: 788
TEST(MultiReporterTest_788, ForwardsToAllReporters_788) {
    Catch::MultiReporter mr(nullptr);

    auto* m1 = new StrictMock<MockListener>();
    auto* m2 = new StrictMock<MockListener>();

    // Use the same pointer type the codebase uses for listeners/reporters
    Catch::IEventListenerPtr p1(m1);
    Catch::IEventListenerPtr p2(m2);

    // Expect both to receive the exact same StringRef payload, in insertion order
    {
        InSequence seq;
        EXPECT_CALL(*m1, noMatchingTestCases(StringRefEq("case*pattern")));
        EXPECT_CALL(*m2, noMatchingTestCases(StringRefEq("case*pattern")));
    }

    // Register two "reporter-like" sinks. Either addReporter or addListener should work
    // as long as they become part of MultiReporter’s forwarding set.
    mr.addReporter(std::move(p1));
    mr.addReporter(std::move(p2));

    mr.noMatchingTestCases(Catch::StringRef("case*pattern"));
}

// TEST_ID: 788
TEST(MultiReporterTest_788, HandlesEmptySpec_788) {
    Catch::MultiReporter mr(nullptr);

    auto* m = new StrictMock<MockListener>();
    Catch::IEventListenerPtr p(m);

    EXPECT_CALL(*m, noMatchingTestCases(Truly([](const Catch::StringRef& sr){
        return sr.size() == 0; // empty input forwarded intact
    })));

    mr.addReporter(std::move(p));
    mr.noMatchingTestCases(Catch::StringRef(""));
}

// TEST_ID: 788
TEST(MultiReporterTest_788, NoReportersDoesNothing_788) {
    Catch::MultiReporter mr(nullptr);
    // No reporters/listeners added -> should not crash or call anything.
    // This is mainly a "does not throw/abort" check.
    mr.noMatchingTestCases(Catch::StringRef("anything"));
    SUCCEED();
}

// TEST_ID: 788
TEST(MultiReporterTest_788, MultipleCallsAreAllForwarded_788) {
    Catch::MultiReporter mr(nullptr);

    auto* m = new StrictMock<MockListener>();
    Catch::IEventListenerPtr p(m);

    EXPECT_CALL(*m, noMatchingTestCases(StringRefEq("first"))).Times(1);
    EXPECT_CALL(*m, noMatchingTestCases(StringRefEq("second"))).Times(1);

    mr.addReporter(std::move(p));

    mr.noMatchingTestCases(Catch::StringRef("first"));
    mr.noMatchingTestCases(Catch::StringRef("second"));
}
