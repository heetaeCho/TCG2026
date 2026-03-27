#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/Dict.h"



using namespace testing;



class DictTest_113 : public ::testing::Test {

protected:

    XRef* mockXRef;

    Dict* dict;



    void SetUp() override {

        mockXRef = new XRef();

        dict = new Dict(mockXRef);

    }



    void TearDown() override {

        delete dict;

        delete mockXRef;

    }

};



TEST_F(DictTest_113, GetLength_ReturnsZeroForEmptyDict_113) {

    EXPECT_EQ(dict->getLength(), 0);

}



TEST_F(DictTest_113, Add_IncreasesLengthByOne_113) {

    dict->add("key", Object());

    EXPECT_EQ(dict->getLength(), 1);

}



TEST_F(DictTest_113, Set_DoesNotIncreaseLengthIfKeyExists_113) {

    dict->set("key", Object());

    dict->set("key", Object());

    EXPECT_EQ(dict->getLength(), 1);

}



TEST_F(DictTest_113, Remove_DecreasesLengthByOne_113) {

    dict->add("key", Object());

    dict->remove("key");

    EXPECT_EQ(dict->getLength(), 0);

}



TEST_F(DictTest_113, HasKey_ReturnsTrueForExistingKey_113) {

    dict->add("key", Object());

    EXPECT_TRUE(dict->hasKey("key"));

}



TEST_F(DictTest_113, HasKey_ReturnsFalseForNonexistentKey_113) {

    EXPECT_FALSE(dict->hasKey("nonexistent_key"));

}



TEST_F(DictTest_113, LookupNF_ReturnsDefaultConstructedObjectForNonexistentKey_113) {

    Object defaultObj;

    EXPECT_EQ(dict->lookupNF("key"), defaultObj);

}



TEST_F(DictTest_113, FindAvailableKey_ReturnsSuggestedKeyIfNotUsed_113) {

    std::string suggestedKey = "suggested_key";

    EXPECT_EQ(dict->findAvailableKey(suggestedKey), suggestedKey);

}



TEST_F(DictTest_113, Copy_ReturnsNewDictWithSameEntries_113) {

    dict->add("key", Object());

    const Dict* copiedDict = dict->copy(mockXRef);

    EXPECT_NE(copiedDict, dict);

    EXPECT_EQ(copiedDict->getLength(), dict->getLength());

    delete copiedDict;

}



TEST_F(DictTest_113, DeepCopy_ReturnsNewDictWithSameEntries_113) {

    dict->add("key", Object());

    const Dict* deepCopiedDict = dict->deepCopy();

    EXPECT_NE(deepCopiedDict, dict);

    EXPECT_EQ(deepCopiedDict->getLength(), dict->getLength());

    delete deepCopiedDict;

}
