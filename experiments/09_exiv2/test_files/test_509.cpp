#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>



using namespace Exiv2;

using namespace Internal;



class Nikon3MakerNoteTest_509 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    std::ostringstream os;

    ExifData exifData;



    Value createValue(uint16_t value) {

        auto val = Value::create(TypeId::unsignedShort);

        val->read(reinterpret_cast<const byte*>(&value), 1);

        return *val;

    }

};



TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_NormalOperation_509) {

    uint16_t testValue = 1024; // Example value that is not zero

    Value value = createValue(testValue);

    nikonMakerNote.printFocusDistanceLd4(os, value, &exifData);

    EXPECT_EQ(os.str(), "0.16 m");

}



TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_ZeroValue_509) {

    uint16_t testValue = 0; // Zero value case

    Value value = createValue(testValue);

    nikonMakerNote.printFocusDistanceLd4(os, value, &exifData);

    EXPECT_EQ(os.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_InvalidCount_509) {

    uint16_t testValue = 1024;

    Value value = createValue(testValue);

    value.setCount(2); // Invalid count

    nikonMakerNote.printFocusDistanceLd4(os, value, &exifData);

    EXPECT_EQ(os.str(), "(XmpExiv2::Value*)");

}



TEST_F(Nikon3MakerNoteTest_509, PrintFocusDistanceLd4_InvalidType_509) {

    uint16_t testValue = 1024;

    Value value = createValue(testValue);

    value.setType(TypeId::signedLong); // Invalid type

    nikonMakerNote.printFocusDistanceLd4(os, value, &exifData);

    EXPECT_EQ(os.str(), "(XmpExiv2::Value*)");

}
