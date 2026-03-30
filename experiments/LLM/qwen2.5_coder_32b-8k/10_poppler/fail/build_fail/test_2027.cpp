#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"

#include "Dict.h"

#include "RefRecursionChecker.h"



using namespace testing;



class RecursiveMergeDictsTest : public ::testing::Test {

protected:

    std::unique_ptr<Dict> primaryDict;

    std::unique_ptr<Dict> secondaryDict;

    std::unique_ptr<RefRecursionChecker> refRecursionChecker;



    void SetUp() override {

        primaryDict = std::make_unique<Dict>(nullptr);

        secondaryDict = std::make_unique<Dict>(nullptr);

        refRecursionChecker = std::make_unique<RefRecursionChecker>();

    }



    Object createDictObject(Dict* dict) {

        return Object(dict);

    }

};



TEST_F(RecursiveMergeDictsTest_2027, MergeWithNoCommonKeys_2027) {

    secondaryDict->add("key1", Object("value1"));

    secondaryDict->add("key2", Object("value2"));



    recursiveMergeDicts(primaryDict.get(), secondaryDict.get(), refRecursionChecker.get());



    EXPECT_TRUE(primaryDict->hasKey("key1"));

    EXPECT_TRUE(primaryDict->hasKey("key2"));

    EXPECT_EQ(primaryDict->lookupNF("key1").getString()->getCString(), "value1");

    EXPECT_EQ(primaryDict->lookupNF("key2").getString()->getCString(), "value2");

}



TEST_F(RecursiveMergeDictsTest_2027, MergeWithCommonNonDictKeys_2027) {

    primaryDict->add("key1", Object("primaryValue"));

    secondaryDict->add("key1", Object("secondaryValue"));



    recursiveMergeDicts(primaryDict.get(), secondaryDict.get(), refRecursionChecker.get());



    EXPECT_TRUE(primaryDict->hasKey("key1"));

    EXPECT_EQ(primaryDict->lookupNF("key1").getString()->getCString(), "primaryValue");

}



TEST_F(RecursiveMergeDictsTest_2027, MergeWithCommonDictKeys_2027) {

    auto nestedPrimaryDict = std::make_unique<Dict>(nullptr);

    primaryDict->add("nestedKey", createDictObject(nestedPrimaryDict.get()));

    nestedPrimaryDict.release();



    auto nestedSecondaryDict = std::make_unique<Dict>(nullptr);

    nestedSecondaryDict->add("subKey1", Object("value1"));

    secondaryDict->add("nestedKey", createDictObject(nestedSecondaryDict.get()));

    nestedSecondaryDict.release();



    recursiveMergeDicts(primaryDict.get(), secondaryDict.get(), refRecursionChecker.get());



    EXPECT_TRUE(primaryDict->hasKey("nestedKey"));

    const auto& nestedDict = primaryDict->lookupNF("nestedKey").getDict();

    EXPECT_TRUE(nestedDict->hasKey("subKey1"));

    EXPECT_EQ(nestedDict->lookupNF("subKey1").getString()->getCString(), "value1");

}



TEST_F(RecursiveMergeDictsTest_2027, MergeWithNestedCommonDictKeys_2027) {

    auto nestedPrimaryDict = std::make_unique<Dict>(nullptr);

    primaryDict->add("nestedKey", createDictObject(nestedPrimaryDict.get()));



    auto subNestedPrimaryDict = std::make_unique<Dict>(nullptr);

    nestedPrimaryDict->add("subNestedKey", createDictObject(subNestedPrimaryDict.get()));

    nestedPrimaryDict.release();

    subNestedPrimaryDict.release();



    auto nestedSecondaryDict = std::make_unique<Dict>(nullptr);

    nestedSecondaryDict->add("subNestedKey", Object("value1"));

    secondaryDict->add("nestedKey", createDictObject(nestedSecondaryDict.get()));

    nestedSecondaryDict.release();



    recursiveMergeDicts(primaryDict.get(), secondaryDict.get(), refRecursionChecker.get());



    EXPECT_TRUE(primaryDict->hasKey("nestedKey"));

    const auto& nestedDict = primaryDict->lookupNF("nestedKey").getDict();

    EXPECT_TRUE(nestedDict->hasKey("subNestedKey"));

    EXPECT_EQ(nestedDict->lookupNF("subNestedKey").getString()->getCString(), "value1");

}



TEST_F(RecursiveMergeDictsTest_2027, MergeWithRecursion_2027) {

    auto nestedPrimaryDict = std::make_unique<Dict>(nullptr);

    primaryDict->add("nestedKey", createDictObject(nestedPrimaryDict.get()));



    Ref ref1{1, 1};

    Ref ref2{1, 1};

    EXPECT_CALL(*refRecursionChecker, insert(Ref{1, 1})).WillOnce(Return(true)).WillOnce(Return(false));



    Object nestedDictObj = createDictObject(nestedPrimaryDict.get());

    ON_CALL(*nestedDictObj.getDict(), lookup("subNestedKey", _)).WillByDefault(Return(Object()));

    secondaryDict->add("nestedKey", nestedDictObj);

    nestedPrimaryDict.release();



    recursiveMergeDicts(primaryDict.get(), secondaryDict.get(), refRecursionChecker.get());



    EXPECT_TRUE(primaryDict->hasKey("nestedKey"));

}



TEST_F(RecursiveMergeDictsTest_2027, MergeWithNoSecondaryKeys_2027) {

    primaryDict->add("key1", Object("value1"));



    recursiveMergeDicts(primaryDict.get(), secondaryDict.get(), refRecursionChecker.get());



    EXPECT_TRUE(primaryDict->hasKey("key1"));

    EXPECT_EQ(primaryDict->lookupNF("key1").getString()->getCString(), "value1");

}
