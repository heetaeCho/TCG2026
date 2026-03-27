// File: context_tests_256.cpp
#include <gtest/gtest.h>

// Include the provided Catch2 header
// (path taken from the prompt; adjust include path in your build if needed)
#include "Catch2/src/catch2/internal/catch_context.hpp"

// We only use pointer identity; never dereference IConfig/IResultCapture.
// To avoid depending on their full definitions, we create dummy addresses.
namespace {
    // Returns a unique, stable pointer value for testing identity.
    template <typename T>
    T* UniquePtrTag(const void* tag_addr) {
        // We only pass pointer values through; never dereference inside CUT.
        return reinterpret_cast<T*>(const_cast<void*>(tag_addr));
    }
}

class ContextTest_256 : public ::testing::Test {
protected:
    void SetUp() override {
        // Start each test from a clean state (observable through the interface)
        // by cleaning up any previously created context.
        // We obtain a mutable context first (creating one if needed),
        // then call its cleanup.
        // This uses only public API.
        Catch::getCurrentContext(); // ensure context exists
        // Use mutable accessor; name per prompt's interface.
        Catch::getCurrentMutableContext().cleanUpContext();
    }

    void TearDown() override {
        // Ensure we leave no state behind between tests.
        Catch::getCurrentContext();
        Catch::getCurrentMutableContext().cleanUpContext();
    }
};

// 1) Creation semantics: getCurrentContext creates a singleton-like instance
TEST_F(ContextTest_256, GetCurrentContext_CreatesAndIsStable_256) {
    auto& ctx1 = Catch::getCurrentContext();
    auto& ctx2 = Catch::getCurrentContext();

    // Observable: repeated calls return the same object address
    EXPECT_EQ(&ctx1, &ctx2);
}

// 2) setConfig/getConfig round-trip with a non-null pointer
TEST_F(ContextTest_256, SetAndGetConfig_RoundTrip_256) {
    // Create a unique dummy address for IConfig const*
    int tag{};
    auto* cfg_ptr = UniquePtrTag<const Catch::IConfig>(&tag);

    Catch::getCurrentMutableContext().setConfig(cfg_ptr);

    auto* got = Catch::getCurrentContext().getConfig();
    EXPECT_EQ(got, cfg_ptr);
}

// 3) setConfig(nullptr) is observable as nullptr via getConfig
TEST_F(ContextTest_256, SetConfig_AllowsNull_256) {
    Catch::getCurrentMutableContext().setConfig(nullptr);
    EXPECT_EQ(Catch::getCurrentContext().getConfig(), nullptr);
}

// 4) setResultCapture/getResultCapture round-trip with a non-null pointer
TEST_F(ContextTest_256, SetAndGetResultCapture_RoundTrip_256) {
    int tag{};
    auto* rc_ptr = UniquePtrTag<Catch::IResultCapture>(&tag);

    Catch::getCurrentMutableContext().setResultCapture(rc_ptr);

    auto* got = Catch::getCurrentContext().getResultCapture();
    EXPECT_EQ(got, rc_ptr);
}

// 5) setResultCapture(nullptr) is observable as nullptr via getResultCapture
TEST_F(ContextTest_256, SetResultCapture_AllowsNull_256) {
    Catch::getCurrentMutableContext().setResultCapture(nullptr);
    EXPECT_EQ(Catch::getCurrentContext().getResultCapture(), nullptr);
}

// 6) cleanUpContext resets the global context instance and stored collaborators
TEST_F(ContextTest_256, CleanUpContext_ResetsInstanceAndCollaborators_256) {
    // Arrange: set both collaborators to unique, non-null pointers
    int cfg_tag{}, rc_tag{};
    auto* cfg_ptr = UniquePtrTag<const Catch::IConfig>(&cfg_tag);
    auto* rc_ptr  = UniquePtrTag<Catch::IResultCapture>(&rc_tag);

    auto& before_ctx = Catch::getCurrentMutableContext();
    before_ctx.setConfig(cfg_ptr);
    before_ctx.setResultCapture(rc_ptr);

    const auto* before_addr = &Catch::getCurrentContext();

    // Act: cleanup
    Catch::getCurrentMutableContext().cleanUpContext();

    // Assert: a new context instance is created lazily
    auto& after_ctx_const = Catch::getCurrentContext();
    EXPECT_NE(before_addr, &after_ctx_const) << "Expected a fresh context after cleanup";

    // And collaborators are reset (observable as nullptrs from public getters)
    EXPECT_EQ(after_ctx_const.getConfig(), nullptr);
    EXPECT_EQ(after_ctx_const.getResultCapture(), nullptr);
}

// 7) Post-cleanup, creation is again stable (idempotent)
TEST_F(ContextTest_256, GetCurrentContext_IsStableAfterCleanup_256) {
    Catch::getCurrentMutableContext().cleanUpContext();

    auto& c1 = Catch::getCurrentContext();
    auto& c2 = Catch::getCurrentContext();
    EXPECT_EQ(&c1, &c2);
}
