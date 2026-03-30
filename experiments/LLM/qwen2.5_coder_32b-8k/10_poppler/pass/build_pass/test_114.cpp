#include <gtest/gtest.h>

#include "Dict.h"

#include <string_view>



class DictTest_114 : public ::testing::Test {

protected:

    XRef* mockXRef = nullptr; // Assuming XRef is a dependency that might need mocking

    Dict dict;



    DictTest_114() : dict(mockXRef) {}

};



TEST_F(DictTest_114, GetKey_NormalOperation_114) {

    // Assuming we have some way to populate the dictionary with entries

    dict.add("key1", Object());

    dict.add("key2", Object());



    EXPECT_STREQ(dict.getKey(0), "key1");

    EXPECT_STREQ(dict.getKey(1), "key2");

}



TEST_F(DictTest_114, GetKey_BoundaryConditions_114) {

    // Assuming we have some way to populate the dictionary with entries

    dict.add("key1", Object());



    EXPECT_STREQ(dict.getKey(0), "key1");



    // Out of bounds access should be handled gracefully or throw an exception

    // Here we assume it returns nullptr for out-of-bounds indices

    EXPECT_EQ(dict.getKey(-1), nullptr);

    EXPECT_EQ(dict.getKey(1), nullptr); // Index 1 is out of bounds after adding only one entry

}



TEST_F(DictTest_114, GetKey_ExceptionalCases_114) {

    // Assuming an empty dictionary

    EXPECT_EQ(dict.getKey(0), nullptr); // No entries, should return nullptr for any index

}



TEST_F(DictTest_114, Add_NormalOperation_114) {

    dict.add("key1", Object());

    EXPECT_TRUE(dict.hasKey("key1"));



    dict.add("key2", Object());

    EXPECT_TRUE(dict.hasKey("key2"));

}



TEST_F(DictTest_114, Set_NormalOperation_114) {

    dict.set("key1", Object());

    EXPECT_TRUE(dict.hasKey("key1"));



    dict.set("key1", Object()); // Overwriting existing key

    EXPECT_TRUE(dict.hasKey("key1"));

}



TEST_F(DictTest_114, Remove_NormalOperation_114) {

    dict.add("key1", Object());

    EXPECT_TRUE(dict.hasKey("key1"));



    dict.remove("key1");

    EXPECT_FALSE(dict.hasKey("key1"));

}



TEST_F(DictTest_114, HasKey_NormalOperation_114) {

    dict.add("key1", Object());

    EXPECT_TRUE(dict.hasKey("key1"));



    dict.add("key2", Object());

    EXPECT_TRUE(dict.hasKey("key2"));



    EXPECT_FALSE(dict.hasKey("nonexistent_key"));

}



TEST_F(DictTest_114, GetLength_NormalOperation_114) {

    EXPECT_EQ(dict.getLength(), 0);



    dict.add("key1", Object());

    EXPECT_EQ(dict.getLength(), 1);



    dict.add("key2", Object());

    EXPECT_EQ(dict.getLength(), 2);

}
