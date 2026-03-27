#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/types.cpp"



namespace Exiv2 {

    class Rational {

    public:

        int32_t nominator;

        int32_t denominator;



        Rational(int32_t nom, int32_t denom) : nominator(nom), denominator(denom) {}

        

        bool operator==(const Rational& other) const {

            return this->nominator == other.nominator && this->denominator == other.denominator;

        }

    };

}



using namespace Exiv2;



class GetRationalTest_1142 : public ::testing::Test {

protected:

    ByteOrder byteOrder = littleEndian; // or bigEndian, depending on the test case

};



TEST_F(GetRationalTest_1142, NormalOperation_1142) {

    uint8_t buffer[8] = {0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00}; // Represents rational 1/2

    Rational expected(1, 2);

    EXPECT_EQ(getRational(buffer, byteOrder), expected);

}



TEST_F(GetRationalTest_1142, ZeroDenominator_1142) {

    uint8_t buffer[8] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Represents rational 1/0

    Rational expected(1, 0);

    EXPECT_EQ(getRational(buffer, byteOrder), expected);

}



TEST_F(GetRationalTest_1142, NegativeNominator_1142) {

    uint8_t buffer[8] = {0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x00, 0x00, 0x00}; // Represents rational -1/1

    Rational expected(-1, 1);

    EXPECT_EQ(getRational(buffer, byteOrder), expected);

}



TEST_F(GetRationalTest_1142, NegativeDenominator_1142) {

    uint8_t buffer[8] = {0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF}; // Represents rational 1/-1

    Rational expected(1, -1);

    EXPECT_EQ(getRational(buffer, byteOrder), expected);

}



TEST_F(GetRationalTest_1142, LargeNominator_1142) {

    uint8_t buffer[8] = {0xFF, 0xFF, 0xFF, 0x7F, 0x01, 0x00, 0x00, 0x00}; // Represents rational MAX_INT/1

    Rational expected(2147483647, 1);

    EXPECT_EQ(getRational(buffer, byteOrder), expected);

}



TEST_F(GetRationalTest_1142, LargeDenominator_1142) {

    uint8_t buffer[8] = {0x01, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x7F}; // Represents rational 1/MAX_INT

    Rational expected(1, 2147483647);

    EXPECT_EQ(getRational(buffer, byteOrder), expected);

}
