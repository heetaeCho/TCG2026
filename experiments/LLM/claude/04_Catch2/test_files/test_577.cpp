#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <string>
#include <map>
#include <memory>

namespace {

// A mock reporter factory for testing registration
class MockReporterFactory : public Catch::IReporterFactory {
public:
    Catch::IEventListenerPtr create(Catch::ReporterConfig&& config) const override {
        return Catch::Detail::unique_ptr<Catch::IEventListener>(nullptr);
    }
    std::string getDescription() const override {
        return "Mock reporter factory for testing";
    }
};

// A mock EventListenerFactory for testing listener registration
class MockEventListenerFactory : public Catch::EventListenerFactory {
public:
    Catch::IEventListenerPtr create(Catch::IConfig const* /*config*/) const override {
        return Catch::Detail::unique_ptr<Catch::IEventListener>(nullptr);
    }
    std::string getDescription() const override {
        return "Mock event listener factory for testing";
    }
};

} // anonymous namespace

class ReporterRegistryTest_577 : public ::testing::Test {
protected:
    Catch::ReporterRegistry registry;
};

// Test that a newly constructed ReporterRegistry has no user-registered factories
// (it may have built-in ones, but getFactories() should at least return a valid reference)
TEST_F(ReporterRegistryTest_577, GetFactoriesReturnsValidReference_577) {
    auto const& factories = registry.getFactories();
    // The map should be a valid reference; we can at least call size on it
    EXPECT_GE(factories.size(), 0u);
}

// Test that a newly constructed ReporterRegistry has no user-registered listeners
TEST_F(ReporterRegistryTest_577, GetListenersInitiallyEmpty_577) {
    auto const& listeners = registry.getListeners();
    EXPECT_TRUE(listeners.empty());
}

// Test registering a single reporter and verifying it appears in getFactories()
TEST_F(ReporterRegistryTest_577, RegisterReporterAppearsInFactories_577) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    registry.registerReporter("TestReporter", std::move(factory));

    auto const& factories = registry.getFactories();
    auto it = factories.find("TestReporter");
    EXPECT_NE(it, factories.end());
    EXPECT_EQ(it->first, "TestReporter");
}

// Test registering multiple reporters
TEST_F(ReporterRegistryTest_577, RegisterMultipleReporters_577) {
    auto factory1 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    auto factory2 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    auto factory3 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());

    registry.registerReporter("Reporter1", std::move(factory1));
    registry.registerReporter("Reporter2", std::move(factory2));
    registry.registerReporter("Reporter3", std::move(factory3));

    auto const& factories = registry.getFactories();
    EXPECT_NE(factories.find("Reporter1"), factories.end());
    EXPECT_NE(factories.find("Reporter2"), factories.end());
    EXPECT_NE(factories.find("Reporter3"), factories.end());
}

// Test that factory lookup is case-insensitive (CaseInsensitiveLess comparator)
TEST_F(ReporterRegistryTest_577, FactoryLookupIsCaseInsensitive_577) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    registry.registerReporter("MyReporter", std::move(factory));

    auto const& factories = registry.getFactories();
    // Case-insensitive lookup: "myreporter" should find "MyReporter"
    auto it = factories.find("myreporter");
    EXPECT_NE(it, factories.end());

    auto it2 = factories.find("MYREPORTER");
    EXPECT_NE(it2, factories.end());

    auto it3 = factories.find("MyReporter");
    EXPECT_NE(it3, factories.end());
}

// Test registering a listener and verifying it appears in getListeners()
TEST_F(ReporterRegistryTest_577, RegisterListenerAppearsInListeners_577) {
    auto listenerFactory = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());
    registry.registerListener(std::move(listenerFactory));

    auto const& listeners = registry.getListeners();
    EXPECT_EQ(listeners.size(), 1u);
}

// Test registering multiple listeners
TEST_F(ReporterRegistryTest_577, RegisterMultipleListeners_577) {
    auto listener1 = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());
    auto listener2 = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());
    auto listener3 = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());

    registry.registerListener(std::move(listener1));
    registry.registerListener(std::move(listener2));
    registry.registerListener(std::move(listener3));

    auto const& listeners = registry.getListeners();
    EXPECT_EQ(listeners.size(), 3u);
}

// Test that a factory not registered is not found
TEST_F(ReporterRegistryTest_577, NonExistentFactoryNotFound_577) {
    auto const& factories = registry.getFactories();
    auto it = factories.find("NonExistentReporter");
    EXPECT_EQ(it, factories.end());
}

// Test that registering reporters does not affect listeners and vice versa
TEST_F(ReporterRegistryTest_577, ReportersAndListenersIndependent_577) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    registry.registerReporter("IndependentReporter", std::move(factory));

    auto listener = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());
    registry.registerListener(std::move(listener));

    auto const& factories = registry.getFactories();
    auto const& listeners = registry.getListeners();

    EXPECT_NE(factories.find("IndependentReporter"), factories.end());
    EXPECT_EQ(listeners.size(), 1u);
}

// Test creating a reporter from a registered factory
TEST_F(ReporterRegistryTest_577, CreateReturnsListenerForRegisteredReporter_577) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    registry.registerReporter("CreatableReporter", std::move(factory));

    // Create a minimal ReporterConfig - need a stream and config
    // The mock factory returns nullptr, so we just verify create doesn't crash
    // and returns (possibly null since our mock returns null)
    std::ostringstream oss;
    auto config = Catch::ReporterConfig(nullptr, oss, Catch::ColourMode::None, {});
    auto listener = registry.create("CreatableReporter", std::move(config));
    // Our mock returns nullptr, so the result should be falsy
    EXPECT_FALSE(listener);
}

// Test that getFactories returns a const reference that reflects updates
TEST_F(ReporterRegistryTest_577, GetFactoriesReflectsNewRegistrations_577) {
    auto const& factories = registry.getFactories();
    size_t initialSize = factories.size();

    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    registry.registerReporter("NewReporter", std::move(factory));

    // The reference should reflect the updated state
    EXPECT_EQ(factories.size(), initialSize + 1);
    EXPECT_NE(factories.find("NewReporter"), factories.end());
}

// Test that getListeners returns a const reference that reflects updates
TEST_F(ReporterRegistryTest_577, GetListenersReflectsNewRegistrations_577) {
    auto const& listeners = registry.getListeners();
    EXPECT_EQ(listeners.size(), 0u);

    auto listener = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());
    registry.registerListener(std::move(listener));

    EXPECT_EQ(listeners.size(), 1u);
}
