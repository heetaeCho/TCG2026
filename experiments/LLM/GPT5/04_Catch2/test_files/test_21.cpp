// unique_ptr_assign_cross_tests_21.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"

using Catch::Detail::unique_ptr;

// Helper types to observe deletion through public effects only
struct TrackBase {
    static int baseDtorCount;
    virtual ~TrackBase() { ++baseDtorCount; }
    virtual int v() const { return 0; }
};
int TrackBase::baseDtorCount = 0;

struct TrackDerived : TrackBase {
    static int derivedDtorCount;
    ~TrackDerived() override { ++derivedDtorCount; }
    int v() const override { return 42; }
};
int TrackDerived::derivedDtorCount = 0;

struct Unrelated {};

// --- Tests ---

// Compile-time availability check of the templated operator=
// Enabled only when U derives from T; otherwise it should be disabled via SFINAE.
TEST(UniquePtrAssign_21, SFINAE_OnlyForDerivedToBase_21) {
    // positive: unique_ptr<Base>& = unique_ptr<Derived>&&
    static_assert(std::is_assignable< unique_ptr<TrackBase>&,
                                      unique_ptr<TrackDerived>&& >::value,
                  "Derived->Base move assignment must be enabled");

    // negative: unique_ptr<Derived>& = unique_ptr<Base>&& (Base !<: Derived)
    static_assert(!std::is_assignable< unique_ptr<TrackDerived>&,
                                       unique_ptr<TrackBase>&& >::value,
                  "Base->Derived move assignment must be disabled");

    // negative: unique_ptr<Base>& = unique_ptr<Unrelated>&& (no relation)
    static_assert(!std::is_assignable< unique_ptr<TrackBase>&,
                                       unique_ptr<Unrelated>&& >::value,
                  "Unrelated types move assignment must be disabled");
    SUCCEED();
}

TEST(UniquePtrAssign_21, TransfersOwnershipAndNullsSource_21) {
    TrackBase::baseDtorCount = 0;
    TrackDerived::derivedDtorCount = 0;

    auto* raw_from = new TrackDerived();
    unique_ptr<TrackDerived> from(raw_from);

    unique_ptr<TrackBase> to(new TrackDerived());

    // Act
    auto* moved_addr = from.get();
    to = std::move(from);

    // Assert: destination now owns the original pointer
    EXPECT_EQ(to.get(), moved_addr);
    EXPECT_EQ(moved_addr, raw_from);

    // Source was released and became empty
    EXPECT_EQ(from.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(from));

    // Sanity: we can use the moved-into pointer polymorphically
    EXPECT_EQ(to->v(), 42);
}

TEST(UniquePtrAssign_21, DeletesPreviousTargetWhenOverwritten_21) {
    TrackBase::baseDtorCount = 0;
    TrackDerived::derivedDtorCount = 0;

    unique_ptr<TrackBase> to(new TrackDerived());   // old object A
    unique_ptr<TrackDerived> from(new TrackDerived()); // new object B

    // Act: assigning should destroy A (via reset) and move B
    to = std::move(from);

    // Immediately after assignment, A must have been destroyed exactly once.
    EXPECT_EQ(TrackDerived::derivedDtorCount, 1);
    EXPECT_EQ(TrackBase::baseDtorCount, 1);

    EXPECT_EQ(from.get(), nullptr);
    EXPECT_NE(to.get(), nullptr);
    EXPECT_EQ(to->v(), 42);
}

TEST(UniquePtrAssign_21, NoDeleteWhenTargetWasNull_21) {
    TrackBase::baseDtorCount = 0;
    TrackDerived::derivedDtorCount = 0;

    unique_ptr<TrackBase> to; // null
    unique_ptr<TrackDerived> from(new TrackDerived());

    to = std::move(from);

    // Since there was no previous target, no destruction should have occurred yet.
    EXPECT_EQ(TrackDerived::derivedDtorCount, 0);
    EXPECT_EQ(TrackBase::baseDtorCount, 0);

    EXPECT_EQ(from.get(), nullptr);
    ASSERT_NE(to.get(), nullptr);
    EXPECT_EQ(to->v(), 42);
}

TEST(UniquePtrAssign_21, ReturnsSelfReference_21) {
    unique_ptr<TrackBase> to(new TrackDerived());
    unique_ptr<TrackDerived> from(new TrackDerived());

    auto& ret = (to = std::move(from));

    // Return type and identity
    static_assert(std::is_same<decltype(ret), unique_ptr<TrackBase>&>::value,
                  "operator= should return lvalue ref to destination unique_ptr");
    EXPECT_EQ(&ret, &to);
}
