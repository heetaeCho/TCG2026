#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/catch_reporter_registrars.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"
#include "catch2/catch_config.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

#include <string>
#include <map>
#include <vector>
#include <sstream>

// A minimal mock/stub reporter for testing
class StubReporter : public Catch::IEventListener {
public:
    StubReporter(Catch::ReporterConfig const& config)
        : IEventListener(config.fullConfig()) {}

    void testRunStarting(Catch::TestRunInfo const&) override {}
    void testCaseStarting(Catch::TestCaseInfo const&) override {}
    void testCasePartialStarting(Catch::TestCaseInfo const&, uint64_t) override {}
    void sectionStarting(Catch::SectionInfo const&) override {}
    void assertionStarting(Catch::AssertionInfo const&) override {}
    void assertionEnded(Catch::AssertionStats const&) override {}
    void sectionEnded(Catch::SectionStats const&) override {}
    void testCasePartialEnded(Catch::TestCaseStats const&, uint64_t) override {}
    void testCaseEnded(Catch::TestCaseStats const&) override {}
    void testRunEnded(Catch::TestRunStats const&) override {}
    void skipTest(Catch::TestCaseInfo const&) override {}
    void listReporters(std::vector<Catch::ReporterDescription> const&) override {}
    void listListeners(std::vector<Catch::ListenerDescription> const&) override {}
    void listTests(std::vector<Catch::TestCaseHandle> const&) override {}
    void listTags(std::vector<Catch::TagInfo> const&) override {}
    void noMatchingTestCases(Catch::StringRef) override {}
    void reportInvalidTestSpec(Catch::StringRef) override {}
    void testGroupStarting(Catch::GroupInfo const&) override {}
    void testGroupEnded(Catch::TestGroupStats const&) override {}
    void fatalErrorEncountered(Catch::StringRef) override {}
    void benchmarkPreparing(Catch::StringRef) override {}
    void benchmarkStarting(Catch::BenchmarkInfo const&) override {}
    void benchmarkEnded(Catch::BenchmarkStats<> const&) override {}
    void benchmarkFailed(Catch::StringRef) override {}
};

// A stub reporter factory
class StubReporterFactory : public Catch::IReporterFactory {
public:
    Catch::IEventListenerPtr create(Catch::ReporterConfig&& config) const override {
        return Catch::Detail::make_unique<StubReporter>(config);
    }
    std::string getDescription() const override {
        return "Stub reporter for testing";
    }
};

// A stub EventListenerFactory
class StubEventListenerFactory : public Catch::EventListenerFactory {
public:
    Catch::IEventListenerPtr create(Catch::IConfig const* config) const override {
        // Return a simple listener
        std::ostringstream oss;
        Catch::ReporterConfig rc(config, oss, Catch::ColourMode::None);
        return Catch::Detail::make_unique<StubReporter>(rc);
    }
    Catch::StringRef getName() const override {
        return "StubListener";
    }
    std::string getDescription() const override {
        return "A stub listener for testing";
    }
};

class ReporterRegistryTest_578 : public ::testing::Test {
protected:
    Catch::ReporterRegistry registry;
};

// Test that a newly created registry has no factories initially (or has defaults)
TEST_F(ReporterRegistryTest_578, GetFactoriesInitially_578) {
    auto const& factories = registry.getFactories();
    // Just verify we can call getFactories without crashing
    // The initial state may or may not have built-in reporters
    EXPECT_TRUE(true);
}

// Test that a newly created registry has no listeners initially
TEST_F(ReporterRegistryTest_578, GetListenersInitiallyEmpty_578) {
    auto const& listeners = registry.getListeners();
    EXPECT_TRUE(listeners.empty());
}

// Test registering a reporter and retrieving it from factories
TEST_F(ReporterRegistryTest_578, RegisterReporterAppearsInFactories_578) {
    auto factory = Catch::Detail::make_unique<StubReporterFactory>();
    registry.registerReporter("stub_reporter", std::move(factory));

    auto const& factories = registry.getFactories();
    auto it = factories.find("stub_reporter");
    EXPECT_NE(it, factories.end());
}

// Test registering multiple reporters
TEST_F(ReporterRegistryTest_578, RegisterMultipleReporters_578) {
    auto factory1 = Catch::Detail::make_unique<StubReporterFactory>();
    auto factory2 = Catch::Detail::make_unique<StubReporterFactory>();

    registry.registerReporter("reporter_a", std::move(factory1));
    registry.registerReporter("reporter_b", std::move(factory2));

    auto const& factories = registry.getFactories();
    EXPECT_NE(factories.find("reporter_a"), factories.end());
    EXPECT_NE(factories.find("reporter_b"), factories.end());
}

// Test registering a listener increases listener count
TEST_F(ReporterRegistryTest_578, RegisterListenerAppearsInListeners_578) {
    EXPECT_EQ(registry.getListeners().size(), 0u);

    auto listenerFactory = Catch::Detail::make_unique<StubEventListenerFactory>();
    registry.registerListener(std::move(listenerFactory));

    EXPECT_EQ(registry.getListeners().size(), 1u);
}

// Test registering multiple listeners
TEST_F(ReporterRegistryTest_578, RegisterMultipleListeners_578) {
    auto lf1 = Catch::Detail::make_unique<StubEventListenerFactory>();
    auto lf2 = Catch::Detail::make_unique<StubEventListenerFactory>();

    registry.registerListener(std::move(lf1));
    registry.registerListener(std::move(lf2));

    EXPECT_EQ(registry.getListeners().size(), 2u);
}

// Test that getFactories returns a const reference (stability check)
TEST_F(ReporterRegistryTest_578, GetFactoriesReturnsSameReference_578) {
    auto const& ref1 = registry.getFactories();
    auto const& ref2 = registry.getFactories();
    EXPECT_EQ(&ref1, &ref2);
}

// Test that getListeners returns a const reference (stability check)
TEST_F(ReporterRegistryTest_578, GetListenersReturnsSameReference_578) {
    auto const& ref1 = registry.getListeners();
    auto const& ref2 = registry.getListeners();
    EXPECT_EQ(&ref1, &ref2);
}

// Test case-insensitive lookup of reporters
TEST_F(ReporterRegistryTest_578, FactoriesAreCaseInsensitive_578) {
    auto factory = Catch::Detail::make_unique<StubReporterFactory>();
    registry.registerReporter("MyReporter", std::move(factory));

    auto const& factories = registry.getFactories();
    // The map uses CaseInsensitiveLess, so different cases should find the same entry
    auto it_lower = factories.find("myreporter");
    auto it_upper = factories.find("MYREPORTER");
    auto it_mixed = factories.find("MyReporter");

    EXPECT_NE(it_mixed, factories.end());
    // Case insensitive comparison should find them all equal
    EXPECT_NE(it_lower, factories.end());
    EXPECT_NE(it_upper, factories.end());
}

// Test create with a registered reporter
TEST_F(ReporterRegistryTest_578, CreateRegisteredReporter_578) {
    auto factory = Catch::Detail::make_unique<StubReporterFactory>();
    registry.registerReporter("stub", std::move(factory));

    // We need a valid config to create a reporter
    // This test verifies that create returns a non-null pointer for a registered reporter
    std::vector<std::string> args{"test"};
    Catch::ConfigData configData;
    configData.reporterSpecifications.push_back(Catch::ReporterSpec{"stub", {}, {}, {}});
    Catch::Config config(configData);

    std::ostringstream oss;
    Catch::ReporterConfig reporterConfig(&config, oss, Catch::ColourMode::None);
    auto listener = registry.create("stub", std::move(reporterConfig));
    EXPECT_NE(listener.get(), nullptr);
}

// Test that a non-existent reporter name lookup in factories returns end()
TEST_F(ReporterRegistryTest_578, NonExistentReporterNotInFactories_578) {
    auto const& factories = registry.getFactories();
    EXPECT_EQ(factories.find("nonexistent_reporter"), factories.end());
}

// Test listener is accessible via getListeners after registration
TEST_F(ReporterRegistryTest_578, ListenerAccessibleAfterRegistration_578) {
    auto lf = Catch::Detail::make_unique<StubEventListenerFactory>();
    auto* rawPtr = lf.get();
    registry.registerListener(std::move(lf));

    auto const& listeners = registry.getListeners();
    ASSERT_EQ(listeners.size(), 1u);
    EXPECT_EQ(listeners[0].get(), rawPtr);
}
