#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "casiomn_int.cpp"  // Assuming this is how we include the class definition



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Casio2MakerNoteTest_1822 : public ::testing::Test {

protected:

    Casio2MakerNote c2mn;

    std::ostringstream oss;

    ExifData exifData;  // Assuming ExifData is a necessary dependency



    Value createValue(const std::vector<long>& values) {

        Value value;

        for (auto val : values) {

            value.push_back(val);

        }

        return value;

    }

};



TEST_F(Casio2MakerNoteTest_1822, Print0x2001_NormalOperation_1822) {

    Value value = createValue({50, 49, 50, 51, 52, 53, 54, 55, 56, 57});

    c2mn.print0x2001(oss, value, &exifData);

    EXPECT_EQ("2050:23:45 67:89", oss.str());

}



TEST_F(Casio2MakerNoteTest_1822, Print0x2001_BoundaryCondition_ExactTenValues_1822) {

    Value value = createValue({50, 49, 50, 51, 52, 53, 54, 55, 56, 57});

    c2mn.print0x2001(oss, value, &exifData);

    EXPECT_EQ("2050:23:45 67:89", oss.str());

}



TEST_F(Casio2MakerNoteTest_1822, Print0x2001_BoundaryCondition_LessThanTenValues_1822) {

    Value value = createValue({50, 49});

    c2mn.print0x2001(oss, value, &exifData);

    EXPECT_EQ(value.toString(), oss.str());

}



TEST_F(Casio2MakerNoteTest_1822, Print0x2001_BoundaryCondition_ZeroValues_1822) {

    Value value = createValue({});

    c2mn.print0x2001(oss, value, &exifData);

    EXPECT_EQ(value.toString(), oss.str());

}



TEST_F(Casio2MakerNoteTest_1822, Print0x2001_ExceptionalCase_NonNumericValues_1822) {

    Value value = createValue({50, 49, 65, 51, 52, 53, 54, 55, 56, 57}); // 'A' is non-numeric

    c2mn.print0x2001(oss, value, &exifData);

    EXPECT_EQ(value.toString(), oss.str());

}



TEST_F(Casio2MakerNoteTest_1822, Print0x2001_NormalOperation_YearAdjustment_1900_1822) {

    Value value = createValue({75, 49, 50, 51, 52, 53, 54, 55, 56, 57});

    c2mn.print0x2001(oss, value, &exifData);

    EXPECT_EQ("1975:23:45 67:89", oss.str());

}



TEST_F(Casio2MakerNoteTest_1822, Print0x2001_NormalOperation_YearAdjustment_2000_1822) {

    Value value = createValue({50, 49, 50, 51, 52, 53, 54, 55, 56, 57});

    c2mn.print0x2001(oss, value, &exifData);

    EXPECT_EQ("2050:23:45 67:89", oss.str());

}
