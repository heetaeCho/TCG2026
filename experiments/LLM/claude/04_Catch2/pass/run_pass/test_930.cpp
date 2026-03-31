#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <functional>

// Minimal implementation of the Catch2 Generators interfaces needed for testing
namespace Catch {

#define CATCH_MOVE(x) std::move(x)
#define CATCH_FORWARD(x) std::forward<decltype(x)>(x)

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

template <typename T, typename U, typename Func>
class MapGenerator : public IGenerator<T> {
private:
    GeneratorWrapper<U> m_generator;
    Func m_function;
    T m_cache;

public:
    template <typename F2 = Func>
    MapGenerator(F2&& function, GeneratorWrapper<U>&& generator)
        : m_generator(std::move(generator)),
          m_function(std::forward<F2>(function)),
          m_cache(m_function(m_generator.get())) {}

    T const& get() const override {
        return m_cache;
    }

    bool next() override {
        const auto success = m_generator.next();
        if (success) {
            m_cache = m_function(m_generator.get());
        }
        return success;
    }
};

// A simple fixed-values generator for testing
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

} // namespace Generators
} // namespace Catch

// Test fixture
class MapGeneratorTest_930 : public ::testing::Test {
protected:
    template <typename T>
    Catch::Generators::GeneratorWrapper<T> makeFixedGenerator(std::vector<T> values) {
        return Catch::Generators::GeneratorWrapper<T>(
            std::make_unique<Catch::Generators::FixedValuesGenerator<T>>(std::move(values))
        );
    }
};

TEST_F(MapGeneratorTest_930, ConstructorAppliesFunctionToFirstElement_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x * 2; },
        makeFixedGenerator<int>({5, 10, 15})
    );

    EXPECT_EQ(gen.get(), 10);
}

TEST_F(MapGeneratorTest_930, NextReturnsTrueWhenMoreElements_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x + 1; },
        makeFixedGenerator<int>({1, 2, 3})
    );

    EXPECT_TRUE(gen.next());
}

TEST_F(MapGeneratorTest_930, NextUpdatesCacheWithMappedValue_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x * 3; },
        makeFixedGenerator<int>({1, 2, 3})
    );

    EXPECT_EQ(gen.get(), 3);  // 1 * 3
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 6);  // 2 * 3
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 9);  // 3 * 3
}

TEST_F(MapGeneratorTest_930, NextReturnsFalseWhenExhausted_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x; },
        makeFixedGenerator<int>({42})
    );

    EXPECT_EQ(gen.get(), 42);
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_930, GetReturnsSameValueWithoutCallingNext_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x + 100; },
        makeFixedGenerator<int>({1, 2})
    );

    EXPECT_EQ(gen.get(), 101);
    EXPECT_EQ(gen.get(), 101);
    EXPECT_EQ(gen.get(), 101);
}

TEST_F(MapGeneratorTest_930, MapChangesType_930) {
    auto gen = Catch::Generators::MapGenerator<std::string, int, std::function<std::string(int)>>(
        [](int x) { return std::to_string(x); },
        makeFixedGenerator<int>({1, 2, 3})
    );

    EXPECT_EQ(gen.get(), "1");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "2");
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), "3");
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_930, GetAfterExhaustedReturnsLastMappedValue_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x * 10; },
        makeFixedGenerator<int>({5, 7})
    );

    EXPECT_EQ(gen.get(), 50);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 70);
    EXPECT_FALSE(gen.next());
    // After exhaustion, get() should still return the last cached value
    EXPECT_EQ(gen.get(), 70);
}

TEST_F(MapGeneratorTest_930, MapWithIdentityFunction_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x; },
        makeFixedGenerator<int>({10, 20, 30})
    );

    EXPECT_EQ(gen.get(), 10);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 20);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 30);
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_930, MapWithSingleElement_930) {
    auto gen = Catch::Generators::MapGenerator<double, int, std::function<double(int)>>(
        [](int x) { return x / 2.0; },
        makeFixedGenerator<int>({7})
    );

    EXPECT_DOUBLE_EQ(gen.get(), 3.5);
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_930, FunctionCalledCorrectNumberOfTimes_930) {
    int call_count = 0;
    auto func = [&call_count](int x) -> int {
        ++call_count;
        return x * x;
    };

    auto gen = Catch::Generators::MapGenerator<int, int, decltype(func)>(
        func,
        makeFixedGenerator<int>({1, 2, 3, 4})
    );

    // Constructor calls function once for the first element
    EXPECT_EQ(call_count, 1);
    EXPECT_EQ(gen.get(), 1);

    gen.next();
    EXPECT_EQ(call_count, 2);
    EXPECT_EQ(gen.get(), 4);

    gen.next();
    EXPECT_EQ(call_count, 3);
    EXPECT_EQ(gen.get(), 9);

    gen.next();
    EXPECT_EQ(call_count, 4);
    EXPECT_EQ(gen.get(), 16);

    gen.next(); // returns false, function should NOT be called
    EXPECT_EQ(call_count, 4);
}

TEST_F(MapGeneratorTest_930, MapWithNegativeValues_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return -x; },
        makeFixedGenerator<int>({-3, 0, 3})
    );

    EXPECT_EQ(gen.get(), 3);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), -3);
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_930, MapStringToLength_930) {
    auto gen = Catch::Generators::MapGenerator<size_t, std::string, std::function<size_t(std::string const&)>>(
        [](std::string const& s) -> size_t { return s.size(); },
        makeFixedGenerator<std::string>({"hello", "hi", ""})
    );

    EXPECT_EQ(gen.get(), 5u);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 2u);
    EXPECT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 0u);
    EXPECT_FALSE(gen.next());
}

TEST_F(MapGeneratorTest_930, MultipleNextAfterExhaustion_930) {
    auto gen = Catch::Generators::MapGenerator<int, int, std::function<int(int)>>(
        [](int x) { return x; },
        makeFixedGenerator<int>({1})
    );

    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
    EXPECT_FALSE(gen.next());
    // Cache should remain unchanged
    EXPECT_EQ(gen.get(), 1);
}

TEST_F(MapGeneratorTest_930, MapWithStatefulFunction_930) {
    int offset = 0;
    auto func = [&offset](int x) -> int {
        return x + offset++;
    };

    auto gen = Catch::Generators::MapGenerator<int, int, decltype(func)>(
        func,
        makeFixedGenerator<int>({10, 20, 30})
    );

    // Constructor: 10 + 0 = 10, offset becomes 1
    EXPECT_EQ(gen.get(), 10);

    gen.next();
    // 20 + 1 = 21, offset becomes 2
    EXPECT_EQ(gen.get(), 21);

    gen.next();
    // 30 + 2 = 32, offset becomes 3
    EXPECT_EQ(gen.get(), 32);
}

TEST_F(MapGeneratorTest_930, GetReturnsConstReference_930) {
    auto gen = Catch::Generators::MapGenerator<std::string, int, std::function<std::string(int)>>(
        [](int x) { return std::string(x, 'a'); },
        makeFixedGenerator<int>({3})
    );

    const std::string& ref1 = gen.get();
    const std::string& ref2 = gen.get();
    // Both references should point to the same cached object
    EXPECT_EQ(&ref1, &ref2);
    EXPECT_EQ(ref1, "aaa");
}
