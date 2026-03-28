// File: convert_into_string_tests_258.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// ---- Minimal public headers from the provided interface ----
namespace Catch {
    class StringRef {
    public:
        using size_type = std::size_t;
        constexpr StringRef() noexcept = default;
        constexpr StringRef(char const* rawChars, size_type size) noexcept
            : m_start(rawChars), m_size(size) {}
        // Convenience for tests
        explicit StringRef(char const* rawChars) noexcept
            : m_start(rawChars), m_size(std::strlen(rawChars)) {}

        constexpr char const* data() const noexcept { return m_start; }
        constexpr size_type size() const noexcept { return m_size; }

    private:
        char const* m_start = "";
        size_type m_size = 0;
    };

    class IConfig {
    public:
        virtual ~IConfig() = default;
        // Only the method we need to observe
        virtual bool showInvisibles() = 0;
    };

    class Context {
    public:
        constexpr IConfig const* getConfig() const { return m_config; }
        constexpr void setConfig(IConfig const* cfg) { m_config = cfg; }
    private:
        IConfig const* m_config = nullptr;
    };

    // Global (free) accessors as used by production code
    const Context& getCurrentContext();
    Context& getCurrentMutableContext();
}

// ---- SUT declaration from the provided snippet ----
namespace Catch { namespace Detail {
    std::string convertIntoString(Catch::StringRef string); // 1-arg overload (SUT)
}}

// -----------------------------------------------------------------------------
// NOTE: We provide a *test double* for the 2-arg overload that the SUT is
// documented to call. This is an external collaborator from the SUT’s POV.
// Its observable behavior encodes the bool so we can verify delegation.
// -----------------------------------------------------------------------------
namespace Catch { namespace Detail {
    std::string convertIntoString(Catch::StringRef s, bool show) {
        // Encode the flag into the result to observe exact value passed in.
        // We do NOT (and must not) reimplement the real logic.
        return std::string(show ? "SHOW:" : "HIDE:")
             + std::string(s.data(), s.size());
    }
}}

// -----------------------------------------------------------------------------
// Google Mock for IConfig: only the collaborator we need (showInvisibles).
// -----------------------------------------------------------------------------
class MockConfig_258 : public Catch::IConfig {
public:
    MOCK_METHOD(bool, showInvisibles, (), (override));
};

// -----------------------------------------------------------------------------
// A tiny in-memory “current context” so tests can control the dependency.
// In real builds these are provided by the library; for unit tests we provide
// trivial stand-ins to satisfy linking and allow controlled setup/teardown.
// -----------------------------------------------------------------------------
namespace {
    Catch::Context g_ctx_258;
}

namespace Catch {
    const Context& getCurrentContext() { return g_ctx_258; }
    Context& getCurrentMutableContext() { return g_ctx_258; }
}

// -----------------------------------------------------------------------------
// Test fixture that saves/restores the global context’s config pointer.
// -----------------------------------------------------------------------------
class ConvertIntoStringTest_258 : public ::testing::Test {
protected:
    void SetUp() override {
        original_ = Catch::getCurrentContext().getConfig();
    }
    void TearDown() override {
        Catch::getCurrentMutableContext().setConfig(original_);
    }
    const Catch::IConfig* original_ = nullptr;
};

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------

// Normal operation: when showInvisibles() == false, the SUT should delegate
// to the 2-arg overload with false (observable in the return string).
TEST_F(ConvertIntoStringTest_258, DelegatesWithFalseFlag_258) {
    using ::testing::Return;

    MockConfig_258 cfg;
    EXPECT_CALL(cfg, showInvisibles())
        .WillOnce(Return(false));

    Catch::getCurrentMutableContext().setConfig(&cfg);

    Catch::StringRef input("abc");
    const std::string out = Catch::Detail::convertIntoString(input);

    EXPECT_EQ(out, "HIDE:abc");
}

// Normal operation: when showInvisibles() == true, the SUT should delegate
// with true (observable in the return string).
TEST_F(ConvertIntoStringTest_258, DelegatesWithTrueFlag_258) {
    using ::testing::Return;

    MockConfig_258 cfg;
    EXPECT_CALL(cfg, showInvisibles())
        .WillOnce(Return(true));

    Catch::getCurrentMutableContext().setConfig(&cfg);

    Catch::StringRef input("xyz");
    const std::string out = Catch::Detail::convertIntoString(input);

    EXPECT_EQ(out, "SHOW:xyz");
}

// Boundary condition: empty StringRef should be forwarded intact while
// still reflecting the flag value.
TEST_F(ConvertIntoStringTest_258, HandlesEmptyStringRef_258) {
    using ::testing::Return;

    MockConfig_258 cfg;
    EXPECT_CALL(cfg, showInvisibles())
        .WillOnce(Return(false));

    Catch::getCurrentMutableContext().setConfig(&cfg);

    Catch::StringRef empty("", 0);
    const std::string out = Catch::Detail::convertIntoString(empty);

    EXPECT_EQ(out, "HIDE:");
}

// Interaction verification: multiple calls should query the current context
// each time (no caching). We return different values on subsequent calls and
// expect the output to follow.
TEST_F(ConvertIntoStringTest_258, UsesCurrentContextEachCall_258) {
    using ::testing::Return;

    MockConfig_258 cfg;
    // First call -> false, second call -> true
    EXPECT_CALL(cfg, showInvisibles())
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    Catch::getCurrentMutableContext().setConfig(&cfg);

    Catch::StringRef s1("one");
    Catch::StringRef s2("two");

    const std::string out1 = Catch::Detail::convertIntoString(s1);
    const std::string out2 = Catch::Detail::convertIntoString(s2);

    EXPECT_EQ(out1, "HIDE:one");
    EXPECT_EQ(out2, "SHOW:two");
}

// Defensive/exceptional observable behavior: if config is not set, the SUT
// would try to call through a null pointer in real code. We avoid causing a
// crash in unit tests; instead we ensure our tests do NOT rely on null config.
// This test documents that behavior by ensuring we require a config in place.
TEST_F(ConvertIntoStringTest_258, RequiresConfigIsSet_DocumentedBehavior_258) {
    // Arrange: ensure a config is present so the call is safe
    using ::testing::Return;
    MockConfig_258 cfg;
    EXPECT_CALL(cfg, showInvisibles()).WillOnce(Return(true));
    Catch::getCurrentMutableContext().setConfig(&cfg);

    // Act
    Catch::StringRef input("safe");
    const std::string out = Catch::Detail::convertIntoString(input);

    // Assert
    EXPECT_EQ(out, "SHOW:safe");
}
