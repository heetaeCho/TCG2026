// File: test_singleton_281.cpp

#include <gtest/gtest.h>
#include <type_traits>
#include <limits>

// Include the header under test (path from the prompt)
#include "Catch2/src/catch2/internal/catch_singletons.hpp"

namespace {

// Public read-only interface (observable via get())
struct ICounter {
    virtual ~ICounter() = default;
    virtual int value() const = 0;
};

// Public mutable interface (observable via getMutable())
struct IMutableCounter : ICounter {
    virtual void set(int v) = 0;
    virtual void add(int delta) = 0;
};

// Concrete implementation used only as a collaborator to instantiate the template.
// We do NOT reimplement or assume any Singleton internals.
struct CounterImpl : IMutableCounter {
    int v_{0};
    int value() const override { return v_; }
    void set(int v) override { v_ = v; }
    void add(int d) override { v_ += d; }
};

// Alias of the class under test with the above types.
using CounterSingleton = Catch::Singleton<CounterImpl, ICounter, IMutableCounter>;

} // namespace

// Test fixture: reset observable state between tests using the public mutable API
class SingletonTest_281 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure a clean, known observable state before each test.
        IMutableCounter& m = CounterSingleton::getMutable();
        m.set(0);
    }
};

// ---- Tests ----

// Normal operation: mutations through getMutable() are visible via get() (const view).
TEST_F(SingletonTest_281, MutationVisibleViaGet_281) {
    IMutableCounter& m = CounterSingleton::getMutable();
    const ICounter& c = CounterSingleton::get();

    m.set(42);
    EXPECT_EQ(c.value(), 42);

    m.add(8);
    EXPECT_EQ(c.value(), 50);
}

// Singleton behavior: getMutable() returns the same instance across calls (stable identity).
TEST_F(SingletonTest_281, GetMutableReturnsStableReference_281) {
    IMutableCounter* p1 = &CounterSingleton::getMutable();
    IMutableCounter* p2 = &CounterSingleton::getMutable();
    EXPECT_EQ(p1, p2) << "getMutable() should return the same object each time";
}

// Interface consistency: get() and getMutable() refer to the SAME most-derived object.
TEST_F(SingletonTest_281, GetAndGetMutableReferToSameObject_281) {
    // Use dynamic_cast<void*> to compare the address of the most-derived object.
    const ICounter& c = CounterSingleton::get();
    IMutableCounter& m = CounterSingleton::getMutable();

    void* mostDerivedFromConst = dynamic_cast<void*>(const_cast<ICounter*>(&c));
    void* mostDerivedFromMutable = dynamic_cast<void*>(&m);

    EXPECT_EQ(mostDerivedFromConst, mostDerivedFromMutable)
        << "get() and getMutable() must reference the same singleton instance";
}

// Aliasing/boundary-ish check: multiple references to mutable interface alias the same instance.
TEST_F(SingletonTest_281, MultipleMutableReferencesAlias_281) {
    IMutableCounter& a = CounterSingleton::getMutable();
    IMutableCounter& b = CounterSingleton::getMutable();

    a.set(std::numeric_limits<int>::max() - 1);
    b.add(1);
    EXPECT_EQ(a.value(), std::numeric_limits<int>::max());
    EXPECT_EQ(b.value(), std::numeric_limits<int>::max());
}

// Compile-time interface checks: exact return types of get() / getMutable().
TEST_F(SingletonTest_281, ReturnTypeConformance_281) {
    // get() must be 'const ICounter&'
    static_assert(std::is_same_v<decltype(CounterSingleton::get()), const ICounter&>,
                  "get() should return 'const InterfaceT&'");

    // getMutable() must be 'IMutableCounter&'
    static_assert(std::is_same_v<decltype(CounterSingleton::getMutable()), IMutableCounter&>,
                  "getMutable() should return 'MutableInterfaceT&'");

    SUCCEED(); // If it compiles, the static_asserts passed.
}
