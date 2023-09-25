#include "pe/Menu/UserConfig.h"
#include "helpers/fsHelper.h"

namespace pe {

constexpr const char sUserConfigPath[] = "sd:/Peepa/UserConfig.bin";

static UserConfig sConfig;

UserConfig& getConfig()
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
    if (data.buffer != nullptr) {
        UserConfig* configData = reinterpret_cast<UserConfig*>(data.buffer);
        sConfig = *configData;
    }
}

void saveConfig()
{
    FsHelper::writeFileToPath(reinterpret_cast<void*>(&sConfig), sizeof(sConfig), sUserConfigPath);
}

} // namespace pe
