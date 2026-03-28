// optional_tests_403.cpp
#include <gtest/gtest.h>
#include <string>
#include "catch2/internal/catch_optional.hpp"

namespace {

struct Tracker {
  // Simple observable type to detect (de)construction and method access
  static int alive;
  static int ctor;
  static int dtor;
  static int copyCtor;
  static int moveCtor;
  static int copyAssign;
  static int moveAssign;

  static void Reset() {
    alive = ctor = dtor = copyCtor = moveCtor = copyAssign = moveAssign = 0;
  }

  int v;

  Tracker() : v(0) { ++alive; ++ctor; }
  explicit Tracker(int x) : v(x) { ++alive; ++ctor; }

  Tracker(const Tracker& other) : v(other.v) { ++alive; ++copyCtor; }
  Tracker(Tracker&& other) noexcept : v(other.v) { ++alive; ++moveCtor; }

  Tracker& operator=(const Tracker& other) {
    if (this != &other) { v = other.v; ++copyAssign; }
    return *this;
  }
  Tracker& operator=(Tracker&& other) noexcept {
    if (this != &other) { v = other.v; ++moveAssign; }
    return *this;
  }

  ~Tracker() { --alive; ++dtor; }

  int get() const { return v; }
};

int Tracker::alive = 0;
int Tracker::ctor = 0;
int Tracker::dtor = 0;
int Tracker::copyCtor = 0;
int Tracker::moveCtor = 0;
int Tracker::copyAssign = 0;
int Tracker::moveAssign = 0;

struct OptionalTest_403 : ::testing::Test {
  void SetUp() override { Tracker::Reset(); }
};

} // namespace

// ---- Basic engagement semantics ----

TEST_F(OptionalTest_403, DefaultConstruct_IsEmpty_403) {
  Catch::Optional<int> o;
  EXPECT_FALSE(o);
  EXPECT_TRUE(o.none());
  EXPECT_FALSE(o.some());
}

TEST_F(OptionalTest_403, ValueConstruct_FromLValue_EngagedAndDereferenceable_403) {
  int x = 7;
  Catch::Optional<int> o(x);
  EXPECT_TRUE(o);
  EXPECT_TRUE(o.some());
  EXPECT_FALSE(o.none());
  EXPECT_EQ(*o, 7);
}

TEST_F(OptionalTest_403, ValueConstruct_FromRValue_EngagedAndArrowWorks_403) {
  Tracker t(42);  // lvalue to avoid temporary-lifetime noise later
  Catch::Optional<Tracker> o(t);
  ASSERT_TRUE(o);
  EXPECT_EQ(o->get(), 42);
  EXPECT_EQ((*o).get(), 42);
}

TEST_F(OptionalTest_403, ValueOr_UsesDefaultWhenEmpty_403) {
  Catch::Optional<int> o;
  EXPECT_EQ(o.valueOr(123), 123);
}

TEST_F(OptionalTest_403, ValueOr_ReturnsHeldValueWhenEngaged_403) {
  Catch::Optional<int> o(5);
  EXPECT_EQ(o.valueOr(123), 5);
}

// ---- reset() behavior (observable effects only) ----

TEST_F(OptionalTest_403, Reset_OnEmpty_NoCrashNoChange_403) {
  Catch::Optional<Tracker> o;
  EXPECT_FALSE(o);
  EXPECT_EQ(Tracker::alive, 0);
  o.reset(); // should be a no-op
  EXPECT_FALSE(o);
  EXPECT_EQ(Tracker::alive, 0);
}

TEST_F(OptionalTest_403, Reset_OnEngaged_DestroysContained_403) {
  Tracker a(1);                         // alive: 1 (a)
  {
    Catch::Optional<Tracker> o(a);      // alive: 2 (a + copy in optional)
    ASSERT_TRUE(o);
    EXPECT_EQ(Tracker::alive, 2);
    o.reset();                          // destroys contained value
    EXPECT_FALSE(o);
    EXPECT_EQ(Tracker::alive, 1);       // only 'a' remains
  }
  // leaving inner scope does not change 'a'
  EXPECT_EQ(Tracker::alive, 1);
}

// ---- Destructor of Optional destroys contained value ----

TEST_F(OptionalTest_403, Destructor_DestroysContainedValue_403) {
  Tracker a(1);                          // alive: 1
  {
    Catch::Optional<Tracker> o(a);       // alive: 2
    ASSERT_TRUE(o);
    EXPECT_EQ(Tracker::alive, 2);
  }                                      // o destroyed, contained Tracker destroyed
  EXPECT_EQ(Tracker::alive, 1);          // only 'a' remains alive
}

// ---- Copy and move construction (no assumptions about source after move) ----

TEST_F(OptionalTest_403, CopyConstruct_FromEmpty_ProducesEmpty_403) {
  Catch::Optional<int> src;
  Catch::Optional<int> dst(src);
  EXPECT_FALSE(dst);
}

TEST_F(OptionalTest_403, CopyConstruct_FromEngaged_CopiesValue_403) {
  Catch::Optional<int> src(33);
  Catch::Optional<int> dst(src);
  ASSERT_TRUE(dst);
  EXPECT_EQ(*dst, 33);
}

TEST_F(OptionalTest_403, MoveConstruct_FromEngaged_HasValue_403) {
  Catch::Optional<int> src(99);
  Catch::Optional<int> dst(std::move(src));
  ASSERT_TRUE(dst);
  EXPECT_EQ(*dst, 99);
  // Do NOT assert anything about src after move (treat as black box)
}

// ---- Assignment operators ----

TEST_F(OptionalTest_403, Assign_FromLValue_EngagesAndSetsValue_403) {
  Catch::Optional<int> o;
  int v = 4;
  o = v;
  ASSERT_TRUE(o);
  EXPECT_EQ(*o, 4);
}

TEST_F(OptionalTest_403, Assign_FromRValue_EngagesAndSetsValue_403) {
  Catch::Optional<std::string> o;
  o = std::string("hello");
  ASSERT_TRUE(o);
  EXPECT_EQ(*o, std::string("hello"));
}

TEST_F(OptionalTest_403, Assign_CopyFromOptional_403) {
  Catch::Optional<int> src(7);
  Catch::Optional<int> dst;
  dst = src;
  ASSERT_TRUE(dst);
  EXPECT_EQ(*dst, 7);
}

TEST_F(OptionalTest_403, Assign_MoveFromOptional_403) {
  Catch::Optional<std::string> src(std::string("foo"));
  Catch::Optional<std::string> dst;
  dst = std::move(src);
  ASSERT_TRUE(dst);
  EXPECT_EQ(*dst, std::string("foo"));
  // No assertions about src after move
}

// ---- Overwrite semantics: old value is destroyed ----

TEST_F(OptionalTest_403, Assign_NewValue_DestroysPreviousContained_403) {
  Tracker a(1);                          // alive: 1
  Tracker b(2);                          // alive: 2
  {
    Catch::Optional<Tracker> o(a);       // alive: 3 (a,b,o(a))
    ASSERT_TRUE(o);
    EXPECT_EQ(Tracker::alive, 3);

    o = b;                               // replace contained with copy of b
    // Net alive should remain 3: old contained destroyed (-1), new copy constructed (+1)
    EXPECT_EQ(Tracker::alive, 3);
  }
  // o out of scope, contained destroyed: alive -> 2 (a and b remain)
  EXPECT_EQ(Tracker::alive, 2);
}

