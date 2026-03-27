#include <gtest/gtest.h>

#include "Dict.h"

#include "Object.h"



using namespace std;



// Mocking parseNumericName for testing purposes since it's not part of provided interface.

extern bool parseNumericName(const char* name, bool hex, void* unused);



class GfxFontTest_1969 : public ::testing::Test {

protected:

    Dict fontDict;

};



TEST_F(GfxFontTest_1969, NoEncodingEntry_1969) {

    EXPECT_FALSE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, EncodingNotADict_1969) {

    Object nonDictObj(42);

    fontDict.dictAdd("Encoding", std::move(nonDictObj));



    EXPECT_FALSE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesNotAnArray_1969) {

    Dict encodingDict;

    Object nonArrayObj(42);

    encodingDict.dictAdd("Differences", std::move(nonArrayObj));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_FALSE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, EmptyDifferencesArray_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_TRUE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesArrayWithIntegersLessThan5_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    diffArray.arrayAdd(0);

    diffArray.arrayAdd(3);

    diffArray.arrayAdd(4);



    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_TRUE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesArrayWithIntegerGreaterThan5_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    diffArray.arrayAdd(0);

    diffArray.arrayAdd(3);

    diffArray.arrayAdd(5);  // This will make it false as per the condition.



    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_FALSE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesArrayWithValidName_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    Object nameObj(Object::nameA, "n0");

    

    EXPECT_CALL(::testing::MockFunction<bool(const char*, bool, void*)>(), Call("n0", false, nullptr)).WillOnce(::testing::Return(true));



    diffArray.arrayAdd(std::move(nameObj));

    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_TRUE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesArrayWithInvalidName_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    Object nameObj(Object::nameA, "n0");



    EXPECT_CALL(::testing::MockFunction<bool(const char*, bool, void*)>(), Call("n0", false, nullptr)).WillOnce(::testing::Return(false));



    diffArray.arrayAdd(std::move(nameObj));

    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_FALSE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesArrayMixedTypes_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    diffArray.arrayAdd(0);  // int

    diffArray.arrayAdd("n2"); // name



    EXPECT_CALL(::testing::MockFunction<bool(const char*, bool, void*)>(), Call("n2", false, nullptr)).WillOnce(::testing::Return(true));



    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_TRUE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesArrayWithNonNameAndIntegers_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    diffArray.arrayAdd(0);  // int

    diffArray.arrayAdd("n2"); // name

    diffArray.arrayAdd(5);  // This will make it false as per the condition.



    EXPECT_CALL(::testing::MockFunction<bool(const char*, bool, void*)>(), Call("n2", false, nullptr)).WillOnce(::testing::Return(true));



    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_FALSE(testForNumericNames(&fontDict, false));

}



TEST_F(GfxFontTest_1969, DifferencesArrayWithNonNameAndInvalidName_1969) {

    Dict encodingDict;

    Object diffArray(Object::arrayA);

    diffArray.arrayAdd(0);  // int

    diffArray.arrayAdd("n2"); // name



    EXPECT_CALL(::testing::MockFunction<bool(const char*, bool, void*)>(), Call("n2", false, nullptr)).WillOnce(::testing::Return(false));



    encodingDict.dictAdd("Differences", std::move(diffArray));



    fontDict.dictAdd("Encoding", std::move(encodingDict));



    EXPECT_FALSE(testForNumericNames(&fontDict, false));

}
