#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Dict.h"



using namespace testing;



class DictTest_118 : public Test {

protected:

    Dict* dict;

    XRef xrefMock;



    void SetUp() override {

        dict = new Dict(&xrefMock);

    }



    void TearDown() override {

        delete dict;

    }

};



TEST_F(DictTest_118, GetXRef_ReturnsCorrectReference_118) {

    EXPECT_EQ(dict->getXRef(), &xrefMock);

}



TEST_F(DictTest_118, HasKey_ReturnsFalseForNonExistentKey_118) {

    EXPECT_FALSE(dict->hasKey("nonexistent"));

}



TEST_F(DictTest_118, AddAndHasKey_ReturnTrueForAddedKey_118) {

    dict->add("key", Object());

    EXPECT_TRUE(dict->hasKey("key"));

}



TEST_F(DictTest_118, RemoveAndHasKey_ReturnFalseAfterRemoval_118) {

    dict->add("key", Object());

    dict->remove("key");

    EXPECT_FALSE(dict->hasKey("key"));

}



TEST_F(DictTest_118, LookupNF_OnNonExistentKey_ThrowsNoException_118) {

    // Assuming lookupNF does not throw an exception for non-existent keys

    EXPECT_NO_THROW(dict->lookupNF("nonexistent"));

}



TEST_F(DictTest_118, SetAndLookup_ReturnsSetValue_118) {

    Object obj;

    dict->set("key", std::move(obj));

    const Object& retrievedObj = dict->lookupNF("key");

    EXPECT_EQ(&retrievedObj, &obj);

}



TEST_F(DictTest_118, GetLength_ReturnsZeroForEmptyDict_118) {

    EXPECT_EQ(dict->getLength(), 0);

}



TEST_F(DictTest_118, AddAndGetLength_IncreasesLengthByOne_118) {

    dict->add("key", Object());

    EXPECT_EQ(dict->getLength(), 1);

}



TEST_F(DictTest_118, RemoveAndGetLength_DecreasesLengthByOne_118) {

    dict->add("key", Object());

    dict->remove("key");

    EXPECT_EQ(dict->getLength(), 0);

}
