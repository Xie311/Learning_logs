/** @file
 *  @brief MAVLink comm protocol generated from HEATBEAT.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_HEATBEAT_H
#define MAVLINK_HEATBEAT_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_HEATBEAT.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_HEATBEAT_XML_HASH -3675143436597506105

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_HEATBEAT

// ENUM DEFINITIONS



// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS


// base include



#if MAVLINK_HEATBEAT_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {}
# define MAVLINK_MESSAGE_NAMES {}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_HEATBEAT_H
