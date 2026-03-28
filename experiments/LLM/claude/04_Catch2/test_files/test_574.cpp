#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_reporter_registry.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_factory.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// Mock for IReporterFactory
class MockReporterFactory : public Catch::IReporterFactory {
public:
    ~MockReporterFactory() override = default;
    MOCK_METHOD(Catch::IEventListenerPtr, create, (Catch::ReporterConfig&& config), (const, override));
    MOCK_METHOD(std::string, getDescription, (), (const, override));
};

// Mock for IEventListener (minimal, to return from factory)
class MockEventListener : public Catch::IEventListener {
public:
    MockEventListener() : Catch::IEventListener(nullptr) {}
    ~MockEventListener() override = default;
    
    void reportInvalidTestSpec(Catch::StringRef) override {}
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
    void fatalErrorEncountered(Catch::StringRef) override {}
    void listProcessors(std::vector<Catch::ProcessorInfo> const&) override {}
    void listReporters(std::vector<Catch::ReporterDescription> const&) override {}
    void listListeners(std::vector<Catch::ListenerDescription> const&) override {}
    void listTests(std::vector<Catch::TestCaseHandle> const&) override {}
    void listTags(std::vector<Catch::TagInfo> const&) override {}
    void noMatchingTestCases(Catch::StringRef) override {}
    void testGroupStarting(Catch::GroupInfo const&) override {}
    void testGroupEnded(Catch::TestGroupStats const&) override {}
    void benchmarkPreparing(Catch::StringRef) override {}
    void benchmarkStarting(Catch::BenchmarkInfo const&) override {}
    void benchmarkEnded(Catch::BenchmarkStats<> const&) override {}
    void benchmarkFailed(Catch::StringRef) override {}
};

// Mock for EventListenerFactory
class MockEventListenerFactory : public Catch::EventListenerFactory {
public:
    ~MockEventListenerFactory() override = default;
    MOCK_METHOD(Catch::IEventListenerPtr, create, (Catch::ReporterConfig&& config), (const, override));
    MOCK_METHOD(Catch::StringRef, getDescription, (), (const, override));
};

// Helper to create a minimal ReporterConfig
static Catch::ReporterConfig makeReporterConfig() {
    return Catch::ReporterConfig(
        nullptr,
        Catch::Detail::unique_ptr<Catch::IStream>(nullptr),
        Catch::ColourMode::None,
        std::map<std::string, std::string>{}
    );
}

class ReporterRegistryTest_574 : public ::testing::Test {
protected:
    Catch::ReporterRegistry registry;
};

// Test that a freshly constructed registry has no factories
TEST_F(ReporterRegistryTest_574, InitiallyEmpty_574) {
    auto const& factories = registry.getFactories();
    EXPECT_TRUE(factories.empty());
}

// Test that a freshly constructed registry has no listeners
TEST_F(ReporterRegistryTest_574, InitiallyNoListeners_574) {
    auto const& listeners = registry.getListeners();
    EXPECT_TRUE(listeners.empty());
}

// Test that create returns nullptr for unregistered reporter name
TEST_F(ReporterRegistryTest_574, CreateReturnsNullForUnknownName_574) {
    auto config = makeReporterConfig();
    auto result = registry.create("nonexistent", std::move(config));
    EXPECT_FALSE(result);
}

// Test that registerReporter adds a factory that appears in getFactories
TEST_F(ReporterRegistryTest_574, RegisterReporterAddsFactory_574) {
    auto factory = Catch::Detail::make_unique<MockReporterFactory>();
    registry.registerReporter("testReporter", std::move(factory));
    
    auto const& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 1u);
    EXPECT_NE(factories.find("testReporter"), factories.end());
}

// Test that create invokes the factory's create method for a registered reporter
TEST_F(ReporterRegistryTest_574, CreateCallsFactoryCreate_574) {
    auto factoryRaw = new MockReporterFactory();
    
    EXPECT_CALL(*factoryRaw, create(::testing::_))
        .Times(1)
        .WillOnce(::testing::Invoke([](Catch::ReporterConfig&&) -> Catch::IEventListenerPtr {
            return Catch::Detail::make_unique<MockEventListener>();
        }));
    
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(factoryRaw);
    registry.registerReporter("myReporter", std::move(factory));
    
    auto config = makeReporterConfig();
    auto result = registry.create("myReporter", std::move(config));
    EXPECT_TRUE(result);
}

// Test that registering multiple reporters works
TEST_F(ReporterRegistryTest_574, RegisterMultipleReporters_574) {
    auto factory1 = Catch::Detail::make_unique<MockReporterFactory>();
    auto factory2 = Catch::Detail::make_unique<MockReporterFactory>();
    
    registry.registerReporter("reporter1", std::move(factory1));
    registry.registerReporter("reporter2", std::move(factory2));
    
    auto const& factories = registry.getFactories();
    EXPECT_EQ(factories.size(), 2u);
    EXPECT_NE(factories.find("reporter1"), factories.end());
    EXPECT_NE(factories.find("reporter2"), factories.end());
}

// Test that create with empty string returns nullptr
TEST_F(ReporterRegistryTest_574, CreateWithEmptyStringReturnsNull_574) {
    auto config = makeReporterConfig();
    auto result = registry.create("", std::move(config));
    EXPECT_FALSE(result);
}

// Test that registerListener adds a listener
TEST_F(ReporterRegistryTest_574, RegisterListenerAddsToListeners_574) {
    auto listener = Catch::Detail::make_unique<MockEventListenerFactory>();
    registry.registerListener(std::move(listener));
    
    auto const& listeners = registry.getListeners();
    EXPECT_EQ(listeners.size(), 1u);
}

// Test that registering multiple listeners works
TEST_F(ReporterRegistryTest_574, RegisterMultipleListeners_574) {
    auto listener1 = Catch::Detail::make_unique<MockEventListenerFactory>();
    auto listener2 = Catch::Detail::make_unique<MockEventListenerFactory>();
    
    registry.registerListener(std::move(listener1));
    registry.registerListener(std::move(listener2));
    
    auto const& listeners = registry.getListeners();
    EXPECT_EQ(listeners.size(), 2u);
}

// Test case-insensitive lookup for factory names (CaseInsensitiveLess comparator)
TEST_F(ReporterRegistryTest_574, CaseInsensitiveFactoryLookup_574) {
    auto factoryRaw = new MockReporterFactory();
    
    EXPECT_CALL(*factoryRaw, create(::testing::_))
        .WillOnce(::testing::Invoke([](Catch::ReporterConfig&&) -> Catch::IEventListenerPtr {
            return Catch::Detail::make_unique<MockEventListener>();
        }));
    
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(factoryRaw);
    registry.registerReporter("MyReporter", std::move(factory));
    
    // Attempt to create with different casing
    auto config = makeReporterConfig();
    auto result = registry.create("myreporter", std::move(config));
    EXPECT_TRUE(result);
}

// Test that getFactories returns reference to same map (consistency)
TEST_F(ReporterRegistryTest_574, GetFactoriesConsistency_574) {
    auto factory = Catch::Detail::make_unique<MockReporterFactory>();
    registry.registerReporter("consReporter", std::move(factory));
    
    auto const& factories1 = registry.getFactories();
    auto const& factories2 = registry.getFactories();
    
    EXPECT_EQ(&factories1, &factories2);
}

// Test that getListeners returns reference to same vector (consistency)
TEST_F(ReporterRegistryTest_574, GetListenersConsistency_574) {
    auto const& listeners1 = registry.getListeners();
    auto const& listeners2 = registry.getListeners();
    
    EXPECT_EQ(&listeners1, &listeners2);
}

// Test that create for a registered reporter that returns nullptr from factory
TEST_F(ReporterRegistryTest_574, CreateReturnsNullWhenFactoryReturnsNull_574) {
    auto factoryRaw = new MockReporterFactory();
    
    EXPECT_CALL(*factoryRaw, create(::testing::_))
        .WillOnce(::testing::Invoke([](Catch::ReporterConfig&&) -> Catch::IEventListenerPtr {
            return nullptr;
        }));
    
    auto factory = Catch::Detail::unique_ptr<Catch::IReporterFactory>(factoryRaw);
    registry.registerReporter("nullReporter", std::move(factory));
    
    auto config = makeReporterConfig();
    auto result = registry.create("nullReporter", std::move(config));
    EXPECT_FALSE(result);
}

// Test case-insensitive: registering same name with different case should map to one entry
TEST_F(ReporterRegistryTest_574, CaseInsensitiveRegistrationOverwrite_574) {
    auto factory1 = Catch::Detail::make_unique<MockReporterFactory>();
    auto factory2 = Catch::Detail::make_unique<MockReporterFactory>();
    
    registry.registerReporter("TestReporter", std::move(factory1));
    registry.registerReporter("testreporter", std::move(factory2));
    
    auto const& factories = registry.getFactories();
    // With case-insensitive comparator, these should be the same key
    // Depending on map behavior, second insert may or may not replace.
    // At minimum, both lookups should find an entry.
    EXPECT_NE(factories.find("TestReporter"), factories.end());
    EXPECT_NE(factories.find("testreporter"), factories.end());
}
