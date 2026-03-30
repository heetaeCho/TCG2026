#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"



using namespace Catch::Benchmark;

using ::testing::_;



class BenchmarkMock : public Benchmark {

public:

    using Benchmark::Benchmark;

    MOCK_METHOD(void, run, (), (override));

    MOCK_METHOD(bool, operator bool, (), (const, override));

};



TEST_F(BenchmarkTest_915, ConstructorWithNameAndFunction_915) {

    auto func = []() {};

    BenchmarkMock benchmark("test_benchmark", func);

    EXPECT_TRUE(static_cast<bool>(benchmark));

}



TEST_F(BenchmarkTest_915, OperatorBool_ReturnsTrue_915) {

    auto func = []() {};

    BenchmarkMock benchmark("test_benchmark", func);

    EXPECT_TRUE(benchmark.operator bool());

}



TEST_F(BenchmarkTest_915, Run_MethodIsCalled_915) {

    auto func = []() {};

    BenchmarkMock benchmark("test_benchmark", func);

    EXPECT_CALL(benchmark, run()).Times(1);

    benchmark.run();

}



TEST_F(BenchmarkTest_915, AssignmentOperatorWithFunction_915) {

    auto func1 = []() {};

    auto func2 = []() {};

    BenchmarkMock benchmark("test_benchmark", func1);

    benchmark = func2;

    EXPECT_TRUE(static_cast<bool>(benchmark));

}
