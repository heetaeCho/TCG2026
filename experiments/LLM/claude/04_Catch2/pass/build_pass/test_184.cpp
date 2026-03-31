#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <string>
#include <deque>
#include <set>

// Include the header under test
namespace Catch {
namespace Matchers {

class AnyTrueMatcher {
public:
    template <typename RangeLike>
    bool match(RangeLike&& rng) const {
        for (auto&& elem : rng) {
            if (elem) {
                return true;
            }
        }
        return false;
    }
};

}
}

using Catch::Matchers::AnyTrueMatcher;

// Test fixture
class AnyTrueMatcherTest_184 : public ::testing::Test {
protected:
    AnyTrueMatcher matcher;
};

// --- Normal operation tests ---

TEST_F(AnyTrueMatcherTest_184, AllTrueVectorBool_184) {
    std::vector<bool> v = {true, true, true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, SomeTrueVectorBool_184) {
    std::vector<bool> v = {false, true, false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, AllFalseVectorBool_184) {
    std::vector<bool> v = {false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, FirstElementTrue_184) {
    std::vector<bool> v = {true, false, false};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, LastElementTrue_184) {
    std::vector<bool> v = {false, false, true};
    EXPECT_TRUE(matcher.match(v));
}

// --- Boundary condition tests ---

TEST_F(AnyTrueMatcherTest_184, EmptyVectorBool_184) {
    std::vector<bool> v = {};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, SingleElementTrue_184) {
    std::vector<bool> v = {true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, SingleElementFalse_184) {
    std::vector<bool> v = {false};
    EXPECT_FALSE(matcher.match(v));
}

// --- Integer-based range tests (truthy/falsy semantics) ---

TEST_F(AnyTrueMatcherTest_184, VectorIntAllZeros_184) {
    std::vector<int> v = {0, 0, 0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, VectorIntSomeNonZero_184) {
    std::vector<int> v = {0, 5, 0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, VectorIntAllNonZero_184) {
    std::vector<int> v = {1, 2, 3};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, VectorIntNegativeValues_184) {
    std::vector<int> v = {0, -1, 0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, EmptyVectorInt_184) {
    std::vector<int> v = {};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, SingleZeroInt_184) {
    std::vector<int> v = {0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, SingleNonZeroInt_184) {
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// --- Different container types ---

TEST_F(AnyTrueMatcherTest_184, ArrayAllFalse_184) {
    std::array<bool, 3> a = {false, false, false};
    EXPECT_FALSE(matcher.match(a));
}

TEST_F(AnyTrueMatcherTest_184, ArraySomeTrue_184) {
    std::array<bool, 3> a = {false, true, false};
    EXPECT_TRUE(matcher.match(a));
}

TEST_F(AnyTrueMatcherTest_184, ListAllZeros_184) {
    std::list<int> l = {0, 0, 0};
    EXPECT_FALSE(matcher.match(l));
}

TEST_F(AnyTrueMatcherTest_184, ListSomeNonZero_184) {
    std::list<int> l = {0, 0, 7};
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(AnyTrueMatcherTest_184, DequeAllFalse_184) {
    std::deque<bool> d = {false, false};
    EXPECT_FALSE(matcher.match(d));
}

TEST_F(AnyTrueMatcherTest_184, DequeOneTrue_184) {
    std::deque<bool> d = {false, true};
    EXPECT_TRUE(matcher.match(d));
}

TEST_F(AnyTrueMatcherTest_184, EmptyList_184) {
    std::list<bool> l = {};
    EXPECT_FALSE(matcher.match(l));
}

// --- Floating point truthy/falsy ---

TEST_F(AnyTrueMatcherTest_184, VectorDoubleAllZeros_184) {
    std::vector<double> v = {0.0, 0.0, 0.0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, VectorDoubleSomeNonZero_184) {
    std::vector<double> v = {0.0, 3.14, 0.0};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, VectorDoubleSmallNonZero_184) {
    std::vector<double> v = {0.0, 0.0001, 0.0};
    EXPECT_TRUE(matcher.match(v));
}

// --- Pointer-like truthy/falsy ---

TEST_F(AnyTrueMatcherTest_184, VectorNullptrs_184) {
    int a = 5;
    std::vector<int*> v = {nullptr, nullptr, nullptr};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, VectorSomeNonNullptr_184) {
    int a = 5;
    std::vector<int*> v = {nullptr, &a, nullptr};
    EXPECT_TRUE(matcher.match(v));
}

// --- C-style array via initializer list / rvalue ---

TEST_F(AnyTrueMatcherTest_184, InitializerListAllFalse_184) {
    EXPECT_FALSE(matcher.match(std::vector<bool>{false, false, false}));
}

TEST_F(AnyTrueMatcherTest_184, InitializerListOneTrue_184) {
    EXPECT_TRUE(matcher.match(std::vector<bool>{false, true, false}));
}

// --- Large range ---

TEST_F(AnyTrueMatcherTest_184, LargeRangeAllFalse_184) {
    std::vector<bool> v(10000, false);
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, LargeRangeLastTrue_184) {
    std::vector<bool> v(10000, false);
    v.back() = true;
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, LargeRangeFirstTrue_184) {
    std::vector<bool> v(10000, false);
    v.front() = true;
    EXPECT_TRUE(matcher.match(v));
}

// --- Const reference ---

TEST_F(AnyTrueMatcherTest_184, ConstVectorMatch_184) {
    const std::vector<bool> v = {false, false, true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AnyTrueMatcherTest_184, ConstVectorNoMatch_184) {
    const std::vector<int> v = {0, 0, 0};
    EXPECT_FALSE(matcher.match(v));
}

// --- Set container ---

TEST_F(AnyTrueMatcherTest_184, SetContainingZeroOnly_184) {
    std::set<int> s = {0};
    EXPECT_FALSE(matcher.match(s));
}

TEST_F(AnyTrueMatcherTest_184, SetContainingNonZero_184) {
    std::set<int> s = {0, 1, 2};
    EXPECT_TRUE(matcher.match(s));
}

TEST_F(AnyTrueMatcherTest_184, EmptySet_184) {
    std::set<int> s = {};
    EXPECT_FALSE(matcher.match(s));
}
