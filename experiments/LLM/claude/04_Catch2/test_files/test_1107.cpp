#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <memory>

// We need to include the Catch2 header for the TakeGenerator
// But since we're testing with Google Test, we'll create a minimal mock setup

// Minimal reimplementation of Catch2 generator interfaces needed for testing
namespace Catch {
namespace Generators {

template <typename T>
class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual T const& get() const = 0;
    virtual bool next() = 0;
};

template <typename T>
class GeneratorWrapper {
    std::unique_ptr<IGenerator<T>> m_generator;
public:
    GeneratorWrapper(std::unique_ptr<IGenerator<T>> generator)
        : m_generator(std::move(generator)) {}
    
    T const& get() const { return m_generator->get(); }
    bool next() { return m_generator->next(); }
};

#define CATCH_MOVE(x) std::move(x)

template <typename T>
class TakeGenerator : public IGenerator<T> {
    GeneratorWrapper<T> m_generator;
    size_t m_returned = 0;
    size_t m_target;
public:
    TakeGenerator(size_t target, GeneratorWrapper<T>&& generator)
        : m_generator(CATCH_MOVE(generator)), m_target(target) {
        assert(target != 0 && "Empty generators are not allowed");
    }

    T const& get() const override {
        return m_generator.get();
    }

    bool next() override {
        ++m_returned;
        if (m_returned >= m_target) {
            return false;
        }
        return m_generator.next();
    }
};

} // namespace Generators
} // namespace Catch

// Mock generator for testing
template <typename T>
class MockInnerGenerator : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    MockInnerGenerator(std::vector<T> values) : m_values(std::move(values)) {
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
Catch::Generators::GeneratorWrapper<T> makeWrapper(std::vector<T> values) {
    return Catch::Generators::GeneratorWrapper<T>(
        std::make_unique<MockInnerGenerator<T>>(std::move(values))
    );
}

class TakeGeneratorTest_1107 : public ::testing::Test {
protected:
    // Helper to create a TakeGenerator with given target and values
};

// Test: get() returns the first element initially
TEST_F(TakeGeneratorTest_1107, GetReturnsFirstElement_1107) {
    auto wrapper = makeWrapper<int>({10, 20, 30, 40, 50});
    Catch::Generators::TakeGenerator<int> gen(3, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 10);
}

// Test: next() advances and get() returns next element
TEST_F(TakeGeneratorTest_1107, NextAdvancesAndGetReturnsNextElement_1107) {
    auto wrapper = makeWrapper<int>({10, 20, 30, 40, 50});
    Catch::Generators::TakeGenerator<int> gen(3, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
}

// Test: TakeGenerator stops after target elements
TEST_F(TakeGeneratorTest_1107, StopsAfterTargetElements_1107) {
    auto wrapper = makeWrapper<int>({10, 20, 30, 40, 50});
    Catch::Generators::TakeGenerator<int> gen(3, std::move(wrapper));
    
    // First element is already available via get()
    EXPECT_EQ(gen.get(), 10);
    
    EXPECT_TRUE(gen.next());   // 2nd element
    EXPECT_EQ(gen.get(), 20);
    
    EXPECT_FALSE(gen.next());  // 3rd would exceed target
}

// Test: TakeGenerator with target of 1 returns false on first next()
TEST_F(TakeGeneratorTest_1107, TargetOneReturnsFalseOnFirstNext_1107) {
    auto wrapper = makeWrapper<int>({10, 20, 30});
    Catch::Generators::TakeGenerator<int> gen(1, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 10);
    EXPECT_FALSE(gen.next());
}

// Test: TakeGenerator with target equal to inner generator size
TEST_F(TakeGeneratorTest_1107, TargetEqualsInnerSize_1107) {
    auto wrapper = makeWrapper<int>({10, 20, 30});
    Catch::Generators::TakeGenerator<int> gen(3, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_FALSE(gen.next());
}

// Test: TakeGenerator with target larger than inner generator size
TEST_F(TakeGeneratorTest_1107, TargetLargerThanInnerSize_1107) {
    auto wrapper = makeWrapper<int>({10, 20});
    Catch::Generators::TakeGenerator<int> gen(5, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    // Inner generator exhausted, next should return false
    EXPECT_FALSE(gen.next());
}

// Test: TakeGenerator with string type
TEST_F(TakeGeneratorTest_1107, WorksWithStringType_1107) {
    auto wrapper = makeWrapper<std::string>({"hello", "world", "foo", "bar"});
    Catch::Generators::TakeGenerator<std::string> gen(2, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), "hello");
    EXPECT_FALSE(gen.next());
}

// Test: TakeGenerator with double type
TEST_F(TakeGeneratorTest_1107, WorksWithDoubleType_1107) {
    auto wrapper = makeWrapper<double>({1.1, 2.2, 3.3});
    Catch::Generators::TakeGenerator<double> gen(2, std::move(wrapper));
    
    EXPECT_DOUBLE_EQ(gen.get(), 1.1);
    EXPECT_FALSE(gen.next());
}

// Test: get() is const and can be called multiple times
TEST_F(TakeGeneratorTest_1107, GetCanBeCalledMultipleTimes_1107) {
    auto wrapper = makeWrapper<int>({42, 99});
    Catch::Generators::TakeGenerator<int> gen(2, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);  // Calling get() again without next() returns same value
    EXPECT_EQ(gen.get(), 42);
}

// Test: Verify all taken values in sequence
TEST_F(TakeGeneratorTest_1107, VerifyAllTakenValuesInSequence_1107) {
    auto wrapper = makeWrapper<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    Catch::Generators::TakeGenerator<int> gen(5, std::move(wrapper));
    
    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    
    // We expect exactly min(target, inner_size) - but target controls the count
    // With target=5 and inner size=10, we should get 5 elements
    EXPECT_EQ(collected.size(), 5u);
    EXPECT_EQ(collected[0], 1);
    EXPECT_EQ(collected[1], 2);
    EXPECT_EQ(collected[2], 3);
    EXPECT_EQ(collected[3], 4);
    EXPECT_EQ(collected[4], 5);
}

// Test: TakeGenerator with single element inner generator and target 1
TEST_F(TakeGeneratorTest_1107, SingleElementInnerTargetOne_1107) {
    auto wrapper = makeWrapper<int>({100});
    Catch::Generators::TakeGenerator<int> gen(1, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 100);
    EXPECT_FALSE(gen.next());
}

// Test: TakeGenerator target=0 should trigger assert (death test)
TEST_F(TakeGeneratorTest_1107, TargetZeroTriggersAssert_1107) {
    EXPECT_DEATH({
        auto wrapper = makeWrapper<int>({1, 2, 3});
        Catch::Generators::TakeGenerator<int> gen(0, std::move(wrapper));
    }, "");
}

// Test: Large target value
TEST_F(TakeGeneratorTest_1107, LargeTargetValue_1107) {
    auto wrapper = makeWrapper<int>({1, 2, 3});
    Catch::Generators::TakeGenerator<int> gen(1000000, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 3);
    // Inner generator exhausted before target reached
    EXPECT_FALSE(gen.next());
}

// Test: next() returns false and stays false after exhaustion
TEST_F(TakeGeneratorTest_1107, NextReturnsFalseAfterExhaustion_1107) {
    auto wrapper = makeWrapper<int>({10, 20, 30});
    Catch::Generators::TakeGenerator<int> gen(2, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), 10);
    EXPECT_FALSE(gen.next());  // target reached after 2nd
    // Calling next again - behavior may vary but target is already reached
    EXPECT_FALSE(gen.next());
}

// Test: TakeGenerator with negative values
TEST_F(TakeGeneratorTest_1107, WorksWithNegativeValues_1107) {
    auto wrapper = makeWrapper<int>({-5, -3, -1, 0, 1});
    Catch::Generators::TakeGenerator<int> gen(3, std::move(wrapper));
    
    EXPECT_EQ(gen.get(), -5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -3);
    EXPECT_FALSE(gen.next());
}
