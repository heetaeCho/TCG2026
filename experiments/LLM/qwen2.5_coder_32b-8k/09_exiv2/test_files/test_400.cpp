#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/tiffcomposite_int.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class TiffImageEntryTest : public ::testing::Test {

protected:

    TiffImageEntry tiffImageEntry;

};



TEST_F(TiffImageEntryTest_NormalOperation_400, DoSizeDataGroupLessThanOrEqualToMnId_400) {

    EXPECT_CALL(tiffImageEntry, group()).WillOnce(::testing::Return(Exiv2::IfdId::mnId));

    EXPECT_EQ(tiffImageEntry.doSizeData(), 0);

}



TEST_F(TiffImageEntryTest_NormalOperation_400, DoSizeDataGroupGreaterThanMnId_400) {

    EXPECT_CALL(tiffImageEntry, group()).WillOnce(::testing::Return(Exiv2::IfdId::canonId));

    EXPECT_CALL(tiffImageEntry, sizeImage()).WillOnce(::testing::Return(100));

    EXPECT_EQ(tiffImageEntry.doSizeData(), 100);

}



TEST_F(TiffImageEntryTest_BoundaryCondition_400, DoSizeDataGroupIsMnId_400) {

    EXPECT_CALL(tiffImageEntry, group()).WillOnce(::testing::Return(Exiv2::IfdId::mnId));

    EXPECT_EQ(tiffImageEntry.doSizeData(), 0);

}



TEST_F(TiffImageEntryTest_BoundaryCondition_400, DoSizeDataGroupIsGreaterThanMnId_400) {

    EXPECT_CALL(tiffImageEntry, group()).WillOnce(::testing::Return(Exiv2::IfdId::canonId));

    EXPECT_CALL(tiffImageEntry, sizeImage()).WillOnce(::testing::Return(1));

    EXPECT_EQ(tiffImageEntry.doSizeData(), 1);

}



TEST_F(TiffImageEntryTest_ErrorCase_400, DoSizeDataGroupIsInvalid_400) {

    EXPECT_CALL(tiffImageEntry, group()).WillOnce(::testing::Return(static_cast<Exiv2::IfdId>(-1)));

    EXPECT_EQ(tiffImageEntry.doSizeData(), 0);

}
