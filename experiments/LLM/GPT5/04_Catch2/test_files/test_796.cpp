// File: tests/ReporterMulti_testCaseStarting_796.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_multi.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/catch_test_case_info.hpp>

using ::testing::_;
using ::testing::Ref;
using ::testing::NiceMock;
using ::testing::StrictMock;

namespace {

// Minimal mock of an event listener, only mocking what we observe.
class MockEventListener_796 : public Catch::IEventListener {
public:
    // Base requires a config ptr; we don't use it in these tests.
    MockEventListener_796() : Catch::IEventListener(nullptr) {}
    ~MockEventListener_796() override = default;

    MOCK_METHOD(void, testCaseStarting,
                (Catch::TestCaseInfo const&),
                (override));
};

// Helper to build a simple TestCaseInfo instance via public API only.
static Catch::TestCaseInfo makeTestCaseInfo_796(
    const char* name = "TC_796",
    const char* tags = "[tag]")
{
    Catch::NameAndTags nt;
    nt.name = name;
    nt.tags = tags;

    Catch::SourceLineInfo sli{"file_796.cpp", 123};
    return Catch::TestCaseInfo(Catch::StringRef("Class796"), nt, sli);
}

} // namespace

// Fixture in case construction needs to be shared later.
class MultiReporterTest_796 : public ::testing::Test {
protected:
    // Most Catch2 builds provide MultiReporter(IConfig const*) constructor.
    // We pass nullptr; tests never dereference it.
    Catch::MultiReporter mr{nullptr};
};

// Normal operation: with one listener, the call is forwarded exactly once
// with the same TestCaseInfo reference.
TEST_F(MultiReporterTest_796, ForwardsToSingleListener_796) {
    auto info = makeTestCaseInfo_796();

    // Prepare listener mock and keep raw pointer for expectations.
    Catch::IEventListenerPtr lptr{ new StrictMock<MockEventListener_796>() };
    auto* lraw = static_cast<MockEventListener_796*>(lptr.get());

    EXPECT_CALL(*lraw, testCaseStarting(Ref(info))).Times(1);

    mr.addListener(std::move(lptr));

    mr.testCaseStarting(info);
}

// Normal operation: with both a listener and a reporter added through the
// public APIs, the event is forwarded to both.
TEST_F(MultiReporterTest_796, ForwardsToListenerAndReporter_796) {
    auto info = makeTestCaseInfo_796("DualTargets_796");

    Catch::IEventListenerPtr lptr{ new StrictMock<MockEventListener_796>() };
    auto* lraw = static_cast<MockEventListener_796*>(lptr.get());

    Catch::IEventListenerPtr rptr{ new StrictMock<MockEventListener_796>() };
    auto* rraw = static_cast<MockEventListener_796*>(rptr.get());

    EXPECT_CALL(*lraw, testCaseStarting(Ref(info))).Times(1);
    EXPECT_CALL(*rraw, testCaseStarting(Ref(info))).Times(1);

    mr.addListener(std::move(lptr));
    mr.addReporter(std::move(rptr));

    mr.testCaseStarting(info);
}

// Boundary condition: no listeners/reporters added — calling the method
// should be a no-op with no crashes or side effects observable here.
TEST_F(MultiReporterTest_796, NoReportersOrListeners_NoCrash_796) {
    auto info = makeTestCaseInfo_796("NoTargets_796");
    // No expectations to set — we just exercise the call.
    mr.testCaseStarting(info);
}

// Re-entrancy/Idempotence of forwarding: multiple invocations should be
// forwarded each time (observable: per-call invocation count).
TEST_F(MultiReporterTest_796, MultipleInvocations_AreAllForwarded_796) {
    auto info1 = makeTestCaseInfo_796("Call1_796");
    auto info2 = makeTestCaseInfo_796("Call2_796");

    Catch::IEventListenerPtr lptr{ new StrictMock<MockEventListener_796>() };
    auto* lraw = static_cast<MockEventListener_796*>(lptr.get());

    // Expect one call per invocation with the exact object each time.
    EXPECT_CALL(*lraw, testCaseStarting(Ref(info1))).Times(1);
    EXPECT_CALL(*lraw, testCaseStarting(Ref(info2))).Times(1);

    mr.addListener(std::move(lptr));

    mr.testCaseStarting(info1);
    mr.testCaseStarting(info2);
}

