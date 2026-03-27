#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Benchmark;

using namespace Catch::Benchmark::Detail;



class MockCallable : public callable {

public:

    MOCK_METHOD(void, call, (Chronometer meter), (const, override));

};



TEST_F(MockCallableTest_895, CallIsInvoked_895) {

    MockCallable mock_callable;

    Chronometer chronometer(Detail::ChronometerConcept(), 1);

    

    EXPECT_CALL(mock_callable, call(chronometer)).Times(1);



    BenchmarkFunction benchmark_function([&mock_callable]() { mock_callable.call(chronometer); });

    benchmark_function(chronometer);

}



TEST_F(BenchmarkFunctionTest_895, MoveConstructorTransfersOwnership_895) {

    MockCallable* mock_callable = new MockCallable();

    BenchmarkFunction original(mock_callable);



    BenchmarkFunction moved(std::move(original));



    EXPECT_EQ(moved.f.get(), mock_callable);

}



TEST_F(BenchmarkFunctionTest_895, MoveAssignmentOperatorTransfersOwnership_895) {

    MockCallable* mock_callable = new MockCallable();

    BenchmarkFunction original(mock_callable);

    BenchmarkFunction target;



    target = std::move(original);



    EXPECT_EQ(target.f.get(), mock_callable);

}



TEST_F(BenchmarkFunctionTest_895, DefaultConstructorInitializesWithDoNothing_895) {

    BenchmarkFunction benchmark_function;

    

    // Assuming that calling do_nothing doesn't have any observable side-effect.

    Chronometer chronometer(Detail::ChronometerConcept(), 1);

    EXPECT_NO_THROW(benchmark_function(chronometer));

}



TEST_F(BenchmarkFunctionTest_895, MeasureCallsCallableWithChronometer_895) {

    MockCallable mock_callable;

    BenchmarkFunction benchmark_function([&mock_callable]() { mock_callable.call(Chronometer(Detail::ChronometerConcept(), 1)); });



    Chronometer chronometer(Detail::ChronometerConcept(), 1);

    

    EXPECT_CALL(mock_callable, call(chronometer)).Times(1);



    benchmark_function.measure([&mock_callable](Chronometer meter) { mock_callable.call(meter); });

}



TEST_F(BenchmarkFunctionTest_895, OperatorParenthesisCallsCallableWithChronometer_895) {

    MockCallable mock_callable;

    BenchmarkFunction benchmark_function(mock_callable);



    Chronometer chronometer(Detail::ChronometerConcept(), 1);

    

    EXPECT_CALL(mock_callable, call(chronometer)).Times(1);



    benchmark_function(chronometer);

}
