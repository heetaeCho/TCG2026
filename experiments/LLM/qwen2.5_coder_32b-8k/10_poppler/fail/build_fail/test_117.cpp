#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Dict.h"

#include "XRef.h"



using namespace testing;



class DictTest : public ::testing::Test {

protected:

    XRef* mockXRef;

    Dict* dictUnderTest;



    void SetUp() override {

        mockXRef = new XRef();

        dictUnderTest = new Dict(mockXRef);

    }



    void TearDown() override {

        delete dictUnderTest;

        delete mockXRef;

    }

};



TEST_F(DictTest_117, SetXRefSetsCorrectly_117) {

    EXPECT_EQ(dictUnderTest->getXRef(), mockXRef);

}



TEST_F(DictTest_117, GetLengthInitiallyZero_117) {

    EXPECT_EQ(dictUnderTest->getLength(), 0);

}



TEST_F(DictTest_117, AddKeyIncrementsCount_117) {

    Object obj;

    dictUnderTest->add("key1", std::move(obj));

    EXPECT_EQ(dictUnderTest->getLength(), 1);

}



TEST_F(DictTest_117, HasKeyReturnsTrueAfterAdd_117) {

    Object obj;

    dictUnderTest->add("key1", std::move(obj));

    EXPECT_TRUE(dictUnderTest->hasKey("key1"));

}



TEST_F(DictTest_117, RemoveKeyDecrementsCount_117) {

    Object obj;

    dictUnderTest->add("key1", std::move(obj));

    dictUnderTest->remove("key1");

    EXPECT_EQ(dictUnderTest->getLength(), 0);

}



TEST_F(DictTest_117, HasKeyReturnsFalseAfterRemove_117) {

    Object obj;

    dictUnderTest->add("key1", std::move(obj));

    dictUnderTest->remove("key1");

    EXPECT_FALSE(dictUnderTest->hasKey("key1"));

}



TEST_F(DictTest_117, LookupNFThrowsOnMissingKey_117) {

    EXPECT_THROW(dictUnderTest->lookupNF("nonexistent"), Exception);

}



TEST_F(DictTest_117, CopyCreatesNewDictWithSameXRef_117) {

    Dict* copiedDict = dictUnderTest->copy(mockXRef);

    EXPECT_EQ(copiedDict->getXRef(), mockXRef);

    delete copiedDict;

}



TEST_F(DictTest_117, DeepCopyCreatesIndependentDict_117) {

    Object obj;

    dictUnderTest->add("key1", std::move(obj));

    Dict* deepCopiedDict = const_cast<Dict*>(dictUnderTest->deepCopy());

    EXPECT_EQ(deepCopiedDict->getLength(), 1);

    deepCopiedDict->remove("key1");

    EXPECT_NE(dictUnderTest->getLength(), deepCopiedDict->getLength());

    delete deepCopiedDict;

}



TEST_F(DictTest_117, SetKeyUpdatesValue_117) {

    Object obj1, obj2;

    dictUnderTest->add("key1", std::move(obj1));

    dictUnderTest->set("key1", std::move(obj2));

    EXPECT_TRUE(dictUnderTest->hasKey("key1"));

}
