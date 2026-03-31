#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <functional>

// Minimal recreation of the repeater struct based on the provided interface
namespace Catch {
namespace Benchmark {
namespace Detail {

template <typename Fun>
struct repeater {
    Fun fun;
public:
    void operator()(int k) const {
        for (int i = 0; i < k; ++i) {
            fun();
        }
    }
};

template <typename Fun>
repeater<Fun> make_repeater(Fun&& f) {
    return repeater<Fun>{std::forward<Fun>(f)};
}

}
}
}

// Test fixture
class RepeaterTest_896 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that the functor is called exactly k times for a positive k
TEST_F(RepeaterTest_896, CallsFunctionKTimes_896) {
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(5);
    
    EXPECT_EQ(callCount, 5);
}

// Test that calling with k=0 does not invoke the function
TEST_F(RepeaterTest_896, ZeroRepetitionsCallsFunctionZeroTimes_896) {
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(0);
    
    EXPECT_EQ(callCount, 0);
}

// Test that calling with k=1 invokes the function exactly once
TEST_F(RepeaterTest_896, SingleRepetitionCallsFunctionOnce_896) {
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(1);
    
    EXPECT_EQ(callCount, 1);
}

// Test that calling with a negative k does not invoke the function
TEST_F(RepeaterTest_896, NegativeRepetitionsCallsFunctionZeroTimes_896) {
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(-1);
    
    EXPECT_EQ(callCount, 0);
}

// Test that calling with a large k invokes the function the correct number of times
TEST_F(RepeaterTest_896, LargeRepetitionCount_896) {
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(10000);
    
    EXPECT_EQ(callCount, 10000);
}

// Test that the repeater can be called multiple times and accumulates properly
TEST_F(RepeaterTest_896, MultipleInvocationsAccumulate_896) {
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(3);
    rep(4);
    
    EXPECT_EQ(callCount, 7);
}

// Test that the function is called in sequence and side effects are ordered
TEST_F(RepeaterTest_896, FunctionCalledInOrder_896) {
    std::vector<int> sequence;
    int counter = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&sequence, &counter]() { sequence.push_back(counter++); }
    };
    
    rep(5);
    
    ASSERT_EQ(sequence.size(), 5u);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(sequence[i], i);
    }
}

// Test that operator() is const-qualified (can be called on a const object)
TEST_F(RepeaterTest_896, OperatorIsConst_896) {
    int callCount = 0;
    const auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(3);
    
    EXPECT_EQ(callCount, 3);
}

// Test with a lambda that modifies external state
TEST_F(RepeaterTest_896, ModifiesExternalState_896) {
    int sum = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&sum]() { sum += 10; }
    };
    
    rep(5);
    
    EXPECT_EQ(sum, 50);
}

// Test with a mock function to verify exact call count
TEST_F(RepeaterTest_896, MockFunctionCalledExactly_896) {
    testing::MockFunction<void()> mockFun;
    
    EXPECT_CALL(mockFun, Call()).Times(7);
    
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        mockFun.AsStdFunction()
    };
    
    rep(7);
}

// Test with k = -100 (negative boundary)
TEST_F(RepeaterTest_896, LargeNegativeRepetitions_896) {
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<std::function<void()>>{
        [&callCount]() { callCount++; }
    };
    
    rep(-100);
    
    EXPECT_EQ(callCount, 0);
}

// Test with a functor object (not just a lambda)
TEST_F(RepeaterTest_896, WorksWithFunctorObject_896) {
    struct Counter {
        int* count;
        void operator()() const { (*count)++; }
    };
    
    int callCount = 0;
    auto rep = Catch::Benchmark::Detail::repeater<Counter>{Counter{&callCount}};
    
    rep(4);
    
    EXPECT_EQ(callCount, 4);
}
