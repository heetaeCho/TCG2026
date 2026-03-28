// object_storage_tests_918.cpp
#include <gtest/gtest.h>
#include <type_traits>
#include <utility>
#include <string>

// Include the real interface (black box)
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Benchmark::Detail::ObjectStorage;

// ---------- Test helpers (external collaborators / observable effects) ----------
struct LifecycleCounters {
    int ctor = 0;
    int dtor = 0;
    int copy = 0;
    int move = 0;

    // For verifying argument forwarding (boundary-ish)
    int seen_int = 0;
    std::string seen_str;
    double seen_double = 0.0;
};

// A trivially observable type whose lifecycle mutates external counters
struct Tracker {
    LifecycleCounters* c = nullptr;

    // Perfect-forwarded ctor used by ObjectStorage::construct
    Tracker(LifecycleCounters* counters,
            int x = 0,
            std::string s = {},
            double d = 0.0)
        : c(counters)
    {
        if (c) {
            ++c->ctor;
            c->seen_int = x;
            c->seen_str = std::move(s);
            c->seen_double = d;
        }
    }

    Tracker(const Tracker& rhs) : c(rhs.c) {
        if (c) ++c->copy;
    }
    Tracker(Tracker&& rhs) noexcept : c(rhs.c) {
        if (c) ++c->move;
        rhs.c = nullptr; // does not affect semantics; just prevents accidental reuse
    }

    ~Tracker() {
        if (c) ++c->dtor;
    }
};

// Trait to detect presence of a defaulted `destruct()` member (SFINAE)
template <typename OS, typename = void>
struct has_default_destruct : std::false_type {};
template <typename OS>
struct has_default_destruct<OS, std::void_t<decltype(std::declval<OS&>().destruct())>> : std::true_type {};

// A move-only tracker to verify forwarding of move-only args
struct MoveOnly {
    LifecycleCounters* c = nullptr;

    explicit MoveOnly(LifecycleCounters* counters) : c(counters) {
        if (c) ++c->ctor;
    }
    MoveOnly(const MoveOnly&) = delete;
    MoveOnly& operator=(const MoveOnly&) = delete;

    MoveOnly(MoveOnly&& other) noexcept : c(other.c) {
        if (c) ++c->move;
        other.c = nullptr;
    }
    MoveOnly& operator=(MoveOnly&& other) noexcept {
        if (this != &other) {
            c = other.c;
            if (c) ++c->move;
            other.c = nullptr;
        }
        return *this;
    }

    ~MoveOnly() {
        if (c) ++c->dtor;
    }
};

// ---------- Tests ----------
class ObjectStorageTest_918 : public ::testing::Test {};

// Normal operation: automatic destruction when Destruct = true
TEST_F(ObjectStorageTest_918, AutoDestruct_PolicyTrue_918) {
    LifecycleCounters cnt{};
    {
        ObjectStorage<Tracker, true> os;
        os.construct(&cnt, 123, std::string("abc"), 4.5);
        // Scope end should destroy contained Tracker automatically.
    }
    EXPECT_EQ(cnt.ctor, 1);
    EXPECT_EQ(cnt.dtor, 1);     // observable effect: destructor was called exactly once
    EXPECT_EQ(cnt.copy, 0);
    EXPECT_EQ(cnt.move, 0);
    // Also verify the forwarded arguments were seen by Tracker's ctor
    EXPECT_EQ(cnt.seen_int, 123);
    EXPECT_EQ(cnt.seen_str, "abc");
    EXPECT_DOUBLE_EQ(cnt.seen_double, 4.5);
}

// Normal operation: manual destruction available and required when Destruct = false
TEST_F(ObjectStorageTest_918, ManualDestruct_PolicyFalse_918) {
    LifecycleCounters cnt{};
    {
        ObjectStorage<Tracker, false> os;
        os.construct(&cnt);
        // Manually destroy; observable: exactly one dtor call in total.
        os.destruct();
        // Scope end should not destroy again (no double-destroy).
    }
    EXPECT_EQ(cnt.ctor, 1);
    EXPECT_EQ(cnt.dtor, 1);
}

// SFINAE/availability: destruct() should NOT be available for Destruct = true
TEST_F(ObjectStorageTest_918, DestructAvailability_SFINAE_918) {
    using OS_Auto = ObjectStorage<Tracker, true>;
    using OS_Manual = ObjectStorage<Tracker, false>;

    static_assert(!has_default_destruct<OS_Auto>::value,
                  "destruct() must not be available when Destruct == true");
    static_assert(has_default_destruct<OS_Manual>::value,
                  "destruct() must be available when Destruct == false");
    SUCCEED(); // compile-time checks above are the core of this test
}

// Copy construction: observable copy of contained Tracker
TEST_F(ObjectStorageTest_918, CopyConstruction_CopiesContained_918) {
    LifecycleCounters cnt{};
    int total_dtors_at_end = 0;
    {
        ObjectStorage<Tracker, true> src;
        src.construct(&cnt, 7, "x", 1.0);
        {
            ObjectStorage<Tracker, true> copy = src; // should copy contained object
            (void)copy;
        } // copy's contained Tracker should be destroyed here
        // src still alive; its contained Tracker still not destroyed
        EXPECT_EQ(cnt.copy, 1);
        EXPECT_EQ(cnt.dtor, 1);
        total_dtors_at_end = cnt.dtor;
    }
    // Now src's contained Tracker is destroyed too
    EXPECT_EQ(cnt.dtor, total_dtors_at_end + 1);
}

// Move construction: observable move of contained Tracker
TEST_F(ObjectStorageTest_918, MoveConstruction_MovesContained_918) {
    LifecycleCounters cnt{};
    int dtors_mid = 0;
    {
        ObjectStorage<Tracker, true> src;
        src.construct(&cnt, 5, "y", 2.0);
        {
            ObjectStorage<Tracker, true> moved = std::move(src); // should move contained object
            (void)moved;
        } // moved-from storage's object destroyed here
        dtors_mid = cnt.dtor;
        // When src goes out of inner scope, it should not destroy again (no double-destroy)
    }
    EXPECT_EQ(cnt.move, 1);
    EXPECT_EQ(cnt.copy, 0);
    EXPECT_EQ(cnt.dtor, dtors_mid); // still the same (destroyed once total)
}

// Boundary-ish: construct with move-only dependency to ensure perfect forwarding works
TEST_F(ObjectStorageTest_918, Construct_ForwardsMoveOnly_918) {
    LifecycleCounters cnt{};
    {
        ObjectStorage<MoveOnly, true> os;
        MoveOnly mo(&cnt);
        os.construct(std::move(mo)); // should accept move-only and move it in
        EXPECT_EQ(cnt.ctor, 1);
        // at least one move must have occurred (into storage)
        EXPECT_GE(cnt.move, 1);
    }
    // moved-in object should be destroyed exactly once
    EXPECT_EQ(cnt.dtor, 1);
}

// Manual destruction not double-invoked for Destruct=false
TEST_F(ObjectStorageTest_918, ManualDestruct_ExactlyOnce_918) {
    LifecycleCounters cnt{};
    {
        ObjectStorage<Tracker, false> os;
        os.construct(&cnt);
        os.destruct();
        // Not calling os.destruct() again; scope end should not call destructor again.
    }
    EXPECT_EQ(cnt.dtor, 1);
}
