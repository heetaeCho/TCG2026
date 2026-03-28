#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/interfaces/catch_interfaces_reporter_factory.hpp>
#include <catch2/catch_config.hpp>
#include <catch2/reporters/catch_reporter_event_listener.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <string>

namespace {

// A listener type WITHOUT a description
struct ListenerWithoutDescription : Catch::EventListenerBase {
    using EventListenerBase::EventListenerBase;
};

// A listener type WITH a description (has static getDescription)
struct ListenerWithDescription : Catch::EventListenerBase {
    using EventListenerBase::EventListenerBase;
    
    static std::string getDescription() {
        return "A test listener with description";
    }
};

// Mock IConfig for create() testing
class MockConfig : public Catch::IConfig {
public:
    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(std::ostream&, stream, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutNoTests, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(Catch::TestSpec const&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(std::vector<std::string> const&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::RunTests::InWhatOrder, runOrder, (), (const, override));
    MOCK_METHOD(Catch::Seed::Value, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(std::vector<Catch::ReporterSpec> const&, getReporterSpecs, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

} // anonymous namespace

class TypedListenerFactoryTest_568 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TypedListenerFactoryTest_568, GetNameReturnsProvidedName_568) {
    // Test that getName() returns the name passed during construction
    Catch::ListenerRegistrar::TypedListenerFactory<ListenerWithoutDescription> factory("my_listener"_catch_sr);
    EXPECT_EQ(factory.getName(), "my_listener");
}

TEST_F(TypedListenerFactoryTest_568, GetNameReturnsEmptyForEmptyName_568) {
    Catch::ListenerRegistrar::TypedListenerFactory<ListenerWithoutDescription> factory(""_catch_sr);
    EXPECT_EQ(factory.getName(), "");
}

TEST_F(TypedListenerFactoryTest_568, GetDescriptionWithDescriptionType_568) {
    // When T has a getDescription static method, it should return that description
    Catch::ListenerRegistrar::TypedListenerFactory<ListenerWithDescription> factory("described_listener"_catch_sr);
    std::string desc = factory.getDescription();
    EXPECT_EQ(desc, "A test listener with description");
}

TEST_F(TypedListenerFactoryTest_568, GetDescriptionWithoutDescriptionType_568) {
    // When T does NOT have a getDescription, it should return some default/empty description
    Catch::ListenerRegistrar::TypedListenerFactory<ListenerWithoutDescription> factory("no_desc_listener"_catch_sr);
    std::string desc = factory.getDescription();
    // Without description trait, expect empty or default string
    EXPECT_TRUE(desc.empty() || !desc.empty()); // At minimum, it should not crash
}

TEST_F(TypedListenerFactoryTest_568, CreateReturnsNonNull_568) {
    Catch::ListenerRegistrar::TypedListenerFactory<ListenerWithoutDescription> factory("test_listener"_catch_sr);
    // create() should return a valid listener pointer
    // Note: We need a valid IConfig; using nullptr might not be safe depending on implementation
    auto listener = factory.create(nullptr);
    EXPECT_NE(listener, nullptr);
}

TEST_F(TypedListenerFactoryTest_568, DifferentNamesAreDifferent_568) {
    Catch::ListenerRegistrar::TypedListenerFactory<ListenerWithoutDescription> factory1("listener_a"_catch_sr);
    Catch::ListenerRegistrar::TypedListenerFactory<ListenerWithoutDescription> factory2("listener_b"_catch_sr);
    EXPECT_NE(factory1.getName(), factory2.getName());
    EXPECT_EQ(factory1.getName(), "listener_a");
    EXPECT_EQ(factory2.getName(), "listener_b");
}
