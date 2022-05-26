#pragma once

#define DEBUG 
#define WEB_INTERFACE

#ifdef DEBUG
#define NUMBER_OF_SLOTS 1
#else
#define RELEASE_CLI
#define NUMBER_OF_SLOTS 8
#endif

