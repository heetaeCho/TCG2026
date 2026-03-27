#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_startup_exception_registry.hpp"

#include <exception>



using namespace Catch;



class StartupExceptionRegistryTest_679 : public ::testing::Test {

protected:

    StartupExceptionRegistry registry;

};



TEST_F(StartupExceptionRegistryTest_679, AddSingleException_679) {

    std::exception_ptr ex = std::make_exception_ptr(std::runtime_error("test"));

    registry.add(ex);

    const auto& exceptions = registry.getExceptions();

    ASSERT_EQ(exceptions.size(), 1);

    EXPECT_TRUE(exceptions[0] == ex);

}



TEST_F(StartupExceptionRegistryTest_679, AddMultipleExceptions_679) {

    std::exception_ptr ex1 = std::make_exception_ptr(std::runtime_error("test1"));

    std::exception_ptr ex2 = std::make_exception_ptr(std::runtime_error("test2"));

    registry.add(ex1);

    registry.add(ex2);

    const auto& exceptions = registry.getExceptions();

    ASSERT_EQ(exceptions.size(), 2);

    EXPECT_TRUE(exceptions[0] == ex1);

    EXPECT_TRUE(exceptions[1] == ex2);

}



TEST_F(StartupExceptionRegistryTest_679, AddNoException_679) {

    const auto& exceptions = registry.getExceptions();

    ASSERT_EQ(exceptions.size(), 0);

}



TEST_F(StartupExceptionRegistryTest_679, BoundaryConditionEmptyExceptionPtr_679) {

    std::exception_ptr ex;

    registry.add(ex);

    const auto& exceptions = registry.getExceptions();

    ASSERT_EQ(exceptions.size(), 1);

    EXPECT_TRUE(!exceptions[0]);

}
