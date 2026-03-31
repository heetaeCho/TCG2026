#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <deque>
#include <string>

// Include the header under test
namespace Catch {
namespace Matchers {

class NoneTrueMatcher {
public:
    template <typename RangeLike>
    bool match(RangeLike&& rng) const {
        for (auto&& elem : rng) {
            if (elem) {
                return false;
            }
        }
        return true;
    }
};

} // namespace Matchers
} // namespace Catch

using Catch::Matchers::NoneTrueMatcher;

// Test fixture
class NoneTrueMatcherTest_183 : public ::testing::Test {
protected:
    NoneTrueMatcher matcher;
};

// --- Normal Operation Tests ---

TEST_F(NoneTrueMatcherTest_183, EmptyVectorReturnsTrue_183) {
    std::vector<bool> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, AllFalseVectorReturnsTrue_183) {
    std::vector<bool> v = {false, false, false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, AllTrueVectorReturnsFalse_183) {
    std::vector<bool> v = {true, true, true};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, MixedBoolVectorReturnsFalse_183) {
    std::vector<bool> v = {false, true, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, SingleFalseReturnsTrue_183) {
    std::vector<bool> v = {false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, SingleTrueReturnsFalse_183) {
    std::vector<bool> v = {true};
    EXPECT_FALSE(matcher.match(v));
}

// --- Integer Range Tests ---

TEST_F(NoneTrueMatcherTest_183, AllZeroIntVectorReturnsTrue_183) {
    std::vector<int> v = {0, 0, 0, 0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, IntVectorWithNonZeroReturnsFalse_183) {
    std::vector<int> v = {0, 0, 1, 0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, IntVectorAllNonZeroReturnsFalse_183) {
    std::vector<int> v = {1, 2, 3, 4};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, EmptyIntVectorReturnsTrue_183) {
    std::vector<int> v;
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, NegativeIntsTreatedAsTruthy_183) {
    std::vector<int> v = {0, -1, 0};
    EXPECT_FALSE(matcher.match(v));
}

// --- Different Container Types ---

TEST_F(NoneTrueMatcherTest_183, ArrayAllZerosReturnsTrue_183) {
    std::array<int, 4> arr = {0, 0, 0, 0};
    EXPECT_TRUE(matcher.match(arr));
}

TEST_F(NoneTrueMatcherTest_183, ArrayWithNonZeroReturnsFalse_183) {
    std::array<int, 3> arr = {0, 5, 0};
    EXPECT_FALSE(matcher.match(arr));
}

TEST_F(NoneTrueMatcherTest_183, ListAllFalseReturnsTrue_183) {
    std::list<bool> lst = {false, false, false};
    EXPECT_TRUE(matcher.match(lst));
}

TEST_F(NoneTrueMatcherTest_183, ListWithTrueReturnsFalse_183) {
    std::list<bool> lst = {false, true, false};
    EXPECT_FALSE(matcher.match(lst));
}

TEST_F(NoneTrueMatcherTest_183, DequeAllZerosReturnsTrue_183) {
    std::deque<int> dq = {0, 0, 0};
    EXPECT_TRUE(matcher.match(dq));
}

TEST_F(NoneTrueMatcherTest_183, DequeWithNonZeroReturnsFalse_183) {
    std::deque<int> dq = {0, 0, 42};
    EXPECT_FALSE(matcher.match(dq));
}

// --- Boundary Conditions ---

TEST_F(NoneTrueMatcherTest_183, EmptyArrayReturnsTrue_183) {
    std::array<int, 0> arr = {};
    EXPECT_TRUE(matcher.match(arr));
}

TEST_F(NoneTrueMatcherTest_183, FirstElementTrueReturnsFalseEarly_183) {
    std::vector<bool> v = {true, false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, LastElementTrueReturnsFalse_183) {
    std::vector<bool> v = {false, false, false, true};
    EXPECT_FALSE(matcher.match(v));
}

// --- Pointer-like types ---

TEST_F(NoneTrueMatcherTest_183, NullptrVectorReturnsTrue_183) {
    std::vector<int*> v = {nullptr, nullptr, nullptr};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, NonNullPointerReturnsFalse_183) {
    int x = 5;
    std::vector<int*> v = {nullptr, &x, nullptr};
    EXPECT_FALSE(matcher.match(v));
}

// --- Double/Float types ---

TEST_F(NoneTrueMatcherTest_183, AllZeroDoublesReturnsTrue_183) {
    std::vector<double> v = {0.0, 0.0, 0.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, NonZeroDoubleReturnsFalse_183) {
    std::vector<double> v = {0.0, 0.1, 0.0};
    EXPECT_FALSE(matcher.match(v));
}

// --- Large Range ---

TEST_F(NoneTrueMatcherTest_183, LargeAllFalseVectorReturnsTrue_183) {
    std::vector<bool> v(10000, false);
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, LargeVectorWithLastTrueReturnsFalse_183) {
    std::vector<bool> v(10000, false);
    v.back() = true;
    EXPECT_FALSE(matcher.match(v));
}

// --- Const reference ---

TEST_F(NoneTrueMatcherTest_183, ConstVectorReturnsTrue_183) {
    const std::vector<int> v = {0, 0, 0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(NoneTrueMatcherTest_183, ConstVectorReturnsFalse_183) {
    const std::vector<int> v = {0, 1, 0};
    EXPECT_FALSE(matcher.match(v));
}

// --- Initializer list via temporary ---

TEST_F(NoneTrueMatcherTest_183, TemporaryVectorAllZeros_183) {
    EXPECT_TRUE(matcher.match(std::vector<int>{0, 0, 0}));
}

TEST_F(NoneTrueMatcherTest_183, TemporaryVectorWithNonZero_183) {
    EXPECT_FALSE(matcher.match(std::vector<int>{0, 0, 7}));
}
