#include <genesis.h>

#include "gfx.h"
#include "music.h"

// 7.5 FPS = 40, 12 FPS = 25, 15 FPS = 20, 20 FPS = 15, 25 FPS = 12  //
#define PAL_FRAME_DELAY 12
#define NTSC_FRAME_DELAY 10
#define MUSIC_START_FRAME 1

static void nextFrame();
static void processMap(Map* map, u16 baseInd, u16 xt, u16 yt);

static void joyEvent(u16 joy, u16 changed, u16 state);

static void hint();
static void vint();
static void doSync();

const Image *images[] =
{
    &frame0,
    &frame1,
    &frame2,
    &frame3,
    &frame4,
    &frame5,
    &frame6,
    &frame7,
    &frame8,
    &frame9,
    &frame10,
    &frame11,
    &frame12,
    &frame13,
    &frame14,
    &frame15,
    &frame16,
    &frame17,
    &frame18,
    &frame19,
    &frame20,
    &frame21,
    &frame22,
    &frame23,
    &frame24,
    &frame25,
    &frame26,
    &frame27,
    &frame28,
    &frame29,
    &frame30,
    &frame31,
    &frame32,
    &frame33,
    &frame34,
    &frame35,
    &frame36,
    &frame37,
    &frame38,
    &frame39,
    &frame40,
    &frame41,
    &frame42,
    &frame43,
    &frame44,
    &frame45,
    &frame46,
    &frame47,
    &frame48,
    &frame49,
    &frame50,
    &frame51,
    &frame52,
    &frame53,
    &frame54,
    &frame55,
    &frame56,
    &frame57,
    &frame58,
    &frame59,
    &frame60,
    &frame61,
    &frame62,
    &frame63,
    &frame64,
    &frame65,
    &frame66,
    &frame67,
    &frame68,
    &frame69,
    &frame70,
    &frame71,
    &frame72,
    &frame73,
    &frame74,
    &frame75,
    &frame76,
    &frame77,
    &frame78,
    &frame79,
    &frame80,
    &frame81,
    &frame82,
    &frame83,
    &frame84,
    &frame85,
    &frame86,
    &frame87,
    &frame88,
    &frame89,
    &frame90,
    &frame91,
    &frame92,
    &frame93,
    &frame94,
    &frame95,
    &frame96,
    &frame97,
    &frame98,
    &frame99,
    &frame100,
    &frame101,
    &frame102,
    &frame103,
    &frame104,
    &frame105,
    &frame106,
    &frame107,
    &frame108,
    &frame109,
    &frame110,
    &frame111,
    &frame112,
    &frame113,
    &frame114,
    &frame115,
    &frame116,
    &frame117,
    &frame118,
    &frame119,
    &frame120,
    &frame121,
    &frame122,
    &frame123,
    &frame124,
    &frame125,
    &frame126,
    &frame127,
    &frame128,
    &frame129,
    &frame130,
    &frame131,
    &frame132,
    &frame133,
    &frame134,
    &frame135,
    &frame136,
    &frame137,
    &frame138,
    &frame139,
    &frame140,
    &frame141,
    &frame142,
    &frame143,
    &frame144,
    &frame145,
    &frame146,
    &frame147,
    &frame148,
    &frame149,
    &frame150,
    &frame151,
    &frame152,
    &frame153,
    &frame154,
    &frame155,
    &frame156,
    &frame157,
    &frame158,
    &frame159,
    &frame160,
    &frame161,
    &frame162,
    &frame163,
    &frame164,
    &frame165,
    &frame166,
    &frame167,
    &frame168,
    &frame169,
    &frame170,
    &frame171,
    &frame172,
    &frame173,
    &frame174,
    &frame175,
    &frame176,
    &frame177,
    &frame178,
    &frame179,
    &frame180,
    &frame181,
    &frame182,
    &frame183,
    &frame184,
    &frame185,
    &frame186,
    &frame187,
    &frame188,
    &frame189,
    &frame190,
    &frame191,
    &frame192,
    &frame193,
    &frame194,
    &frame195,
    &frame196,
    &frame197,
    &frame198,
    &frame199,
    &frame200,
    &frame201,
    &frame202,
    &frame203,
    &frame204,
    &frame205,
    &frame206,
    &frame207,
    &frame208,
    &frame209,
    &frame210,
    &frame211,
    &frame212,
    &frame213,
    &frame214,
    &frame215,
    &frame216,
    &frame217,
    &frame218,
    &frame219,
    &frame220,
    &frame221,
    &frame222,
    &frame223,
    &frame224,
    &frame225,
    &frame226,
    &frame227,
    &frame228,
    &frame229,
    &frame230,
    &frame231,
    &frame232,
    &frame233,
    &frame234,
    &frame235,
    &frame236,
    &frame237,
    &frame238,
    &frame239,
    &frame240,
    &frame241,
    &frame242,
    &frame243,
    &frame244,
    &frame245,
    &frame246,
    &frame247,
    &frame248,
    &frame249,
    &frame250,
    &frame251,
    &frame252,
    &frame253,
    &frame254,
    &frame255,
    &frame256,
    &frame257,
    &frame258,
    &frame259,
    &frame260,
    &frame261,
    &frame262,
    &frame263,
    &frame264,
    &frame265,
    &frame266,
    &frame267,
    &frame268,
    &frame269,
    &frame270,
    &frame271,
    &frame272,
    &frame273,
    &frame274,
    &frame275,
    &frame276,
    &frame277,
    &frame278,
    &frame279,
    &frame280,
    &frame281,
    &frame282,
    &frame283,
    &frame284,
    &frame285,
    &frame286,
    &frame287,
    &frame288,
    &frame289,
    &frame290,
    &frame291,
    &frame292,
    &frame293,
    &frame294,
    &frame295,
    &frame296,
    &frame297,
    &frame298,
    &frame299,
    &frame300,
    &frame301,
    &frame302,
    &frame303,
    &frame304,
    &frame305,
    &frame306,
    &frame307,
    &frame308,
    &frame309,
    &frame310,
    &frame311,
    &frame312,
    &frame313,
    &frame314,
    &frame315,
    &frame316,
    &frame317,
    &frame318,
    &frame319,
    &frame320,
    &frame321,
    &frame322,
    &frame323,
    &frame324,
    &frame325,
    &frame326,
    &frame327,
    &frame328,
    &frame329,
    &frame330,
    &frame331,
    &frame332,
    &frame333,
    &frame334,
    &frame335,
    &frame336,
    &frame337,
    &frame338,
    &frame339,
    &frame340,
    &frame341,
    &frame342,
    &frame343,
    &frame344,
    &frame345,
    &frame346,
    &frame347,
    &frame348,
    &frame349,
    &frame350,
    &frame351,
    &frame352,
    &frame353,
    &frame354,
    &frame355,
    &frame356,
    &frame357,
    &frame358,
    &frame359,
    &frame360,
    &frame361,
    &frame362,
    &frame363,
    &frame364,
    &frame365,
    &frame366,
    &frame367,
    &frame368,
    &frame369,
    &frame370,
    &frame371,
    &frame372,
    &frame373,
    &frame374,
    &frame375,
    &frame376,
    &frame377,
    &frame378,
    &frame379,
    &frame380,
    &frame381,
    &frame382,
    &frame383,
    &frame384,
    &frame385,
    &frame386,
    &frame387,
    &frame388,
    &frame389,
    &frame390,
    &frame391,
    &frame392,
    &frame393,
    &frame394,
    &frame395,
    &frame396,
    &frame397,
    &frame398,
    &frame399,
    &frame400,
    &frame401,
    &frame402,
    &frame403,
    &frame404,
    &frame405,
    &frame406,
    &frame407,
    &frame408,
    &frame409,
    &frame410,
    &frame411,
    &frame412,
    &frame413,
    &frame414,
    &frame415,
    &frame416,
    &frame417,
    &frame418,
    &frame419,
    &frame420,
    &frame421,
    &frame422,
    &frame423,
    &frame424,
    &frame425,
    &frame426,
    &frame427,
    &frame428,
    &frame429,
    &frame430,
    &frame431,
    &frame432,
    &frame433,
    &frame434,
    &frame435,
    &frame436,
    &frame437,
    &frame438,
    &frame439,
    &frame440,
    &frame441,
    &frame442,
    &frame443,
    &frame444,
    &frame445,
    &frame446,
    &frame447,
    &frame448,
    &frame449,
    &frame450,
    &frame451,
    &frame452,
    &frame453,
    &frame454,
    &frame455,
    &frame456,
    &frame457,
    &frame458,
    &frame459,
    &frame460,
    &frame461,
    &frame462,
    &frame463,
    &frame464,
    &frame465,
    &frame466,
    &frame467,
    &frame468,
    &frame469,
    &frame470,
    &frame471,
    &frame472,
    &frame473,
    &frame474,
    &frame475,
    &frame476,
    &frame477,
    &frame478,
    &frame479,
    &frame480,
    &frame481,
    &frame482,
    &frame483,
    &frame484,
    &frame485,
    &frame486,
    &frame487,
    &frame488,
    &frame489,
    &frame490,
    &frame491,
    &frame492,
    &frame493,
    &frame494,
    &frame495,
    &frame496,
    &frame497,
    &frame498,
    &frame499,
    &frame500,
    &frame501,
    &frame502,
    &frame503,
    &frame504,
    &frame505,
    &frame506,
    &frame507,
    &frame508,
    &frame509,
    &frame510,
    &frame511,
    &frame512,
    &frame513,
    &frame514,
    &frame515,
    &frame516,
    &frame517,
    &frame518,
    &frame519,
    &frame520,
    &frame521,
    &frame522,
    &frame523,
    &frame524,
    &frame525,
    &frame526,
    &frame527,
    &frame528,
    &frame529,
    &frame530,
    &frame531,
    &frame532,
    &frame533,
    &frame534,
    &frame535,
    &frame536,
    &frame537,
    &frame538,
    &frame539,
    &frame540,
    &frame541,
    &frame542,
    &frame543,
    &frame544,
    &frame545,
    &frame546,
    &frame547,
    &frame548,
    &frame549,
    &frame550,
    &frame551,
    &frame552,
    &frame553,
    &frame554,
    &frame555,
    &frame556,
    &frame557,
    &frame558,
    &frame559,
    &frame560,
    &frame561,
    &frame562,
    &frame563,
    &frame564,
    &frame565,
    &frame566,
    &frame567,
    &frame568,
    &frame569,
    &frame570,
    &frame571,
    &frame572,
    &frame573,
    &frame574,
    &frame575,
    &frame576,
    &frame577,
    &frame578,
    &frame579,
    &frame580,
    &frame581,
    &frame582,
    &frame583,
    &frame584,
    &frame585,
    &frame586,
    &frame587,
    &frame588,
    &frame589,
    &frame590,
    &frame591,
    &frame592,
    &frame593,
    &frame594,
    &frame595,
    &frame596,
    &frame597,
    &frame598,
    &frame599,
    &frame600,
    &frame601,
    &frame602,
    &frame603,
    &frame604,
    &frame605,
    &frame606,
    &frame607,
    &frame608,
    &frame609,
    &frame610,
    &frame611,
    &frame612,
    &frame613,
    &frame614,
    &frame615,
    &frame616,
    &frame617,
    &frame618,
    &frame619,
    &frame620,
    &frame621,
    &frame622,
    &frame623,
    &frame624,
    &frame625,
    &frame626,
    &frame627,
    &frame628,
    &frame629,
    &frame630,
    &frame631,
    &frame632,
    &frame633,
    &frame634,
    &frame635,
    &frame636,
    &frame637,
    &frame638,
    &frame639,
    &frame640,
    &frame641,
    &frame642,
    &frame643,
    &frame644,
    &frame645,
    &frame646,
    &frame647,
    &frame648,
    &frame649,
    &frame650,
    &frame651,
    &frame652,
    &frame653,
    &frame654,
    &frame655,
    &frame656,
    &frame657,
    &frame658,
    &frame659,
    &frame660,
    &frame661,
    &frame662,
    &frame663,
    &frame664,
    &frame665,
    &frame666,
    &frame667,
    &frame668,
    &frame669,
    &frame670,
    &frame671,
    &frame672,
    &frame673,
    &frame674,
    &frame675,
    &frame676,
    &frame677,
    &frame678,
    &frame679,
    &frame680,
    &frame681,
    &frame682,
    &frame683,
    &frame684,
    &frame685,
    &frame686,
    &frame687,
    &frame688,
    &frame689,
    &frame690,
    &frame691,
    &frame692,
    &frame693,
    &frame694,
    &frame695,
    &frame696,
    &frame697,
    &frame698,
    &frame699,
    &frame700,
    &frame701,
    &frame702,
    &frame703,
    &frame704,
    &frame705,
    &frame706,
    &frame707,
    &frame708,
    &frame709,
    &frame710,
    &frame711,
    &frame712,
    &frame713,
    &frame714,
    &frame715,
    &frame716,
    &frame717,
    &frame718,
    &frame719,
    &frame720,
    &frame721,
    &frame722,
    &frame723,
    &frame724,
    &frame725,
    &frame726,
    &frame727,
    &frame728,
    &frame729,
    &frame730,
    &frame731,
    &frame732,
    &frame733,
    &frame734,
    &frame735,
    &frame736,
    &frame737,
    &frame738,
    &frame739,
    &frame740
};

const u16 noOfFrames = sizeof(images) / sizeof(Image*);

u16 ind;
TileSet* tileset;
Map* map;
u16 indBase;
u16 vpos;
vu16 frameDone;
s32 frameDelay;
u32 lastGetTick = 0;

int main()
{
    // disable VInt alignment
    SYS_setVIntAligned(FALSE);
    SYS_setHIntCallback(hint);
    SYS_setVIntCallback(vint);

    // set no limit to DMA
    DMA_setMaxTransferSize(0);
    // disable auto flush for DMA queue
    DMA_setAutoFlush(FALSE);

    // disable interrupt when accessing VDP
    SYS_disableInts();

    // initialization
    VDP_setScreenWidth320();

    // reset plan configuration
    VDP_setAPlanAddress(0xC000);
    VDP_setBPlanAddress(0xE000);
    VDP_setSpriteListAddress(0xB000);
    VDP_setHScrollTableAddress(0xB800);
    // set plan size to 64x64
    VDP_setPlanSize(64, 64);

    // load background A
    ind = TILE_USERINDEX;
    VDP_drawImageEx(PLAN_A, &border, TILE_ATTR_FULL(PAL2, FALSE, FALSE, FALSE, ind), 0, 0, TRUE, TRUE);
    VDP_setPalette(PAL3, palette_grey);
    VDP_setTextPalette(PAL3);

    // we want hint on line 204
    VDP_setHIntCounter(204);
    // enable hint
    VDP_setHInterrupt(TRUE);

    if (IS_PALSYSTEM) {
        frameDelay = PAL_FRAME_DELAY;
    } else {
        frameDelay = NTSC_FRAME_DELAY;
    }

    // re-enable ints
    SYS_enableInts();

    ind += border.tileset->numTile;

    tileset = allocateTileSetEx(512);
    map = allocateMapEx(256 / 8, 200 / 8);
    indBase = ind;
    vpos = 0;
    frameDone = FALSE;

    JOY_setEventHandler(joyEvent);

    while(TRUE)
    {
        nextFrame();
    }

    return 0;
}

static void nextFrame()
{
    doSync();

    static u16 pal = PAL0;
    static u16 frame = 0;

    if (frame == MUSIC_START_FRAME) {
        SND_startPlay_PCM(sound, sizeof(sound), SOUND_RATE_11025, SOUND_PAN_CENTER, 0);
    }

    // sync (wait for frame to be sent to VDP)
    while(frameDone);

    SYS_disableInts();

    const Image *image = images[frame];
    const u16 numTile = image->tileset->numTile;

    // fix tile index if needed
    if ((ind + numTile) >= TILE_USERMAXINDEX) ind = indBase;

    // unpack tileset and tilemap
    unpackTileSet(image->tileset, tileset);
    unpackMap(image->map, map);

    // send to DMA queue
    DMA_queueDma(DMA_VRAM, (u32) tileset->tiles, ind * 32, numTile * 16, 2);
    processMap(map, TILE_ATTR_FULL(pal, FALSE, FALSE, FALSE, ind), 4, vpos + ((224 - 184) / (8 * 2)));
    DMA_queueDma(DMA_CRAM, (u32) image->palette->data, pal * 16 * 2, 16, 2);

    ind += numTile;
    pal ^= 1;
    vpos ^= 0x20;
    frame++;
    if (frame >= noOfFrames) frame = 0;

    frameDone = TRUE;

    // re-enable ints
    SYS_enableInts();
}

static void processMap(Map* map, u16 baseInd, u16 xt, u16 yt)
{
    u16* src = map->tilemap;
    const u16 w = map->w;
    u16 h = map->h;

    // set base index info into tilemap data
    u16 i = w * h;
    while(i--) *src++ += baseInd;

    src = map->tilemap;
    // initialize map VRAM destination address
    u16 adr = VDP_getBPlanAddress() + ((xt + (yt * 64)) * 2);

    // send map data through DMA queue
    while(h--)
    {
        DMA_queueDma(DMA_VRAM, (u32) src, adr, w, 2);
        src += w;
        adr += 64 * 2;
    }
}

static void doSync()
{
   u32 tick;
   s32 delta;
   s32 over;
   do {
        tick = getTick();
        delta = tick - lastGetTick;
        over = delta - frameDelay;
   }
   while (over < 0);
   lastGetTick = tick - over;
}

static void joyEvent(u16 joy, u16 changed, u16 state)
{
    //
}

static void hint()
{
    if (frameDone)
    {
        //VDP_setEnable(FALSE);
        DMA_flushQueue();
        VDP_setEnable(TRUE);

        VDP_setVerticalScroll(PLAN_B, (vpos ^ 0x20) * 8);
        VDP_showFPS(FALSE);

        frameDone = FALSE;
    }
}

static void vint()
{
    //

}
