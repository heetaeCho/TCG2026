#include <gtest/gtest.h>

#include "exiv2/xmpsidecar.hpp"

#include <memory>

#include <string>



// Mock class for BasicIo to simulate external dependency

class MockBasicIo : public Exiv2::BasicIo {

public:

    MOCK_METHOD(void, read, (byte*, long), (override));

    MOCK_METHOD(void, write, (const byte*, long), (override));

};



// Test fixture for XmpSidecar tests

class XmpSidecarTest_1715 : public ::testing::Test {

protected:

    std::unique_ptr<MockBasicIo> mock_io;

    Exiv2::XmpSidecar xmp_sidecar;



    XmpSidecarTest_1715() 

        : mock_io(std::make_unique<MockBasicIo>()),

          xmp_sidecar(std::move(mock_io), false) {}

};



// Test case to verify the mimeType function returns the correct value

TEST_F(XmpSidecarTest_1715, MimeTypeReturnsCorrectValue_1715) {

    EXPECT_EQ(xmp_sidecar.mimeType(), "application/rdf+xml");

}



// Test case to verify setComment function works without errors (normal operation)

TEST_F(XmpSidecarTest_1715, SetCommentWorksNormally_1715) {

    EXPECT_NO_THROW(xmp_sidecar.setComment("Sample comment"));

}



// Test case to verify readMetadata function works without errors (normal operation)

TEST_F(XmpSidecarTest_1715, ReadMetadataWorksNormally_1715) {

    EXPECT_CALL(*mock_io, read(::testing::_, ::testing::_)).Times(1);

    EXPECT_NO_THROW(xmp_sidecar.readMetadata());

}



// Test case to verify writeMetadata function works without errors (normal operation)

TEST_F(XmpSidecarTest_1715, WriteMetadataWorksNormally_1715) {

    EXPECT_CALL(*mock_io, write(::testing::_, ::testing::_)).Times(1);

    EXPECT_NO_THROW(xmp_sidecar.writeMetadata());

}



// Test case to verify boundary conditions with empty comment

TEST_F(XmpSidecarTest_1715, SetEmptyComment_1715) {

    EXPECT_NO_THROW(xmp_sidecar.setComment(""));

}



// Test case to verify boundary conditions with very long comment

TEST_F(XmpSidecarTest_1715, SetVeryLongComment_1715) {

    std::string long_comment(1024 * 1024, 'a'); // 1MB of 'a'

    EXPECT_NO_THROW(xmp_sidecar.setComment(long_comment));

}
