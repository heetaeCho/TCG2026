#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <initializer_list>

// Minimal scaffolding to match the interface described
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
class FixedValuesGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_idx = 0;

public:
    FixedValuesGenerator(std::initializer_list<T> values)
        : m_values(values) {}

    T const& get() const override {
        return m_values[m_idx];
    }

    bool next() override {
        ++m_idx;
        return m_idx < m_values.size();
    }
};

} // namespace Generators
} // namespace Catch

// ===================== TESTS =====================

using namespace Catch::Generators;

// --- Int tests ---

class FixedValuesGeneratorIntTest_316 : public ::testing::Test {};

TEST_F(FixedValuesGeneratorIntTest_316, GetReturnsFirstValueInitially_316) {
    FixedValuesGenerator<int> gen({10, 20, 30});
    EXPECT_EQ(gen.get(), 10);
}

TEST_F(FixedValuesGeneratorIntTest_316, GetReturnsSameValueWithoutNext_316) {
    FixedValuesGenerator<int> gen({42, 99});
    EXPECT_EQ(gen.get(), 42);
    EXPECT_EQ(gen.get(), 42);
}

TEST_F(FixedValuesGeneratorIntTest_316, NextAdvancesToSecondValue_316) {
    FixedValuesGenerator<int> gen({1, 2, 3});
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2);
}

TEST_F(FixedValuesGeneratorIntTest_316, NextReturnsTrueWhileMoreValues_316) {
    FixedValuesGenerator<int> gen({1, 2, 3});
    EXPECT_TRUE(gen.next());  // now at index 1
    EXPECT_TRUE(gen.next());  // now at index 2
    EXPECT_EQ(gen.get(), 3);
}

TEST_F(FixedValuesGeneratorIntTest_316, NextReturnsFalseWhenExhausted_316) {
    FixedValuesGenerator<int> gen({1, 2, 3});
    EXPECT_TRUE(gen.next());
    EXPECT_TRUE(gen.next());
    EXPECT_FALSE(gen.next());
}

TEST_F(FixedValuesGeneratorIntTest_316, SingleValueGetReturnsIt_316) {
    FixedValuesGenerator<int> gen({77});
    EXPECT_EQ(gen.get(), 77);
}

TEST_F(FixedValuesGeneratorIntTest_316, SingleValueNextReturnsFalse_316) {
    FixedValuesGenerator<int> gen({77});
    EXPECT_FALSE(gen.next());
}

TEST_F(FixedValuesGeneratorIntTest_316, IterateThroughAllValues_316) {
    FixedValuesGenerator<int> gen({5, 10, 15, 20});
    std::vector<int> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    EXPECT_EQ(collected, (std::vector<int>{5, 10, 15, 20}));
}

TEST_F(FixedValuesGeneratorIntTest_316, TwoElementsTraversal_316) {
    FixedValuesGenerator<int> gen({100, 200});
    EXPECT_EQ(gen.get(), 100);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 200);
    EXPECT_FALSE(gen.next());
}

// --- String tests ---

class FixedValuesGeneratorStringTest_316 : public ::testing::Test {};

TEST_F(FixedValuesGeneratorStringTest_316, GetReturnsFirstString_316) {
    FixedValuesGenerator<std::string> gen({"hello", "world"});
    EXPECT_EQ(gen.get(), "hello");
}

TEST_F(FixedValuesGeneratorStringTest_316, NextAdvancesString_316) {
    FixedValuesGenerator<std::string> gen({"hello", "world"});
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "world");
}

TEST_F(FixedValuesGeneratorStringTest_316, StringExhaustion_316) {
    FixedValuesGenerator<std::string> gen({"a", "b", "c"});
    EXPECT_TRUE(gen.next());
    EXPECT_TRUE(gen.next());
    EXPECT_FALSE(gen.next());
}

TEST_F(FixedValuesGeneratorStringTest_316, SingleString_316) {
    FixedValuesGenerator<std::string> gen({"only"});
    EXPECT_EQ(gen.get(), "only");
    EXPECT_FALSE(gen.next());
}

TEST_F(FixedValuesGeneratorStringTest_316, EmptyStringsHandled_316) {
    FixedValuesGenerator<std::string> gen({"", "non-empty", ""});
    EXPECT_EQ(gen.get(), "");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "non-empty");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "");
    EXPECT_FALSE(gen.next());
}

// --- Double tests ---

class FixedValuesGeneratorDoubleTest_316 : public ::testing::Test {};

TEST_F(FixedValuesGeneratorDoubleTest_316, GetReturnsFirstDouble_316) {
    FixedValuesGenerator<double> gen({1.5, 2.5, 3.5});
    EXPECT_DOUBLE_EQ(gen.get(), 1.5);
}

TEST_F(FixedValuesGeneratorDoubleTest_316, IterateAllDoubles_316) {
    FixedValuesGenerator<double> gen({0.1, 0.2, 0.3});
    std::vector<double> collected;
    collected.push_back(gen.get());
    while (gen.next()) {
        collected.push_back(gen.get());
    }
    ASSERT_EQ(collected.size(), 3u);
    EXPECT_DOUBLE_EQ(collected[0], 0.1);
    EXPECT_DOUBLE_EQ(collected[1], 0.2);
    EXPECT_DOUBLE_EQ(collected[2], 0.3);
}

// --- Negative values ---

class FixedValuesGeneratorNegativeTest_316 : public ::testing::Test {};

TEST_F(FixedValuesGeneratorNegativeTest_316, NegativeIntegers_316) {
    FixedValuesGenerator<int> gen({-1, -2, -3});
    EXPECT_EQ(gen.get(), -1);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -2);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -3);
    EXPECT_FALSE(gen.next());
}

// --- Large number of values ---

class FixedValuesGeneratorLargeTest_316 : public ::testing::Test {};

TEST_F(FixedValuesGeneratorLargeTest_316, ManyValues_316) {
    std::initializer_list<int> vals = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    FixedValuesGenerator<int> gen(vals);
    int count = 0;
    EXPECT_EQ(gen.get(), 0);
    while (gen.next()) {
        count++;
    }
    EXPECT_EQ(count, 9);
    EXPECT_EQ(gen.get(), 9);
}

// --- Get returns const reference ---

class FixedValuesGeneratorRefTest_316 : public ::testing::Test {};

TEST_F(FixedValuesGeneratorRefTest_316, GetReturnsConstReference_316) {
    FixedValuesGenerator<std::string> gen({"test"});
    const std::string& ref1 = gen.get();
    const std::string& ref2 = gen.get();
    // Same object should be returned
    EXPECT_EQ(&ref1, &ref2);
}

TEST_F(FixedValuesGeneratorRefTest_316, GetReturnsReferenceToInternalStorage_316) {
    FixedValuesGenerator<int> gen({42, 99});
    const int& ref1 = gen.get();
    EXPECT_EQ(ref1, 42);
    gen.next();
    const int& ref2 = gen.get();
    EXPECT_EQ(ref2, 99);
    // Different elements
    EXPECT_NE(&ref1, &ref2);
}

// --- Duplicate values ---

class FixedValuesGeneratorDuplicateTest_316 : public ::testing::Test {};

TEST_F(FixedValuesGeneratorDuplicateTest_316, DuplicateValuesWork_316) {
    FixedValuesGenerator<int> gen({5, 5, 5});
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 5);
    EXPECT_FALSE(gen.next());
}
