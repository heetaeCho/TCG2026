#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/Catch2/extras/catch_amalgamated.hpp"

#include "TestProjects/Catch2/src/catch2/interfaces/catch_interfaces_config.hpp"



using namespace Catch::Benchmark;

using namespace testing;



class BenchmarkTest_914 : public Test {

protected:

    std::shared_ptr<NiceMock<MockIConfig>> configMock;

    Benchmark benchmark;



    class MockIConfig : public IConfig {

    public:

        MOCK_CONST_METHOD0(skipBenchmarks, bool());

    };



    BenchmarkTest_914() 

        : configMock(std::make_shared<NiceMock<MockIConfig>>()),

          benchmark("testBenchmark") {

        Catch::Context().setConfig(configMock.get());

    }

};



TEST_F(BenchmarkTest_914, RunExecutesFunctionWhenBenchmarksNotSkipped_914) {

    bool functionWasCalled = false;

    auto func = [&functionWasCalled]() { functionWasCalled = true; };

    

    benchmark = std::move(func);

    

    EXPECT_CALL(*configMock, skipBenchmarks()).WillOnce(Return(false));

    benchmark.run();



    EXPECT_TRUE(functionWasCalled);

}



TEST_F(BenchmarkTest_914, RunDoesNotExecuteFunctionWhenBenchmarksSkipped_914) {

    bool functionWasCalled = false;

    auto func = [&functionWasCalled]() { functionWasCalled = true; };

    

    benchmark = std::move(func);

    

    EXPECT_CALL(*configMock, skipBenchmarks()).WillOnce(Return(true));

    benchmark.run();



    EXPECT_FALSE(functionWasCalled);

}



TEST_F(BenchmarkTest_914, AssignmentOperatorSetsFunction_914) {

    bool functionWasCalled = false;

    auto func = [&functionWasCalled]() { functionWasCalled = true; };

    

    benchmark = std::move(func);

    

    EXPECT_CALL(*configMock, skipBenchmarks()).WillOnce(Return(false));

    benchmark.run();



    EXPECT_TRUE(functionWasCalled);

}



TEST_F(BenchmarkTest_914, BenchmarkCanBeConstructedWithNameAndFunction_914) {

    bool functionWasCalled = false;

    auto func = [&functionWasCalled]() { functionWasCalled = true; };

    

    Benchmark namedBenchmark("testBenchmark", std::move(func));

    

    EXPECT_CALL(*configMock, skipBenchmarks()).WillOnce(Return(false));

    namedBenchmark.run();



    EXPECT_TRUE(functionWasCalled);

}



TEST_F(BenchmarkTest_914, BoolOperatorReturnsTrueForValidFunction_914) {

    auto func = []() {};

    benchmark = std::move(func);



    EXPECT_TRUE(static_cast<bool>(benchmark));

}
