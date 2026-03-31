#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"

// A simple generator that produces values from a fixed sequence
template <typename T>
class FixedValuesGenerator : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    FixedValuesGenerator(std::vector<T> values) : m_values(std::move(values)) {
        assert(!m_values.empty());
    }

    T const& get() const override {
        return m_values[m_index];
    }

    bool next() override {
        if (m_index + 1 < m_values.size()) {
            ++m_index;
            return true;
        }
        return false;
    }
};

template <typename T>
Catch::Generators::GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValuesGenerator<T>>(std::move(values))
    );
}

class TakeGeneratorTest_920 : public ::testing::Test {
protected:
};

TEST_F(TakeGeneratorTest_920, GetReturnsFirstValueInitially_920) {
    auto gen = makeFixedGenerator<int>({10, 20, 30, 40, 50});
    Catch::Generators::TakeGenerator<int> take(3, std::move(gen));
    
    EXPECT_EQ(take.get(), 10);
}

TEST_F(TakeGeneratorTest_920, NextReturnsTrueWithinTarget_920) {
    auto gen = makeFixedGenerator<int>({10, 20, 30, 40, 50});
    Catch::Generators::TakeGenerator<int> take(3, std::move(gen));
    
    // Should be able to advance (first next -> second element, still within target of 3)
    EXPECT_TRUE(take.next());
    EXPECT_EQ(take.get(), 20);
}

TEST_F(TakeGeneratorTest_920, NextReturnsTrueUpToTargetMinusOne_920) {
    auto gen = makeFixedGenerator<int>({10, 20, 30, 40, 50});
    Catch::Generators::TakeGenerator<int> take(3, std::move(gen));
    
    EXPECT_TRUE(take.next());  // returned=1, get()=20
    EXPECT_TRUE(take.next());  // returned=2, get()=30
    EXPECT_EQ(take.get(), 30);
}

TEST_F(TakeGeneratorTest_920, NextReturnsFalseAfterTargetReached_920) {
    auto gen = makeFixedGenerator<int>({10, 20, 30, 40, 50});
    Catch::Generators::TakeGenerator<int> take(3, std::move(gen));
    
    EXPECT_TRUE(take.next());   // 2nd element
    EXPECT_TRUE(take.next());   // 3rd element
    EXPECT_FALSE(take.next());  // beyond target
}

TEST_F(TakeGeneratorTest_920, TakeOneElement_920) {
    auto gen = makeFixedGenerator<int>({42, 43, 44});
    Catch::Generators::TakeGenerator<int> take(1, std::move(gen));
    
    EXPECT_EQ(take.get(), 42);
    EXPECT_FALSE(take.next());  // Only 1 element requested
}

TEST_F(TakeGeneratorTest_920, TakeMoreThanAvailable_920) {
    auto gen = makeFixedGenerator<int>({1, 2});
    Catch::Generators::TakeGenerator<int> take(5, std::move(gen));
    
    EXPECT_EQ(take.get(), 1);
    EXPECT_TRUE(take.next());
    EXPECT_EQ(take.get(), 2);
    // Underlying generator exhausted before target
    EXPECT_FALSE(take.next());
}

TEST_F(TakeGeneratorTest_920, TakeExactlyAvailableCount_920) {
    auto gen = makeFixedGenerator<int>({100, 200, 300});
    Catch::Generators::TakeGenerator<int> take(3, std::move(gen));
    
    EXPECT_EQ(take.get(), 100);
    EXPECT_TRUE(take.next());
    EXPECT_EQ(take.get(), 200);
    EXPECT_TRUE(take.next());
    EXPECT_EQ(take.get(), 300);
    EXPECT_FALSE(take.next());
}

TEST_F(TakeGeneratorTest_920, TakeWithStringType_920) {
    auto gen = makeFixedGenerator<std::string>({"hello", "world", "foo", "bar"});
    Catch::Generators::TakeGenerator<std::string> take(2, std::move(gen));
    
    EXPECT_EQ(take.get(), "hello");
    EXPECT_TRUE(take.next());
    EXPECT_EQ(take.get(), "world");
    EXPECT_FALSE(take.next());
}

TEST_F(TakeGeneratorTest_920, TakeZeroElements_920) {
    auto gen = makeFixedGenerator<int>({1, 2, 3});
    Catch::Generators::TakeGenerator<int> take(0, std::move(gen));
    
    // With target=0, next() should immediately return false
    EXPECT_FALSE(take.next());
}

TEST_F(TakeGeneratorTest_920, GetIsConsistentWithoutNext_920) {
    auto gen = makeFixedGenerator<int>({7, 8, 9});
    Catch::Generators::TakeGenerator<int> take(3, std::move(gen));
    
    // Calling get() multiple times without next() should return same value
    EXPECT_EQ(take.get(), 7);
    EXPECT_EQ(take.get(), 7);
    EXPECT_EQ(take.get(), 7);
}

TEST_F(TakeGeneratorTest_920, SequentialGetAfterNext_920) {
    auto gen = makeFixedGenerator<double>({1.1, 2.2, 3.3, 4.4});
    Catch::Generators::TakeGenerator<double> take(4, std::move(gen));
    
    EXPECT_DOUBLE_EQ(take.get(), 1.1);
    EXPECT_TRUE(take.next());
    EXPECT_DOUBLE_EQ(take.get(), 2.2);
    EXPECT_TRUE(take.next());
    EXPECT_DOUBLE_EQ(take.get(), 3.3);
    EXPECT_TRUE(take.next());
    EXPECT_DOUBLE_EQ(take.get(), 4.4);
    EXPECT_FALSE(take.next());
}

TEST_F(TakeGeneratorTest_920, TakeLargeTarget_920) {
    std::vector<int> values;
    for (int i = 0; i < 1000; ++i) {
        values.push_back(i);
    }
    auto gen = makeFixedGenerator<int>(values);
    Catch::Generators::TakeGenerator<int> take(500, std::move(gen));
    
    EXPECT_EQ(take.get(), 0);
    int count = 0;
    while (take.next()) {
        count++;
    }
    // Should have advanced 499 times (500 elements total, first is free)
    EXPECT_EQ(count, 499);
}
