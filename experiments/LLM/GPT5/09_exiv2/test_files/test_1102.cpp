// =================================================================================================
// TEST_ID: 1102
// Unit tests for Exiv2::ImageFactory::getType(const std::string& path)
// File under test: ./TestProjects/exiv2/src/image.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdio>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#if __has_include(<filesystem>)
  #include <filesystem>
  namespace fs = std::filesystem;
#endif

#include "exiv2/basicio.hpp"
#include "exiv2/image.hpp"

namespace {

class ImageFactoryGetTypePathTest_1102 : public ::testing::Test {
 protected:
  struct TempFile {
    std::string path;
    bool created{false};

    ~TempFile() {
      if (created && !path.empty()) {
        std::remove(path.c_str());
      }
    }
  };

  static std::string UniqueTempPath(const char* suffix) {
#if __has_include(<filesystem>)
    const fs::path dir = fs::temp_directory_path();
    fs::path name = fs::path("exiv2_imgfactory_gettype_1102_") / fs::path("");
    // Build a reasonably unique filename without relying on platform-specific APIs.
    // (PID is not portable without extra headers; time+address is enough for unit tests.)
    const auto uniq =
        std::to_string(reinterpret_cast<std::uintptr_t>(&dir)) + "_" +
        std::to_string(static_cast<unsigned long long>(std::time(nullptr)));
    fs::path file = dir / (std::string("exiv2_imgfactory_gettype_1102_") + uniq + suffix);
    return file.string();
#else
    // Fallback: tmpnam (best-effort for test environments)
    char buf[L_tmpnam];
    std::tmpnam(buf);
    return std::string(buf) + suffix;
#endif
  }

  static TempFile MakeTempFile(const std::vector<unsigned char>& bytes, const char* suffix = ".bin") {
    TempFile tf;
    tf.path = UniqueTempPath(suffix);

    std::ofstream out(tf.path, std::ios::binary | std::ios::trunc);
    if (!out.is_open()) {
      return tf;
    }
    if (!bytes.empty()) {
      out.write(reinterpret_cast<const char*>(bytes.data()),
                static_cast<std::streamsize>(bytes.size()));
    }
    out.close();
    tf.created = true;
    return tf;
  }

  struct CallResult {
    bool threw{false};
    Exiv2::ImageType type{Exiv2::ImageType::none};
  };

  static CallResult CallGetTypeViaPath(Exiv2::ImageFactory& factory, const std::string& path) {
    CallResult r;
    try {
      r.type = factory.getType(path);
    } catch (...) {
      r.threw = true;
    }
    return r;
  }

  static CallResult CallGetTypeViaFileIo(Exiv2::ImageFactory& factory, const std::string& path) {
    CallResult r;
    try {
      Exiv2::FileIo io(path);
      r.type = factory.getType(io);
    } catch (...) {
      r.threw = true;
    }
    return r;
  }
};

}  // namespace

// -------------------------------------------------------------------------------------------------
// If filesystem support is disabled, the wrapper is defined to return ImageType::none.
// -------------------------------------------------------------------------------------------------
#ifndef EXV_ENABLE_FILESYSTEM

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemDisabled_ReturnsNoneForNonexistentPath_1102) {
  Exiv2::ImageFactory factory;
  EXPECT_EQ(factory.getType("this_file_should_not_exist_1102.img"), Exiv2::ImageType::none);
}

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemDisabled_ReturnsNoneForEmptyPath_1102) {
  Exiv2::ImageFactory factory;
  EXPECT_EQ(factory.getType(std::string()), Exiv2::ImageType::none);
}

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemDisabled_ReturnsNoneForArbitraryPathString_1102) {
  Exiv2::ImageFactory factory;
  EXPECT_EQ(factory.getType("C:\\not\\a\\real\\path\\1102"), Exiv2::ImageType::none);
  EXPECT_EQ(factory.getType("/definitely/not/a/real/path/1102"), Exiv2::ImageType::none);
}

#else  // EXV_ENABLE_FILESYSTEM

// -------------------------------------------------------------------------------------------------
// If filesystem support is enabled, getType(path) is a thin wrapper: it constructs FileIo(path)
// and returns getType(BasicIo&). We verify observable equivalence to the BasicIo overload without
// inferring internal detection logic.
// -------------------------------------------------------------------------------------------------

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemEnabled_DelegatesToBasicIoOverload_EmptyFile_1102) {
  auto tf = MakeTempFile({}, ".img");
  ASSERT_TRUE(tf.created);

  Exiv2::ImageFactory factory;
  const auto viaPath = CallGetTypeViaPath(factory, tf.path);
  const auto viaIo = CallGetTypeViaFileIo(factory, tf.path);

  ASSERT_EQ(viaPath.threw, viaIo.threw);
  if (!viaPath.threw) {
    EXPECT_EQ(viaPath.type, viaIo.type);
  }
}

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemEnabled_DelegatesToBasicIoOverload_RandomBytes_1102) {
  const std::vector<unsigned char> bytes = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77,
                                            0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
  auto tf = MakeTempFile(bytes, ".bin");
  ASSERT_TRUE(tf.created);

  Exiv2::ImageFactory factory;
  const auto viaPath = CallGetTypeViaPath(factory, tf.path);
  const auto viaIo = CallGetTypeViaFileIo(factory, tf.path);

  ASSERT_EQ(viaPath.threw, viaIo.threw);
  if (!viaPath.threw) {
    EXPECT_EQ(viaPath.type, viaIo.type);
  }
}

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemEnabled_DelegatesToBasicIoOverload_SmallSignatureLikeBytes_1102) {
  // Provide some “signature-like” bytes (e.g., JPEG SOI) but do NOT assert what type it is.
  // We only assert wrapper/path behavior matches the BasicIo overload.
  const std::vector<unsigned char> bytes = {0xFF, 0xD8, 0xFF, 0xE0, 0x00, 0x10, 'J', 'F', 'I', 'F', 0x00};
  auto tf = MakeTempFile(bytes, ".jpg");
  ASSERT_TRUE(tf.created);

  Exiv2::ImageFactory factory;
  const auto viaPath = CallGetTypeViaPath(factory, tf.path);
  const auto viaIo = CallGetTypeViaFileIo(factory, tf.path);

  ASSERT_EQ(viaPath.threw, viaIo.threw);
  if (!viaPath.threw) {
    EXPECT_EQ(viaPath.type, viaIo.type);
  }
}

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemEnabled_EmptyPath_BehavesSameAsDirectFileIo_1102) {
  // Boundary: empty path string. Behavior may be implementation-defined (throw or return something),
  // but the wrapper should behave consistently with directly constructing FileIo("") and calling
  // getType(BasicIo&).
  Exiv2::ImageFactory factory;

  const auto viaPath = CallGetTypeViaPath(factory, std::string());
  const auto viaIo = CallGetTypeViaFileIo(factory, std::string());

  ASSERT_EQ(viaPath.threw, viaIo.threw);
  if (!viaPath.threw) {
    EXPECT_EQ(viaPath.type, viaIo.type);
  }
}

TEST_F(ImageFactoryGetTypePathTest_1102, FilesystemEnabled_NonexistentPath_BehavesSameAsDirectFileIo_1102) {
  // Error case: nonexistent file. We do not assume whether this throws or returns ImageType::none;
  // we only require wrapper consistency with the BasicIo overload path via FileIo.
  const std::string missing = "this_file_should_not_exist_1102.img";

  Exiv2::ImageFactory factory;
  const auto viaPath = CallGetTypeViaPath(factory, missing);
  const auto viaIo = CallGetTypeViaFileIo(factory, missing);

  ASSERT_EQ(viaPath.threw, viaIo.threw);
  if (!viaPath.threw) {
    EXPECT_EQ(viaPath.type, viaIo.type);
  }
}

#endif  // EXV_ENABLE_FILESYSTEM