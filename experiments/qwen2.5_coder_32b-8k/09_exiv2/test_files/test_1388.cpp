#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



class Print0x000aTest : public Test {

protected:

    Internal::TagDetails tagDetails = {{'2', "2-dimensional measurement"}, {'3', "3-dimensional measurement"}};

    NiceMock<MockValue> mockValue;

    ExifData exifData;



    class MockValue : public Value {

    public:

        using Value::Value;

        MOCK_METHOD(std::ostream&, write, (std::ostream& os), (const override));

    };



    Print0x000aTest() : mockValue(TypeId::undefined) {}

};



TEST_F(Print0x000aTest_1388, NormalOperation_PrintsCorrectly_1388) {

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "2-dimensional measurement";

    }));



    std::ostringstream oss;

    Internal::print0x000a(oss, mockValue, &exifData);



    EXPECT_EQ("2-dimensional measurement", oss.str());

}



TEST_F(Print0x000aTest_1388, BoundaryCondition_EmptyTagDetails_1388) {

    Internal::TagDetails emptyTagDetails = {};

    const auto& originalExifGPSMeasureMode = Exiv2::Internal::exifGPSMeasureMode;

    Exiv2::Internal::exifGPSMeasureMode = emptyTagDetails;



    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os;

    }));



    std::ostringstream oss;

    Internal::print0x000a(oss, mockValue, &exifData);



    Exiv2::Internal::exifGPSMeasureMode = originalExifGPSMeasureMode;



    EXPECT_EQ("", oss.str());

}



TEST_F(Print0x000aTest_1388, ExceptionalCase_NullMetadata_1388) {

    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os;

    }));



    std::ostringstream oss;

    Internal::print0x000a(oss, mockValue, nullptr);



    EXPECT_EQ("", oss.str());

}
