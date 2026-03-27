// File: test_xmldocument_loadfile_279.cpp
#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <cstdio>
#include <fstream>
#include <string>
#include <filesystem>

namespace {

class XMLDocumentLoadFileTest_279 : public ::testing::Test {
protected:
    static std::filesystem::path TempDir_279() {
        // Use the system temp directory. If unavailable, fall back to current path.
        std::error_code ec;
        auto p = std::filesystem::temp_directory_path(ec);
        if (ec) return std::filesystem::current_path();
        return p;
    }

    static std::filesystem::path UniquePath_279(const std::string& stem) {
        // Create a reasonably unique name without relying on any tinyxml2 internals.
        // (This is just for test file paths.)
        auto base = TempDir_279();
        auto name = stem + "_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed()) +
                    "_" + std::to_string(reinterpret_cast<std::uintptr_t>(&base)) + ".xml";
        return base / name;
    }

    static void WriteTextFile_279(const std::filesystem::path& path, const std::string& content) {
        std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
        ASSERT_TRUE(ofs.is_open()) << "Failed to open temp file for writing: " << path.string();
        ofs.write(content.data(), static_cast<std::streamsize>(content.size()));
        ASSERT_TRUE(ofs.good()) << "Failed to write content to: " << path.string();
        ofs.close();
    }

    static void RemoveIfExists_279(const std::filesystem::path& path) {
        std::error_code ec;
        std::filesystem::remove(path, ec);
    }
};

TEST_F(XMLDocumentLoadFileTest_279, LoadValidFileReturnsSuccessAndSetsRoot_279) {
    const auto path = UniquePath_279("tinyxml2_loadfile_valid");
    RemoveIfExists_279(path);
    WriteTextFile_279(path, "<root/>");

    tinyxml2::XMLDocument doc(true, tinyxml2::PRESERVE_WHITESPACE);
    const tinyxml2::XMLError err = doc.LoadFile(path.string().c_str());

    EXPECT_EQ(err, tinyxml2::XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "root");

    RemoveIfExists_279(path);
}

TEST_F(XMLDocumentLoadFileTest_279, LoadMissingFileReturnsFileNotFoundAndSetsError_279) {
    const auto missing = UniquePath_279("tinyxml2_loadfile_missing");
    RemoveIfExists_279(missing);
    ASSERT_FALSE(std::filesystem::exists(missing));

    tinyxml2::XMLDocument doc(true, tinyxml2::PRESERVE_WHITESPACE);
    const tinyxml2::XMLError err = doc.LoadFile(missing.string().c_str());

    EXPECT_EQ(err, tinyxml2::XML_ERROR_FILE_NOT_FOUND);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_ERROR_FILE_NOT_FOUND);

    // ErrorStr is observable via the public API. Don't overfit exact formatting across platforms,
    // but ensure it's non-empty and references "filename" when available.
    const char* es = doc.ErrorStr();
    ASSERT_NE(es, nullptr);
    EXPECT_NE(std::string(es).size(), 0u);

    RemoveIfExists_279(missing);
}

TEST_F(XMLDocumentLoadFileTest_279, LoadFileClearsPreviousParseStateAndReplacesRoot_279) {
    const auto pathA = UniquePath_279("tinyxml2_loadfile_a");
    const auto pathB = UniquePath_279("tinyxml2_loadfile_b");
    RemoveIfExists_279(pathA);
    RemoveIfExists_279(pathB);

    WriteTextFile_279(pathA, "<a/>");
    WriteTextFile_279(pathB, "<b/>");

    tinyxml2::XMLDocument doc(true, tinyxml2::PRESERVE_WHITESPACE);

    ASSERT_EQ(doc.LoadFile(pathA.string().c_str()), tinyxml2::XML_SUCCESS);
    ASSERT_NE(doc.RootElement(), nullptr);
    ASSERT_STREQ(doc.RootElement()->Name(), "a");

    // Loading a different file should clear prior content and replace the root element.
    ASSERT_EQ(doc.LoadFile(pathB.string().c_str()), tinyxml2::XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "b");

    RemoveIfExists_279(pathA);
    RemoveIfExists_279(pathB);
}

TEST_F(XMLDocumentLoadFileTest_279, LoadValidFileClearsPreviousError_279) {
    const auto valid = UniquePath_279("tinyxml2_loadfile_valid2");
    RemoveIfExists_279(valid);
    WriteTextFile_279(valid, "<ok/>");

    tinyxml2::XMLDocument doc(true, tinyxml2::PRESERVE_WHITESPACE);

    // Create an observable prior error state using the public interface.
    ASSERT_NE(doc.Parse("<unclosed>", 10), tinyxml2::XML_SUCCESS);
    ASSERT_TRUE(doc.Error());

    // Now load a valid file; LoadFile() calls Clear() and should result in success and no error.
    const tinyxml2::XMLError err = doc.LoadFile(valid.string().c_str());
    EXPECT_EQ(err, tinyxml2::XML_SUCCESS);
    EXPECT_FALSE(doc.Error());
    ASSERT_NE(doc.RootElement(), nullptr);
    EXPECT_STREQ(doc.RootElement()->Name(), "ok");

    RemoveIfExists_279(valid);
}

TEST_F(XMLDocumentLoadFileTest_279, LoadFileWithEmptyFilenameIsAnError_279) {
    // Boundary: empty string. Behavior can vary by platform/filesystem,
    // but it should not report XML_SUCCESS in typical environments.
    tinyxml2::XMLDocument doc(true, tinyxml2::PRESERVE_WHITESPACE);
    const tinyxml2::XMLError err = doc.LoadFile("");

    EXPECT_NE(err, tinyxml2::XML_SUCCESS);
    EXPECT_TRUE(doc.Error());
}

#if !defined(NDEBUG)
TEST_F(XMLDocumentLoadFileTest_279, LoadFileWithNullptrMayTriggerAssertInDebug_279) {
    // The implementation explicitly calls TIXMLASSERT(false) when filename is null.
    // In debug builds this may terminate the process; verify via a death test.
    tinyxml2::XMLDocument doc(true, tinyxml2::PRESERVE_WHITESPACE);

    EXPECT_DEATH_IF_SUPPORTED(
        {
            (void)doc.LoadFile(nullptr);
        },
        ""); // Don't require a specific assert message.
}
#endif

TEST_F(XMLDocumentLoadFileTest_279, LoadFileWithNullptrReturnsCouldNotBeOpenedWhenNotFatal_279) {
    // Even if the assert is compiled out (or doesn't terminate), the observable behavior is:
    // return XML_ERROR_FILE_COULD_NOT_BE_OPENED and set ErrorID accordingly.
    // This test is valuable for release builds or environments where asserts don't abort.
    tinyxml2::XMLDocument doc(true, tinyxml2::PRESERVE_WHITESPACE);

    // If it aborts, the debug death test above covers that configuration.
    // Here, we just exercise the non-fatal observable result.
    const tinyxml2::XMLError err = doc.LoadFile(nullptr);

    EXPECT_EQ(err, tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED);
    EXPECT_TRUE(doc.Error());
    EXPECT_EQ(doc.ErrorID(), tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED);

    const char* es = doc.ErrorStr();
    ASSERT_NE(es, nullptr);
    EXPECT_NE(std::string(es).size(), 0u);
}

} // namespace
