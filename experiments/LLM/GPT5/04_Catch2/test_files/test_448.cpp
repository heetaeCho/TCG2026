// tests/session_destructor_cleans_up_448.cpp
#include <gtest/gtest.h>

// Forward-declare the class under test and its destructor dependency.
namespace Catch {
    class Session;

    // Test double for the external collaborator invoked by ~Session().
    // This satisfies the linker and lets us verify observable interaction.
    inline int& cleanUpCallCounter_448() {
        static int counter = 0;
        return counter;
    }

    // This replaces/fulfills the symbol that ~Session() calls.
    // It does not simulate internal behavior of Session; it only records calls.
    void cleanUp() {
        ++cleanUpCallCounter_448();
    }
}

// Include the implementation unit that defines ~Session() calling Catch::cleanUp().
#include "Catch2/src/catch2/catch_session.cpp"

// If you have the public header available, you can include it instead of the
// forward declaration above. The tests only rely on constructing/destroying
// Session to observe the destructor's effect.
// #include "Catch2/src/catch2/catch_session.hpp"

class SessionTest_448 : public ::testing::Test {
protected:
    void SetUp() override {
        // Reset the counter before each test for isolation.
        Catch::cleanUpCallCounter_448() = 0;
    }
};

// [TEST_ID: 448]
TEST_F(SessionTest_448, DestructorInvokesCleanUpOnce_448) {
    EXPECT_EQ(Catch::cleanUpCallCounter_448(), 0);

    {
        Catch::Session s;  // On scope exit, ~Session() should call Catch::cleanUp()
        EXPECT_EQ(Catch::cleanUpCallCounter_448(), 0) << "Destructor not run yet";
    }

    EXPECT_EQ(Catch::cleanUpCallCounter_448(), 1)
        << "~Session() must call Catch::cleanUp() exactly once";
}

// [TEST_ID: 448]
TEST_F(SessionTest_448, DestructorInvokesCleanUpOnDelete_448) {
    EXPECT_EQ(Catch::cleanUpCallCounter_448(), 0);

    Catch::Session* s = new Catch::Session();
    EXPECT_EQ(Catch::cleanUpCallCounter_448(), 0) << "Destructor not run yet";
    delete s;  // Should trigger ~Session() -> Catch::cleanUp()

    EXPECT_EQ(Catch::cleanUpCallCounter_448(), 1)
        << "Deleting a heap-allocated Session must invoke Catch::cleanUp() once";
}

// [TEST_ID: 448]
TEST_F(SessionTest_448, MultipleInstancesEachCallCleanUp_448) {
    EXPECT_EQ(Catch::cleanUpCallCounter_448(), 0);

    {
        Catch::Session a;
        Catch::Session b;
        // Neither destructor has run yet inside the scope
        EXPECT_EQ(Catch::cleanUpCallCounter_448(), 0);
    }

    // Both destructors should have run upon leaving the scope
    EXPECT_EQ(Catch::cleanUpCallCounter_448(), 2)
        << "Each Session destruction must call Catch::cleanUp() once";
}
