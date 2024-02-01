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
            "No",
            "Nein" } },
    { "true",
        { "Yes",
            "Yes",
            "Ja" } },

    {
        "hacks",
        { "Hacks",
            "チート",
            "Hacks" },
    },
    { "timer",
        { "Timer",
            "タイマー",
            "Timer" } },
    { "inputdisplay",
        { "Input Display",
            "入力表示",
            "Input Display" } },
    { "keybinds",
        { "Keybinds",
            "キー設定",
            "Tastenkürzel" } },
    { "stage",
        { "Stages",
            "ステージ",
            "Level" } },
    { "settings",
        { "Settings",
            "詳細設定",
            "Einstellungen" } },
    { "actions",
        { "Actions",
            "アクション",
            "Aktionen" } },

    { "position",
        { "Position",
            "配置",
            "Position" } },
    { "fontsize",
        { "Font Size",
            "フォントサイズ",
            "Schriftgröße" } },

    { "dpadup",
        { "D-Pad up",
            "十字キー 上",
            "D-Pad up" } },
    { "dpaddown",
        { "D-Pad down",
            "十字キー 下",
            "D-Pad down" } },
    { "dpadright",
        { "D-Pad right",
            "十字キー 右",
            "D-Pad right" } },
    { "dpadleft",
        { "D-Pad left",
            "十字キー 左",
            "D-Pad left" } },
    { "rsl",
        { "Rstick + Left",
            "Rstick + Left",
            "Rstick + Left" } },
    { "rsr",
        { "Rstick + Right",
            "Rstick + Right",
            "Rstick + Right" } },
    { "zlzr",
        { "ZL + ZR",
            "ZL + ZR",
            "ZL + ZR" } },
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
            "Reload Scene",
            "Szenen-Neustart" } },
    { "action2",
        { "Previous Scene",
            "Previous Scene",
            "Vorherige Szene" } },
    { "action3",
        { "Save Position",
            "位置をセーブ",
            "Position Speichern" } },
    { "action4",
        { "Load Position",
            "位置をロード",
            "Position Laden" } },
    { "action5",
        { "Start Timer",
            "タイマースタート",
            "Timer Starten" } },
    { "action6",
        { "Stop Timer",
            "タイマーストップ",
            "Timer Beenden" } },
    { "action7",
        { "Reset Timer",
            "タイマーリセット",
            "Timer-Reset" } },
    { "action8",
        { "Next Wiggler Pattern",
            "メカハナ 次の乱数",
            "Nächstes Wiggler-Muster" } },
    { "action9",
        { "Previous Wiggler Pattern",
            "メカハナ 前の乱数",
            "Vorheriges Wiggler-Muster" } },
    { "action10",
        { "Life-Up Heart",
            "ライフUPハート",
            "1-UP Herz" } },
    { "action11",
        { "Heal Mario",
            "Heal Mario",
            "Mario Heilen" } },
    { "action12",
        { "Add 1000 Coins",
            "Add 1000 Coins",
            "+1000 Münzen" } },
    { "action13",
        { "Subtract 1000 Coins",
            "Subtract 1000 Coins",
            "-1000 Münzen" } },

    { "grayshinerefresh",
        { "Gray Moon Refresh",
            "Gray Moon Refresh",
            "Graue Monde erneuern" } },
    { "shinerefresh",
        { "Moon Refresh",
            "Moon Refresh",
            "Monde erneuern" } },
    { "bgmdisable",
        { "Disable BGM",
            "BGMを無効にする",
            "Hintergrundmusik deaktivieren" } },
    { "alwaysenablewarps",
        { "Always enable warps",
            "常にワープを有効化",
            "Immer Warps aktivieren" } },
    { "disableautosave",
        { "Autosave",
            "オートセーブ",
            "Autosave" } },

    { "scenario", { "Scenario", "シナリオ", "Szenario" } },
    { "go", { "Go", "行く", "Los" } },

    { "timerstart",
        { "Timer Start Event",
            "タイマースタート",
            "Timer Start-Event" } },
    { "timerend",
        { "Timer End Event",
            "タイマーストップ",
            "Timer Ende-Event" } },
    { "timersplit",
        { "Split",
            "スプリット",
            "Split" } },
    { "timer0",
        { "None",
            "なし",
            "Keins" } },
    { "timer1",
        { "Moon Grab",
            "ムーンに触れた瞬間",
            "Mond-Berührung" } },
    { "timer2",
        { "Moon Tick",
            "ムーンがカウントされた瞬間",
            "Mond-Anzeige" } },

    { "wheeltime",
        { "Wheel Activation Time (frames)",
            "ホイール認識時間",
            "Rad-Aktivierungszeit (Frames)" } },
    { "wheelstick",
        { "Wheel Activation Stick",
            "ホイールLR切り替え",
            "Rad-Aktivierungsstick" } },

    { "left",
        { "Left",
            "L",
            "Links" } },
    { "right",
        { "Right",
            "R",
            "Rechts" } },

    { "mofumofupattern",
        { "Wiggler Pattern",
            "メカハナの乱数",
            "Wiggler-Muster" } }
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