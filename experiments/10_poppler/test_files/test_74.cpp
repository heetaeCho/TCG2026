#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_74, IsNum_ReturnsTrueForInt_74) {

    Object obj(1);

    EXPECT_TRUE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsTrueForReal_74) {

    Object obj(1.0);

    EXPECT_TRUE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsTrueForInt64_74) {

    Object obj(static_cast<long long>(1));

    EXPECT_TRUE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForBool_74) {

    Object obj(true);

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForString_74) {

    Object obj("test");

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForNull_74) {

    Object obj = Object::null();

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForArray_74) {

    Array* array = new Array();

    Object obj(array);

    delete array;

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForDict_74) {

    Dict* dict = new Dict();

    Object obj(dict);

    delete dict;

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForStream_74) {

    // Assuming Stream is a mockable interface

    // Since we cannot create an actual stream object here, this test assumes that the constructor works as expected.

    Object obj(static_cast<Stream*>(nullptr));

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForRef_74) {

    Ref ref(1, 0);

    Object obj(ref);

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForCmd_74) {

    Object obj("cmd");

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForError_74) {

    Object obj = Object::error();

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForEOF_74) {

    Object obj = Object::eof();

    EXPECT_FALSE(obj.isNum());

}



TEST_F(ObjectTest_74, IsNum_ReturnsFalseForNone_74) {

    Object obj;

    EXPECT_FALSE(obj.isNum());

}
