// FILE: tests/result_value_base_move_ctor_1063.cpp

#include <gtest/gtest.h>
#include <utility>
#include <type_traits>

// Include the real interface under test
#include <catch2/internal/catch_clara.hpp>

namespace {

// A movable/copyable value type that records observable copy/move operations.
struct MoveSpy {
    int id{0};

    // Global observable counters (static) to verify interactions.
    static int copies;
    static int moves;

    static void ResetCounters() {
        copies = 0;
        moves = 0;
    }

    MoveSpy() = default;
    explicit MoveSpy(int v) : id(v) {}

    // Copy semantics
    MoveSpy(const MoveSpy& other) : id(other.id) { ++copies; }
    MoveSpy& operator=(const MoveSpy& other) {
        if (this != &other) {
            id = other.id;
            ++copies;
        }
        return *this;
    }

    // Move semantics
    MoveSpy(MoveSpy&& other) noexcept : id(other.id) {
        ++moves;
        // we don't care about moved-from state beyond being valid
    }
    MoveSpy& operator=(MoveSpy&& other) noexcept {
        if (this != &other) {
            id = other.id;
            ++moves;
        }
        return *this;
    }
};
int MoveSpy::copies = 0;
int MoveSpy::moves  = 0;

// Expose a minimal, test-only façade that forwards to the protected interface
// without reimplementing any internal logic.
struct ExposedRVB : public Catch::Clara::Detail::ResultValueBase<MoveSpy> {
    using Base = Catch::Clara::Detail::ResultValueBase<MoveSpy>;
    using ResultType = Catch::Clara::Detail::ResultType;

    // Publish the relevant protected constructors for testing.
    explicit ExposedRVB(ResultType rt) : Base(rt) {}
    ExposedRVB(ResultType rt, const MoveSpy& v) : Base(rt, v) {}
    ExposedRVB(ResultType rt, MoveSpy&& v) : Base(rt, std::move(v)) {}

    // Publish the move ctor so we can invoke it directly
    ExposedRVB(ExposedRVB&& other) noexcept : Base(std::move(other)) {}

    // Publish the const& accessor for observable state
    const MoveSpy& value() const & { return Base::value(); }
};

} // namespace

// -------------------- Tests --------------------

class ResultValueBaseMoveCtorTest_1063 : public ::testing::Test {
protected:
    void SetUp() override { MoveSpy::ResetCounters(); }
};

// Normal operation: moving from an Ok result should move the contained value
TEST_F(ResultValueBaseMoveCtorTest_1063, MoveCtor_MovesValue_WhenOk_1063) {
    using ResultType = Catch::Clara::Detail::ResultType;

    MoveSpy seed{42};
    // Construct source as Ok via lvalue (copy), so later we can attribute
    // exactly one move to the move-construction under test.
    ExposedRVB src(ResultType::Ok, seed);
    MoveSpy::ResetCounters(); // isolate the move-ctor’s effect

    ExposedRVB dst(std::move(src)); // move-construct

    // Observable expectations: one move occurred; no copies required.
    EXPECT_EQ(MoveSpy::moves, 1) << "Move-constructing Ok should move the value";
    EXPECT_EQ(MoveSpy::copies, 0) << "Move-constructing should not copy the value";

    // And the moved-into object exposes the value with the original id
    EXPECT_EQ(dst.value().id, 42);
}

// Boundary/negative path: when not Ok (LogicError), moving should NOT move a value
TEST_F(ResultValueBaseMoveCtorTest_1063, MoveCtor_DoesNotMove_WhenLogicError_1063) {
    using ResultType = Catch::Clara::Detail::ResultType;

    ExposedRVB src(ResultType::LogicError);
    ExposedRVB dst(std::move(src));

    // No value to move => zero moves/copies observable at the T level
    EXPECT_EQ(MoveSpy::moves, 0);
    EXPECT_EQ(MoveSpy::copies, 0);
}

// Boundary/negative path: when not Ok (RuntimeError), moving should NOT move a value
TEST_F(ResultValueBaseMoveCtorTest_1063, MoveCtor_DoesNotMove_WhenRuntimeError_1063) {
    using ResultType = Catch::Clara::Detail::ResultType;

    ExposedRVB src(ResultType::RuntimeError);
    ExposedRVB dst(std::move(src));

    EXPECT_EQ(MoveSpy::moves, 0);
    EXPECT_EQ(MoveSpy::copies, 0);
}

// API surface check: value() returns a const reference (no copies/moves on access)
TEST_F(ResultValueBaseMoveCtorTest_1063, ValueAccessor_ReturnsConstRef_1063) {
    using ResultType = Catch::Clara::Detail::ResultType;

    const MoveSpy seed{7};
    const ExposedRVB ok(ResultType::Ok, seed);

    // type trait check (compile-time) — observable API contract
    static_assert(std::is_same<decltype(ok.value()), const MoveSpy&>::value,
                  "value() must return const MoveSpy&");

    // runtime: reading should not trigger copies/moves
    MoveSpy::ResetCounters();
    (void)ok.value().id; // observe without modifying
    EXPECT_EQ(MoveSpy::moves, 0);
    EXPECT_EQ(MoveSpy::copies, 0);
}

