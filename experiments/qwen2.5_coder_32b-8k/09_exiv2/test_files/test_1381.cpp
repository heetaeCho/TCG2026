#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exif.hpp>

#include <exiv2/value.hpp>



namespace Exiv2 {

namespace Internal {



class PrintExifUnitTest_1381 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;



    PrintExifUnitTest_1381() : value(TypeId::unsignedRational) {}



    std::string printExifUnitToString(const Value& value, const ExifData* metadata = nullptr) {

        std::ostringstream oss;

        printExifUnit(oss, value, metadata);

        return oss.str();

    }

};



TEST_F(PrintExifUnitTest_1381, NormalOperation_1381) {

    EXPECT_EQ(printExifUnitToString(value), "none");

}



TEST_F(PrintExifUnitTest_1381, BoundaryConditions_ValueNotModified_1381) {

    std::string originalValue = printExifUnitToString(value);

    EXPECT_EQ(printExifUnitToString(value), originalValue);

}



TEST_F(PrintExifUnitTest_1381, MetadataNullptr_1381) {

    EXPECT_EQ(printExifUnitToString(value, nullptr), "none");

}



// Since the internal behavior is treated as a black box and we don't have control over

// setting specific values in ExifData or Value that would change the output of printExifUnit,

// we can only test with the default constructed objects.



}  // namespace Internal

}  // namespace Exiv2
