// ColourGuard operator<< tests (TEST_ID: 425)
#include <gtest/gtest.h>
#include <sstream>

// Use the real header from your build/include path.
// If your include root exposes <catch2/...>, prefer the angle-bracket form.
#include <catch2/internal/catch_console_colour.hpp>

namespace {

class ColourGuardTest_425 : public ::testing::Test {
protected:
    using Guard = Catch::ColourImpl::ColourGuard;

    // We do not depend on any specific enumerator; we just need a valid Code value.
    static Catch::Colour::Code ZeroCode() {
        return static_cast<Catch::Colour::Code>(0);
    }

    // Construct a guard with a null ColourImpl*. This must be safe from the interface
    // perspective; if the implementation treats null as "no colour", operator<</engage
    // should be no-ops on the stream.
    static Guard MakeNullGuard() {
        return Guard(ZeroCode(), /*colourImpl*/ nullptr);
    }
};

// Verifies that operator<< returns the same std::ostream reference (chainability)
// and does not throw for a guard constructed with a null impl.
TEST_F(ColourGuardTest_425, StreamInsertionReturnsSameStream_425) {
    auto guard = MakeNullGuard();
    std::ostringstream oss;
    const std::string before = oss.str();

    std::ostream* ret = &(oss << guard);
    EXPECT_EQ(ret, &oss);

    // With a null impl, engaging should be a no-op on the stream’s contents.
    EXPECT_EQ(oss.str(), before);
}

// Verifies that multiple insertions are chainable and safe.
TEST_F(ColourGuardTest_425, MultipleInsertionsAreChainable_425) {
    auto guard = MakeNullGuard();
    std::ostringstream oss;

    std::ostream* ret = &((oss << guard) << guard);
    EXPECT_EQ(ret, &oss);
}

// Verifies that engage(std::ostream&) returns *this (lvalue ref), enabling chaining
// via the object API. We do not assert on any internal state or side effects.
TEST_F(ColourGuardTest_425, EngageReturnsSelfReference_425) {
    auto guard = MakeNullGuard();
    std::ostringstream oss;
    auto& ref = guard.engage(oss);
    EXPECT_EQ(&ref, &guard);

    // For a null impl, engaging should not alter contents.
    EXPECT_TRUE(oss.str().empty());
}

// Verifies that move construction yields a usable guard for stream insertion.
// We do not depend on the moved-from state.
TEST_F(ColourGuardTest_425, MoveConstructionProducesUsableGuard_425) {
    auto original = MakeNullGuard();
    Catch::ColourImpl::ColourGuard moved(std::move(original));

    std::ostringstream oss;
    EXPECT_NO_THROW({
        std::ostream* ret = &(oss << moved);
        EXPECT_EQ(ret, &oss);
    });
}

// Verifies that move assignment returns *this and the resulting guard is usable.
// We only assert on the returned reference identity and insertion safety.
TEST_F(ColourGuardTest_425, MoveAssignmentReturnsSelfAndUsable_425) {
    auto src = MakeNullGuard();
    auto dst = MakeNullGuard();

    Catch::ColourImpl::ColourGuard* assignedPtr = &(dst = std::move(src));
    EXPECT_EQ(assignedPtr, &dst);

    std::ostringstream oss;
    EXPECT_NO_THROW({
        std::ostream* ret = &(oss << dst);
        EXPECT_EQ(ret, &oss);
    });
}

// Verifies that operator<< does not throw when the ColourImpl* is null.
// (Covers the exceptional/no-op path that should be observable at the interface.)
TEST_F(ColourGuardTest_425, InsertionWithNullImplDoesNotThrow_425) {
    auto guard = MakeNullGuard();
    std::ostringstream oss;
    EXPECT_NO_THROW({
        std::ostream* ret = &(oss << guard);
        EXPECT_EQ(ret, &oss);
    });
}

} // namespace
