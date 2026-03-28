// File: tests/multi_reporter_listtests_808.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Catch2/src/catch2/reporters/catch_reporter_multi.hpp"
#include "Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp"

#include <stdexcept>

using ::testing::_;
using ::testing::InSequence;
using ::testing::Ref;
using ::testing::StrictMock;

namespace Catch {

class MockListener_808 : public IEventListener {
public:
    MockListener_808() : IEventListener(nullptr) {}
    ~MockListener_808() override = default;

    // Only override what we need for these tests.
    MOCK_METHOD(void, listTests, (const std::vector<TestCaseHandle>&), (override));
};

// A small helper to wrap raw mock pointers into Catch's unique_ptr
static IEventListenerPtr makePtr_808(MockListener_808* p) {
    // IEventListenerPtr is an alias to Catch::Detail::unique_ptr<IEventListener>
    return IEventListenerPtr(p);
}

class MultiReporterListTests_808 : public ::testing::Test {
protected:
    // MultiReporter typically takes an IConfig*; listTests does not rely on it, so nullptr is fine.
    MultiReporter reporter{nullptr};
};

// Normal operation: forwards to all added reporters in insertion order
TEST_F(MultiReporterListTests_808, ForwardsToAllReportersInOrder_808) {
    StrictMock<MockListener_808>* first  = new StrictMock<MockListener_808>();
    StrictMock<MockListener_808>* second = new StrictMock<MockListener_808>();

    reporter.addReporter(makePtr_808(first));
    reporter.addReporter(makePtr_808(second));

    std::vector<TestCaseHandle> tests; // empty is fine; we assert same-ref forwarding

    InSequence seq;
    EXPECT_CALL(*first,  listTests(Ref(tests))).Times(1);
    EXPECT_CALL(*second, listTests(Ref(tests))).Times(1);

    reporter.listTests(tests);
}

// Boundary: no reporters/listeners added — should be a no-op (no crash)
TEST_F(MultiReporterListTests_808, NoReporters_NoOp_808) {
    std::vector<TestCaseHandle> tests;
    // No expectations — just ensure it does not throw or crash
    reporter.listTests(tests);
    SUCCEED();
}

// Interaction: mixing listeners and reporters — everyone receives the call
TEST_F(MultiReporterListTests_808, ForwardsToListenersAndReporters_808) {
    StrictMock<MockListener_808>* listener = new StrictMock<MockListener_808>();
    StrictMock<MockListener_808>* reporterish = new StrictMock<MockListener_808>();

    reporter.addListener(makePtr_808(listener));
    reporter.addReporter(makePtr_808(reporterish));

    std::vector<TestCaseHandle> tests;

    // Order is not critical in this test; just ensure both are called with the same ref
    EXPECT_CALL(*listener,    listTests(Ref(tests))).Times(1);
    EXPECT_CALL(*reporterish, listTests(Ref(tests))).Times(1);

    reporter.listTests(tests);
}

// Error/exceptional case: if a reporter throws, the exception propagates and later reporters are not called
TEST_F(MultiReporterListTests_808, PropagatesExceptionAndStopsFurtherCalls_808) {
    StrictMock<MockListener_808>* throwing = new StrictMock<MockListener_808>();
    StrictMock<MockListener_808>* not_called = new StrictMock<MockListener_808>();

    reporter.addReporter(makePtr_808(throwing));
    reporter.addReporter(makePtr_808(not_called));

    std::vector<TestCaseHandle> tests;

    EXPECT_CALL(*throwing, listTests(Ref(tests)))
        .WillOnce([](const std::vector<TestCaseHandle>&){ throw std::runtime_error("boom"); });

    // Must not be invoked if the first throws
    EXPECT_CALL(*not_called, listTests(_)).Times(0);

    EXPECT_THROW(reporter.listTests(tests), std::runtime_error);
}

// Sanity: forwards the exact same vector instance (by reference), not a copy
TEST_F(MultiReporterListTests_808, ForwardsSameReference_808) {
    StrictMock<MockListener_808>* mock = new StrictMock<MockListener_808>();
    reporter.addReporter(makePtr_808(mock));

    std::vector<TestCaseHandle> tests;

    EXPECT_CALL(*mock, listTests(Ref(tests))).Times(1);

    reporter.listTests(tests);
}

} // namespace Catch
