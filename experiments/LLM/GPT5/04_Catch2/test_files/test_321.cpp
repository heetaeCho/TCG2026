// File: tests/generators_next_321_tests.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/generators/catch_generators.hpp"

using ::testing::InSequence;
using ::testing::Return;

namespace Catch {
namespace Generators {

// Minimal interface that Catch2's generators expose.
// We only use what next() under test interacts with.
template <typename T>
struct IGenerator {
    virtual ~IGenerator() = default;
    virtual T const& get() const = 0;
    virtual bool next() = 0;
};

// A Google Mock for IGenerator<T>. This is an external collaborator
// used by Generators<T>, so mocking it is allowed by the constraints.
template <typename T>
struct MockIGenerator : IGenerator<T> {
    MOCK_METHOD(T const&, get, (), (const, override));
    MOCK_METHOD(bool, next, (), (override));
};

// In Catch2, GeneratorWrapper<T> typically wraps a unique_ptr<IGenerator<T>>.
// We rely only on its observable construction/ownership semantics.
template <typename T>
class GeneratorWrapper {
public:
    explicit GeneratorWrapper(std::unique_ptr<IGenerator<T>> gen)
        : gen_(std::move(gen)) {}

    // Forward the calls used by Generators<T>::next()
    bool next()              { return gen_->next(); }
    T const& get() const     { return gen_->get();  }

private:
    std::unique_ptr<IGenerator<T>> gen_;
};

// The class under test (partial from the codebase). We do not
// re-implement its internals in tests; we only call its public API.
// Here we declare the public surface we need for construction & calls.
template <typename T>
class Generators {
public:
    template <typename... Gs>
    explicit Generators(Gs&&... gs) {
        (add_generator(std::forward<Gs>(gs)), ...);
    }

    // Public API we are testing
    bool next();       // implemented in the production codebase
    T const& get() const;

private:
    void add_generator(GeneratorWrapper<T>&& gw) {
        m_generators.emplace_back(std::move(gw));
    }

    // Members are declared by the production header; redeclared here
    // only so the test compiles. Tests never access them directly.
    std::vector<GeneratorWrapper<T>> m_generators;
    size_t m_current = 0;
};

} // namespace Generators
} // namespace Catch

using Catch::Generators::MockIGenerator;
using Catch::Generators::GeneratorWrapper;
using Catch::Generators::Generators;

// ---------- Tests ----------

TEST(GeneratorsNextTest_321, EmptySequenceReturnsFalseImmediately_321) {
    // Construct with no underlying generators.
    Generators<int> gens;  // relies on variadic ctor allowing zero args

    // When there are no generators, next() should be false right away.
    EXPECT_FALSE(gens.next());
}

TEST(GeneratorsNextTest_321, SingleGeneratorPropagatesStatusAndEnds_321) {
    auto mock = std::make_unique<MockIGenerator<int>>();
    const int dummy = 42;
    ON_CALL(*mock, get()).WillByDefault(Return(dummy));

    {
        InSequence s;
        EXPECT_CALL(*mock, next()).WillOnce(Return(true));   // still on the same generator
        EXPECT_CALL(*mock, next()).WillOnce(Return(false));  // signals exhaustion -> advance past last -> done
    }

    Generators<int> gens{ GeneratorWrapper<int>(std::move(mock)) };

    // 1st call: underlying next() == true => container still has current -> returns true
    EXPECT_TRUE(gens.next());
    // 2nd call: underlying next() == false => advance to index 1 == size() -> returns false
    EXPECT_FALSE(gens.next());
}

TEST(GeneratorsNextTest_321, TwoImmediateEmptyGeneratorsYieldsTrueThenFalse_321) {
    auto m1 = std::make_unique<MockIGenerator<int>>();
    auto m2 = std::make_unique<MockIGenerator<int>>();
    const int d1 = 1, d2 = 2;
    ON_CALL(*m1, get()).WillByDefault(Return(d1));
    ON_CALL(*m2, get()).WillByDefault(Return(d2));

    {
        InSequence s;
        EXPECT_CALL(*m1, next()).WillOnce(Return(false)); // first is immediately done -> advance to second, but still within bounds
        EXPECT_CALL(*m2, next()).WillOnce(Return(false)); // second done -> advance past end
    }

    Generators<int> gens{
        GeneratorWrapper<int>(std::move(m1)),
        GeneratorWrapper<int>(std::move(m2))
    };

    // 1st call: first returns false, container advances to next, returns true (since there is another generator)
    EXPECT_TRUE(gens.next());
    // 2nd call: second returns false, container advances past end, returns false
    EXPECT_FALSE(gens.next());
}

TEST(GeneratorsNextTest_321, AdvancesAcrossGeneratorsAndOnlyEndsAfterLastExhausted_321) {
    auto g1 = std::make_unique<MockIGenerator<int>>();
    auto g2 = std::make_unique<MockIGenerator<int>>();
    const int a = 10, b = 20;
    ON_CALL(*g1, get()).WillByDefault(Return(a));
    ON_CALL(*g2, get()).WillByDefault(Return(b));

    {
        InSequence s;
        // g1 has two successful advances, then exhausts
        EXPECT_CALL(*g1, next()).WillOnce(Return(true));
        EXPECT_CALL(*g1, next()).WillOnce(Return(true));
        EXPECT_CALL(*g1, next()).WillOnce(Return(false)); // triggers advance to g2 but still returns true overall
        // g2 has one success, then exhausts
        EXPECT_CALL(*g2, next()).WillOnce(Return(true));
        EXPECT_CALL(*g2, next()).WillOnce(Return(false)); // advance past end -> overall false
    }

    Generators<int> gens{
        GeneratorWrapper<int>(std::move(g1)),
        GeneratorWrapper<int>(std::move(g2))
    };

    EXPECT_TRUE(gens.next());  // g1 true
    EXPECT_TRUE(gens.next());  // g1 true
    EXPECT_TRUE(gens.next());  // g1 false -> move to g2 -> still within range
    EXPECT_TRUE(gens.next());  // g2 true
    EXPECT_FALSE(gens.next()); // g2 false -> moved past last -> false
}
