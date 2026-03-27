#include <gtest/gtest.h>

#include "catch_reporter_registry.hpp"

#include "catch_unique_ptr.hpp"



namespace Catch {

    class MockIReporterFactory : public IReporterFactory {

    public:

        MOCK_METHOD1(create, IEventListenerPtr(ReporterConfig&&));

    };



    using namespace ::testing;



    class ReporterRegistryTest_575 : public Test {

    protected:

        ReporterRegistry registry;

    };



    TEST_F(ReporterRegistryTest_575, RegisterValidReporterName_575) {

        auto factory = std::make_unique<MockIReporterFactory>();

        EXPECT_NO_THROW(registry.registerReporter("valid_name", std::move(factory)));

    }



    TEST_F(ReporterRegistryTest_575, RegisterDuplicateReporterNameThrows_575) {

        auto factory1 = std::make_unique<MockIReporterFactory>();

        registry.registerReporter("duplicate_name", std::move(factory1));



        auto factory2 = std::make_unique<MockIReporterFactory>();

        EXPECT_THROW(registry.registerReporter("duplicate_name", std::move(factory2)), std::logic_error);

    }



    TEST_F(ReporterRegistryTest_575, RegisterInvalidReporterNameWithColonThrows_575) {

        auto factory = std::make_unique<MockIReporterFactory>();

        EXPECT_THROW(registry.registerReporter("invalid:name", std::move(factory)), std::logic_error);

    }



    TEST_F(ReporterRegistryTest_575, GetFactoriesInitiallyEmpty_575) {

        const auto& factories = registry.getFactories();

        EXPECT_TRUE(factories.empty());

    }



    TEST_F(ReporterRegistryTest_575, RegisterReporterAndGetFactories_575) {

        auto factory = std::make_unique<MockIReporterFactory>();

        registry.registerReporter("test_reporter", std::move(factory));



        const auto& factories = registry.getFactories();

        EXPECT_EQ(factories.size(), 1);

        EXPECT_TRUE(factories.find("test_reporter") != factories.end());

    }



    TEST_F(ReporterRegistryTest_575, RegisterListenerAndGetListeners_575) {

        auto listenerFactory = std::make_unique<EventListenerFactory>();

        registry.registerListener(std::move(listenerFactory));



        const auto& listeners = registry.getListeners();

        EXPECT_EQ(listeners.size(), 1);

    }

}
