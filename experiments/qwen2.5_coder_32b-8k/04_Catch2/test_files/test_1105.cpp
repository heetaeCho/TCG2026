#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"



using namespace Catch::Benchmark::Detail;



class ObjectStorageTest : public ::testing::Test {

protected:

    using TestType = int;

    ObjectStorage<TestType, true> storageWithDestruct;

    ObjectStorage<TestType, false> storageWithoutDestruct;

};



TEST_F(ObjectStorageTest_1105, ConstructObject_1105) {

    storageWithDestruct.construct(42);

    // Assuming stored_object() can be used to verify the constructed value

    EXPECT_EQ(storageWithDestruct.stored_object(), 42);



    storageWithoutDestruct.construct(99);

    EXPECT_EQ(storageWithoutDestruct.stored_object(), 99);

}



TEST_F(ObjectStorageTest_1105, DestructObjectWithDestructFlagTrue_1105) {

    storageWithDestruct.construct(42);

    storageWithDestruct.destruct();

    // Assuming stored_object() will be in an invalid state after destruction

    // This is a bit tricky to verify without more context, but we can assume it throws or has some side effect

}



TEST_F(ObjectStorageTest_1105, DestructObjectWithDestructFlagFalse_1105) {

    storageWithoutDestruct.construct(99);

    storageWithoutDestruct.destruct();

    // No-op for !Destruct case, so no change in stored_object()

    EXPECT_EQ(storageWithoutDestruct.stored_object(), 99);

}



TEST_F(ObjectStorageTest_1105, CopyConstructorWithDestructFlagTrue_1105) {

    storageWithDestruct.construct(42);

    ObjectStorage<TestType, true> copy = storageWithDestruct;

    EXPECT_EQ(copy.stored_object(), 42);

}



TEST_F(ObjectStorageTest_1105, MoveConstructorWithDestructFlagTrue_1105) {

    storageWithDestruct.construct(42);

    ObjectStorage<TestType, true> moved = std::move(storageWithDestruct);

    EXPECT_EQ(moved.stored_object(), 42);

}



TEST_F(ObjectStorageTest_1105, CopyConstructorWithDestructFlagFalse_1105) {

    storageWithoutDestruct.construct(99);

    ObjectStorage<TestType, false> copy = storageWithoutDestruct;

    EXPECT_EQ(copy.stored_object(), 99);

}



TEST_F(ObjectStorageTest_1105, MoveConstructorWithDestructFlagFalse_1105) {

    storageWithoutDestruct.construct(99);

    ObjectStorage<TestType, false> moved = std::move(storageWithoutDestruct);

    EXPECT_EQ(moved.stored_object(), 99);

}
