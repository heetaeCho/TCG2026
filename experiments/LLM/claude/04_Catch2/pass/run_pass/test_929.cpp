#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <functional>

// Minimal stubs to support testing MapGenerator from the Catch2 amalgamated header.
// We replicate just enough of the Catch2 Generators infrastructure to instantiate MapGenerator.

namespace Catch {

// Minimal move/forward macros if not defined
#ifndef CATCH_MOVE
#define CATCH_MOVE(...) static_cast<std::remove_reference_t<decltype(__VA_ARGS__)>&&>(__VA_ARGS__)
#endif
#ifndef CATCH_FORWARD
#define CATCH_FORWARD(...) static_cast<decltype(__VA_ARGS__)&&>(__VA_ARGS__)
#endif

namespace Generators {

// IGenerator interface
template <typename T>
class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual T const& get() const = 0;
    virtual bool next() = 0;
};

// GeneratorWrapper wrapping a unique_ptr to IGenerator
template <typename T>
class GeneratorWrapper {
    std::unique_ptr<IGenerator<T>> m_generator;
public:
    GeneratorWrapper(std::unique_ptr<IGenerator<T>> generator)
        : m_generator(std::move(generator)) {}

    T const& get() const { return m_generator->get(); }
    bool next() { return m_generator->next(); }
};

// A simple fixed-values generator for testing purposes
template <typename T>
class FixedValuesGenerator : public IGenerator<T> {
    std::vector<T> m_values;
    size_t m_index = 0;
public:
    FixedValuesGenerator(std::vector<T> values)
        : m_values(std::move(values)) {}

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

// MapGenerator as described in the interface
template <typename T, typename U, typename Func>
class MapGenerator : public IGenerator<T> {
    GeneratorWrapper<U> m_generator;
    Func m_function;
    T m_cache;

public:
    template <typename F2 = Func>
    MapGenerator(F2&& function, GeneratorWrapper<U>&& generator)
        : m_generator(CATCH_MOVE(generator)),
          m_function(CATCH_FORWARD(function)),
          m_cache(m_function(m_generator.get())) {}

    T const& get() const override {
        return m_cache;
    }

    bool next() override {
        if (m_generator.next()) {
            m_cache = m_function(m_generator.get());
            return true;
        }
        return false;
    }
};

} // namespace Generators
} // namespace Catch

// ===== TESTS =====

using namespace Catch::Generators;

// Helper to create a GeneratorWrapper from a vector of values
template <typename T>
GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
    return GeneratorWrapper<T>(
        std::make_unique<FixedValuesGenerator<T>>(std::move(values))
    );
}

class MapGeneratorTest_929 : public ::testing::Test {};

// Test that get() returns the mapped value of the first element after construction
TEST_F(MapGeneratorTest_929, GetReturnsFirstMappedValue_929) {
    auto gen = makeFixedGenerator<int>({1, 2, 3});
    auto mapper = [](int x) { return x * 10; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 10);
}

// Test that next() advances and get() returns the next mapped value
TEST_F(MapGeneratorTest_929, NextAdvancesAndGetReturnsMappedValue_929) {
    auto gen = makeFixedGenerator<int>({1, 2, 3});
    auto mapper = [](int x) { return x * 10; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 10);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 20);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 30);
}

// Test that next() returns false when there are no more elements
TEST_F(MapGeneratorTest_929, NextReturnsFalseWhenExhausted_929) {
    auto gen = makeFixedGenerator<int>({1});
    auto mapper = [](int x) { return x + 100; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 101);
    EXPECT_FALSE(mapGen.next());
}

// Test with a single-element generator
TEST_F(MapGeneratorTest_929, SingleElementGenerator_929) {
    auto gen = makeFixedGenerator<int>({42});
    auto mapper = [](int x) { return x * 2; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 84);
    EXPECT_FALSE(mapGen.next());
    // After exhaustion, get() should still return the last cached value
    EXPECT_EQ(mapGen.get(), 84);
}

// Test that get() is consistent (calling it multiple times returns the same value)
TEST_F(MapGeneratorTest_929, GetIsIdempotent_929) {
    auto gen = makeFixedGenerator<int>({5, 10});
    auto mapper = [](int x) { return x + 1; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 6);
    EXPECT_EQ(mapGen.get(), 6);
    EXPECT_EQ(mapGen.get(), 6);
}

// Test type transformation: int -> string
TEST_F(MapGeneratorTest_929, TypeTransformationIntToString_929) {
    auto gen = makeFixedGenerator<int>({1, 2, 3});
    auto mapper = [](int x) -> std::string { return std::to_string(x); };
    MapGenerator<std::string, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), "1");
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), "2");
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), "3");
    EXPECT_FALSE(mapGen.next());
}

// Test type transformation: string -> size_t (string length)
TEST_F(MapGeneratorTest_929, TypeTransformationStringToSize_929) {
    auto gen = makeFixedGenerator<std::string>({"hello", "hi", "!"});
    auto mapper = [](const std::string& s) -> size_t { return s.size(); };
    MapGenerator<size_t, std::string, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 5u);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 2u);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 1u);
    EXPECT_FALSE(mapGen.next());
}

// Test that the mapping function is called the correct number of times
TEST_F(MapGeneratorTest_929, MappingFunctionCalledCorrectNumberOfTimes_929) {
    int callCount = 0;
    auto gen = makeFixedGenerator<int>({10, 20, 30});
    auto mapper = [&callCount](int x) -> int {
        ++callCount;
        return x;
    };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    // Constructor calls mapper once for the initial value
    EXPECT_EQ(callCount, 1);

    mapGen.next();
    EXPECT_EQ(callCount, 2);

    mapGen.next();
    EXPECT_EQ(callCount, 3);

    // get() should not increment the call count
    mapGen.get();
    EXPECT_EQ(callCount, 3);
}

// Test that calling next() after exhaustion still returns false
TEST_F(MapGeneratorTest_929, NextAfterExhaustionReturnsFalse_929) {
    auto gen = makeFixedGenerator<int>({1, 2});
    auto mapper = [](int x) { return x; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_TRUE(mapGen.next());
    EXPECT_FALSE(mapGen.next());
    // Calling next again after exhaustion
    EXPECT_FALSE(mapGen.next());
}

// Test with identity function
TEST_F(MapGeneratorTest_929, IdentityFunction_929) {
    auto gen = makeFixedGenerator<int>({7, 14, 21});
    auto mapper = [](int x) { return x; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 7);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 14);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 21);
    EXPECT_FALSE(mapGen.next());
}

// Test with negative numbers
TEST_F(MapGeneratorTest_929, NegativeNumbers_929) {
    auto gen = makeFixedGenerator<int>({-1, -2, -3});
    auto mapper = [](int x) { return -x; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), 1);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 2);
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), 3);
    EXPECT_FALSE(mapGen.next());
}

// Test with a complex mapping (struct transformation)
TEST_F(MapGeneratorTest_929, ComplexMapping_929) {
    struct Point {
        int x, y;
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };

    auto gen = makeFixedGenerator<int>({1, 2, 3});
    auto mapper = [](int val) -> Point { return {val, val * val}; };
    MapGenerator<Point, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    EXPECT_EQ(mapGen.get(), (Point{1, 1}));
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), (Point{2, 4}));
    EXPECT_TRUE(mapGen.next());
    EXPECT_EQ(mapGen.get(), (Point{3, 9}));
    EXPECT_FALSE(mapGen.next());
}

// Test that get() returns a const reference
TEST_F(MapGeneratorTest_929, GetReturnsConstReference_929) {
    auto gen = makeFixedGenerator<std::string>({"test"});
    auto mapper = [](const std::string& s) -> std::string { return s + "_mapped"; };
    MapGenerator<std::string, std::string, decltype(mapper)> mapGen(mapper, std::move(gen));

    const std::string& ref1 = mapGen.get();
    const std::string& ref2 = mapGen.get();
    // Both references should point to the same cached object
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1, "test_mapped");
}

// Test traversal of many elements
TEST_F(MapGeneratorTest_929, ManyElements_929) {
    std::vector<int> values;
    for (int i = 0; i < 100; ++i) {
        values.push_back(i);
    }
    auto gen = makeFixedGenerator<int>(values);
    auto mapper = [](int x) { return x * x; };
    MapGenerator<int, int, decltype(mapper)> mapGen(mapper, std::move(gen));

    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(mapGen.get(), i * i);
        if (i < 99) {
            EXPECT_TRUE(mapGen.next());
        } else {
            EXPECT_FALSE(mapGen.next());
        }
    }
}
