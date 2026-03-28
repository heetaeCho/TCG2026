#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pentaxmn_int.hpp"

#include "exif.hpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class PentaxMakerNoteTest_200 : public ::testing::Test {

protected:

    Value value;

    ExifData metadata;



    PentaxMakerNoteTest_200() : value(TypeId::unsignedLong) {}



    void setupMetadata(const std::string& dateKey, uint32_t dateValue,

                       const std::string& timeKey, uint32_t timeValue) {

        Exiv2::Exifdatum exifDate(Exiv2::ExifKey(dateKey), &value);

        Exiv2::Exifdatum exifTime(Exiv2::ExifKey(timeKey), &value);



        exifDate.setValue(&value);

        exifTime.setValue(&value);



        uint32_t dateBytes[4] = {

            (dateValue >> 24) & 0xFF, (dateValue >> 16) & 0xFF,

            (dateValue >> 8) & 0xFF, dateValue & 0xFF

        };

        uint32_t timeBytes[3] = {

            (timeValue >> 24) & 0xFF, (timeValue >> 16) & 0xFF,

            (timeValue >> 8) & 0xFF

        };



        exifDate.setDataArea(reinterpret_cast<const byte*>(dateBytes), 4);

        exifTime.setDataArea(reinterpret_cast<const byte*>(timeBytes), 3);



        metadata.add(exifDate.key(), &exifDate.value());

        metadata.add(exifTime.key(), &exifTime.value());

    }

};



TEST_F(PentaxMakerNoteTest_200, NormalOperation_200) {

    setupMetadata("Exif.PentaxDng.Date", 0x12345678,

                  "Exif.PentaxDng.Time", 0x9ABCDEF);



    uint32_t countEnc = 0x87654321;

    value.setDataArea(reinterpret_cast<const byte*>(&countEnc), 4);



    std::ostringstream os;

    PentaxMakerNote::printShutterCount(os, value, &metadata);

    

    uint32_t expectedCount = countEnc ^ 0x12345678 ^ (~0x9ABCDEF);

    EXPECT_EQ(os.str(), std::to_string(expectedCount));

}



TEST_F(PentaxMakerNoteTest_200, MetadataNull_200) {

    uint32_t countEnc = 0x87654321;

    value.setDataArea(reinterpret_cast<const byte*>(&countEnc), 4);



    std::ostringstream os;

    PentaxMakerNote::printShutterCount(os, value, nullptr);

    

    EXPECT_EQ(os.str(), "undefined");

}



TEST_F(PentaxMakerNoteTest_200, DateKeyNotFound_200) {

    setupMetadata("Exif.Pentax.Date", 0x12345678,

                  "Exif.PentaxDng.Time", 0x9ABCDEF);



    uint32_t countEnc = 0x87654321;

    value.setDataArea(reinterpret_cast<const byte*>(&countEnc), 4);



    std::ostringstream os;

    PentaxMakerNote::printShutterCount(os, value, &metadata);

    

    EXPECT_EQ(os.str(), "undefined");

}



TEST_F(PentaxMakerNoteTest_200, TimeKeyNotFound_200) {

    setupMetadata("Exif.PentaxDng.Date", 0x12345678,

                  "Exif.Pentax.Time", 0x9ABCDEF);



    uint32_t countEnc = 0x87654321;

    value.setDataArea(reinterpret_cast<const byte*>(&countEnc), 4);



    std::ostringstream os;

    PentaxMakerNote::printShutterCount(os, value, &metadata);

    

    EXPECT_EQ(os.str(), "undefined");

}



TEST_F(PentaxMakerNoteTest_200, ValueSizeMismatch_200) {

    setupMetadata("Exif.PentaxDng.Date", 0x12345678,

                  "Exif.PentaxDng.Time", 0x9ABCDEF);



    uint32_t countEnc = 0x87654321;

    value.setDataArea(reinterpret_cast<const byte*>(&countEnc), 3); // Mismatched size



    std::ostringstream os;

    PentaxMakerNote::printShutterCount(os, value, &metadata);

    

    EXPECT_EQ(os.str(), "undefined");

}



TEST_F(PentaxMakerNoteTest_200, DateSizeMismatch_200) {

    setupMetadata("Exif.PentaxDng.Date", 0x12345678,

                  "Exif.PentaxDng.Time", 0x9ABCDEF);



    Exiv2::Exifdatum exifDate(Exiv2::ExifKey("Exif.PentaxDng.Date"), &value);

    uint32_t dateBytes[3] = { 0x12, 0x34, 0x56 }; // Mismatched size

    exifDate.setDataArea(reinterpret_cast<const byte*>(dateBytes), 3);



    metadata.add(exifDate.key(), &exifDate.value());



    uint32_t countEnc = 0x87654321;

    value.setDataArea(reinterpret_cast<const byte*>(&countEnc), 4);



    std::ostringstream os;

    PentaxMakerNote::printShutterCount(os, value, &metadata);

    

    EXPECT_EQ(os.str(), "undefined");

}



TEST_F(PentaxMakerNoteTest_200, TimeSizeMismatch_200) {

    setupMetadata("Exif.PentaxDng.Date", 0x12345678,

                  "Exif.PentaxDng.Time", 0x9ABCDEF);



    Exiv2::Exifdatum exifTime(Exiv2::ExifKey("Exif.PentaxDng.Time"), &value);

    uint32_t timeBytes[2] = { 0x9A, 0xBC }; // Mismatched size

    exifTime.setDataArea(reinterpret_cast<const byte*>(timeBytes), 2);



    metadata.add(exifTime.key(), &exifTime.value());



    uint32_t countEnc = 0x87654321;

    value.setDataArea(reinterpret_cast<const byte*>(&countEnc), 4);



    std::ostringstream os;

    PentaxMakerNote::printShutterCount(os, value, &metadata);

    

    EXPECT_EQ(os.str(), "undefined");

}
