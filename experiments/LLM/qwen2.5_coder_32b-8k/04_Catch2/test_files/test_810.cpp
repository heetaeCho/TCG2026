#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/reporters/catch_reporter_registrars.hpp"

#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"



using namespace Catch;

using namespace Catch::Detail;



class MockIMutableRegistryHub : public IMutableRegistryHub {

public:

    MOCK_METHOD(void, registerReporter, (const std::string&, IReporterFactoryPtr), (override));

    MOCK_METHOD(void, registerStartupException, (), (override));

};



TEST(registerReporterImplTest_810, NormalOperation_810) {

    MockIMutableRegistryHub mockRegistry;

    auto reporterPtr = IReporterFactoryPtr();



    EXPECT_CALL(mockRegistry, registerReporter("testReporter", _)).Times(1);



    registerReporterImpl("testReporter", std::move(reporterPtr));

}



TEST(registerReporterImplTest_810, BoundaryCondition_EmptyName_810) {

    MockIMutableRegistryHub mockRegistry;

    auto reporterPtr = IReporterFactoryPtr();



    EXPECT_CALL(mockRegistry, registerReporter("", _)).Times(1);



    registerReporterImpl("", std::move(reporterPtr));

}



TEST(registerReporterImplTest_810, ExceptionalCase_RegisterStartupException_810) {

    MockIMutableRegistryHub mockRegistry;

    auto reporterPtr = IReporterFactoryPtr();



    EXPECT_CALL(mockRegistry, registerReporter("testReporter", _)).WillOnce(testing::Throw(std::runtime_error("Simulated Error")));

    EXPECT_CALL(mockRegistry, registerStartupException()).Times(1);



    registerReporterImpl("testReporter", std::move(reporterPtr));

}
