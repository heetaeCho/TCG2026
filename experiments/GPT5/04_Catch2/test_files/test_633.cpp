// File: tests/console_colour_make_impl_633_tests.cpp

#include <gtest/gtest.h>
#include <memory>
#include <ostream>
#include <sstream>

// Ensure deterministic behavior for non-Win32 builds in these tests
#ifdef CATCH_CONFIG_COLOUR_WIN32
#undef CATCH_CONFIG_COLOUR_WIN32
#endif

// ---- Headers from the provided interface ----
#include "catch2/internal/catch_istream.hpp"
#include "catch2/internal/catch_console_colour.cpp"          // for makeColourImpl + visible derived
#include "catch2/interfaces/catch_interfaces_config.hpp"

// Forward declare impls we need for RTTI checks (available via the included .cpp)
namespace Catch {
    class ColourImpl;
    class ANSIColourImpl;
    class NoColourImpl;
}

namespace {

// Minimal test double for Catch::IStream based ONLY on its interface.
class TestStream final : public Catch::IStream {
public:
    explicit TestStream(bool isConsole = false)
        : is_console_(isConsole)
    {}

    ~TestStream() override = default;

    std::ostream& stream() override {
        return oss_;
    }

    bool isConsole() const override {
        return is_console_;
    }

private:
    bool is_console_;
    std::ostringstream oss_;
};

} // namespace


// ---------- Tests ----------

TEST(MakeColourImpl_633, ReturnsANSIImplWhenExplicitANSI_633) {
    TestStream s{/*isConsole=*/true};
    auto ptr = Catch::Detail::makeColourImpl(Catch::ColourMode::ANSI, &s);

    ASSERT_NE(ptr, nullptr) << "Expected a non-null impl for explicit ANSI mode.";
    // Verify it is the ANSI implementation through RTTI
    auto asAnsi = dynamic_cast<Catch::ANSIColourImpl*>(ptr.get());
    EXPECT_NE(asAnsi, nullptr) << "Explicit ANSI mode should return ANSIColourImpl.";
}

TEST(MakeColourImpl_633, ReturnsNoColourImplWhenExplicitNone_633) {
    TestStream s{/*isConsole=*/false};
    auto ptr = Catch::Detail::makeColourImpl(Catch::ColourMode::None, &s);

    ASSERT_NE(ptr, nullptr) << "Expected a non-null impl for explicit None mode.";
    // We do NOT rely on private internals; just verify it is NOT ANSI
    auto asAnsi = dynamic_cast<Catch::ANSIColourImpl*>(ptr.get());
    EXPECT_EQ(asAnsi, nullptr) << "None mode should not return ANSIColourImpl.";
    // Note: We intentionally do not assert on NoColourImpl concrete type to avoid
    // depending on unprovided headers/definitions.
}

TEST(MakeColourImpl_633, PlatformDefaultYieldsSomeImplementation_633) {
    // We do not assert which impl it is, only that a valid impl is produced.
    TestStream s{/*isConsole=*/true};
    auto ptr = Catch::Detail::makeColourImpl(Catch::ColourMode::PlatformDefault, &s);

    EXPECT_NE(ptr, nullptr) << "PlatformDefault must produce a valid colour implementation.";
    // Additionally, ensure it is either ANSI or non-ANSI, but definitely not null.
    // This test stays within observable behavior constraints without inferring internals.
}

TEST(MakeColourImpl_633, InvalidModeTriggersError_633) {
    TestStream s{/*isConsole=*/false};
    // Using an out-of-range enum value should reach the error path.
    auto bad = static_cast<Catch::ColourMode>(999);

    // We do not rely on the exact exception type thrown by CATCH_ERROR; we only
    // assert that an exception is thrown.
    EXPECT_ANY_THROW({
        (void)Catch::Detail::makeColourImpl(bad, &s);
    });
}
