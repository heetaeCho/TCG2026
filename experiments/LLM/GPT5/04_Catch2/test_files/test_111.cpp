// ReporterConfig_tests_111.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

//
// We only use the public interface and observable behavior.
// To avoid peeking into internals, we define the minimum
// collaborators/types needed for construction & interaction.
//

// Include the header that declares ReporterConfig and its deps.
// If your project uses a different include path, adjust accordingly.
#include "catch2/interfaces/catch_interfaces_reporter.hpp"

namespace Catch {

// Minimal stand-ins for external interfaces, used only as collaborators.
// We don't simulate any internal behavior.
struct IStream {
    virtual ~IStream() = default;
};
struct IConfig {
    virtual ~IConfig() = default;
};

// Provide a simple concrete IStream for ownership/identity checks.
struct TestStream final : IStream {};

// Define a ColourMode compatible with the header usage.
// If your real enum exists in the included header, this
// will already be defined and these lines can be removed.
#ifndef CATCH_COLOURMODE_DEFINED_FOR_TESTS
enum class ColourMode { None = 0, Auto = 1 };
#endif

} // namespace Catch

using namespace Catch;

class ReporterConfigTest_111 : public ::testing::Test {
protected:
    // Helper to build a config with typical valid inputs
    static ReporterConfig MakeConfig(
        const IConfig* cfg,
        Detail::unique_ptr<IStream> stream,
        ColourMode mode,
        std::map<std::string, std::string> opts
    ) {
        return ReporterConfig(cfg, std::move(stream), mode, std::move(opts));
    }
};

// -------- Normal operation --------

TEST_F(ReporterConfigTest_111, ConstructorAndAccessors_111) {
    // Arrange
    IConfig dummyCfg; // acts as external dependency
    auto raw = new TestStream();
    Detail::unique_ptr<IStream> stream(raw);
    std::map<std::string, std::string> opts{
        {"key1", "value1"},
        {"feature", "enabled"}
    };
    const ColourMode mode = ColourMode::Auto;

    // Act
    ReporterConfig rc = MakeConfig(&dummyCfg, std::move(stream), mode, opts);

    // Assert (observable behavior via public APIs)
    EXPECT_EQ(rc.fullConfig(), &dummyCfg);
    EXPECT_EQ(rc.colourMode(), mode);

    const auto& got = rc.customOptions();
    ASSERT_EQ(got.size(), 2u);
    EXPECT_EQ(got.at("key1"), "value1");
    EXPECT_EQ(got.at("feature"), "enabled");
}

TEST_F(ReporterConfigTest_111, TakeStream_RvalueTransfersOwnershipAndIdentity_111) {
    // Arrange
    IConfig dummyCfg;
    auto* raw = new TestStream(); // keep raw ptr so we can compare identity
    Detail::unique_ptr<IStream> stream(raw);

    ReporterConfig rc = MakeConfig(&dummyCfg, std::move(stream), ColourMode::None, {});

    // Act: rvalue-qualified API must be called on an rvalue
    Detail::unique_ptr<IStream> taken = std::move(rc).takeStream();

    // Assert
    ASSERT_TRUE(static_cast<bool>(taken)) << "takeStream should return a non-null unique_ptr";
    EXPECT_EQ(taken.get(), raw) << "Ownership and object identity should transfer intact";
}

// Move construction should preserve observable state in the destination.
TEST_F(ReporterConfigTest_111, MoveConstruction_PreservesState_111) {
    // Arrange
    IConfig cfg;
    auto* raw = new TestStream();
    Detail::unique_ptr<IStream> stream(raw);
    std::map<std::string, std::string> opts{{"a","1"},{"b","2"}};
    const ColourMode mode = ColourMode::Auto;

    ReporterConfig original = MakeConfig(&cfg, std::move(stream), mode, opts);

    // Act
    ReporterConfig movedTo = std::move(original);

    // Assert
    EXPECT_EQ(movedTo.fullConfig(), &cfg);
    EXPECT_EQ(movedTo.colourMode(), mode);
    const auto& got = movedTo.customOptions();
    ASSERT_EQ(got.size(), 2u);
    EXPECT_EQ(got.at("a"), "1");
    EXPECT_EQ(got.at("b"), "2");

    // And we can still successfully take the stream from the moved-to object
    auto taken = std::move(movedTo).takeStream();
    ASSERT_TRUE(static_cast<bool>(taken));
    EXPECT_EQ(taken.get(), raw);
}

// -------- Boundary / exceptional behavior (observable) --------

// If constructed with a null stream, the implementation asserts before returning.
// We verify this via a death test on the rvalue-qualified takeStream().
//
// Note: This requires asserts to be enabled (debug builds).
TEST_F(ReporterConfigTest_111, TakeStream_DeathWhenStreamIsNull_111) {
    IConfig cfg;
    Detail::unique_ptr<IStream> nullStream(nullptr);
    ReporterConfig rc = MakeConfig(&cfg, std::move(nullStream), ColourMode::None, {});

#if GTEST_HAS_DEATH_TEST
    // Expect any assertion failure; pattern kept generic for portability.
    EXPECT_DEATH({ (void)std::move(rc).takeStream(); }, "");
#else
    GTEST_SKIP() << "Death tests not supported on this platform/build.";
#endif
}

// -------- Constness / reference semantics (read-only) --------

TEST_F(ReporterConfigTest_111, CustomOptions_IsReadOnlyView_111) {
    IConfig cfg;
    Detail::unique_ptr<IStream> stream(new TestStream());
    std::map<std::string, std::string> opts{{"k","v"}};

    ReporterConfig rc = MakeConfig(&cfg, std::move(stream), ColourMode::None, opts);

    const auto& view = rc.customOptions();
    ASSERT_EQ(view.size(), 1u);
    EXPECT_EQ(view.at("k"), "v");

    // Compile-time check of constness (no runtime effect):
    // auto& nonConstRef = rc.customOptions(); // <- should not compile; returns const&
    // We don't attempt mutation, respecting const interface.
}
