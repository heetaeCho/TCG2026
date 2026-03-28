#include <catch2/generators/catch_generators.hpp>
#include <catch2/generators/catch_generators_adapters.hpp>
#include <catch2/generators/catch_generators_random.hpp>
#include <catch2/generators/catch_generators_range.hpp>
#include <gtest/gtest.h>
#include <string>
#include <memory>
#include <vector>

using namespace Catch::Generators;

// A simple custom generator for testing
template<typename T>
class FixedValueGenerator final : public Catch::Generators::IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    explicit FixedValueGenerator(std::vector<T> values) : m_values(std::move(values)) {
        assert(!m_values.empty());
    }

    T const& get() const override {
        return m_values[m_index];
    }

    bool next() override {
        ++m_index;
        return m_index < m_values.size();
    }
};

template<typename T>
GeneratorWrapper<T> makeFixedValueWrapper(std::vector<T> values) {
    return GeneratorWrapper<T>(
        Catch::Detail::make_unique<FixedValueGenerator<T>>(std::move(values))
    );
}

class MakeGeneratorsTest_324 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(MakeGeneratorsTest_324, CreateFromIntGenerator_324) {
    auto wrapper = makeFixedValueWrapper<int>({1, 2, 3});
    auto generators = makeGenerators<int>(std::move(wrapper));
    
    // The Generators object should be valid after construction
    // We can verify the first value is accessible
    EXPECT_EQ(generators.get(), 1);
}

TEST_F(MakeGeneratorsTest_324, IterateThroughValues_324) {
    auto wrapper = makeFixedValueWrapper<int>({10, 20, 30});
    auto generators = makeGenerators<int>(std::move(wrapper));
    
    EXPECT_EQ(generators.get(), 10);
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), 20);
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), 30);
    EXPECT_FALSE(generators.next());
}

TEST_F(MakeGeneratorsTest_324, SingleValueGenerator_324) {
    auto wrapper = makeFixedValueWrapper<int>({42});
    auto generators = makeGenerators<int>(std::move(wrapper));
    
    EXPECT_EQ(generators.get(), 42);
    EXPECT_FALSE(generators.next());
}

TEST_F(MakeGeneratorsTest_324, StringTypeGenerator_324) {
    auto wrapper = makeFixedValueWrapper<std::string>({"hello", "world"});
    auto generators = makeGenerators<std::string>(std::move(wrapper));
    
    EXPECT_EQ(generators.get(), "hello");
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), "world");
    EXPECT_FALSE(generators.next());
}

TEST_F(MakeGeneratorsTest_324, DoubleTypeGenerator_324) {
    auto wrapper = makeFixedValueWrapper<double>({1.5, 2.5, 3.5});
    auto generators = makeGenerators<double>(std::move(wrapper));
    
    EXPECT_DOUBLE_EQ(generators.get(), 1.5);
    EXPECT_TRUE(generators.next());
    EXPECT_DOUBLE_EQ(generators.get(), 2.5);
    EXPECT_TRUE(generators.next());
    EXPECT_DOUBLE_EQ(generators.get(), 3.5);
    EXPECT_FALSE(generators.next());
}

TEST_F(MakeGeneratorsTest_324, BoolTypeGenerator_324) {
    auto wrapper = makeFixedValueWrapper<bool>({true, false, true});
    auto generators = makeGenerators<bool>(std::move(wrapper));
    
    EXPECT_EQ(generators.get(), true);
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), false);
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), true);
    EXPECT_FALSE(generators.next());
}

TEST_F(MakeGeneratorsTest_324, LargeNumberOfValues_324) {
    std::vector<int> values;
    for (int i = 0; i < 1000; ++i) {
        values.push_back(i);
    }
    auto wrapper = makeFixedValueWrapper<int>(values);
    auto generators = makeGenerators<int>(std::move(wrapper));
    
    EXPECT_EQ(generators.get(), 0);
    for (int i = 1; i < 1000; ++i) {
        EXPECT_TRUE(generators.next());
        EXPECT_EQ(generators.get(), i);
    }
    EXPECT_FALSE(generators.next());
}

TEST_F(MakeGeneratorsTest_324, NegativeIntValues_324) {
    auto wrapper = makeFixedValueWrapper<int>({-1, -100, 0, 100});
    auto generators = makeGenerators<int>(std::move(wrapper));
    
    EXPECT_EQ(generators.get(), -1);
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), -100);
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), 0);
    EXPECT_TRUE(generators.next());
    EXPECT_EQ(generators.get(), 100);
    EXPECT_FALSE(generators.next());
}

TEST_F(MakeGeneratorsTest_324, GetWithoutNextReturnsFirstValue_324) {
    auto wrapper = makeFixedValueWrapper<int>({5, 10, 15});
    auto generators = makeGenerators<int>(std::move(wrapper));
    
    // Calling get() multiple times without next should return same value
    EXPECT_EQ(generators.get(), 5);
    EXPECT_EQ(generators.get(), 5);
    EXPECT_EQ(generators.get(), 5);
}

TEST_F(MakeGeneratorsTest_324, EmptyStringValue_324) {
    auto wrapper = makeFixedValueWrapper<std::string>({""});
    auto generators = makeGenerators<std::string>(std::move(wrapper));
    
    EXPECT_EQ(generators.get(), "");
    EXPECT_FALSE(generators.next());
}
