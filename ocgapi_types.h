/*
 * Copyright (C) 2019  Edoardo Lolletti (edo9300) and Dylam De La Torre (DyXel)
 * See version history for a full list of authors.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef OCGAPI_TYPES_H
#define OCGAPI_TYPES_H
#include <stdint.h>

#define OCG_VERSION_MAJOR 4
#define OCG_VERSION_MINOR 0

typedef enum OCG_LogTypes {
	OCG_LOG_TYPE_ERROR,
	OCG_LOG_TYPE_FROM_SCRIPT,
	OCG_LOG_TYPE_UNDEFINED
}OCG_LogTypes;

typedef enum OCG_DuelCreationStatus {
	OCG_DUEL_CREATION_SUCCESS,
	OCG_DUEL_CREATION_NO_OUTPUT,
	OCG_DUEL_CREATION_NOT_CREATED,
	OCG_DUEL_CREATION_NULL_DATA_READER,
	OCG_DUEL_CREATION_NULL_SCRIPT_READER
}OCG_DuelCreationStatus;

typedef enum OCG_DuelStatus {
	OCG_DUEL_STATUS_END,
	OCG_DUEL_STATUS_AWAITING,
	OCG_DUEL_STATUS_CONTINUE
}OCG_DuelStatus;

typedef void* OCG_Duel;

typedef struct OCG_CardData {
	uint32_t code;
	uint32_t alias;
	uint64_t setcode;
	uint32_t type;
	uint32_t level;
	uint32_t attribute;
	uint32_t race;
	int32_t attack;
	int32_t defense;
	uint32_t lscale;
	uint32_t rscale;
	uint32_t link_marker;
}OCG_CardData;

typedef struct OCG_Player {
	int startingLP;
	int startingDrawCount;
	int drawCountPerTurn;
}OCG_Player;

typedef int (*OCG_DataReader)(void* payload, int code, OCG_CardData* data);
typedef int (*OCG_ScriptReader)(void* payload, OCG_Duel duel, const char* name);
typedef void (*OCG_LogHandler)(void* payload, const char* string, int type);

typedef struct OCG_DuelOptions {
	uint32_t seed;
	int flags;
	OCG_Player team1;
	OCG_Player team2;
	OCG_DataReader cardReader;
	void* payload1; /* relayed to cardReader */
	OCG_ScriptReader scriptReader;
	void* payload2; /* relayed to scriptReader */
	OCG_LogHandler logHandler;
	void* payload3; /* relayed to errorHandler */
}OCG_DuelOptions;

typedef struct OCG_NewCardInfo {
	uint8_t team; /* either 0 or 1 */
	uint8_t duelist; /* index of original owner */
	uint32_t code;
	uint8_t con;
	uint32_t loc;
	uint32_t seq;
	uint32_t pos;
}OCG_NewCardInfo;

typedef struct OCG_QueryInfo {
	uint32_t flags;
	uint8_t con;
	uint32_t loc;
	uint32_t seq;
	uint32_t overlay_seq;
}OCG_QueryInfo;

#endif /* OCGAPI_TYPES_H */
