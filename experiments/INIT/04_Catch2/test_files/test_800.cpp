// File: tests/Reporters/MultiReporter_assertionEnded_800.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_multi.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/catch_assertion_result.hpp>
#include <catch2/internal/catch_result_type.hpp>
#include <catch2/catch_source_line_info.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_message.hpp>

using ::testing::_;
using ::testing::A;
using ::testing::NiceMock;
using ::testing::StrictMock;
using ::testing::Return;

namespace {

using namespace Catch;

// ---- Mocks (external collaborators only) ----

class MockConfig final : public IConfig {
public:
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));

    // The rest of IConfig’s virtuals are not used by these tests.
    // They have default implementations in Catch2 or are irrelevant here.
};

class MockListener final : public IEventListener {
public:
    // Pass config up to the base so MultiReporter can read m_config
    explicit MockListener(IConfig const* cfg, bool reportAll)
        : IEventListener(cfg) {
        // Control observable preferences via the public base machinery
        m_preferences.shouldReportAllAssertions = reportAll;
    }

    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
};

// Helper to build AssertionStats with desired result type (observable to MultiReporter)
static AssertionStats makeStats(ResultWas::OfType resultType) {
    // Minimal-but-valid ingredients for AssertionResult
    AssertionInfo info{
        StringRef("TEST_MACRO"),
        SourceLineInfo{ "dummy.cpp", 123 },
        StringRef("x == y"),
        ResultDisposition::Normal
    };

    AssertionResultData data{};
    data.resultType = resultType;

    AssertionResult result(info, std::move(data));
    std::vector<MessageInfo> messages;
    Totals totals{};
    return AssertionStats(result, messages, totals);
}

class MultiReporterAssertionEndedTest_800 : public ::testing::Test {
protected:
    StrictMock<MockConfig> config_;
    // MultiReporter is constructed with a config; this mirrors real usage.
    MultiReporter mr_{ &config_ };

    // Convenience helpers for adding listeners/reporters while keeping raw ptrs for expectations
    MockListener* addListener(bool reportAll) {
        auto* raw = new NiceMock<MockListener>(&config_, reportAll);
        Detail::unique_ptr<IEventListener> ptr(raw);
        mr_.addListener(std::move(ptr));
        return raw;
    }

    MockListener* addReporter(bool reportAll) {
        auto* raw = new StrictMock<MockListener>(&config_, reportAll);
        Detail::unique_ptr<IEventListener> ptr(raw);
        mr_.addReporter(std::move(ptr));
        return raw;
    }
};

} // namespace

// [Normal operation] Non-OK results are always reported to all reporter-likes.
TEST_F(MultiReporterAssertionEndedTest_800,
       NonOkResult_DispatchesToAllReporterLikes_800) {
    // Given two sinks with different preferences
    auto* l1 = addListener(/*reportAll=*/false);
    auto* l2 = addReporter(/*reportAll=*/true);

    // Config’s includeSuccessfulResults() is irrelevant for non-OK
    ON_CALL(config_, includeSuccessfulResults()).WillByDefault(Return(false));

    // Expect forwarding to both
    EXPECT_CALL(*l1, assertionEnded(A<AssertionStats const&>())).Times(1);
    EXPECT_CALL(*l2, assertionEnded(A<AssertionStats const&>())).Times(1);

    auto stats = makeStats(ResultWas::ExplicitFailure);
    mr_.assertionEnded(stats);
}

// [Normal operation] OK + config includes successes -> forwarded to all.
TEST_F(MultiReporterAssertionEndedTest_800,
       OkResult_WhenConfigIncludesSuccess_DispatchesToAll_800) {
    auto* l1 = addListener(/*reportAll=*/false);
    auto* l2 = addReporter(/*reportAll=*/true);

    EXPECT_CALL(config_, includeSuccessfulResults()).WillOnce(Return(true));

    EXPECT_CALL(*l1, assertionEnded(A<AssertionStats const&>())).Times(1);
    EXPECT_CALL(*l2, assertionEnded(A<AssertionStats const&>())).Times(1);

    auto stats = makeStats(ResultWas::Ok);
    mr_.assertionEnded(stats);
}

// [Boundary] OK + config does NOT include successes -> only those preferring all assertions get called.
TEST_F(MultiReporterAssertionEndedTest_800,
       OkResult_ConfigOmitsSuccess_DispatchesOnlyToReportAll_800) {
    auto* l_reportNone = addListener(/*reportAll=*/false);
    auto* l_reportAll  = addReporter(/*reportAll=*/true);

    EXPECT_CALL(config_, includeSuccessfulResults()).WillOnce(Return(false));

    // No call for the one that does not want all assertions on success
    // (NiceMock for l_reportNone so absence of calls doesn't fail test)
    EXPECT_CALL(*l_reportAll, assertionEnded(A<AssertionStats const&>())).Times(1);

    auto stats = makeStats(ResultWas::Ok);
    mr_.assertionEnded(stats);
}

// [Boundary/Exceptional] No reporter-likes registered -> must not crash or throw.
TEST_F(MultiReporterAssertionEndedTest_800,
       NoListenersAdded_DoesNotCrash_800) {
    EXPECT_CALL(config_, includeSuccessfulResults()).WillOnce(Return(true));
    auto stats = makeStats(ResultWas::Ok);

    // Just invoke; absence of crashes/exceptions is the assertion
    mr_.assertionEnded(stats);
}
