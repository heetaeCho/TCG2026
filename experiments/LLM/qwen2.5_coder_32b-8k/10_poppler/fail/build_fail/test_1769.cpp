#include <gtest/gtest.h>

#include "Object.h"



// Mocking Object for testing purposes if needed, but in this case, we don't need to mock it further as per constraints



using namespace std::string_literals;



class IsTableScopeNameTest_1769 : public ::testing::Test {

protected:

    Object rowObj;

    Object columnObj;

    Object bothObj;

    Object otherObj;



    IsTableScopeNameTest_1769()

        : rowObj(ObjType::objName, "Row"s),

          columnObj(ObjType::objName, "Column"s),

          bothObj(ObjType::objName, "Both"s),

          otherObj(ObjType::objName, "Other"s) {}

};



TEST_F(IsTableScopeNameTest_1769, Row_ReturnsTrue_1769) {

    EXPECT_TRUE(isTableScopeName(&rowObj));

}



TEST_F(IsTableScopeNameTest_1769, Column_ReturnsTrue_1769) {

    EXPECT_TRUE(isTableScopeName(&columnObj));

}



TEST_F(IsTableScopeNameTest_1769, Both_ReturnsTrue_1769) {

    EXPECT_TRUE(isTableScopeName(&bothObj));

}



TEST_F(IsTableScopeNameTest_1769, Other_ReturnsFalse_1769) {

    EXPECT_FALSE(isTableScopeName(&otherObj));

}



TEST_F(IsTableScopeNameTest_1769, NullObject_ReturnsFalse_1769) {

    Object nullObj = Object::null();

    EXPECT_FALSE(isTableScopeName(&nullObj));

}



TEST_F(IsTableScopeNameTest_1769, EmptyString_ReturnsFalse_1769) {

    Object emptyStrObj(ObjType::objName, ""s);

    EXPECT_FALSE(isTableScopeName(&emptyStrObj));

}



TEST_F(IsTableScopeNameTest_1769, NonNameObject_ReturnsFalse_1769) {

    Object intObj(42);

    EXPECT_FALSE(isTableScopeName(&intObj));

}
