// File: result_value_base_dtor_tests_363.cpp
#include <gtest/gtest.h>

// Include the header that declares Catch::Clara::Detail::ResultValueBase<T>
// and ResultType. Adjust the include path if needed.
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace CCD = Catch::Clara::Detail;

// A payload whose destructor increments a counter so we can observe destruction.
struct DtorTracker {
    static int dtor_count;
    int payload;
    explicit DtorTracker(int v = 0) : payload(v) {}
    DtorTracker(DtorTracker const&) = default;
    DtorTracker(DtorTracker&&) noexcept = default;
    DtorTracker& operator=(DtorTracker const&) = default;
    DtorTracker& operator=(DtorTracker&&) noexcept = default;
    ~DtorTracker() { ++dtor_count; }

    static void Reset() { dtor_count = 0; }
};
int DtorTracker::dtor_count = 0;

// Test shim that exposes the protected constructors/destructor of ResultValueBase<T>.
template <typename T>
class ExposedResultValueBase : public CCD::ResultValueBase<T> {
    using Base = CCD::ResultValueBase<T>;
public:
    // Construct with explicit ResultType (used for non-Ok cases where no value is provided).
    explicit ExposedResultValueBase(CCD::ResultType type)
        : Base(type) {}

    // Construct with a value; per interface, this sets ResultType to Ok.
    explicit ExposedResultValueBase(T const& v)
        : Base(CCD::ResultType::Ok, v) {}

    // rvalue convenience
    explicit ExposedResultValueBase(T&& v)
        : Base(CCD::ResultType::Ok, std::move(v)) {}

    // Make destructor public so objects can be created/destroyed in tests.
    ~ExposedResultValueBase() override = default;

    // Expose value() for observable behavior checks.
    using Base::value;
};

// ---- Tests ----

TEST(ResultValueBaseDtor_363, DestructorCalls_T_OnlyWhenTypeIsOk_363) {
    DtorTracker::Reset();
    {
        ExposedResultValueBase<DtorTracker> ok_obj{ DtorTracker{123} };
        EXPECT_EQ(DtorTracker::dtor_count, 0) << "No destruction before scope end";
    }
    // When m_type == Ok, base dtor should call ~T()
    EXPECT_EQ(DtorTracker::dtor_count, 1);
}

TEST(ResultValueBaseDtor_363, DestructorDoesNotCall_T_WhenTypeIsLogicError_363) {
    DtorTracker::Reset();
    {
        ExposedResultValueBase<DtorTracker> err_obj{ CCD::ResultType::LogicError };
        EXPECT_EQ(DtorTracker::dtor_count, 0);
    }
    // Non-Ok types must not destroy a non-existent value
    EXPECT_EQ(DtorTracker::dtor_count, 0);
}

TEST(ResultValueBaseDtor_363, DestructorDoesNotCall_T_WhenTypeIsRuntimeError_363) {
    DtorTracker::Reset();
    {
        ExposedResultValueBase<DtorTracker> err_obj{ CCD::ResultType::RuntimeError };
        EXPECT_EQ(DtorTracker::dtor_count, 0);
    }
    EXPECT_EQ(DtorTracker::dtor_count, 0);
}

TEST(ResultValueBaseDtor_363, ValueIsAccessibleAndIntactWhenOk_363) {
    DtorTracker::Reset();
    int seen = -1;
    {
        ExposedResultValueBase<DtorTracker> ok_obj{ DtorTracker{42} };
        // Observable behavior: value() should be usable and reflect construction.
        seen = ok_obj.value().payload;
        EXPECT_EQ(DtorTracker::dtor_count, 0);
    }
    EXPECT_EQ(seen, 42);
    // After destruction of an Ok object, ~T() must have run exactly once.
    EXPECT_EQ(DtorTracker::dtor_count, 1);
}

TEST(ResultValueBaseDtor_363, MultipleOkObjectsEachDestroyValueOnce_363) {
    DtorTracker::Reset();
    {
        ExposedResultValueBase<DtorTracker> a{ DtorTracker{1} };
        ExposedResultValueBase<DtorTracker> b{ DtorTracker{2} };
        ExposedResultValueBase<DtorTracker> c{ DtorTracker{3} };
        EXPECT_EQ(DtorTracker::dtor_count, 0);
    }
    EXPECT_EQ(DtorTracker::dtor_count, 3);
}
