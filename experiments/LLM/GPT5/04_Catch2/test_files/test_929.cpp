// File: tests/map_generator_get_929_test.cpp
#include <gtest/gtest.h>
#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// ----- Simple external collaborator for tests (not testing MapGenerator internals) -----
template <typename U>
class FakeVectorGenerator final : public IGenerator<U> {
public:
    explicit FakeVectorGenerator(std::vector<U> values)
        : values_(std::move(values)), idx_(0) {}

    // Observable behavior: returns current element
    U const& get() const override {
        if (values_.empty() || idx_ >= values_.size()) {
            throw std::out_of_range("FakeVectorGenerator::get out of range");
        }
        return values_[idx_];
    }

    // Observable behavior: advances, returns true if now valid, false if exhausted
    bool next() override {
        if (values_.empty() || idx_ >= values_.size()) {
            return false;
        }
        if (idx_ + 1 < values_.size()) {
            ++idx_;
            return true;
        }
        // Move past last to indicate exhaustion
        ++idx_;
        return false;
    }

private:
    std::vector<U> values_;
    size_t idx_;
};

// ----- Test fixture -----
class MapGeneratorTest_929 : public ::testing::Test {};

// Normal operation: get() returns mapped value from the collaborator’s current value.
TEST_F(MapGeneratorTest_929, GetReturnsMappedValue_Stringify_929) {
    auto base = GeneratorWrapper<int>(std::unique_ptr<IGenerator<int>>(
        new FakeVectorGenerator<int>({1})));

    auto stringify = [](int x) { return std::to_string(x); };
    MapGenerator<std::string, int, decltype(stringify)> gen(stringify, CATCH_MOVE(base));

    // Observable: get() yields the mapped value for current element (1 -> "1")
    EXPECT_EQ(gen.get(), std::string("1"));
}

// Boundary: get() returns a const reference to the same cached object between calls (no next()).
TEST_F(MapGeneratorTest_929, GetReturnsStableConstRef_929) {
    auto base = GeneratorWrapper<int>(std::unique_ptr<IGenerator<int>>(
        new FakeVectorGenerator<int>({42})));

    auto stringify = [](int x) { return std::to_string(x); };
    MapGenerator<std::string, int, decltype(stringify)> gen(stringify, CATCH_MOVE(base));

    // Taking addresses checks we get the same object by const reference
    auto const* p1 = &gen.get();
    auto const* p2 = &gen.get();
    EXPECT_EQ(p1, p2);
    EXPECT_EQ(*p1, "42");
}

// Normal operation: next() advances; subsequent get() reflects the mapped value for the new element.
TEST_F(MapGeneratorTest_929, NextAdvancesAndUpdatesMappedValue_929) {
    auto base = GeneratorWrapper<int>(std::unique_ptr<IGenerator<int>>(
        new FakeVectorGenerator<int>({10, 20})));

    auto times2 = [](int x) { return x * 2; };
    MapGenerator<int, int, decltype(times2)> gen(times2, CATCH_MOVE(base));

    // Initial get() reflects mapping of first element: 10 -> 20
    EXPECT_EQ(gen.get(), 20);

    // After next(), mapping should reflect second element: 20 -> 40
    ASSERT_TRUE(gen.next());
    EXPECT_EQ(gen.get(), 40);
}

// Boundary: next() at end returns false; get() remains at last observable mapped value.
TEST_F(MapGeneratorTest_929, NextReturnsFalseAtEnd_GetRemainsLast_929) {
    auto base = GeneratorWrapper<int>(std::unique_ptr<IGenerator<int>>(
        new FakeVectorGenerator<int>({7})) );

    auto id = [](int x) { return x; };
    MapGenerator<int, int, decltype(id)> gen(id, CATCH_MOVE(base));

    EXPECT_EQ(gen.get(), 7);

    // First next() should exhaust (single element) and return false
    EXPECT_FALSE(gen.next());

    // Observable: get() still returns last mapped value (no new element)
    EXPECT_EQ(gen.get(), 7);
}

// Exceptional case (observable): mapping function throws during next(); exception propagates.
TEST_F(MapGeneratorTest_929, NextPropagatesMappingException_929) {
    auto base = GeneratorWrapper<int>(std::unique_ptr<IGenerator<int>>(
        new FakeVectorGenerator<int>({1, 2})) );

    // Throw when mapping value 2; the initial value 1 is fine.
    struct Boom : std::runtime_error {
        Boom() : std::runtime_error("boom") {}
    };

    auto maybeThrow = [](int x) -> int {
        if (x == 2) throw Boom{};
        return x;
    };

    MapGenerator<int, int, decltype(maybeThrow)> gen(maybeThrow, CATCH_MOVE(base));
    EXPECT_EQ(gen.get(), 1);

    // Advancing to value 2 triggers the mapping exception; it should be observable.
    EXPECT_THROW((void)gen.next(), Boom);
}
