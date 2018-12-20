#include "util/ra_log.h"

RA_LOG ra_log(LOG_LEVEL);

void RA_LOG::exc(const char *cStrTemplate, ...) {
    if(ralm < ralmExc) return;
    char Buffer[0x400] = {'\0'};
    va_list args;
    va_start(args, cStrTemplate);
    vsprintf(Buffer, cStrTemplate, args);
    va_end(args);
    printf(cExc, Buffer);
}

void RA_LOG::err(const char *cStrTemplate, ...) {
    if(ralm < ralmErr) return;
    char Buffer[0x400] = {'\0'};
    va_list args;
    va_start(args, cStrTemplate);
    vsprintf(Buffer, cStrTemplate, args);
    va_end(args);
    printf(cErr, Buffer);
}

void RA_LOG::warn(const char *cStrTemplate, ...) {
    if(ralm < ralmWarn) return;
    char Buffer[0x400] = {'\0'};
    va_list args;
    va_start(args, cStrTemplate);
    vsprintf(Buffer, cStrTemplate, args);
    va_end(args);
    printf(cWarn, Buffer);
}

void RA_LOG::dbg(const char *cStrTemplate, ...) {
    if(ralm < ralmDebug) return;
    char Buffer[0x400] = {'\0'};
    va_list args;
    va_start(args, cStrTemplate);
    vsprintf(Buffer, cStrTemplate, args);
    va_end(args);
    printf(cDebug, Buffer);
}

void RA_LOG::log(const char *cStrTemplate, ...) {
    if(ralm < ralmLog) return;
    char Buffer[0x400] = {'\0'};
    va_list args;
    va_start(args, cStrTemplate);
    vsprintf(Buffer, cStrTemplate, args);
    va_end(args);
    printf(cLog, Buffer);
}

void RA_LOG::dtl(const char *cStrTemplate, ...) {
    if(ralm < ralmDetails) return;
    char Buffer[0x400] = {'\0'};
    va_list args;
    va_start(args, cStrTemplate);
    vsprintf(Buffer, cStrTemplate, args);
    va_end(args);
    printf(cDetails, Buffer);
}
