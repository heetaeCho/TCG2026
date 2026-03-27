#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/Object.h"

#include "poppler/Dict.h"

#include "poppler/Error.h"



using namespace testing;



// Mocking error function to capture errors

void mockError(ErrorCategory errCategory, int pos, const char *msg) {

    // Capture the error for verification in tests

}



extern "C" void (*original_error)(ErrorCategory, int, const char*);



class DoMergeFormDictTest_2700 : public ::testing::Test {

protected:

    Dict srcFormDict;

    Dict mergeFormDict;



    virtual void SetUp() {

        original_error = error;

        error = mockError;

    }



    virtual void TearDown() {

        error = original_error;

    }

};



TEST_F(DoMergeFormDictTest_2700, NormalOperation_2700) {

    Object srcFieldsArray(new Array());

    srcFormDict.dictAdd("Fields", std::move(srcFieldsArray));



    Object mergeFieldsArray(new Array());

    mergeFieldsArray.getArray()->append(Object(Ref{.num = 1, .gen = 0}));

    mergeFormDict.dictAdd("Fields", std::move(mergeFieldsArray));



    int numOffset = 5;

    bool result = doMergeFormDict(&srcFormDict, &mergeFormDict, numOffset);

    

    ASSERT_TRUE(result);

    const Object& fieldsObj = srcFormDict.lookupNF("Fields");

    ASSERT_TRUE(fieldsObj.isArray());

    EXPECT_EQ(fieldsObj.arrayGetLength(), 1);



    Ref ref = fieldsObj.arrayGetNF(0).getRef();

    EXPECT_EQ(ref.num, 6); // 1 + numOffset

    EXPECT_EQ(ref.gen, 0);

}



TEST_F(DoMergeFormDictTest_2700, EmptyMergeFields_2700) {

    Object srcFieldsArray(new Array());

    srcFormDict.dictAdd("Fields", std::move(srcFieldsArray));



    Object mergeFieldsArray(new Array()); // empty

    mergeFormDict.dictAdd("Fields", std::move(mergeFieldsArray));



    int numOffset = 5;

    bool result = doMergeFormDict(&srcFormDict, &mergeFormDict, numOffset);

    

    ASSERT_TRUE(result);

    const Object& fieldsObj = srcFormDict.lookupNF("Fields");

    ASSERT_TRUE(fieldsObj.isArray());

    EXPECT_EQ(fieldsObj.arrayGetLength(), 0);

}



TEST_F(DoMergeFormDictTest_2700, NonArraySrcFields_2700) {

    srcFormDict.dictAdd("Fields", Object(true));



    Object mergeFieldsArray(new Array());

    mergeFieldsArray.getArray()->append(Object(Ref{.num = 1, .gen = 0}));

    mergeFormDict.dictAdd("Fields", std::move(mergeFieldsArray));



    int numOffset = 5;

    bool result = doMergeFormDict(&srcFormDict, &mergeFormDict, numOffset);

    

    ASSERT_FALSE(result);

}



TEST_F(DoMergeFormDictTest_2700, NonArrayMergeFields_2700) {

    Object srcFieldsArray(new Array());

    srcFormDict.dictAdd("Fields", std::move(srcFieldsArray));



    mergeFormDict.dictAdd("Fields", Object(true));



    int numOffset = 5;

    bool result = doMergeFormDict(&srcFormDict, &mergeFormDict, numOffset);

    

    ASSERT_FALSE(result);

}



TEST_F(DoMergeFormDictTest_2700, NonRefInMergeFields_2700) {

    Object srcFieldsArray(new Array());

    srcFormDict.dictAdd("Fields", std::move(srcFieldsArray));



    Object mergeFieldsArray(new Array());

    mergeFieldsArray.getArray()->append(Object(42)); // non-Ref

    mergeFormDict.dictAdd("Fields", std::move(mergeFieldsArray));



    int numOffset = 5;

    bool result = doMergeFormDict(&srcFormDict, &mergeFormDict, numOffset);

    

    ASSERT_FALSE(result);

}



TEST_F(DoMergeFormDictTest_2700, MultipleRefsInMergeFields_2700) {

    Object srcFieldsArray(new Array());

    srcFormDict.dictAdd("Fields", std::move(srcFieldsArray));



    Object mergeFieldsArray(new Array());

    mergeFieldsArray.getArray()->append(Object(Ref{.num = 1, .gen = 0}));

    mergeFieldsArray.getArray()->append(Object(Ref{.num = 2, .gen = 0}));

    mergeFormDict.dictAdd("Fields", std::move(mergeFieldsArray));



    int numOffset = 5;

    bool result = doMergeFormDict(&srcFormDict, &mergeFormDict, numOffset);

    

    ASSERT_TRUE(result);

    const Object& fieldsObj = srcFormDict.lookupNF("Fields");

    ASSERT_TRUE(fieldsObj.isArray());

    EXPECT_EQ(fieldsObj.arrayGetLength(), 2);



    Ref ref1 = fieldsObj.arrayGetNF(0).getRef();

    EXPECT_EQ(ref1.num, 6); // 1 + numOffset

    EXPECT_EQ(ref1.gen, 0);



    Ref ref2 = fieldsObj.arrayGetNF(1).getRef();

    EXPECT_EQ(ref2.num, 7); // 2 + numOffset

    EXPECT_EQ(ref2.gen, 0);

}
