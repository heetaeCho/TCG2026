#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <limits>



namespace Exiv2 {

    class Value {

    public:

        virtual ~Value() = default;

        virtual size_t count() const = 0;

        virtual Rational toRational(size_t index) const = 0;

    };



    struct Rational {

        int32_t first;

        int32_t second;

    };



    namespace Internal {

        std::ostream& printDegrees(std::ostream& os, const Value& value, const ExifData* exifData);

    }

}



using namespace ::testing;



class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(count, size_t());

    MOCK_CONST_METHOD1(toRational, Exiv2::Rational(size_t));

};



class PrintDegreesTest_1379 : public Test {

protected:

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    const Exiv2::ExifData* exifData = nullptr; // Assuming ExifData is a class

};



TEST_F(PrintDegreesTest_1379, NormalOperation_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(3));

    EXPECT_CALL(mockValue, toRational(0)).WillOnce(Return(Exiv2::Rational{45, 1}));

    EXPECT_CALL(mockValue, toRational(1)).WillOnce(Return(Exiv2::Rational{30, 1}));

    EXPECT_CALL(mockValue, toRational(2)).WillOnce(Return(Exiv2::Rational{0, 1}));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("45 deg 30' 0\"", os.str());

}



TEST_F(PrintDegreesTest_1379, BoundaryConditions_ZeroDegrees_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(3));

    EXPECT_CALL(mockValue, toRational(0)).WillOnce(Return(Exiv2::Rational{0, 1}));

    EXPECT_CALL(mockValue, toRational(1)).WillOnce(Return(Exiv2::Rational{0, 1}));

    EXPECT_CALL(mockValue, toRational(2)).WillOnce(Return(Exiv2::Rational{0, 1}));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("0 deg 0' 0\"", os.str());

}



TEST_F(PrintDegreesTest_1379, BoundaryConditions_MaxSeconds_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(3));

    EXPECT_CALL(mockValue, toRational(0)).WillOnce(Return(Exiv2::Rational{45, 1}));

    EXPECT_CALL(mockValue, toRational(1)).WillOnce(Return(Exiv2::Rational{30, 1}));

    EXPECT_CALL(mockValue, toRational(2)).WillOnce(Return(Exiv2::Rational{std::numeric_limits<int32_t>::max(), 1}));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("(45/1 30/1 " + std::to_string(std::numeric_limits<int32_t>::max()) + "/1)", os.str());

}



TEST_F(PrintDegreesTest_1379, ErrorCase_DenominatorZero_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(3));

    EXPECT_CALL(mockValue, toRational(0)).WillOnce(Return(Exiv2::Rational{45, 0}));

    EXPECT_CALL(mockValue, toRational(1)).WillOnce(Return(Exiv2::Rational{30, 1}));

    EXPECT_CALL(mockValue, toRational(2)).WillOnce(Return(Exiv2::Rational{0, 1}));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("(45/0 30/1 0/1)", os.str());

}



TEST_F(PrintDegreesTest_1379, ErrorCase_MinDenominatorZero_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(3));

    EXPECT_CALL(mockValue, toRational(0)).WillOnce(Return(Exiv2::Rational{45, 1}));

    EXPECT_CALL(mockValue, toRational(1)).WillOnce(Return(Exiv2::Rational{30, 0}));

    EXPECT_CALL(mockValue, toRational(2)).WillOnce(Return(Exiv2::Rational{0, 1}));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("(45/1 30/0 0/1)", os.str());

}



TEST_F(PrintDegreesTest_1379, ErrorCase_SecDenominatorZero_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(3));

    EXPECT_CALL(mockValue, toRational(0)).WillOnce(Return(Exiv2::Rational{45, 1}));

    EXPECT_CALL(mockValue, toRational(1)).WillOnce(Return(Exiv2::Rational{30, 1}));

    EXPECT_CALL(mockValue, toRational(2)).WillOnce(Return(Exiv2::Rational{0, 0}));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("(45/1 30/1 0/0)", os.str());

}



TEST_F(PrintDegreesTest_1379, ErrorCase_CountLessThanThree_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(2));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("()", os.str());

}



TEST_F(PrintDegreesTest_1379, PrecisionHandling_1379) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(3));

    EXPECT_CALL(mockValue, toRational(0)).WillOnce(Return(Exiv2::Rational{45, 1}));

    EXPECT_CALL(mockValue, toRational(1)).WillOnce(Return(Exiv2::Rational{30, 1}));

    EXPECT_CALL(mockValue, toRational(2)).WillOnce(Return(Exiv2::Rational{45, 1}));



    Exiv2::Internal::printDegrees(os, mockValue, exifData);

    EXPECT_EQ("45 deg 30' 45.00\"", os.str());

}
