// File: tests/register_listener_impl_811_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

// ---- Minimal includes / forward decls based on the provided interfaces ----
namespace Catch {

// Forward declaration of types we interact with.
struct EventListenerFactory; // treated as opaque

namespace Detail {
// Minimal unique_ptr compatible with the provided interface (we rely on its observable API)
template <typename T>
using unique_ptr = Catch::Detail::unique_ptr<T>; // assume real header provides it
} // namespace Detail

class IMutableRegistryHub {
public:
    virtual ~IMutableRegistryHub() = default;
    virtual void registerListener(Detail::unique_ptr<EventListenerFactory> factory) = 0;
    // Other virtuals omitted (not used in these tests)
};

// Function under test depends on this accessor.
// We provide a link-seam so the SUT calls our test instance.
IMutableRegistryHub& getMutableRegistryHub();

// Function under test (from partial code)
namespace Detail {
    void registerListenerImpl(Detail::unique_ptr<EventListenerFactory> listenerFactory);
}

} // namespace Catch

// ---- Test-only support types & seams ----
namespace Catch {

// A concrete, trivially constructible test factory type.
// We do not rely on any behavior — construction & identity only.
struct EventListenerFactory {
    virtual ~EventListenerFactory() = default;
};

// Global seam target that our getMutableRegistryHub() will return.
static Catch::IMutableRegistryHub* g_mockHub_for_tests = nullptr;

// Provide the seam used by the implementation under test.
Catch::IMutableRegistryHub& getMutableRegistryHub() {
    // In tests we guarantee this is set before calling SUT.
    return *g_mockHub_for_tests;
}

} // namespace Catch

// Mock hub verifying the outward interaction from registerListenerImpl.
class MockMutableRegistryHub_811 : public Catch::IMutableRegistryHub {
public:
    // GMock supports move-only types by value as of newer releases.
    MOCK_METHOD(void, registerListener,
                (Catch::Detail::unique_ptr<Catch::EventListenerFactory> factory),
                (override));
};

// Small helper to make a unique_ptr without exposing internals
template <typename T, typename... Args>
Catch::Detail::unique_ptr<T> MakeUnique_811(Args&&... args) {
    return Catch::Detail::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

// --------------------------- TESTS ---------------------------

class RegisterListenerImplTest_811 : public ::testing::Test {
protected:
    MockMutableRegistryHub_811 mockHub{};
    void SetUp() override {
        Catch::g_mockHub_for_tests = &mockHub;
    }
    void TearDown() override {
        Catch::g_mockHub_for_tests = nullptr;
    }
};

// Normal operation: forwards a non-null factory to the registry via move.
TEST_F(RegisterListenerImplTest_811, ForwardsFactoryToRegistry_811) {
    using ::testing::Invoke;
    using ::testing::_;
    // Prepare a distinct pointer identity we can check inside the expectation.
    auto raw_ptr = new Catch::EventListenerFactory();
    Catch::Detail::unique_ptr<Catch::EventListenerFactory> uptr(raw_ptr);

    EXPECT_CALL(mockHub, registerListener(_))
        .WillOnce(Invoke([&](Catch::Detail::unique_ptr<Catch::EventListenerFactory> received) {
            // Observables: we received exactly the pointer that was provided.
            EXPECT_NE(received.get(), nullptr);
            EXPECT_EQ(received.get(), raw_ptr);
            // Ownership should transfer; releasing here avoids double delete.
            (void)received.release();
        }));

    // Call the SUT — it should fetch the hub and move the factory into registerListener.
    Catch::Detail::registerListenerImpl(std::move(uptr));
    // Note: uptr is moved at the call site; we cannot check it post-call without
    // relying on internal state of unique_ptr — which we avoid. We only verified
    // what the hub received, which is observable via the mock.
}

// Boundary: passing a null factory should still call registerListener (with null).
TEST_F(RegisterListenerImplTest_811, ForwardsNullFactory_811) {
    using ::testing::Invoke;
    using ::testing::_;

    EXPECT_CALL(mockHub, registerListener(_))
        .WillOnce(Invoke([](Catch::Detail::unique_ptr<Catch::EventListenerFactory> received) {
            EXPECT_EQ(received.get(), nullptr);
        }));

    Catch::Detail::unique_ptr<Catch::EventListenerFactory> nullFactory(nullptr);
    Catch::Detail::registerListenerImpl(std::move(nullFactory));
}

// Exceptional path (observable): if the registry throws, the exception propagates.
TEST_F(RegisterListenerImplTest_811, PropagatesRegistryExceptions_811) {
    using ::testing::Throw;
    using ::testing::_;

    EXPECT_CALL(mockHub, registerListener(_))
        .WillOnce(Throw(std::runtime_error("boom")));

    auto factory = MakeUnique_811<Catch::EventListenerFactory>();

    EXPECT_THROW(
        Catch::Detail::registerListenerImpl(std::move(factory)),
        std::runtime_error
    );
}

// Interaction count: ensure SUT queries the hub exactly once and calls registerListener once.
TEST_F(RegisterListenerImplTest_811, CallsHubAndRegistersExactlyOnce_811) {
    using ::testing::_;
    using ::testing::Invoke;

    // We can't directly count getMutableRegistryHub() calls without extra hooks,
    // but an indirect observable is that exactly one registerListener call occurs.
    EXPECT_CALL(mockHub, registerListener(_))
        .Times(1)
        .WillOnce(Invoke([](Catch::Detail::unique_ptr<Catch::EventListenerFactory> /*received*/) {}));

    auto factory = MakeUnique_811<Catch::EventListenerFactory>();
    Catch::Detail::registerListenerImpl(std::move(factory));
}
