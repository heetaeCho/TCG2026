#include <gtest/gtest.h>
#include <string>
#include "exiv2/properties.hpp"  // Include the header for the Exiv2::XmpNsInfo

namespace Exiv2 {

class XmpNsInfoTest : public ::testing::Test {
protected:
    // Setup and teardown if needed
    void SetUp() override {
        // Initialize objects or mocks if needed
    }

    void TearDown() override {
        // Clean up if needed
    }
};

// TEST_ID: 1241
TEST_F(XmpNsInfoTest, EqualityOperator_Prefix_Equal_1241) {
    // Setup: Create two Prefix objects with the same value
    XmpNsInfo::Prefix prefix1{"prefix"};
    XmpNsInfo::Prefix prefix2{"prefix"};

    // Setup: Create XmpNsInfo objects with the given Prefixes
    XmpNsInfo info1{"namespace1", "prefix", nullptr};
    XmpNsInfo info2{"namespace1", "prefix", nullptr};

    // Verify: Check if the Prefixes are equal using the equality operator
    EXPECT_TRUE(info1 == prefix1);
    EXPECT_TRUE(info2 == prefix2);
}

// TEST_ID: 1242
TEST_F(XmpNsInfoTest, EqualityOperator_Prefix_NotEqual_1242) {
    // Setup: Create two Prefix objects with different values
    XmpNsInfo::Prefix prefix1{"prefix1"};
    XmpNsInfo::Prefix prefix2{"prefix2"};

    // Setup: Create XmpNsInfo objects with the given Prefixes
    XmpNsInfo info1{"namespace1", "prefix1", nullptr};
    XmpNsInfo info2{"namespace1", "prefix2", nullptr};

    // Verify: Check if the Prefixes are not equal using the equality operator
    EXPECT_FALSE(info1 == prefix2);
    EXPECT_FALSE(info2 == prefix1);
}

// TEST_ID: 1243
TEST_F(XmpNsInfoTest, EqualityOperator_Ns_Equal_1243) {
    // Setup: Create two Ns objects with the same value
    XmpNsInfo::Ns ns1{"namespace"};
    XmpNsInfo::Ns ns2{"namespace"};

    // Setup: Create XmpNsInfo objects with the given Ns
    XmpNsInfo info1{"namespace", "prefix", nullptr};
    XmpNsInfo info2{"namespace", "prefix", nullptr};

    // Verify: Check if the Ns are equal using the equality operator
    EXPECT_TRUE(info1 == ns1);
    EXPECT_TRUE(info2 == ns2);
}

// TEST_ID: 1244
TEST_F(XmpNsInfoTest, EqualityOperator_Ns_NotEqual_1244) {
    // Setup: Create two Ns objects with different values
    XmpNsInfo::Ns ns1{"namespace1"};
    XmpNsInfo::Ns ns2{"namespace2"};

    // Setup: Create XmpNsInfo objects with the given Ns
    XmpNsInfo info1{"namespace1", "prefix", nullptr};
    XmpNsInfo info2{"namespace2", "prefix", nullptr};

    // Verify: Check if the Ns are not equal using the equality operator
    EXPECT_FALSE(info1 == ns2);
    EXPECT_FALSE(info2 == ns1);
}

// TEST_ID: 1245
TEST_F(XmpNsInfoTest, EqualityOperator_Prefix_XmpNsInfo_Equal_1245) {
    // Setup: Create XmpNsInfo objects with identical prefixes
    XmpNsInfo::Prefix prefix{"prefix"};
    XmpNsInfo info1{"namespace", "prefix", nullptr};
    XmpNsInfo info2{"namespace", "prefix", nullptr};

    // Verify: Check if the equality operator works with XmpNsInfo objects
    EXPECT_TRUE(info1 == prefix);
    EXPECT_TRUE(info2 == prefix);
}

// TEST_ID: 1246
TEST_F(XmpNsInfoTest, EqualityOperator_Prefix_XmpNsInfo_NotEqual_1246) {
    // Setup: Create XmpNsInfo objects with different prefixes
    XmpNsInfo::Prefix prefix1{"prefix1"};
    XmpNsInfo::Prefix prefix2{"prefix2"};
    XmpNsInfo info1{"namespace", "prefix1", nullptr};
    XmpNsInfo info2{"namespace", "prefix2", nullptr};

    // Verify: Check if the equality operator works with different prefixes
    EXPECT_FALSE(info1 == prefix2);
    EXPECT_FALSE(info2 == prefix1);
}

}  // namespace Exiv2