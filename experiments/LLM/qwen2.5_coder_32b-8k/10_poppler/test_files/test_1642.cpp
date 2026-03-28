#include <gtest/gtest.h>

#include <cstdint>



// Assuming sha512sigma1 is part of a class or namespace, we'll mock it up for testing.

// Since the function is static and inline, we can't directly mock it with Google Mock,

// so we'll wrap it in a class for testing purposes.



class Sha512Mock {

public:

    static uint64_t sha512sigma1(uint64_t x) {

        return ::sha512sigma1(x);

    }

};



TEST(Sha512Sigma1Test_1642, NormalOperation_1642) {

    EXPECT_EQ(Sha512Mock::sha512sigma1(0xFFFFFFFFFFFFFFFF), 0x7FFFEFFF80000000);

    EXPECT_EQ(Sha512Mock::sha512sigma1(0x0000000000000000), 0x0000000000000000);

}



TEST(Sha512Sigma1Test_1642, BoundaryConditions_1642) {

    EXPECT_EQ(Sha512Mock::sha512sigma1(1), 0x8000000000000000);

    EXPECT_EQ(Sha512Mock::sha512sigma1(0x8000000000000000), 0x4000000000000001);

}



TEST(Sha512Sigma1Test_1642, SpecificValues_1642) {

    EXPECT_EQ(Sha512Mock::sha512sigma1(0x0123456789ABCDEF), 0x1BCA9F8E6D5C3B2A);

    EXPECT_EQ(Sha512Mock::sha512sigma1(0xFEDCBA9876543210), 0x058DC2A9F8E6D5C3);

}

```


