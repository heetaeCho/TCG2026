#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/tags_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Print0x0213Test_1393 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Print0x0213Test_1393, NormalOperationWithValidTag_1393) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("Centered"));

    print0x0213(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Centered");

}



TEST_F(Print0x0213Test_1393, NormalOperationWithAnotherValidTag_1393) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("Co-sited"));

    print0x0213(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "Co-sited");

}



TEST_F(Print0x0213Test_1393, BoundaryConditionWithEmptyString_1393) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return(""));

    print0x0213(os, mockValue, &mockMetadata);

    EXPECT_EQ(os.str(), "");

}



TEST_F(Print0x0213Test_1393, ExceptionalCaseWithNullMetadata_1393) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString()).WillOnce(::testing::Return("Centered"));

    print0x0213(os, mockValue, nullptr);

    EXPECT_EQ(os.str(), "Centered");

}



TEST_F(Print0x0213Test_1393, VerificationOfExternalInteraction_1393) {

    std::ostringstream os;

    EXPECT_CALL(mockValue, toString()).Times(1);

    print0x0213(os, mockValue, &mockMetadata);

}
