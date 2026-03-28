// TEST_ID 548
// Unit tests for Exiv2::FileIo (basicio.cpp / basicio.hpp)
// Focus: observable RAII/destructor safety + basic open/close/path behaviors.
// Constraints respected: black-box testing only via public interface.

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

namespace {

class FileIoTest_548 : public ::testing::Test {
 protected:
  static fs::path MakeUniquePath(const std::string& stem) {
    const auto base = fs::temp_directory_path();
    const auto uniq = stem + "_" + std::to_string(::testing::UnitTest::GetInstance()->random_seed()) + "_" +
                      std::to_string(reinterpret_cast<std::uintptr_t>(&stem));
    return base / (uniq + ".bin");
  }

  static void WriteFile(const fs::path& p, const std::string& bytes) {
    std::ofstream os(p, std::ios::binary | std::ios::trunc);
    ASSERT_TRUE(os.is_open());
    os.write(bytes.data(), static_cast<std::streamsize>(bytes.size()));
    os.close();
  }
};

}  // namespace

TEST_F(FileIoTest_548, DestructorOnUnopenedInstanceDoesNotThrow_548) {
  const fs::path p = MakeUniquePath("exiv2_fileio_unopened");
  // Ensure no file exists (should be fine either way).
  std::error_code ec;
  fs::remove(p, ec);

  EXPECT_NO_THROW({
    Exiv2::FileIo io(p.string());
    // Do not open; destructor must still be safe (basicio.cpp shows ~FileIo calls close()).
  });
}

TEST_F(FileIoTest_548, CloseAfterOpenMakesIsopenFalse_548) {
  const fs::path p = MakeUniquePath("exiv2_fileio_close");
  WriteFile(p, "abc");

  Exiv2::FileIo io(p.string());

  // Use the interface: "open()" returns int; typical Exiv2 convention is 0 on success.
  const int open_rc = io.open();
  EXPECT_EQ(0, open_rc);
  EXPECT_TRUE(io.isopen());

  EXPECT_NO_THROW({
    (void)io.close();
  });
  EXPECT_FALSE(io.isopen());

  // Boundary/idempotence: calling close again should not crash and should remain not-open.
  EXPECT_NO_THROW({
    (void)io.close();
  });
  EXPECT_FALSE(io.isopen());

  std::error_code ec;
  fs::remove(p, ec);
}

TEST_F(FileIoTest_548, DestructorAfterOpenDoesNotThrow_548) {
  const fs::path p = MakeUniquePath("exiv2_fileio_dtor_open");
  WriteFile(p, "hello");

  EXPECT_NO_THROW({
    Exiv2::FileIo io(p.string());
    const int open_rc = io.open();
    EXPECT_EQ(0, open_rc);
    EXPECT_TRUE(io.isopen());
    // No explicit close; destructor should handle it safely.
  });

  std::error_code ec;
  fs::remove(p, ec);
}

TEST_F(FileIoTest_548, SetPathUpdatesReportedPath_548) {
  const fs::path p1 = MakeUniquePath("exiv2_fileio_path1");
  const fs::path p2 = MakeUniquePath("exiv2_fileio_path2");
  WriteFile(p1, "x");
  WriteFile(p2, "y");

  Exiv2::FileIo io(p1.string());

  // Observable behavior: path() should reflect current configured path.
  // (Some platforms/implementations may normalize; so we assert it ends with filename.)
  const std::string initial = io.path();
  EXPECT_TRUE(initial.find(p1.filename().string()) != std::string::npos);

  io.setPath(p2.string());
  const std::string updated = io.path();
  EXPECT_TRUE(updated.find(p2.filename().string()) != std::string::npos);

  std::error_code ec;
  fs::remove(p1, ec);
  fs::remove(p2, ec);
}

TEST_F(FileIoTest_548, OpenNonexistentFileIsObservableAsFailure_548) {
  const fs::path p = MakeUniquePath("exiv2_fileio_nonexistent");
  std::error_code ec;
  fs::remove(p, ec);
  ASSERT_FALSE(fs::exists(p));

  Exiv2::FileIo io(p.string());
  const int open_rc = io.open();

  // Black-box observable expectations:
  // - Either open_rc indicates failure, or isopen() stays false, or error() becomes non-zero.
  // We avoid assuming a specific error code, only that failure is observable somehow.
  const bool failure_observed = (open_rc != 0) || (!io.isopen()) || (io.error() != 0);
  EXPECT_TRUE(failure_observed);

  // Ensure state is not "open" on a path that doesn't exist.
  EXPECT_FALSE(io.isopen());
}