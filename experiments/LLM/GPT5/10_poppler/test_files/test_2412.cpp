// poppler-movie-test.cc
#include <gtest/gtest.h>

#include <cassert>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>

// -----------------------------------------------------------------------------
// Minimal GLib/GObject stubs (only what poppler-movie.cc needs)
// -----------------------------------------------------------------------------
using gboolean = int;
using gchar = char;

#ifndef G_MAXUINT64
#define G_MAXUINT64 (std::numeric_limits<std::uint64_t>::max())
#endif

static inline void g_assert(bool cond)
{
    // poppler uses g_assert() (abort on failure).
    assert(cond);
}

static inline gchar *g_strdup(const char *s)
{
    if (!s) {
        return nullptr;
    }
    const size_t n = std::strlen(s);
    auto *out = static_cast<gchar *>(std::malloc(n + 1));
    if (!out) {
        return nullptr;
    }
    std::memcpy(out, s, n + 1);
    return out;
}

struct GObject {
    virtual ~GObject() = default;
};

template <typename T>
static inline T *g_object_new(std::uintptr_t /*type*/, void * /*first_property_name*/)
{
    // Allocate zero-initialized memory like GObject instance often appears.
    // We keep it simple: just new T() and ensure fields are default-initialized.
    return new T();
}

// -----------------------------------------------------------------------------
// Minimal PopplerMovie object model compatible with the implementation snippet
// -----------------------------------------------------------------------------
enum PopplerMoviePlayMode {
    POPPLER_MOVIE_PLAY_MODE_ONCE = 0,
    POPPLER_MOVIE_PLAY_MODE_OPEN,
    POPPLER_MOVIE_PLAY_MODE_REPEAT,
    POPPLER_MOVIE_PLAY_MODE_PALINDROME,
};

struct PopplerMovie : public GObject {
    gchar *filename = nullptr;
    gboolean need_poster = 0;
    gboolean show_controls = 0;
    PopplerMoviePlayMode mode = POPPLER_MOVIE_PLAY_MODE_ONCE;
    gboolean synchronous_play = 0;
    double volume = 0.0;
    double rate = 0.0;
    std::uint64_t start = 0;
    std::uint64_t duration = 0;
    unsigned short rotation_angle = 0;
    int width = 0;
    int height = 0;

    ~PopplerMovie() override
    {
        std::free(filename);
    }
};

#define POPPLER_TYPE_MOVIE (static_cast<std::uintptr_t>(0xC0FFEEu))
#define POPPLER_MOVIE(obj) (reinterpret_cast<PopplerMovie *>(obj))

// -----------------------------------------------------------------------------
// Minimal Poppler core stubs used by _poppler_movie_new
// -----------------------------------------------------------------------------
class GooString {
public:
    explicit GooString(std::string s) : s_(std::move(s)) {}
    const char *c_str() const { return s_.c_str(); }
    void set(std::string s) { s_ = std::move(s); }

private:
    std::string s_;
};

class Object {
public:
    enum class Kind { None, Ref, Stream, Other };

    Object() : kind_(Kind::None) {}
    explicit Object(Kind k) : kind_(k) {}

    bool isRef() const { return kind_ == Kind::Ref; }
    bool isStream() const { return kind_ == Kind::Stream; }

private:
    Kind kind_;
};

namespace MovieActivationParameters {
enum MovieRepeatMode { repeatModeOnce = 0, repeatModeOpen = 1, repeatModeRepeat = 2, repeatModePalindrome = 3 };
} // namespace MovieActivationParameters

struct MovieActivationParametersStruct {
    struct MovieTime {
        unsigned long units = 0;
        int units_per_second = 0;
    };

    MovieTime start;
    MovieTime duration;
    double rate = 0.0;
    bool synchronousPlay = false;
    MovieActivationParameters::MovieRepeatMode repeatMode = MovieActivationParameters::repeatModeOnce;
    bool showControls = false;
};

class Movie {
public:
    Movie() = default;

    const MovieActivationParametersStruct *getActivationParameters() const { return &MA_; }
    const GooString *getFileName() const { return filename_.get(); }
    bool getShowPoster() const { return showPoster_; }
    Object getPoster() const { return poster_; }
    unsigned short getRotationAngle() const { return rotationAngle_; }
    void getAspect(int *widthA, int *heightA) const
    {
        if (widthA) *widthA = aspectW_;
        if (heightA) *heightA = aspectH_;
    }

    // Helpers for tests to configure the fake Movie:
    void setFileName(std::string s) { filename_ = std::make_unique<GooString>(std::move(s)); }
    void setShowPoster(bool v) { showPoster_ = v; }
    void setPoster(Object o) { poster_ = o; }
    MovieActivationParametersStruct &activation() { return MA_; }
    void setRotationAngle(unsigned short a) { rotationAngle_ = a; }
    void setAspect(int w, int h)
    {
        aspectW_ = w;
        aspectH_ = h;
    }

private:
    unsigned short rotationAngle_ = 0;
    Object poster_;
    bool showPoster_ = false;
    MovieActivationParametersStruct MA_;
    std::unique_ptr<GooString> filename_;
    int aspectW_ = 0;
    int aspectH_ = 0;
};

// -----------------------------------------------------------------------------
// Include the implementation under test (as provided in prompt)
// -----------------------------------------------------------------------------
PopplerMovie *_poppler_movie_new(const Movie *poppler_movie)
{
    PopplerMovie *movie;
    g_assert(poppler_movie != nullptr);
    movie = POPPLER_MOVIE(g_object_new<PopplerMovie>(POPPLER_TYPE_MOVIE, nullptr));
    movie->filename = g_strdup(poppler_movie->getFileName()->c_str());
    if (poppler_movie->getShowPoster()) {
        Object tmp = poppler_movie->getPoster();
        movie->need_poster = (!tmp.isRef() && !tmp.isStream());
    }
    movie->show_controls = poppler_movie->getActivationParameters()->showControls;
    switch (poppler_movie->getActivationParameters()->repeatMode) {
    case MovieActivationParameters::repeatModeOnce:
        movie->mode = POPPLER_MOVIE_PLAY_MODE_ONCE;
        break;
    case MovieActivationParameters::repeatModeOpen:
        movie->mode = POPPLER_MOVIE_PLAY_MODE_OPEN;
        break;
    case MovieActivationParameters::repeatModeRepeat:
        movie->mode = POPPLER_MOVIE_PLAY_MODE_REPEAT;
        break;
    case MovieActivationParameters::repeatModePalindrome:
        movie->mode = POPPLER_MOVIE_PLAY_MODE_PALINDROME;
        break;
    }
    movie->synchronous_play = poppler_movie->getActivationParameters()->synchronousPlay;
    movie->volume = poppler_movie->getActivationParameters()->volume / 100.0;
    movie->rate = poppler_movie->getActivationParameters()->rate;
    if (poppler_movie->getActivationParameters()->start.units_per_second > 0 &&
        poppler_movie->getActivationParameters()->start.units <= G_MAXUINT64 / 1000000000) {
        movie->start = 1000000000ULL * poppler_movie->getActivationParameters()->start.units /
                       poppler_movie->getActivationParameters()->start.units_per_second;
    } else {
        movie->start = 0ULL;
    }
    if (poppler_movie->getActivationParameters()->duration.units_per_second > 0 &&
        poppler_movie->getActivationParameters()->duration.units <= G_MAXUINT64 / 1000000000) {
        movie->duration = 1000000000ULL * poppler_movie->getActivationParameters()->duration.units /
                          poppler_movie->getActivationParameters()->duration.units_per_second;
    } else {
        movie->duration = 0ULL;
    }
    movie->rotation_angle = poppler_movie->getRotationAngle();
    poppler_movie->getAspect(&movie->width, &movie->height);
    return movie;
}

// -----------------------------------------------------------------------------
// Tests
// -----------------------------------------------------------------------------
class PopplerMovieNewTest_2412 : public ::testing::Test {
protected:
    static void DestroyMovie(PopplerMovie *m) { delete m; }
};

TEST_F(PopplerMovieNewTest_2412, NullInputDeath_2412)
{
    ASSERT_DEATH(
        {
            PopplerMovie *m = _poppler_movie_new(nullptr);
            (void)m;
        },
        "");
}

TEST_F(PopplerMovieNewTest_2412, CopiesFilenameAndIsIndependent_2412)
{
    Movie src;
    src.setFileName("video.mp4");

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);
    ASSERT_NE(m->filename, nullptr);
    EXPECT_STREQ(m->filename, "video.mp4");

    // Ensure g_strdup produced an independent copy (changing source should not change movie).
    src.setFileName("changed.avi");
    EXPECT_STREQ(m->filename, "video.mp4");

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, PosterFlagWhenShowPosterFalseLeavesDefault_2412)
{
    Movie src;
    src.setFileName("a.mov");
    src.setShowPoster(false);
    // Even if a poster object exists, it should not be consulted when showPoster is false.
    src.setPoster(Object(Object::Kind::Other));

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);

    // With our zero-init/new defaults, need_poster should remain false.
    EXPECT_EQ(m->need_poster, 0);

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, PosterFlagWhenShowPosterTrueAndPosterIsRef_2412)
{
    Movie src;
    src.setFileName("a.mov");
    src.setShowPoster(true);
    src.setPoster(Object(Object::Kind::Ref));

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);
    EXPECT_EQ(m->need_poster, 0);

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, PosterFlagWhenShowPosterTrueAndPosterIsStream_2412)
{
    Movie src;
    src.setFileName("a.mov");
    src.setShowPoster(true);
    src.setPoster(Object(Object::Kind::Stream));

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);
    EXPECT_EQ(m->need_poster, 0);

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, PosterFlagWhenShowPosterTrueAndPosterIsNeitherRefNorStream_2412)
{
    Movie src;
    src.setFileName("a.mov");
    src.setShowPoster(true);
    src.setPoster(Object(Object::Kind::Other));

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);
    EXPECT_NE(m->need_poster, 0);

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, CopiesControlsSyncVolumeRate_2412)
{
    Movie src;
    src.setFileName("b.mov");
    src.activation().showControls = true;
    src.activation().synchronousPlay = true;
    src.activation().volume = 25.0;
    src.activation().rate = 1.5;

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);

    EXPECT_NE(m->show_controls, 0);
    EXPECT_NE(m->synchronous_play, 0);
    EXPECT_DOUBLE_EQ(m->volume, 0.25);
    EXPECT_DOUBLE_EQ(m->rate, 1.5);

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, RepeatModeMapping_AllModes_2412)
{
    Movie src;
    src.setFileName("c.mov");

    // once
    src.activation().repeatMode = MovieActivationParameters::repeatModeOnce;
    {
        PopplerMovie *m = _poppler_movie_new(&src);
        ASSERT_NE(m, nullptr);
        EXPECT_EQ(m->mode, POPPLER_MOVIE_PLAY_MODE_ONCE);
        DestroyMovie(m);
    }

    // open
    src.activation().repeatMode = MovieActivationParameters::repeatModeOpen;
    {
        PopplerMovie *m = _poppler_movie_new(&src);
        ASSERT_NE(m, nullptr);
        EXPECT_EQ(m->mode, POPPLER_MOVIE_PLAY_MODE_OPEN);
        DestroyMovie(m);
    }

    // repeat
    src.activation().repeatMode = MovieActivationParameters::repeatModeRepeat;
    {
        PopplerMovie *m = _poppler_movie_new(&src);
        ASSERT_NE(m, nullptr);
        EXPECT_EQ(m->mode, POPPLER_MOVIE_PLAY_MODE_REPEAT);
        DestroyMovie(m);
    }

    // palindrome
    src.activation().repeatMode = MovieActivationParameters::repeatModePalindrome;
    {
        PopplerMovie *m = _poppler_movie_new(&src);
        ASSERT_NE(m, nullptr);
        EXPECT_EQ(m->mode, POPPLER_MOVIE_PLAY_MODE_PALINDROME);
        DestroyMovie(m);
    }
}

TEST_F(PopplerMovieNewTest_2412, StartAndDurationComputedWhenUnitsPerSecondPositiveAndWithinLimit_2412)
{
    Movie src;
    src.setFileName("d.mov");

    src.activation().start.units = 2;
    src.activation().start.units_per_second = 1;
    src.activation().duration.units = 3;
    src.activation().duration.units_per_second = 2;

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);

    EXPECT_EQ(m->start, 2000000000ULL);              // 1e9 * 2 / 1
    EXPECT_EQ(m->duration, 1500000000ULL);           // 1e9 * 3 / 2

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, StartAndDurationZeroWhenUnitsPerSecondNonPositive_2412)
{
    Movie src;
    src.setFileName("e.mov");

    src.activation().start.units = 123;
    src.activation().start.units_per_second = 0;
    src.activation().duration.units = 456;
    src.activation().duration.units_per_second = -7;

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);

    EXPECT_EQ(m->start, 0ULL);
    EXPECT_EQ(m->duration, 0ULL);

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, StartAndDurationZeroWhenUnitsOverflowGuardTriggers_2412)
{
    Movie src;
    src.setFileName("f.mov");

    const std::uint64_t limit = G_MAXUINT64 / 1000000000ULL;

    // Just above the limit should trip the guard and force 0.
    src.activation().start.units = static_cast<unsigned long>(limit + 1);
    src.activation().start.units_per_second = 1;

    src.activation().duration.units = static_cast<unsigned long>(limit + 1);
    src.activation().duration.units_per_second = 1;

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);

    EXPECT_EQ(m->start, 0ULL);
    EXPECT_EQ(m->duration, 0ULL);

    DestroyMovie(m);
}

TEST_F(PopplerMovieNewTest_2412, CopiesRotationAngleAndAspect_2412)
{
    Movie src;
    src.setFileName("g.mov");
    src.setRotationAngle(270);
    src.setAspect(640, 360);

    PopplerMovie *m = _poppler_movie_new(&src);
    ASSERT_NE(m, nullptr);

    EXPECT_EQ(m->rotation_angle, 270);
    EXPECT_EQ(m->width, 640);
    EXPECT_EQ(m->height, 360);

    DestroyMovie(m);
}