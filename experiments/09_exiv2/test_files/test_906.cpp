#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <exiv2/exiv2.hpp>



namespace Exiv2 {

    namespace Internal {

        class OlympusMakerNote { 

        public: 

            std::ostream& print0x0305(std::ostream& os, const Value& value, const ExifData*) { 

                if (value.count() != 1 || value.typeId() != unsignedRational) { 

                    return os << value; 

                } 

                auto [r, s] = value.toRational(); 

                if (static_cast<uint32_t>(r) == 0xffffffff) { 

                    return os << _("Infinity"); 

                } 

                return os << stringFormat("{:.2f} m", static_cast<float>(r) / 1000); 

            } 

        }; 

    }

}



using namespace Exiv2::Internal;



class OlympusMakerNoteTest_906 : public ::testing::Test {

protected:

    OlympusMakerNote olympusMakerNote;

    std::ostringstream oss;

};



TEST_F(OlympusMakerNoteTest_906, NormalOperation_RationalValue_906) {

    Exiv2::URationalValue value;

    value.setValue(Exiv2::URational(1500, 1));

    olympusMakerNote.print0x0305(oss, value, nullptr);

    EXPECT_EQ(oss.str(), "1.50 m");

}



TEST_F(OlympusMakerNoteTest_906, InfinityValue_906) {

    Exiv2::URationalValue value;

    value.setValue(Exiv2::URational(0xffffffff, 1));

    olympusMakerNote.print0x0305(oss, value, nullptr);

    EXPECT_EQ(oss.str(), "Infinity");

}



TEST_F(OlympusMakerNoteTest_906, InvalidCountValue_906) {

    Exiv2::URationalValue value;

    value.setValue(Exiv2::URational(1500, 1));

    value.resize(2);

    olympusMakerNote.print0x0305(oss, value, nullptr);

    EXPECT_EQ(oss.str(), "[ 1500/1 ]");

}



TEST_F(OlympusMakerNoteTest_906, InvalidTypeIdValue_906) {

    Exiv2::UShortValue value;

    value.setValue(1500);

    olympusMakerNote.print0x0305(oss, value, nullptr);

    EXPECT_EQ(oss.str(), "[ 1500 ]");

}



TEST_F(OlympusMakerNoteTest_906, ZeroDenominator_906) {

    Exiv2::URationalValue value;

    value.setValue(Exiv2::URational(1500, 0));

    olympusMakerNote.print0x0305(oss, value, nullptr);

    EXPECT_EQ(oss.str(), "[ 1500/0 ]");

}
