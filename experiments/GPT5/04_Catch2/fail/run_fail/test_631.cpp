// File: colour_guard_tests_631.cpp
#include <gtest/gtest.h>
#include <vector>
#include <ostream>
#include <sstream>

// Include the real headers from your project
// (Paths below follow the prompt; adjust include paths to your repo layout)
#include "catch2/internal/catch_console_colour.hpp"

namespace {

using Catch::ColourImpl;
using Catch::Colour;
using Catch::ColourImpl;

// Spy subclass to observe external interaction: calls to ColourImpl::use.
// We only verify that the guard invokes `use(Colour::None)` on destruction
// when engaged; we do not assert any other internal behavior.
class SpyColourImpl : public ColourImpl {
public:
    using ColourImpl::ColourImpl;

    // Record every colour code requested via `use`.
    mutable std::vector<Colour::Code> calls;

private:
    // Match the interface: Catch2 declares `use` as a virtual (private) function.
    // It is legal to override a private virtual in a derived class.
    // If your implementation's signature differs (e.g., not `const`), change the cv-qualifier here.
    void use(Colour::Code code) const override {
        calls.push_back(code);
    }
};

} // namespace

// ---------- Tests ----------

TEST(ColourGuardTest_631, DestructorDoesNotResetWhenNeverEngaged_631) {
    SpyColourImpl impl{/*IStream*=*/nullptr};
    {
        // Create guard but do NOT call engage(...).
        auto guard = impl.guardColour(Colour::Red);
        (void)guard; // unused in this scope
    }
    // Because guard was never engaged, its destructor must not reset colour.
    // i.e., no call to use(Colour::None)
    ASSERT_TRUE(impl.calls.empty());
}

TEST(ColourGuardTest_631, EngagedDestructorResetsToNone_631) {
    SpyColourImpl impl{/*IStream*=*/nullptr};
    {
        auto guard = impl.guardColour(Colour::Green);

        // Engage to activate the guard. We don't assert what it does internally;
        // we only assert that on destruction it resets to None.
        std::ostringstream os;
        guard.engage(os);
    }
    // The final observable effect of an engaged guard's destructor is a reset to None.
    ASSERT_FALSE(impl.calls.empty());
    EXPECT_EQ(impl.calls.back(), Colour::None);
}

TEST(ColourGuardTest_631, MoveConstructedGuardResetsOnlyOnce_631) {
    SpyColourImpl impl{/*IStream*=*/nullptr};
    size_t resets_before = 0;
    {
        // Create and engage original guard
        auto g1 = impl.guardColour(Colour::Yellow);
        std::ostringstream os;
        g1.engage(os);

        // Move-construct a new guard from g1
        auto g2 = std::move(g1);

        // End inner scope for g1 (moved-from). Its destructor should NOT reset.
        // We create an extra block to force g1's destructor to run now.
        {
            // nothing else
        }

        resets_before = impl.calls.size();
        // Now g2 goes out of scope at the end of this outer block.
    }
    // After g2 is destroyed, we should have exactly one additional call,
    // which must be reset to None.
    ASSERT_GE(impl.calls.size(), resets_before + 1);
    EXPECT_EQ(impl.calls.back(), Colour::None);

    // Optional stronger check: Count how many "None" resets happened and
    // ensure it is exactly 1 (i.e., not reset twice).
    size_t none_count = 0;
    for (auto c : impl.calls) if (c == Colour::None) ++none_count;
    EXPECT_EQ(none_count, 1u);
}

TEST(ColourGuardTest_631, MoveAssignedGuardResetsOnlyOnce_631) {
    SpyColourImpl impl{/*IStream*=*/nullptr};

    size_t none_count_before = 0;
    {
        auto gA = impl.guardColour(Colour::Blue);
        std::ostringstream os;
        gA.engage(os); // engaged guard

        auto gB = impl.guardColour(Colour::Red); // default-constructed, not engaged

        // Move-assign: after this, only the destination should be responsible
        // for resetting on destruction.
        gB = std::move(gA);

        // Let moved-from gA die first (end of this scope). It should NOT reset.
        none_count_before = std::count(impl.calls.begin(), impl.calls.end(), Colour::None);
        {
            // nothing else
        }

        // gB will die at the end of the outer scope below.
    }

    // Exactly one additional reset to None should have happened due to gB.
    size_t none_count_after = std::count(impl.calls.begin(), impl.calls.end(), Colour::None);
    EXPECT_EQ(none_count_after, none_count_before + 1);
    ASSERT_FALSE(impl.calls.empty());
    EXPECT_EQ(impl.calls.back(), Colour::None);
}

TEST(ColourGuardTest_631, EngageReturnsLvalueRef_AllowingChaining_631) {
    SpyColourImpl impl{/*IStream*=*/nullptr};
    auto guard = impl.guardColour(Colour::Cyan);
    std::ostringstream os;

    // Verify that engage(...) returns an lvalue reference to the same guard,
    // as specified by the interface (observable via address equality).
    auto* addr_before = std::addressof(guard);
    auto* addr_after = std::addressof(guard.engage(os));
    EXPECT_EQ(addr_before, addr_after);
}

