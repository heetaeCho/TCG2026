// TestInvokerFixture_tests_429.cpp
#include <gtest/gtest.h>
#include <stdexcept>

// If you include the real header in your build, prefer:
//   #include "catch2/internal/catch_test_registry.hpp"
// For these tests we only rely on the public interface that is visible to users:
namespace Catch {
struct ITestInvoker {
    virtual ~ITestInvoker() = default;
    virtual void prepareTestCase() = 0;
    virtual void tearDownTestCase() = 0;
    virtual void invoke() const = 0;
};

// The class under test (decl only; implemented in the production code).
template <typename C>
class TestInvokerFixture : public ITestInvoker {
public:
    // Binds a const, nullary member function of C
    constexpr TestInvokerFixture(void (C::*testAsMethod)() const) noexcept
        : m_testAsMethod(testAsMethod) {}
    void prepareTestCase() override;
    void tearDownTestCase() override;
    void invoke() const override;
private:
    void (C::*m_testAsMethod)() const;
};
} // namespace Catch

// ---------- Test helpers (external to the class under test) ----------

struct InstanceTracker {
    static int ctor_count;
    static int dtor_count;
    static int live_count;
    static int last_ctor_id;
    static int next_id;

    int id{};
    InstanceTracker() : id(next_id++) {
        ++ctor_count;
        ++live_count;
        last_ctor_id = id;
    }
    InstanceTracker(const InstanceTracker&) = delete;
    InstanceTracker& operator=(const InstanceTracker&) = delete;
    ~InstanceTracker() {
        ++dtor_count;
        --live_count;
    }
};
int InstanceTracker::ctor_count = 0;
int InstanceTracker::dtor_count = 0;
int InstanceTracker::live_count = 0;
int InstanceTracker::last_ctor_id = -1;
int InstanceTracker::next_id = 1;

// Probe that records how many times the bound method was invoked.
// Must be default-constructible and have a const nullary method.
struct CallProbe : InstanceTracker {
    static int called;
    void run() const { ++called; }
};
int CallProbe::called = 0;

// A type whose bound method throws, to observe exception propagation.
struct ThrowingProbe : InstanceTracker {
    void run() const { throw std::runtime_error("boom"); }
};

// Convenience alias for the class under test
template <typename C>
using Invoker = Catch::TestInvokerFixture<C>;

// ---------- Tests ----------

TEST(TestInvokerFixtureTest_429, PrepareCreatesOneFixtureInstance_429) {
    // Reset counters
    InstanceTracker::ctor_count = InstanceTracker::dtor_count =
        InstanceTracker::live_count = 0;

    Invoker<CallProbe> inv{ &CallProbe::run };
    EXPECT_EQ(InstanceTracker::live_count, 0);

    inv.prepareTestCase();
    EXPECT_EQ(InstanceTracker::live_count, 1);
    EXPECT_EQ(InstanceTracker::ctor_count, 1);
    EXPECT_EQ(InstanceTracker::dtor_count, 0);
}

TEST(TestInvokerFixtureTest_429, TearDownDestroysFixtureInstance_429) {
    // Reset counters
    InstanceTracker::ctor_count = InstanceTracker::dtor_count =
        InstanceTracker::live_count = 0;

    Invoker<CallProbe> inv{ &CallProbe::run };
    inv.prepareTestCase();
    ASSERT_EQ(InstanceTracker::live_count, 1);

    inv.tearDownTestCase();
    EXPECT_EQ(InstanceTracker::live_count, 0);
    EXPECT_EQ(InstanceTracker::dtor_count, 1);
}

TEST(TestInvokerFixtureTest_429, InvokeCallsBoundConstMethod_OncePerCall_429) {
    // Reset counters
    InstanceTracker::ctor_count = InstanceTracker::dtor_count =
        InstanceTracker::live_count = 0;
    CallProbe::called = 0;

    Invoker<CallProbe> inv{ &CallProbe::run };
    inv.prepareTestCase();

    inv.invoke();
    EXPECT_EQ(CallProbe::called, 1);

    inv.invoke();
    EXPECT_EQ(CallProbe::called, 2);

    inv.tearDownTestCase();
    EXPECT_EQ(InstanceTracker::live_count, 0);
}

TEST(TestInvokerFixtureTest_429, PrepareTwiceReplacesFixtureInstance_429) {
    // Reset counters
    InstanceTracker::ctor_count = InstanceTracker::dtor_count =
        InstanceTracker::live_count = 0;
    InstanceTracker::last_ctor_id = -1;

    Invoker<CallProbe> inv{ &CallProbe::run };

    inv.prepareTestCase();
    const int first_id = InstanceTracker::last_ctor_id;
    ASSERT_EQ(InstanceTracker::live_count, 1);

    inv.prepareTestCase(); // Preparing again should tear down previous & create new
    const int second_id = InstanceTracker::last_ctor_id;

    EXPECT_EQ(InstanceTracker::live_count, 1);     // still exactly one live instance
    EXPECT_EQ(InstanceTracker::ctor_count, 2);     // constructed twice
    EXPECT_EQ(InstanceTracker::dtor_count, 1);     // old instance destroyed
    EXPECT_NE(first_id, second_id);                // two distinct instances
}

TEST(TestInvokerFixtureTest_429, ExceptionsFromBoundMethodPropagate_429) {
    // Reset counters
    InstanceTracker::ctor_count = InstanceTracker::dtor_count =
        InstanceTracker::live_count = 0;

    Invoker<ThrowingProbe> inv{ &ThrowingProbe::run };
    inv.prepareTestCase();

    EXPECT_THROW(inv.invoke(), std::runtime_error);

    inv.tearDownTestCase();
    EXPECT_EQ(InstanceTracker::live_count, 0);
}

TEST(TestInvokerFixtureTest_429, FixtureIsDestroyedWhenInvokerGoesOutOfScope_429) {
    // Reset counters
    InstanceTracker::ctor_count = InstanceTracker::dtor_count =
        InstanceTracker::live_count = 0;

    {
        Invoker<CallProbe> inv{ &CallProbe::run };
        inv.prepareTestCase();
        ASSERT_EQ(InstanceTracker::live_count, 1);
        // No explicit tearDown here on purpose; rely on RAII of the invoker
    }
    // When invoker is destroyed, any held fixture should be released
    EXPECT_EQ(InstanceTracker::live_count, 0);
    EXPECT_EQ(InstanceTracker::dtor_count, 1);
}
