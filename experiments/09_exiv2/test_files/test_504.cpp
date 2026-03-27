#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/value.hpp>

#include <exiv2/exif.hpp>



namespace Exiv2 {

    namespace Internal {

        class Nikon3MakerNote {

        public:

            std::ostream& printPictureControl(std::ostream& os, const Value& value, const ExifData*) {

                if (value.count() != 1 || value.typeId() != unsignedByte) return os << "(" << value << ")";

                const auto pcval = value.toInt64() - 0x80;

                if (pcval == 0) return os << _("Normal");

                if (pcval == 127) return os << _("n/a");

                if (pcval == -127) return os << _("User");

                if (pcval == -128) return os << _("Auto");

                return os << pcval;

            }

        };

    }

}



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_504 : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    std::ostringstream oss;

    Exiv2::ExifData exifData;

};



TEST_F(Nikon3MakerNoteTest_504, NormalOperation_NormalValue_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1u); // 1 - 0x80 = -127 -> "User"



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "User");

}



TEST_F(Nikon3MakerNoteTest_504, NormalOperation_NAValue_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(207u); // 207 - 0x80 = 127 -> "n/a"



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_504, NormalOperation_AutoValue_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(0u); // 0 - 0x80 = -128 -> "Auto"



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "Auto");

}



TEST_F(Nikon3MakerNoteTest_504, NormalOperation_DefaultValue_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(128u); // 128 - 0x80 = 0 -> "Normal"



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "Normal");

}



TEST_F(Nikon3MakerNoteTest_504, BoundaryCondition_ZeroValue_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(128u); // 128 - 0x80 = 0 -> "Normal"



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "Normal");

}



TEST_F(Nikon3MakerNoteTest_504, BoundaryCondition_MaxValue_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(255u); // 255 - 0x80 = 127 -> "n/a"



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "n/a");

}



TEST_F(Nikon3MakerNoteTest_504, BoundaryCondition_MinValue_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(0u); // 0 - 0x80 = -128 -> "Auto"



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "Auto");

}



TEST_F(Nikon3MakerNoteTest_504, ErrorCase_WrongCount_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::unsignedByte);

    value.modify(1u); // 1 - 0x80 = -127

    value.setCount(2); // Simulate wrong count



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "(U(2) 1 )");

}



TEST_F(Nikon3MakerNoteTest_504, ErrorCase_WrongType_504) {

    Exiv2::Value value = Exiv2::Value::create(Exiv2::asciiString);

    value.modify("test"); // Simulate wrong type



    nikonMakerNote.printPictureControl(oss, value, &exifData);



    EXPECT_EQ(oss.str(), "(ASCII 4 t e s t )");

}
