#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "tags_int.cpp"  // Assuming this is where print0xa405 is defined



namespace Exiv2 {

    class ValueMock : public Value {

    public:

        MOCK_METHOD(int64_t, toInt64, (), (const override));

    };

}



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0xa405Test_1415 : public ::testing::Test {

protected:

    std::ostringstream os_;

    ValueMock value_;

};



TEST_F(Print0xa405Test_1415, NormalOperation_NonZeroLength_1415) {

    EXPECT_CALL(value_, toInt64()).WillOnce(::testing::Return(123));

    print0xa405(os_, value_, nullptr);

    EXPECT_EQ(os_.str(), "123.0 mm");

}



TEST_F(Print0xa405Test_1415, BoundaryCondition_ZeroLength_1415) {

    EXPECT_CALL(value_, toInt64()).WillOnce(::testing::Return(0));

    print0xa405(os_, value_, nullptr);

    EXPECT_EQ(os_.str(), "Unknown");

}



TEST_F(Print0xa405Test_1415, BoundaryCondition_NegativeLength_1415) {

    EXPECT_CALL(value_, toInt64()).WillOnce(::testing::Return(-1));

    print0xa405(os_, value_, nullptr);

    EXPECT_EQ(os_.str(), "-1.0 mm");

}
