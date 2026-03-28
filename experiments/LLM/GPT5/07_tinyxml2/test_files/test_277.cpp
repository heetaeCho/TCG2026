// File: ./TestProjects/tinyxml2/test_callfopen_277.cpp

#include <gtest/gtest.h>

#include <tinyxml2.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

class CallFopenTest_277 : public ::testing::Test {
protected:
    fs::path MakeTempDir_277() {
        const fs::path base = fs::temp_directory_path() / "tinyxml2_callfopen_tests_277";
        fs::create_directories(base);

        // Create a unique subdir name without relying on non-portable APIs.
        for (int i = 0; i < 200; ++i) {
            fs::path candidate = base / ("case_" + std::to_string(::getpid()) + "_" + std::to_string(i));
            std::error_code ec;
            if (fs::create_directories(candidate, ec) && !ec) {
                return candidate;
            }
        }

        // Fallback: just use base (tests may collide in extreme cases, but still functional).
        return base;
    }

    static void WriteTextFile_277(const fs::path& p, const std::string& content) {
        std::ofstream out(p, std::ios::binary);
        ASSERT_TRUE(out.is_open()) << "Failed to open file for writing: " << p.string();
        out.write(content.data(), static_cast<std::streamsize>(content.size()));
        out.close();
    }
};

TEST_F(CallFopenTest_277, LoadFile_Nonexistent_ReturnsFileNotFound_277) {
    tinyxml2::XMLDocument doc;

    fs::path dir = MakeTempDir_277();
    fs::path missing = dir / "this_file_should_not_exist_277.xml";
    ASSERT_FALSE(fs::exists(missing));

    const tinyxml2::XMLError err = doc.LoadFile(missing.string().c_str());

    // Observable behavior through public API: non-existent file should not succeed.
    EXPECT_NE(err, tinyxml2::XML_SUCCESS);
}

TEST_F(CallFopenTest_277, SaveFile_InvalidDirectory_ReturnsNonSuccess_277) {
    tinyxml2::XMLDocument doc;
    doc.Parse("<root/>");

    fs::path dir = MakeTempDir_277();
    fs::path nonexistentDir = dir / "no_such_dir_277";
    ASSERT_FALSE(fs::exists(nonexistentDir));

    fs::path outPath = nonexistentDir / "out_277.xml";

    const tinyxml2::XMLError err = doc.SaveFile(outPath.string().c_str());

    // Observable behavior: saving to a path whose parent directory doesn't exist should not succeed.
    EXPECT_NE(err, tinyxml2::XML_SUCCESS);
    EXPECT_FALSE(fs::exists(outPath));
}

TEST_F(CallFopenTest_277, SaveFile_ValidPath_CreatesFileAndSuccess_277) {
    tinyxml2::XMLDocument doc;
    doc.Parse("<root><child/></root>");

    fs::path dir = MakeTempDir_277();
    fs::path outPath = dir / "saved_277.xml";

    const tinyxml2::XMLError err = doc.SaveFile(outPath.string().c_str());

    EXPECT_EQ(err, tinyxml2::XML_SUCCESS);
    EXPECT_TRUE(fs::exists(outPath));

    // Also verify we can load it back successfully (end-to-end observable behavior).
    tinyxml2::XMLDocument doc2;
    const tinyxml2::XMLError err2 = doc2.LoadFile(outPath.string().c_str());
    EXPECT_EQ(err2, tinyxml2::XML_SUCCESS);
    EXPECT_NE(doc2.RootElement(), nullptr);
}

TEST_F(CallFopenTest_277, LoadFile_ValidXml_ReturnsSuccess_277) {
    fs::path dir = MakeTempDir_277();
    fs::path inPath = dir / "valid_277.xml";
    WriteTextFile_277(inPath, "<root><a>text</a></root>");

    tinyxml2::XMLDocument doc;
    const tinyxml2::XMLError err = doc.LoadFile(inPath.string().c_str());

    EXPECT_EQ(err, tinyxml2::XML_SUCCESS);
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");
}

TEST_F(CallFopenTest_277, LoadFile_EmptyFile_ReturnsNonSuccess_277) {
    fs::path dir = MakeTempDir_277();
    fs::path inPath = dir / "empty_277.xml";
    WriteTextFile_277(inPath, "");

    tinyxml2::XMLDocument doc;
    const tinyxml2::XMLError err = doc.LoadFile(inPath.string().c_str());

    // Observable behavior: empty file should not parse as a successful XML document.
    EXPECT_NE(err, tinyxml2::XML_SUCCESS);
}

#if defined(GTEST_HAS_DEATH_TEST) && GTEST_HAS_DEATH_TEST
// If tinyxml2 is built with assertions enabled, passing nullptr where a filepath is required
// may trigger an assert. This is an observable "exceptional" behavior via the public interface.
TEST_F(CallFopenTest_277, LoadFile_Nullptr_TriggersDeathInAssertBuilds_277) {
#ifndef NDEBUG
    tinyxml2::XMLDocument doc;
    EXPECT_DEATH(
        {
            (void)doc.LoadFile(nullptr);
        },
        ""
    );
#else
    GTEST_SKIP() << "Skipping death test in release builds (NDEBUG defined).";
#endif
}
#endif

}  // namespace
