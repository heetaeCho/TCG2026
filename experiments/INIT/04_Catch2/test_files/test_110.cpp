// IStream_test_110.cpp
#include <gtest/gtest.h>
#include <ostream>

// Include the provided header (adjust include path as needed in your repo)
#include "Catch2/src/catch2/internal/catch_istream.hpp"

using namespace Catch;

class IStreamTest_110 : public ::testing::Test {};

// Verifies the documented/observable default behavior.
TEST_F(IStreamTest_110, DefaultIsNotConsole_110) {
    IStream s;
    EXPECT_FALSE(s.isConsole());
}

// Verifies overriding behavior via polymorphism without relying on internals.
TEST_F(IStreamTest_110, OverrideIsConsoleTrue_110) {
    struct Derived : IStream {
        bool isConsole() const override { return true; }
    } d;

    IStream& base = d;
    EXPECT_TRUE(base.isConsole());
}

// Verifies destructor is virtual by observing derived destructor invocation
// when deleting through a base pointer (no internal state assumptions).
TEST_F(IStreamTest_110, VirtualDestructorInvokedThroughBase_110) {
    struct Derived : IStream {
        explicit Derived(bool& destroyed) : destroyed_(destroyed) {}
        ~Derived() override { destroyed_ = true; }
        bool& destroyed_;
    };

    bool destroyed = false;
    IStream* p = new Derived(destroyed);
    delete p;  // delete via base pointer should call Derived::~Derived()
    EXPECT_TRUE(destroyed);
}

// Confirms const-correctness of the observable method.
TEST_F(IStreamTest_110, IsConsoleCallableOnConstObject_110) {
    const IStream s;
    EXPECT_FALSE(s.isConsole());
}
