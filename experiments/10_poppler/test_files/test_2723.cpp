#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>

#include <memory>

#include "poppler/utils/pdftotext.cc"

#include "poppler/poppler/Object.h"

#include "poppler/poppler/Dict.h"

#include "poppler/poppler/UnicodeMap.h"



using namespace std;

using namespace testing;



class PrintInfoStringTest_2723 : public Test {

protected:

    FILE* output_file_;

    Dict info_dict_;

    UnicodeMap u_map_;



    void SetUp() override {

        output_file_ = fopen("test_output.txt", "w");

        ASSERT_NE(output_file_, nullptr);

    }



    void TearDown() override {

        fclose(output_file_);

        remove("test_output.txt");

    }

};



TEST_F(PrintInfoStringTest_2723, NormalOperationASCII_2723) {

    const char* key = "Title";

    const char* text1 = "<title>";

    const char* text2 = "</title>";

    std::unique_ptr<GooString> title_str(new GooString("Sample Title"));

    info_dict_.dictAdd(key, Object(std::move(title_str)));



    printInfoString(output_file_, &info_dict_, key, text1, text2, &u_map_);



    rewind(output_file_);

    char buffer[50];

    fgets(buffer, sizeof(buffer), output_file_);

    EXPECT_STREQ(buffer, "<title>Sample Title</title>");

}



TEST_F(PrintInfoStringTest_2723, NormalOperationUnicode_2723) {

    const char* key = "Title";

    const char* text1 = "<title>";

    const char* text2 = "</title>";

    std::unique_ptr<GooString> title_str(new GooString("\xfe\xff\x00S\x00a\x00m\x00p\x00l\x00e"));

    info_dict_.dictAdd(key, Object(std::move(title_str)));



    printInfoString(output_file_, &info_dict_, key, text1, text2, &u_map_);



    rewind(output_file_);

    char buffer[50];

    fgets(buffer, sizeof(buffer), output_file_);

    EXPECT_STREQ(buffer, "<title>Sample</title>");

}



TEST_F(PrintInfoStringTest_2723, KeyNotFound_2723) {

    const char* key = "NonExistentKey";

    const char* text1 = "<title>";

    const char* text2 = "</title>";



    printInfoString(output_file_, &info_dict_, key, text1, text2, &u_map_);



    rewind(output_file_);

    char buffer[50];

    fgets(buffer, sizeof(buffer), output_file_);

    EXPECT_STREQ(buffer, "");

}



TEST_F(PrintInfoStringTest_2723, EmptyString_2723) {

    const char* key = "Title";

    const char* text1 = "<title>";

    const char* text2 = "</title>";

    std::unique_ptr<GooString> title_str(new GooString(""));

    info_dict_.dictAdd(key, Object(std::move(title_str)));



    printInfoString(output_file_, &info_dict_, key, text1, text2, &u_map_);



    rewind(output_file_);

    char buffer[50];

    fgets(buffer, sizeof(buffer), output_file_);

    EXPECT_STREQ(buffer, "<title></title>");

}



TEST_F(PrintInfoStringTest_2723, BoundaryConditionSmallBuffer_2723) {

    const char* key = "Title";

    const char* text1 = "<title>";

    const char* text2 = "</title>";

    std::unique_ptr<GooString> title_str(new GooString("A"));

    info_dict_.dictAdd(key, Object(std::move(title_str)));



    printInfoString(output_file_, &info_dict_, key, text1, text2, &u_map_);



    rewind(output_file_);

    char buffer[50];

    fgets(buffer, sizeof(buffer), output_file_);

    EXPECT_STREQ(buffer, "<title>A</title>");

}



TEST_F(PrintInfoStringTest_2723, BoundaryConditionLargeBuffer_2723) {

    const char* key = "Title";

    const char* text1 = "<title>";

    const char* text2 = "</title>";

    std::string large_string(4096, 'A');

    std::unique_ptr<GooString> title_str(new GooString(large_string.c_str()));

    info_dict_.dictAdd(key, Object(std::move(title_str)));



    printInfoString(output_file_, &info_dict_, key, text1, text2, &u_map_);



    rewind(output_file_);

    char buffer[8192];

    fgets(buffer, sizeof(buffer), output_file_);

    EXPECT_EQ(strlen(buffer) - strlen("</title>") - 7, large_string.size());

}



TEST_F(PrintInfoStringTest_2723, UnicodeMapInteraction_2723) {

    const char* key = "Title";

    const char* text1 = "<title>";

    const char* text2 = "</title>";

    std::unique_ptr<GooString> title_str(new GooString("\xfe\xff\x00S\x00a\x00m\x00p\x00l\x00e"));

    info_dict_.dictAdd(key, Object(std::move(title_str)));



    auto mock_map_unicode = [](Unicode u, char* buf, int bufSize) {

        strncpy(buf, "Mapped", bufSize);

        return 6;

    };

    UnicodeMap mock_u_map(mock_map_unicode);



    printInfoString(output_file_, &info_dict_, key, text1, text2, &mock_u_map);



    rewind(output_file_);

    char buffer[50];

    fgets(buffer, sizeof(buffer), output_file_);

    EXPECT_STREQ(buffer, "<title>MappedMappedMappedMappedMapped</title>");

}
