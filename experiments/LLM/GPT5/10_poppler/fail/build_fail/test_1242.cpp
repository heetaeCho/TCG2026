#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler-private.h"
#include "Error.h"  // Assuming this header contains ErrorStringType enum definition.

namespace Poppler {

    // Mock class for testing purposes
    class MockPoppler {
    public:
        MOCK_METHOD(Poppler::ErrorStringType, fromPopplerCore, (::ErrorStringType type), (const));
    };

}  // namespace Poppler

// TEST ID 1242
TEST_F(PopplerErrorConversionTest_1242, fromPopplerCore_ValidErrorCodeString_1242) {
    // Given a valid ErrorCodeString type
    ::ErrorStringType type = ::ErrorStringType::ErrorCodeString;

    // When we call the function
    Poppler::ErrorStringType result = Poppler::fromPopplerCore(type);

    // Then it should return ErrorCodeString
    EXPECT_EQ(result, Poppler::ErrorStringType::ErrorCodeString);
}

// TEST ID 1243
TEST_F(PopplerErrorConversionTest_1243, fromPopplerCore_ValidUserString_1243) {
    // Given a valid UserString type
    ::ErrorStringType type = ::ErrorStringType::UserString;

    // When we call the function
    Poppler::ErrorStringType result = Poppler::fromPopplerCore(type);

    // Then it should return UserString
    EXPECT_EQ(result, Poppler::ErrorStringType::UserString);
}

// TEST ID 1244
TEST_F(PopplerErrorConversionTest_1244, fromPopplerCore_InvalidType_1244) {
    // Given an invalid ErrorStringType (not handled by the switch)
    ::ErrorStringType type = static_cast<::ErrorStringType>(999);  // Assume 999 is invalid

    // When we call the function
    Poppler::ErrorStringType result = Poppler::fromPopplerCore(type);

    // Then it should default to ErrorCodeString (the fallback case)
    EXPECT_EQ(result, Poppler::ErrorStringType::ErrorCodeString);
}

}  // namespace Poppler