#include <gtest/gtest.h>
#include <vector>
#include <array>
#include <list>
#include <string>
#include <deque>

// Include the header under test
namespace Catch {
namespace Matchers {

class AllTrueMatcher {
public:
    template <typename RangeLike>
    bool match(RangeLike&& rng) const {
        for (auto&& elem : rng) {
            if (!elem) {
                return false;
            }
        }
        return true;
    }
};

} // namespace Matchers
} // namespace Catch

class AllTrueMatcherTest_182 : public ::testing::Test {
protected:
    Catch::Matchers::AllTrueMatcher matcher;
};

// Normal operation tests

TEST_F(AllTrueMatcherTest_182, AllTrueVector_ReturnsTrue_182) {
    std::vector<bool> v = {true, true, true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, AllFalseVector_ReturnsFalse_182) {
    std::vector<bool> v = {false, false, false};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, MixedBoolVector_ReturnsFalse_182) {
    std::vector<bool> v = {true, false, true};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, SingleTrueElement_ReturnsTrue_182) {
    std::vector<bool> v = {true};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, SingleFalseElement_ReturnsFalse_182) {
    std::vector<bool> v = {false};
    EXPECT_FALSE(matcher.match(v));
}

// Boundary conditions

TEST_F(AllTrueMatcherTest_182, EmptyVector_ReturnsTrue_182) {
    std::vector<bool> v = {};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, EmptyIntVector_ReturnsTrue_182) {
    std::vector<int> v = {};
    EXPECT_TRUE(matcher.match(v));
}

// Integer-based tests (truthy/falsy semantics)

TEST_F(AllTrueMatcherTest_182, AllNonZeroInts_ReturnsTrue_182) {
    std::vector<int> v = {1, 2, 3, 42, -1};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, ContainsZeroInt_ReturnsFalse_182) {
    std::vector<int> v = {1, 2, 0, 3};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, AllZeroInts_ReturnsFalse_182) {
    std::vector<int> v = {0, 0, 0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, SingleZeroInt_ReturnsFalse_182) {
    std::vector<int> v = {0};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, SingleNonZeroInt_ReturnsTrue_182) {
    std::vector<int> v = {42};
    EXPECT_TRUE(matcher.match(v));
}

// Different container types

TEST_F(AllTrueMatcherTest_182, ArrayAllTrue_ReturnsTrue_182) {
    std::array<bool, 3> a = {true, true, true};
    EXPECT_TRUE(matcher.match(a));
}

TEST_F(AllTrueMatcherTest_182, ArrayWithFalse_ReturnsFalse_182) {
    std::array<bool, 3> a = {true, false, true};
    EXPECT_FALSE(matcher.match(a));
}

TEST_F(AllTrueMatcherTest_182, ListAllTrue_ReturnsTrue_182) {
    std::list<bool> l = {true, true, true};
    EXPECT_TRUE(matcher.match(l));
}

TEST_F(AllTrueMatcherTest_182, ListWithFalse_ReturnsFalse_182) {
    std::list<bool> l = {true, false, true};
    EXPECT_FALSE(matcher.match(l));
}

TEST_F(AllTrueMatcherTest_182, DequeAllTrue_ReturnsTrue_182) {
    std::deque<bool> d = {true, true, true};
    EXPECT_TRUE(matcher.match(d));
}

TEST_F(AllTrueMatcherTest_182, DequeWithFalse_ReturnsFalse_182) {
    std::deque<bool> d = {true, true, false};
    EXPECT_FALSE(matcher.match(d));
}

// Pointer-like types (nullptr is falsy)

TEST_F(AllTrueMatcherTest_182, AllNonNullPointers_ReturnsTrue_182) {
    int a = 1, b = 2, c = 3;
    std::vector<int*> v = {&a, &b, &c};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, ContainsNullPointer_ReturnsFalse_182) {
    int a = 1, b = 2;
    std::vector<int*> v = {&a, nullptr, &b};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, AllNullPointers_ReturnsFalse_182) {
    std::vector<int*> v = {nullptr, nullptr};
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, EmptyPointerVector_ReturnsTrue_182) {
    std::vector<int*> v = {};
    EXPECT_TRUE(matcher.match(v));
}

// Double/float tests (0.0 is falsy)

TEST_F(AllTrueMatcherTest_182, AllNonZeroDoubles_ReturnsTrue_182) {
    std::vector<double> v = {1.0, 2.5, -3.14, 0.001};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, ContainsZeroDouble_ReturnsFalse_182) {
    std::vector<double> v = {1.0, 0.0, 2.0};
    EXPECT_FALSE(matcher.match(v));
}

// First element false - early return test

TEST_F(AllTrueMatcherTest_182, FirstElementFalse_ReturnsFalse_182) {
    std::vector<bool> v = {false, true, true, true};
    EXPECT_FALSE(matcher.match(v));
}

// Last element false

TEST_F(AllTrueMatcherTest_182, LastElementFalse_ReturnsFalse_182) {
    std::vector<bool> v = {true, true, true, false};
    EXPECT_FALSE(matcher.match(v));
}

// Large container

TEST_F(AllTrueMatcherTest_182, LargeAllTrueVector_ReturnsTrue_182) {
    std::vector<int> v(10000, 1);
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, LargeVectorWithOneZeroAtEnd_ReturnsFalse_182) {
    std::vector<int> v(10000, 1);
    v.back() = 0;
    EXPECT_FALSE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, LargeVectorWithOneZeroAtBeginning_ReturnsFalse_182) {
    std::vector<int> v(10000, 1);
    v.front() = 0;
    EXPECT_FALSE(matcher.match(v));
}

// Rvalue reference container

TEST_F(AllTrueMatcherTest_182, RvalueVectorAllTrue_ReturnsTrue_182) {
    EXPECT_TRUE(matcher.match(std::vector<bool>{true, true, true}));
}

TEST_F(AllTrueMatcherTest_182, RvalueVectorWithFalse_ReturnsFalse_182) {
    EXPECT_FALSE(matcher.match(std::vector<bool>{true, false, true}));
}

TEST_F(AllTrueMatcherTest_182, RvalueEmptyVector_ReturnsTrue_182) {
    EXPECT_TRUE(matcher.match(std::vector<bool>{}));
}

// Initializer list via array

TEST_F(AllTrueMatcherTest_182, CStyleArrayAllTrue_ReturnsTrue_182) {
    bool arr[] = {true, true, true};
    EXPECT_TRUE(matcher.match(arr));
}

TEST_F(AllTrueMatcherTest_182, CStyleArrayWithFalse_ReturnsFalse_182) {
    bool arr[] = {true, false, true};
    EXPECT_FALSE(matcher.match(arr));
}

// Negative integers are truthy

TEST_F(AllTrueMatcherTest_182, NegativeInts_ReturnsTrue_182) {
    std::vector<int> v = {-1, -2, -100};
    EXPECT_TRUE(matcher.match(v));
}

// Char type (0 char is falsy)

TEST_F(AllTrueMatcherTest_182, NonNullChars_ReturnsTrue_182) {
    std::vector<char> v = {'a', 'b', 'c'};
    EXPECT_TRUE(matcher.match(v));
}

TEST_F(AllTrueMatcherTest_182, ContainsNullChar_ReturnsFalse_182) {
    std::vector<char> v = {'a', '\0', 'c'};
    EXPECT_FALSE(matcher.match(v));
}
