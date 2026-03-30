#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Dict.h"

#include "poppler/Object.h"



using namespace testing;



// Test fixture for recursiveMergeDicts function

class RecursiveMergeDictsTest_2028 : public ::testing::Test {

protected:

    Dict* primary;

    const Dict* secondary;



    void SetUp() override {

        primary = new Dict(nullptr);

        secondary = new Dict(nullptr);

    }



    void TearDown() override {

        delete primary;

        delete secondary;

    }

};



// Test for normal operation

TEST_F(RecursiveMergeDictsTest_2028, NormalOperation_2028) {

    // Set up some values in the dictionaries

    Object obj1(Object::makeNull());

    Object obj2(Object::makeInt(42));

    

    primary->add("key1", std::move(obj1));

    secondary->add("key2", std::move(obj2));



    // Perform the merge

    recursiveMergeDicts(primary, secondary);



    // Verify that the keys are present in the merged dictionary

    EXPECT_TRUE(primary->hasKey("key1"));

    EXPECT_TRUE(primary->hasKey("key2"));



    // Verify that the values are correct after the merge

    const Object& value1 = primary->lookupNF("key1");

    const Object& value2 = primary->lookupNF("key2");



    EXPECT_EQ(value1.getType(), objTypeNull);

    EXPECT_EQ(value2.getInt(), 42);

}



// Test for boundary conditions: empty secondary dictionary

TEST_F(RecursiveMergeDictsTest_2028, EmptySecondary_2028) {

    // Set up some values in the primary dictionary

    Object obj1(Object::makeNull());

    primary->add("key1", std::move(obj1));



    // Perform the merge with an empty secondary dictionary

    recursiveMergeDicts(primary, secondary);



    // Verify that only the original key is present

    EXPECT_TRUE(primary->hasKey("key1"));

    EXPECT_FALSE(primary->hasKey("key2"));

}



// Test for boundary conditions: empty primary dictionary

TEST_F(RecursiveMergeDictsTest_2028, EmptyPrimary_2028) {

    // Set up some values in the secondary dictionary

    Object obj1(Object::makeInt(42));

    secondary->add("key2", std::move(obj1));



    // Perform the merge with an empty primary dictionary

    recursiveMergeDicts(primary, secondary);



    // Verify that only the key from the secondary is present

    EXPECT_FALSE(primary->hasKey("key1"));

    EXPECT_TRUE(primary->hasKey("key2"));



    const Object& value2 = primary->lookupNF("key2");

    EXPECT_EQ(value2.getInt(), 42);

}



// Test for boundary conditions: identical keys in both dictionaries

TEST_F(RecursiveMergeDictsTest_2028, IdenticalKeys_2028) {

    // Set up the same key with different values in each dictionary

    Object obj1(Object::makeInt(42));

    Object obj2(Object::makeInt(99));



    primary->add("key1", std::move(obj1));

    secondary->add("key1", std::move(obj2));



    // Perform the merge

    recursiveMergeDicts(primary, secondary);



    // Verify that only the value from the secondary dictionary is present

    const Object& value = primary->lookupNF("key1");

    EXPECT_EQ(value.getInt(), 99);

}



// Test for boundary conditions: very large number of keys in both dictionaries

TEST_F(RecursiveMergeDictsTest_2028, LargeDictionaries_2028) {

    // Add a large number of entries to both dictionaries

    int num_entries = 1000;

    for (int i = 0; i < num_entries; ++i) {

        std::string key1 = "key" + std::to_string(i);

        std::string key2 = "key" + std::to_string(i + num_entries);



        Object obj1(Object::makeInt(i));

        Object obj2(Object::makeInt(i + num_entries));



        primary->add(key1, std::move(obj1));

        secondary->add(key2, std::move(obj2));

    }



    // Perform the merge

    recursiveMergeDicts(primary, secondary);



    // Verify that all keys are present in the merged dictionary

    for (int i = 0; i < num_entries * 2; ++i) {

        std::string key = "key" + std::to_string(i);

        EXPECT_TRUE(primary->hasKey(key));

    }



    // Verify a sample value from each dictionary after merge

    const Object& value1 = primary->lookupNF("key50");

    const Object& value2 = primary->lookupNF("key1050");



    EXPECT_EQ(value1.getInt(), 50);

    EXPECT_EQ(value2.getInt(), 1050);

}
