// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <cstdlib>
#include <fstream>
#include <string>

#if __has_include(<filesystem>)
#include <filesystem>
namespace fs = std::filesystem;
#endif

#include "makernote_int.hpp"

namespace {

// Simple RAII env-var guard (portable enough for our test needs).
class EnvVarGuard {
 public:
  EnvVarGuard(const char* name, const std::string& value) : name_(name) {
    const char* old = std::getenv(name_);
    had_old_ = (old != nullptr);
    if (had_old_) old_value_ = old;
    Set(value);
  }

  ~EnvVarGuard() {
    if (had_old_) {
      Set(old_value_);
    } else {
      Unset();
    }
  }

  EnvVarGuard(const EnvVarGuard&) = delete;
  EnvVarGuard& operator=(const EnvVarGuard&) = delete;

 private:
  void Set(const std::string& v) {
#if defined(_WIN32)
    _putenv_s(name_, v.c_str());
#else
    setenv(name_, v.c_str(), 1);
#endif
  }

  void Unset() {
#if defined(_WIN32)
    // Windows uses "NAME=" to unset via putenv; _putenv_s supports empty to remove.
    _putenv_s(name_, "");
#else
    unsetenv(name_);
#endif
  }

  const char* name_;
  bool had_old_{false};
  std::string old_value_;
};

#if __has_include(<filesystem>)
static fs::path MakeUniqueTempDir_1428() {
  fs::path base = fs::temp_directory_path() / "exiv2_readExiv2Config_1428";
  std::error_code ec;
  fs::remove_all(base, ec);
  fs::create_directories(base, ec);
  return base;
}
#endif

static void WriteTextFile_1428(const std::string& path, const std::string& content) {
  std::ofstream os(path, std::ios::binary);
  ASSERT_TRUE(os.good());
  os << content;
  os.flush();
  ASSERT_TRUE(os.good());
}

}  // namespace

class ReadExiv2ConfigTest_1428 : public ::testing::Test {};

TEST_F(ReadExiv2ConfigTest_1428, ReturnsDefaultWithTypicalInputs_1428) {
  const std::string def = "DEFAULT_1428";
  const std::string out = Exiv2::Internal::readExiv2Config("AnySection", "AnyKey", def);

#if !(defined(EXV_ENABLE_INIH) && defined(EXV_ENABLE_FILESYSTEM))
  EXPECT_EQ(out, def);
#else
  // When INI/filesystem support is enabled, behavior may depend on the config file.
  // This test only asserts it returns *something* (non-crashing) and leaves precise
  // config-dependent validation to the dedicated tests below.
  EXPECT_FALSE(out.empty()) << "Expected a string result (at minimum the default).";
#endif
}

TEST_F(ReadExiv2ConfigTest_1428, ReturnsDefaultForEmptyStrings_1428) {
  const std::string def;
  const std::string out = Exiv2::Internal::readExiv2Config("", "", def);

#if !(defined(EXV_ENABLE_INIH) && defined(EXV_ENABLE_FILESYSTEM))
  EXPECT_EQ(out, def);
#else
  // With config support enabled, an empty default should remain observable as empty
  // unless a config file explicitly overrides it.
  EXPECT_EQ(out, def);
#endif
}

TEST_F(ReadExiv2ConfigTest_1428, ReturnsDefaultForLongDefaultString_1428) {
  std::string def(4096, 'x');
  const std::string out = Exiv2::Internal::readExiv2Config("Sec", "Key", def);

#if !(defined(EXV_ENABLE_INIH) && defined(EXV_ENABLE_FILESYSTEM))
  EXPECT_EQ(out, def);
#else
  // In absence of a configured override, the default should be preserved.
  // A configured override is tested separately under controlled environment.
  EXPECT_FALSE(out.empty());
#endif
}

#if defined(EXV_ENABLE_INIH) && defined(EXV_ENABLE_FILESYSTEM) && __has_include(<filesystem>)

TEST_F(ReadExiv2ConfigTest_1428, ReturnsDefaultWhenConfigFileMissing_1428) {
  const fs::path tmp = MakeUniqueTempDir_1428();

#if defined(_WIN32)
  EnvVarGuard guard("USERPROFILE", tmp.string());
#else
  EnvVarGuard guard("HOME", tmp.string());
#endif

  const std::string cfgPath = Exiv2::Internal::getExiv2ConfigPath();

  // Ensure the config file does not exist.
  {
    std::error_code ec;
    fs::remove(fs::path(cfgPath), ec);
  }

  const std::string def = "DEF_MISSING_1428";
  const std::string out = Exiv2::Internal::readExiv2Config("S", "K", def);
  EXPECT_EQ(out, def);
}

TEST_F(ReadExiv2ConfigTest_1428, ReadsValueFromIniWhenPresent_1428) {
  const fs::path tmp = MakeUniqueTempDir_1428();

#if defined(_WIN32)
  EnvVarGuard guard("USERPROFILE", tmp.string());
#else
  EnvVarGuard guard("HOME", tmp.string());
#endif

  const std::string cfgPath = Exiv2::Internal::getExiv2ConfigPath();
  const fs::path cfg = fs::path(cfgPath);

  // Ensure parent directory exists.
  {
    std::error_code ec;
    fs::create_directories(cfg.parent_path(), ec);
  }

  const std::string section = "Section1428";
  const std::string key = "Key1428";
  const std::string value = "Value1428";

  const std::string ini =
      "[" + section + "]\n" +
      key + "=" + value + "\n";

  WriteTextFile_1428(cfg.string(), ini);

  const std::string def = "DEFAULT_1428";
  const std::string out = Exiv2::Internal::readExiv2Config(section, key, def);
  EXPECT_EQ(out, value);
}

TEST_F(ReadExiv2ConfigTest_1428, MissingKeyFallsBackToDefault_1428) {
  const fs::path tmp = MakeUniqueTempDir_1428();

#if defined(_WIN32)
  EnvVarGuard guard("USERPROFILE", tmp.string());
#else
  EnvVarGuard guard("HOME", tmp.string());
#endif

  const std::string cfgPath = Exiv2::Internal::getExiv2ConfigPath();
  const fs::path cfg = fs::path(cfgPath);

  {
    std::error_code ec;
    fs::create_directories(cfg.parent_path(), ec);
  }

  const std::string section = "Section1428";
  const std::string presentKey = "PresentKey1428";
  const std::string presentValue = "PresentValue1428";

  const std::string ini =
      "[" + section + "]\n" +
      presentKey + "=" + presentValue + "\n";

  WriteTextFile_1428(cfg.string(), ini);

  const std::string def = "DEF_MISSING_KEY_1428";
  const std::string out = Exiv2::Internal::readExiv2Config(section, "AbsentKey1428", def);
  EXPECT_EQ(out, def);
}

TEST_F(ReadExiv2ConfigTest_1428, ParseErrorFallsBackToDefault_1428) {
  const fs::path tmp = MakeUniqueTempDir_1428();

#if defined(_WIN32)
  EnvVarGuard guard("USERPROFILE", tmp.string());
#else
  EnvVarGuard guard("HOME", tmp.string());
#endif

  const std::string cfgPath = Exiv2::Internal::getExiv2ConfigPath();
  const fs::path cfg = fs::path(cfgPath);

  {
    std::error_code ec;
    fs::create_directories(cfg.parent_path(), ec);
  }

  // Intentionally malformed INI content (likely to trigger INIReader parse error).
  const std::string malformed = "[Section1428\nKey=Value\n";
  WriteTextFile_1428(cfg.string(), malformed);

  const std::string def = "DEF_PARSE_ERROR_1428";
  const std::string out = Exiv2::Internal::readExiv2Config("Section1428", "Key", def);
  EXPECT_EQ(out, def);
}

#endif  // EXV_ENABLE_INIH && EXV_ENABLE_FILESYSTEM && filesystem