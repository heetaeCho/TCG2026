// File: run_context_handleMessage_tests_516.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use the interfaces as presented in the prompt.
#include "Catch2/src/catch2/internal/catch_run_context.hpp"
#include "Catch2/src/catch2/internal/catch_assertion_handler.hpp"
#include "Catch2/src/catch2/catch_assertion_info.hpp"
#include "Catch2/src/catch2/catch_assertion_result.hpp"
#include "Catch2/src/catch2/internal/catch_result_type.hpp"

using ::testing::NiceMock;

namespace {

// Minimal stubs to construct RunContext safely, keeping to the interface.
// These match the usage seen in the provided RunContext constructor
// (only _config->name() is required there).

struct DummyConfig : public Catch::IConfig {
    // Provide only what's needed/used by RunContext in the snippet: name()
    Catch::StringRef name() const override { return Catch::StringRef("DummyConfig"); }

    // --- The rest of IConfig's interface is not used by this test path.
    // Provide benign defaults to satisfy linkage/abstractness if needed.
    // If your environment's IConfig has additional pure virtuals, add trivial
    // overrides here that return safe defaults.
};

struct DummyEventListener : public Catch::IEventListener {
    // Provide no-op implementations to avoid nullptr deref inside RunContext flows.
    // If your environment’s IEventListener has additional pure virtuals,
    // add empty overrides here.
};

struct RunContextHandleMessageTest_516 : public ::testing::Test {
    std::unique_ptr<DummyConfig>           cfg;
    Catch::IEventListenerPtr               reporter;
    std::unique_ptr<Catch::RunContext>     ctx;

    void SetUp() override {
        cfg = std::make_unique<DummyConfig>();
        reporter = Catch::IEventListenerPtr(new DummyEventListener());
        ctx = std::make_unique<Catch::RunContext>(cfg.get(), std::move(reporter));
    }

    static Catch::AssertionInfo makeInfo(const char* macro = "REQUIRE", const char* expr = "true") {
        Catch::AssertionInfo info;
        info.macroName = Catch::StringRef(macro);
        info.capturedExpression = Catch::StringRef(expr);
        info.resultDisposition = static_cast<Catch::ResultDisposition::Flags>(0);
        return info;
    }
};

} // namespace

// --- Tests ---

// ExplicitSkip should set reaction.shouldSkip = true, and last result should carry the message/type.
TEST_F(RunContextHandleMessageTest_516, HandleMessage_SetsSkipOnExplicitSkip_516) {
    Catch::AssertionReaction reaction{};
    auto info = makeInfo("INFO", "skip message");
    std::string msg = "skipping this on purpose";

    ctx->handleMessage(info, Catch::ResultWas::ExplicitSkip, std::move(msg), reaction);

    EXPECT_TRUE(reaction.shouldSkip);

    // Verify observable last-result surface
    auto last = ctx->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::ExplicitSkip);
    EXPECT_TRUE(last->hasMessage());
    EXPECT_EQ(std::string(last->getMessage()), "skipping this on purpose");
    EXPECT_EQ(std::string(last->getTestMacroName()), "INFO");
}

// Non-OK result should NOT set shouldSkip (populateReaction may set other fields, which we do not assert).
TEST_F(RunContextHandleMessageTest_516, HandleMessage_DoesNotSetSkipOnFailure_516) {
    Catch::AssertionReaction reaction{};
    auto info = makeInfo("REQUIRE", "1 == 2");
    std::string msg = "expression failed";

    ctx->handleMessage(info, Catch::ResultWas::ExpressionFailed, std::move(msg), reaction);

    EXPECT_FALSE(reaction.shouldSkip);

    // Verify observable last-result surface
    auto last = ctx->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::ExpressionFailed);
    EXPECT_TRUE(last->hasMessage());
    EXPECT_EQ(std::string(last->getMessage()), "expression failed");
    EXPECT_EQ(std::string(last->getTestMacroName()), "REQUIRE");
}

// OK result with a message should not set shouldSkip (only ExplicitSkip does).
TEST_F(RunContextHandleMessageTest_516, HandleMessage_OkDoesNotSetSkip_516) {
    Catch::AssertionReaction reaction{};
    auto info = makeInfo("CHECK", "true");
    std::string msg = "all good";

    ctx->handleMessage(info, Catch::ResultWas::Ok, std::move(msg), reaction);

    EXPECT_FALSE(reaction.shouldSkip);

    auto last = ctx->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::Ok);
    EXPECT_TRUE(last->hasMessage());
    EXPECT_EQ(std::string(last->getMessage()), "all good");
    EXPECT_EQ(std::string(last->getTestMacroName()), "CHECK");
}

// Warning/Info are generally OK results; confirm they do not set skip.
TEST_F(RunContextHandleMessageTest_516, HandleMessage_InfoDoesNotSetSkip_516) {
    Catch::AssertionReaction reaction{};
    auto info = makeInfo("INFO", "note");
    std::string msg = "this is just info";

    ctx->handleMessage(info, Catch::ResultWas::Info, std::move(msg), reaction);

    EXPECT_FALSE(reaction.shouldSkip);

    auto last = ctx->getLastResult();
    ASSERT_NE(last, nullptr);
    EXPECT_EQ(last->getResultType(), Catch::ResultWas::Info);
    EXPECT_TRUE(last->hasMessage());
    EXPECT_EQ(std::string(last->getMessage()), "this is just info");
    EXPECT_EQ(std::string(last->getTestMacroName()), "INFO");
}
