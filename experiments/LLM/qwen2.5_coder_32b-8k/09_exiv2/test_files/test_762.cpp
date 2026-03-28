#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using testing::_;

using testing::Return;



class ExifdatumTest : public ::testing::Test {

protected:

    MockValue* mock_value_;

    Exifdatum exif_datum_;



    class MockValue : public Value {

    public:

        MOCK_METHOD1(toRational, Rational(size_t n)) const;

        using Value::Value; // Inherit constructors

    };



    ExifdatumTest() 

        : mock_value_(new MockValue(TypeId::rational),

          exif_datum_(*exiv2::ExifKey::create("Exif.Image.Artist"), mock_value_) {

    }



    ~ExifdatumTest() override = default;

};



TEST_F(ExifdatumTest, ToRational_ValidIndex_ReturnsExpectedRational_762) {

    EXPECT_CALL(*mock_value_, toRational(0)).WillOnce(Return(Rational(1, 2)));

    Rational result = exif_datum_.toRational(0);

    EXPECT_EQ(result, Rational(1, 2));

}



TEST_F(ExifdatumTest, ToRational_InvalidIndex_ReturnsNegativeOneOverOne_762) {

    Rational result = exif_datum_.toRational(1); // Assuming index 1 is invalid

    EXPECT_EQ(result, Rational(-1, 1));

}



TEST_F(ExifdatumTest, ToRational_ZeroIndex_ReturnsExpectedRational_762) {

    EXPECT_CALL(*mock_value_, toRational(0)).WillOnce(Return(Rational(3, 4)));

    Rational result = exif_datum_.toRational(0);

    EXPECT_EQ(result, Rational(3, 4));

}



TEST_F(ExifdatumTest, ToRational_LargeIndex_ReturnsNegativeOneOverOne_762) {

    Rational result = exif_datum_.toRational(LARGE_INT); // Assuming large index is invalid

    EXPECT_EQ(result, Rational(-1, 1));

}
