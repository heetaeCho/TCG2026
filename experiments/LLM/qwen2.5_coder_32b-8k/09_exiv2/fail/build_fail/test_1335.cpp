#include <gtest/gtest.h>

#include "exiv2/tags.hpp"



namespace Exiv2 {

    class ExifKey;

}



using namespace Exiv2;



class ExifKeyTest_1335 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if needed

    }



    void TearDown() override {

        // Teardown code, if needed

    }

};



TEST_F(ExifKeyTest_1335, SetIdxSetsIndex_1335) {

    ExifKey key("some_key");

    key.setIdx(42);

    EXPECT_EQ(key.idx(), 42);

}



TEST_F(ExifKeyTest_1335, DefaultConstructorInitializesIndexToZero_1335) {

    ExifKey key;

    EXPECT_EQ(key.idx(), 0);

}



TEST_F(ExifKeyTest_1335, CopyConstructorPreservesIndex_1335) {

    ExifKey original("some_key");

    original.setIdx(42);

    ExifKey copy(original);

    EXPECT_EQ(copy.idx(), 42);

}



TEST_F(ExifKeyTest_1335, AssignmentOperatorCopiesIndex_1335) {

    ExifKey original("some_key");

    original.setIdx(42);

    ExifKey target;

    target = original;

    EXPECT_EQ(target.idx(), 42);

}



TEST_F(ExifKeyTest_1335, BoundaryConditionSetIdxWithNegativeIndex_1335) {

    ExifKey key("some_key");

    key.setIdx(-1);

    EXPECT_EQ(key.idx(), -1);

}



TEST_F(ExifKeyTest_1335, BoundaryConditionSetIdxWithLargePositiveIndex_1335) {

    ExifKey key("some_key");

    key.setIdx(std::numeric_limits<int>::max());

    EXPECT_EQ(key.idx(), std::numeric_limits<int>::max());

}
