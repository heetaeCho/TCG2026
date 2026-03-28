#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/PDFDoc.h"

#include "poppler/XRef.h"

#include "poppler/Dict.h"

#include "poppler/Object.h"



using namespace testing;



// Mocking dependencies that might be passed to doMergeNameDict

class MockXRef : public XRef {

public:

    MOCK_METHOD(void, setModifiedObject, (const Object *o, Ref r), (override));

};



class MockDict : public Dict {

public:

    MOCK_CONST_METHOD1(getLength, int());

    MOCK_CONST_METHOD1(getKey, const char *(int i));

    MOCK_METHOD1(lookup, Object(std::string_view key));

    MOCK_METHOD2(add, void(std::string_view key, Object &&val));

};



class MockObject : public Object {

public:

    MOCK_METHOD0(isDict, bool());

    MOCK_METHOD0(isNull, bool());

    MOCK_CONST_METHOD0(getDict, Dict*());

};



TEST_F(TestFixture_2699, MergeEmptyDicts_2699) {

    MockXRef mockSrcXRef;

    MockXRef mockCountRef;

    MockDict mockSrcNameDict;

    MockDict mockMergeNameDict;



    EXPECT_CALL(mockMergeNameDict, getLength()).WillOnce(Return(0));



    doMergeNameDict(nullptr, &mockSrcXRef, &mockCountRef, 0, 1, &mockSrcNameDict, &mockMergeNameDict, 0);

}



TEST_F(TestFixture_2699, MergeNonEmptyDicts_2699) {

    MockXRef mockSrcXRef;

    MockXRef mockCountRef;

    MockDict mockSrcNameDict;

    MockDict mockMergeNameDict;

    MockObject mockMergeNameTree;

    MockObject mockSrcNameTree;



    EXPECT_CALL(mockMergeNameDict, getLength()).WillOnce(Return(1));

    EXPECT_CALL(mockMergeNameDict, getKey(0)).WillOnce(Return("key1"));

    EXPECT_CALL(mockMergeNameDict, lookup("key1")).WillOnce(ReturnRef(mockMergeNameTree));



    EXPECT_CALL(mockSrcNameDict, lookup("key1")).WillOnce(ReturnRef(mockSrcNameTree));

    EXPECT_CALL(mockSrcNameTree, isDict()).WillOnce(Return(true));

    EXPECT_CALL(mockMockSrcNameTree, getDict()).WillOnce(Return(&mockSrcNameDict));



    EXPECT_CALL(mockMergeNameTree, isDict()).WillOnce(Return(true));

    EXPECT_CALL(mockMergeNameTree, getDict()).WillOnce(Return(&mockMergeNameDict));



    doMergeNameDict(nullptr, &mockSrcXRef, &mockCountRef, 0, 1, &mockSrcNameDict, &mockMergeNameDict, 0);

}



TEST_F(TestFixture_2699, MergeWithNullSourceEntry_2699) {

    MockXRef mockSrcXRef;

    MockXRef mockCountRef;

    MockDict mockSrcNameDict;

    MockDict mockMergeNameDict;

    MockObject mockMergeNameTree;



    EXPECT_CALL(mockMergeNameDict, getLength()).WillOnce(Return(1));

    EXPECT_CALL(mockMergeNameDict, getKey(0)).WillOnce(Return("key1"));

    EXPECT_CALL(mockMergeNameDict, lookup("key1")).WillOnce(ReturnRef(mockMergeNameTree));



    EXPECT_CALL(mockSrcNameDict, lookup("key1")).WillOnce(Return(Object()));

    EXPECT_CALL(mockObject, isNull()).WillOnce(Return(true));

    

    EXPECT_CALL(mockObject, isDict()).WillOnce(Return(true));

    EXPECT_CALL(mockMockObject, getDict()).WillOnce(Return(&mockMergeNameDict));



    doMergeNameDict(nullptr, &mockSrcXRef, &mockCountRef, 0, 1, &mockSrcNameDict, &mockMergeNameDict, 0);

}



TEST_F(TestFixture_2699, MergeWithNonDictSourceEntry_2699) {

    MockXRef mockSrcXRef;

    MockXRef mockCountRef;

    MockDict mockSrcNameDict;

    MockDict mockMergeNameDict;

    MockObject mockMergeNameTree;



    EXPECT_CALL(mockMergeNameDict, getLength()).WillOnce(Return(1));

    EXPECT_CALL(mockMergeNameDict, getKey(0)).WillOnce(Return("key1"));

    EXPECT_CALL(mockMergeNameDict, lookup("key1")).WillOnce(ReturnRef(mockMergeNameTree));



    EXPECT_CALL(mockSrcNameDict, lookup("key1")).WillOnce(Return(Object()));

    EXPECT_CALL(mockObject, isNull()).WillOnce(Return(false));

    EXPECT_CALL(mockObject, isDict()).WillOnce(Return(false));



    doMergeNameDict(nullptr, &mockSrcXRef, &mockCountRef, 0, 1, &mockSrcNameDict, &mockMergeNameDict, 0);

}
