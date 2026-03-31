#include <gtest/gtest.h>
#include <ft2build.h>
#include FT_FREETYPE_H

// Declaration of the function under test
FT_Error ft_new_face_from_file(FT_Library library, const char *filename_utf8, FT_Long face_index, FT_Face *aface);

class FtNewFaceFromFileTest_32 : public ::testing::Test {
protected:
    FT_Library library;
    FT_Face face;

    void SetUp() override {
        FT_Error error = FT_Init_FreeType(&library);
        ASSERT_EQ(error, 0) << "Failed to initialize FreeType library";
        face = nullptr;
    }

    void TearDown() override {
        if (face) {
            FT_Done_Face(face);
            face = nullptr;
        }
        if (library) {
            FT_Done_FreeType(library);
            library = nullptr;
        }
    }
};

// Test that passing a null filename returns an error
TEST_F(FtNewFaceFromFileTest_32, NullFilenameReturnsError_32) {
    FT_Error error = ft_new_face_from_file(library, nullptr, 0, &face);
    EXPECT_NE(error, 0);
}

// Test that passing a non-existent file returns an error
TEST_F(FtNewFaceFromFileTest_32, NonExistentFileReturnsError_32) {
    FT_Error error = ft_new_face_from_file(library, "/nonexistent/path/to/font.ttf", 0, &face);
    EXPECT_NE(error, 0);
}

// Test that passing an empty string filename returns an error
TEST_F(FtNewFaceFromFileTest_32, EmptyFilenameReturnsError_32) {
    FT_Error error = ft_new_face_from_file(library, "", 0, &face);
    EXPECT_NE(error, 0);
}

// Test that passing a null library with a valid-looking filename returns an error
TEST_F(FtNewFaceFromFileTest_32, NullLibraryReturnsError_32) {
    FT_Error error = ft_new_face_from_file(nullptr, "/some/path/font.ttf", 0, &face);
    EXPECT_NE(error, 0);
}

// Test that passing an invalid face index with a non-existent file still returns an error
TEST_F(FtNewFaceFromFileTest_32, InvalidFaceIndexWithNonExistentFile_32) {
    FT_Error error = ft_new_face_from_file(library, "/nonexistent/font.ttf", 999, &face);
    EXPECT_NE(error, 0);
}

// Test that a directory path (not a font file) returns an error
TEST_F(FtNewFaceFromFileTest_32, DirectoryPathReturnsError_32) {
    FT_Error error = ft_new_face_from_file(library, "/tmp", 0, &face);
    EXPECT_NE(error, 0);
}

// Test with a negative face index and non-existent file
TEST_F(FtNewFaceFromFileTest_32, NegativeFaceIndexNonExistentFile_32) {
    FT_Error error = ft_new_face_from_file(library, "/nonexistent/font.ttf", -1, &face);
    EXPECT_NE(error, 0);
}

// Test loading a valid font file if one exists on the system
// This test attempts common font paths; it will be skipped if no font is found
TEST_F(FtNewFaceFromFileTest_32, ValidFontFileLoadsSuccessfully_32) {
    // Try common system font paths
    const char *font_paths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf",
        "/System/Library/Fonts/Helvetica.ttc",
        "C:\\Windows\\Fonts\\arial.ttf",
        nullptr
    };

    bool found = false;
    for (int i = 0; font_paths[i] != nullptr; i++) {
        FILE *f = fopen(font_paths[i], "rb");
        if (f) {
            fclose(f);
            FT_Error error = ft_new_face_from_file(library, font_paths[i], 0, &face);
            if (error == 0) {
                found = true;
                EXPECT_NE(face, nullptr);
                break;
            }
        }
    }

    if (!found) {
        GTEST_SKIP() << "No valid system font found to test with";
    }
}

// Test that loading a valid font with an out-of-range face index returns an error
TEST_F(FtNewFaceFromFileTest_32, ValidFontInvalidFaceIndex_32) {
    const char *font_paths[] = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/TTF/DejaVuSans.ttf",
        "/usr/share/fonts/dejavu-sans-fonts/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "/usr/share/fonts/liberation-sans/LiberationSans-Regular.ttf",
        nullptr
    };

    bool found = false;
    for (int i = 0; font_paths[i] != nullptr; i++) {
        FILE *f = fopen(font_paths[i], "rb");
        if (f) {
            fclose(f);
            found = true;
            FT_Error error = ft_new_face_from_file(library, font_paths[i], 9999, &face);
            EXPECT_NE(error, 0) << "Expected error for invalid face index 9999";
            break;
        }
    }

    if (!found) {
        GTEST_SKIP() << "No valid system font found to test with";
    }
}

// Test loading a non-font file returns an error
TEST_F(FtNewFaceFromFileTest_32, NonFontFileReturnsError_32) {
    // Create a temporary non-font file
    const char *tmp_path = "/tmp/ft_test_not_a_font_32.txt";
    FILE *f = fopen(tmp_path, "w");
    if (f) {
        fprintf(f, "This is not a font file");
        fclose(f);

        FT_Error error = ft_new_face_from_file(library, tmp_path, 0, &face);
        EXPECT_NE(error, 0);

        remove(tmp_path);
    } else {
        GTEST_SKIP() << "Could not create temporary file for testing";
    }
}

// Test loading an empty file returns an error
TEST_F(FtNewFaceFromFileTest_32, EmptyFileReturnsError_32) {
    const char *tmp_path = "/tmp/ft_test_empty_font_32.ttf";
    FILE *f = fopen(tmp_path, "w");
    if (f) {
        fclose(f);

        FT_Error error = ft_new_face_from_file(library, tmp_path, 0, &face);
        EXPECT_NE(error, 0);

        remove(tmp_path);
    } else {
        GTEST_SKIP() << "Could not create temporary file for testing";
    }
}
