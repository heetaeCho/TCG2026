#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "ft_utils.h"

#include <ft2build.h>

#include FT_FREETYPE_H



class ft_new_face_from_fileTest_32 : public ::testing::Test {

protected:

    FT_Library library;

    FT_Face face;



    void SetUp() override {

        FT_Init_FreeType(&library);

    }



    void TearDown() override {

        if (face) {

            FT_Done_Face(face);

        }

        FT_Done_FreeType(library);

    }

};



TEST_F(ft_new_face_from_fileTest_32, ValidFileAndIndex_ReturnsSuccess_32) {

    FT_Error error = ft_new_face_from_file(library, "valid_font.ttf", 0, &face);

    EXPECT_EQ(error, FT_Err_Ok);

}



TEST_F(ft_new_face_from_fileTest_32, InvalidFileName_ReturnsError_32) {

    FT_Error error = ft_new_face_from_file(library, nullptr, 0, &face);

    EXPECT_EQ(error, FT_Err_Invalid_Argument);

}



TEST_F(ft_new_face_from_fileTest_32, NonExistentFile_ReturnsError_32) {

    FT_Error error = ft_new_face_from_file(library, "non_existent.ttf", 0, &face);

    EXPECT_EQ(error, FT_Err_Cannot_Open_Resource);

}



TEST_F(ft_new_face_from_fileTest_32, EmptyFile_ReturnsError_32) {

    // Assuming there's a way to create an empty file for testing

    FT_Error error = ft_new_face_from_file(library, "empty_font.ttf", 0, &face);

    EXPECT_EQ(error, FT_Err_Cannot_Open_Stream);

}



TEST_F(ft_new_face_from_fileTest_32, InvalidFaceIndex_ReturnsError_32) {

    // Assuming invalid index will cause an error

    FT_Error error = ft_new_face_from_file(library, "valid_font.ttf", -1, &face);

    EXPECT_EQ(error, FT_Err_Invalid_Argument); // or another appropriate error code

}



TEST_F(ft_new_face_from_fileTest_32, NullFacePointer_ReturnsError_32) {

    FT_Error error = ft_new_face_from_file(library, "valid_font.ttf", 0, nullptr);

    EXPECT_EQ(error, FT_Err_Invalid_Argument); // or another appropriate error code

}
