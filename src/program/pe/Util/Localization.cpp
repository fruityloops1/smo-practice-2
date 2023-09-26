#include "pe/Util/Localization.h"
#include "al/Library/String/StringUtil.h"
#include "pe/Menu/UserConfig.h"

namespace pe {

struct MsgEntry {
    const char* msgId;
    const char* msgContents[3];
};

constexpr MsgEntry sLocalizationData[] {
    { "false",
        { "No",
            "いいえ",
            "Nein" } },
    { "true",
        { "Yes",
            "はい",
            "Ja" } },

    { "keybinds",
        { "Keybinds",
            "キーバインド",
            "Tastenkürzel" } },
    { "settings",
        { "Settings",
            "設定 (せってい)",
            "Einstellungen" } },

    { "dpadup",
        { "D-Pad up",
            "ディーパッド 上",
            "D-Pad up" } },
    { "dpaddown",
        { "D-Pad down",
            "ディーパッド 下",
            "D-Pad down" } },
    { "dpadright",
        { "D-Pad right",
            "ディーパッド 右",
            "D-Pad right" } },
    { "dpadleft",
        { "D-Pad left",
            "ディーパッド 左",
            "D-Pad left" } },

    { "action0",
        { "None",
            "なし",
            "Keine" } },
    { "action1",
        { "Restart Scene",
            "シーンをリスタートする",
            "Szenen-Neustart" } },
    { "action2",
        { "Save Position",
            "セーブ位置",
            "Position Speichern" } },
    { "action3",
        { "Load Position",
            "ロード位置",
            "Position Laden" } },
};

const char* getLocalizedString(const char* msg)
{
    for (const MsgEntry entry : sLocalizationData) {
        if (al::isEqualString(msg, entry.msgId))
            return entry.msgContents[(int)getConfig()->currentLanguage];
    }

    return "NULL";
}

} // namespace pe
