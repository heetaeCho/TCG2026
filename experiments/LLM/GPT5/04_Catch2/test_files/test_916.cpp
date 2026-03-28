// File: tests/object_storage_tests_916.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include <string>

// Include the header that provides ObjectStorage
// Adjust the include path if needed in your project.
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Benchmark::Detail::ObjectStorage;

// A tiny helper to observe construction / destruction through global counters.
// This is an external collaborator for tests and does not inspect ObjectStorage internals.
struct Tracker {
    static inline int ctor_count = 0;
    static inline int dtor_count = 0;
    static inline int last_int = -1;
    static inline std::string last_str;

    static void Reset() {
        ctor_count = 0;
        dtor_count = 0;
        last_int = -1;
        last_str.clear();
    }

    Tracker() { ++ctor_count; }
    Tracker(int i, std::string s) {
        ++ctor_count;
        last_int = i;
        last_str = std::move(s);
    }
    ~Tracker() { ++dtor_count; }
};

// Detection idiom to check if .destruct() is available on a given storage type.
template <typename S, typename = void>
struct has_destruct : std::false_type {};

template <typename S>
struct has_destruct<S, std::void_t<decltype(std::declval<S&>().template destruct<>())>>
    : std::true_type {};

// ---------- Tests ----------

TEST(ObjectStorageTest_916, NoConstruct_NoDestructionOnScopeEnd_916) {
    Tracker::Reset();
    {
        ObjectStorage<Tracker, /*Destruct=*/true> auto_d;
        // No construct() call; leaving scope should not call Tracker's destructor.
    }
    EXPECT_EQ(Tracker::ctor_count, 0);
    EXPECT_EQ(Tracker::dtor_count, 0);

    Tracker::Reset();
    {
        ObjectStorage<Tracker, /*Destruct=*/false> manual_d;
        // No construct() call; leaving scope should not call Tracker's destructor.
    }
    EXPECT_EQ(Tracker::ctor_count, 0);
    EXPECT_EQ(Tracker::dtor_count, 0);
}

TEST(ObjectStorageTest_916, DestructTrue_ConstructAndAutoDestroy_916) {
    Tracker::Reset();
    {
        ObjectStorage<Tracker, /*Destruct=*/true> storage;
        storage.construct(); // default-construct Tracker
        EXPECT_EQ(Tracker::ctor_count, 1);
        EXPECT_EQ(Tracker::dtor_count, 0);
        // On leaving scope, ObjectStorage's destructor should clean up the stored Tracker.
    }
    EXPECT_EQ(Tracker::ctor_count, 1);
    EXPECT_EQ(Tracker::dtor_count, 1);
}

TEST(ObjectStorageTest_916, DestructFalse_ConstructThenManualDestruct_916) {
    Tracker::Reset();
    {
        ObjectStorage<Tracker, /*Destruct=*/false> storage;
        storage.construct(42, std::string{"hello"});
        // Not auto-destroying: before manual destruct(), no dtor call should have happened.
        EXPECT_EQ(Tracker::ctor_count, 1);
        EXPECT_EQ(Tracker::dtor_count, 0);

        // Manual destruction is required/allowed for Destruct=false.
        storage.destruct<>();
        EXPECT_EQ(Tracker::dtor_count, 1);

        // Leaving scope should not call destructor again (no auto-destruction path).
    }
    EXPECT_EQ(Tracker::dtor_count, 1);
}

TEST(ObjectStorageTest_916, Construct_ForwardsArguments_916) {
    Tracker::Reset();
    {
        ObjectStorage<Tracker, /*Destruct=*/true> storage;
        storage.construct(7, std::string{"arg"});
        // Observe forwarded arguments via Tracker's static side effects.
        EXPECT_EQ(Tracker::ctor_count, 1);
        EXPECT_EQ(Tracker::last_int, 7);
        EXPECT_EQ(Tracker::last_str, "arg");
    }
    // Auto-destroy should have occurred once.
    EXPECT_EQ(Tracker::dtor_count, 1);
}

TEST(ObjectStorageTest_916, ManualDestruct_AvailabilityViaSFINAE_916) {
    // Compile-time, interface-level checks (no logic inference):
    using AutoD = ObjectStorage<Tracker, /*Destruct=*/true>;
    using ManualD = ObjectStorage<Tracker, /*Destruct=*/false>;

    // For Destruct=false, destruct() must be available.
    static_assert(has_destruct<ManualD>::value, "destruct() should be available when Destruct=false");
    // For Destruct=true, destruct() must NOT be available.
    static_assert(!has_destruct<AutoD>::value, "destruct() should not be available when Destruct=true");

    // A small runtime smoke to ensure nothing weird changed:
    Tracker::Reset();
    {
        ManualD s;
        s.construct();
        EXPECT_EQ(Tracker::ctor_count, 1);
        s.destruct<>();
        EXPECT_EQ(Tracker::dtor_count, 1);
    }
    // No auto-destruction after manual destruct for Destruct=false.
    EXPECT_EQ(Tracker::dtor_count, 1);
}

//
// Notes:
// - We intentionally do not test copy/move semantics of ObjectStorage because its
//   observable behavior w.r.t. stored object lifetime is not specified by the
//   provided interface, and asserting a specific behavior would risk relying on
//   unexposed internals.
// - We also avoid double-calling destruct() to steer clear of undefined behavior.
//

