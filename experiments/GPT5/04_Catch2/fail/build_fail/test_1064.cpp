// File: tests/result_value_base_ctor_1064_tests.cpp

#include <gtest/gtest.h>

// Include the real header under test.
// Adjust the include path if your project structure differs.
#include "catch2/internal/catch_clara.hpp"

#include <type_traits>
#include <utility>

namespace C = Catch::Clara::Detail;

// ---------- Helper types (for observable behavior only) ----------

struct CopyTracker {
    static int copies;
    int id;
    explicit CopyTracker(int v = 0) : id(v) {}
    CopyTracker(const CopyTracker& other) : id(other.id) { ++copies; }
    CopyTracker& operator=(const CopyTracker&) = delete;
};
int CopyTracker::copies = 0;

struct ThrowOnCopy {
    struct Boom {};
    ThrowOnCopy() = default;
    ThrowOnCopy(const ThrowOnCopy&) { throw Boom{}; }
    ThrowOnCopy& operator=(const ThrowOnCopy&) = delete;
};

struct BigObject {
    // Large-ish payload to exercise placement-new on a bigger type
    // without relying on any internal state.
    alignas(16) unsigned char data[4096]{};
    // Make it obviously copyable.
    BigObject() = default;
    BigObject(const BigObject&) = default;
    BigObject& operator=(const BigObject&) = delete;
};

// ---------- Detection idiom for optional value() accessor ----------

template <typename R>
class has_value_method {
    template <typename T>
    static auto test(int) -> decltype(std::declval<T&>().value(), std::true_type{});
    template <typename>
    static auto test(...) -> std::false_type;
public:
    static constexpr bool value = decltype(test<R>(0))::value;
};

template <typename R>
constexpr bool has_value_method_v = has_value_method<R>::value;

// ---------- Tests ----------

// NOTE: We assume ResultValueBase is a template on the stored value type,
// and that ResultType::Ok exists (as implied by the provided snippet).
// We do not rely on ResultBase API (no calls into it).
// We only verify effects that are externally observable from constructing.

TEST(ResultValueBase_1064, ConstructorCopiesInputOnce_1064) {
    using T = CopyTracker;
    T::copies = 0;

    T input{42};

    // Construct the target.
    // The signature shown in the prompt takes (ResultType, T const&).
    // We pass ResultType::Ok (any value should do; we aren't asserting on it).
    C::ResultValueBase<T> rvb{Catch::Clara::Detail::ResultType::Ok, input};

    // Observable effect: copy-ctor must have been invoked exactly once
    // to place-construct T at &m_value.
    EXPECT_EQ(T::copies, 1);
}

TEST(ResultValueBase_1064, ConstructorPropagatesCopyException_1064) {
    using T = ThrowOnCopy;

    // Constructing should throw the exception raised by T's copy-ctor.
    EXPECT_THROW(
        (C::ResultValueBase<T>{Catch::Clara::Detail::ResultType::Ok, T{}}),
        T::Boom
    );
}

TEST(ResultValueBase_1064, ConstructorHandlesLargeType_1064) {
    using T = BigObject;

    // Should simply succeed (no assumptions about internals).
    EXPECT_NO_THROW(
        (C::ResultValueBase<T>{Catch::Clara::Detail::ResultType::Ok, T{}})
    );
}

// Optional: If your implementation provides a value() accessor that returns
// const T& (or similar), we verify it matches the input. If not available,
// the test self-skips without failing or making assumptions.
TEST(ResultValueBase_1064, ValueAccessorMatchesInputWhenAvailable_1064) {
    using T = CopyTracker;
    T::copies = 0;
    T input{7};

    C::ResultValueBase<T> rvb{Catch::Clara::Detail::ResultType::Ok, input};

    using RvbT = decltype(rvb);
    if constexpr (has_value_method_v<RvbT>) {
        // If a value() method exists, assert it returns the copied value.
        // We cannot assert address equality (placement-new into internal storage),
        // so we only check observable state on T (its 'id').
        const T& out = rvb.value();
        EXPECT_EQ(out.id, 7);
        // The copying behavior is already validated in the copy-count test.
    } else {
        GTEST_SKIP() << "ResultValueBase<T> has no value() accessor in this build.";
    }
}
