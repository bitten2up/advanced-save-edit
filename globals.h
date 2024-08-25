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

#define TRUE  1
#define FALSE 0

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

// Used in struc_30008A0
typedef struct {
    u32 playerId;
    u16 playerName[MAX_PLAYER_NAME_LENGTH];

    bool8 slotFilled;

    u8 wins;
    u8 losses;
    u8 draws;
} VsRecords;

// Used in struc_3000CF0
typedef struct {
    u8 unk0;
    u8 wins;
    u8 draws;
    u8 losses;
    u32 unk4;
    u16 playerName[MAX_PLAYER_NAME_LENGTH];
} VsRecords2;

typedef struct {
    u16 table[NUM_COURSE_ZONES][ACTS_PER_ZONE][TIME_RECORDS_PER_COURSE];
} TimeRecords;
typedef struct {
    u32 magicNumber; // default: 0x47544E4C ("LNTG")
    u32 v4;

    // @NOTE This contains mostly the same information as struc_3000530, but
    // some values are missing or in a different order.
    u32 id; // | 0x08
    u16 playerName[MAX_PLAYER_NAME_LENGTH];
    u8 v18; // Don't know why this byte is here, but it's correct

    u8 unlockedCharacters; // 0x19 |
    u8 unlockedZones; // 0x1A |
    u8 continueZone; // 0x1B | Zone the player continues at on startup after character
                     // select (0 to 6)
    u8 v1C;

    u16 chaoCount[7]; // | v1D - 0x2B
    u8 specialKeys[7]; // Each counter counts for 1 Act | 0x2C - 0x32
    u8 unlockedStages[9]; // | 0x33-0x3B
    u8 collectedEmeralds; // Stored bitwise: x7654321b | 0x3C

    // NOTE: These are different from
    //       struct struc_3000530, why?
    u8 v3D; // v33: struc_3000530
    u8 collectedMedals[9][4]; // 0x3E | v37: struc_3000530
    u16 v62; // v34?: struc_3000530
    u8 vsWins; // v60?: struc_3000530

    u8 vsLosses;
    u8 vsDraws;
    u8 v67;

    VsRecords2 vsRecords[10]; // 0x68

    TimeRecords timeRecords[7][4][5]; // 0x130

    u8 buttonConfig[3];
    u8 v363;
    u8 v364;
    u8 v365;
    u8 language;
    u8 v367; // INVESTIGATE: v367 might be unused.

    u32 checksum; // v368 | Checksum? In sub_800212C() this value is calculated and show that
              // it HAS to be the last member of the struct
} SaveSectorData;
