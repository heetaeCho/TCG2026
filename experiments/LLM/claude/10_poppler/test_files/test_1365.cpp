#include <gtest/gtest.h>

// Include necessary headers
#include "poppler/CertificateInfo.h"

// We need to access the static function defined in the .cc file
// Since it's a static (file-scope) function in a namespace, we include the source
// to make it available in this translation unit
#include "qt5/src/poppler-form.cc"

using namespace Poppler;

class FromPopplerCoreKeyLocationTest_1365 : public ::testing::Test {
protected:
};

// Test mapping of KeyLocation::Computer
TEST_F(FromPopplerCoreKeyLocationTest_1365, ComputerMapsCorrectly_1365)
{
    CertificateInfo::KeyLocation result = fromPopplerCore(KeyLocation::Computer);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Computer);
}

// Test mapping of KeyLocation::Other
TEST_F(FromPopplerCoreKeyLocationTest_1365, OtherMapsCorrectly_1365)
{
    CertificateInfo::KeyLocation result = fromPopplerCore(KeyLocation::Other);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Other);
}

// Test mapping of KeyLocation::Unknown
TEST_F(FromPopplerCoreKeyLocationTest_1365, UnknownMapsCorrectly_1365)
{
    CertificateInfo::KeyLocation result = fromPopplerCore(KeyLocation::Unknown);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Unknown);
}

// Test mapping of KeyLocation::HardwareToken
TEST_F(FromPopplerCoreKeyLocationTest_1365, HardwareTokenMapsCorrectly_1365)
{
    CertificateInfo::KeyLocation result = fromPopplerCore(KeyLocation::HardwareToken);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::HardwareToken);
}

// Test that an invalid/out-of-range enum value falls through to Unknown
TEST_F(FromPopplerCoreKeyLocationTest_1365, InvalidValueReturnsUnknown_1365)
{
    // Cast an invalid integer to KeyLocation to test the default return path
    KeyLocation invalidLocation = static_cast<KeyLocation>(999);
    CertificateInfo::KeyLocation result = fromPopplerCore(invalidLocation);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Unknown);
}

// Test that negative invalid value also returns Unknown
TEST_F(FromPopplerCoreKeyLocationTest_1365, NegativeInvalidValueReturnsUnknown_1365)
{
    KeyLocation invalidLocation = static_cast<KeyLocation>(-1);
    CertificateInfo::KeyLocation result = fromPopplerCore(invalidLocation);
    EXPECT_EQ(result, CertificateInfo::KeyLocation::Unknown);
}

// Test all valid enum values map to distinct output values
TEST_F(FromPopplerCoreKeyLocationTest_1365, AllValidValuesMapToDistinctOutputs_1365)
{
    CertificateInfo::KeyLocation resultUnknown = fromPopplerCore(KeyLocation::Unknown);
    CertificateInfo::KeyLocation resultOther = fromPopplerCore(KeyLocation::Other);
    CertificateInfo::KeyLocation resultComputer = fromPopplerCore(KeyLocation::Computer);
    CertificateInfo::KeyLocation resultHardwareToken = fromPopplerCore(KeyLocation::HardwareToken);

    // Verify all results are distinct (except potentially Unknown which is the default)
    EXPECT_NE(resultOther, resultComputer);
    EXPECT_NE(resultOther, resultHardwareToken);
    EXPECT_NE(resultComputer, resultHardwareToken);
    EXPECT_NE(resultUnknown, resultOther);
    EXPECT_NE(resultUnknown, resultComputer);
    EXPECT_NE(resultUnknown, resultHardwareToken);
}

// Test that the underlying integer values are preserved in the mapping
TEST_F(FromPopplerCoreKeyLocationTest_1365, UnderlyingValuesPreserved_1365)
{
    EXPECT_EQ(static_cast<int>(fromPopplerCore(KeyLocation::Unknown)), 0);
    EXPECT_EQ(static_cast<int>(fromPopplerCore(KeyLocation::Other)), 1);
    EXPECT_EQ(static_cast<int>(fromPopplerCore(KeyLocation::Computer)), 2);
    EXPECT_EQ(static_cast<int>(fromPopplerCore(KeyLocation::HardwareToken)), 3);
}
