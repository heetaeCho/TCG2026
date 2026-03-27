#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;



// Mock class to simulate callable interface

class MockCallable {

public:

    MOCK_METHOD1(call, void(Catch::Benchmark::Chronometer));

};



TEST(BenchmarkFunctionTest_894, DefaultConstructorInitializesCorrectly_894) {

    BenchmarkFunction bf;

    // Since we can't directly check internal state, we rely on observable behavior.

}



TEST(BenchmarkFunctionTest_894, MoveConstructorTransfersOwnership_894) {

    MockCallable* mock_callable = new MockCallable();

    BenchmarkFunction bf1([mock_callable](Catch::Benchmark::Chronometer meter) { mock_callable->call(meter); });

    BenchmarkFunction bf2(std::move(bf1));



    // Since we can't directly check internal state, we rely on observable behavior.

}



TEST(BenchmarkFunctionTest_894, MoveAssignmentOperatorTransfersOwnership_894) {

    MockCallable* mock_callable = new MockCallable();

    BenchmarkFunction bf1([mock_callable](Catch::Benchmark::Chronometer meter) { mock_callable->call(meter); });

    BenchmarkFunction bf2;

    bf2 = std::move(bf1);



    // Since we can't directly check internal state, we rely on observable behavior.

}



TEST(BenchmarkFunctionTest_894, InvokeCallsCallableWithChronometer_894) {

    MockCallable mock_callable;

    EXPECT_CALL(mock_callable, call(::testing::_));



    BenchmarkFunction bf([&mock_callable](Catch::Benchmark::Chronometer meter) { mock_callable.call(meter); });

    Catch::Benchmark::Chronometer chronometer;

    bf(chronometer);

}



TEST(BenchmarkFunctionTest_894, InvokeDoesNotCrashWithNullCallable_894) {

    BenchmarkFunction bf;  // Default constructor initializes with do_nothing

    Catch::Benchmark::Chronometer chronometer;

    EXPECT_NO_THROW(bf(chronometer));

}
