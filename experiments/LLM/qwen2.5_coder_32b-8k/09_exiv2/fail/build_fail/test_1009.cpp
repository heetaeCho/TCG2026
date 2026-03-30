#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <Exiv2/value.hpp>

#include <Exiv2/exifdata.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class MinoltaMakerNoteTest_1009 : public ::testing::Test {

protected:

    MinoltaMakerNote minoltaMakerNote;

};



TEST_F(MinoltaMakerNoteTest_1009, PrintMinoltaBrightnessStd_NormalOperation_1009) {

    std::ostringstream os;

    Value value(24);  // Example value where (value.toInt64() / 8) - 6 = 0

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaBrightnessStd(os, value, exifData);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(MinoltaMakerNoteTest_1009, PrintMinoltaBrightnessStd_BoundaryCondition_ZeroValue_1009) {

    std::ostringstream os;

    Value value(48);  // Example value where (value.toInt64() / 8) - 6 = 0

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaBrightnessStd(os, value, exifData);



    EXPECT_EQ(os.str(), "0");

}



TEST_F(MinoltaMakerNoteTest_1009, PrintMinoltaBrightnessStd_BoundaryCondition_MaxValue_1009) {

    std::ostringstream os;

    Value value(std::numeric_limits<int64_t>::max());  // Large positive value

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaBrightnessStd(os, value, exifData);



    std::ostringstream expectedOs;

    expectedOs << (std::numeric_limits<int64_t>::max() / 8) - 6;

    EXPECT_EQ(os.str(), expectedOs.str());

}



TEST_F(MinoltaMakerNoteTest_1009, PrintMinoltaBrightnessStd_BoundaryCondition_MinValue_1009) {

    std::ostringstream os;

    Value value(std::numeric_limits<int64_t>::min());  // Large negative value

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaBrightnessStd(os, value, exifData);



    std::ostringstream expectedOs;

    expectedOs << (std::numeric_limits<int64_t>::min() / 8) - 6;

    EXPECT_EQ(os.str(), expectedOs.str());

}



TEST_F(MinoltaMakerNoteTest_1009, PrintMinoltaBrightnessStd_ExceptionalCase_NegativeValue_1009) {

    std::ostringstream os;

    Value value(-48);  // Example negative value where (value.toInt64() / 8) - 6 < 0

    const ExifData* exifData = nullptr;



    minoltaMakerNote.printMinoltaBrightnessStd(os, value, exifData);



    EXPECT_EQ(os.str(), "-12");

}
