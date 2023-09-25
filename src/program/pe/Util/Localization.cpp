#include "pe/Util/Localization.h"
#include "al/Library/String/StringUtil.h"

namespace pe {

static PeepaLanguage sLanguage = PeepaLanguage::English; 

PeepaLanguage& getLanguage()
{
    return sLanguage;
}

struct MsgEntry {
    const char* msgId;
    const char* msgContents[3];
};

constexpr MsgEntry sLocalizationData[]
{
    {
        "teleport",
        {
            "Teleport",
            "テレポート",
            "Teleportieren"
        }
    }
};

const char* getLocalizedString(const char* msg)
{
    for (const MsgEntry entry : sLocalizationData)
    {
        if (al::isEqualString(msg, entry.msgId))
            return entry.msgContents[(int)sLanguage];
    }

    return "NULL";
}

} // namespace pe
