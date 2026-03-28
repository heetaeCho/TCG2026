#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tiffvisitor_int.hpp"

#include "exif.hpp"

#include "value.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class TiffEncoderTest : public ::testing::Test {

protected:

    void SetUp() override {

        tiffDataEntry = std::make_unique<TiffDataEntry>(0x123, IfdId::exifIFD, TiffType::ascii);

        exifDatum = std::make_unique<Exifdatum>(ExifKey(0x123, "Exif"), nullptr);

        tiffEncoder = std::make_unique<TiffEncoder>(ExifData(), IptcData(), XmpData(), nullptr, false, PrimaryGroups(), nullptr, nullptr);

    }



    std::unique_ptr<TiffDataEntry> tiffDataEntry;

    std::unique_ptr<Exifdatum> exifDatum;

    std::unique_ptr<TiffEncoder> tiffEncoder;

};



TEST_F(TiffEncoderTest_1682, EncodeDataEntryNormalOperation_1682) {

    DataBuf dataBuffer(reinterpret_cast<const byte*>("SampleData"), 10);

    auto* value = new Value(Exiv2::asciiString);

    value->setDataArea(dataBuffer.c_data(), dataBuffer.size());

    exifDatum->setValue(value);



    tiffDataEntry->setData(nullptr, 10, std::make_shared<DataBuf>(dataBuffer));

    tiffEncoder->encodeDataEntry(tiffDataEntry.get(), exifDatum.get());



    EXPECT_EQ(memcmp(tiffDataEntry->pDataArea_, dataBuffer.c_data(), dataBuffer.size()), 0);

}



TEST_F(TiffEncoderTest_1682, EncodeDataEntryBoundaryConditionEmptyData_1682) {

    DataBuf emptyBuffer;

    auto* value = new Value(Exiv2::asciiString);

    value->setDataArea(emptyBuffer.c_data(), emptyBuffer.size());

    exifDatum->setValue(value);



    tiffDataEntry->setData(nullptr, 0, std::make_shared<DataBuf>(emptyBuffer));

    tiffEncoder->encodeDataEntry(tiffDataEntry.get(), exifDatum.get());



    EXPECT_EQ(memcmp(tiffDataEntry->pDataArea_, emptyBuffer.c_data(), emptyBuffer.size()), 0);

}



TEST_F(TiffEncoderTest_1682, EncodeDataEntryBoundaryConditionMaxSize_1682) {

    DataBuf maxBuffer(LARGE_INT - 1, 'A');

    auto* value = new Value(Exiv2::asciiString);

    value->setDataArea(maxBuffer.c_data(), maxBuffer.size());

    exifDatum->setValue(value);



    tiffDataEntry->setData(nullptr, maxBuffer.size(), std::make_shared<DataBuf>(maxBuffer));

    tiffEncoder->encodeDataEntry(tiffDataEntry.get(), exifDatum.get());



    EXPECT_EQ(memcmp(tiffDataEntry->pDataArea_, maxBuffer.c_data(), maxBuffer.size()), 0);

}



TEST_F(TiffEncoderTest_1682, EncodeDataEntryDataAreaGrows_1682) {

    DataBuf initialBuffer(reinterpret_cast<const byte*>("Initial"), 7);

    tiffDataEntry->setData(nullptr, 7, std::make_shared<DataBuf>(initialBuffer));

    tiffDataEntry->sizeDataArea_ = 7;



    DataBuf newBuffer(reinterpret_cast<const byte*>("NewLongerData"), 13);

    auto* value = new Value(Exiv2::asciiString);

    value->setDataArea(newBuffer.c_data(), newBuffer.size());

    exifDatum->setValue(value);



    tiffEncoder->encodeDataEntry(tiffDataEntry.get(), exifDatum.get());



    EXPECT_EQ(memcmp(tiffDataEntry->pDataArea_, newBuffer.c_data(), newBuffer.size()), 0);

}



TEST_F(TiffEncoderTest_1682, EncodeDataEntryNoChangeInSize_1682) {

    DataBuf initialBuffer(reinterpret_cast<const byte*>("Sample"), 6);

    tiffDataEntry->setData(nullptr, 6, std::make_shared<DataBuf>(initialBuffer));

    tiffDataEntry->sizeDataArea_ = 6;



    auto* value = new Value(Exiv2::asciiString);

    value->setDataArea(initialBuffer.c_data(), initialBuffer.size());

    exifDatum->setValue(value);



    tiffEncoder->encodeDataEntry(tiffDataEntry.get(), exifDatum.get());



    EXPECT_EQ(memcmp(tiffDataEntry->pDataArea_, initialBuffer.c_data(), initialBuffer.size()), 0);

}
