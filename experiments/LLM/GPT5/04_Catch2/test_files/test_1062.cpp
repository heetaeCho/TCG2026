// File: tests/result_value_base_copy_tests_1062.cpp

#include <gtest/gtest.h>
#include <stdexcept>
#include <type_traits>

// Include your project header that defines ResultValueBase & ResultType.
#include "catch2/internal/catch_clara.hpp"

// ---------------------------
// Test-only helper wrappers
// ---------------------------

namespace test_helpers {

template <typename T>
struct ExposedResultValue : Catch::Clara::Detail::ResultValueBase<T> {
    using Base       = Catch::Clara::Detail::ResultValueBase<T>;
    using ResultType = Catch::Clara::Detail::ResultType;

    // Expose selected Base constructors as public forwarding c'tors
    explicit ExposedResultValue(ResultType type)
        : Base(type) {}

    ExposedResultValue(ResultType /*ignored*/, const T& v)
        : Base(ResultType::Ok, v) {}

    ExposedResultValue(ResultType /*ignored*/, T&& v)
        : Base(ResultType::Ok, std::move(v)) {}

    // Public copy/move for the tests
    ExposedResultValue(const ExposedResultValue& other)
        : Base(other) {}

    ExposedResultValue(ExposedResultValue&& other) noexcept(std::is_nothrow_move_constructible<T>::value)
        : Base(std::move(other)) {}

    using Base::value; // make value() visible (public in Base per interface)
};

// A copy-counting type to observe whether T's copy-ctor is invoked
struct CopyCounting {
    static int copies;
    int id{0};

    CopyCounting() = default;
    explicit CopyCounting(int i) : id(i) {}
    CopyCounting(const CopyCounting& other) : id(other.id) { ++copies; }
    CopyCounting(CopyCounting&& other) noexcept : id(other.id) {}

    CopyCounting& operator=(const CopyCounting& other) {
        id = other.id; ++copies; return *this;
    }
    CopyCounting& operator=(CopyCounting&& other) noexcept {
        id = other.id; return *this;
    }

    static void Reset() { copies = 0; }
};
int CopyCounting::copies = 0;

// A non-copyable type to ensure copying a non-Ok result does not try to copy T
struct NonCopyable {
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) noexcept = default;
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable& operator=(NonCopyable&&) noexcept = default;
};

// A type that throws on copy to verify exception propagation
struct ThrowOnCopy {
    ThrowOnCopy() = default;
    ThrowOnCopy(const ThrowOnCopy&) { throw std::runtime_error("boom"); }
    ThrowOnCopy(ThrowOnCopy&&) noexcept = default;
};

} // namespace test_helpers

// ---------------------------
// Test fixture
// ---------------------------

class ResultValueBaseTest_1062 : public ::testing::Test {};

// ---------------------------
// Tests
// ---------------------------

TEST_F(ResultValueBaseTest_1062, Copy_OkCopiesValue_1062) {
    using namespace test_helpers;
    using RV = ExposedResultValue<CopyCounting>;
    using ResultType = Catch::Clara::Detail::ResultType;

    CopyCounting::Reset();
    RV original(ResultType::Ok, CopyCounting{42});

    // Act: copy-construct an Ok result
    RV copy(original);

    // Assert: T was copy-constructed exactly once and value preserved
    EXPECT_EQ(CopyCounting::copies, 1);
    EXPECT_EQ(copy.value().id, 42);
    EXPECT_EQ(original.value().id, 42);
}

TEST_F(ResultValueBaseTest_1062, Copy_NonOkDoesNotRequireTCopy_1062) {
    using namespace test_helpers;
    using RV = ExposedResultValue<NonCopyable>;
    using ResultType = Catch::Clara::Detail::ResultType;

    // Construct a non-Ok (RuntimeError) result that holds a NonCopyable T type.
    RV err(ResultType::RuntimeError);

    // If the copy constructor tried to copy T, this wouldn't compile.
    // At runtime, it should also not throw.
    EXPECT_NO_THROW({
        RV copy(err);
        (void)copy;
    });
}

TEST_F(ResultValueBaseTest_1062, Copy_OkPropagatesExceptionFromTCopy_1062) {
    using namespace test_helpers;
    using RV = ExposedResultValue<ThrowOnCopy>;
    using ResultType = Catch::Clara::Detail::ResultType;

    RV ok(ResultType::Ok, ThrowOnCopy{});

    // Copying an Ok result should attempt to copy-construct T and propagate T's exception
    EXPECT_THROW({ RV copy(ok); (void)copy; }, std::runtime_error);
}

TEST_F(ResultValueBaseTest_1062, Value_ReadableFromCopiedOkResult_1062) {
    using namespace test_helpers;
    using RV = ExposedResultValue<int>;
    using ResultType = Catch::Clara::Detail::ResultType;

    RV a(ResultType::Ok, 7);
    RV b(a); // copy

    // value() should be accessible on the copy and equal to the original's value
    EXPECT_EQ(a.value(), 7);
    EXPECT_EQ(b.value(), 7);

    // Also verify const-ref return type at compile time (interface-level check)
    static_assert(std::is_same_v<decltype(std::declval<const RV&>().value()), const int&>,
                  "value() must return const T&");
}
