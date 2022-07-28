#pragma once

#include <QString>

#define PRODUCTION 0
#define DEVELOPMENT 1

//TODO: Move to global config
#define LAUNCH_MODE DEVELOPMENT

#if LAUNCH_MODE == PRODUCTION
    const QString DATABASE_NAME = "mapp-prod";
    const QString HOST = "localhost";
    const QString ROOT_USER = "root";
    const QString ROOT_PASSWORD = "S9kTZm~LG";
#else
    const QString DATABASE_NAME = "mapp-test";
    const QString HOST = "localhost";
    const QString ROOT_USER = "root";
    const QString ROOT_PASSWORD = "S9kTZm~LG";
#endif
    const QString CONNECTION_NAME = "mapp";
