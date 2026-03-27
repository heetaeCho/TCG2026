#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_unique_ptr.hpp"



namespace {



using namespace Catch::Benchmark::Detail;

using namespace Catch::Detail;



class EnvironmentMock : public Environment {

public:

    MOCK_METHOD(void, someMethod, (), (override));

};



TEST(MeasureEnvironmentTest_911, FirstCallInitializesEnv_911) {

    // Arrange

    auto env = measure_environment<std::chrono::steady_clock>();

    

    // Act & Assert

    EXPECT_NE(&env, nullptr);

}



TEST(MeasureEnvironmentTest_911, SubsequentCallsReturnSameEnv_911) {

    // Arrange

    auto& first_env = measure_environment<std::chrono::steady_clock>();

    

    // Act

    auto& second_env = measure_environment<std::chrono::steady_clock>();

    

    // Assert

    EXPECT_EQ(&first_env, &second_env);

}



TEST(MeasureEnvironmentTest_911, EnvIsNotNullptr_911) {

    // Arrange & Act

    auto env = measure_environment<std::chrono::steady_clock>();

    

    // Assert

    EXPECT_NE(env.get(), nullptr);

}



}  // namespace
