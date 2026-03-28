#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/exiv2.hpp>

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class PrintXmpDateTest_1424 : public ::testing::Test {

protected:

    std::ostringstream os;

    ExifData exifData;  // Assuming ExifData is needed even though it's not used in the function



    Value createStringValue(const std::string& str) {

        Value* value = new StringValue();

        value->read(str.c_str(), str.size());

        return *value;

    }

};



TEST_F(PrintXmpDateTest_1424, ValidXmpDate19Chars_1424) {

    Value value = createStringValue("2023-10-05T14:48:00");

    printXmpDate(os, value, &exifData);

    EXPECT_EQ(os.str(), "2023:10:05 14:48:00");

}



TEST_F(PrintXmpDateTest_1424, ValidXmpDate20CharsWithZ_1424) {

    Value value = createStringValue("2023-10-05T14:48:00Z");

    printXmpDate(os, value, &exifData);

    EXPECT_EQ(os.str(), "2023:10:05 14:48:00");

}



TEST_F(PrintXmpDateTest_1424, InvalidSizeTooShort_1424) {

    Value value = createStringValue("2023-10-05T14:48");

    printXmpDate(os, value, &exifData);

    EXPECT_EQ(os.str(), "2023-10-05T14:48");  // Should output the original string

}



TEST_F(PrintXmpDateTest_1424, InvalidSizeTooLong_1424) {

    Value value = createStringValue("2023-10-05T14:48:00.123");

    printXmpDate(os, value, &exifData);

    EXPECT_EQ(os.str(), "2023-10-05T14:48:00.123");  // Should output the original string

}



TEST_F(PrintXmpDateTest_1424, InvalidType_1424) {

    Value* value = new ShortValue();  // Using a different type than xmpText

    value->read(reinterpret_cast<const byte*>(&value), sizeof(value));

    printXmpDate(os, *value, &exifData);

    delete value;

    EXPECT_EQ(os.str(), "");  // Should output nothing as the type is not xmpText

}
