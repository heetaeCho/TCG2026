// File: tests/unique_ptr_deref_test.cpp

#include <gtest/gtest.h>
#include "Catch2/src/catch2/internal/catch_unique_ptr.hpp"
#include <type_traits>

namespace cd = Catch::Detail;

// Simple POD type to observe mutations through dereference
struct Box {
    int v;
};

// Polymorphic types to verify base-reference behavior
struct Base {
    virtual ~Base() = default;
    virtual int id() const { return 1; }
};
struct Derived : Base {
    int id() const override { return 2; }
};

// --- Tests ---

// Normal operation: dereferencing yields a reference to the pointee and allows mutation.
TEST(CatchUniquePtrTest_24, DerefReturnsReferenceAndAllowsMutation_24) {
    cd::unique_ptr<Box> p(new Box{42});
    Box& ref = *p;                   // operator* must return a reference to the pointee
    EXPECT_EQ(ref.v, 42);
    ref.v = 100;                     // mutate through the reference
    EXPECT_EQ(p->v, 100);            // observable via operator-> (public interface)
}

// Type property: operator* returns an lvalue reference (T&).
TEST(CatchUniquePtrTest_24, DerefReturnsLvalueReferenceType_24) {
    cd::unique_ptr<Box> p(new Box{7});
    static_assert(std::is_same<decltype(*p), Box&>::value, "operator* should return T&");
    // Also verify we can assign through the reference (no copy of pointer state assumed).
    (*p).v = 8;
    EXPECT_EQ(p->v, 8);
}

// Address identity: &(*p) must equal get(), i.e., operator* refers to the same object.
TEST(CatchUniquePtrTest_24, DerefReferenceHasSameAddressAsGet_24) {
    cd::unique_ptr<Box> p(new Box{1});
    Box& ref = *p;
    EXPECT_EQ(&ref, p.get());
}

// Polymorphism: dereferencing a base-typed unique_ptr that points to a derived object
// yields a Base& that still dispatches virtually.
TEST(CatchUniquePtrTest_24, DerefYieldsBaseRefFromDerivedObject_24) {
    cd::unique_ptr<Base> p(new Derived{});
    Base& b = *p;                    // should be a Base& to the Derived object
    EXPECT_EQ(b.id(), 2);            // virtual dispatch confirms correct underlying object
}

// Boundary / exceptional case: dereferencing a null pointer should fail an assertion in debug builds.
// In release builds (NDEBUG), behavior is undefined, so we skip the death test there.
#if !defined(NDEBUG)
TEST(CatchUniquePtrTest_24, DerefNullptrDiesInDebug_24) {
    cd::unique_ptr<Box> p(nullptr);
    // Expect a debug assertion / death on dereference. We don't rely on a specific message.
    ASSERT_DEATH(
        {
            // Cast to void to silence "value computed is not used".
            (void)*p;
        },
        ""); // empty regex: accept any death reason
}
#else
TEST(CatchUniquePtrTest_24, DerefNullptrUndefinedBehaviorRelease_Skipped_24) {
    GTEST_SKIP() << "Assertions disabled (NDEBUG defined); deref(nullptr) is undefined, skipping.";
}
#endif
