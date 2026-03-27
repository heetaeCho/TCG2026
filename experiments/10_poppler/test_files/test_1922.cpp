#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "XRef.h"

#include "Object.h"



using namespace testing;



class RecursiveRemoveListTest : public ::testing::Test {

protected:

    std::unique_ptr<XRef> xref;

    Ref ref;



    void SetUp() override {

        xref = std::make_unique<XRef>();

        ref = Ref{1, 0};

    }

};



TEST_F(RecursiveRemoveListTest_NormalOperation_1922, SingleDictEntryRemoved_1922) {

    // Arrange

    Object dictObj(new Dict);

    EXPECT_CALL(*xref.get(), fetch(ref)).WillOnce(Return(dictObj));



    // Act

    int count = recursiveRemoveList(ref, xref.get());



    // Assert

    ASSERT_EQ(count, 1);

}



TEST_F(RecursiveRemoveListTest_NormalOperation_1922, NestedDictEntriesRemoved_1922) {

    // Arrange

    Ref nestedRef{2, 0};

    Object dictObj(new Dict);

    dictObj.dictAdd("First", Object(nestedRef));

    Object nestedDictObj(new Dict);

    EXPECT_CALL(*xref.get(), fetch(ref)).WillOnce(Return(dictObj));

    EXPECT_CALL(*xref.get(), fetch(nestedRef)).WillOnce(Return(nestedDictObj));



    // Act

    int count = recursiveRemoveList(ref, xref.get());



    // Assert

    ASSERT_EQ(count, 2);

}



TEST_F(RecursiveRemoveListTest_NormalOperation_1922, MultipleSiblingsRemoved_1922) {

    // Arrange

    Ref siblingRef{3, 0};

    Object dictObj(new Dict);

    dictObj.dictAdd("Next", Object(siblingRef));

    Object siblingDictObj(new Dict);

    EXPECT_CALL(*xref.get(), fetch(ref)).WillOnce(Return(dictObj));

    EXPECT_CALL(*xref.get(), fetch(siblingRef)).WillOnce(Return(siblingDictObj));



    // Act

    int count = recursiveRemoveList(ref, xref.get());



    // Assert

    ASSERT_EQ(count, 2);

}



TEST_F(RecursiveRemoveListTest_NormalOperation_1922, NestedAndSiblingsRemoved_1922) {

    // Arrange

    Ref nestedRef{4, 0};

    Ref siblingRef{5, 0};

    Object dictObj(new Dict);

    dictObj.dictAdd("First", Object(nestedRef));

    dictObj.dictAdd("Next", Object(siblingRef));

    Object nestedDictObj(new Dict);

    Object siblingDictObj(new Dict);

    EXPECT_CALL(*xref.get(), fetch(ref)).WillOnce(Return(dictObj));

    EXPECT_CALL(*xref.get(), fetch(nestedRef)).WillOnce(Return(nestedDictObj));

    EXPECT_CALL(*xref.get(), fetch(siblingRef)).WillOnce(Return(siblingDictObj));



    // Act

    int count = recursiveRemoveList(ref, xref.get());



    // Assert

    ASSERT_EQ(count, 3);

}



TEST_F(RecursiveRemoveListTest_BoundaryConditions_1922, EmptyDictRemoved_1922) {

    // Arrange

    Object dictObj(new Dict);

    EXPECT_CALL(*xref.get(), fetch(ref)).WillOnce(Return(dictObj));



    // Act

    int count = recursiveRemoveList(ref, xref.get());



    // Assert

    ASSERT_EQ(count, 1);

}



TEST_F(RecursiveRemoveListTest_BoundaryConditions_1922, NonDictObjectRemoved_1922) {

    // Arrange

    Object nonDictObj(Object::null());

    EXPECT_CALL(*xref.get(), fetch(ref)).WillOnce(Return(nonDictObj));



    // Act

    int count = recursiveRemoveList(ref, xref.get());



    // Assert

    ASSERT_EQ(count, 0);

}



TEST_F(RecursiveRemoveListTest_ExceptionalCases_1922, InvalidRefHandling_1922) {

    // Arrange

    Ref invalidRef = Ref::INVALID();

    Object dictObj(new Dict);

    EXPECT_CALL(*xref.get(), fetch(invalidRef)).WillOnce(Return(dictObj));



    // Act & Assert

    int count = recursiveRemoveList(invalidRef, xref.get());

    ASSERT_EQ(count, 0);

}
