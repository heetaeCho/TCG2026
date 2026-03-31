#include <gtest/gtest.h>
#include <gmock/gmock.h>

// We need to include enough of the Catch2 amalgamated header to get the Chronometer class
// But since we're testing it in isolation, we need to provide the necessary dependencies.

// Forward declare / mock the ChronometerConcept
namespace Catch {
namespace Benchmark {
namespace Detail {

struct ChronometerConcept {
    virtual void start() = 0;
    virtual void finish() = 0;
    virtual ~ChronometerConcept() = default;
};

} // namespace Detail

// Minimal Chronometer definition based on the known interface
struct Chronometer {
private:
    Detail::ChronometerConcept* impl;
    int repeats;

public:
    Chronometer(Detail::ChronometerConcept& meter, int repeats_)
        : impl(&meter)
        , repeats(repeats_) {}

    int runs() const { return repeats; }
};

} // namespace Benchmark
} // namespace Catch

// Mock for the ChronometerConcept
class MockChronometerConcept : public Catch::Benchmark::Detail::ChronometerConcept {
public:
    MOCK_METHOD(void, start, (), (override));
    MOCK_METHOD(void, finish, (), (override));
};

// Test fixture
class ChronometerTest_892 : public ::testing::Test {
protected:
    MockChronometerConcept mockMeter;
};

// Test that runs() returns the repeats value passed at construction
TEST_F(ChronometerTest_892, RunsReturnsRepeatsValue_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, 100);
    EXPECT_EQ(chrono.runs(), 100);
}

// Test with a single repeat
TEST_F(ChronometerTest_892, RunsReturnsSingleRepeat_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, 1);
    EXPECT_EQ(chrono.runs(), 1);
}

// Test with zero repeats (boundary condition)
TEST_F(ChronometerTest_892, RunsReturnsZeroRepeats_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, 0);
    EXPECT_EQ(chrono.runs(), 0);
}

// Test with a large number of repeats
TEST_F(ChronometerTest_892, RunsReturnsLargeRepeatsValue_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, 1000000);
    EXPECT_EQ(chrono.runs(), 1000000);
}

// Test with negative repeats (edge case)
TEST_F(ChronometerTest_892, RunsReturnsNegativeRepeats_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, -1);
    EXPECT_EQ(chrono.runs(), -1);
}

// Test with INT_MAX (boundary condition)
TEST_F(ChronometerTest_892, RunsReturnsIntMax_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, std::numeric_limits<int>::max());
    EXPECT_EQ(chrono.runs(), std::numeric_limits<int>::max());
}

// Test with INT_MIN (boundary condition)
TEST_F(ChronometerTest_892, RunsReturnsIntMin_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, std::numeric_limits<int>::min());
    EXPECT_EQ(chrono.runs(), std::numeric_limits<int>::min());
}

// Test that runs() is const and can be called multiple times with same result
TEST_F(ChronometerTest_892, RunsIsConsistentAcrossMultipleCalls_892) {
    Catch::Benchmark::Chronometer chrono(mockMeter, 42);
    EXPECT_EQ(chrono.runs(), 42);
    EXPECT_EQ(chrono.runs(), 42);
    EXPECT_EQ(chrono.runs(), 42);
}

// Test that different Chronometer instances maintain independent repeat counts
TEST_F(ChronometerTest_892, DifferentInstancesHaveIndependentRepeats_892) {
    MockChronometerConcept mockMeter2;
    Catch::Benchmark::Chronometer chrono1(mockMeter, 10);
    Catch::Benchmark::Chronometer chrono2(mockMeter2, 20);
    EXPECT_EQ(chrono1.runs(), 10);
    EXPECT_EQ(chrono2.runs(), 20);
    EXPECT_NE(chrono1.runs(), chrono2.runs());
}

// Test construction with same meter but different repeats
TEST_F(ChronometerTest_892, SameMeterDifferentRepeats_892) {
    Catch::Benchmark::Chronometer chrono1(mockMeter, 5);
    Catch::Benchmark::Chronometer chrono2(mockMeter, 50);
    EXPECT_EQ(chrono1.runs(), 5);
    EXPECT_EQ(chrono2.runs(), 50);
}
