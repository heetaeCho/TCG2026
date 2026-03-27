#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Dict.h"

#include "Object.h"

#include "StructElement.h"



using namespace testing;



class RoleMapResolveTest : public Test {

protected:

    Dict roleMap;

};



TEST_F(RoleMapResolveTest, NormalOperation_1786) {

    Object resolvedObj(Object(ObjType::objName, "DocumentRoot"));

    EXPECT_CALL(roleMap, lookup(StrEq("DocumentRoot"))).WillOnce(Return(resolvedObj));

    EXPECT_EQ(roleMapResolve(&roleMap, "DocumentRoot"), StructElement::Type::DocumentRoot);

}



TEST_F(RoleMapResolveTest, CircularReference_1786) {

    Object first(Object(ObjType::objName, "First"));

    Object second(Object(ObjType::objName, "Second"));



    EXPECT_CALL(roleMap, lookup(StrEq("First"))).WillOnce(Return(first));

    EXPECT_CALL(roleMap, lookup(StrEq("Second"))).WillOnce(Return(second));

    EXPECT_CALL(roleMap, lookup(StrEq("Circular"))).WillRepeatedly(Return(first));



    EXPECT_EQ(roleMapResolve(&roleMap, "Circular"), StructElement::Type::Unknown);

}



TEST_F(RoleMapResolveTest, UnknownName_1786) {

    Object unknownObj(Object(ObjType::objName, "UnknownName"));

    EXPECT_CALL(roleMap, lookup(StrEq("UnknownName"))).WillOnce(Return(unknownObj));

    EXPECT_EQ(roleMapResolve(&roleMap, "UnknownName"), StructElement::Type::Unknown);

}



TEST_F(RoleMapResolveTest, NonNameObject_1786) {

    Object nonNameObj(Object(ObjType::objInt, 42));

    EXPECT_CALL(roleMap, lookup(StrEq("NonName"))).WillOnce(Return(nonNameObj));

    EXPECT_EQ(roleMapResolve(&roleMap, "NonName"), StructElement::Type::Unknown);

}



TEST_F(RoleMapResolveTest, NestedResolution_1786) {

    Object first(Object(ObjType::objName, "First"));

    Object second(Object(ObjType::objName, "DocumentRoot"));



    EXPECT_CALL(roleMap, lookup(StrEq("First"))).WillOnce(Return(first));

    EXPECT_CALL(roleMap, lookup(StrEq("Second"))).WillOnce(Return(second));



    EXPECT_EQ(roleMapResolve(&roleMap, "First"), StructElement::Type::DocumentRoot);

}



TEST_F(RoleMapResolveTest, NullObject_1786) {

    Object nullObj(Object::null());

    EXPECT_CALL(roleMap, lookup(StrEq("NullName"))).WillOnce(Return(nullObj));

    EXPECT_EQ(roleMapResolve(&roleMap, "NullName"), StructElement::Type::Unknown);

}
