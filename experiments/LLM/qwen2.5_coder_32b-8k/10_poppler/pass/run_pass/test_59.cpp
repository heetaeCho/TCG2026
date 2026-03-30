#include <gtest/gtest.h>



// Assuming the Ref struct is defined as follows:

struct Ref {

    public: int num;

    public: int gen;

    public: static constexpr Ref INVALID() { return Ref{-1, -1}; }

};



inline bool operator<(const Ref lhs, const Ref rhs) noexcept {

    if (lhs.num != rhs.num) {

        return lhs.num < rhs.num;

    }

    return lhs.gen < rhs.gen;

}



// Test fixture for Ref comparison

class RefComparisonTest_59 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if necessary

    }



    void TearDown() override {

        // Teardown code, if necessary

    }

};



// Test case to check normal operation where lhs.num < rhs.num

TEST_F(RefComparisonTest_59, NormalOperation_LhsNumLessThanRhsNum_59) {

    Ref lhs{1, 2};

    Ref rhs{2, 3};

    EXPECT_TRUE(lhs < rhs);

}



// Test case to check normal operation where lhs.num > rhs.num

TEST_F(RefComparisonTest_59, NormalOperation_LhsNumGreaterThanRhsNum_59) {

    Ref lhs{3, 4};

    Ref rhs{2, 1};

    EXPECT_FALSE(lhs < rhs);

}



// Test case to check normal operation where lhs.gen < rhs.gen and lhs.num == rhs.num

TEST_F(RefComparisonTest_59, NormalOperation_LhsGenLessThanRhsGen_SameNum_59) {

    Ref lhs{2, 1};

    Ref rhs{2, 3};

    EXPECT_TRUE(lhs < rhs);

}



// Test case to check normal operation where lhs.gen > rhs.gen and lhs.num == rhs.num

TEST_F(RefComparisonTest_59, NormalOperation_LhsGenGreaterThanRhsGen_SameNum_59) {

    Ref lhs{2, 4};

    Ref rhs{2, 3};

    EXPECT_FALSE(lhs < rhs);

}



// Test case to check boundary condition where both num and gen are equal

TEST_F(RefComparisonTest_59, BoundaryCondition_EqualRefs_59) {

    Ref lhs{1, 2};

    Ref rhs{1, 2};

    EXPECT_FALSE(lhs < rhs);

}



// Test case to check boundary condition with invalid refs

TEST_F(RefComparisonTest_59, BoundaryCondition_InvalidRefs_59) {

    Ref lhs = Ref::INVALID();

    Ref rhs{0, 0};

    EXPECT_TRUE(lhs < rhs);



    Ref lhs2{0, 0};

    Ref rhs2 = Ref::INVALID();

    EXPECT_FALSE(lhs2 < rhs2);

}
