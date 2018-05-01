/**
 * Copyright 2015 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
/**
 * @file ParodusInternal.h
 *
 * @description This file is used to manage internal functions of parodus
 *
 */
#ifndef _PARODUSINTERNAL_H_
#define _PARODUSINTERNAL_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "math.h"
#include <ctype.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cJSON.h>
#include <nopoll.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <wrp-c.h>

#include "parodus_log.h"
/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/
#define UNUSED(x) (void )(x)
#define NANOMSG_SOCKET_TIMEOUT_MSEC                      2000

#ifndef TEST
#define FOREVER()   1
#else
extern int numLoops;
#define FOREVER()   numLoops--
#endif

/*----------------------------------------------------------------------------*/
/*                               Data Structures                              */
/*----------------------------------------------------------------------------*/

typedef struct ParodusMsg__
{
	noPollMsg * msg;
	void * payload;
	size_t len;
	struct ParodusMsg__ *next;
} ParodusMsg;

// Used in token.c to get jwt from dns server
typedef struct {
	const char *rr_ptr;
	int rr_len;
} rr_rec_t;

//------------ Used in comnection.c -----------------
#define SERVER_ADDR_LEN 256
#define PORT_LEN 8

typedef struct {
  int allow_insecure;
  char server_addr[SERVER_ADDR_LEN];
  char port[PORT_LEN];
} server_t;

typedef struct {
  server_t defaults;	// from command line
  server_t jwt;		// from jwt endpoint claim
  server_t redirect;	// from redirect response to
			//  nopoll_conn_wait_until_connection_ready
} server_list_t;

//---- Used in connection.c for expire timer
typedef struct {
  int running;
  struct timespec start_time;
  struct timespec end_time;
} expire_timer_t;

//--- Used in connection.c for backoff delay timer
typedef struct {
  int max_delay;
  int delay;
} backoff_timer_t;


/*----------------------------------------------------------------------------*/
/*                            File Scoped Variables                           */
/*----------------------------------------------------------------------------*/
extern ParodusMsg *ParodusMsgQ;
int numLoops;
/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

int checkHostIp(char * serverIP);

void parStrncpy(char *destStr, const char *srcStr, size_t destSize);

char* getWebpaConveyHeader();

#ifdef __cplusplus
}
#endif
    

#endif

