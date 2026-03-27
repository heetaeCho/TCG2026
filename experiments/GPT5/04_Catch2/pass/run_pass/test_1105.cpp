// File: tests/object_storage_tests_1105.cpp

#include <gtest/gtest.h>
#include <utility>
#include <string>

// Include the real interface (already present in your codebase)
#include "Catch2/extras/catch_amalgamated.hpp"

namespace cbd = Catch::Benchmark::Detail;

// Helper type that records which constructor/destructor paths are taken.
// This lets us observe ObjectStorage's effects purely through T's public behavior.
struct Probe {
    static int default_ctor_count;
    static int value_ctor_count;
    static int copy_ctor_count;
    static int move_ctor_count;
    static int dtor_count;

    static int last_value_constructed;
    static int last_value_copied_from;
    static int last_value_moved_from;

    int value{0};

    Probe() : value(0) {
        ++default_ctor_count;
        last_value_constructed = value;
    }
    explicit Probe(int v) : value(v) {
        ++value_ctor_count;
        last_value_constructed = value;
    }
    Probe(const Probe& other) : value(other.value) {
        ++copy_ctor_count;
        last_value_copied_from = other.value;
    }
    Probe(Probe&& other) noexcept : value(other.value) {
        ++move_ctor_count;
        last_value_moved_from = other.value;
        // leave other in valid state; not required to observe further
    }
    ~Probe() {
        ++dtor_count;
    }

    static void Reset() {
        default_ctor_count = value_ctor_count = copy_ctor_count = move_ctor_count = dtor_count = 0;
        last_value_constructed = last_value_copied_from = last_value_moved_from = 0;
    }
};

int Probe::default_ctor_count = 0;
int Probe::value_ctor_count   = 0;
int Probe::copy_ctor_count    = 0;
int Probe::move_ctor_count    = 0;
int Probe::dtor_count         = 0;

int Probe::last_value_constructed = 0;
int Probe::last_value_copied_from = 0;
int Probe::last_value_moved_from  = 0;

// Move-only collaborator to verify that ObjectStorage uses T's move constructor.
struct MoveOnlyProbe {
    static int value_ctor_count;
    static int move_ctor_count;
    static int dtor_count;
    static int last_value_constructed;
    static int last_value_moved_from;

    int value{0};

    explicit MoveOnlyProbe(int v) : value(v) {
        ++value_ctor_count;
        last_value_constructed = v;
    }
    MoveOnlyProbe(const MoveOnlyProbe&) = delete;
    MoveOnlyProbe& operator=(const MoveOnlyProbe&) = delete;

    MoveOnlyProbe(MoveOnlyProbe&& other) noexcept : value(other.value) {
        ++move_ctor_count;
        last_value_moved_from = other.value;
    }
    ~MoveOnlyProbe() {
        ++dtor_count;
    }

    static void Reset() {
        value_ctor_count = move_ctor_count = dtor_count = 0;
        last_value_constructed = last_value_moved_from = 0;
    }
};

int MoveOnlyProbe::value_ctor_count = 0;
int MoveOnlyProbe::move_ctor_count  = 0;
int MoveOnlyProbe::dtor_count       = 0;
int MoveOnlyProbe::last_value_constructed = 0;
int MoveOnlyProbe::last_value_moved_from  = 0;


// ============ TESTS ============

// Normal operation: construct a value and copy-construct storage.
// Verifies that T's copy-ctor is invoked with the original value.
// (Copy-ctor path is explicitly shown in the provided partial code.)
TEST(ObjectStorageTest_1105, CopyConstructorCopiesStoredObject_1105) {
    Probe::Reset();

    {
        cbd::ObjectStorage<Probe, /*Destruct=*/true> a;
        a.construct(42); // observable: Probe(int) called

        EXPECT_EQ(Probe::value_ctor_count, 1);
        EXPECT_EQ(Probe::last_value_constructed, 42);

        cbd::ObjectStorage<Probe, /*Destruct=*/true> b(a); // should call Probe copy-ctor
        // We cannot access stored object directly; we only observe copy-ctor effect.
        EXPECT_EQ(Probe::copy_ctor_count, 1);
        EXPECT_EQ(Probe::last_value_copied_from, 42);
    }

    // With Destruct=true, both objects’ contained Probes should have been destroyed.
    // 2 constructed -> 2 destroyed
    EXPECT_EQ(Probe::dtor_count, 2);
}

// Boundary/behavioral difference: automatic destruction when Destruct=true.
// Verifies that destruction happens on scope exit without manual calls.
TEST(ObjectStorageTest_1105, AutoDestructTrue_DestroyedOnScopeExit_1105) {
    Probe::Reset();

    {
        cbd::ObjectStorage<Probe, /*Destruct=*/true> s;
        s.construct(7);
        EXPECT_EQ(Probe::value_ctor_count, 1);
        EXPECT_EQ(Probe::dtor_count, 0);
    }

    // After scope: the stored Probe must be destroyed automatically.
    EXPECT_EQ(Probe::dtor_count, 1);
}

// Manual destruction path when Destruct=false: destructor should NOT run at scope exit
// unless destruct() is explicitly called. We verify that behavior via Probe's dtor count.
TEST(ObjectStorageTest_1105, ManualDestructFalse_DestructOnlyOnExplicitCall_1105) {
    Probe::Reset();

    // Use an inner scope to check the scope-exit behavior precisely.
    {
        cbd::ObjectStorage<Probe, /*Destruct=*/false> s;
        s.construct(99);

        EXPECT_EQ(Probe::value_ctor_count, 1);
        EXPECT_EQ(Probe::dtor_count, 0);

        // Destruct should be available only when Destruct=false (per interface).
        s.destruct(); // explicit destruction
        EXPECT_EQ(Probe::dtor_count, 1);
    }

    // Because the object was manually destroyed, scope exit should not destroy again.
    EXPECT_EQ(Probe::dtor_count, 1);
}

// Move-construction of ObjectStorage should route to T's move constructor for move-only types.
// This is a compile-time and runtime (counter) verification without peeking into internals.
TEST(ObjectStorageTest_1105, MoveConstructor_UsesMoveCtorOfT_1105) {
    MoveOnlyProbe::Reset();

    {
        cbd::ObjectStorage<MoveOnlyProbe, /*Destruct=*/true> a;
        a.construct(123);
        EXPECT_EQ(MoveOnlyProbe::value_ctor_count, 1);
        EXPECT_EQ(MoveOnlyProbe::last_value_constructed, 123);

        cbd::ObjectStorage<MoveOnlyProbe, /*Destruct=*/true> b(std::move(a));
        // If ObjectStorage attempted to copy, this would fail to compile.
        // We also observe the move-ctor counter at runtime.
        EXPECT_EQ(MoveOnlyProbe::move_ctor_count, 1);
        EXPECT_EQ(MoveOnlyProbe::last_value_moved_from, 123);
    }

    // Two storages each held exactly one MoveOnlyProbe over their lifetimes.
    // After scope exit, both should be destroyed automatically (Destruct=true).
    EXPECT_EQ(MoveOnlyProbe::dtor_count, 2);
}

// Normal operation: default-constructible path via construct() with no args.
// Verifies the default constructor of T is used and destruction follows policy.
TEST(ObjectStorageTest_1105, DefaultConstructThroughConstruct_NoArgs_1105) {
    Probe::Reset();

    {
        cbd::ObjectStorage<Probe, /*Destruct=*/true> s;
        s.construct(); // should call Probe()
        EXPECT_EQ(Probe::default_ctor_count, 1);
        EXPECT_EQ(Probe::dtor_count, 0);
    }

    EXPECT_EQ(Probe::dtor_count, 1);
}
