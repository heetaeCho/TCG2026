#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>

// Mock reporter factory
class MockReporterFactory : public Catch::IReporterFactory {
public:
    Catch::IEventListenerPtr create(Catch::ReporterConfig&& config) const override {
        return Catch::IEventListenerPtr(nullptr);
    }
    std::string getDescription() const override {
        return "Mock reporter factory";
    }
};

// Mock EventListenerFactory
class MockEventListenerFactory : public Catch::EventListenerFactory {
public:
    Catch::IEventListenerPtr create(Catch::IConfig const* config) const override {
        return Catch::IEventListenerPtr(nullptr);
    }
    std::string getDescription() const override {
        return "Mock event listener factory";
    }
};

class ReporterRegistryTest_575 : public ::testing::Test {
protected:
    Catch::ReporterRegistry registry;
};

// Test that a newly created registry has no custom factories
TEST_F(ReporterRegistryTest_575, InitialFactoriesEmpty_575) {
    auto const& factories = registry.getFactories();
    EXPECT_TRUE(factories.empty());
}

// Test that a newly created registry has no listeners
TEST_F(ReporterRegistryTest_575, InitialListenersEmpty_575) {
    auto const& listeners = registry.getListeners();
    EXPECT_TRUE(listeners.empty());
}

// Test registering a reporter with a valid name
TEST_F(ReporterRegistryTest_575, RegisterReporterValidName_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_NO_THROW(registry.registerReporter("myReporter", std::move(factory)));

    auto const& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 1u);
    EXPECT_TRUE(factories.count("myReporter") > 0);
}

// Test that registering a reporter with "::" in the name throws
TEST_F(ReporterRegistryTest_575, RegisterReporterWithDoubleColonThrows_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_THROW(registry.registerReporter("my::reporter", std::move(factory)), std::runtime_error);
}

// Test that registering a duplicate reporter name throws
TEST_F(ReporterRegistryTest_575, RegisterDuplicateReporterThrows_575) {
    auto factory1 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    auto factory2 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());

    EXPECT_NO_THROW(registry.registerReporter("duplicate", std::move(factory1)));
    EXPECT_THROW(registry.registerReporter("duplicate", std::move(factory2)), std::runtime_error);
}

// Test registering multiple reporters with different names
TEST_F(ReporterRegistryTest_575, RegisterMultipleReporters_575) {
    auto factory1 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    auto factory2 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    auto factory3 = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());

    registry.registerReporter("reporter1", std::move(factory1));
    registry.registerReporter("reporter2", std::move(factory2));
    registry.registerReporter("reporter3", std::move(factory3));

    auto const& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 3u);
}

// Test registering a listener
TEST_F(ReporterRegistryTest_575, RegisterListener_575) {
    auto listener = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());
    EXPECT_NO_THROW(registry.registerListener(std::move(listener)));

    auto const& listeners = registry.getListeners();
    EXPECT_EQ(listeners.size(), 1u);
}

// Test registering multiple listeners
TEST_F(ReporterRegistryTest_575, RegisterMultipleListeners_575) {
    auto listener1 = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());
    auto listener2 = Catch::Detail::unique_ptr<Catch::EventListenerFactory>(new MockEventListenerFactory());

    registry.registerListener(std::move(listener1));
    registry.registerListener(std::move(listener2));

    auto const& listeners = registry.getListeners();
    EXPECT_EQ(listeners.size(), 2u);
}

// Test that name with "::" at the beginning throws
TEST_F(ReporterRegistryTest_575, RegisterReporterDoubleColonAtBeginning_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_THROW(registry.registerReporter("::reporter", std::move(factory)), std::runtime_error);
}

// Test that name with "::" at the end throws
TEST_F(ReporterRegistryTest_575, RegisterReporterDoubleColonAtEnd_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_THROW(registry.registerReporter("reporter::", std::move(factory)), std::runtime_error);
}

// Test that a single colon is allowed in reporter name
TEST_F(ReporterRegistryTest_575, RegisterReporterSingleColonAllowed_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_NO_THROW(registry.registerReporter("my:reporter", std::move(factory)));

    auto const& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 1u);
}

// Test registering an empty name (should be allowed as no "::" present)
TEST_F(ReporterRegistryTest_575, RegisterReporterEmptyName_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_NO_THROW(registry.registerReporter("", std::move(factory)));

    auto const& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 1u);
}

// Test that name with multiple "::" throws
TEST_F(ReporterRegistryTest_575, RegisterReporterMultipleDoubleColonThrows_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_THROW(registry.registerReporter("a::b::c", std::move(factory)), std::runtime_error);
}

// Test that getFactories returns correct factory pointer
TEST_F(ReporterRegistryTest_575, GetFactoriesReturnsCorrectFactory_575) {
    auto rawPtr = new MockReporterFactory();
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(rawPtr);
    registry.registerReporter("test", std::move(factory));

    auto const& factories = registry.getFactories();
    auto it = factories.find("test");
    ASSERT_NE(it, factories.end());
    EXPECT_EQ(it->second.get(), rawPtr);
}

// Test that just "::" as name throws
TEST_F(ReporterRegistryTest_575, RegisterReporterOnlyDoubleColonThrows_575) {
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(new MockReporterFactory());
    EXPECT_THROW(registry.registerReporter("::", std::move(factory)), std::runtime_error);
}
