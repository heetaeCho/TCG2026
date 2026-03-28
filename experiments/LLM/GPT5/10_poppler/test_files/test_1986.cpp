#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/FileSpec.h"
#include "./TestProjects/poppler/poppler/Object.h"

// Mock class for Object to simulate interactions
class MockObject : public Object {
public:
    MOCK_METHOD(bool, isString, (), (const));
    MOCK_METHOD(bool, isDict, (), (const));
    MOCK_METHOD(Object, dictLookup, (std::string_view key), (const));
};

// Test suite for `getFileSpecName` function
TEST_F(FileSpecTest_1986, GetFileSpecName_ReturnsFileName_WhenStringIsPassed_1986) {
    MockObject fileSpec;
    EXPECT_CALL(fileSpec, isString()).WillOnce(testing::Return(true));

    // Simulate the behavior of returning a copy of the string
    Object expected("TestFileName");
    EXPECT_CALL(fileSpec, copy()).WillOnce(testing::Return(expected));

    Object result = getFileSpecName(&fileSpec);
    EXPECT_EQ(result.getString()->getCString(), "TestFileName");
}

TEST_F(FileSpecTest_1986, GetFileSpecName_ReturnsFirstValidFileNameFromDict_1986) {
    MockObject fileSpec;
    EXPECT_CALL(fileSpec, isString()).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict()).WillOnce(testing::Return(true));

    // Simulate the dict lookup process
    Object fileName1("FirstFileName");
    Object fileName2("SecondFileName");
    
    EXPECT_CALL(fileSpec, dictLookup("UF")).WillOnce(testing::Return(fileName1));
    EXPECT_CALL(fileSpec, dictLookup("F")).WillOnce(testing::Return(fileName2)); // Will be ignored since UF returns a value

    Object result = getFileSpecName(&fileSpec);
    EXPECT_EQ(result.getString()->getCString(), "FirstFileName");
}

TEST_F(FileSpecTest_1986, GetFileSpecName_ReturnsEmptyObject_WhenNoValidFileNameFound_1986) {
    MockObject fileSpec;
    EXPECT_CALL(fileSpec, isString()).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict()).WillOnce(testing::Return(true));

    // Simulate the absence of valid file names
    Object emptyObject;
    EXPECT_CALL(fileSpec, dictLookup("UF")).WillOnce(testing::Return(emptyObject));
    EXPECT_CALL(fileSpec, dictLookup("F")).WillOnce(testing::Return(emptyObject));
    EXPECT_CALL(fileSpec, dictLookup("DOS")).WillOnce(testing::Return(emptyObject));
    EXPECT_CALL(fileSpec, dictLookup("Mac")).WillOnce(testing::Return(emptyObject));
    EXPECT_CALL(fileSpec, dictLookup("Unix")).WillOnce(testing::Return(emptyObject));

    Object result = getFileSpecName(&fileSpec);
    EXPECT_TRUE(result.isNull());
}

TEST_F(FileSpecTest_1986, GetFileSpecName_HandlesMissingFileSpec_1986) {
    MockObject* fileSpec = nullptr;
    Object result = getFileSpecName(fileSpec);
    EXPECT_TRUE(result.isNull());  // Assuming this case returns a null Object for missing input
}

// Boundary test for Object type
TEST_F(FileSpecTest_1986, GetFileSpecName_HandlesEdgeCasesWithDifferentObjectTypes_1986) {
    MockObject fileSpec;
    EXPECT_CALL(fileSpec, isString()).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict()).WillOnce(testing::Return(true));

    // Case with an empty dict
    Object emptyObject;
    EXPECT_CALL(fileSpec, dictLookup("UF")).WillOnce(testing::Return(emptyObject));

    Object result = getFileSpecName(&fileSpec);
    EXPECT_TRUE(result.isNull());
}