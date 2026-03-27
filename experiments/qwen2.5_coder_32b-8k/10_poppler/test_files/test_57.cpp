#include <gtest/gtest.h>



// Assuming Ref struct is defined as follows based on the provided information:

struct Ref {

    public: int num;

    public: int gen;



    public: static constexpr Ref INVALID() {

        return Ref{0, 0};

    }

};



inline bool operator==(const Ref lhs, const Ref rhs) noexcept { 

    return lhs.num == rhs.num && lhs.gen == rhs.gen; 

}



// Test suite for the Ref struct

class RefTest_57 : public ::testing::Test {};



TEST_F(RefTest_57, EqualRefsReturnTrue_57) {

    Ref ref1{10, 20};

    Ref ref2{10, 20};

    EXPECT_TRUE(ref1 == ref2);

}



TEST_F(RefTest_57, DifferentNumReturnsFalse_57) {

    Ref ref1{10, 20};

    Ref ref2{11, 20};

    EXPECT_FALSE(ref1 == ref2);

}



TEST_F(RefTest_57, DifferentGenReturnsFalse_57) {

    Ref ref1{10, 20};

    Ref ref2{10, 21};

    EXPECT_FALSE(ref1 == ref2);

}



TEST_F(RefTest_57, BothDifferentNumAndGenReturnsFalse_57) {

    Ref ref1{10, 20};

    Ref ref2{11, 21};

    EXPECT_FALSE(ref1 == ref2);

}



TEST_F(RefTest_57, InvalidRefEqualsItself_57) {

    Ref invalidRef = Ref::INVALID();

    EXPECT_TRUE(invalidRef == invalidRef);

}



TEST_F(RefTest_57, ValidRefNotEqualToInvalidRef_57) {

    Ref validRef{10, 20};

    Ref invalidRef = Ref::INVALID();

    EXPECT_FALSE(validRef == invalidRef);

}
