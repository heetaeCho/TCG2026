#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;

using namespace testing;



// Mock class for Value to verify interactions if needed.

class MockValue : public Value {

public:

    MOCK_METHOD(std::ostream&, write, (std::ostream& os), (const override));

};



TEST_F(Test_1392, Print0x0112_ValidOrientation_1392) {

    ExifData metadata;

    MockValue mockValue(TypeId::undefined);



    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "top, left";

    }));



    std::ostringstream oss;

    Internal::print0x0112(oss, mockValue, &metadata);

    EXPECT_EQ("top, left", oss.str());

}



TEST_F(Test_1392, Print0x0112_DefaultOrientation_1392) {

    ExifData metadata;

    MockValue mockValue(TypeId::undefined);



    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "Unknown";

    }));



    std::ostringstream oss;

    Internal::print0x0112(oss, mockValue, &metadata);

    EXPECT_EQ("Unknown", oss.str());

}



TEST_F(Test_1392, Print0x0112_NullMetadata_1392) {

    MockValue mockValue(TypeId::undefined);



    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "top, left";

    }));



    std::ostringstream oss;

    Internal::print0x0112(oss, mockValue, nullptr);

    EXPECT_EQ("top, left", oss.str());

}



TEST_F(Test_1392, Print0x0112_OutOfRangeOrientation_1392) {

    ExifData metadata;

    MockValue mockValue(TypeId::undefined);



    EXPECT_CALL(mockValue, write(_)).WillOnce(Invoke([](std::ostream& os) -> std::ostream& {

        return os << "Unknown";

    }));



    std::ostringstream oss;

    Internal::print0x0112(oss, mockValue, &metadata);

    EXPECT_EQ("Unknown", oss.str());

}
