#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <sstream>

#include <string>



// Forward declaration of the necessary classes and namespaces

namespace Exiv2 { 

    class Value {

    public:

        virtual ~Value() = default;

        virtual int64_t toInt64() const = 0;

    };



    struct ExifData {};



    namespace Internal {

        class PanasonicMakerNote {

        public:

            std::ostream& print0x0036(std::ostream& os, const Value& value, const ExifData*) {

                if (value.toInt64() == 65535) os << N_("not set");

                else os << value;

                return os;

            }

        };

    }

}



// Mock class for the Value interface

class MockValue : public Exiv2::Value {

public:

    MOCK_CONST_METHOD0(toInt64, int64_t());

};



TEST_F(PanasonicMakerNoteTest_711, Print0x0036_NormalOperation_ValueNot65535_711) {

    using namespace Exiv2;

    using namespace Exiv2::Internal;



    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(123));



    PanasonicMakerNote pmn;

    std::ostringstream os;

    pmn.print0x0036(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "123");

}



TEST_F(PanasonicMakerNoteTest_711, Print0x0036_NormalOperation_ValueIs65535_711) {

    using namespace Exiv2;

    using namespace Exiv2::Internal;



    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(65535));



    PanasonicMakerNote pmn;

    std::ostringstream os;

    pmn.print0x0036(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "not set");

}



TEST_F(PanasonicMakerNoteTest_711, Print0x0036_BoundaryCondition_ZeroValue_711) {

    using namespace Exiv2;

    using namespace Exiv2::Internal;



    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(0));



    PanasonicMakerNote pmn;

    std::ostringstream os;

    pmn.print0x0036(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(PanasonicMakerNoteTest_711, Print0x0036_BoundaryCondition_MaxInt64Value_711) {

    using namespace Exiv2;

    using namespace Exiv2::Internal;



    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(std::numeric_limits<int64_t>::max()));



    PanasonicMakerNote pmn;

    std::ostringstream os;

    pmn.print0x0036(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<int64_t>::max()));

}



TEST_F(PanasonicMakerNoteTest_711, Print0x0036_BoundaryCondition_MinInt64Value_711) {

    using namespace Exiv2;

    using namespace Exiv2::Internal;



    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(std::numeric_limits<int64_t>::min()));



    PanasonicMakerNote pmn;

    std::ostringstream os;

    pmn.print0x0036(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<int64_t>::min()));

}
