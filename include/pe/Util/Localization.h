#pragma once

namespace pe {

enum class PeepaLanguage {
    English,
    Japanese,
    German
};

PeepaLanguage& getLanguage();
const char* getLocalizedString(const char* msg);

} // namespace pe
