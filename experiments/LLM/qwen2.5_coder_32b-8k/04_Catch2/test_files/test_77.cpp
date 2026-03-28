#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_tostring.hpp"



namespace Catch { namespace Detail {



class ConvertUnstreamableTest_77 : public ::testing::Test {

protected:

    // Helper function to convert enum to string for testing

    template<typename T>

    std::string convertEnumToString(T const& value) {

        return convertUnstreamable(value);

    }

};



// Test normal operation with a sample enum

enum SampleEnum_77 { Value1, Value2, Value3 };

TEST_F(ConvertUnstreamableTest_77, ConvertKnownEnumValue_77) {

    EXPECT_EQ(convertEnumToString(SampleEnum_77::Value1), "SampleEnum_77::Value1");

    EXPECT_EQ(convertEnumToString(SampleEnum_77::Value2), "SampleEnum_77::Value2");

    EXPECT_EQ(convertEnumToString(SampleEnum_77::Value3), "SampleEnum_77::Value3");

}



// Test boundary conditions with the smallest and largest possible enum values

TEST_F(ConvertUnstreamableTest_77, ConvertBoundaryEnumValues_77) {

    EXPECT_EQ(convertEnumToString(static_cast<SampleEnum_77>(0)), "SampleEnum_77::Value1");

    EXPECT_EQ(convertEnumToString(static_cast<SampleEnum_77>(2)), "SampleEnum_77::Value3");

}



// Test exceptional or error cases by passing an invalid enum value

TEST_F(ConvertUnstreamableTest_77, ConvertInvalidEnumValue_77) {

    // Assuming that convertUnknownEnumToString will return a default string for unknown values

    EXPECT_EQ(convertEnumToString(static_cast<SampleEnum_77>(-1)), "unknown_enum_value");

    EXPECT_EQ(convertEnumToString(static_cast<SampleEnum_77>(4)), "unknown_enum_value");

}



} }  // namespace Catch::Detail
