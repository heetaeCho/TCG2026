#include <gtest/gtest.h>
#include "./TestProjects/Catch2/extras/catch_amalgamated.hpp"
#include <vector>

// A simple generator that produces values from a vector
template <typename T>
class FixedGenerator : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    explicit FixedGenerator(std::vector<T> values)
        : m_values(std::move(values)) {
        assert(!m_values.empty());
    }

    T const& get() const override {
        return m_values[m_index];
    }

    bool next() override {
        if (m_index + 1 >= m_values.size()) {
            return false;
        }
        ++m_index;
        return true;
    }
};

template <typename T>
Catch::Generators::GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return Catch::Generators::GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedGenerator<T>>(std::move(values))
    );
}

class TakeGeneratorTest_921 : public ::testing::Test {};

// Test that taking 0 elements returns false on first next()
TEST_F(TakeGeneratorTest_921, TakeZeroReturnsfalseImmediately_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        0, makeFixedGenerator<int>({1, 2, 3})
    );
    // m_returned starts at 0, target is 0, so first next() increments to 1 >= 0 => false
    EXPECT_FALSE(gen.next());
}

// Test that taking 1 element: first next() returns false (already consumed the initial element via get)
TEST_F(TakeGeneratorTest_921, TakeOneElementNextReturnsFalse_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        1, makeFixedGenerator<int>({10, 20, 30})
    );
    // get() should return first element
    EXPECT_EQ(gen.get(), 10);
    // next(): m_returned becomes 1, 1 >= 1 => false
    EXPECT_FALSE(gen.next());
}

// Test taking multiple elements works correctly
TEST_F(TakeGeneratorTest_921, TakeThreeFromFiveElements_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        3, makeFixedGenerator<int>({10, 20, 30, 40, 50})
    );
    EXPECT_EQ(gen.get(), 10);

    // next() #1: m_returned=1, 1 < 3, delegates to underlying => true
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);

    // next() #2: m_returned=2, 2 < 3, delegates to underlying => true
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);

    // next() #3: m_returned=3, 3 >= 3 => false
    EXPECT_FALSE(gen.next());
}

// Test that when underlying generator exhausts before target, next returns false
TEST_F(TakeGeneratorTest_921, UnderlyingExhaustsBeforeTarget_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        5, makeFixedGenerator<int>({10, 20})
    );
    EXPECT_EQ(gen.get(), 10);

    // next() #1: m_returned=1, 1 < 5, underlying next() => true (moves to 20)
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);

    // next() #2: m_returned=2, 2 < 5, underlying next() => false, m_returned set to 5
    EXPECT_FALSE(gen.next());
}

// Test taking exactly as many elements as available
TEST_F(TakeGeneratorTest_921, TakeExactlyAvailableCount_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        3, makeFixedGenerator<int>({1, 2, 3})
    );
    EXPECT_EQ(gen.get(), 1);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    // next() #3: m_returned=3, 3 >= 3 => false
    EXPECT_FALSE(gen.next());
}

// Test that after exhaustion, subsequent next() calls still return false
TEST_F(TakeGeneratorTest_921, AfterExhaustionNextStillReturnsFalse_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        2, makeFixedGenerator<int>({10, 20, 30})
    );
    EXPECT_EQ(gen.get(), 10);

    EXPECT_TRUE(gen.next());
    EXPECT_FALSE(gen.next());
    // Calling next again should still be false (m_returned keeps incrementing past target)
    EXPECT_FALSE(gen.next());
}

// Test with a single-element underlying generator and target > 1
TEST_F(TakeGeneratorTest_921, SingleElementGeneratorWithLargerTarget_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        10, makeFixedGenerator<int>({42})
    );
    EXPECT_EQ(gen.get(), 42);

    // Underlying has only one element, next() on underlying returns false
    EXPECT_FALSE(gen.next());
}

// Test with string type
TEST_F(TakeGeneratorTest_921, WorksWithStringType_921) {
    auto gen = Catch::Generators::TakeGenerator<std::string>(
        2, makeFixedGenerator<std::string>({"hello", "world", "foo"})
    );
    EXPECT_EQ(gen.get(), "hello");

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");

    EXPECT_FALSE(gen.next());
}

// Test take with large target but small source
TEST_F(TakeGeneratorTest_921, LargeTargetSmallSource_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        1000000, makeFixedGenerator<int>({1, 2, 3})
    );
    EXPECT_EQ(gen.get(), 1);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);

    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);

    // Underlying exhausted
    EXPECT_FALSE(gen.next());
}

// Test get() returns correct value without calling next
TEST_F(TakeGeneratorTest_921, GetReturnsFirstValueWithoutNext_921) {
    auto gen = Catch::Generators::TakeGenerator<int>(
        3, makeFixedGenerator<int>({99, 100, 101})
    );
    // Multiple calls to get() without next() should return same value
    EXPECT_EQ(gen.get(), 99);
    EXPECT_EQ(gen.get(), 99);
}
