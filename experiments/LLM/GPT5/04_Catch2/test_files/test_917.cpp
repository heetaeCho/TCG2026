// File: object_storage_tests_917.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>

// Include the real header from your tree
#include "Catch2/extras/catch_amalgamated.hpp"

namespace detail_917 {

// A tracking type used to observe construction/destruction & forwarding.
// This is an *external* collaborator for the template parameter T.
struct Tracker {
    static int default_ctor_count;
    static int lvalue_int_ctor_count;
    static int rvalue_int_ctor_count;
    static int dtor_count;

    static void Reset() {
        default_ctor_count = 0;
        lvalue_int_ctor_count = 0;
        rvalue_int_ctor_count = 0;
        dtor_count = 0;
    }

    Tracker() { ++default_ctor_count; }
    explicit Tracker(const int&) { ++lvalue_int_ctor_count; }
    explicit Tracker(int&&) { ++rvalue_int_ctor_count; }
    Tracker(const Tracker&) = delete;
    Tracker(Tracker&&) = delete;
    ~Tracker() { ++dtor_count; }
};

int Tracker::default_ctor_count = 0;
int Tracker::lvalue_int_ctor_count = 0;
int Tracker::rvalue_int_ctor_count = 0;
int Tracker::dtor_count = 0;

// Detection idiom to check if .destruct() is available on the type.
template <typename S, typename = void>
struct has_destruct : std::false_type {};

template <typename S>
struct has_destruct<S, std::void_t<decltype(std::declval<S&>().template destruct<>())>>
    : std::true_type {};

} // namespace detail_917

// Aliases for brevity
template <typename T, bool Destruct>
using ObjectStorage = Catch::Benchmark::Detail::ObjectStorage<T, Destruct>;

// --------------------------- Tests ---------------------------

// Normal operation: Destruct==true -> object should be destroyed automatically.
TEST(ObjectStorage_917, AutoDestruct_DestroysOnScopeExit_917) {
    using namespace detail_917;
    Tracker::Reset();
    {
        ObjectStorage<Tracker, /*Destruct=*/true> os;
        os.construct(); // default-construct the stored Tracker
        EXPECT_EQ(Tracker::default_ctor_count, 1);
        // No destruction yet (object still alive)
        EXPECT_EQ(Tracker::dtor_count, 0);
    } // scope exit -> if Destruct==true, stored object should be destroyed
    EXPECT_EQ(Tracker::dtor_count, 1);
}

// Boundary / API shape: destruct() should only exist when Destruct==false (per interface).
TEST(ObjectStorage_917, SFINAE_DestructPresence_917) {
    using namespace detail_917;
    using AutoD = ObjectStorage<Tracker, /*Destruct=*/true>;
    using ManualD = ObjectStorage<Tracker, /*Destruct=*/false>;

    // Compile-time interface checks (no runtime behavior).
    static_assert(!has_destruct<AutoD>::value,
                  "destruct() must NOT be available when Destruct==true");
    static_assert(has_destruct<ManualD>::value,
                  "destruct() must be available when Destruct==false");
}

// Exceptional/error-ish observable case: Destruct==false -> no automatic destruction;
// only destroyed when destruct() is called.
TEST(ObjectStorage_917, ManualDestruct_OnlyWhenCalled_917) {
    using namespace detail_917;
    Tracker::Reset();
    {
        ObjectStorage<Tracker, /*Destruct=*/false> os;
        os.construct(); // default-construct
        EXPECT_EQ(Tracker::default_ctor_count, 1);
        // Still alive so far
        EXPECT_EQ(Tracker::dtor_count, 0);

        // Manually destroy via the public API
        os.destruct<>();
        EXPECT_EQ(Tracker::dtor_count, 1);
        // (No further observable effects we can/should assert without internal access)
    }
    // Because we already destroyed manually, leaving scope should not destroy again
    EXPECT_EQ(Tracker::dtor_count, 1);
}

// Forwarding behavior: verify lvalue vs rvalue ctor selection is preserved by construct(...)
TEST(ObjectStorage_917, PerfectForwarding_LvalueVsRvalue_917) {
    using namespace detail_917;

    // Lvalue path
    {
        Tracker::Reset();
        int x = 7;
        ObjectStorage<Tracker, /*Destruct=*/true> os;
        os.construct(x); // should bind to Tracker(const int&)
        EXPECT_EQ(Tracker::lvalue_int_ctor_count, 1);
        EXPECT_EQ(Tracker::rvalue_int_ctor_count, 0);
        EXPECT_EQ(Tracker::dtor_count, 0);
    }
    // destroyed on scope exit
    EXPECT_EQ(Tracker::dtor_count, 1);

    // Rvalue path
    {
        Tracker::Reset();
        ObjectStorage<Tracker, /*Destruct=*/true> os;
        os.construct(42); // should bind to Tracker(int&&)
        EXPECT_EQ(Tracker::lvalue_int_ctor_count, 0);
        EXPECT_EQ(Tracker::rvalue_int_ctor_count, 1);
        EXPECT_EQ(Tracker::dtor_count, 0);
    }
    // destroyed on scope exit
    EXPECT_EQ(Tracker::dtor_count, 1);
}
