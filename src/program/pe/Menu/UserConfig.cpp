#include "pe/Menu/UserConfig.h"
#include "helpers/fsHelper.h"
#include "pe/Menu/Menu.h"

namespace pe {

constexpr const char sUserConfigPath[] = "sd:/PeepaUserConfig.bin";

static UserConfig* sConfig = nullptr;

UserConfig*& getConfig()
{
    return sConfig;
}

void loadConfig()
{
    if (!FsHelper::isFileExist(sUserConfigPath)) {
        saveConfig();
        return;
    }

    FsHelper::LoadData data;
    data.path = sUserConfigPath;
    FsHelper::loadFileFromPath(data);
    if (data.buffer != nullptr && data.bufSize == sizeof(UserConfig)) {
        UserConfig* configData = reinterpret_cast<UserConfig*>(data.buffer);
        *sConfig = *configData;
    }
}

void saveConfig()
{
    FsHelper::writeFileToPath(reinterpret_cast<void*>(sConfig), sizeof(UserConfig), sUserConfigPath);
}

} // namespace pe
