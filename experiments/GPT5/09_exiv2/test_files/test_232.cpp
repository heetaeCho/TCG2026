#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

class TiffMappingInfoTest_232 : public ::testing::Test {
protected:
    // Setup code if needed
    TiffMappingInfoTest_232() {}

    // Tear down code if needed
    ~TiffMappingInfoTest_232() override {}
};

// Test the tag function of TiffMappingInfo
TEST_F(TiffMappingInfoTest_232, TagReturnsExpectedValue_232) {
    TiffMappingInfo info;
    // Assuming extendedTag_ is set somewhere before calling tag
    uint16_t expectedTag = 100; // Example value
    info.extendedTag_ = static_cast<int>(expectedTag);  // Set extendedTag_ to match expected value

    EXPECT_EQ(info.tag(), expectedTag);
}

// Test operator== for TiffMappingInfo
TEST_F(TiffMappingInfoTest_232, OperatorEqualsReturnsTrueForEqualObjects_232) {
    TiffMappingInfo info1;
    TiffMappingInfo info2;
    info1.extendedTag_ = 123;
    info2.extendedTag_ = 123;

    EXPECT_TRUE(info1 == info2);  // Assuming operator== compares extendedTag_ values
}

TEST_F(TiffMappingInfoTest_232, OperatorEqualsReturnsFalseForDifferentObjects_232) {
    TiffMappingInfo info1;
    TiffMappingInfo info2;
    info1.extendedTag_ = 123;
    info2.extendedTag_ = 456;

    EXPECT_FALSE(info1 == info2);  // Assuming operator== compares extendedTag_ values
}

// Test behavior when TiffMappingInfo's extendedTag_ is uninitialized (boundary test)
TEST_F(TiffMappingInfoTest_232, TagReturnsZeroForUninitializedExtendedTag_232) {
    TiffMappingInfo info;

    // Extended tag uninitialized, so expected value is zero
    EXPECT_EQ(info.tag(), 0);
}

}  // namespace Internal
}  // namespace Exiv2