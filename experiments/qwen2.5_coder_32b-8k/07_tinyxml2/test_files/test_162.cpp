#include <gtest/gtest.h>



namespace tinyxml2 {

    class XMLUtil;

}



using namespace tinyxml2;



class XMLUtilTest_162 : public ::testing::Test {

protected:

    bool hasBOM;

};



TEST_F(XMLUtilTest_162, ReadBOM_UTF8_NoBOM_162) {

    const char* input = "Sample text";

    const char* result = XMLUtil::ReadBOM(input, &hasBOM);

    

    EXPECT_FALSE(hasBOM);

    EXPECT_EQ(result, input);

}



TEST_F(XMLUtilTest_162, ReadBOM_UTF8_HasBOM_162) {

    const unsigned char utf8_bom[] = {0xEF, 0xBB, 0xBF, 'S', 'a', 'm', 'p', 'l', 'e', ' ', 't', 'e', 'x', 't'};

    const char* input = reinterpret_cast<const char*>(utf8_bom);

    const char* expectedOutput = input + 3;

    const char* result = XMLUtil::ReadBOM(input, &hasBOM);

    

    EXPECT_TRUE(hasBOM);

    EXPECT_EQ(result, expectedOutput);

}



TEST_F(XMLUtilTest_162, ReadBOM_UTF8_EmptyString_162) {

    const char* input = "";

    const char* result = XMLUtil::ReadBOM(input, &hasBOM);

    

    EXPECT_FALSE(hasBOM);

    EXPECT_EQ(result, input);

}



TEST_F(XMLUtilTest_162, ReadBOM_UTF8_PartialBOM_162) {

    const unsigned char partial_bom[] = {0xEF, 0xBB};

    const char* input = reinterpret_cast<const char*>(partial_bom);

    const char* result = XMLUtil::ReadBOM(input, &hasBOM);

    

    EXPECT_FALSE(hasBOM);

    EXPECT_EQ(result, input);

}



TEST_F(XMLUtilTest_162, ReadBOM_UTF8_OnlyBOM_162) {

    const unsigned char only_bom[] = {0xEF, 0xBB, 0xBF};

    const char* input = reinterpret_cast<const char*>(only_bom);

    const char* expectedOutput = input + 3;

    const char* result = XMLUtil::ReadBOM(input, &hasBOM);

    

    EXPECT_TRUE(hasBOM);

    EXPECT_EQ(result, expectedOutput);

}
