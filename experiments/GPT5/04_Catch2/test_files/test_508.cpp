// File: run_context_get_current_test_name_508_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <string>

// Catch2 public headers needed for the types referenced by the interface.
// If your project uses amalgamated headers, adjust includes accordingly.
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_test_case_info.hpp"

using ::testing::NiceMock;
using ::testing::Invoke;

namespace {

// ------------------------
// Minimal test doubles
// ------------------------

// A minimal no-op event listener so RunContext can be constructed and call into it.
// Implement/override only what your Catch2 version marks as pure virtual.
// If your repo has a ready-made no-op listener, use that instead.
struct NoopEventListener : Catch::IEventListener {
    // Depending on your Catch2 version, add empty overrides as needed.
    // We intentionally keep this as a no-op sink.
    // If your interface requires ctor with IConfig, provide it too.
    // Virtual destructor already exists in the base type.
};

// A very small config stub that only needs to satisfy what RunContext accesses
// in the constructor and during run. If your version of IConfig has more
// pure-virtual methods, either add trivial overrides, or replace this with
// your existing test config stub.
class StubConfig : public Catch::IConfig {
public:
    StubConfig() = default;
    ~StubConfig() override = default;

    // Return any stable name for the current run
    std::string const& name() const override {
        static std::string k = "stub-run";
        return k;
    }

    // ---- Add trivial overrides here if your IConfig has more pure virtuals ----
    // For example (names vary by Catch2 version):
    // bool allowThrows() const override { return true; }
    // bool shouldDebugBreak() const override { return false; }
    // int abortAfter() const override { return 0; }
    // bool warnAboutMissingAssertions() const override { return true; }
    // ... etc.
};

// Google Mock invoker that lets us observe getCurrentTestName() while the test is "running".
struct MockTestInvoker : Catch::ITestInvoker {
    MOCK_METHOD(void, invoke, (), (const, override));
};

// Helper to construct a TestCaseHandle with a specific name and supplied invoker.
static Catch::TestCaseHandle makeTestCaseHandle(
    const std::string& test_name,
    Catch::ITestInvoker* invoker
) {
    // Build the minimal pieces required by TestCaseInfo’s constructor.
    // Names and exact types (NameAndTags / SourceLineInfo) are from Catch2’s public API.
    Catch::NameAndTags nt;
    nt.name = test_name;
    nt.tags = "";

    Catch::SourceLineInfo sli{ __FILE__, static_cast<std::size_t>(__LINE__) };

    // Create the TestCaseInfo – we only care about the .name observable.
    auto* info = new Catch::TestCaseInfo(/* className */ Catch::StringRef(),
                                         /* name&tags */ nt,
                                         /* line info */ sli);

    // Construct TestCaseHandle that RunContext will use.
    return Catch::TestCaseHandle(info, invoker);
}

// Small RAII to own the allocated TestCaseInfo inside TestCaseHandle created by makeTestCaseHandle
struct OwnedTestCase {
    Catch::TestCaseHandle handle;
    std::unique_ptr<Catch::TestCaseInfo> info_owner;

    OwnedTestCase(Catch::TestCaseHandle h, Catch::TestCaseInfo* raw_info)
        : handle(h), info_owner(raw_info) {}
};

// Since TestCaseHandle stores a raw pointer to TestCaseInfo, this helper gives us ownership.
static OwnedTestCase makeOwnedTestCase(
    const std::string& test_name,
    Catch::ITestInvoker* invoker
) {
    Catch::NameAndTags nt;
    nt.name = test_name;
    nt.tags = "";

    Catch::SourceLineInfo sli{ __FILE__, static_cast<std::size_t>(__LINE__) };
    auto* info_raw = new Catch::TestCaseInfo(Catch::StringRef(), nt, sli);
    Catch::TestCaseHandle h(info_raw, invoker);
    return OwnedTestCase(h, info_raw);
}

class RunContext_GetCurrentTestName_508 : public ::testing::Test {
protected:
    // Basic fixture wires up a RunContext with a stub config and a no-op reporter.
    std::unique_ptr<StubConfig> config_;
    std::unique_ptr<NoopEventListener> listener_;
    std::unique_ptr<Catch::RunContext> ctx_;

    void SetUp() override {
        config_   = std::make_unique<StubConfig>();
        listener_ = std::make_unique<NoopEventListener>();

        // Move the reporter into RunContext (unique_ptr-like alias in Catch2)
        Catch::IEventListenerPtr reporter(listener_.release());

        ctx_ = std::make_unique<Catch::RunContext>(config_.get(), std::move(reporter));
    }
};

} // namespace

// ------------------------
// Tests
// ------------------------

TEST_F(RunContext_GetCurrentTestName_508, ReturnsEmptyWhenNoActiveTest_508) {
    // No test has been started, so getCurrentTestName should be empty.
    EXPECT_TRUE(ctx_->getCurrentTestName().empty());
}

TEST_F(RunContext_GetCurrentTestName_508, ReturnsActiveTestNameDuringInvocation_508) {
    // Arrange
    NiceMock<MockTestInvoker> invoker;
    std::string observed;

    // When the test body is invoked, query RunContext for the current name, and capture it.
    EXPECT_CALL(invoker, invoke())
        .WillOnce(Invoke([&](){
            observed = ctx_->getCurrentTestName();
        }));

    auto owned = makeOwnedTestCase("SampleCase_508", &invoker);

    // Act: run the test case (black-box), which should make it "active" during invocation
    ctx_->runTest(owned.handle);

    // Assert: while inside the test body, the observed name matches what we provided
    EXPECT_EQ(observed, "SampleCase_508");
}

TEST_F(RunContext_GetCurrentTestName_508, ReturnsEmptyAfterTestCompletes_508) {
    // Arrange
    NiceMock<MockTestInvoker> invoker;
    // Do nothing in the test body
    EXPECT_CALL(invoker, invoke()).WillOnce(Invoke([](){}));

    auto owned = makeOwnedTestCase("AnotherCase_508", &invoker);

    // Act
    ctx_->runTest(owned.handle);

    // Assert: After the test finishes, there should be no active test name.
    EXPECT_TRUE(ctx_->getCurrentTestName().empty());
}
