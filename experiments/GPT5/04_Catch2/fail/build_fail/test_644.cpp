// tests/context_get_current_mutable_context_644.cpp
#include <gtest/gtest.h>

// Forward declare the needed Catch2 interfaces and functions based on the prompt.
// These are collaborators (pointer types only), so minimal stubs are sufficient.
namespace Catch {
    // External collaborators (we only store their pointers)
    struct IConfig { virtual ~IConfig() = default; };
    struct IResultCapture { virtual ~IResultCapture() = default; };

    // Context interface per provided header (partial, sufficient for tests)
    class Context {
    public:
        // Public API we will exercise (per prompt)
        void cleanUpContext();
        constexpr IResultCapture* getResultCapture() const;
        constexpr IConfig const* getConfig() const;
        constexpr void setResultCapture(IResultCapture* resultCapture);
        constexpr void setConfig(IConfig const* config);
    };

    // Free function under test per provided implementation
    Context& getCurrentMutableContext();
} // namespace Catch

using namespace Catch;

// ---- Test fixture ----
class ContextTest_644 : public ::testing::Test {
protected:
    // Ensure each test starts from a clean context state if the API allows it.
    void TearDown() override {
        // We can only use public API; avoid assumptions other than that
        // cleanUpContext() should leave the system in a state where
        // getCurrentMutableContext() remains usable again.
        getCurrentMutableContext().cleanUpContext();
    }
};

// 1) Basic: returns a valid reference and is idempotent within a "session"
TEST_F(ContextTest_644, GetCurrentMutableContext_ReturnsSameReferenceConsecutively_644) {
    Context& ctx1 = getCurrentMutableContext();
    Context& ctx2 = getCurrentMutableContext();

    // Observable properties:
    // - Both calls must succeed and refer to a (the) context object.
    // - Without intervening cleanup, repeated calls should be stable.
    EXPECT_EQ(&ctx1, &ctx2);
}

// 2) Initial state: config/result-capture pointers are null before any setters
TEST_F(ContextTest_644, InitialPointersAreNull_644) {
    Context& ctx = getCurrentMutableContext();

    // As per header defaults (m_config, m_resultCapture initialized to nullptr),
    // the observable getters should reflect null when nothing was set.
    EXPECT_EQ(ctx.getConfig(), nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// 3) Setters + getters: setting collaborators is reflected via getters
TEST_F(ContextTest_644, SetAndGetConfigAndResultCapture_644) {
    struct DummyConfig : IConfig {};
    struct DummyResult : IResultCapture {};
    DummyConfig cfg;
    DummyResult res;

    Context& ctx = getCurrentMutableContext();

    // Precondition: allow either null or pre-existing; we only assert *after* set
    ctx.setConfig(&cfg);
    ctx.setResultCapture(&res);

    EXPECT_EQ(ctx.getConfig(), &cfg);
    EXPECT_EQ(ctx.getResultCapture(), &res);

    // Overwrite with nullptr is also a valid observable scenario if supported
    ctx.setConfig(nullptr);
    ctx.setResultCapture(nullptr);
    EXPECT_EQ(ctx.getConfig(), nullptr);
    EXPECT_EQ(ctx.getResultCapture(), nullptr);
}

// 4) Cleanup: after cleanUpContext, the API remains usable and stable thereafter
TEST_F(ContextTest_644, CleanUpThenGetContext_IsUsableAndStable_644) {
    // Acquire a reference prior to cleanup (no assertions about identity after)
    Context& before = getCurrentMutableContext();
    (void)before; // silence unused in case identity is optimized away

    // Clean up via public API
    getCurrentMutableContext().cleanUpContext();

    // After cleanup, we should still be able to obtain a valid reference
    Context& after1 = getCurrentMutableContext();
    Context& after2 = getCurrentMutableContext();

    // Postcondition: returned references are stable across consecutive calls again
    EXPECT_EQ(&after1, &after2);
}

// 5) Set-after-cleanup: state does not "leak" across a cleanup boundary
TEST_F(ContextTest_644, StateDoesNotPersistAcrossCleanup_ForPointers_644) {
    struct DummyConfigA : IConfig {};
    struct DummyResultA : IResultCapture {};
    DummyConfigA cfgA;
    DummyResultA resA;

    Context& ctx1 = getCurrentMutableContext();
    ctx1.setConfig(&cfgA);
    ctx1.setResultCapture(&resA);

    EXPECT_EQ(ctx1.getConfig(), &cfgA);
    EXPECT_EQ(ctx1.getResultCapture(), &resA);

    // Cleanup should reset any stored collaborators to a neutral/initial state.
    getCurrentMutableContext().cleanUpContext();

    Context& ctx2 = getCurrentMutableContext();
    // Observable expectation: newly obtained context reports initial/null state.
    EXPECT_EQ(ctx2.getConfig(), nullptr);
    EXPECT_EQ(ctx2.getResultCapture(), nullptr);
}
