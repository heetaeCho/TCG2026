// TEST_ID: 807

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

using ::testing::Ref;
using ::testing::StrictMock;
using ::testing::NiceMock;
using ::testing::_;
namespace C = Catch;

// Minimal mock of IEventListener that only observes listListeners.
// We do not simulate any internal MultiReporter behavior.
class MockEventListener_807 : public C::IEventListener {
public:
    explicit MockEventListener_807(C::IConfig const* cfg = nullptr)
        : C::IEventListener(cfg) {}

    MOCK_METHOD(void, listListeners,
                (const std::vector<C::ListenerDescription>&),
                (override));
};

// Test fixture holding a MultiReporter instance.
// We pass nullptr for IConfig*, as tests do not depend on configuration.
class MultiReporterListListenersTest_807 : public ::testing::Test {
protected:
    // Many Catch2 reporter-ish types accept (IConfig const*) in ctor,
    // and MultiReporter typically forwards it. Using nullptr is fine
    // because we only exercise listListeners forwarding.
    C::MultiReporter mr_{ /*IConfig*/ nullptr };
};

// [Normal] Single listener receives the exact same descriptions by reference.
TEST_F(MultiReporterListListenersTest_807, ForwardsToSingleListener_807) {
    // Arrange
    auto* raw = new StrictMock<MockEventListener_807>(nullptr);
    std::vector<C::ListenerDescription> descriptions; // empty is fine; we only check forwarding & reference equality

    EXPECT_CALL(*raw, listListeners(Ref(descriptions))).Times(1);

    C::IEventListenerPtr p(raw); // MultiReporter takes ownership
    mr_.addListener(std::move(p));

    // Act
    mr_.listListeners(descriptions);

    // Assert is via EXPECT_CALL
}

// [Normal] Multiple entries (mix of listener + reporter) all receive the same descriptions.
TEST_F(MultiReporterListListenersTest_807, ForwardsToAllReporterLikes_807) {
    auto* l1 = new StrictMock<MockEventListener_807>(nullptr);
    auto* r  = new StrictMock<MockEventListener_807>(nullptr);
    auto* l2 = new StrictMock<MockEventListener_807>(nullptr);

    std::vector<C::ListenerDescription> descriptions;

    EXPECT_CALL(*l1, listListeners(Ref(descriptions))).Times(1);
    EXPECT_CALL(*r,  listListeners(Ref(descriptions))).Times(1);
    EXPECT_CALL(*l2, listListeners(Ref(descriptions))).Times(1);

    C::IEventListenerPtr p1(l1);
    C::IEventListenerPtr p2(r);
    C::IEventListenerPtr p3(l2);

    mr_.addListener(std::move(p1)); // add as listener
    mr_.addReporter(std::move(p2)); // add as reporter
    mr_.addListener(std::move(p3)); // another listener

    mr_.listListeners(descriptions); // each should be invoked exactly once
}

// [Boundary] No listeners/reporters added — calling listListeners should be a no-op (no crash).
TEST_F(MultiReporterListListenersTest_807, NoReporterLikes_NoOp_807) {
    std::vector<C::ListenerDescription> descriptions;
    // Should not throw or crash. (GTest will fail the test if it does.)
    mr_.listListeners(descriptions);
    SUCCEED();
}

// [Robustness] Can be called repeatedly; each time forwards to all contained entries.
TEST_F(MultiReporterListListenersTest_807, MultipleCallsForwardEachTime_807) {
    auto* raw = new StrictMock<MockEventListener_807>(nullptr);
    std::vector<C::ListenerDescription> descriptions;

    // Expect two forwards on the same underlying listener
    EXPECT_CALL(*raw, listListeners(Ref(descriptions))).Times(2);

    C::IEventListenerPtr p(raw);
    mr_.addListener(std::move(p));

    mr_.listListeners(descriptions);
    mr_.listListeners(descriptions);
}
