#include <gtest/gtest.h>

#include "catch2/internal/catch_unique_ptr.hpp"



using Catch::Detail::unique_ptr;



// Test fixture for unique_ptr tests

class UniquePtrTest_26 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if necessary

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



// Normal operation: Check get() returns the pointer

TEST_F(UniquePtrTest_26, GetReturnsPointer_26) {

    int* raw_ptr = new int(42);

    unique_ptr<int> ptr(raw_ptr);

    EXPECT_EQ(ptr.get(), raw_ptr);

}



// Boundary condition: Check get() returns nullptr when unique_ptr is default constructed

TEST_F(UniquePtrTest_26, GetReturnsNullptr_DefaultConstructed_26) {

    unique_ptr<int> ptr;

    EXPECT_EQ(ptr.get(), nullptr);

}



// Normal operation: Check reset() sets the pointer to new value and deletes old one

TEST_F(UniquePtrTest_26, ResetSetsNewPointer_26) {

    int* raw_ptr1 = new int(42);

    unique_ptr<int> ptr(raw_ptr1);

    int* raw_ptr2 = new int(84);

    EXPECT_NE(ptr.get(), raw_ptr2);

    delete raw_ptr2; // prevent memory leak if reset does not delete

    ptr.reset(new int(84));

    EXPECT_EQ(*ptr, 84);

}



// Exceptional case: Check reset() handles nullptr correctly

TEST_F(UniquePtrTest_26, ResetHandlesNullptr_26) {

    unique_ptr<int> ptr(new int(42));

    ptr.reset(nullptr);

    EXPECT_EQ(ptr.get(), nullptr);

}



// Normal operation: Check release() returns the pointer and sets internal pointer to nullptr

TEST_F(UniquePtrTest_26, ReleaseReturnsPointerAndResets_26) {

    int* raw_ptr = new int(42);

    unique_ptr<int> ptr(raw_ptr);

    EXPECT_EQ(ptr.get(), raw_ptr);

    int* released_ptr = ptr.release();

    EXPECT_EQ(released_ptr, raw_ptr);

    EXPECT_EQ(ptr.get(), nullptr);

    delete released_ptr; // clean up manually since ownership has been released

}



// Boundary condition: Check release() on a default constructed unique_ptr returns nullptr

TEST_F(UniquePtrTest_26, ReleaseOnDefaultConstructedReturnsNullptr_26) {

    unique_ptr<int> ptr;

    EXPECT_EQ(ptr.release(), nullptr);

}



// Normal operation: Check operator bool() returns true when pointer is not null

TEST_F(UniquePtrTest_26, BoolOperatorReturnsTrueForNonNull_26) {

    unique_ptr<int> ptr(new int(42));

    EXPECT_TRUE(static_cast<bool>(ptr));

}



// Boundary condition: Check operator bool() returns false when pointer is null

TEST_F(UniquePtrTest_26, BoolOperatorReturnsFalseForNull_26) {

    unique_ptr<int> ptr;

    EXPECT_FALSE(static_cast<bool>(ptr));

}



// Normal operation: Check move constructor transfers ownership

TEST_F(UniquePtrTest_26, MoveConstructorTransfersOwnership_26) {

    unique_ptr<int> ptr1(new int(42));

    unique_ptr<int> ptr2(std::move(ptr1));

    EXPECT_EQ(ptr1.get(), nullptr);

    EXPECT_NE(ptr2.get(), nullptr);

    EXPECT_EQ(*ptr2, 42);

}



// Normal operation: Check move assignment operator transfers ownership

TEST_F(UniquePtrTest_26, MoveAssignmentOperatorTransfersOwnership_26) {

    unique_ptr<int> ptr1(new int(42));

    unique_ptr<int> ptr2;

    ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr1.get(), nullptr);

    EXPECT_NE(ptr2.get(), nullptr);

    EXPECT_EQ(*ptr2, 42);

}



// Boundary condition: Check move assignment from null unique_ptr

TEST_F(UniquePtrTest_26, MoveAssignmentFromNullDoesNothing_26) {

    unique_ptr<int> ptr1;

    unique_ptr<int> ptr2(new int(84));

    ptr2 = std::move(ptr1);

    EXPECT_EQ(ptr1.get(), nullptr);

    EXPECT_NE(ptr2.get(), nullptr);

    EXPECT_EQ(*ptr2, 84);

}



// Boundary condition: Check move assignment to self does nothing

TEST_F(UniquePtrTest_26, MoveAssignmentToSelfDoesNothing_26) {

    unique_ptr<int> ptr(new int(42));

    ptr = std::move(ptr); // NOLINT(bugprone-use-after-move)

    EXPECT_NE(ptr.get(), nullptr);

    EXPECT_EQ(*ptr, 42);

}



// Normal operation: Check operator* and operator-> work correctly

TEST_F(UniquePtrTest_26, OperatorStarAndArrowWorkCorrectly_26) {

    unique_ptr<int> ptr(new int(42));

    *ptr = 84;

    EXPECT_EQ(*ptr, 84);

    EXPECT_EQ(ptr->operator*(), 84);

}



// Boundary condition: Check operator* and operator-> throw on null pointer

TEST_F(UniquePtrTest_26, OperatorStarAndArrowThrowOnNull_26) {

    unique_ptr<int> ptr;

    EXPECT_THROW(*ptr, std::runtime_error); // Assuming dereferencing nullptr throws runtime_error

    EXPECT_THROW(ptr->operator*(), std::runtime_error);

}

```


