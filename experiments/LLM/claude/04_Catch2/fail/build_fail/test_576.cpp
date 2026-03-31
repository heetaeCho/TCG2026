#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <string>
#include <map>
#include <vector>

namespace {

// Mock EventListenerFactory for testing registerListener/getListeners
class MockEventListenerFactory : public Catch::EventListenerFactory {
public:
    Catch::Detail::unique_ptr<Catch::EventListenerBase> create(
        Catch::IConfig const* /*config*/) const override {
        return Catch::Detail::unique_ptr<Catch::EventListenerBase>(nullptr);
    }

    Catch::StringRef getName() const override {
        return "MockListener";
    }

    std::string getDescription() const override {
        return "A mock listener for testing";
    }
};

// Mock ReporterFactory for testing registerReporter/getFactories/create
class MockReporterFactory : public Catch::IReporterFactory {
public:
    Catch::IEventListenerPtr create(Catch::ReporterConfig&& /*config*/) const override {
        return Catch::Detail::unique_ptr<Catch::EventListenerBase>(nullptr);
    }

    std::string getDescription() const override {
        return "A mock reporter factory for testing";
    }
};

} // anonymous namespace

class ReporterRegistryTest_576 : public ::testing::Test {
protected:
    void SetUp() override {
        registry_ = std::make_unique<Catch::ReporterRegistry>();
    }

    void TearDown() override {
        registry_.reset();
    }

    std::unique_ptr<Catch::ReporterRegistry> registry_;
};

// Test that a newly constructed ReporterRegistry has no listeners
TEST_F(ReporterRegistryTest_576, InitiallyHasNoListeners_576) {
    auto const& listeners = registry_->getListeners();
    EXPECT_TRUE(listeners.empty());
}

// Test that a newly constructed ReporterRegistry has no factories
TEST_F(ReporterRegistryTest_576, InitiallyHasNoFactories_576) {
    auto const& factories = registry_->getFactories();
    EXPECT_TRUE(factories.empty());
}

// Test registering a single listener and verifying it's retrievable
TEST_F(ReporterRegistryTest_576, RegisterSingleListener_576) {
    auto factory = Catch::Detail::make_unique<MockEventListenerFactory>();
    registry_->registerListener(std::move(factory));

    auto const& listeners = registry_->getListeners();
    EXPECT_EQ(listeners.size(), 1u);
}

// Test registering multiple listeners
TEST_F(ReporterRegistryTest_576, RegisterMultipleListeners_576) {
    registry_->registerListener(Catch::Detail::make_unique<MockEventListenerFactory>());
    registry_->registerListener(Catch::Detail::make_unique<MockEventListenerFactory>());
    registry_->registerListener(Catch::Detail::make_unique<MockEventListenerFactory>());

    auto const& listeners = registry_->getListeners();
    EXPECT_EQ(listeners.size(), 3u);
}

// Test registering a single reporter factory
TEST_F(ReporterRegistryTest_576, RegisterSingleReporter_576) {
    auto factory = Catch::Detail::make_unique<MockReporterFactory>();
    registry_->registerReporter("TestReporter", std::move(factory));

    auto const& factories = registry_->getFactories();
    EXPECT_EQ(factories.size(), 1u);
    EXPECT_NE(factories.find("TestReporter"), factories.end());
}

// Test registering multiple reporter factories with different names
TEST_F(ReporterRegistryTest_576, RegisterMultipleReporters_576) {
    registry_->registerReporter("Reporter1", Catch::Detail::make_unique<MockReporterFactory>());
    registry_->registerReporter("Reporter2", Catch::Detail::make_unique<MockReporterFactory>());
    registry_->registerReporter("Reporter3", Catch::Detail::make_unique<MockReporterFactory>());

    auto const& factories = registry_->getFactories();
    EXPECT_EQ(factories.size(), 3u);
    EXPECT_NE(factories.find("Reporter1"), factories.end());
    EXPECT_NE(factories.find("Reporter2"), factories.end());
    EXPECT_NE(factories.find("Reporter3"), factories.end());
}

// Test that getFactories returns a map that supports case-insensitive lookup
TEST_F(ReporterRegistryTest_576, FactoriesAreCaseInsensitive_576) {
    registry_->registerReporter("MyReporter", Catch::Detail::make_unique<MockReporterFactory>());

    auto const& factories = registry_->getFactories();
    // The map uses CaseInsensitiveLess, so "myreporter" should find "MyReporter"
    EXPECT_NE(factories.find("myreporter"), factories.end());
    EXPECT_NE(factories.find("MYREPORTER"), factories.end());
    EXPECT_NE(factories.find("MyReporter"), factories.end());
}

// Test that registering listeners does not affect factories
TEST_F(ReporterRegistryTest_576, ListenerRegistrationDoesNotAffectFactories_576) {
    registry_->registerListener(Catch::Detail::make_unique<MockEventListenerFactory>());

    auto const& factories = registry_->getFactories();
    EXPECT_TRUE(factories.empty());
}

// Test that registering reporters does not affect listeners
TEST_F(ReporterRegistryTest_576, ReporterRegistrationDoesNotAffectListeners_576) {
    registry_->registerReporter("Reporter1", Catch::Detail::make_unique<MockReporterFactory>());

    auto const& listeners = registry_->getListeners();
    EXPECT_TRUE(listeners.empty());
}

// Test that listeners are stored in the order they were registered
TEST_F(ReporterRegistryTest_576, ListenersAreInRegistrationOrder_576) {
    auto factory1 = Catch::Detail::make_unique<MockEventListenerFactory>();
    auto factory2 = Catch::Detail::make_unique<MockEventListenerFactory>();

    auto* ptr1 = factory1.get();
    auto* ptr2 = factory2.get();

    registry_->registerListener(std::move(factory1));
    registry_->registerListener(std::move(factory2));

    auto const& listeners = registry_->getListeners();
    ASSERT_EQ(listeners.size(), 2u);
    EXPECT_EQ(listeners[0].get(), ptr1);
    EXPECT_EQ(listeners[1].get(), ptr2);
}

// Test that getFactories and getListeners return const references that remain valid
TEST_F(ReporterRegistryTest_576, ReferencesRemainValidAfterMoreRegistrations_576) {
    registry_->registerListener(Catch::Detail::make_unique<MockEventListenerFactory>());
    auto const& listeners = registry_->getListeners();
    EXPECT_EQ(listeners.size(), 1u);

    registry_->registerListener(Catch::Detail::make_unique<MockEventListenerFactory>());
    // The reference should still be valid and reflect the updated state
    EXPECT_EQ(listeners.size(), 2u);
}

// Test looking up a non-existent reporter factory
TEST_F(ReporterRegistryTest_576, LookupNonExistentReporter_576) {
    registry_->registerReporter("ExistingReporter", Catch::Detail::make_unique<MockReporterFactory>());

    auto const& factories = registry_->getFactories();
    EXPECT_EQ(factories.find("NonExistent"), factories.end());
}
