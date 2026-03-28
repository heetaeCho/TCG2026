#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

namespace {

// We need to create a mock for Detail::ChronometerConcept to construct a Chronometer
// Since ChronometerConcept is an internal detail, we need to work with what's available.

// A concrete implementation of ChronometerConcept for testing purposes
class MockChronometerConcept : public Catch::Benchmark::Detail::ChronometerConcept {
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, finish, (), (override));
};

class ChronometerTest_891 : public ::testing::Test {
protected:
    MockChronometerConcept mockConcept;
};

// Test that runs() returns the correct number of repeats
TEST_F(ChronometerTest_891, RunsReturnsRepeats_891) {
    int expectedRepeats = 10;
    Catch::Benchmark::Chronometer chrono(mockConcept, expectedRepeats);
    EXPECT_EQ(chrono.runs(), expectedRepeats);
}

// Test that runs() returns 1 when constructed with 1 repeat
TEST_F(ChronometerTest_891, RunsReturnsSingleRepeat_891) {
    Catch::Benchmark::Chronometer chrono(mockConcept, 1);
    EXPECT_EQ(chrono.runs(), 1);
}

// Test that runs() returns 0 when constructed with 0 repeats
TEST_F(ChronometerTest_891, RunsReturnsZeroRepeats_891) {
    Catch::Benchmark::Chronometer chrono(mockConcept, 0);
    EXPECT_EQ(chrono.runs(), 0);
}

// Test that runs() returns a large number of repeats
TEST_F(ChronometerTest_891, RunsReturnsLargeRepeats_891) {
    int largeRepeats = 1000000;
    Catch::Benchmark::Chronometer chrono(mockConcept, largeRepeats);
    EXPECT_EQ(chrono.runs(), largeRepeats);
}

// Test measure with a callable that takes no arguments (std::false_type path)
TEST_F(ChronometerTest_891, MeasureWithNoArgCallable_891) {
    int repeats = 5;
    Catch::Benchmark::Chronometer chrono(mockConcept, repeats);
    
    EXPECT_CALL(mockConcept, start()).Times(1);
    EXPECT_CALL(mockConcept, finish()).Times(1);
    
    int callCount = 0;
    chrono.measure([&callCount]() {
        callCount++;
    });
    
    // The callable should be invoked `repeats` times
    EXPECT_EQ(callCount, repeats);
}

// Test measure with a callable that takes an int argument (std::true_type path)
TEST_F(ChronometerTest_891, MeasureWithIntArgCallable_891) {
    int repeats = 5;
    Catch::Benchmark::Chronometer chrono(mockConcept, repeats);
    
    EXPECT_CALL(mockConcept, start()).Times(1);
    EXPECT_CALL(mockConcept, finish()).Times(1);
    
    std::vector<int> receivedIndices;
    chrono.measure([&receivedIndices](int i) {
        receivedIndices.push_back(i);
    });
    
    // The callable should be invoked `repeats` times with indices 0..repeats-1
    ASSERT_EQ(static_cast<int>(receivedIndices.size()), repeats);
    for (int i = 0; i < repeats; ++i) {
        EXPECT_EQ(receivedIndices[i], i);
    }
}

// Test measure with a callable that takes int, verifying indices are sequential
TEST_F(ChronometerTest_891, MeasureWithIntArgVerifiesSequentialIndices_891) {
    int repeats = 3;
    Catch::Benchmark::Chronometer chrono(mockConcept, repeats);
    
    EXPECT_CALL(mockConcept, start()).Times(1);
    EXPECT_CALL(mockConcept, finish()).Times(1);
    
    std::vector<int> indices;
    chrono.measure([&indices](int i) {
        indices.push_back(i);
    });
    
    ASSERT_EQ(indices.size(), 3u);
    EXPECT_EQ(indices[0], 0);
    EXPECT_EQ(indices[1], 1);
    EXPECT_EQ(indices[2], 2);
}

// Test measure with single repeat and no-arg callable
TEST_F(ChronometerTest_891, MeasureSingleRepeatNoArg_891) {
    Catch::Benchmark::Chronometer chrono(mockConcept, 1);
    
    EXPECT_CALL(mockConcept, start()).Times(1);
    EXPECT_CALL(mockConcept, finish()).Times(1);
    
    int callCount = 0;
    chrono.measure([&callCount]() {
        callCount++;
    });
    
    EXPECT_EQ(callCount, 1);
}

// Test measure with single repeat and int-arg callable
TEST_F(ChronometerTest_891, MeasureSingleRepeatWithIntArg_891) {
    Catch::Benchmark::Chronometer chrono(mockConcept, 1);
    
    EXPECT_CALL(mockConcept, start()).Times(1);
    EXPECT_CALL(mockConcept, finish()).Times(1);
    
    std::vector<int> indices;
    chrono.measure([&indices](int i) {
        indices.push_back(i);
    });
    
    ASSERT_EQ(indices.size(), 1u);
    EXPECT_EQ(indices[0], 0);
}

// Test that start is called before the callable and finish is called after
TEST_F(ChronometerTest_891, MeasureCallsStartBeforeAndFinishAfter_891) {
    int repeats = 3;
    Catch::Benchmark::Chronometer chrono(mockConcept, repeats);
    
    ::testing::InSequence seq;
    EXPECT_CALL(mockConcept, start()).Times(1);
    EXPECT_CALL(mockConcept, finish()).Times(1);
    
    chrono.measure([]() {});
}

// Test measure with zero repeats - callable should not be called (or called 0 times)
TEST_F(ChronometerTest_891, MeasureZeroRepeatsNoArg_891) {
    Catch::Benchmark::Chronometer chrono(mockConcept, 0);
    
    EXPECT_CALL(mockConcept, start()).Times(1);
    EXPECT_CALL(mockConcept, finish()).Times(1);
    
    int callCount = 0;
    chrono.measure([&callCount]() {
        callCount++;
    });
    
    EXPECT_EQ(callCount, 0);
}

} // namespace
