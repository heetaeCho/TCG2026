// File: unique_ptr_tests_26.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

#include "catch2/internal/catch_unique_ptr.hpp"

using Catch::Detail::unique_ptr;

namespace {

// Helper type to observe destruction via external, test-visible counters.
struct Spy {
  static int ctor_count;
  static int dtor_count;

  int data;

  explicit Spy(int d = 0) : data(d) { ++ctor_count; }
  ~Spy() { ++dtor_count; }

  int inc() { return ++data; }

  // non-copyable to avoid accidental copies in tests
  Spy(const Spy&) = delete;
  Spy& operator=(const Spy&) = delete;
  Spy(Spy&&) = default;
  Spy& operator=(Spy&&) = default;
};

int Spy::ctor_count = 0;
int Spy::dtor_count = 0;

struct Base {
  virtual ~Base() = default;
  virtual int id() const { return 1; }
};
struct Derived : Base {
  int id() const override { return 2; }
};

} // namespace

// ---------- Construction & basic observers ----------

TEST(UniquePtrTest_26, DefaultConstructed_IsNull_26) {
  Spy::ctor_count = Spy::dtor_count = 0;

  unique_ptr<Spy> p;
  EXPECT_EQ(p.get(), nullptr);
  EXPECT_FALSE(static_cast<bool>(p));
  EXPECT_EQ(Spy::ctor_count, 0);
  EXPECT_EQ(Spy::dtor_count, 0);
}

TEST(UniquePtrTest_26, ConstructWithPointer_GetReturnsSame_26) {
  Spy::ctor_count = Spy::dtor_count = 0;

  Spy* raw = new Spy(42);
  {
    unique_ptr<Spy> p(raw);
    EXPECT_EQ(p.get(), raw);
    EXPECT_TRUE(static_cast<bool>(p));
  }
  // unique_ptr went out of scope and should delete the object
  EXPECT_EQ(Spy::dtor_count, 1);
}

TEST(UniquePtrTest_26, DereferenceAndArrowAccess_26) {
  Spy::ctor_count = Spy::dtor_count = 0;

  unique_ptr<Spy> p(new Spy(5));
  EXPECT_EQ((*p).data, 5);
  EXPECT_EQ(p->inc(), 6);
  EXPECT_EQ(p->data, 6);
}

// ---------- reset / release semantics ----------

TEST(UniquePtrTest_26, ResetDeletesOldAndTakesNew_26) {
  Spy::ctor_count = Spy::dtor_count = 0;

  {
    unique_ptr<Spy> p(new Spy(0));
    EXPECT_EQ(Spy::dtor_count, 0);

    p.reset(new Spy(1));          // old object should be deleted now
    EXPECT_EQ(Spy::dtor_count, 1);
    ASSERT_NE(p.get(), nullptr);
    EXPECT_EQ(p->data, 1);

    p.reset();                    // delete current, become null
    EXPECT_EQ(Spy::dtor_count, 2);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(p));
  }
  // No further deletions after scope end
  EXPECT_EQ(Spy::dtor_count, 2);
}

TEST(UniquePtrTest_26, ReleaseYieldsPointerAndDetaches_26) {
  Spy::ctor_count = Spy::dtor_count = 0;

  Spy* raw = nullptr;
  {
    unique_ptr<Spy> p(new Spy(7));
    raw = p.release();
    EXPECT_NE(raw, nullptr);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_FALSE(static_cast<bool>(p));
    // release does not delete
    EXPECT_EQ(Spy::dtor_count, 0);
  }
  // still not deleted since we hold raw
  EXPECT_EQ(Spy::dtor_count, 0);

  delete raw; // manual delete after release
  EXPECT_EQ(Spy::dtor_count, 1);
}

// ---------- move semantics ----------

TEST(UniquePtrTest_26, MoveConstructor_TransfersOwnership_26) {
  Spy::ctor_count = Spy::dtor_count = 0;

  Spy* raw = new Spy(3);
  {
    unique_ptr<Spy> a(raw);
    unique_ptr<Spy> b(std::move(a));

    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b.get(), raw);
    EXPECT_EQ(b->data, 3);
  }
  // b's destruction should delete the object exactly once
  EXPECT_EQ(Spy::dtor_count, 1);
}

TEST(UniquePtrTest_26, MoveAssignment_TransfersAndDeletesOld_26) {
  Spy::ctor_count = Spy::dtor_count = 0;

  Spy* first  = new Spy(1);
  Spy* second = new Spy(2);

  {
    unique_ptr<Spy> a(first);
    unique_ptr<Spy> b(second);

    // Assigning into b should delete its old pointee (second)
    b = std::move(a);

    EXPECT_EQ(Spy::dtor_count, 1); // 'second' deleted
    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b.get(), first);
    EXPECT_EQ(b->data, 1);
  }
  // 'first' deleted when b goes out of scope
  EXPECT_EQ(Spy::dtor_count, 2);
}

// ---------- cross-type (Derived -> Base) moves ----------

TEST(UniquePtrTest_26, TemplatedMoveConstructor_DerivedToBase_26) {
  unique_ptr<Derived> d(new Derived());
  unique_ptr<Base> b(std::move(d));
  EXPECT_EQ(d.get(), nullptr);
  ASSERT_NE(b.get(), nullptr);
  EXPECT_EQ(b->id(), 2);
}

TEST(UniquePtrTest_26, TemplatedMoveAssignment_DerivedToBase_26) {
  unique_ptr<Base> b;
  {
    unique_ptr<Derived> d(new Derived());
    b = std::move(d);
    EXPECT_EQ(d.get(), nullptr);
    ASSERT_NE(b.get(), nullptr);
  }
  EXPECT_EQ(b->id(), 2);
}

// ---------- type traits / disabled copy semantics ----------

TEST(UniquePtrTest_26, CopySemanticsAreDeleted_26) {
  // These reflect the interface constraints (copy operations are deleted).
  EXPECT_FALSE(std::is_copy_constructible< unique_ptr<Spy> >::value);
  EXPECT_FALSE(std::is_copy_assignable   < unique_ptr<Spy> >::value);
}

// Note: operator->() is declared noexcept in the interface. This is a compile-time
// property; we verify it without invoking implementation details.
TEST(UniquePtrTest_26, ArrowOperatorIsNoexcept_26) {
  // Unevaluated context via declval, result checked at runtime as a constexpr bool.
  constexpr bool kNoexceptArrow =
      noexcept(std::declval<unique_ptr<Spy>&>().operator->());
  EXPECT_TRUE(kNoexceptArrow);
}
