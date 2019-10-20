#pragma once

// Audit log
#define MSG_COMDELETE            4000
#define MSG_COMADD               4001
#define MSG_COMMODIFY            4002
#define MSG_CMDSTATUSACQCHGD     4005
#define MSG_CMDOPSTARTED         4006
#define MSG_CMDOPENDED           4007
#define MSG_SERVICESTARTED       4010
#define MSG_SERVICESTOPPED       4011
#define MSG_NEWAGTNOTIFIED       4015
#define MSG_SVRINFOUPDATED       4016

// Command
#define MSG_COMMANDNOTEXIST      4020
#define MSG_NOCOMMANDREQUEST     4022
#define MSG_NOCOMMANDNAME        4023
#define MSG_COMNAMELENGTHERR     4024
#define MSG_COMSCRIPTLENERR      4025
#define MSG_FILENAMELENERR       4026
#define MSG_FILENAMEFBDNCHAR     4027
#define MSG_DUPCMDNAME           4028

// Server Info
#define MSG_NOSVRINFOREQUEST     4040
#define MSG_NOPOLLINGINTVL       4041
#define MSG_NOSAINTVL            4042
#define MSG_INVALIDPOINTVL       4043
#define MSG_INVALIDSVINTVL       4044

// Common error message
#define MSG_NO_ELEM_IN_REQUEST   4201
#define MSG_STRING_LEN_ERROR     4202
#define MSG_NOREQUEST            4203
#define MSG_NO_EXEC_RIGHT        4204
