#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class RefTest_56 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Teardown if necessary

    }

};



TEST_F(RefTest_56, InvalidRefValues_56) {

    Ref invalidRef = Ref::INVALID();

    EXPECT_EQ(invalidRef.num, -1);

    EXPECT_EQ(invalidRef.gen, -1);

}



// Assuming there are no other methods to test in the provided interface,

// we focus on the behavior of the INVALID() method.



TEST_F(RefTest_56, InvalidRefConstexpr_56) {

    constexpr Ref invalidRef = Ref::INVALID();

    static_assert(invalidRef.num == -1, "Invalid num value");

    static_assert(invalidRef.gen == -1, "Invalid gen value");

}

```


