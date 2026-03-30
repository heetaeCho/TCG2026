// colour_impl_guard_colour_test.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Use the real header from your codebase
#include "catch2/internal/catch_console_colour.hpp"

namespace {

// A tiny helper to get at least one valid code value without assuming the enum layout.
// We only treat Colour::Code as an opaque token passed through the API.
static Catch::Colour::Code AnyValidCode() {
    // Prefer a widely-present code name if available; fall back to a zero-initialized value.
    // We intentionally do not assume semantics of the value.
#ifdef CATCH_CONFIG_COLOUR_CODE_WHITE
    return Catch::Colour::Code::White;
#elif defined(CATCH_CONFIG_COLOUR_CODE_NONE)
    return Catch::Colour::Code::None;
#else
    return static_cast<Catch::Colour::Code>(0);
#endif
}

// Fixture kept minimal: we don't inspect any internal state or side effects.
class ColourImplTest_629 : public ::testing::Test {
protected:
    // The constructor under test accepts an IStream*. We pass nullptr as an
    // error-ish/boundary case that should still be safely handled by the public API.
    Catch::ColourImpl* makeImplWithNullStream() {
        return new Catch::ColourImpl(nullptr);
    }
};

} // namespace

// --- Normal operation: guard can be created and held in a scope without throwing.
TEST_F(ColourImplTest_629, GuardCanBeCreatedAndDestroyed_NoThrow_629) {
    std::unique_ptr<Catch::ColourImpl> impl(makeImplWithNullStream());
    auto code = AnyValidCode();

    EXPECT_NO_THROW({
        auto guard = impl->guardColour(code);
        (void)guard; // silence unused warning; lifetime bound to scope
    });
}

// --- Normal operation: multiple sequential guards are fine.
TEST_F(ColourImplTest_629, MultipleSequentialGuards_NoThrow_629) {
    std::unique_ptr<Catch::ColourImpl> impl(makeImplWithNullStream());
    auto codeA = AnyValidCode();
    auto codeB = static_cast<Catch::Colour::Code>(
        static_cast<int>(AnyValidCode()) + 1 // different-ish token; still opaque
    );

    EXPECT_NO_THROW({
        auto g1 = impl->guardColour(codeA);
        (void)g1;
    });

    EXPECT_NO_THROW({
        auto g2 = impl->guardColour(codeB);
        (void)g2;
    });
}

// --- Normal operation: nested guards in the same scope do not throw.
TEST_F(ColourImplTest_629, NestedGuards_NoThrow_629) {
    std::unique_ptr<Catch::ColourImpl> impl(makeImplWithNullStream());
    auto outerCode = AnyValidCode();
    auto innerCode = static_cast<Catch::Colour::Code>(
        static_cast<int>(outerCode) + 2
    );

    EXPECT_NO_THROW({
        auto outer = impl->guardColour(outerCode);
        (void)outer;
        {
            auto inner = impl->guardColour(innerCode);
            (void)inner;
        }
    });
}

// --- Boundary-ish: constructing with nullptr stream should still allow guard usage via the public API.
TEST_F(ColourImplTest_629, NullStream_AllowsGuardCreation_NoThrow_629) {
    std::unique_ptr<Catch::ColourImpl> impl(makeImplWithNullStream());
    EXPECT_NO_THROW({
        auto guard = impl->guardColour(AnyValidCode());
        (void)guard;
    });
}

// --- Smoke: calling guardColour repeatedly with the same code is stable (idempotent usage pattern).
TEST_F(ColourImplTest_629, RepeatedSameCode_NoThrow_629) {
    std::unique_ptr<Catch::ColourImpl> impl(makeImplWithNullStream());
    auto code = AnyValidCode();

    EXPECT_NO_THROW({
        auto g1 = impl->guardColour(code);
        (void)g1;
    });

    EXPECT_NO_THROW({
        auto g2 = impl->guardColour(code);
        (void)g2;
    });
}

