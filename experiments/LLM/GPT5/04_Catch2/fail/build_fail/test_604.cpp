// list_tests_604.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 interfaces (treat implementation as a black box)
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_config.hpp"

// Forward declaration of the function under test (defined in the TU being built)
namespace Catch {
    bool list(IEventListener& reporter, Config const& config);
}

using ::testing::_;
using ::testing::InSequence;
using ::testing::Times;

namespace {

// Minimal Google Mock for IEventListener that observes only listing-related calls.
class MockEventListener_604 : public Catch::IEventListener {
public:
    // Pass-through ctor; implementation treats m_config as an opaque pointer.
    explicit MockEventListener_604(const Catch::IConfig* cfg = nullptr)
        : Catch::IEventListener(cfg) {}

    // We only mock the methods that can be called by listing workflow.
    MOCK_METHOD(void, listReporters,
                (const std::vector<Catch::ReporterDescription>&), (override));
    MOCK_METHOD(void, listListeners,
                (const std::vector<Catch::ListenerDescription>&), (override));
    MOCK_METHOD(void, listTests,
                (const std::vector<Catch::TestCaseHandle>&), (override));
    MOCK_METHOD(void, listTags,
                (const std::vector<Catch::TagInfo>&), (override));
};

} // namespace

// Helper to build a Config with specific list* flags set.
// We rely only on the public constructor that accepts ConfigData and the
// public list* getters to observe behavior.
static Catch::Config makeConfig_604(bool listTests,
                                    bool listTags,
                                    bool listReporters,
                                    bool listListeners) {
    Catch::ConfigData data;               // Using public type & ctor from the codebase
    // Set only the fields relevant to listing behavior; other fields remain defaulted.
    data.listTests = listTests;
    data.listTags = listTags;
    data.listReporters = listReporters;
    data.listListeners = listListeners;
    return Catch::Config{data};
}

// ------------------------------------------------------------
// Tests
// ------------------------------------------------------------

// Verifies: When no list flags are set, list(...) returns false and does not
// invoke any listing callbacks on the reporter.
TEST(ListFunction_604, NoFlags_ReturnsFalse_And_NoReporterInteractions_604) {
    auto config = makeConfig_604(false, false, false, false);
    MockEventListener_604 reporter;

    EXPECT_CALL(reporter, listTests(_)).Times(0);
    EXPECT_CALL(reporter, listTags(_)).Times(0);
    EXPECT_CALL(reporter, listReporters(_)).Times(0);
    EXPECT_CALL(reporter, listListeners(_)).Times(0);

    const bool listed = Catch::list(reporter, config);
    EXPECT_FALSE(listed);
}

// Verifies: If listTests flag is set, list(...) returns true and triggers listTests only.
TEST(ListFunction_604, ListTestsFlag_TriggersListTests_Only_And_ReturnsTrue_604) {
    auto config = makeConfig_604(true, false, false, false);
    MockEventListener_604 reporter;

    EXPECT_CALL(reporter, listTests(_)).Times(1);
    EXPECT_CALL(reporter, listTags(_)).Times(0);
    EXPECT_CALL(reporter, listReporters(_)).Times(0);
    EXPECT_CALL(reporter, listListeners(_)).Times(0);

    const bool listed = Catch::list(reporter, config);
    EXPECT_TRUE(listed);
}

// Verifies: If listTags flag is set, list(...) returns true and triggers listTags only.
TEST(ListFunction_604, ListTagsFlag_TriggersListTags_Only_And_ReturnsTrue_604) {
    auto config = makeConfig_604(false, true, false, false);
    MockEventListener_604 reporter;

    EXPECT_CALL(reporter, listTests(_)).Times(0);
    EXPECT_CALL(reporter, listTags(_)).Times(1);
    EXPECT_CALL(reporter, listReporters(_)).Times(0);
    EXPECT_CALL(reporter, listListeners(_)).Times(0);

    const bool listed = Catch::list(reporter, config);
    EXPECT_TRUE(listed);
}

// Verifies: If listReporters flag is set, list(...) returns true and triggers listReporters only.
TEST(ListFunction_604, ListReportersFlag_TriggersListReporters_Only_And_ReturnsTrue_604) {
    auto config = makeConfig_604(false, false, true, false);
    MockEventListener_604 reporter;

    EXPECT_CALL(reporter, listTests(_)).Times(0);
    EXPECT_CALL(reporter, listTags(_)).Times(0);
    EXPECT_CALL(reporter, listReporters(_)).Times(1);
    EXPECT_CALL(reporter, listListeners(_)).Times(0);

    const bool listed = Catch::list(reporter, config);
    EXPECT_TRUE(listed);
}

// Verifies: If listListeners flag is set, list(...) returns true and triggers listListeners only.
TEST(ListFunction_604, ListListenersFlag_TriggersListListeners_Only_And_ReturnsTrue_604) {
    auto config = makeConfig_604(false, false, false, true);
    MockEventListener_604 reporter;

    EXPECT_CALL(reporter, listTests(_)).Times(0);
    EXPECT_CALL(reporter, listTags(_)).Times(0);
    EXPECT_CALL(reporter, listReporters(_)).Times(0);
    EXPECT_CALL(reporter, listListeners(_)).Times(1);

    const bool listed = Catch::list(reporter, config);
    EXPECT_TRUE(listed);
}

// Verifies: When multiple flags are set, list(...) returns true and triggers
// all corresponding callbacks in the documented order: tests → tags → reporters → listeners.
TEST(ListFunction_604, MultipleFlags_CallsInOrder_And_ReturnsTrue_604) {
    auto config = makeConfig_604(true, true, true, true);
    MockEventListener_604 reporter;

    InSequence seq; // enforce order: listTests, listTags, listReporters, listListeners
    EXPECT_CALL(reporter, listTests(_)).Times(1);
    EXPECT_CALL(reporter, listTags(_)).Times(1);
    EXPECT_CALL(reporter, listReporters(_)).Times(1);
    EXPECT_CALL(reporter, listListeners(_)).Times(1);

    const bool listed = Catch::list(reporter, config);
    EXPECT_TRUE(listed);
}
