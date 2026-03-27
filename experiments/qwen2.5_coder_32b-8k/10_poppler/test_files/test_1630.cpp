#include <gtest/gtest.h>

#include <cstdint>



// Assuming the function sha256Sigma0 is part of a class or namespace for testing purposes.

// Here we define a simple wrapper to make it testable.

class Sha256Helper {

public:

    static unsigned int sha256Sigma0(unsigned int x) {

        return ::sha256Sigma0(x);

    }

};



TEST_F(Sha256HelperTest_1630, TestNormalOperation_1630) {

    EXPECT_EQ(Sha256Helper::sha256Sigma0(0x12345678), 0xc9d0c04b);

}



TEST_F(Sha256HelperTest_1630, TestBoundaryConditions_ZeroInput_1630) {

    EXPECT_EQ(Sha256Helper::sha256Sigma0(0x00000000), 0x00000000);

}



TEST_F(Sha256HelperTest_1630, TestBoundaryConditions_MaxInput_1630) {

    EXPECT_EQ(Sha256Helper::sha256Sigma0(0xFFFFFFFF), 0x76b8a79d);

}

```


