#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/value.hpp"

#include "exiv2/properties.hpp"

#include "xmp.cpp"



using namespace Exiv2;



class XmpdatumImplTest : public ::testing::Test {

protected:

    XmpKey key1 = XmpKey("Xmp.dc.title");

    XmpKey key2 = XmpKey("Xmp.dc.description");



    Value* value1 = Value::create(TypeId::string);

    Value* value2 = Value::create(TypeId::string);



    Xmpdatum::Impl impl1 = Xmpdatum::Impl(key1, value1);

};



TEST_F(XmpdatumImplTest_1277, CopyConstructor_CopiesKeyAndValue_1277) {

    Xmpdatum::Impl implCopy(impl1);



    EXPECT_EQ(*implCopy.key_, *impl1.key_);

    EXPECT_EQ(*implCopy.value_, *impl1.value_);

}



TEST_F(XmpdatumImplTest_1277, AssignmentOperator_CopiesKeyAndValue_1277) {

    Xmpdatum::Impl impl2(key2, value2);

    impl2 = impl1;



    EXPECT_EQ(*impl2.key_, *impl1.key_);

    EXPECT_EQ(*impl2.value_, *impl1.value_);

}



TEST_F(XmpdatumImplTest_1277, SelfAssignmentOperator_ReturnsSelf_1277) {

    Xmpdatum::Impl& selfAssigned = impl1 = impl1;



    EXPECT_EQ(&selfAssigned, &impl1);

}



TEST_F(XmpdatumImplTest_1277, CopyConstructor_DeepCopiesKeyAndValue_1277) {

    Xmpdatum::Impl implCopy(impl1);



    // Change original key and value

    *value1 = "Modified";

    

    EXPECT_NE(*implCopy.value_, *impl1.value_);

}



TEST_F(XmpdatumImplTest_1277, AssignmentOperator_DeepCopiesKeyAndValue_1277) {

    Xmpdatum::Impl impl2(key2, value2);

    impl2 = impl1;



    // Change original key and value

    *value1 = "Modified";

    

    EXPECT_NE(*impl2.value_, *impl1.value_);

}
