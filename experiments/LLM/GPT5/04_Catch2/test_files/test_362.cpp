// File: result_value_base_move_assignment_362_test.cpp
#include <gtest/gtest.h>
#include <utility>

// Include the header where ResultValueBase / ResultType live.
// If your project layout differs, adjust this include accordingly.
#include "catch2/internal/catch_clara.hpp"

namespace ct = Catch::Clara::Detail;

// A tiny testable adapter that only exposes protected functionality.
// It does NOT access any private state or reimplement internals.
template <typename T>
struct TestableResult_362 : public ct::ResultValueBase<T> {
    using Base = ct::ResultValueBase<T>;
    using Base::value;         // expose value()
    using Base::operator=;     // expose move/copy assignment

    // Public "Ok" constructors that delegate to Base's protected ctors
    explicit TestableResult_362(const T& v) : Base(ct::ResultType::Ok, v) {}
    explicit TestableResult_362(T&& v) : Base(ct::ResultType::Ok, std::move(v)) {}

    // Factory for non-Ok states (so we can observe post-assignment via value())
    static TestableResult_362 LogicError() { return TestableResult_362(ct::ResultType::LogicError); }
    static TestableResult_362 RuntimeError() { return TestableResult_362(ct::ResultType::RuntimeError); }

private:
    // Pass-through to the Base's protected constructor that sets only the type
    explicit TestableResult_362(ct::ResultType t) : Base(t) {}
};

// ----------------------------- Tests ---------------------------------

// Normal operation: moving Ok -> Ok transfers observable value.
TEST(ResultValueBase_MoveAssign_362, MoveAssign_OkToOk_MovesValue_362) {
    TestableResult_362<int> lhs(1);
    TestableResult_362<int> rhs(99);

    lhs = std::move(rhs);  // calls Base::operator=(ResultValueBase&&)

    // Observable behavior: value() should now reflect the source's value.
    EXPECT_EQ(lhs.value(), 99);
}

// Boundary-ish case: destination starts in an error state, source is Ok.
// After move-assign, destination should behave as Ok and expose the moved value.
TEST(ResultValueBase_MoveAssign_362, MoveAssign_ErrorToOk_BecomesOkAndExposesValue_362) {
    auto lhs = TestableResult_362<int>::LogicError();
    TestableResult_362<int> rhs(123);

    lhs = std::move(rhs);

    // Observable behavior: value() should be accessible and equal to source value.
    EXPECT_EQ(lhs.value(), 123);
}

// Self move-assignment on an Ok object should not crash and should preserve observable value.
TEST(ResultValueBase_MoveAssign_362, SelfMoveAssign_Ok_PreservesValue_362) {
    TestableResult_362<std::string> s(std::string("hello"));

    // Explicit self move-assign. This should be safe and leave value observable & intact.
    s = std::move(s);

    EXPECT_EQ(s.value(), "hello");
}

// Move-assign with different value category (rvalue source).
TEST(ResultValueBase_MoveAssign_362, MoveAssign_FromRvalueSource_OkToOk_362) {
    TestableResult_362<std::string> lhs(std::string("lhs"));
    TestableResult_362<std::string> rhs(std::string("RIGHT"));

    lhs = std::move(rhs);

    EXPECT_EQ(lhs.value(), "RIGHT");
}

// Stress with a type that moves differently from copy (to exercise placement-new path),
// without asserting anything about the moved-from state (black-box constraint).
struct MoveOnly_362 {
    MoveOnly_362() = default;
    explicit MoveOnly_362(int v) : v(v) {}
    MoveOnly_362(const MoveOnly_362&) = delete;
    MoveOnly_362& operator=(const MoveOnly_362&) = delete;
    MoveOnly_362(MoveOnly_362&& other) noexcept : v(other.v) { other.v = -99999; }
    MoveOnly_362& operator=(MoveOnly_362&& other) noexcept {
        if (this != &other) { v = other.v; other.v = -99999; }
        return *this;
    }
    int v = 0;
};

TEST(ResultValueBase_MoveAssign_362, MoveAssign_WithMoveOnlyType_362) {
    TestableResult_362<MoveOnly_362> lhs(MoveOnly_362{1});
    TestableResult_362<MoveOnly_362> rhs(MoveOnly_362{777});

    lhs = std::move(rhs);

    // Observable: destination's value now reflects the source's content.
    EXPECT_EQ(lhs.value().v, 777);
    // We do NOT make any assertions about rhs (moved-from) per black-box constraints.
}
