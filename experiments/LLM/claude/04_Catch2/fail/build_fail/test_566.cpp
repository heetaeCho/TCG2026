#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_compiler_capabilities.hpp"

#include <memory>
#include <string>

// Mock IConfig for testing
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

// A simple test listener that we can use with the TypedListenerFactory
class TestListener : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    // Provide a description for the listener
    static std::string getDescription() {
        return "Test listener for unit testing";
    }
};

// Another listener without a getDescription static method behavior variation
class AnotherTestListener : public Catch::EventListenerBase {
public:
    using EventListenerBase::EventListenerBase;

    static std::string getDescription() {
        return "Another test listener";
    }
};

class ListenerRegistrarTest_566 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that TypedListenerFactory::create returns a non-null pointer
TEST_F(ListenerRegistrarTest_566, CreateReturnsNonNullListener_566) {
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory("TestListener");
    MockConfig config;
    
    auto listener = factory.create(&config);
    ASSERT_NE(listener, nullptr);
}

// Test that TypedListenerFactory::getName returns the name passed at construction
TEST_F(ListenerRegistrarTest_566, GetNameReturnsConstructedName_566) {
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory("MyTestListener");
    
    Catch::StringRef name = factory.getName();
    EXPECT_EQ(name, "MyTestListener");
}

// Test that TypedListenerFactory::getDescription returns a valid description string
TEST_F(ListenerRegistrarTest_566, GetDescriptionReturnsValidString_566) {
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory("TestListener");
    
    std::string description = factory.getDescription();
    EXPECT_FALSE(description.empty());
}

// Test that create with a different listener type produces correct object
TEST_F(ListenerRegistrarTest_566, CreateWithAnotherListenerType_566) {
    Catch::ListenerRegistrar<AnotherTestListener>::TypedListenerFactory factory("AnotherListener");
    MockConfig config;
    
    auto listener = factory.create(&config);
    ASSERT_NE(listener, nullptr);
}

// Test getName with empty string
TEST_F(ListenerRegistrarTest_566, GetNameWithEmptyString_566) {
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory("");
    
    Catch::StringRef name = factory.getName();
    EXPECT_EQ(name, "");
}

// Test getName with a long string
TEST_F(ListenerRegistrarTest_566, GetNameWithLongString_566) {
    std::string longName(256, 'x');
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory(longName);
    
    Catch::StringRef name = factory.getName();
    EXPECT_EQ(std::string(name.data(), name.size()), longName);
}

// Test that different factories with the same type but different names have different getName results
TEST_F(ListenerRegistrarTest_566, DifferentFactoriesHaveDifferentNames_566) {
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory1("Listener1");
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory2("Listener2");
    
    EXPECT_NE(factory1.getName(), factory2.getName());
    EXPECT_EQ(factory1.getName(), "Listener1");
    EXPECT_EQ(factory2.getName(), "Listener2");
}

// Test that getDescription for different listener types may differ
TEST_F(ListenerRegistrarTest_566, GetDescriptionDiffersByType_566) {
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory1("Listener1");
    Catch::ListenerRegistrar<AnotherTestListener>::TypedListenerFactory factory2("Listener2");
    
    std::string desc1 = factory1.getDescription();
    std::string desc2 = factory2.getDescription();
    
    // Both should return valid strings; they may or may not differ depending on implementation
    EXPECT_FALSE(desc1.empty());
    EXPECT_FALSE(desc2.empty());
}

// Test create returns unique instances on each call
TEST_F(ListenerRegistrarTest_566, CreateReturnsUniqueInstances_566) {
    Catch::ListenerRegistrar<TestListener>::TypedListenerFactory factory("TestListener");
    MockConfig config;
    
    auto listener1 = factory.create(&config);
    auto listener2 = factory.create(&config);
    
    ASSERT_NE(listener1, nullptr);
    ASSERT_NE(listener2, nullptr);
    EXPECT_NE(listener1.get(), listener2.get());
}

// Test that the factory can be used as an EventListenerFactory pointer (polymorphism)
TEST_F(ListenerRegistrarTest_566, FactoryIsPolymorphicEventListenerFactory_566) {
    auto factory = std::make_unique<Catch::ListenerRegistrar<TestListener>::TypedListenerFactory>("PolyListener");
    
    // Use through base class pointer
    Catch::EventListenerFactory* basePtr = factory.get();
    
    EXPECT_EQ(basePtr->getName(), "PolyListener");
    
    MockConfig config;
    auto listener = basePtr->create(&config);
    ASSERT_NE(listener, nullptr);
}
