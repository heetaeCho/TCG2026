#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "minoltamn_int.cpp"



namespace Exiv2 {

namespace Internal {



class PrintMinoltaSonyZoneMatchingTest : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;

    const ExifData* metadata = nullptr;



    void SetUp() override {

        // Set up any common state before tests (if needed)

    }



    void TearDown() override {

        // Clean up any common state after tests (if needed)

    }

};



TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, NormalOperationISOSettingUsed_1037) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(0));

    printMinoltaSonyZoneMatching(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "ISO Setting Used");

}



TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, NormalOperationHighKey_1037) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(1));

    printMinoltaSonyZoneMatching(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "High Key");

}



TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, NormalOperationLowKey_1037) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(2));

    printMinoltaSonyZoneMatching(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "Low Key");

}



TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, BoundaryConditionInvalidIndex_1037) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(-1));

    printMinoltaSonyZoneMatching(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(PrintMinoltaSonyZoneMatchingTest_1037, BoundaryConditionOutofBoundsIndex_1037) {

    EXPECT_CALL(mockValue, toInt64(0)).WillOnce(::testing::Return(3));

    printMinoltaSonyZoneMatching(os, mockValue, metadata);

    EXPECT_EQ(os.str(), "");

}



} // namespace Internal

} // namespace Exiv2
