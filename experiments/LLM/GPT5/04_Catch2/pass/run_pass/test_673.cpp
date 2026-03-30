// File: tests/add_singleton_673_tests.cpp

#include <gtest/gtest.h>
#include "catch2/internal/catch_singletons.hpp"

// Forward declare the function under test if it's not already declared by the header.
namespace Catch {
    void addSingleton(ISingleton* singleton);
}

// A simple concrete singleton to observe destruction as an externally visible effect.
// We only rely on the public (virtual) destructor of ISingleton.
struct DummySingleton_673 : Catch::ISingleton {
    static int dtor_calls;
    ~DummySingleton_673() override { ++dtor_calls; }
};
int DummySingleton_673::dtor_calls = 0;

class AddSingletonTest_673 : public ::testing::Test {
protected:
    void SetUp() override { DummySingleton_673::dtor_calls = 0; }
};

// Normal operation: adding a valid singleton pointer should not immediately destroy it.
TEST_F(AddSingletonTest_673, AddValidPointerDoesNotDestroyImmediately_673) {
    auto* s = new DummySingleton_673{};
    EXPECT_EQ(DummySingleton_673::dtor_calls, 0);

    // Act – no assumptions about internal storage; just call the API.
    Catch::addSingleton(s);

    // Assert: instance is not destroyed as a result of addSingleton.
    EXPECT_EQ(DummySingleton_673::dtor_calls, 0);

    // Clean up: deleting should invoke the destructor exactly once.
    delete s;
    EXPECT_EQ(DummySingleton_673::dtor_calls, 1);
}

// Boundary condition: passing nullptr should be a no-op (no throw / crash).
TEST_F(AddSingletonTest_673, AcceptsNullptrGracefully_673) {
    // Expect no exceptions or crashes when adding nullptr.
    // (We cannot assert internal state; we just verify it doesn't destroy anything.)
    ASSERT_NO_FATAL_FAILURE(Catch::addSingleton(nullptr));
    EXPECT_EQ(DummySingleton_673::dtor_calls, 0);
}

// Normal + interaction between multiple items: adding multiple distinct instances
// should not destroy any of them immediately, and each should still be deletable once.
TEST_F(AddSingletonTest_673, AddMultiplePointersNoImmediateDestruction_673) {
    auto* a = new DummySingleton_673{};
    auto* b = new DummySingleton_673{};

    Catch::addSingleton(a);
    Catch::addSingleton(b);

    // No destruction should have happened yet.
    EXPECT_EQ(DummySingleton_673::dtor_calls, 0);

    // Clean up both; each should be destroyed exactly once overall.
    delete a;
    delete b;
    EXPECT_EQ(DummySingleton_673::dtor_calls, 2);
}
