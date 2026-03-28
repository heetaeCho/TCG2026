#include <gtest/gtest.h>
#include <string>

// Include necessary Catch2 headers
#include "catch2/reporters/catch_reporter_registrars.hpp"
#include "catch2/catch_session.hpp"
#include "catch2/interfaces/catch_interfaces_reporter_registry.hpp"
#include "catch2/catch_get_random_seed.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_context.hpp"

namespace {

// A minimal reporter that satisfies the requirements for ReporterFactory<T>
class DummyReporter_1083 : public Catch::StreamingReporterBase {
public:
    using StreamingReporterBase::StreamingReporterBase;

    static std::string getDescription() {
        return "A dummy reporter for testing registration";
    }
};

class AnotherDummyReporter_1083 : public Catch::StreamingReporterBase {
public:
    using StreamingReporterBase::StreamingReporterBase;

    static std::string getDescription() {
        return "Another dummy reporter for testing registration";
    }
};

class ThirdDummyReporter_1083 : public Catch::StreamingReporterBase {
public:
    using StreamingReporterBase::StreamingReporterBase;

    static std::string getDescription() {
        return "Third dummy reporter";
    }
};

} // anonymous namespace

class ReporterRegistrarTest_1083 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure Catch2 context is initialized
    }
};

// Test that registering a reporter with a valid name does not throw
TEST_F(ReporterRegistrarTest_1083, RegisterWithValidName_1083) {
    EXPECT_NO_THROW({
        Catch::ReporterRegistrar<DummyReporter_1083> registrar("dummy_test_reporter_1083");
    });
}

// Test that registering another reporter with a different name works
TEST_F(ReporterRegistrarTest_1083, RegisterAnotherReporterWithDifferentName_1083) {
    EXPECT_NO_THROW({
        Catch::ReporterRegistrar<AnotherDummyReporter_1083> registrar("another_dummy_reporter_1083");
    });
}

// Test registration with an empty name - boundary condition
TEST_F(ReporterRegistrarTest_1083, RegisterWithEmptyName_1083) {
    // Empty name is a boundary condition; behavior depends on implementation
    // but we verify it doesn't crash unexpectedly or we observe expected behavior
    EXPECT_NO_THROW({
        Catch::ReporterRegistrar<ThirdDummyReporter_1083> registrar("");
    });
}

// Test that the registered reporter can be found in the registry
TEST_F(ReporterRegistrarTest_1083, RegisteredReporterIsAccessibleInRegistry_1083) {
    static bool registered = false;
    if (!registered) {
        Catch::ReporterRegistrar<DummyReporter_1083> registrar("findable_reporter_1083");
        registered = true;
    }

    // Verify the reporter exists in the registry by checking registered reporters
    auto const& registry = Catch::getRegistryHub().getReporterRegistry();
    auto const& reporters = registry.getFactories();
    
    auto it = reporters.find("findable_reporter_1083");
    EXPECT_NE(it, reporters.end());
}

// Test registration with a name containing special characters
TEST_F(ReporterRegistrarTest_1083, RegisterWithSpecialCharacterName_1083) {
    EXPECT_NO_THROW({
        Catch::ReporterRegistrar<DummyReporter_1083> registrar("special-reporter_1083!@#");
    });
}

// Test registration with a long name - boundary condition
TEST_F(ReporterRegistrarTest_1083, RegisterWithLongName_1083) {
    std::string longName(1000, 'a');
    longName += "_1083";
    EXPECT_NO_THROW({
        Catch::ReporterRegistrar<DummyReporter_1083> registrar(longName);
    });
}

// Test that the factory created by registration can produce a reporter
TEST_F(ReporterRegistrarTest_1083, FactoryProducesReporter_1083) {
    static bool registered = false;
    if (!registered) {
        Catch::ReporterRegistrar<AnotherDummyReporter_1083> registrar("producible_reporter_1083");
        registered = true;
    }

    auto const& registry = Catch::getRegistryHub().getReporterRegistry();
    auto const& reporters = registry.getFactories();

    auto it = reporters.find("producible_reporter_1083");
    ASSERT_NE(it, reporters.end());
    EXPECT_NE(it->second, nullptr);
}
