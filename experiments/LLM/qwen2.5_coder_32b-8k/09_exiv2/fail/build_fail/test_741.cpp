#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class ExifdatumTest_741 : public ::testing::Test {

protected:

    ExifKey key;

    Value* value = new Value(TypeId::undefined);

    Exifdatum exifDatum{key, value};

};



TEST_F(ExifdatumTest_741, SetDataAreaWithValidBuffer_741) {

    byte buf[] = {0x01, 0x02, 0x03};

    size_t len = sizeof(buf);

    int result = exifDatum.setDataArea(buf, len);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(ExifdatumTest_741, SetDataAreaWithEmptyBuffer_741) {

    byte buf[] = {};

    size_t len = sizeof(buf);

    int result = exifDatum.setDataArea(buf, len);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(ExifdatumTest_741, SetDataAreaWithNullBuffer_741) {

    byte* buf = nullptr;

    size_t len = 10;

    int result = exifDatum.setDataArea(buf, len);

    EXPECT_EQ(result, -1); // Assuming failure is indicated by -1

}



TEST_F(ExifdatumTest_741, SetDataAreaWithLargeBuffer_741) {

    byte buf[LARGE_INT] = {0};

    size_t len = sizeof(buf);

    int result = exifDatum.setDataArea(buf, len);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(ExifdatumTest_741, SetDataAreaWithoutValue_741) {

    Exifdatum exifDatumWithoutValue{key, nullptr};

    byte buf[] = {0x01, 0x02, 0x03};

    size_t len = sizeof(buf);

    int result = exifDatumWithoutValue.setDataArea(buf, len);

    EXPECT_EQ(result, -1); // Assuming failure is indicated by -1

}
