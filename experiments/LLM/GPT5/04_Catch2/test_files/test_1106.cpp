// File: tests/ObjectStorageMoveCtor_1106.tests.cpp

#include <gtest/gtest.h>
#include <stdexcept>
#include "Catch2/extras/catch_amalgamated.hpp"

using Catch::Benchmark::Detail::ObjectStorage;

// A simple tracker type whose ctor/dtor and move/copy operations are observable
struct Tracker {
    static int value_ctor;
    static int default_ctor;
    static int copy_ctor;
    static int move_ctor;
    static int dtor;

    static void Reset() {
        value_ctor = default_ctor = copy_ctor = move_ctor = dtor = 0;
    }

    int id = 0;
    bool throw_on_move = false;

    Tracker() { ++default_ctor; }

    explicit Tracker(int v, bool throw_move = false)
        : id(v), throw_on_move(throw_move) { ++value_ctor; }

    Tracker(const Tracker& other)
        : id(other.id), throw_on_move(other.throw_on_move) { ++copy_ctor; }

    // Not noexcept on purpose so we can test exception propagation
    Tracker(Tracker&& other)
        : id(other.id), throw_on_move(other.throw_on_move) {
        ++move_ctor;
        if (other.throw_on_move) {
            throw std::runtime_error("move boom");
        }
    }

    ~Tracker() { ++dtor; }
};

int Tracker::value_ctor = 0;
int Tracker::default_ctor = 0;
int Tracker::copy_ctor   = 0;
int Tracker::move_ctor   = 0;
int Tracker::dtor        = 0;


// ========== Tests ==========

// Normal operation: moving from a constructed source creates a second object
// via Tracker's move-ctor. With Destruct=true, both storages destroy their objects.
TEST(ObjectStorage_MoveCtor_1106, MoveFromConstructed_DestructTrue_1106) {
    Tracker::Reset();

    int dtor_after_inner = -1;

    {
        ObjectStorage<Tracker, /*Destruct=*/true> src;
        src.construct(7);  // value-construct T inside src

        {
            ObjectStorage<Tracker, /*Destruct=*/true> dst(std::move(src));
            // We can only assert observable global side effects:
            // - exactly one value construction (src.construct)
            // - exactly one move construction (dst from src)
            EXPECT_EQ(Tracker::value_ctor, 1);
            EXPECT_EQ(Tracker::move_ctor, 1);
            EXPECT_EQ(Tracker::copy_ctor, 0);
            EXPECT_EQ(Tracker::dtor, 0); // nothing destroyed yet inside this scope
        } // dst goes out of scope here

        // After dst is destroyed, one destructor should have run
        dtor_after_inner = Tracker::dtor;
        EXPECT_EQ(dtor_after_inner, 1);
        // src still alive; second destruction will happen after exiting outer scope
    }

    // After both go out of scope, two dtors total
    EXPECT_EQ(Tracker::dtor, 2);
    EXPECT_EQ(Tracker::value_ctor, 1);
    EXPECT_EQ(Tracker::move_ctor, 1);
    EXPECT_EQ(Tracker::copy_ctor, 0);
    // Sanity: inner scope changed dtor count once
    EXPECT_EQ(Tracker::dtor - 1, dtor_after_inner);
}

// Boundary/Policy: When Destruct=false, no automatic destruction occurs.
// We manually destroy both storages via destruct().
TEST(ObjectStorage_MoveCtor_1106, MoveFromConstructed_ManualDestruct_1106) {
    Tracker::Reset();

    {
        ObjectStorage<Tracker, /*Destruct=*/false> src;
        src.construct(42);

        ObjectStorage<Tracker, /*Destruct=*/false> dst(std::move(src));
        // Still only one move, one value
        EXPECT_EQ(Tracker::value_ctor, 1);
        EXPECT_EQ(Tracker::move_ctor, 1);
        EXPECT_EQ(Tracker::copy_ctor, 0);
        EXPECT_EQ(Tracker::dtor, 0); // no auto destruction for Destruct=false

        // Manual destruction is part of the public interface when Destruct=false
        dst.destruct();
        EXPECT_EQ(Tracker::dtor, 1);

        src.destruct();
        EXPECT_EQ(Tracker::dtor, 2);
    }

    // Leaving scope shouldn't change counts further for Destruct=false
    EXPECT_EQ(Tracker::dtor, 2);
    EXPECT_EQ(Tracker::value_ctor, 1);
    EXPECT_EQ(Tracker::move_ctor, 1);
    EXPECT_EQ(Tracker::copy_ctor, 0);
}

// Exceptional case: If the value type's move-ctor throws, the exception should
// propagate and only the source's contained object will be destroyed (for Destruct=true).
TEST(ObjectStorage_MoveCtor_1106, MoveCtorExceptionPropagates_DestructTrue_1106) {
    Tracker::Reset();

    try {
        ObjectStorage<Tracker, /*Destruct=*/true> src;
        src.construct(123, /*throw_on_move=*/true);

        // Attempting to move-construct should throw
        EXPECT_THROW(
            (void)ObjectStorage<Tracker, /*Destruct=*/true>(std::move(src)),
            std::runtime_error
        );
        // After the failed construction, dst never existed; only src remains.
        // No destruction yet (src still alive in this scope).
        EXPECT_EQ(Tracker::move_ctor, 1);   // one attempt
        EXPECT_EQ(Tracker::dtor, 0);
        EXPECT_EQ(Tracker::copy_ctor, 0);
        EXPECT_EQ(Tracker::value_ctor, 1);
    } catch (...) {
        // Ensure no swallowing; rethrow to let the assertion above handle it.
        throw;
    }

    // Exiting the try-scope destroys the source's contained object exactly once.
    EXPECT_EQ(Tracker::dtor, 1);
    EXPECT_EQ(Tracker::value_ctor, 1);
    EXPECT_EQ(Tracker::move_ctor, 1);
    EXPECT_EQ(Tracker::copy_ctor, 0);
}
