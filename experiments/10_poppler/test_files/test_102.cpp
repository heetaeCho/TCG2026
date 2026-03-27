#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_102 : public ::testing::Test {

protected:

    ObjectTest_102() {}

    virtual ~ObjectTest_102() {}



    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_102, GetDict_ReturnsNullPointerWhenNotDict_102) {

    Object obj;

    EXPECT_EQ(obj.getDict(), nullptr);

}



TEST_F(ObjectTest_102, IsDict_ReturnsFalseForNonDictObject_102) {

    Object obj(ObjType::objInt, 42);

    EXPECT_FALSE(obj.isDict());

}



TEST_F(ObjectTest_102, GetDict_ReturnsValidPointerWhenDict_102) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_EQ(obj.getDict(), dict);

    delete dict;

}



TEST_F(ObjectTest_102, IsDict_ReturnsTrueForDictObject_102) {

    Dict* dict = new Dict();

    Object obj(dict);

    EXPECT_TRUE(obj.isDict());

    delete dict;

}



TEST_F(ObjectTest_102, GetDict_DoesNotModifyObjectState_102) {

    Dict* dict = new Dict();

    const Object obj(dict);

    EXPECT_EQ(obj.getDict(), dict);

    delete dict;

}
