#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



namespace {



class SonyMakerNoteTests : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;

    std::ostringstream os;



    SonyMakerNoteTests() : value(unsignedLong) {}

};



TEST_F(SonyMakerNoteTests_1619, NormalOperationWithKnownModel_1619) {

    value.setInt64(123);

    std::string model = "ILCE-7";

    EXPECT_CALL(*this, getModel(&metadata, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(model), testing::Return(true)));



    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, &metadata);

    EXPECT_EQ("123", os.str());

}



TEST_F(SonyMakerNoteTests_1619, NormalOperationWithUnknownModel_1619) {

    value.setInt64(123);

    std::string model = "UNKNOWN_MODEL";

    EXPECT_CALL(*this, getModel(&metadata, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(model), testing::Return(true)));



    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, &metadata);

    EXPECT_EQ("n/a", os.str());

}



TEST_F(SonyMakerNoteTests_1619, ValueCountNotOne_1619) {

    value.setInt64(123);

    value.ok_ = true;

    metadata.clear();



    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, &metadata);

    EXPECT_EQ("(0)", os.str());

}



TEST_F(SonyMakerNoteTests_1619, InvalidTypeId_1619) {

    Value invalidValue(unsignedShort); // Using unsignedShort instead of unsignedLong

    invalidValue.setInt64(123);

    metadata.clear();



    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, invalidValue, &metadata);

    EXPECT_EQ("(0)", os.str());

}



TEST_F(SonyMakerNoteTests_1619, NullMetadata_1619) {

    value.setInt64(123);



    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, nullptr);

    EXPECT_EQ("(0)", os.str());

}



TEST_F(SonyMakerNoteTests_1619, GetModelFailure_1619) {

    value.setInt64(123);

    metadata.clear();

    EXPECT_CALL(*this, getModel(&metadata, testing::_))

        .WillOnce(testing::DoAll(testing::SetArgReferee<1>(""), testing::Return(false)));



    SonyMakerNote::printSonyMisc3cShotNumberSincePowerUp(os, value, &metadata);

    EXPECT_EQ("(0)", os.str());

}



// Mock function to replace the getModel method in ExifData

bool getModel(const ExifData* metadata, std::string& model) {

    // This function will be mocked in the tests

    return false;

}



}  // namespace
