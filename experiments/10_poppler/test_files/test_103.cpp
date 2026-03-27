#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_103 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_103, GetStream_ReturnsValidPointerForStreamType_103) {

    Object obj(ObjType::objStream, "dummy_stream");

    Stream* stream = obj.getStream();

    EXPECT_NE(stream, nullptr);

}



TEST_F(ObjectTest_103, GetStream_ReturnsNullForNonStreamType_103) {

    Object obj(ObjType::objDict, "{}");

    Stream* stream = obj.getStream();

    EXPECT_EQ(stream, nullptr);

}



TEST_F(ObjectTest_103, IsStream_ReturnsTrueForStreamType_103) {

    Object obj(ObjType::objStream, "dummy_stream");

    EXPECT_TRUE(obj.isStream());

}



TEST_F(ObjectTest_103, IsStream_ReturnsFalseForNonStreamType_103) {

    Object obj(ObjType::objDict, "{}");

    EXPECT_FALSE(obj.isStream());

}



TEST_F(ObjectTest_103, GetType_ReturnsCorrectType_103) {

    Object obj(ObjType::objInt64, 12345LL);

    EXPECT_EQ(obj.getType(), ObjType::objInt64);

}



TEST_F(ObjectTest_103, IsDict_ReturnsTrueForDictType_103) {

    Object obj(ObjType::objDict, "{}");

    EXPECT_TRUE(obj.isDict());

}



TEST_F(ObjectTest_103, IsDict_ReturnsFalseForNonDictType_103) {

    Object obj(ObjType::objArray, "[]");

    EXPECT_FALSE(obj.isDict());

}



TEST_F(ObjectTest_103, GetTypeName_ReturnsCorrectName_103) {

    Object obj(ObjType::objReal, 3.14);

    std::string typeName = obj.getTypeName();

    EXPECT_EQ(typeName, "real");

}
