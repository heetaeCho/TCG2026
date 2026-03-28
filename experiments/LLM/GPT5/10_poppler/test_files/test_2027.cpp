#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Dict.h"
#include "Object.h"

using ::testing::_;
using ::testing::Return;
using ::testing::AtLeast;

class DictMock : public Dict {
public:
    MOCK_METHOD(bool, hasKey, (std::string_view key), (const, override));
    MOCK_METHOD(void, add, (std::string_view key, Object && val), (override));
    MOCK_METHOD(Object, lookup, (std::string_view key, int recursion), (const, override));
    MOCK_METHOD(int, getLength, (), (const, override));
    MOCK_METHOD(const char *, getKey, (int i), (const, override));
    MOCK_METHOD(Object, getVal, (int i), (const, override));
};

class RecursiveMergeDictsTest : public ::testing::Test {
protected:
    DictMock primaryDict;
    DictMock secondaryDict;
    RefRecursionChecker recursionChecker;
};

// TEST_ID 2027
TEST_F(RecursiveMergeDictsTest, HandlesNormalOperation_2027) {
    // Set up expectations
    EXPECT_CALL(secondaryDict, getLength())
        .WillOnce(Return(1));
    EXPECT_CALL(secondaryDict, getKey(0))
        .WillOnce(Return("key"));
    EXPECT_CALL(secondaryDict, lookup("key", _))
        .WillOnce(Return(Object()));
    EXPECT_CALL(primaryDict, hasKey("key"))
        .WillOnce(Return(false));
    EXPECT_CALL(primaryDict, add("key", _));

    // Call the method under test
    recursiveMergeDicts(&primaryDict, &secondaryDict, &recursionChecker);

    // Verify if the add method was called correctly
    testing::Mock::VerifyAndClearExpectations(&primaryDict);
}

// TEST_ID 2028
TEST_F(RecursiveMergeDictsTest, HandlesRecursiveMerge_2028) {
    // Set up expectations for the recursive call
    EXPECT_CALL(secondaryDict, getLength())
        .WillOnce(Return(1));
    EXPECT_CALL(secondaryDict, getKey(0))
        .WillOnce(Return("key"));
    EXPECT_CALL(secondaryDict, lookup("key", _))
        .WillOnce(Return(Object()));
    EXPECT_CALL(primaryDict, hasKey("key"))
        .WillOnce(Return(true));
    EXPECT_CALL(primaryDict, lookup("key", _))
        .WillOnce(Return(Object()));
    EXPECT_CALL(secondaryDict, lookup("key", _))
        .WillOnce(Return(Object()));

    // Call the method under test
    recursiveMergeDicts(&primaryDict, &secondaryDict, &recursionChecker);

    // Verify that no infinite recursion occurs
    testing::Mock::VerifyAndClearExpectations(&primaryDict);
}

// TEST_ID 2029
TEST_F(RecursiveMergeDictsTest, HandlesNoActionWhenAlreadySeen_2029) {
    // Set up expectations
    EXPECT_CALL(secondaryDict, getLength())
        .WillOnce(Return(1));
    EXPECT_CALL(secondaryDict, getKey(0))
        .WillOnce(Return("key"));
    EXPECT_CALL(secondaryDict, lookup("key", _))
        .WillOnce(Return(Object()));

    // Insert the key into the recursionChecker to simulate already seen refs
    recursionChecker.insert(Ref{1, 1});

    // Set up that the primaryDict already has the key
    EXPECT_CALL(primaryDict, hasKey("key"))
        .WillOnce(Return(true));

    // Call the method under test
    recursiveMergeDicts(&primaryDict, &secondaryDict, &recursionChecker);

    // Ensure no changes were made due to the recursion check
    testing::Mock::VerifyAndClearExpectations(&primaryDict);
}

// TEST_ID 2030
TEST_F(RecursiveMergeDictsTest, HandlesEmptySecondaryDict_2030) {
    // Set up expectations for empty secondary dict
    EXPECT_CALL(secondaryDict, getLength())
        .WillOnce(Return(0));

    // Call the method under test
    recursiveMergeDicts(&primaryDict, &secondaryDict, &recursionChecker);

    // Verify that no changes are made when the secondary dict is empty
    testing::Mock::VerifyAndClearExpectations(&primaryDict);
}

// TEST_ID 2031
TEST_F(RecursiveMergeDictsTest, HandlesMissingKeyInPrimaryDict_2031) {
    // Set up expectations for a missing key in primaryDict
    EXPECT_CALL(secondaryDict, getLength())
        .WillOnce(Return(1));
    EXPECT_CALL(secondaryDict, getKey(0))
        .WillOnce(Return("key"));
    EXPECT_CALL(secondaryDict, lookup("key", _))
        .WillOnce(Return(Object()));

    // Expect that the primaryDict will have the key missing
    EXPECT_CALL(primaryDict, hasKey("key"))
        .WillOnce(Return(false));

    // Expect that add will be called on primaryDict
    EXPECT_CALL(primaryDict, add("key", _));

    // Call the method under test
    recursiveMergeDicts(&primaryDict, &secondaryDict, &recursionChecker);

    // Verify that the add function was called correctly
    testing::Mock::VerifyAndClearExpectations(&primaryDict);
}