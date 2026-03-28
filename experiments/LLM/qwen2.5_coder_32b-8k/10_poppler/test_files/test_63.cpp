#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/poppler/poppler/Object.h"



using namespace std;

using namespace testing;



class RefTest : public ::testing::Test {

protected:

    Ref ref1;

    Ref ref2;

    

    void SetUp() override {

        ref1 = {42, 0};

        ref2 = {63, 1};

    }

};



TEST_F(RefTest_63, InvalidRefHasZeroValues_63) {

    Ref invalidRef = Ref::INVALID();

    EXPECT_EQ(invalidRef.num, 0);

    EXPECT_EQ(invalidRef.gen, 0);

}



TEST_F(RefTest_63, HashFunctionProducesDifferentHashesForDifferentRefs_63) {

    std::hash<Ref> hashFunc;

    EXPECT_NE(hashFunc(ref1), hashFunc(ref2));

}



TEST_F(RefTest_63, HashFunctionProducesSameHashForSameRefs_63) {

    std::hash<Ref> hashFunc;

    Ref refCopy = {42, 0};

    EXPECT_EQ(hashFunc(ref1), hashFunc(refCopy));

}



TEST_F(RefTest_63, HashFunctionHandlesZeroValuesProperly_63) {

    std::hash<Ref> hashFunc;

    Ref zeroRef = {0, 0};

    EXPECT_EQ(hashFunc(zeroRef), hashFunc(Ref::INVALID()));

}
