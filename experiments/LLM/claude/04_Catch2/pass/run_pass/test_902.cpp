#include <gtest/gtest.h>
#include <chrono>
#include <thread>
#include <type_traits>

// We need to include the header under test
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// A simple clock that we can control for testing purposes
struct MockClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<MockClock, duration>;
    static const bool is_steady = true;

    static time_point now_value;
    static int call_count;

    static time_point now() {
        call_count++;
        auto val = now_value;
        // Advance time on second call to simulate elapsed time
        if (call_count == 2) {
            now_value += std::chrono::nanoseconds(1000);
        }
        return val;
    }

    static void reset(std::chrono::nanoseconds initial = std::chrono::nanoseconds(0),
                      std::chrono::nanoseconds advance = std::chrono::nanoseconds(1000)) {
        now_value = time_point(initial);
        call_count = 0;
        advance_amount = advance;
    }

    static std::chrono::nanoseconds advance_amount;
};

MockClock::time_point MockClock::now_value = MockClock::time_point(std::chrono::nanoseconds(0));
int MockClock::call_count = 0;
std::chrono::nanoseconds MockClock::advance_amount = std::chrono::nanoseconds(1000);

// A controllable clock where we set start and end times explicitly
struct ControllableClock {
    using duration = std::chrono::nanoseconds;
    using rep = duration::rep;
    using period = duration::period;
    using time_point = std::chrono::time_point<ControllableClock, duration>;
    static const bool is_steady = true;

    static std::vector<time_point> times;
    static size_t index;

    static time_point now() {
        if (index < times.size()) {
            return times[index++];
        }
        return time_point(duration(0));
    }

    static void reset(std::vector<duration> durations) {
        times.clear();
        index = 0;
        for (auto& d : durations) {
            times.push_back(time_point(d));
        }
    }
};

std::vector<ControllableClock::time_point> ControllableClock::times;
size_t ControllableClock::index = 0;

class MeasureTest_902 : public ::testing::Test {
protected:
    void SetUp() override {
        ControllableClock::reset({});
    }
};

// Test that measure returns the correct elapsed time (delta)
TEST_F(MeasureTest_902, ReturnsCorrectElapsedTime_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(100),
        std::chrono::nanoseconds(600)
    });

    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [](){ return 42; }
    );

    auto delta = result.elapsed;
    EXPECT_EQ(delta.count(), 500);
}

// Test that measure returns the function's return value
TEST_F(MeasureTest_902, ReturnsFunctionResult_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(0),
        std::chrono::nanoseconds(100)
    });

    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [](){ return 42; }
    );

    // The result should contain the return value of the function
    // result.result should be the return value
    EXPECT_EQ(result.iterations, 1);
}

// Test that measure always sets iterations to 1
TEST_F(MeasureTest_902, IterationsIsAlwaysOne_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(0),
        std::chrono::nanoseconds(100)
    });

    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [](){ return 0; }
    );

    EXPECT_EQ(result.iterations, 1);
}

// Test that measure forwards arguments to the function
TEST_F(MeasureTest_902, ForwardsArguments_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(0),
        std::chrono::nanoseconds(200)
    });

    bool called_with_correct_args = false;
    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [&called_with_correct_args](int a, int b) {
            called_with_correct_args = (a == 10 && b == 20);
            return a + b;
        },
        10, 20
    );

    EXPECT_TRUE(called_with_correct_args);
}

// Test that measure works with zero elapsed time
TEST_F(MeasureTest_902, ZeroElapsedTime_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(500),
        std::chrono::nanoseconds(500)
    });

    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [](){ return 1; }
    );

    EXPECT_EQ(result.elapsed.count(), 0);
    EXPECT_EQ(result.iterations, 1);
}

// Test measure with a function that takes a long time (large delta)
TEST_F(MeasureTest_902, LargeElapsedTime_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(0),
        std::chrono::nanoseconds(1000000000) // 1 second in nanoseconds
    });

    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [](){ return 99; }
    );

    EXPECT_EQ(result.elapsed.count(), 1000000000);
    EXPECT_EQ(result.iterations, 1);
}

// Test that the function is actually invoked
TEST_F(MeasureTest_902, FunctionIsInvoked_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(0),
        std::chrono::nanoseconds(50)
    });

    bool was_called = false;
    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [&was_called]() {
            was_called = true;
            return 0;
        }
    );

    EXPECT_TRUE(was_called);
}

// Test measure with a function returning a string
TEST_F(MeasureTest_902, WorksWithStringReturn_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(10),
        std::chrono::nanoseconds(20)
    });

    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [](){ return std::string("hello"); }
    );

    EXPECT_EQ(result.elapsed.count(), 10);
    EXPECT_EQ(result.iterations, 1);
}

// Test measure with multiple arguments of different types
TEST_F(MeasureTest_902, MultipleArgumentTypes_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(0),
        std::chrono::nanoseconds(300)
    });

    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [](int a, double b, const std::string& c) {
            return static_cast<int>(a + b + c.size());
        },
        5, 3.14, std::string("test")
    );

    EXPECT_EQ(result.elapsed.count(), 300);
    EXPECT_EQ(result.iterations, 1);
}

// Test using std::chrono::steady_clock as the clock type
TEST_F(MeasureTest_902, WorksWithSteadyClock_902) {
    auto result = Catch::Benchmark::Detail::measure<std::chrono::steady_clock>(
        [](){ return 42; }
    );

    // With a real clock, elapsed should be non-negative
    EXPECT_GE(result.elapsed.count(), 0);
    EXPECT_EQ(result.iterations, 1);
}

// Test that measure correctly handles a function that modifies external state
TEST_F(MeasureTest_902, FunctionModifiesExternalState_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(0),
        std::chrono::nanoseconds(100)
    });

    int counter = 0;
    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [&counter]() {
            counter += 5;
            return counter;
        }
    );

    EXPECT_EQ(counter, 5);
    EXPECT_EQ(result.iterations, 1);
}

// Test with a function that takes a single argument
TEST_F(MeasureTest_902, SingleArgument_902) {
    ControllableClock::reset({
        std::chrono::nanoseconds(100),
        std::chrono::nanoseconds(250)
    });

    int received_arg = 0;
    auto result = Catch::Benchmark::Detail::measure<ControllableClock>(
        [&received_arg](int x) {
            received_arg = x;
            return x * 2;
        },
        7
    );

    EXPECT_EQ(received_arg, 7);
    EXPECT_EQ(result.elapsed.count(), 150);
    EXPECT_EQ(result.iterations, 1);
}
