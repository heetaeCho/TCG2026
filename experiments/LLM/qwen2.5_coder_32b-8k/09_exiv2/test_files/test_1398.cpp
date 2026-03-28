#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tags_int.cpp"

#include <sstream>



namespace Exiv2 {

    class Value {

    public:

        virtual ~Value() = default;

        virtual int64_t toInt64() const = 0;

    };

}



using namespace Exiv2::Internal;



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(int64_t, toInt64, (), (const, override));

};



TEST_F(WriteBatchTest_1398, Print0x8827_NormalOperation_1398) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(12345));



    std::ostringstream os;

    print0x8827(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "12345");

}



TEST_F(WriteBatchTest_1398, Print0x8827_BoundaryCondition_Zero_1398) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(0));



    std::ostringstream os;

    print0x8827(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(WriteBatchTest_1398, Print0x8827_BoundaryCondition_MaxInt64_1398) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(std::numeric_limits<int64_t>::max()));



    std::ostringstream os;

    print0x8827(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<int64_t>::max()));

}



TEST_F(WriteBatchTest_1398, Print0x8827_BoundaryCondition_MinInt64_1398) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toInt64()).WillOnce(::testing::Return(std::numeric_limits<int64_t>::min()));



    std::ostringstream os;

    print0x8827(os, mockValue, nullptr);



    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<int64_t>::min()));

}
