#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/types.hpp"
#include "exiv2/error.hpp"
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mocking external collaborator for testing
class MockLogHandler {
public:
    MOCK_METHOD(void, log, (int level, const char* msg), ());
};

class TiffTypeTest : public ::testing::Test {
protected:
    MockLogHandler mockLogHandler;
    TiffTypeTest() {
        // Set up the log handler for testing
        LogMsg::setHandler([this](int level, const char* msg) { mockLogHandler.log(level, msg); });
    }
};

TEST_F(TiffTypeTest, ValidTypeIdReturnsCorrectTiffType_412) {
    // Testing a valid TypeId, expected to return the corresponding TiffType
    TypeId validTypeId = unsignedByte;  // 1
    TiffType expectedType = ttUnsignedByte;

    EXPECT_EQ(toTiffType(validTypeId), expectedType);
}

TEST_F(TiffTypeTest, TypeIdGreaterThanMaxValueReturnsUndefined_413) {
    // Testing TypeId greater than 0xffff, which should return ttUndefined
    TypeId invalidTypeId = static_cast<TypeId>(0x10000);
    TiffType expectedType = ttUndefined;

    EXPECT_EQ(toTiffType(invalidTypeId), expectedType);
}

TEST_F(TiffTypeTest, InvalidTypeIdLogsWarning_414) {
    // Testing logging behavior when TypeId is greater than 0xffff
    TypeId invalidTypeId = static_cast<TypeId>(0x10000);

    // Expecting that the warning message will be logged
    EXPECT_CALL(mockLogHandler, log(LogMsg::warn, ::testing::HasSubstr("is not a valid Exif (TIFF) type")))
        .Times(1);

    toTiffType(invalidTypeId);  // This will trigger the log warning
}

TEST_F(TiffTypeTest, ValidTypeIdReturnsCorrectTiffTypeWithMultipleCases_415) {
    // Testing multiple valid TypeIds and verifying they return correct TiffType
    EXPECT_EQ(toTiffType(unsignedShort), ttUnsignedShort);
    EXPECT_EQ(toTiffType(unsignedLong), ttUnsignedLong);
    EXPECT_EQ(toTiffType(tiffFloat), ttTiffFloat);
    EXPECT_EQ(toTiffType(tiffDouble), ttTiffDouble);
}

TEST_F(TiffTypeTest, InvalidTypeIdReturnsUndefinedWithLog_416) {
    // Testing invalid TypeId logging and return value
    TypeId invalidTypeId = static_cast<TypeId>(131070);  // invalidTypeId
    TiffType expectedType = ttUndefined;

    EXPECT_CALL(mockLogHandler, log(LogMsg::warn, ::testing::HasSubstr("is not a valid Exif (TIFF) type")))
        .Times(1);

    EXPECT_EQ(toTiffType(invalidTypeId), expectedType);
}

}  // namespace Internal
}  // namespace Exiv2