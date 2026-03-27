#include <gtest/gtest.h>



// Assuming rotr function is part of a class or namespace for testing purposes.

// Here we define a simple class to encapsulate the static function for testing.

class DecryptUtils {

public:

    static unsigned int rotr(unsigned int x, unsigned int n) {

        return (x >> n) | (x << (32 - n));

    }

};



TEST(DecryptUtilsTest_1627, NormalOperation_1627) {

    EXPECT_EQ(DecryptUtils::rotr(0b10000000000000000000000000000001, 1), 0b10000000000000000000000000000010);

    EXPECT_EQ(DecryptUtils::rotr(0b00000000000000000000000000000010, 1), 0b10000000000000000000000000000010);

}



TEST(DecryptUtilsTest_1627, BoundaryConditions_1627) {
