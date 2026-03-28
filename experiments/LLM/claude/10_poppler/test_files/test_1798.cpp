#include <gtest/gtest.h>
#include <optional>
#include <string>
#include <filesystem>
#include <fstream>
#include <cstdlib>

// We test the function getDefaultFirefoxCertDB() which is static in the .cc file.
// To test it, we need to either:
// 1. Include the .cc file directly (since the function is static)
// 2. Or restructure. We'll include the .cc to get access to the static function.

// Note: Since the function is static (file-local linkage), we include the .cc file
// to make it available in this translation unit.
#include "poppler/NSSCryptoSignBackend.cc"

class GetDefaultFirefoxCertDBTest_1798 : public ::testing::Test {
protected:
    std::string testBasePath;
    std::string originalHome;
    bool hadHome = false;
#ifdef _WIN32
    std::string originalAppData;
    bool hadAppData = false;
#endif

    void SetUp() override {
        // Save original environment
#ifdef _WIN32
        const char *appdata = getenv("APPDATA");
        if (appdata) {
            hadAppData = true;
            originalAppData = appdata;
        }
#else
        const char *home = getenv("HOME");
        if (home) {
            hadHome = true;
            originalHome = home;
        }
#endif
        // Create a temporary directory for testing
        testBasePath = std::filesystem::temp_directory_path().string() + "/firefox_cert_test_1798";
        std::filesystem::remove_all(testBasePath);
        std::filesystem::create_directories(testBasePath);
    }

    void TearDown() override {
        // Restore original environment
#ifdef _WIN32
        if (hadAppData) {
            setenv("APPDATA", originalAppData.c_str(), 1);
        } else {
            unsetenv("APPDATA");
        }
#else
        if (hadHome) {
            setenv("HOME", originalHome.c_str(), 1);
        } else {
            unsetenv("HOME");
        }
#endif
        // Clean up test directory
        std::filesystem::remove_all(testBasePath);
    }

    void setEnvForTest(const std::string &basePath) {
#ifdef _WIN32
        setenv("APPDATA", basePath.c_str(), 1);
#else
        setenv("HOME", basePath.c_str(), 1);
#endif
    }

    std::string getFirefoxProfilesPath(const std::string &basePath) {
#ifdef _WIN32
        return basePath + "/Mozilla/Firefox/Profiles/";
#else
        return basePath + "/.mozilla/firefox/";
#endif
    }

    // Helper to create a profile directory with cert9.db
    void createProfileWithCert(const std::string &profilesPath, const std::string &profileName) {
        std::string profileDir = profilesPath + "/" + profileName;
        std::filesystem::create_directories(profileDir);
        std::string certPath = profileDir + "/cert9.db";
        std::ofstream ofs(certPath);
        ofs << "dummy cert data";
        ofs.close();
    }
};

// Test: When environment variable (HOME/APPDATA) is not set, should return empty
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsEmptyWhenEnvNotSet_1798) {
#ifdef _WIN32
    unsetenv("APPDATA");
#else
    unsetenv("HOME");
#endif
    auto result = getDefaultFirefoxCertDB();
    EXPECT_FALSE(result.has_value());
}

// Test: When firefox profiles directory does not exist, should return empty
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsEmptyWhenFirefoxDirNotExist_1798) {
    setEnvForTest(testBasePath);
    // Don't create the firefox profiles directory
    auto result = getDefaultFirefoxCertDB();
    EXPECT_FALSE(result.has_value());
}

// Test: When firefox profiles directory exists but is empty, should return empty
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsEmptyWhenNoProfiles_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::filesystem::create_directories(profilesPath);

    auto result = getDefaultFirefoxCertDB();
    EXPECT_FALSE(result.has_value());
}

// Test: When profile directories exist but none contain "default" in the name
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsEmptyWhenNoDefaultProfile_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::filesystem::create_directories(profilesPath);

    // Create a profile without "default" in the name
    createProfileWithCert(profilesPath, "abcxyz.release");

    auto result = getDefaultFirefoxCertDB();
    EXPECT_FALSE(result.has_value());
}

// Test: When a default profile exists with cert9.db, should return that directory
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsDirWhenDefaultProfileWithCertExists_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::filesystem::create_directories(profilesPath);

    std::string profileName = "abc123.default";
    createProfileWithCert(profilesPath, profileName);

    auto result = getDefaultFirefoxCertDB();
    ASSERT_TRUE(result.has_value());
    // The returned path should contain the profile name
    EXPECT_NE(result->find("default"), std::string::npos);
    EXPECT_NE(result->find(profileName), std::string::npos);
}

// Test: When a default profile directory exists but has no cert9.db, should return empty
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsEmptyWhenDefaultProfileNoCert_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::string profileDir = profilesPath + "/abc123.default";
    std::filesystem::create_directories(profileDir);
    // Don't create cert9.db

    auto result = getDefaultFirefoxCertDB();
    EXPECT_FALSE(result.has_value());
}

// Test: When multiple default profiles exist, should return the one with the latest cert9.db
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsLatestWhenMultipleDefaultProfiles_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::filesystem::create_directories(profilesPath);

    // Create first default profile
    std::string profileName1 = "older.default";
    createProfileWithCert(profilesPath, profileName1);

    // Wait a tiny bit and create second default profile (to get a later write time)
    // We'll use filesystem time manipulation instead
    std::string profileName2 = "newer.default-release";
    createProfileWithCert(profilesPath, profileName2);

    // Make sure the second one has a later timestamp
    std::string certPath1 = profilesPath + "/" + profileName1 + "/cert9.db";
    std::string certPath2 = profilesPath + "/" + profileName2 + "/cert9.db";

    // Set the first cert to an older time
    auto oldTime = std::filesystem::last_write_time(certPath1);
    std::filesystem::last_write_time(certPath1, oldTime - std::chrono::hours(24));

    auto result = getDefaultFirefoxCertDB();
    ASSERT_TRUE(result.has_value());
    // Should return the newer one
    EXPECT_NE(result->find(profileName2), std::string::npos);
}

// Test: When "default" appears in subdirectory name (e.g., "default-release"), should still match
TEST_F(GetDefaultFirefoxCertDBTest_1798, MatchesDefaultRelease_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::filesystem::create_directories(profilesPath);

    std::string profileName = "xyz.default-release";
    createProfileWithCert(profilesPath, profileName);

    auto result = getDefaultFirefoxCertDB();
    ASSERT_TRUE(result.has_value());
    EXPECT_NE(result->find(profileName), std::string::npos);
}

// Test: cert9.db exists but is a directory, not a regular file - should not match
TEST_F(GetDefaultFirefoxCertDBTest_1798, ReturnsEmptyWhenCertIsDirectory_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::string profileDir = profilesPath + "/abc.default";
    std::filesystem::create_directories(profileDir + "/cert9.db"); // cert9.db as directory

    auto result = getDefaultFirefoxCertDB();
    EXPECT_FALSE(result.has_value());
}

// Test: Mix of matching and non-matching profiles
TEST_F(GetDefaultFirefoxCertDBTest_1798, IgnoresNonDefaultProfiles_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::filesystem::create_directories(profilesPath);

    // Non-default profile with cert
    createProfileWithCert(profilesPath, "abc.release");
    // Default profile with cert
    createProfileWithCert(profilesPath, "xyz.default");

    auto result = getDefaultFirefoxCertDB();
    ASSERT_TRUE(result.has_value());
    EXPECT_NE(result->find("xyz.default"), std::string::npos);
}

// Test: Profile is a file, not a directory (edge case) - should be skipped
TEST_F(GetDefaultFirefoxCertDBTest_1798, SkipsFilesInProfilesDir_1798) {
    setEnvForTest(testBasePath);
    std::string profilesPath = getFirefoxProfilesPath(testBasePath);
    std::filesystem::create_directories(profilesPath);

    // Create a file (not directory) with "default" in name
    std::string filePath = profilesPath + "/some.default";
    std::ofstream ofs(filePath);
    ofs << "not a directory";
    ofs.close();

    auto result = getDefaultFirefoxCertDB();
    EXPECT_FALSE(result.has_value());
}
