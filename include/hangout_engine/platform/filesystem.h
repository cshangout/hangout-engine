#pragma once

#include <filesystem>

namespace HE {
    using Path = std::filesystem::path;

    class Filesystem {
    private:
    public:
        static inline Path GetRootPath() {
            return std::filesystem::current_path();
        }

        static inline Path GetAssetPath() {
            return GetRootPath() /= "assets";
        }
    };
}
