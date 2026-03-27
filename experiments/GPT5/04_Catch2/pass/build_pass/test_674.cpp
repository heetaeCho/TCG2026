// File: tests/test_cleanupSingletons_674.cpp
#include <gtest/gtest.h>
#include <atomic>

//
// If your project has the public header for these, include it instead, e.g.:
//   #include "catch2/internal/catch_singletons.hpp"
// The following are interface-only forward declarations to avoid relying on internals.
//
namespace Catch {
    struct ISingleton { virtual ~ISingleton() = default; };
    void addSingleton(ISingleton* singleton);
    void cleanupSingletons();
}

// A simple singleton whose destructor updates a global counter.
// This is an observable side effect that lets us verify deletion happened,
// without relying on internal state of the singleton storage.
class DtorRecorder : public Catch::ISingleton {
public:
    explicit DtorRecorder(int id) : id_(id) {}
    ~DtorRecorder() override {
        (void)id_;
        ++s_dtorCount;
    }
    static void reset() { s_dtorCount.store(0); }
    static int count() { return s_dtorCount.load(); }
private:
    int id_;
    static std::atomic<int> s_dtorCount;
};

std::atomic<int> DtorRecorder::s_dtorCount{0};

class CleanupSingletonsTest_674 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure a clean slate before each test; calling cleanup on an
        // empty or uninitialized store should be safe and observable
        // as "no crash / no extra destructor calls".
        DtorRecorder::reset();
        Catch::cleanupSingletons();
    }
    void TearDown() override {
        // Make sure nothing leaks between tests.
        Catch::cleanupSingletons();
    }
};

// [Normal operation]
// When singletons were registered, cleanupSingletons deletes them (calls dtors).
TEST_F(CleanupSingletonsTest_674, DeletesAllRegisteredSingletons_674) {
    // Arrange: register a few instances
    Catch::addSingleton(new DtorRecorder(1));
    Catch::addSingleton(new DtorRecorder(2));
    Catch::addSingleton(new DtorRecorder(3));

    // Act
    Catch::cleanupSingletons();

    // Assert: all destructors ran exactly once each
    EXPECT_EQ(DtorRecorder::count(), 3);
}

// [Boundary condition]
// Calling cleanupSingletons when there are no registered singletons should be safe (no crash).
TEST_F(CleanupSingletonsTest_674, NoopWhenEmpty_674) {
    // Act
    Catch::cleanupSingletons();

    // Assert: nothing was destroyed
    EXPECT_EQ(DtorRecorder::count(), 0);
}

// [Boundary + Idempotency]
// Calling cleanupSingletons more than once should not cause double deletes or crashes.
TEST_F(CleanupSingletonsTest_674, IdempotentMultipleCalls_674) {
    // Arrange
    Catch::addSingleton(new DtorRecorder(10));
    Catch::addSingleton(new DtorRecorder(11));

    // Act: First cleanup should delete both
    Catch::cleanupSingletons();
    int afterFirst = DtorRecorder::count();

    // Second cleanup should do nothing further (and must not crash)
    Catch::cleanupSingletons();

    // Assert
    EXPECT_EQ(afterFirst, 2);
    EXPECT_EQ(DtorRecorder::count(), 2);
}

// [Post-cleanup reuse]
// After cleanup, registering new singletons should still work and be cleanable again.
TEST_F(CleanupSingletonsTest_674, ReuseAfterCleanup_674) {
    // Arrange: initial registration and cleanup
    Catch::addSingleton(new DtorRecorder(21));
    Catch::addSingleton(new DtorRecorder(22));
    Catch::cleanupSingletons();
    EXPECT_EQ(DtorRecorder::count(), 2);

    // Reset the observable counter to clearly attribute subsequent deletions
    DtorRecorder::reset();

    // Act: register again after prior cleanup and clean once more
    Catch::addSingleton(new DtorRecorder(23));
    Catch::addSingleton(new DtorRecorder(24));
    Catch::addSingleton(new DtorRecorder(25));
    Catch::cleanupSingletons();

    // Assert: only the second batch was destroyed this time
    EXPECT_EQ(DtorRecorder::count(), 3);
}
