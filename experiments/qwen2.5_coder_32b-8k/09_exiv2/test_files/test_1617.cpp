#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"

#include "./TestProjects/exiv2/src/sonymn_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class SonyMakerNoteTest_1617 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

    std::ostringstream os;

    Value value;

    MockExifData mockMetadata;

};



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_ValueCountNotOne_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).Times(0);

    value = Value(TypeId::shortType); // Just to ensure it's not null

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, &mockMetadata);

    EXPECT_EQ(os.str(), "(0)\n");

}



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_MetadataNull_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).Times(0);

    value = Value(TypeId::shortType); // Ensure it's not null and count is 1

    ON_CALL(value, count()).WillByDefault(::testing::Return(1));

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, nullptr);

    EXPECT_EQ(os.str(), "(0)\n");

}



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_ModelNotSupported_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>("UnsupportedModel"),

        ::testing::Return(true)

    ));

    value = Value(TypeId::shortType);

    ON_CALL(value, count()).WillByDefault(::testing::Return(1));

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, &mockMetadata);

    EXPECT_EQ(os.str(), "0%\n");

}



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_ModelSupportedSLT_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>("SLT-A7"),

        ::testing::Return(true)

    ));

    value = Value(TypeId::shortType);

    ON_CALL(value, count()).WillByDefault(::testing::Return(1));

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, &mockMetadata);

    EXPECT_EQ(os.str(), "n/a\n");

}



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_ModelSupportedHV_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>("ILCA-99HV"),

        ::testing::Return(true)

    ));

    value = Value(TypeId::shortType);

    ON_CALL(value, count()).WillByDefault(::testing::Return(1));

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, &mockMetadata);

    EXPECT_EQ(os.str(), "n/a\n");

}



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_ModelSupportedILCA_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>("ILCA-99"),

        ::testing::Return(true)

    ));

    value = Value(TypeId::shortType);

    ON_CALL(value, count()).WillByDefault(::testing::Return(1));

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, &mockMetadata);

    EXPECT_EQ(os.str(), "n/a\n");

}



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_ValueToInt64Zero_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>("SupportedModel"),

        ::testing::Return(true)

    ));

    value = Value(TypeId::shortType);

    ON_CALL(value, count()).WillByDefault(::testing::Return(1));

    ON_CALL(value, toInt64(_)).WillByDefault(::testing::Return(0));

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, &mockMetadata);

    EXPECT_EQ(os.str(), "0%\n");

}



TEST_F(SonyMakerNoteTest_1617, printSonyMisc2bLensZoomPosition_ValueToInt64NonZero_1617) {

    EXPECT_CALL(mockMetadata, getModel(_)).WillOnce(::testing::DoAll(

        ::testing::SetArgReferee<0>("SupportedModel"),

        ::testing::Return(true)

    ));

    value = Value(TypeId::shortType);

    ON_CALL(value, count()).WillByDefault(::testing::Return(1));

    ON_CALL(value, toInt64(_)).WillByDefault(::testing::Return(2048)); // 2048 / 10.24 = 200%

    sonyMakerNote.printSonyMisc2bLensZoomPosition(os, value, &mockMetadata);

    EXPECT_EQ(os.str(), "200%\n");

}



class MockExifData : public Exiv2::ExifData {

public:

    MOCK_METHOD1(getModel, bool(std::string& model));

};
