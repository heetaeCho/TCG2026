#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "tiffcomposite_int.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffReaderTest_1706 : public ::testing::Test {

protected:

    ByteOrder byteOrder = littleEndian;

    size_t size = 1024;

    std::unique_ptr<byte[]> pData = std::make_unique<byte[]>(size);

    const byte* pLast = pData.get() + size;

    TiffComponent root(0, ifd0Id);

    TiffRwState state(byteOrder, 0);

    TiffReader reader(pData.get(), size, &root, state);



    std::unique_ptr<MnHeader> pHeader = std::make_unique<MnHeader>();

    TiffIfdMakernote makernote(0x002A, ifd0Id, exifId, std::move(pHeader), false);

};



TEST_F(TiffReaderTest_1706, NormalOperation_ReadsHeaderSuccessfully_1706) {

    EXPECT_CALL(makernote, readHeader(::testing::_, ::testing::_, byteOrder))

        .WillOnce(::testing::Return(true));



    reader.visitIfdMakernote(&makernote);



    EXPECT_EQ(makernote.byteOrder(), byteOrder);

}



TEST_F(TiffReaderTest_1706, FailureToReadHeader_LogsErrorAndSetsGoFalse_1706) {

    ::testing::internal::CaptureStderr();



    EXPECT_CALL(makernote, readHeader(::testing::_, ::testing::_, byteOrder))

        .WillOnce(::testing::Return(false));



    reader.visitIfdMakernote(&makernote);



    std::string output = ::testing::internal::GetCapturedStderr();

    EXPECT_TRUE(output.find("Failed to read") != std::string::npos);

    EXPECT_FALSE(reader.go(TiffVisitor::GoEvent::geKnownMakernote));

}



TEST_F(TiffReaderTest_1706, BoundaryCondition_ZeroSizeHeader_1706) {

    size = 0;

    reader = TiffReader(pData.get(), size, &root, state);



    EXPECT_CALL(makernote, readHeader(::testing::_, ::testing::_, byteOrder))

        .WillOnce(::testing::Return(false));



    reader.visitIfdMakernote(&makernote);

}



TEST_F(TiffReaderTest_1706, BoundaryCondition_MaxSizeHeader_1706) {

    size = std::numeric_limits<size_t>::max();

    pLast = pData.get() + size;

    reader = TiffReader(pData.get(), size, &root, state);



    EXPECT_CALL(makernote, readHeader(::testing::_, ::testing::_, byteOrder))

        .WillOnce(::testing::Return(true));



    reader.visitIfdMakernote(&makernote);

}



TEST_F(TiffReaderTest_1706, ExternalInteraction_SetsImageByteOrder_1706) {

    EXPECT_CALL(makernote, setImageByteOrder(byteOrder))

        .Times(1);



    reader.visitIfdMakernote(&makernote);

}
