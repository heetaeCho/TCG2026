// File: tests/run_context_emplace_unscoped_message_507_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/catch_message.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>

using ::testing::NiceMock;
using ::testing::Return;

namespace Catch {

// Minimal mock for IConfig that RunContext ctor uses for _config->name()
class MockConfig : public IConfig {
public:
    MOCK_METHOD(StringRef, name, (), (const, override));

    // The real IConfig might have more virtuals; if so in your codebase,
    // keep these no-op defaults or extend with mocks as needed.
    // We provide sensible defaults to satisfy potential pure-virtuals.
    // If your IConfig already provides defaults, these will simply override.
    // ----- Common optional overrides with harmless defaults -----
    bool allowThrows() const override { return true; }
    bool showInvisibles() const override { return false; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    // Some Catch2 versions require this:
    // std::ostream& stream() const override { return std::cout; }
};

} // namespace Catch

namespace {

using namespace Catch;

struct RunContext_EmplaceUnscopedMessage_507 : ::testing::Test {
    NiceMock<MockConfig> cfg;

    // Helper to create SUT with a null reporter (allowed by interface)
    RunContext makeSUT() {
        ON_CALL(cfg, name()).WillByDefault(Return(StringRef("run-ctx-emplace-507")));
        IEventListenerPtr reporter; // null
        return RunContext(&cfg, std::move(reporter));
    }

    static MessageBuilder makeBuilder(StringRef macroName = StringRef("MSG"),
                                      ResultWas::OfType type = ResultWas::OfType::Info) {
        // Use real source info for observability (if later reported by other APIs)
        SourceLineInfo sli{ __FILE__, static_cast<std::size_t>(__LINE__) };
        return MessageBuilder(macroName, sli, type);
    }
};

// Normal operation: accepts a temporary MessageBuilder with streamed content and does not throw.
TEST_F(RunContext_EmplaceUnscopedMessage_507, EmplaceAcceptsTemporaryBuilder_NoThrow_507) {
    auto sut = makeSUT();

    EXPECT_NO_THROW({
        sut.emplaceUnscopedMessage( makeBuilder() << "hello world" );
    });
}

// Boundary: empty message (no streamed content) should also be accepted without throwing.
TEST_F(RunContext_EmplaceUnscopedMessage_507, EmplaceWithEmptyMessage_NoThrow_507) {
    auto sut = makeSUT();

    EXPECT_NO_THROW({
        sut.emplaceUnscopedMessage( makeBuilder(StringRef("EMPTY"), ResultWas::OfType::Info) );
    });
}

// Robustness: multiple unscoped messages in succession should be accepted without throwing.
TEST_F(RunContext_EmplaceUnscopedMessage_507, EmplaceMultipleMessages_NoThrow_507) {
    auto sut = makeSUT();

    EXPECT_NO_THROW({
        sut.emplaceUnscopedMessage( makeBuilder(StringRef("A"), ResultWas::OfType::Info) << "first" );
        sut.emplaceUnscopedMessage( makeBuilder(StringRef("B"), ResultWas::OfType::Warning) << "second" );
        sut.emplaceUnscopedMessage( makeBuilder(StringRef("C"), ResultWas::OfType::ExplicitFailure) << "third" );
    });
}

// API correctness: passing an rvalue after an explicit std::move should be valid and non-throwing.
TEST_F(RunContext_EmplaceUnscopedMessage_507, EmplaceWithExplicitMove_NoThrow_507) {
    auto sut = makeSUT();

    auto builder = makeBuilder(StringRef("MOVE"), ResultWas::OfType::Info);
    // attach some content before moving
    builder = std::move(builder) << "moved";
    EXPECT_NO_THROW({
        sut.emplaceUnscopedMessage( std::move(builder) );
    });
}

} // namespace
