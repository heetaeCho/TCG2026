#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the necessary headers
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Benchmark;
using namespace Catch::Benchmark::Detail;

// ============================================================================
// Mock for ChronometerConcept to create valid Chronometer instances
// ============================================================================
struct MockChronometerConcept : public Detail::ChronometerConcept {
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, finish, (), (override));
};

// ============================================================================
// Test Fixture
// ============================================================================
class BenchmarkFunctionTest_895 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================================
// Test: Default constructor creates a valid BenchmarkFunction
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, DefaultConstructor_895) {
    BenchmarkFunction bf;
    // Default constructed BenchmarkFunction should be callable (uses do_nothing)
    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);
    // Should not throw - default is do_nothing
    EXPECT_NO_THROW(bf(meter));
}

// ============================================================================
// Test: Constructor with a lambda function
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, ConstructWithLambda_895) {
    bool called = false;
    BenchmarkFunction bf([&called](Chronometer) {
        called = true;
    });

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);
    bf(meter);

    EXPECT_TRUE(called);
}

// ============================================================================
// Test: Move constructor transfers ownership
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, MoveConstructor_895) {
    bool called = false;
    BenchmarkFunction bf1([&called](Chronometer) {
        called = true;
    });

    BenchmarkFunction bf2(std::move(bf1));

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);
    bf2(meter);

    EXPECT_TRUE(called);
}

// ============================================================================
// Test: Move assignment operator transfers ownership
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, MoveAssignment_895) {
    bool called = false;
    BenchmarkFunction bf1([&called](Chronometer) {
        called = true;
    });

    BenchmarkFunction bf2;
    bf2 = std::move(bf1);

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);
    bf2(meter);

    EXPECT_TRUE(called);
}

// ============================================================================
// Test: Operator() invokes the stored callable
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, OperatorCallInvokesCallable_895) {
    int call_count = 0;
    BenchmarkFunction bf([&call_count](Chronometer) {
        call_count++;
    });

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);

    bf(meter);
    EXPECT_EQ(call_count, 1);

    bf(meter);
    EXPECT_EQ(call_count, 2);
}

// ============================================================================
// Test: BenchmarkFunction can be constructed with a functor object
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, ConstructWithFunctor_895) {
    struct MyFunctor {
        int* counter;
        void operator()(Chronometer) const { (*counter)++; }
    };

    int counter = 0;
    MyFunctor functor{&counter};
    BenchmarkFunction bf(functor);

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);
    bf(meter);

    EXPECT_EQ(counter, 1);
}

// ============================================================================
// Test: Default constructed BenchmarkFunction does nothing when called
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, DefaultDoesNothing_895) {
    BenchmarkFunction bf;
    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 5);

    // Calling default should not crash or throw
    EXPECT_NO_THROW(bf(meter));
}

// ============================================================================
// Test: Move assignment replaces existing callable
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, MoveAssignmentReplacesCallable_895) {
    bool first_called = false;
    bool second_called = false;

    BenchmarkFunction bf1([&first_called](Chronometer) {
        first_called = true;
    });

    BenchmarkFunction bf2([&second_called](Chronometer) {
        second_called = true;
    });

    bf1 = std::move(bf2);

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);
    bf1(meter);

    EXPECT_FALSE(first_called);
    EXPECT_TRUE(second_called);
}

// ============================================================================
// Test: Chronometer's runs() returns the repeats value
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, ChronometerRuns_895) {
    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 42);
    EXPECT_EQ(meter.runs(), 42);
}

// ============================================================================
// Test: BenchmarkFunction with stateful lambda preserves state across calls
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, StatefulLambdaPreservesState_895) {
    auto shared_count = std::make_shared<int>(0);
    BenchmarkFunction bf([shared_count](Chronometer) {
        (*shared_count)++;
    });

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);

    bf(meter);
    bf(meter);
    bf(meter);

    EXPECT_EQ(*shared_count, 3);
}

// ============================================================================
// Test: Chronometer with different repeat counts
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, ChronometerDifferentRepeats_895) {
    MockChronometerConcept mock_concept;

    Chronometer meter1(mock_concept, 1);
    EXPECT_EQ(meter1.runs(), 1);

    Chronometer meter2(mock_concept, 100);
    EXPECT_EQ(meter2.runs(), 100);

    Chronometer meter3(mock_concept, 0);
    EXPECT_EQ(meter3.runs(), 0);
}

// ============================================================================
// Test: BenchmarkFunction receives the correct Chronometer
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, ReceivesCorrectChronometer_895) {
    int observed_runs = -1;
    BenchmarkFunction bf([&observed_runs](Chronometer meter) {
        observed_runs = meter.runs();
    });

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 77);
    bf(meter);

    EXPECT_EQ(observed_runs, 77);
}

// ============================================================================
// Test: Multiple move constructions chain correctly
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, ChainedMoveConstruction_895) {
    bool called = false;
    BenchmarkFunction bf1([&called](Chronometer) {
        called = true;
    });

    BenchmarkFunction bf2(std::move(bf1));
    BenchmarkFunction bf3(std::move(bf2));

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);
    bf3(meter);

    EXPECT_TRUE(called);
}

// ============================================================================
// Test: Move assignment from default-constructed BenchmarkFunction
// ============================================================================
TEST_F(BenchmarkFunctionTest_895, MoveAssignFromDefault_895) {
    bool called = false;
    BenchmarkFunction bf1([&called](Chronometer) {
        called = true;
    });

    BenchmarkFunction bf_default;
    bf1 = std::move(bf_default);

    MockChronometerConcept mock_concept;
    Chronometer meter(mock_concept, 1);

    // After moving a default (do_nothing) into bf1, calling should do nothing
    EXPECT_NO_THROW(bf1(meter));
    EXPECT_FALSE(called);
}
