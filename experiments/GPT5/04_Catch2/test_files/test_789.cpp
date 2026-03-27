// File: tests/multi_reporter_fatal_error_789.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/reporters/catch_reporter_multi.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"

using ::testing::StrictMock;
using ::testing::_;
using ::testing::Truly;

namespace {

// Simple matcher comparing StringRef content via its explicit std::string conversion
MATCHER_P(StringRefEq, expected, "StringRef equals expected string") {
    return static_cast<std::string>(arg) == expected;
}

class MockListener_789 : public Catch::IEventListener {
public:
    explicit MockListener_789(Catch::IConfig const* cfg = nullptr)
        : Catch::IEventListener(cfg) {}
    ~MockListener_789() override = default;

    MOCK_METHOD(void, fatalErrorEncountered, (Catch::StringRef error), (override));
};

class MultiReporterFatalErrorTest_789 : public ::testing::Test {
protected:
    // In Catch2, MultiReporter is typically constructed with IConfig*. We pass nullptr here.
    Catch::MultiReporter mr_{nullptr};

    // Helper to wrap a raw pointer in the Catch::Detail::unique_ptr base type
    template <typename T>
    Catch::Detail::unique_ptr<Catch::IEventListener> wrap(T* p) {
        return Catch::Detail::unique_ptr<Catch::IEventListener>(p);
    }
};

} // namespace

// --- Tests ---

TEST_F(MultiReporterFatalErrorTest_789, NoReporters_DoesNotCrash_789) {
    // Should be a no-op with no reporters/listeners registered.
    EXPECT_NO_THROW(mr_.fatalErrorEncountered(Catch::StringRef("boom")));
}

TEST_F(MultiReporterFatalErrorTest_789, ForwardsToSingleReporter_789) {
    // Arrange
    auto* mock = new StrictMock<MockListener_789>();
    EXPECT_CALL(*mock, fatalErrorEncountered(StringRefEq("boom"))).Times(1);

    // Hand ownership to MultiReporter
    mr_.addReporter(wrap(mock));

    // Act
    mr_.fatalErrorEncountered(Catch::StringRef("boom"));
}

TEST_F(MultiReporterFatalErrorTest_789, ForwardsToReporterAndListener_789) {
    // Arrange (two different recipients)
    auto* reporter = new StrictMock<MockListener_789>();
    auto* listener = new StrictMock<MockListener_789>();

    EXPECT_CALL(*reporter, fatalErrorEncountered(StringRefEq("E!"))).Times(1);
    EXPECT_CALL(*listener, fatalErrorEncountered(StringRefEq("E!"))).Times(1);

    // Register via both APIs — tests only observable fan-out, not internal storage
    mr_.addReporter(wrap(reporter));
    mr_.addListener(wrap(listener));

    // Act
    mr_.fatalErrorEncountered(Catch::StringRef("E!"));
}

TEST_F(MultiReporterFatalErrorTest_789, ForwardsEmptyString_789) {
    auto* mock = new StrictMock<MockListener_789>();
    EXPECT_CALL(*mock, fatalErrorEncountered(StringRefEq(""))).Times(1);

    mr_.addReporter(wrap(mock));
    mr_.fatalErrorEncountered(Catch::StringRef(""));
}
