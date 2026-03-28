#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace testing;

using namespace Exiv2::Internal;



class PrintMinoltaSonyPrioritySetupShutterReleaseTest : public Test {

protected:

    std::ostringstream os;

    NiceMock<MockValue> mockValue;

    const ExifData* metadata = nullptr;



    class MockValue : public Value {

    public:

        MOCK_CONST_METHOD0(count, size_t());

        MOCK_CONST_METHOD1(toInt64, int64_t(size_t));

    };

};



TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, NormalOperation_AF_1032) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(0));



    printMinoltaSonyPrioritySetupShutterRelease(os, mockValue, metadata);



    EXPECT_EQ("AF", os.str());

}



TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, NormalOperation_Release_1032) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(1));



    printMinoltaSonyPrioritySetupShutterRelease(os, mockValue, metadata);



    EXPECT_EQ("Release", os.str());

}



TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, BoundaryCondition_EmptyCount_1032) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(0));



    printMinoltaSonyPrioritySetupShutterRelease(os, mockValue, metadata);



    EXPECT_EQ("", os.str());

}



TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, BoundaryCondition_OutOfRangeValue_1032) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(1));

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(Return(2));



    printMinoltaSonyPrioritySetupShutterRelease(os, mockValue, metadata);



    EXPECT_EQ("", os.str());

}



TEST_F(PrintMinoltaSonyPrioritySetupShutterReleaseTest_1032, ExceptionalCase_NegativeCount_1032) {

    EXPECT_CALL(mockValue, count()).WillOnce(Return(-1));



    printMinoltaSonyPrioritySetupShutterRelease(os, mockValue, metadata);



    EXPECT_EQ("", os.str());

}
