// File: tests/take_generator_get_tests_920.cpp

#include <gtest/gtest.h>
#include <memory>
#include <vector>

// Use the real amalgamated header in your tree.
// If your includes differ, adjust the include path accordingly.
#include "Catch2/extras/catch_amalgamated.hpp"

using namespace Catch::Generators;

// A simple external collaborator used only for testing: a finite generator
// that yields elements from a provided vector. This is *not* simulating any
// internal logic of TakeGenerator; it’s just a source to wrap via GeneratorWrapper.
template <typename T>
class VectorGenerator : public IGenerator<T> {
public:
    explicit VectorGenerator(std::vector<T> values)
        : m_values(std::move(values)), m_idx(0) {
        // Ensure there is always a valid current element when get() is called
        // by starting "positioned" at the first element if available.
    }

    T const& get() const override {
        // Precondition for users of IGenerator<T>: only call get() when there is a current element.
        // Our tests respect that by first ensuring construction with non-empty input or after
        // verifying next() succeeded.
        return m_values[m_idx];
    }

    bool next() override {
        if (m_values.empty()) return false;
        if (m_idx + 1 < m_values.size()) {
            ++m_idx;
            return true;
        }
        return false;
    }

private:
    std::vector<T> m_values;
    std::size_t m_idx;
};

// A thin helper to build a GeneratorWrapper<T> from a unique_ptr<IGenerator<T>>.
template <typename T>
static GeneratorWrapper<T> Wrap(std::unique_ptr<IGenerator<T>> g) {
    return GeneratorWrapper<T>(std::move(g));
}

class TakeGeneratorTest_920 : public ::testing::Test {};

// [Normal] get() forwards the underlying current value reference.
TEST_F(TakeGeneratorTest_920, GetForwardsReference_920) {
    auto base = std::make_unique<VectorGenerator<int>>(std::vector<int>{10, 20, 30});
    auto* raw = base.get(); // keep raw pointer to compare addresses from get()

    auto wrapper = Wrap<int>(std::move(base));
    TakeGenerator<int> take(/*target=*/3, std::move(wrapper));

    // get() should return the same reference as the underlying generator's get()
    int const& from_take = take.get();
    int const& from_underlying = raw->get();

    EXPECT_EQ(from_take, 10);
    EXPECT_EQ(from_underlying, 10);
    EXPECT_EQ(&from_take, &from_underlying) << "get() should forward the same reference";
}

// [Normal] After a successful next(), get() reflects the next underlying value.
TEST_F(TakeGeneratorTest_920, GetReflectsUnderlyingAfterNext_920) {
    auto wrapper = Wrap<int>(std::make_unique<VectorGenerator<int>>(std::vector<int>{1, 2, 3}));
    TakeGenerator<int> take(/*target=*/3, std::move(wrapper));

    EXPECT_EQ(take.get(), 1);        // initial current
    EXPECT_TRUE(take.next());        // advance once
    EXPECT_EQ(take.get(), 2);        // should reflect next element
}

// [Boundary] target = 1 yields one observable value; further next() should fail.
TEST_F(TakeGeneratorTest_920, StopsAfterTargetOne_920) {
    auto wrapper = Wrap<int>(std::make_unique<VectorGenerator<int>>(std::vector<int>{5, 6, 7}));
    TakeGenerator<int> take(/*target=*/1, std::move(wrapper));

    // We can observe the first value
    EXPECT_EQ(take.get(), 5);

    // With target == 1, there should be no further advances permitted by the take view.
    EXPECT_FALSE(take.next());
    // After exhaustion, the behavior of get() is not asserted (not specified/observable safely).
}

// [Boundary] target = 0: no advances should be possible.
TEST_F(TakeGeneratorTest_920, ZeroTargetNextReturnsFalse_920) {
    auto wrapper = Wrap<int>(std::make_unique<VectorGenerator<int>>(std::vector<int>{42}));
    TakeGenerator<int> take(/*target=*/0, std::move(wrapper));

    // With zero target, we should not be able to advance at all.
    EXPECT_FALSE(take.next());
    // We deliberately do not call get() here since there is no current element to observe.
}

// [Exceptional/Edge via collaborator] Underlying shorter than target:
// take() should stop when the underlying runs out (observable via next()).
TEST_F(TakeGeneratorTest_920, UnderlyingShorterThanTarget_920) {
    auto wrapper = Wrap<int>(std::make_unique<VectorGenerator<int>>(std::vector<int>{9, 10, 11}));
    TakeGenerator<int> take(/*target=*/5, std::move(wrapper));

    // We can observe the first value
    EXPECT_EQ(take.get(), 9);

    // 1st advance -> OK (to 10)
    EXPECT_TRUE(take.next());
    EXPECT_EQ(take.get(), 10);

    // 2nd advance -> OK (to 11)
    EXPECT_TRUE(take.next());
    EXPECT_EQ(take.get(), 11);

    // 3rd advance -> underlying exhausted -> should fail
    EXPECT_FALSE(take.next());
}
