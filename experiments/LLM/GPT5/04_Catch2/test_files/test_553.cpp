// File: tests/assertion_handler_allow_throws_553.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Headers from the provided interface
#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// If your project uses the usual Catch2 internals, these are typically available:
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_result_builder.hpp" // for ResultDisposition::Flags, etc.

using ::testing::Return;
using ::testing::StrictMock;

namespace {

// Minimal mock for IConfig that only overrides allowThrows()
// (Other virtuals are left to the real implementation; we do not rely on them.)
class MockConfig : public Catch::IConfig {
public:
    // In many Catch2 versions, allowThrows is logically const.
    // We mark it const here to align with typical signatures.
    MOCK_METHOD(bool, allowThrows, (), (const, override));
};

struct AssertionHandlerAllowThrowsTest_553 : public ::testing::Test {
    // Helper to create a valid AssertionHandler instance with dummy-yet-valid params.
    // We do not inspect or depend on its internals.
    static Catch::AssertionHandler makeHandler() {
        using namespace Catch;
        // Provide minimal, valid inputs expected by the constructor.
        // We avoid assumptions about semantics; these are simple placeholders.
        StringRef macroName{"TEST_MACRO"};
        SourceLineInfo lineInfo{__FILE__, static_cast<std::size_t>(__LINE__)};
        StringRef captured{"x"};
        auto disposition = ResultDisposition::Normal; // a common, harmless flag
        return AssertionHandler{macroName, lineInfo, captured, disposition};
    }

    // Helper to plug a config into the current mutable context through public API.
    static void setConfig(const Catch::IConfig* cfg) {
        Catch::getCurrentMutableContext().setConfig(cfg);
    }
};

} // namespace

// Normal operation: when IConfig::allowThrows() returns true, handler forwards and returns true.
TEST_F(AssertionHandlerAllowThrowsTest_553, ReturnsTrueWhenConfigAllows_553) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, allowThrows()).Times(1).WillOnce(Return(true));
    setConfig(&cfg);

    auto handler = makeHandler();
    EXPECT_TRUE(handler.allowThrows());
}

// Normal operation: when IConfig::allowThrows() returns false, handler forwards and returns false.
TEST_F(AssertionHandlerAllowThrowsTest_553, ReturnsFalseWhenConfigDisallows_553) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, allowThrows()).Times(1).WillOnce(Return(false));
    setConfig(&cfg);

    auto handler = makeHandler();
    EXPECT_FALSE(handler.allowThrows());
}

// Verification of external interaction: ensure the call is forwarded exactly once to the current config.
TEST_F(AssertionHandlerAllowThrowsTest_553, ForwardsExactlyOnceToCurrentConfig_553) {
    StrictMock<MockConfig> cfg;
    EXPECT_CALL(cfg, allowThrows()).Times(1).WillOnce(Return(true));
    setConfig(&cfg);

    auto handler = makeHandler();
    (void)handler.allowThrows(); // single call expected
}

// Boundary-ish observable behavior: if the current Context's config changes between calls,
// the handler should respect the *current* config (no caching).
TEST_F(AssertionHandlerAllowThrowsTest_553, ReflectsContextConfigChangesBetweenCalls_553) {
    StrictMock<MockConfig> cfg1;
    StrictMock<MockConfig> cfg2;

    {
        ::testing::InSequence seq; // order: first cfg1.allowThrows(), then cfg2.allowThrows()
        EXPECT_CALL(cfg1, allowThrows()).WillOnce(Return(true));
        EXPECT_CALL(cfg2, allowThrows()).WillOnce(Return(false));
    }

    setConfig(&cfg1);
    auto handler = makeHandler();

    // First call uses cfg1
    EXPECT_TRUE(handler.allowThrows());

    // Switch to cfg2 and call again; should now reflect the new config
    setConfig(&cfg2);
    EXPECT_FALSE(handler.allowThrows());
}
