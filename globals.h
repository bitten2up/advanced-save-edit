typedef uint8_t   u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t    s8;
typedef int16_t  s16;
typedef int32_t  s32;
typedef int64_t  s64;

typedef u8  bool8;
typedef u16 bool16;
typedef u32 bool32;

#define MAX_PLAYER_NAME_LENGTH 6
#define NUM_CHARACTERS 5

#define PLAYER_NAME_END_CHAR 0xFFFF

#define NUM_MULTIPLAYER_SCORES 10
#define MAX_MULTIPLAYER_SCORE  99

#define TIME_RECORDS_PER_COURSE 3
#define NUM_COURSE_ZONES   7
#define ACTS_PER_ZONE      4

struct MultiplayerScore {
    u32 playerId;
    u16 playerName[MAX_PLAYER_NAME_LENGTH];

    bool8 slotFilled;

    u8 wins;
    u8 losses;
    u8 draws;
};

struct TimeRecords {
    u16 table[NUM_CHARACTERS][NUM_COURSE_ZONES][ACTS_PER_ZONE][TIME_RECORDS_PER_COURSE];
};
