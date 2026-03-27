#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XMPMeta.hpp"
#include "XMPCore_Impl.hpp"
#include "XMP_Const.h"

using ::testing::_;
using ::testing::Return;

class XMPUtilsTest_1984 : public ::testing::Test {
protected:
    // Mock objects or setup can be done here
    XMPMeta stdXMP;
    XMPMeta extXMP;
    XMP_StringPtr schemaURI = "http://example.com/schema";
    XMP_StringPtr propName = "property";
};

TEST_F(XMPUtilsTest_1984, MoveOneProperty_NormalOperation_1984) {
    // Test normal operation of MoveOneProperty
    bool result = MoveOneProperty(stdXMP, &extXMP, schemaURI, propName);
    EXPECT_TRUE(result);  // Expect the property move operation to succeed
}

TEST_F(XMPUtilsTest_1984, MoveOneProperty_PropertyNotFound_1984) {
    // Test when the property is not found
    XMP_StringPtr nonExistingPropName = "nonExistingProperty";
    bool result = MoveOneProperty(stdXMP, &extXMP, schemaURI, nonExistingPropName);
    EXPECT_FALSE(result);  // Expect the property move operation to fail
}

TEST_F(XMPUtilsTest_1984, MoveOneProperty_EmptyProperty_1984) {
    // Test with an empty property name
    XMP_StringPtr emptyPropName = "";
    bool result = MoveOneProperty(stdXMP, &extXMP, schemaURI, emptyPropName);
    EXPECT_FALSE(result);  // Expect the property move operation to fail for empty property
}

TEST_F(XMPUtilsTest_1984, MoveOneProperty_SchemaNotFound_1984) {
    // Test when schema is not found in either XMP
    XMP_StringPtr nonExistingSchemaURI = "http://example.com/nonExistingSchema";
    bool result = MoveOneProperty(stdXMP, &extXMP, nonExistingSchemaURI, propName);
    EXPECT_FALSE(result);  // Expect the property move operation to fail
}

TEST_F(XMPUtilsTest_1984, MoveOneProperty_ExtXMPNull_1984) {
    // Test when extXMP is null
    XMPMeta* nullExtXMP = nullptr;
    bool result = MoveOneProperty(stdXMP, nullExtXMP, schemaURI, propName);
    EXPECT_FALSE(result);  // Expect the property move operation to fail if extXMP is null
}

TEST_F(XMPUtilsTest_1984, MoveOneProperty_VerifyExternalInteraction_1984) {
    // Test verification of external interaction (i.e., mock interaction on external XMPMeta)
    // In a real scenario, we could mock the behavior of stdXMP and extXMP interactions
    EXPECT_CALL(stdXMP, DeleteEmptySchema(_))
        .Times(1);  // Expect that DeleteEmptySchema is called once during the property move

    bool result = MoveOneProperty(stdXMP, &extXMP, schemaURI, propName);
    EXPECT_TRUE(result);  // Expect the property move operation to succeed
}