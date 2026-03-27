#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/error.hpp"



namespace Exiv2 {

    namespace Internal {

        static void findLensSpecFlags(const Value& value, std::string& flagsStart, std::string& flagsEnd);

    }

}



using ::testing::_;

using ::testing::Return;

using ::testing::Throw;



class MockValue : public Exiv2::Value {

public:

    MOCK_METHOD(size_t, toUint32, (size_t n), (const, override));

};



TEST(findLensSpecFlagsTest_1606, NormalOperation_NoFlags_1606) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(0));

    EXPECT_CALL(mockValue, toUint32(7)).WillOnce(Return(0));



    std::string flagsStart, flagsEnd;

    Exiv2::Internal::findLensSpecFlags(mockValue, flagsStart, flagsEnd);



    EXPECT_EQ(flagsStart, "");

    EXPECT_EQ(flagsEnd, "");

}



TEST(findLensSpecFlagsTest_1606, NormalOperation_SingleFlag_Start_1606) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(16));

    EXPECT_CALL(mockValue, toUint32(7)).WillOnce(Return(0));



    std::string flagsStart, flagsEnd;

    Exiv2::Internal::findLensSpecFlags(mockValue, flagsStart, flagsEnd);



    EXPECT_EQ(flagsStart, "SSM");

    EXPECT_EQ(flagsEnd, "");

}



TEST(findLensSpecFlagsTest_1606, NormalOperation_MultipleFlags_StartAndEnd_1606) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(259));

    EXPECT_CALL(mockValue, toUint32(7)).WillOnce(Return(48));



    std::string flagsStart, flagsEnd;

    Exiv2::Internal::findLensSpecFlags(mockValue, flagsStart, flagsEnd);



    EXPECT_EQ(flagsStart, "FE DT");

    EXPECT_EQ(flagsEnd, "ZA G");

}



TEST(findLensSpecFlagsTest_1606, NormalOperation_MultipleFlags_StartOnly_1606) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(98));

    EXPECT_CALL(mockValue, toUint32(7)).WillOnce(Return(0));



    std::string flagsStart, flagsEnd;

    Exiv2::Internal::findLensSpecFlags(mockValue, flagsStart, flagsEnd);



    EXPECT_EQ(flagsStart, "Reflex STF");

    EXPECT_EQ(flagsEnd, "");

}



TEST(findLensSpecFlagsTest_1606, NormalOperation_MultipleFlags_EndOnly_1606) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(0));

    EXPECT_CALL(mockValue, toUint32(7)).WillOnce(Return(48));



    std::string flagsStart, flagsEnd;

    Exiv2::Internal::findLensSpecFlags(mockValue, flagsStart, flagsEnd);



    EXPECT_EQ(flagsStart, "");

    EXPECT_EQ(flagsEnd, "ZA G");

}



TEST(findLensSpecFlagsTest_1606, BoundaryCondition_MaxUint32Values_1606) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(UINT32_MAX));

    EXPECT_CALL(mockValue, toUint32(7)).WillOnce(Return(UINT32_MAX));



    std::string flagsStart, flagsEnd;

    Exiv2::Internal::findLensSpecFlags(mockValue, flagsStart, flagsEnd);



    EXPECT_EQ(flagsStart, "PZ OSS LE II");

    EXPECT_EQ(flagsEnd, "Fisheye Macro Reflex STF");

}



TEST(findLensSpecFlagsTest_1606, ExceptionalCase_MaskDoesNotMatch_1606) {

    MockValue mockValue;

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toUint32(7)).WillOnce(Return(1));



    std::string flagsStart, flagsEnd;

    EXPECT_THROW(Exiv2::Internal::findLensSpecFlags(mockValue, flagsStart, flagsEnd), Exiv2::Error);

}
