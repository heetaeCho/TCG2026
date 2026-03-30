#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace testing;

using namespace Exiv2;



namespace {



class MockValue : public Value {

public:

    MOCK_METHOD(std::ostream&, write, (std::ostream& os), (const, override));

};



class TagsIntTest_1389 : public Test {

protected:

    ExifData exifData;

    MockValue mockValue;

};



TEST_F(TagsIntTest_1389, NormalOperation_K_1389) {

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "K";

    }));



    std::ostringstream oss;

    Internal::print0x000c(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "km/h");

}



TEST_F(TagsIntTest_1389, NormalOperation_M_1389) {

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "M";

    }));



    std::ostringstream oss;

    Internal::print0x000c(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "mph");

}



TEST_F(TagsIntTest_1389, NormalOperation_N_1389) {

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "N";

    }));



    std::ostringstream oss;

    Internal::print0x000c(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "knots");

}



TEST_F(TagsIntTest_1389, BoundaryCondition_EmptyString_1389) {

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os;

    }));



    std::ostringstream oss;

    Internal::print0x000c(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "");

}



TEST_F(TagsIntTest_1389, BoundaryCondition_UnrecognizedChar_1389) {

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "X";

    }));



    std::ostringstream oss;

    Internal::print0x000c(oss, mockValue, &exifData);

    EXPECT_EQ(oss.str(), "");

}



}  // namespace
