// File: result_value_base_value_tests_360.cpp

#include <gtest/gtest.h>
#include <string>
#include <type_traits>
#include <utility>

#if __has_include("Catch2/src/catch2/internal/catch_clara.hpp")
  #include "Catch2/src/catch2/internal/catch_clara.hpp"
#else
  #include "catch2/internal/catch_clara.hpp"
#endif

namespace CCD = Catch::Clara::Detail;

// Helper: expose only what we need via a thin derived wrapper.
// This does NOT re-implement any internal logic; it simply forwards to
// the existing protected constructors/operators to allow instantiation
// in tests and calls the public value() accessor.
template <typename T>
class TestResultValue : public CCD::ResultValueBase<T> {
  using Base = CCD::ResultValueBase<T>;
public:
  // Construct with a value (copy and move). We pass Ok so value() is valid.
  explicit TestResultValue(const T& v)
      : Base(CCD::ResultType::Ok, v) {}

  explicit TestResultValue(T&& v)
      : Base(CCD::ResultType::Ok, std::move(v)) {}

  // Forwarding copy/move ctors
  TestResultValue(const TestResultValue& other) : Base(other) {}
  TestResultValue(TestResultValue&& other) noexcept : Base(std::move(other)) {}

  // Expose assignment by forwarding to base's protected operator=
  TestResultValue& assignFrom(const TestResultValue& other) {
    Base::operator=(other);
    return *this;
  }
  TestResultValue& moveAssignFrom(TestResultValue&& other) noexcept {
    Base::operator=(std::move(other));
    return *this;
  }

  // Re-expose value() for clarity at call sites
  using Base::value;

  ~TestResultValue() override = default;
};

// ------------------------ Tests ------------------------

TEST(ResultValueBaseTest_360, ValueReturnsStoredConstRef_Int_360) {
  TestResultValue<int> rv(42);
  const int& ref = rv.value();

  EXPECT_EQ(ref, 42);                         // observable value equals input
  EXPECT_EQ(&ref, &rv.value());               // same address across calls (ref stability)
}

TEST(ResultValueBaseTest_360, ValueReturnsStoredConstRef_String_360) {
  TestResultValue<std::string> rv(std::string("hello world"));
  const std::string& ref = rv.value();

  EXPECT_EQ(ref, "hello world");
  EXPECT_EQ(&ref, &rv.value());               // address stable across calls
}

TEST(ResultValueBaseTest_360, ValueIsCallableOnConstObject_360) {
  const TestResultValue<int> rv(7);
  // Compile-time check: return type is "const T&"
  static_assert(std::is_same<decltype(rv.value()), const int&>::value,
                "value() must return const T&");
  EXPECT_EQ(rv.value(), 7);
}

TEST(ResultValueBaseTest_360, CopyConstructionPreservesValue_360) {
  TestResultValue<std::string> a(std::string("alpha"));
  TestResultValue<std::string> b(a);  // copy-construct

  EXPECT_EQ(b.value(), "alpha");
  // both independently expose the same observable value
  EXPECT_EQ(a.value(), b.value());
}

TEST(ResultValueBaseTest_360, MoveConstructionTransfersValue_360) {
  TestResultValue<std::string> a(std::string("bravo"));
  TestResultValue<std::string> b(std::move(a));  // move-construct

  // The moved-to instance must expose the original observable value.
  EXPECT_EQ(b.value(), "bravo");
  // We do not assert anything about 'a' after move (moved-from state is unspecified).
}

TEST(ResultValueBaseTest_360, CopyAssignmentReplacesValue_360) {
  TestResultValue<std::string> x(std::string("x"));
  TestResultValue<std::string> y(std::string("y"));

  x.assignFrom(y);  // forward to base's operator=

  EXPECT_EQ(x.value(), "y");
  EXPECT_EQ(y.value(), "y");
}

TEST(ResultValueBaseTest_360, MoveAssignmentReplacesValue_360) {
  TestResultValue<std::string> x(std::string("left"));
  TestResultValue<std::string> y(std::string("right"));

  x.moveAssignFrom(std::move(y));  // forward to base's operator=

  EXPECT_EQ(x.value(), "right");
  // No assertions about 'y' post-move.
}
