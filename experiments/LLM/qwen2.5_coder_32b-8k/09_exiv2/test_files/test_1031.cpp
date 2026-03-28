#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    namespace Internal {

        std::ostream& printMinoltaSonyDynamicRangeOptimizerMode(std::ostream& os, const Value& value, const ExifData* metadata);

    }

}



using ::testing::_;



class PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031 : public ::testing::Test {

protected:

    Exiv2::Value mockValue;

    Exiv2::ExifData mockMetadata;

};



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, NormalOperationOff_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(0u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("Off", os.str());

}



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, NormalOperationStandard_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(1u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("Standard", os.str());

}



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, NormalOperationAdvancedAuto_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(2u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("Advanced Auto", os.str());

}



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, NormalOperationAdvancedLevel_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(3u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("Advanced Level", os.str());

}



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, NormalOperationAuto_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(4097u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("Auto", os.str());

}



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, BoundaryConditionZero_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(0u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("Off", os.str());

}



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, BoundaryConditionMaxKnown_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(4097u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("Auto", os.str());

}



TEST_F(PrintMinoltaSonyDynamicRangeOptimizerModeTest_1031, ExceptionalCaseUnknownValue_1031) {

    EXPECT_CALL(mockValue, toUint32(0)).WillOnce(::testing::Return(5u));

    std::ostringstream os;

    Exiv2::Internal::printMinoltaSonyDynamicRangeOptimizerMode(os, mockValue, &mockMetadata);

    EXPECT_EQ("5", os.str()); // Assuming it prints the value as a string if unknown

}
