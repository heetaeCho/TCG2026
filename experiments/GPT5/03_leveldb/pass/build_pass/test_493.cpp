// File: no_destructor_test_493.cc
#include <gtest/gtest.h>
#include <cstdint>
#include <memory>
#include <string>
#include "util/no_destructor.h"

using leveldb::NoDestructor;

// ---------- Helpers used by tests (observable via public interface) ----------

struct DefaultConstructible493 {
  static inline int ctor_count = 0;
  DefaultConstructible493() { ++ctor_count; }
};

struct CtorArgsType493 {
  int a_;
  std::string b_;
  CtorArgsType493(int a, std::string b) : a_(a), b_(std::move(b)) {}
  int a() const { return a_; }
  const std::string& b() const { return b_; }
};

struct MoveOnlyArgType493 {
  std::unique_ptr<int> p_;
  explicit MoveOnlyArgType493(std::unique_ptr<int> p) : p_(std::move(p)) {}
  bool has_value() const { return static_cast<bool>(p_); }
  int value() const { return p_ ? *p_ : -1; }
};

struct DtorCounter493 {
  static inline int dtor_count = 0;
  ~DtorCounter493() { ++dtor_count; }
  // Provide some trivial API to keep it “observable”
  int x = 7;
};

struct alignas(64) BigAlign493 {
  int v = 123;
  int value() const { return v; }
};

// ------------------------------- Test Cases ---------------------------------

// [493] Basic default construction increments observable ctor counter.
TEST(NoDestructorTest_493, DefaultConstructionIncrementsCtorCount_493) {
  DefaultConstructible493::ctor_count = 0;
  {
    NoDestructor<DefaultConstructible493> holder;
    ASSERT_NE(holder.get(), nullptr);
    // Observable effect: the wrapped type’s constructor was called exactly once.
    EXPECT_EQ(DefaultConstructible493::ctor_count, 1);
  }
  // We do not make any assertion about destruction here (covered elsewhere).
}

// [493] Perfect-forwarding with multiple arguments constructs the instance correctly.
TEST(NoDestructorTest_493, ForwardsMultipleArgs_493) {
  NoDestructor<CtorArgsType493> holder(42, std::string("hello"));
  auto* obj = holder.get();
  ASSERT_NE(obj, nullptr);
  EXPECT_EQ(obj->a(), 42);
  EXPECT_EQ(obj->b(), "hello");
}

// [493] Perfect-forwarding of move-only argument (e.g., std::unique_ptr) works.
TEST(NoDestructorTest_493, ForwardsMoveOnlyArg_493) {
  auto up = std::make_unique<int>(1234);
  NoDestructor<MoveOnlyArgType493> holder(std::move(up));

  // After move, original unique_ptr should be empty (observable move semantics).
  EXPECT_EQ(up.get(), nullptr);

  auto* obj = holder.get();
  ASSERT_NE(obj, nullptr);
  EXPECT_TRUE(obj->has_value());
  EXPECT_EQ(obj->value(), 1234);
}

// [493] get() returns a stable, non-null pointer across calls.
TEST(NoDestructorTest_493, GetReturnsStableNonNull_493) {
  NoDestructor<CtorArgsType493> holder(7, "x");
  CtorArgsType493* p1 = holder.get();
  ASSERT_NE(p1, nullptr);
  CtorArgsType493* p2 = holder.get();
  ASSERT_NE(p2, nullptr);
  EXPECT_EQ(p1, p2);  // Pointer identity should be stable.
  EXPECT_EQ(p1->a(), 7);
  EXPECT_EQ(p1->b(), "x");
}

// [493] The wrapped instance’s destructor is not invoked when the wrapper goes out of scope.
// (Observable via a type whose destructor increments a counter.)
TEST(NoDestructorTest_493, DoesNotCallWrappedDestructorOnScopeExit_493) {
  DtorCounter493::dtor_count = 0;
  {
    NoDestructor<DtorCounter493> holder;
    ASSERT_NE(holder.get(), nullptr);
    EXPECT_EQ(holder.get()->x, 7);  // sanity use
  }
  // If NoDestructor truly avoids destroying the contained instance,
  // the wrapped destructor counter should remain zero.
  EXPECT_EQ(DtorCounter493::dtor_count, 0);
}

// [493] The stored instance satisfies the alignment requirement (pointer address aligned).
TEST(NoDestructorTest_493, ProperAlignment_493) {
  NoDestructor<BigAlign493> holder;
  BigAlign493* p = holder.get();
  ASSERT_NE(p, nullptr);

  std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(p);
  EXPECT_EQ(addr % alignof(BigAlign493), 0u) << "Instance pointer is not properly aligned";
  EXPECT_EQ(p->value(), 123);  // basic sanity check
}
