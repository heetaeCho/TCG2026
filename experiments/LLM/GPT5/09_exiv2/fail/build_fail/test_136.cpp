#include <gtest/gtest.h>
#include <exiv2/value.hpp>  // The header file where the `getType` function is defined
#include <exiv2/types.hpp>  // The header file for the `TypeId` enum

namespace Exiv2 {

// Test for `getType<uint16_t>()`
TEST_F(Exiv2TypeTest_136, GetTypeForUint16_136) {
    // Testing the normal case: getType<uint16_t>() should return unsignedShort
    EXPECT_EQ(getType<uint16_t>(), unsignedShort);
}

}  // namespace Exiv2