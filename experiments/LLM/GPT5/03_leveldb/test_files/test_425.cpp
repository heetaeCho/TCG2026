// File: no_destructor_get_test_425.cc

#include "util/no_destructor.h"

#include <gtest/gtest.h>
#include <type_traits>
#include <cstdint>
#include <utility>

// ----- Compile-time interface checks (no runtime behavior) -----
static_assert(!std::is_copy_constructible<leveldb::NoDestructor<int>>::value,
              "NoDestructor should be non-copy-constructible");
static_assert(!std::is_copy_assignable<leveldb::NoDestructor<int>>::value,
              "NoDestructor should be non-copy-assignable");

// A simple type with state initialized via constructor.
struct Widget {
  explicit Widget(int x, const char* p) : value(x), ptr(p) {}
  int value;
  const char* ptr;
};

// A move-only type to verify perfect-forwarding of constructor args.
struct MoveOnly {
  explicit MoveOnly(int v) : value(v) {}
  MoveOnly(MoveOnly&&) = default;
  MoveOnly& operator=(MoveOnly&&) = default;
  MoveOnly(const MoveOnly&) = delete;
  MoveOnly& operator=(const MoveOnly&) = delete;

  int value;
};

// A type that records destructor calls (observable side-effect).
struct DtorProbe {
  static int dtor_count;
  explicit DtorProbe(int v) : value(v) {}
  ~DtorProbe() { ++dtor_count; }
  int value;
};
int DtorProbe::dtor_count = 0;

// -------------------------- Tests --------------------------

TEST(NoDestructorTest_425, ConstructAndGetReturnsValidPointer_425) {
  leveldb::NoDestructor<Widget> holder(42, "hello");
  Widget* w = holder.get();

  ASSERT_NE(w, nullptr);
  EXPECT_EQ(w->value, 42);
  EXPECT_STREQ(w->ptr, "hello");
}

TEST(NoDestructorTest_425, GetReturnsSamePointerOnMultipleCalls_425) {
  leveldb::NoDestructor<Widget> holder(7, "p");
  Widget* a = holder.get();
  Widget* b = holder.get();
  EXPECT_EQ(a, b);
}

TEST(NoDestructorTest_425, SupportsMoveOnlyType_425) {
  leveldb::NoDestructor<MoveOnly> holder(MoveOnly(99));
  MoveOnly* mo = holder.get();
  ASSERT_NE(mo, nullptr);
  EXPECT_EQ(mo->value, 99);
}

TEST(NoDestructorTest_425, AlignmentIsCorrect_425) {
  // Use a type with stricter-than-int alignment to make the check meaningful.
  struct alignas(16) Aligned {
    explicit Aligned(int v) : value(v) {}
    int value;
  };

  leveldb::NoDestructor<Aligned> holder(5);
  Aligned* ptr = holder.get();
  ASSERT_NE(ptr, nullptr);

  std::uintptr_t addr = reinterpret_cast<std::uintptr_t>(ptr);
  EXPECT_EQ(addr % alignof(Aligned), 0u);
}

TEST(NoDestructorTest_425, DestructorIsNotInvokedOnScopeExit_425) {
  DtorProbe::dtor_count = 0;

  {
    leveldb::NoDestructor<DtorProbe> holder(123);
    DtorProbe* p = holder.get();
    ASSERT_NE(p, nullptr);
    EXPECT_EQ(p->value, 123);
    // Intentionally do nothing else; leaving scope should not call DtorProbe::~DtorProbe
    // if NoDestructor truly suppresses destruction of the held instance.
  }

  // Observable behavior: if the held instance's destructor were called,
  // the counter would have incremented. We expect it to remain zero.
  EXPECT_EQ(DtorProbe::dtor_count, 0);
}
