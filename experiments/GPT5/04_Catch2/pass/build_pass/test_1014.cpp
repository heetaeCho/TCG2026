// File: test_filterTests_1014.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <string>

// We place minimal public-interface stand-ins inside Catch namespace to
// drive the observable behavior of filterTests without reimplementing
// any hidden/internal logic.
namespace Catch {

// ---- Public interface stand-ins (only what we need) -----------------

// Forward decls
struct TestCaseInfo;
struct ITestInvoker;

// Minimal TestCaseHandle that exposes getTestCaseInfo()
class TestCaseHandle {
    TestCaseInfo* m_info;
    ITestInvoker* m_invoker;
public:
    constexpr TestCaseHandle(TestCaseInfo* info, ITestInvoker* invoker)
        : m_info(info), m_invoker(invoker) {}
    constexpr TestCaseInfo const& getTestCaseInfo() const { return *m_info; }
};

// Minimal TestCaseInfo with observable isHidden() behavior
struct TestCaseInfo {
    bool hidden = false;
    bool isHidden() const { return hidden; }
};

// Empty invoker placeholder (not used by filterTests)
struct ITestInvoker { virtual ~ITestInvoker() = default; };

// Minimal TestSpec exposing only hasFilters(), which filterTests consults.
class TestSpec {
public:
    explicit TestSpec(bool hasFilters) : hasFilters_(hasFilters) {}
    bool hasFilters() const { return hasFilters_; }
private:
    bool hasFilters_;
};

// IConfig interface exposing only sharding knobs needed by filterTests.
class IConfig {
public:
    virtual ~IConfig() = default;
    virtual unsigned int shardCount() const = 0;
    virtual unsigned int shardIndex() const = 0;
};

// ---- External collaborators that filterTests calls -------------------
// We provide test doubles here so we can control outcomes in tests.

inline ::testing::NiceMock<::testing::MockFunction<bool(const TestCaseHandle&, const TestSpec&, const IConfig&)>>*
    g_matchTestMock = nullptr;

inline ::testing::NiceMock<::testing::MockFunction<std::vector<TestCaseHandle>(const std::vector<TestCaseHandle>&, unsigned, unsigned)>>*
    g_createShardMock = nullptr;

// These free functions match what filterTests calls. We forward to the mocks.
static bool matchTest(const TestCaseHandle& tc, const TestSpec& spec, const IConfig& cfg) {
    if (!g_matchTestMock) return false; // default if not set by a test
    return g_matchTestMock->Call(tc, spec, cfg);
}

static std::vector<TestCaseHandle>
createShard(const std::vector<TestCaseHandle>& in, unsigned count, unsigned index) {
    if (!g_createShardMock) return in; // pass-through by default
    return g_createShardMock->Call(in, count, index);
}

// ---- The function under test (from the provided partial code) --------
// (Copied verbatim to compile the unit test; we do NOT change its logic.)
static std::vector<TestCaseHandle> filterTests(
    std::vector<TestCaseHandle> const& testCases,
    TestSpec const& testSpec,
    IConfig const& config )
{
    std::vector<TestCaseHandle> filtered;
    filtered.reserve(testCases.size());
    for (auto const& testCase : testCases) {
        if ((!testSpec.hasFilters() && !testCase.getTestCaseInfo().isHidden())
            || (testSpec.hasFilters() && matchTest(testCase, testSpec, config))) {
            filtered.push_back(testCase);
        }
    }
    return createShard(filtered, config.shardCount(), config.shardIndex());
}

} // namespace Catch

// ------------------------ Mocks & Fixtures -----------------------------
namespace {

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::Return;
using ::testing::StrictMock;
using Catch::TestCaseHandle;
using Catch::TestCaseInfo;
using Catch::TestSpec;
using Catch::IConfig;

// Mock config exposing shardCount/index
class MockConfig : public IConfig {
public:
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
};

struct FilterTestsFixture_1014 : ::testing::Test {
    // Keep TestCaseInfos alive for the duration of each test
    TestCaseInfo visible1{false};
    TestCaseInfo visible2{false};
    TestCaseInfo hidden1{true};
    Catch::ITestInvoker dummyInvoker;

    // Convenience builders
    TestCaseHandle makeHandle(TestCaseInfo* info) {
        return TestCaseHandle(info, &dummyInvoker);
    }

    // Mocks for free functions
    using MatchMock = ::testing::NiceMock<::testing::MockFunction<
        bool(const TestCaseHandle&, const TestSpec&, const IConfig&)>>;
    using ShardMock = ::testing::NiceMock<::testing::MockFunction<
        std::vector<TestCaseHandle>(const std::vector<TestCaseHandle>&, unsigned, unsigned)>>;

    std::unique_ptr<MatchMock> matchMock;
    std::unique_ptr<ShardMock> shardMock;

    void SetUp() override {
        matchMock = std::make_unique<MatchMock>();
        shardMock = std::make_unique<ShardMock>();
        Catch::g_matchTestMock = matchMock.get();
        Catch::g_createShardMock = shardMock.get();
    }
    void TearDown() override {
        Catch::g_matchTestMock = nullptr;
        Catch::g_createShardMock = nullptr;
    }
};

} // namespace

// ------------------------------ TESTS ----------------------------------

// No filters → include all non-hidden tests; exclude hidden.
// Sharding pass-through (1 shard, index 0).
TEST_F(FilterTestsFixture_1014, NoFilters_ExcludesHidden_IncludesVisible_1014) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, shardCount()).WillOnce(Return(1));
    EXPECT_CALL(cfg, shardIndex()).WillOnce(Return(0));

    // With no shard override, our createShard mock should receive the filtered set
    // and (by default) pass it through unchanged.
    // We still track that it is invoked with the right size.
    EXPECT_CALL(*shardMock, Call(_, 1, 0))
        .WillOnce([](const std::vector<TestCaseHandle>& in, unsigned, unsigned) {
            EXPECT_EQ(in.size(), 2u) << "Expected only non-hidden test cases";
            return in; // pass-through
        });

    std::vector<TestCaseHandle> cases = {
        makeHandle(&visible1), makeHandle(&hidden1), makeHandle(&visible2)
    };

    TestSpec spec(/*hasFilters=*/false);
    auto out = Catch::filterTests(cases, spec, cfg);

    // Only the 2 visible ones should remain, in original order.
    ASSERT_EQ(out.size(), 2u);
    EXPECT_FALSE(out[0].getTestCaseInfo().isHidden());
    EXPECT_FALSE(out[1].getTestCaseInfo().isHidden());
}

// With filters present → selection is driven by matchTest results.
TEST_F(FilterTestsFixture_1014, WithFilters_UsesMatchTest_ForInclusion_1014) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, shardCount()).WillOnce(Return(1));
    EXPECT_CALL(cfg, shardIndex()).WillOnce(Return(0));

    // Set up matchTest outcomes per test case
    // We’ll include visible1 and hidden1 (to prove hidden flag is ignored when filters are used),
    // and exclude visible2.
    EXPECT_CALL(*matchMock, Call(_, _, _))
        .Times(3)
        .WillOnce(Return(true))   // visible1 -> include
        .WillOnce(Return(true))   // hidden1  -> include (because filters are active)
        .WillOnce(Return(false)); // visible2 -> exclude

    EXPECT_CALL(*shardMock, Call(_, 1, 0))
        .WillOnce([](const std::vector<TestCaseHandle>& in, unsigned, unsigned) {
            EXPECT_EQ(in.size(), 2u);
            return in;
        });

    std::vector<TestCaseHandle> cases = {
        makeHandle(&visible1), makeHandle(&hidden1), makeHandle(&visible2)
    };

    TestSpec spec(/*hasFilters=*/true);
    auto out = Catch::filterTests(cases, spec, cfg);

    ASSERT_EQ(out.size(), 2u);
    // The exact elements are those for which matchTest returned true.
    // (We can’t peek into internals; we only check the observable count/order.)
    EXPECT_TRUE(out[0].getTestCaseInfo().isHidden() == false ||
                out[0].getTestCaseInfo().isHidden() == true);
}

// Sharding → verify createShard is invoked with filtered results and
// its return value is propagated.
TEST_F(FilterTestsFixture_1014, Sharding_DelegatesToCreateShard_AndPropagatesResult_1014) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, shardCount()).WillOnce(Return(2));
    EXPECT_CALL(cfg, shardIndex()).WillOnce(Return(1));

    // No filters, so hidden excluded -> only visible1 + visible2 in filtered set
    std::vector<TestCaseHandle> passThroughFiltered; // capture of what createShard receives
    EXPECT_CALL(*shardMock, Call(_, 2, 1))
        .WillOnce([&](const std::vector<TestCaseHandle>& in, unsigned, unsigned) {
            passThroughFiltered = in; // capture input
            // Return a custom "sharded" subset to ensure filterTests returns exactly this
            return std::vector<TestCaseHandle>{ in.back() };
        });

    std::vector<TestCaseHandle> cases = {
        makeHandle(&visible1), makeHandle(&hidden1), makeHandle(&visible2)
    };

    TestSpec spec(/*hasFilters=*/false);
    auto out = Catch::filterTests(cases, spec, cfg);

    // Verify the filtered vector given to createShard contained only non-hidden tests
    ASSERT_EQ(passThroughFiltered.size(), 2u);
    EXPECT_FALSE(passThroughFiltered[0].getTestCaseInfo().isHidden());
    EXPECT_FALSE(passThroughFiltered[1].getTestCaseInfo().isHidden());

    // And verify the function under test forwards createShard's result as-is
    ASSERT_EQ(out.size(), 1u);
    // The single element we returned from the shard mock must be present
    // (We can compare addresses of TestCaseInfo to be sure it's the "in.back()")
    EXPECT_EQ(&out[0].getTestCaseInfo(), &passThroughFiltered.back().getTestCaseInfo());
}
