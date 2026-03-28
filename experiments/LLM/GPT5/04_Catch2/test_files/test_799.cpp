// File: tests/reporter/MultiReporter_assertionStarting_799.test.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_assertion_info.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using ::testing::_;
using ::testing::InSequence;
using ::testing::Ref;
using ::testing::StrictMock;

namespace Catch {

// Minimal mock for external collaborator (IEventListener)
class MockListener_799 : public IEventListener {
public:
    // Base expects a config pointer; passing nullptr is fine for these tests.
    MockListener_799() : IEventListener(nullptr) {}

    MOCK_METHOD(void, assertionStarting,
                (AssertionInfo const& assertionInfo), (override));
};

namespace {
    // Helper to wrap raw pointer into Catch's unique_ptr used by MultiReporter
    static Detail::unique_ptr<IEventListener> WrapPtr_799(IEventListener* p) {
        return Detail::unique_ptr<IEventListener>(p);
    }
}

// Fixture in case we need shared helpers later
class MultiReporterTest_799 : public ::testing::Test {
protected:
    MultiReporter uut_; // system under test
};

TEST_F(MultiReporterTest_799, ForwardsToAllReportersInInsertionOrder_799) {
    // Arrange
    auto* l1 = new StrictMock<MockListener_799>();
    auto* r1 = new StrictMock<MockListener_799>();
    auto* l2 = new StrictMock<MockListener_799>();

    // Insert in a specific order across listeners/reporters
    uut_.addListener(WrapPtr_799(l1));
    uut_.addReporter(WrapPtr_799(r1));
    uut_.addListener(WrapPtr_799(l2));

    AssertionInfo info{}; // treat as opaque; default-constructed

    // Expect: calls happen in insertion order with the same info reference
    InSequence seq;
    EXPECT_CALL(*l1, assertionStarting(Ref(info))).Times(1);
    EXPECT_CALL(*r1, assertionStarting(Ref(info))).Times(1);
    EXPECT_CALL(*l2, assertionStarting(Ref(info))).Times(1);

    // Act
    uut_.assertionStarting(info);

    // Assert (via expectations)
}

TEST_F(MultiReporterTest_799, DoesNothingWhenNoReporters_799) {
    // Arrange: no listeners/reporters added
    AssertionInfo info{};

    // Act & Assert: Should not crash; no interactions to verify.
    // Using SUCCEED() to make intent explicit.
    uut_.assertionStarting(info);
    SUCCEED();
}

TEST_F(MultiReporterTest_799, PassesExactSameAssertionInfoObject_799) {
    // Arrange
    auto* l = new StrictMock<MockListener_799>();
    uut_.addListener(WrapPtr_799(l));

    AssertionInfo info{};

    // Expect the very same object reference to be forwarded (not a copy)
    EXPECT_CALL(*l, assertionStarting(Ref(info))).Times(1);

    // Act
    uut_.assertionStarting(info);

    // Assert via expectations
}

TEST_F(MultiReporterTest_799, MixedListenersAndReporters_AllReceiveNotification_799) {
    // Arrange
    auto* a = new StrictMock<MockListener_799>();
    auto* b = new StrictMock<MockListener_799>();

    // Mix addReporter / addListener calls in varying order
    uut_.addReporter(WrapPtr_799(a));
    uut_.addListener(WrapPtr_799(b));

    AssertionInfo info{};

    // Both must be called exactly once with the same reference
    EXPECT_CALL(*a, assertionStarting(Ref(info))).Times(1);
    EXPECT_CALL(*b, assertionStarting(Ref(info))).Times(1);

    // Act
    uut_.assertionStarting(info);

    // Assert via expectations
}

} // namespace Catch
