#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/reporters/catch_reporter_event_listener.hpp"

namespace {

// A concrete EventListenerFactory for testing
class TestListenerFactory : public Catch::EventListenerFactory {
public:
    Catch::StringRef getDescription() const override {
        return "Test listener for unit testing";
    }

    Catch::Detail::unique_ptr<Catch::EventListener> 
    create(Catch::ReporterConfig&& config) const override {
        // Return nullptr - we just need the factory to be valid
        return Catch::Detail::unique_ptr<Catch::EventListener>(nullptr);
    }
};

class TestListenerFactory2 : public Catch::EventListenerFactory {
public:
    Catch::StringRef getDescription() const override {
        return "Second test listener";
    }

    Catch::Detail::unique_ptr<Catch::EventListener>
    create(Catch::ReporterConfig&& config) const override {
        return Catch::Detail::unique_ptr<Catch::EventListener>(nullptr);
    }
};

} // anonymous namespace

class RegisterListenerImplTest_811 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure Catch2 registry is initialized
    }
};

// Test that registerListenerImpl accepts a valid factory without crashing
TEST_F(RegisterListenerImplTest_811, RegisterValidFactory_811) {
    auto factory = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(
        new TestListenerFactory());
    
    EXPECT_NO_THROW(
        Catch::Detail::registerListenerImpl(std::move(factory))
    );
}

// Test that registerListenerImpl can be called multiple times with different factories
TEST_F(RegisterListenerImplTest_811, RegisterMultipleFactories_811) {
    auto factory1 = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(
        new TestListenerFactory());
    auto factory2 = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(
        new TestListenerFactory2());
    
    EXPECT_NO_THROW(
        Catch::Detail::registerListenerImpl(std::move(factory1))
    );
    EXPECT_NO_THROW(
        Catch::Detail::registerListenerImpl(std::move(factory2))
    );
}

// Test that the unique_ptr is moved (consumed) after registration
TEST_F(RegisterListenerImplTest_811, FactoryOwnershipIsTransferred_811) {
    auto factory = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(
        new TestListenerFactory());
    
    // Verify factory is valid before registration
    ASSERT_TRUE(static_cast<bool>(factory));
    
    Catch::Detail::registerListenerImpl(std::move(factory));
    
    // After move, factory should be null/empty
    EXPECT_FALSE(static_cast<bool>(factory));
}

// Test registering with a factory created from a derived type
TEST_F(RegisterListenerImplTest_811, RegisterDerivedFactory_811) {
    // Create using derived type pointer, moved into base unique_ptr
    Catch::Detail::unique_ptr<Catch::EventListenerFactory> factory(
        new TestListenerFactory());
    
    EXPECT_NO_THROW(
        Catch::Detail::registerListenerImpl(std::move(factory))
    );
}

// Test that registering the same type of factory multiple times works
TEST_F(RegisterListenerImplTest_811, RegisterSameFactoryTypeMultipleTimes_811) {
    for (int i = 0; i < 3; ++i) {
        auto factory = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(
            new TestListenerFactory());
        EXPECT_NO_THROW(
            Catch::Detail::registerListenerImpl(std::move(factory))
        );
    }
}
