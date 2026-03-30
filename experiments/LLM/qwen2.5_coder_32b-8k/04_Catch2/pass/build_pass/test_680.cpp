#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_startup_exception_registry.hpp"



using namespace Catch;



class StartupExceptionRegistryTest_680 : public ::testing::Test {

protected:

    StartupExceptionRegistry registry;

};



TEST_F(StartupExceptionRegistryTest_680, GetExceptionsInitiallyEmpty_680) {

    EXPECT_TRUE(registry.getExceptions().empty());

}



TEST_F(StartupExceptionRegistryTest_680, AddSingleException_680) {

    std::exception_ptr exception = std::make_exception_ptr(std::runtime_error("test"));

    registry.add(exception);

    const auto& exceptions = registry.getExceptions();

    EXPECT_EQ(exceptions.size(), 1);

    EXPECT_EQ(exceptions[0], exception);

}



TEST_F(StartupExceptionRegistryTest_680, AddMultipleExceptions_680) {

    std::exception_ptr exception1 = std::make_exception_ptr(std::runtime_error("test1"));

    std::exception_ptr exception2 = std::make_exception_ptr(std::runtime_error("test2"));

    registry.add(exception1);

    registry.add(exception2);

    const auto& exceptions = registry.getExceptions();

    EXPECT_EQ(exceptions.size(), 2);

    EXPECT_EQ(exceptions[0], exception1);

    EXPECT_EQ(exceptions[1], exception2);

}



TEST_F(StartupExceptionRegistryTest_680, AddNoException_680) {

    const auto& exceptions = registry.getExceptions();

    EXPECT_TRUE(exceptions.empty());

}
