#ifndef USB_H_
#define USB_H_

#include "define.h"
#include "ftd2xx.h"

FT_STATUS ouvertLien(FT_HANDLE *carte);
FT_STATUS fermerLien(FT_HANDLE *carte);

#endif