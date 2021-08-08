#ifndef __ASCII__
#define __ASCII__

#define COLOR_NONE       ""
#define COLOR_FG_BLACK   "\x1b[30;1m"
#define COLOR_FG_RED     "\x1b[31;1m"
#define COLOR_FG_GREEN   "\x1b[32;1m"
#define COLOR_FG_YELLOW  "\x1b[33;1m"
#define COLOR_FG_BLUE    "\x1b[34;1m"
#define COLOR_FG_MAGENTA "\x1b[35;1m"
#define COLOR_FG_CYAN    "\x1b[36;1m"
#define COLOR_FG_WHITE   "\x1b[37;1m"
#define COLOR_BG_BLACK   "\x1b[40;1m"
#define COLOR_BG_RED     "\x1b[41;1m"
#define COLOR_BG_GREEN   "\x1b[42;1m"
#define COLOR_BG_YELLOW  "\x1b[43;1m"
#define COLOR_BG_BLUE    "\x1b[44;1m"
#define COLOR_BG_MAGENTA "\x1b[45;1m"
#define COLOR_BG_CYAN    "\x1b[46;1m"
#define COLOR_BG_WHITE   "\x1b[47;1m"
#define COLOR_RESET      "\x1b[m"

struct ascii_logo {
  char* art;
  uint32_t width;
  uint32_t height;
  bool replace_blocks;
  char* color_ascii[8];
  char* color_text[2];
};

/*
 * Brief explanation:
 * C1, C2, ...: ColorN, gets replaced by printer.c with
 *              the color in ascii_logo->color_ascii[N]
 * CR:          Color reset, gets replaced by the reset color by printer.c
 */

#define ASCII_AMD \
"$C2          '###############             \
$C2             ,#############            \
$C2                      .####            \
$C2              #.      .####            \
$C2            :##.      .####            \
$C2           :###.      .####            \
$C2           #########.   :##            \
$C2           #######.       ;            \
$C1                                       \
$C1    ###     ###      ###   #######     \
$C1   ## ##    #####  #####   ##     ##   \
$C1  ##   ##   ### #### ###   ##      ##  \
$C1 #########  ###  ##  ###   ##      ##  \
$C1##       ## ###      ###   ##     ##   \
$C1##       ## ###      ###   #######     "

#define ASCII_INTEL \
"$C1                              ################                \
$C1                      #######                #######          \
$C1                 ####                              ####       \
$C1             ###                                     ####     \
$C1        ###                                             ###   \
$C1        ###                                             ###   \
$C1     #                    ###                ###        ###   \
$C1   ##   ###   #########   ######   ######    ###        ###   \
$C1  ##    ###   ###    ###  ###    ####  ####  ###        ###   \
$C1 ##     ###   ###    ###  ###    ###    ###  ###       ###    \
$C1##      ###   ###    ###  ###    ##########  ###     ####     \
$C1##      ###   ###    ###  ###    ###         ###   #####      \
$C1##       ##   ###    ###   #####  #########   ##  ###         \
$C1###                                                           \
$C1 ###                                                          \
$C1 ####                                        ####             \
$C1   #####                               ##########             \
$C1     ##########               ################                \
$C1         ###############################                      "

#define ASCII_SNAPD \
"              $C1@@$C2########               \
           $C1@@@@@$C2###########            \
     $C1@@  @@@@@$C2#################        \
   $C1@@@@@@@@@@$C2####################      \
  $C1@@@@@@@@@@@@$C2#####################    \
 $C1@@@@@@@@@@@@@@@$C2####################   \
 $C1@@@@@@@@@@@@@@@@@$C2###################  \
 $C1@@@@@@@@@@@@@@@@@@@@$C2################  \
    $C1@@@@@@@@@@@@@@@@@@@@$C2#############  \
       $C1@@@@@@@@@@@@@@@@@@$C2############  \
$C1@          @@@@@@@@@@@@@@@$C2###########  \
 $C1@@@@@       @@@@@@@@@@@@@$C2##########   \
  $C1@@@@@@@@@   @@@@@@@@@@@@$C2########     \
    $C1@@@@@@@@@  @@@@@@@@@@$C2#######       \
       $C1@@@@@@@@@@@@@@@@$C2#######         \
           $C1@@@@$C2###########             "

#define ASCII_MTK \
"$C1    ##  ## ######  ######  #     ### $C2@@@@@@ @@@@@@ @@  @@  \
$C1   ### ### #       #    #  #    ####   $C2@@   @      @@ @@   \
$C1  ######## # ###   #    #  #   ## ##   $C2@@   @ @@@  @@@@    \
$C1 ## ### ## #       #    #  #  ##  ##   $C2@@   @      @@ @@   \
$C1##  ##  ## ######  #####   # ##   ##   $C2@@   @@@@@@ @@  @@  "

#define ASCII_EXYNOS \
"$C2                      \
$C2                      \
$C2                      \
     $C1##$CR  $C1##$CR  $C1##$CR       \
       $C1##$CR  $C1##$CR         \
         $C1##$CR           \
       $C1##$CR  $C1##$CR         \
     $C1##$CR  $C1##$CR  $C1##$CR       \
$C2                      \
$C2     SAMSUNG          \
$C2     Exynos           \
$C2                      \
$C2                      "

#define ASCII_KIRIN \
"$C1                                #######              \
$C1    #####             ####################           \
$C1       ######################################        \
$C1         #######################################     \
$C1            #######################################  \
$C1              ##############################         \
$C1             ##########################              \
$C1          #########################                  \
$C1        ########################                     \
$C1     ########################                        \
$C1  #########################                          \
$C1#########################                            "

#define ASCII_BROADCOM \
"$C2                                            \
$C2             ################               \
$C2        ##########################          \
$C2     ################################       \
$C2   ################$C1@@@@$C2################     \
$C2  ################$C1@@@@@@$C2################    \
$C2 #################$C1@@@@@@$C2#################   \
$C2#################$C1@@@@@@@@$C2#################  \
$C2#################$C1@@@@@@@@$C2#################  \
$C2################$C1@@@@$C2##$C1@@@@$C2################  \
$C2################$C1@@@@$C2##$C1@@@@$C2################  \
$C2###############$C1@@@@$C2####$C1@@@@$C2###############  \
$C1 @@@@@@@@@@$C2####$C1@@@@$C2####$C1@@@@$C2####$C1@@@@@@@@@@   \
$C2  ######$C1@@@@@@@@@@$C2######$C1@@@@@@@@@@$C2######    \
$C2    ##################################      \
$C2      ##############################        \
$C2         ########################           \
$C2             ###############                \
$C2                                            "

#define ASCII_ARM \
"$C1   #####  ##   # #####  ## ####  ######   \
$C1 ###    ####   ###      ####  ###   ###   \
$C1###       ##   ###      ###    ##    ###  \
$C1 ###    ####   ###      ###    ##    ###  \
$C1  ######  ##   ###      ###    ##    ###  "

// jp2a --height=17 ibm.jpg
#define ASCII_IBM \
"######### ################   #########        #########  \
                                                         \
######### ##################  ##########    ##########   \
                                                         \
  #####      ######    ######   ####################     \
                                                         \
  #####      ##############     ####################     \
                                                         \
  #####      ######    ######   #####  ######  #####     \
                                                         \
######### ################## ########   ####   ########  \
                                                         \
######### ################   ########    ##    ########  "

typedef struct ascii_logo asciiL;

//                     ------------------------------------------------------------------------------------------------------
//                     | LOGO          | W | H | REPLACE | COLORS LOGO (>0 && <10)        | COLORS TEXT (=2)                |
//                     ------------------------------------------------------------------------------------------------------
asciiL logo_amd      = { ASCII_AMD,      39, 15, false, {COLOR_FG_WHITE, COLOR_FG_GREEN}, {COLOR_FG_WHITE, COLOR_FG_GREEN}  };
asciiL logo_intel    = { ASCII_INTEL,    62, 19, false, {COLOR_FG_CYAN},                  {COLOR_FG_CYAN,  COLOR_FG_WHITE}  };
asciiL logo_snapd    = { ASCII_SNAPD,    39, 16, false, {COLOR_FG_RED, COLOR_FG_WHITE},   {COLOR_FG_RED,   COLOR_FG_WHITE}  };
asciiL logo_mtk      = { ASCII_MTK,      59,  5, false, {COLOR_FG_BLUE, COLOR_FG_YELLOW}, {COLOR_FG_BLUE,  COLOR_FG_YELLOW} };
asciiL logo_exynos   = { ASCII_EXYNOS,   22, 13, true,  {COLOR_BG_BLUE, COLOR_FG_WHITE},  {COLOR_FG_BLUE,  COLOR_FG_WHITE}  };
asciiL logo_kirin    = { ASCII_KIRIN,    53, 12, false, {COLOR_FG_RED},                   {COLOR_FG_WHITE, COLOR_FG_RED}    };
asciiL logo_broadcom = { ASCII_BROADCOM, 44, 19, false, {COLOR_FG_WHITE, COLOR_FG_RED},   {COLOR_FG_WHITE, COLOR_FG_RED}    };
asciiL logo_arm      = { ASCII_ARM,      42,  5, false, {COLOR_FG_CYAN},                  {COLOR_FG_WHITE, COLOR_FG_CYAN}   };
asciiL logo_ibm      = { ASCII_IBM,      57, 13, true,  {COLOR_BG_CYAN, COLOR_FG_WHITE},  {COLOR_FG_CYAN,  COLOR_FG_WHITE}  };
asciiL logo_unknown  = { NULL,            0,  0, false, {COLOR_NONE },                    {COLOR_NONE,     COLOR_NONE}      };

#endif
