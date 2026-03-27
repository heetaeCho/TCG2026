#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"

#include <memory>



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_2748, Constructor_Bool_2748) {

    Object obj(true);

    EXPECT_TRUE(obj.isBool());

    EXPECT_EQ(obj.getBool(), true);

}



TEST_F(ObjectTest_2748, Constructor_Int_2748) {

    Object obj(42);

    EXPECT_TRUE(obj.isInt());

    EXPECT_EQ(obj.getInt(), 42);

}



TEST_F(ObjectTest_2748, Constructor_Double_2748) {

    Object obj(3.14);

    EXPECT_TRUE(obj.isReal());

    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);

}



TEST_F(ObjectTest_2748, Constructor_StringView_2748) {

    std::string_view str = "testString";

    Object obj(str);

    EXPECT_TRUE(obj.isHexString());

    EXPECT_STREQ(obj.getHexString()->c_str(), str.data());

}



TEST_F(ObjectTest_2748, Constructor_UniquePtrGooString_2748) {

    auto uniqueStr = std::make_unique<GooString>("uniqueTest");

    Object obj(std::move(uniqueStr));

    EXPECT_TRUE(obj.isHexString());

    EXPECT_STREQ(obj.getHexString()->c_str(), "uniqueTest");

}



TEST_F(ObjectTest_2748, Constructor_ObjType_StringView_2748) {

    std::string_view str = "testString";

    Object obj(objHexString, str);

    EXPECT_TRUE(obj.isHexString());

    EXPECT_STREQ(obj.getHexString()->c_str(), str.data());

}



TEST_F(ObjectTest_2748, Constructor_CharPtr_2748) {

    const char* cstr = "charPtrTest";

    Object obj(objHexString, cstr);

    EXPECT_TRUE(obj.isHexString());

    EXPECT_STREQ(obj.getHexString()->c_str(), cstr);

}



TEST_F(ObjectTest_2748, Constructor_Int64_2748) {

    long long int64Val = 9223372036854775807LL;

    Object obj(int64Val);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), int64Val);

}



TEST_F(ObjectTest_2748, Constructor_MoveSemantics_2748) {

    Object original(true);

    Object moved(std::move(original));

    EXPECT_TRUE(moved.isBool());

    EXPECT_EQ(moved.getBool(), true);

    EXPECT_FALSE(original.isBool()); // Original should be in a valid but unspecified state

}



TEST_F(ObjectTest_2748, Static_NullObject_2748) {

    Object obj = Object::null();

    EXPECT_TRUE(obj.isNull());

}



TEST_F(ObjectTest_2748, Static_EofObject_2748) {

    Object obj = Object::eof();

    EXPECT_TRUE(obj.isEOF());

}



TEST_F(ObjectTest_2748, Static_ErrorObject_2748) {

    Object obj = Object::error();

    EXPECT_TRUE(obj.isError());

}



TEST_F(ObjectTest_2748, SetToNull_2748) {

    Object obj(true);

    obj.setToNull();

    EXPECT_TRUE(obj.isNull());

}
