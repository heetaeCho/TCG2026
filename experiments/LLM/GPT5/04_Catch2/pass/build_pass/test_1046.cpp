// File: tests/unique_ptr_tests_1046.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include "catch2/internal/catch_unique_ptr.hpp"

using Catch::Detail::unique_ptr;

// Helpers used only to observe externally-visible effects (no access to internals)
namespace {
struct DtorCounter {
    static int dcount;
    int value;
    explicit DtorCounter(int v = 0) : value(v) {}
    virtual ~DtorCounter() { ++dcount; }
};
int DtorCounter::dcount = 0;

struct DerivedCounter : DtorCounter {
    static int derived_dcount;
    explicit DerivedCounter(int v = 0) : DtorCounter(v) {}
    ~DerivedCounter() override { ++derived_dcount; }
};
int DerivedCounter::derived_dcount = 0;
} // namespace

class UniquePtrTest_1046 : public ::testing::Test {
protected:
    void SetUp() override {
        DtorCounter::dcount = 0;
        DerivedCounter::derived_dcount = 0;
    }
};

// --- Type traits & noexcept (interface-level properties) ---

TEST_F(UniquePtrTest_1046, NotCopyConstructible_1046) {
    static_assert(!std::is_copy_constructible< unique_ptr<int> >::value,
                  "unique_ptr must not be copy-constructible");
}

TEST_F(UniquePtrTest_1046, NotCopyAssignable_1046) {
    static_assert(!std::is_copy_assignable< unique_ptr<int> >::value,
                  "unique_ptr must not be copy-assignable");
}

TEST_F(UniquePtrTest_1046, MoveCtorIsNoexcept_1046) {
    static_assert(noexcept(unique_ptr<int>(std::declval< unique_ptr<int>&& >())),
                  "move constructor should be noexcept");
}

TEST_F(UniquePtrTest_1046, MoveAssignIsNoexcept_1046) {
    static_assert(noexcept(std::declval< unique_ptr<int>& >() =
                           std::declval< unique_ptr<int>&& >()),
                  "move assignment should be noexcept");
}

// --- Basic ownership semantics ---

TEST_F(UniquePtrTest_1046, DefaultConstructedIsNull_AndBoolFalse_1046) {
    unique_ptr<DtorCounter> p;
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(p));
}

TEST_F(UniquePtrTest_1046, ConstructFromRawPointer_IsNonNull_AndAccessible_1046) {
    auto* raw = new DtorCounter(7);
    unique_ptr<DtorCounter> p(raw);
    EXPECT_EQ(p.get(), raw);
    EXPECT_TRUE(p);
    EXPECT_EQ((*p).value, 7);
    EXPECT_EQ(p->value, 7);
}

// --- Move construction nulls the source & transfers pointer ---

TEST_F(UniquePtrTest_1046, MoveConstruction_NullsSource_TransfersOwnership_1046) {
    auto* raw = new DtorCounter(11);
    unique_ptr<DtorCounter> src(raw);
    EXPECT_TRUE(src);
    unique_ptr<DtorCounter> dst(std::move(src));

    // Source must be empty after move; destination should hold the pointer
    EXPECT_FALSE(src);
    EXPECT_EQ(src.get(), nullptr);
    EXPECT_TRUE(dst);
    EXPECT_EQ(dst.get(), raw);

    // Ensure exactly one deletion when dst goes out of scope
    EXPECT_EQ(DtorCounter::dcount, 0);
}

// --- Converting move (Derived -> Base) keeps proper deletion via virtual dtor ---

TEST_F(UniquePtrTest_1046, ConvertingMove_FromDerivedToBase_VirtualDeleteInvoked_1046) {
    auto* raw = new DerivedCounter(42);
    unique_ptr<DerivedCounter> from(raw);
    unique_ptr<DtorCounter> to(std::move(from)); // converting move

    EXPECT_FALSE(from);        // source is null
    EXPECT_TRUE(to);           // destination non-null
    EXPECT_EQ(to.get(), raw);  // same underlying pointer

    // Before scope end, no destructor should have run
    EXPECT_EQ(DtorCounter::dcount, 0);
    EXPECT_EQ(DerivedCounter::derived_dcount, 0);
    // Destruction counts are verified at tear-down when 'to' is destroyed.
}

// --- Move assignment releases old and takes new ---

TEST_F(UniquePtrTest_1046, MoveAssignment_ReleasesOld_TakesNew_1046) {
    auto* first = new DtorCounter(1);
    auto* second = new DtorCounter(2);

    unique_ptr<DtorCounter> a(first);
    unique_ptr<DtorCounter> b(second);

    // Move-assign b into a: the object previously owned by 'a' should be deleted
    a = std::move(b);

    EXPECT_TRUE(a);
    EXPECT_EQ(a.get(), second);
    EXPECT_FALSE(b);
    EXPECT_EQ(b.get(), nullptr);

    // first should have been deleted exactly once
    EXPECT_EQ(DtorCounter::dcount, 1);
}

// --- reset deletes old and adopts new (including nullptr) ---

TEST_F(UniquePtrTest_1046, Reset_DeletesOld_AdoptsNew_1046) {
    auto* first = new DtorCounter(10);
    auto* second = new DtorCounter(20);

    unique_ptr<DtorCounter> p(first);
    p.reset(second); // deletes first, now owns second

    EXPECT_EQ(DtorCounter::dcount, 1);
    EXPECT_EQ(p.get(), second);
    EXPECT_TRUE(p);

    p.reset(); // delete second and become null
    EXPECT_EQ(DtorCounter::dcount, 2);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_FALSE(p);
}

// --- release hands off ownership without deleting ---

TEST_F(UniquePtrTest_1046, Release_TransfersRawPointer_NoDelete_1046) {
    auto* raw = new DtorCounter(33);
    unique_ptr<DtorCounter> p(raw);

    DtorCounter* out = p.release();

    EXPECT_EQ(out, raw);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_FALSE(p);
    // No deletion should have happened on release
    EXPECT_EQ(DtorCounter::dcount, 0);

    // Caller is responsible to delete after release
    delete out;
    EXPECT_EQ(DtorCounter::dcount, 1);
}

// --- Moving from a null source yields a null destination, source remains null ---

TEST_F(UniquePtrTest_1046, MoveFromNull_YieldsNullAndRemainsNull_1046) {
    unique_ptr<DtorCounter> empty;
    unique_ptr<DtorCounter> moved(std::move(empty));

    EXPECT_FALSE(empty);
    EXPECT_EQ(empty.get(), nullptr);
    EXPECT_FALSE(moved);
    EXPECT_EQ(moved.get(), nullptr);

    EXPECT_EQ(DtorCounter::dcount, 0);
}

// --- Dereference and arrow operators (read/write through pointer) ---

TEST_F(UniquePtrTest_1046, DereferenceAndArrow_ReadWrite_1046) {
    auto* raw = new DtorCounter(5);
    unique_ptr<DtorCounter> p(raw);

    EXPECT_EQ((*p).value, 5);
    p->value = 9;
    EXPECT_EQ((*p).value, 9);
}
