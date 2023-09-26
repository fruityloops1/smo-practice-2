#pragma once

namespace pe {

enum class PeepaLanguage {
    English,
    Japanese,
    German
};

const char* getLocalizedString(const char* msg);

} // namespace pe
