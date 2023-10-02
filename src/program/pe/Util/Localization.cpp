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

    {
        "hacks",
        { "Hacks",
            "ハックス",
            "Hacks" },
    },
    { "timer",
        { "Timer",
            "タイマー",
            "Timer" } },
    { "keybinds",
        { "Keybinds",
            "キーバインド",
            "Tastenkürzel" } },
    { "settings",
        { "Settings",
            "設定 (せってい)",
            "Einstellungen" } },

    { "position",
        { "Position",
            "位置",
            "Position" } },
    { "fontsize",
        { "Font Size",
            "フォントサイズ",
            "Schriftgröße" } },

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
    { "wheel1",
        { "Wheel 1",
            "ホイール 1",
            "Rad 1" } },
    { "wheel2",
        { "Wheel 2",
            "ホイール 2",
            "Rad 2" } },
    { "wheel3",
        { "Wheel 3",
            "ホイール 3",
            "Rad 3" } },
    { "wheel4",
        { "Wheel 4",
            "ホイール 4",
            "Rad 4" } },
    { "wheel5",
        { "Wheel 5",
            "ホイール 5",
            "Rad 5" } },
    { "wheel6",
        { "Wheel 6",
            "ホイール 6",
            "Rad 6" } },
    { "wheel7",
        { "Wheel 7",
            "ホイール 7",
            "Rad 7" } },
    { "wheel8",
        { "Wheel 8",
            "ホイール 8",
            "Rad 8" } },

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
    { "action4",
        { "Respawn Chest Moons",
            "リスポーンチェスト ムーンズ",
            "Respawn Truhen-Monde" } },

    { "shinerefresh",
        { "Gray Moon Refresh",
            "グレイ ムーン リフレッシュ",
            "Graue Monde erneuern" } }
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
