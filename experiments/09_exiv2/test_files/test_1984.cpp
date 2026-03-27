#include <gtest/gtest.h>

#include "XMPMeta.hpp"

#include "XMPCore_Impl.hpp"



class XMPUtilsTest_1984 : public ::testing::Test {

protected:

    XMPMeta stdXMP;

    XMPMeta extXMP;



    void SetUp() override {

        // Initialize any common data or state here

        stdXMP.SetProperty("http://example.com/schema", "propName", "propValue", 0);

    }

};



TEST_F(XMPUtilsTest_1984, MoveOneProperty_SuccessfulMove_1984) {

    ASSERT_TRUE(MoveOneProperty(stdXMP, &extXMP, "http://example.com/schema", "propName"));

    EXPECT_FALSE(stdXMP.DoesPropertyExist("http://example.com/schema", "propName"));

    EXPECT_TRUE(extXMP.DoesPropertyExist("http://example.com/schema", "propName"));

}



TEST_F(XMPUtilsTest_1984, MoveOneProperty_NonExistentSchemaInStdXMP_1984) {

    EXPECT_FALSE(MoveOneProperty(stdXMP, &extXMP, "nonexistentSchema", "propName"));

    EXPECT_TRUE(stdXMP.DoesPropertyExist("http://example.com/schema", "propName"));

}



TEST_F(XMPUtilsTest_1984, MoveOneProperty_NonExistentPropInStdXMP_1984) {

    EXPECT_FALSE(MoveOneProperty(stdXMP, &extXMP, "http://example.com/schema", "nonexistentProp"));

    EXPECT_TRUE(stdXMP.DoesPropertyExist("http://example.com/schema", "propName"));

}



TEST_F(XMPUtilsTest_1984, MoveOneProperty_CreateNewSchemaInExtXMP_1984) {

    ASSERT_FALSE(extXMP.DoesPropertyExist("newSchema", "propName"));

    EXPECT_TRUE(MoveOneProperty(stdXMP, &extXMP, "newSchema", "propName"));

    EXPECT_TRUE(extXMP.DoesPropertyExist("newSchema", "propName"));

}



TEST_F(XMPUtilsTest_1984, MoveOneProperty_DeleteEmptySchemaInStdXMP_1984) {

    stdXMP.DeleteProperty("http://example.com/schema", "propName");

    stdXMP.SetProperty("http://example.com/schema", "anotherProp", "anotherValue", 0);

    

    ASSERT_TRUE(stdXMP.DoesPropertyExist("http://example.com/schema", "anotherProp"));

    EXPECT_TRUE(MoveOneProperty(stdXMP, &extXMP, "http://example.com/schema", "anotherProp"));

    EXPECT_FALSE(stdXMP.DoesPropertyExist("http://example.com/schema", "anotherProp"));

}



TEST_F(XMPUtilsTest_1984, MoveOneProperty_MultiplePropertiesSameSchema_1984) {

    stdXMP.SetProperty("http://example.com/schema", "prop2", "value2", 0);

    

    EXPECT_TRUE(MoveOneProperty(stdXMP, &extXMP, "http://example.com/schema", "propName"));

    EXPECT_TRUE(extXMP.DoesPropertyExist("http://example.com/schema", "propName"));

    EXPECT_TRUE(stdXMP.DoesPropertyExist("http://example.com/schema", "prop2"));

}
