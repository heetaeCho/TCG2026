// Optional_valueOr_tests_411.cpp
#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_optional.hpp"

using Catch::Optional;

// A tiny helper type to observe copies without touching Optional internals.
struct CopyMoveTracker {
    static int copies;

    int value;

    explicit CopyMoveTracker(int v = 0) : value(v) {}

    CopyMoveTracker(const CopyMoveTracker& other) : value(other.value) {
        ++copies;
    }

    CopyMoveTracker& operator=(const CopyMoveTracker&) = default;

    bool operator==(const CopyMoveTracker& rhs) const { return value == rhs.value; }
};
int CopyMoveTracker::copies = 0;

// ---------- Normal operation ----------

TEST(OptionalValueOrTest_411, EmptyReturnsDefault_411) {
    Optional<int> opt; // empty
    EXPECT_TRUE(opt.none());
    EXPECT_EQ(opt.valueOr(42), 42);
}

TEST(OptionalValueOrTest_411, PresentReturnsStoredValue_411) {
    Optional<int> opt(7);
    EXPECT_TRUE(opt.some());
    EXPECT_EQ(opt.valueOr(99), 7); // default ignored when value is present
}

TEST(OptionalValueOrTest_411, WorksWithStdString_411) {
    Optional<std::string> empty;
    std::string def = "default";
    EXPECT_EQ(empty.valueOr(def), "default");

    Optional<std::string> has("hello");
    std::string def2 = "unused";
    EXPECT_EQ(has.valueOr(def2), "hello");
}

// ---------- Boundary / type semantics ----------

TEST(OptionalValueOrTest_411, ConstOptionalCanCallValueOr_411) {
    const Optional<int> optConst(3);
    EXPECT_EQ(optConst.valueOr(1), 3);
}

TEST(OptionalValueOrTest_411, PreservesContainedValueAfterCall_411) {
    Optional<std::string> opt("abc");
    auto out = opt.valueOr(std::string("zzz"));
    EXPECT_EQ(out, "abc");
    // Verify the contained value is unchanged and still readable via public API
    EXPECT_EQ(*opt, "abc");
}

// This checks observable copy behavior: valueOr returns by value,
// so one copy should occur from the chosen branch (contained or default).
TEST(OptionalValueOrTest_411, CopiesOnceFromContainedWhenPresent_411) {
    CopyMoveTracker contained(5);
    Optional<CopyMoveTracker> opt(contained); // construction may copy; don't measure it
    CopyMoveTracker::copies = 0;

    CopyMoveTracker def(9); // lvalue default to avoid temporary-related copies
    auto out = opt.valueOr(def);

    EXPECT_EQ(out.value, 5);
    EXPECT_EQ(CopyMoveTracker::copies, 1); // one copy to produce the return value
}

TEST(OptionalValueOrTest_411, CopiesOnceFromDefaultWhenEmpty_411) {
    Optional<CopyMoveTracker> empty;
    CopyMoveTracker::copies = 0;

    CopyMoveTracker def(7);
    auto out = empty.valueOr(def);

    EXPECT_EQ(out.value, 7);
    EXPECT_EQ(CopyMoveTracker::copies, 1); // one copy from default to the return value
}

// ---------- Additional boundary values ----------

TEST(OptionalValueOrTest_411, HandlesZeroAndNegativeIntegers_411) {
    Optional<int> empty;
    EXPECT_EQ(empty.valueOr(0), 0);
    EXPECT_EQ(empty.valueOr(-123), -123);

    Optional<int> hasZero(0);
    EXPECT_EQ(hasZero.valueOr(-1), 0);

    Optional<int> hasNeg(-456);
    EXPECT_EQ(hasNeg.valueOr(999), -456);
}

