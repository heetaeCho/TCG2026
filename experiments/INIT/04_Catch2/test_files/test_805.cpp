// File: tests/Reporter/MultiReporter_skipTest_805.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include only public interfaces
#include "catch2/reporters/catch_reporter_multi.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"

using ::testing::_;
using ::testing::Ref;
using ::testing::StrictMock;

namespace {

// Minimal mock for external collaborator (listener/reporters)
class MockEventListener : public Catch::IEventListener {
public:
    // IEventListener takes IConfig*, which we don't need here; nullptr is fine.
    explicit MockEventListener() : Catch::IEventListener(nullptr) {}

    // We only care about skipTest for these tests.
    MOCK_METHOD(void, skipTest, (Catch::TestCaseInfo const&), (override));
};

// Helper to build a lightweight TestCaseInfo via its public ctor.
// We do not rely on any private/internal state.
inline Catch::TestCaseInfo makeTestCaseInfo(
    Catch::StringRef cls = Catch::StringRef("DummyClass"),
    const std::string& name = "DummyTest",
    const std::string& file = "dummy_file.cpp",
    std::size_t line = 42
) {
    Catch::NameAndTags nt{name, ""};              // public carrier for name/tags
    Catch::SourceLineInfo sli{file.c_str(), line};
    return Catch::TestCaseInfo(cls, nt, sli);     // public constructor
}

struct MultiReporterSkipTest_805 : ::testing::Test {
    Catch::MultiReporter mr;
};

} // namespace

// [Normal] Single reporter: skipTest is forwarded exactly once with the same reference.
TEST_F(MultiReporterSkipTest_805, ForwardsToSingleReporter_805) {
    auto* raw = new StrictMock<MockEventListener>();
    // Take ownership in the MultiReporter via its public API
    Catch::IEventListenerPtr p1(raw);
    mr.addReporter(std::move(p1));

    auto testInfo = makeTestCaseInfo();

    // Verify same object reference is forwarded
    EXPECT_CALL(*raw, skipTest(Ref(testInfo))).Times(1);

    mr.skipTest(testInfo);
}

// [Normal] Multiple listeners/reporters: all receive the call.
TEST_F(MultiReporterSkipTest_805, ForwardsToAllAttached_805) {
    auto* r1 = new StrictMock<MockEventListener>();
    auto* r2 = new StrictMock<MockEventListener>();
    auto* l1 = new StrictMock<MockEventListener>();

    Catch::IEventListenerPtr p1(r1);
    Catch::IEventListenerPtr p2(r2);
    Catch::IEventListenerPtr p3(l1);

    // Mix of addReporter/addListener — both are public APIs and external to the test.
    mr.addReporter(std::move(p1));
    mr.addListener(std::move(p2));
    mr.addListener(std::move(p3));

    auto testInfo = makeTestCaseInfo();

    EXPECT_CALL(*r1, skipTest(Ref(testInfo))).Times(1);
    EXPECT_CALL(*r2, skipTest(Ref(testInfo))).Times(1);
    EXPECT_CALL(*l1, skipTest(Ref(testInfo))).Times(1);

    mr.skipTest(testInfo);
}

// [Boundary] No attached listeners/reporters: calling skipTest is a no-op (no crash).
TEST_F(MultiReporterSkipTest_805, NoListeners_NoCrash_805) {
    auto testInfo = makeTestCaseInfo();
    // Should not throw or crash; nothing to expect.
    mr.skipTest(testInfo);
    SUCCEED();
}

// [Robustness] Repeated calls: propagation happens every time.
TEST_F(MultiReporterSkipTest_805, RepeatedCalls_PropagatesEveryTime_805) {
    auto* raw = new StrictMock<MockEventListener>();
    Catch::IEventListenerPtr p(raw);
    mr.addReporter(std::move(p));

    auto testInfo = makeTestCaseInfo();

    EXPECT_CALL(*raw, skipTest(Ref(testInfo))).Times(2);

    mr.skipTest(testInfo);
    mr.skipTest(testInfo);
}
