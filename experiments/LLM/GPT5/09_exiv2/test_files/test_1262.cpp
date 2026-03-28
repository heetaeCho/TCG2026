#include <gtest/gtest.h>
#include "properties.hpp"

namespace Exiv2 {

class XmpKeyTest : public ::testing::Test {
protected:
    XmpKey xmpKey;
    XmpKey xmpKeyWithPrefix;

    XmpKeyTest() : xmpKey("testKey"), xmpKeyWithPrefix("testPrefix", "testProperty") {}
};

TEST_F(XmpKeyTest, FamilyName_Default) {
    // TEST_ID 1262
    EXPECT_STREQ(xmpKey.familyName(), "Iptc");
}

TEST_F(XmpKeyTest, FamilyName_WithPrefix) {
    // TEST_ID 1263
    EXPECT_STREQ(xmpKeyWithPrefix.familyName(), "Iptc");
}

TEST_F(XmpKeyTest, FamilyName_Empty) {
    // TEST_ID 1264
    XmpKey emptyKey("");
    EXPECT_STREQ(emptyKey.familyName(), "Iptc");
}

TEST_F(XmpKeyTest, Clone_Default) {
    // TEST_ID 1265
    XmpKey clonedKey = *xmpKey.clone();
    EXPECT_STREQ(clonedKey.familyName(), "Iptc");
    EXPECT_EQ(clonedKey.key(), xmpKey.key());
}

TEST_F(XmpKeyTest, AssignmentOperator) {
    // TEST_ID 1266
    XmpKey assignedKey = xmpKey;
    EXPECT_STREQ(assignedKey.familyName(), "Iptc");
    EXPECT_EQ(assignedKey.key(), xmpKey.key());
}

TEST_F(XmpKeyTest, AssignmentOperator_WithPrefix) {
    // TEST_ID 1267
    XmpKey assignedKeyWithPrefix = xmpKeyWithPrefix;
    EXPECT_STREQ(assignedKeyWithPrefix.familyName(), "Iptc");
    EXPECT_EQ(assignedKeyWithPrefix.key(), xmpKeyWithPrefix.key());
}

TEST_F(XmpKeyTest, Destructor) {
    // TEST_ID 1268
    {
        XmpKey tempKey("testKey");
        EXPECT_STREQ(tempKey.familyName(), "Iptc");
    }  // tempKey goes out of scope, destructor should be called
    // No assertion needed, just checking for memory issues on destruction
}

TEST_F(XmpKeyTest, Key) {
    // TEST_ID 1269
    EXPECT_EQ(xmpKey.key(), "testKey");
}

TEST_F(XmpKeyTest, Key_Empty) {
    // TEST_ID 1270
    XmpKey emptyKey("");
    EXPECT_EQ(emptyKey.key(), "");
}

TEST_F(XmpKeyTest, BoundaryTest_LongKey) {
    // TEST_ID 1271
    std::string longKey(1000, 'a');
    XmpKey longKeyObj(longKey);
    EXPECT_EQ(longKeyObj.key(), longKey);
}

TEST_F(XmpKeyTest, BoundaryTest_LongPrefix) {
    // TEST_ID 1272
    std::string longPrefix(1000, 'b');
    std::string longProperty(1000, 'c');
    XmpKey longPrefixObj(longPrefix, longProperty);
    EXPECT_EQ(longPrefixObj.key(), longPrefix + longProperty);
}

}  // namespace Exiv2