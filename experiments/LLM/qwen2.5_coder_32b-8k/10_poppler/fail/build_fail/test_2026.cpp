#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/Object.h"

#include "./TestProjects/poppler/poppler/Dict.h"

#include "./TestProjects/poppler/poppler/XRef.h"



using namespace ::testing;



class SetChildDictEntryValueTest : public Test {

protected:

    XRef xref;

    Dict parentDict{&xref};

};



TEST_F(SetChildDictEntryValueTest, NormalOperation_2026) {

    const char* childDictName = "childDict";

    const char* childDictEntryName = "entryName";

    Ref childDictEntryValue{1, 0};



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName, childDictEntryValue, &xref);



    Object childDictObj = parentDict.lookup(childDictName);

    ASSERT_TRUE(childDictObj.isDict());



    Dict* childDict = childDictObj.getDict();

    Object entryValue = childDict->lookup(childDictEntryName);

    EXPECT_EQ(entryValue.getRef(), childDictEntryValue);

}



TEST_F(SetChildDictEntryValueTest, ChildDictAlreadyExists_2026) {

    const char* childDictName = "childDict";

    const char* childDictEntryName1 = "entryName1";

    Ref childDictEntryValue1{1, 0};



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName1, childDictEntryValue1, &xref);



    Object childDictObj = parentDict.lookup(childDictName);

    ASSERT_TRUE(childDictObj.isDict());



    Dict* childDict = childDictObj.getDict();

    const char* childDictEntryName2 = "entryName2";

    Ref childDictEntryValue2{2, 0};



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName2, childDictEntryValue2, &xref);



    Object entryValue1 = childDict->lookup(childDictEntryName1);

    EXPECT_EQ(entryValue1.getRef(), childDictEntryValue1);



    Object entryValue2 = childDict->lookup(childDictEntryName2);

    EXPECT_EQ(entryValue2.getRef(), childDictEntryValue2);

}



TEST_F(SetChildDictEntryValueTest, ChildDictDoesNotExist_2026) {

    const char* childDictName = "childDict";

    const char* childDictEntryName = "entryName";

    Ref childDictEntryValue{1, 0};



    Object initialLookup = parentDict.lookup(childDictName);

    EXPECT_FALSE(initialLookup.isDict());



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName, childDictEntryValue, &xref);



    Object finalLookup = parentDict.lookup(childDictName);

    ASSERT_TRUE(finalLookup.isDict());

}



TEST_F(SetChildDictEntryValueTest, BoundaryCondition_EmptyStrings_2026) {

    const char* childDictName = "";

    const char* childDictEntryName = "";

    Ref childDictEntryValue{1, 0};



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName, childDictEntryValue, &xref);



    Object childDictObj = parentDict.lookup(childDictName);

    ASSERT_TRUE(childDictObj.isDict());



    Dict* childDict = childDictObj.getDict();

    Object entryValue = childDict->lookup(childDictEntryName);

    EXPECT_EQ(entryValue.getRef(), childDictEntryValue);

}



TEST_F(SetChildDictEntryValueTest, BoundaryCondition_MaxIntegers_2026) {

    const char* childDictName = "childDict";

    const char* childDictEntryName = "entryName";

    Ref childDictEntryValue{std::numeric_limits<int>::max(), std::numeric_limits<int>::max()};



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName, childDictEntryValue, &xref);



    Object childDictObj = parentDict.lookup(childDictName);

    ASSERT_TRUE(childDictObj.isDict());



    Dict* childDict = childDictObj.getDict();

    Object entryValue = childDict->lookup(childDictEntryName);

    EXPECT_EQ(entryValue.getRef(), childDictEntryValue);

}



TEST_F(SetChildDictEntryValueTest, BoundaryCondition_MinIntegers_2026) {

    const char* childDictName = "childDict";

    const char* childDictEntryName = "entryName";

    Ref childDictEntryValue{std::numeric_limits<int>::min(), std::numeric_limits<int>::min()};



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName, childDictEntryValue, &xref);



    Object childDictObj = parentDict.lookup(childDictName);

    ASSERT_TRUE(childDictObj.isDict());



    Dict* childDict = childDictObj.getDict();

    Object entryValue = childDict->lookup(childDictEntryName);

    EXPECT_EQ(entryValue.getRef(), childDictEntryValue);

}



TEST_F(SetChildDictEntryValueTest, ExceptionalCase_InvalidRef_2026) {

    const char* childDictName = "childDict";

    const char* childDictEntryName = "entryName";

    Ref childDictEntryValue{Ref::INVALID()};



    setChildDictEntryValue(&parentDict, childDictName, childDictEntryName, childDictEntryValue, &xref);



    Object childDictObj = parentDict.lookup(childDictName);

    ASSERT_TRUE(childDictObj.isDict());



    Dict* childDict = childDictObj.getDict();

    Object entryValue = childDict->lookup(childDictEntryName);

    EXPECT_EQ(entryValue.getRef(), childDictEntryValue);

}
