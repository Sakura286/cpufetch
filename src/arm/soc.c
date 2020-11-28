#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "soc.h"
#include "udev.h"
#include "../common/global.h"

#define min(a,b) (((a)<(b))?(a):(b))
#define STRING_UNKNOWN    "Unknown"

static char* soc_trademark_string[] = {
  [SOC_SNAPDRAGON] = "Snapdragon",
  [SOC_MEDIATEK]   = "MediaTek",
  [SOC_EXYNOS]     = "Exynos",
  [SOC_KIRIN]      = "Kirin",
  [SOC_BROADCOM]   = "Broadcom",
};

void fill_soc(struct system_on_chip* soc, char* soc_name, VENDOR soc_vendor, int32_t process) {
  soc->soc_vendor = soc_vendor;
  soc->process = process;
  int len = strlen(soc_name) + strlen(soc_trademark_string[soc->soc_vendor]) + 1;
  soc->soc_name = malloc(sizeof(char) * len);
  memset(soc->soc_name, 0, sizeof(char) * len);
  sprintf(soc->soc_name, "%s %s", soc_trademark_string[soc->soc_vendor], soc_name);    
}

bool match_soc(struct system_on_chip* soc, char* raw_name, char* expected_name, char* soc_name, VENDOR soc_vendor, int32_t process) {
  if(strlen(raw_name) > strlen(expected_name))
    return false;
  
  int len = strlen(raw_name);
  if(strncmp(raw_name, expected_name, len) != 0) {
    return false;
  }
  else {
    fill_soc(soc, soc_name, soc_vendor, process);
    return true;    
  }
}

char* toupperstr(char* str) {
  int len = strlen(str) + 1;
  char* ret = malloc(sizeof(char) * len);
  memset(ret, 0, sizeof(char) * len);
  
  for(int i=0; i < len; i++) {
    ret[i] = toupper((unsigned char) str[i]);    
  }
  
  return ret;
}

#define SOC_START if (false) {}
#define CHECK_SOC(raw_name, expected_name, soc_name, soc_vendor, soc, process) \
   else if (match_soc(soc, raw_name, expected_name, soc_name, soc_vendor, process)) return true;
#define SOC_END else { return false; }

// https://en.wikipedia.org/wiki/Raspberry_Pi
// http://phonedb.net/index.php?m=processor&id=562&c=broadcom_bcm21663
// https://hwbot.org/hardware/processors#key=bcmxxx
bool match_broadcom(char* soc_name, struct system_on_chip* soc) {
  char* tmp;

  if((tmp = strstr(soc_name, "BCM")) == NULL)
    return false;
  
  SOC_START
  CHECK_SOC(tmp, "BCM2835",              "2835",              SOC_BROADCOM, soc, 65)    
  CHECK_SOC(tmp, "BCM2836",              "2836",              SOC_BROADCOM, soc, 40)    
  CHECK_SOC(tmp, "BCM2837",              "2837",              SOC_BROADCOM, soc, 40) 
  CHECK_SOC(tmp, "BCM2837B0",            "2837B0",            SOC_BROADCOM, soc, 40) 
  CHECK_SOC(tmp, "BCM2711",              "2711",              SOC_BROADCOM, soc, 28)  
  CHECK_SOC(tmp, "BCM21553",             "21553",             SOC_BROADCOM, soc, 65)    
  CHECK_SOC(tmp, "BCM21553-Thunderbird", "21553 Thunderbird", SOC_BROADCOM, soc, 65)      
  CHECK_SOC(tmp, "BCM21663",             "21663",             SOC_BROADCOM, soc, 40) 
  CHECK_SOC(tmp, "BCM21664",             "21664",             SOC_BROADCOM, soc, 40) 
  CHECK_SOC(tmp, "BCM28155",             "28155",             SOC_BROADCOM, soc, 40) 
  CHECK_SOC(tmp, "BCM23550",             "23550",             SOC_BROADCOM, soc, 40) 
  CHECK_SOC(tmp, "BCM28145",             "28145",             SOC_BROADCOM, soc, 40) 
  CHECK_SOC(tmp, "BCM2157",              "2157",              SOC_BROADCOM, soc, 65) 
  CHECK_SOC(tmp, "BCM21654",             "21654",             SOC_BROADCOM, soc, 40) 
  SOC_END
}

// https://www.techinsights.com/
// https://datasheetspdf.com/pdf-file/1316605/HiSilicon/Hi3660/1
bool match_hisilicon(char* soc_name, struct system_on_chip* soc) {
  char* tmp;

  if((tmp = strstr(soc_name, "Hi")) == NULL)
    return false;
  
  SOC_START
  CHECK_SOC(tmp, "Hi3620GFC",  "K3V2",  SOC_KIRIN, soc, 40)
  //CHECK_SOC(tmp, "?",          "K3V2E", SOC_KIRIN, soc,  ?)
  //CHECK_SOC(tmp, "?",          "620",   SOC_KIRIN, soc, 28)
  //CHECK_SOC(tmp, "?",          "650",   SOC_KIRIN, soc, 16)
  //CHECK_SOC(tmp, "?",          "655",   SOC_KIRIN, soc, 16)
  //CHECK_SOC(tmp, "?",          "658",   SOC_KIRIN, soc, 16)
  //CHECK_SOC(tmp, "?",          "659",   SOC_KIRIN, soc, 16)
  //CHECK_SOC(tmp, "?",          "710",   SOC_KIRIN, soc, 12)
  //CHECK_SOC(tmp, "?",          "710A",  SOC_KIRIN, soc, 12)
  //CHECK_SOC(tmp, "?",          "710F",  SOC_KIRIN, soc, 12)
  //CHECK_SOC(tmp, "?",          "810",   SOC_KIRIN, soc,  7)
  //CHECK_SOC(tmp, "?",          "820",   SOC_KIRIN, soc,  7)
  //CHECK_SOC(tmp, "?",          "9000",  SOC_KIRIN, soc,  5)
  //CHECK_SOC(tmp, "?",          "9000E", SOC_KIRIN, soc,  5)
  //CHECK_SOC(tmp, "?",          "910",   SOC_KIRIN, soc, 28)
  //CHECK_SOC(tmp, "?",          "910T",  SOC_KIRIN, soc, 28)
  CHECK_SOC(tmp, "Hi3630",     "920",   SOC_KIRIN, soc, 28)
  //CHECK_SOC(tmp, "?",          "925",   SOC_KIRIN, soc, 28)
  //CHECK_SOC(tmp, "?",          "930",   SOC_KIRIN, soc, ?)
  //CHECK_SOC(tmp, "?",          "935",   SOC_KIRIN, soc, ?)
  CHECK_SOC(tmp, "Hi3650",     "950",   SOC_KIRIN, soc, 16)
  //CHECK_SOC(tmp, "?",          "955",   SOC_KIRIN, soc, ?)
  CHECK_SOC(tmp, "Hi3660",     "960",   SOC_KIRIN, soc, 16)
  //CHECK_SOC(tmp, "?",          "960S",  SOC_KIRIN, soc, 16)
  CHECK_SOC(tmp, "Hi3670",     "970",   SOC_KIRIN, soc, 10)
  CHECK_SOC(tmp, "Hi3680",     "980",   SOC_KIRIN, soc,  7)
  //CHECK_SOC(tmp, "?",          "985",   SOC_KIRIN, soc,  7)
  CHECK_SOC(tmp, "Hi3690",     "990",   SOC_KIRIN, soc,  7)
  SOC_END
}

bool match_exynos(char* soc_name, struct system_on_chip* soc) {
  char* tmp;

  if((tmp = strstr(soc_name, "universal")) == NULL)
    return false;
  
  SOC_START
  // universalXXXX //
  CHECK_SOC(tmp, "universal3475", "3475", SOC_EXYNOS, soc, 28) 
  CHECK_SOC(tmp, "universal4210", "4210", SOC_EXYNOS, soc, 45)
  CHECK_SOC(tmp, "universal4212", "4212", SOC_EXYNOS, soc, 32)
  CHECK_SOC(tmp, "universal4412", "4412", SOC_EXYNOS, soc, 32)
  CHECK_SOC(tmp, "universal5250", "5250", SOC_EXYNOS, soc, 32)
  CHECK_SOC(tmp, "universal5410", "5410", SOC_EXYNOS, soc, 28)
  CHECK_SOC(tmp, "universal5420", "5420", SOC_EXYNOS, soc, 28)
  CHECK_SOC(tmp, "universal5422", "5422", SOC_EXYNOS, soc, 28)
  CHECK_SOC(tmp, "universal5430", "5430", SOC_EXYNOS, soc, 20)
  CHECK_SOC(tmp, "universal5433", "5433", SOC_EXYNOS, soc, 20)
  CHECK_SOC(tmp, "universal5260", "5260", SOC_EXYNOS, soc, 28)
  CHECK_SOC(tmp, "universal7270", "7270", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7420", "7420", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7570", "7570", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7870", "7870", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7872", "7872", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7880", "7880", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7884", "7884", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7885", "7885", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal7904", "7904", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal8890", "8890", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal8895", "8895", SOC_EXYNOS, soc, 10)
  CHECK_SOC(tmp, "universal9110", "9110", SOC_EXYNOS, soc, 14)
  CHECK_SOC(tmp, "universal9609", "9609", SOC_EXYNOS, soc, 10)
  CHECK_SOC(tmp, "universal9610", "9610", SOC_EXYNOS, soc, 10)
  CHECK_SOC(tmp, "universal9611", "9611", SOC_EXYNOS, soc, 10)
  CHECK_SOC(tmp, "universal9810", "9810", SOC_EXYNOS, soc, 10)
  CHECK_SOC(tmp, "universal9820", "9820", SOC_EXYNOS, soc,  8)
  CHECK_SOC(tmp, "universal9825", "9825", SOC_EXYNOS, soc,  7)
  // New exynos. Dont know if they will work //
  CHECK_SOC(tmp, "universal1080", "1080", SOC_EXYNOS, soc,  5)  
  CHECK_SOC(tmp, "universal990",   "990", SOC_EXYNOS, soc,  7)
  CHECK_SOC(tmp, "universal980",   "980", SOC_EXYNOS, soc,  8)    
  CHECK_SOC(tmp, "universal880",   "880", SOC_EXYNOS, soc,  8)
  SOC_END
}

bool match_mediatek(char* soc_name, struct system_on_chip* soc) {
  char* tmp;

  if((tmp = strstr(soc_name, "MT")) == NULL)
    return false;
  
  SOC_START
  // Dimensity //
  //CHECK_SOC(tmp, "?",     "Dimensity 1000",  SOC_MEDIATEK, soc, 7) 
  //CHECK_SOC(tmp, "?",     "Dimensity 1000L", SOC_MEDIATEK, soc, 7) 
  //CHECK_SOC(tmp, "?",     "Dimensity 700",   SOC_MEDIATEK, soc, 7) 
  //CHECK_SOC(tmp, "?",     "Dimensity 720",   SOC_MEDIATEK, soc, 7) 
  CHECK_SOC(tmp, "MT6873",  "Dimensity 800",   SOC_MEDIATEK, soc, 7)
  //CHECK_SOC(tmp, "?",     "Dimensity 820",   SOC_MEDIATEK, soc, 7)
  // Helio //
  CHECK_SOC(tmp, "MT6761",  "Helio A22",       SOC_MEDIATEK, soc, 12)
  CHECK_SOC(tmp, "MT6762D", "Helio A25",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio G25",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio G35",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio G70",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio G80",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio G90",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio G90T",      SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio G95",       SOC_MEDIATEK, soc, 12)
  CHECK_SOC(tmp, "MT6755M", "Helio P10",       SOC_MEDIATEK, soc, 28)
  //CHECK_SOC(tmp, "?",     "Helio P15",       SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6757",  "Helio P20",       SOC_MEDIATEK, soc, 16)
  CHECK_SOC(tmp, "MT6762",  "Helio P22",       SOC_MEDIATEK, soc, 12)
  CHECK_SOC(tmp, "MT6763T", "Helio P23",       SOC_MEDIATEK, soc, 16)
  //CHECK_SOC(tmp, "?",     "Helio P25",       SOC_MEDIATEK, soc, 16)
  //CHECK_SOC(tmp, "?",     "Helio P30",       SOC_MEDIATEK, soc, 16)
  CHECK_SOC(tmp, "MT6765",  "Helio P35",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio P60",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio P65",       SOC_MEDIATEK, soc, 12)
  CHECK_SOC(tmp, "MT6771V", "Helio P70",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio P90",       SOC_MEDIATEK, soc, 12)
  //CHECK_SOC(tmp, "?",     "Helio P95",       SOC_MEDIATEK, soc, 12)
  CHECK_SOC(tmp, "MT6795",  "Helio X10",       SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6797",  "Helio X20 / X23", SOC_MEDIATEK, soc, 20)
  //CHECK_SOC(tmp, "?",     "Helio X25",       SOC_MEDIATEK, soc, 20)
  CHECK_SOC(tmp, "MT6797X", "Helio X27",       SOC_MEDIATEK, soc, 20)
  CHECK_SOC(tmp, "MT6797",  "Helio X30",       SOC_MEDIATEK, soc, 10)
  // MT XXXX //
  CHECK_SOC(tmp, "MT2523",  "MT2523",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT2601",  "MT2601",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6515",  "MT6515",          SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT6516",  "MT6516",          SOC_MEDIATEK, soc, 65)
  CHECK_SOC(tmp, "MT6517",  "MT6517",          SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT6572",  "MT6572",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6572M", "MT6572M",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6573",  "MT6573",          SOC_MEDIATEK, soc, 65)
  CHECK_SOC(tmp, "MT6575",  "MT6575",          SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT6577",  "MT6577",          SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT6577T", "MT6577T",         SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT6580",  "MT6580",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6582",  "MT6582",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6582M", "MT6582M",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6589",  "MT6589",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6589",  "MT6589",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6589T", "MT6589T",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6592",  "MT6592",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6595",  "MT6595",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6732",  "MT6732",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6735",  "MT6735",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6735M", "MT6735M",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6735P", "MT6735P",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6737",  "MT6737",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6737M", "MT6737M",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6737T", "MT6737T",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6739",  "MT6739",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6750",  "MT6750",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6750S", "MT6750S",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6750T", "MT6750T",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6752",  "MT6752",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6753",  "MT6753",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6795",  "MT6795",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT6850",  "MT6850",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT7697",  "MT7697",          SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT8121",  "MT8121",          SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT8125",  "MT8125",          SOC_MEDIATEK, soc, 40)
  CHECK_SOC(tmp, "MT8127",  "MT8127",          SOC_MEDIATEK, soc, 32)
  CHECK_SOC(tmp, "MT8135",  "MT8135",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8163A", "MT8163A",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8163B", "MT8163B",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8167B", "MT8167B",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8173",  "MT8173",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8176",  "MT8176",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8321",  "MT8321",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8382",  "MT8382",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8581",  "MT8581",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8735",  "MT8735",          SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8765B", "MT8765B",         SOC_MEDIATEK, soc, 28)
  CHECK_SOC(tmp, "MT8783",  "MT8783",          SOC_MEDIATEK, soc, 28)
  SOC_END
}

bool match_qualcomm(char* soc_name, struct system_on_chip* soc) {
  char* tmp;
  char* soc_name_upper = toupperstr(soc_name);

  if((tmp = strstr(soc_name_upper, "MSM")) != NULL);
  else if((tmp = strstr(soc_name_upper, "SDM")) != NULL);
  else if((tmp = strstr(soc_name_upper, "APQ")) != NULL);
  else if((tmp = strstr(soc_name_upper, "SM")) != NULL);    
  else if((tmp = strstr(soc_name_upper, "QM")) != NULL);      
  else return false;
  
  SOC_START
  // Snapdragon S1 //
  CHECK_SOC(tmp, "MSM7627A",       "S1",        SOC_SNAPDRAGON, soc, 65) 
  CHECK_SOC(tmp, "MSM7225",        "S1",        SOC_SNAPDRAGON, soc, 65) 
  CHECK_SOC(tmp, "MSM7625",        "S1",        SOC_SNAPDRAGON, soc, 65) 
  CHECK_SOC(tmp, "MSM7625A",       "S1",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM7627",        "S1",        SOC_SNAPDRAGON, soc, 65) 
  CHECK_SOC(tmp, "MSM7227A",       "S1",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "QSD8250",        "S1",        SOC_SNAPDRAGON, soc, 65) 
  CHECK_SOC(tmp, "MSM7227",        "S1",        SOC_SNAPDRAGON, soc, 65) 
  CHECK_SOC(tmp, "MSM7225A",       "S1",        SOC_SNAPDRAGON, soc, 45) 
  // Snapdragon S2 //
  CHECK_SOC(tmp, "MSM7230",        "S2",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8655T",       "S2",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8255",        "S2",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8255T",       "S2",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8655",        "S2",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "APQ8055",        "S2",        SOC_SNAPDRAGON, soc, 45) 
  // Snapdragon S3 //
  CHECK_SOC(tmp, "MSM8260",        "S3",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8660",        "S3",        SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "APQ8060",        "S3",        SOC_SNAPDRAGON, soc, 45) 
  // Snapdragon S4 //
  CHECK_SOC(tmp, "MSM8225",        "S4 Play",   SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8225Q",       "S4 Play",   SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8227",        "S4 Plus",   SOC_SNAPDRAGON, soc, 28) 
  CHECK_SOC(tmp, "MSM8960",        "S4 Plus",   SOC_SNAPDRAGON, soc, 28) 
  CHECK_SOC(tmp, "MSM8930",        "S4 Plus",   SOC_SNAPDRAGON, soc, 28) 
  CHECK_SOC(tmp, "MSM8260A",       "S4 Plus",   SOC_SNAPDRAGON, soc, 28) 
  CHECK_SOC(tmp, "MSM8230",        "S4 Plus",   SOC_SNAPDRAGON, soc, 28) 
  CHECK_SOC(tmp, "APQ8064",        "S4 Pro",    SOC_SNAPDRAGON, soc, 28) 
  // Snapdragon 2XX //
  CHECK_SOC(tmp, "MSM8212",        "200",       SOC_SNAPDRAGON, soc, 45) 
  CHECK_SOC(tmp, "MSM8625Q",       "200",       SOC_SNAPDRAGON, soc, 45)
  CHECK_SOC(tmp, "MSM8210",        "200",       SOC_SNAPDRAGON, soc, 45)
  CHECK_SOC(tmp, "MSM8225Q",       "200",       SOC_SNAPDRAGON, soc, 45)
  CHECK_SOC(tmp, "MSM8208",        "208",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8909",        "210",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "APQ8009",        "212",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "QM215",          "215",       SOC_SNAPDRAGON, soc, 28)
  // Snapdragon 4XX //
  CHECK_SOC(tmp, "MSM8226",        "400",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8926",        "400",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8930",        "400",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8928",        "400",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8230AB",      "400",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8228",        "400",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8930AA",      "400",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8916T",       "412",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8916",        "410",       SOC_SNAPDRAGON, soc, 28)  
  CHECK_SOC(tmp, "MSM8929",        "415",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8917",        "425",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8920",        "427",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "SDM429",         "429",       SOC_SNAPDRAGON, soc, 12)
  CHECK_SOC(tmp, "MSM8937",        "430",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8940",        "435",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "SDM439",         "439",       SOC_SNAPDRAGON, soc, 12)
  CHECK_SOC(tmp, "SDM450",         "450",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "SM4250",         "460",       SOC_SNAPDRAGON, soc, 11)
  // Snapdragon 6XX //
  CHECK_SOC(tmp, "APQ8064T",       "600",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8936",        "610",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8939",        "615 / 616", SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8952",        "617",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8953",        "625",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "MSM8953 PRO",    "626",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "SDM630",         "630",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "SDM632",         "632",       SOC_SNAPDRAGON, soc, 12)
  CHECK_SOC(tmp, "SDM636",         "636",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "MSM8956",        "650",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8976",        "652",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8976 PRO",    "653",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "SDM660",         "660",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "SM6115",         "662",       SOC_SNAPDRAGON, soc, 11)
  CHECK_SOC(tmp, "SM6125",         "665",       SOC_SNAPDRAGON, soc, 11)
  CHECK_SOC(tmp, "SDM670",         "670",       SOC_SNAPDRAGON, soc, 10)
  CHECK_SOC(tmp, "SDM675",         "675",       SOC_SNAPDRAGON, soc, 11)
  CHECK_SOC(tmp, "SDM690",         "690",       SOC_SNAPDRAGON, soc,  8)
  // Snapdragon 7XX //
  //CHECK_SOC(tmp, "?",            "710",       SOC_SNAPDRAGON, soc, 10)
  //CHECK_SOC(tmp, "?",            "712",       SOC_SNAPDRAGON, soc, 10)
  CHECK_SOC(tmp, "SM7125",         "720G",      SOC_SNAPDRAGON, soc,  8)
  CHECK_SOC(tmp, "SM7150-AA",      "730",       SOC_SNAPDRAGON, soc,  8)
  CHECK_SOC(tmp, "SM7150-AB",      "730G",      SOC_SNAPDRAGON, soc,  8)
  CHECK_SOC(tmp, "SM7150-AC",      "732G",      SOC_SNAPDRAGON, soc,  8)
  CHECK_SOC(tmp, "SM7225",         "750G",      SOC_SNAPDRAGON, soc,  8)
  CHECK_SOC(tmp, "SM7250-AA",      "765",       SOC_SNAPDRAGON, soc,  7)
  CHECK_SOC(tmp, "SM7250-AB",      "765G",      SOC_SNAPDRAGON, soc,  7)
  CHECK_SOC(tmp, "SM7250-AC",      "768G",      SOC_SNAPDRAGON, soc,  7)
  // Snapdragon 8XX //
  CHECK_SOC(tmp, "MSM8974AA",      "800",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8974AB",      "800",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8974AC",      "800",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8974PRO-AB",  "801",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8974PRO-AC",  "801",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "APQ8084",        "805",       SOC_SNAPDRAGON, soc, 28)
  CHECK_SOC(tmp, "MSM8992",        "808",       SOC_SNAPDRAGON, soc, 20)
  CHECK_SOC(tmp, "MSM8994",        "810",       SOC_SNAPDRAGON, soc, 20)
  CHECK_SOC(tmp, "MSM8996",        "820",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "MSM8996 PRO A",  "821",       SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "MSM8996 PRO AB", "821 AB",    SOC_SNAPDRAGON, soc, 14)
  CHECK_SOC(tmp, "MSM8995",        "835",       SOC_SNAPDRAGON, soc, 10)
  //CHECK_SOC(tmp, "?",            "845",       SOC_SNAPDRAGON, soc, 10)
  //CHECK_SOC(tmp, "?",            "850",       SOC_SNAPDRAGON, soc, 10)
  CHECK_SOC(tmp, "SM8150",         "855",       SOC_SNAPDRAGON, soc,  7)
  //CHECK_SOC(tmp, "?",            "855+",      SOC_SNAPDRAGON, soc,  7)
  CHECK_SOC(tmp, "SM8250",         "865",       SOC_SNAPDRAGON, soc,  7)
  CHECK_SOC(tmp, "SM8250-AB",      "865+",      SOC_SNAPDRAGON, soc,  7)
  SOC_END
}

bool match_special(char* soc_name, struct system_on_chip* soc) {
  char* tmp;

  // Xiaomi hides Redmi Note 8/8T under "Qualcomm Technologies, Inc TRINKET"
  if((tmp = strstr(soc_name, "TRINKET")) != NULL) {
    fill_soc(soc, "665", SOC_SNAPDRAGON, 11);
    return true;
  }
  
  return false;  
}

struct system_on_chip* parse_soc_from_string(struct system_on_chip* soc) {
  char* raw_name = soc->raw_name;
  
  if (match_qualcomm(raw_name, soc))
    return soc;
  
  if(match_mediatek(raw_name, soc))
    return soc;
  
  if(match_exynos(raw_name, soc))
    return soc;
  
  if(match_hisilicon(raw_name, soc))
    return soc;
  
  match_special(raw_name, soc);  
  
  return soc;
}

#ifdef __ANDROID__
#include <sys/system_properties.h>

static inline int android_property_get(const char* key, char* value) {
  return __system_property_get(key, value);
}

struct system_on_chip* guess_soc_from_android(struct system_on_chip* soc) {
  char tmp[100];
  int property_len = 0;
  
  property_len = android_property_get("ro.mediatek.platform", (char *) &tmp);
  if(property_len > 0) {
    soc->raw_name = malloc(sizeof(char) * (property_len + 1));
    strncpy(soc->raw_name, tmp, property_len + 1);
    soc->raw_name[property_len] = '\0';
    soc->soc_vendor = SOC_UNKNOWN;
    return parse_soc_from_string(soc);
  }
  
  property_len = android_property_get("ro.product.board", (char *) &tmp);
  if(property_len > 0) {    
    soc->raw_name = malloc(sizeof(char) * (property_len + 1));
    strncpy(soc->raw_name, tmp, property_len + 1);
    soc->raw_name[property_len] = '\0';
    soc->soc_vendor = SOC_UNKNOWN;
    return parse_soc_from_string(soc);
  }    
  
  return soc;
}
#endif

struct system_on_chip* guess_soc_from_cpuinfo(struct system_on_chip* soc) {
  char* tmp = get_hardware_from_cpuinfo(&strlen);
  
  if(tmp != NULL) {
    soc->raw_name = tmp;
    return parse_soc_from_string(soc);
  }
  
  return soc;
}

struct system_on_chip* get_soc() {
  struct system_on_chip* soc = malloc(sizeof(struct system_on_chip));
  soc->raw_name = NULL;
  soc->soc_vendor = SOC_UNKNOWN;
  soc->process = UNKNOWN;
  
  soc = guess_soc_from_cpuinfo(soc);
  if(soc->soc_vendor == SOC_UNKNOWN) {
    if(soc->raw_name != NULL)
      printBug("SoC detection failed using /proc/cpuinfo: Found '%s' string", soc->raw_name);   
    else
      printWarn("SoC detection failed using /proc/cpuinfo: No string found");
#ifdef __ANDROID__
    soc = guess_soc_from_android(soc);
    if(soc->raw_name == NULL)
      printWarn("SoC detection failed using Android: No string found");
    else if(soc->soc_vendor == SOC_UNKNOWN)
      printBug("SoC detection failed using Android: Found '%s' string", soc->raw_name);   
#endif
  }

  if(soc->raw_name == NULL) {
    soc->raw_name = malloc(sizeof(char) * (strlen(STRING_UNKNOWN)+1));
    snprintf(soc->raw_name, strlen(STRING_UNKNOWN)+1, STRING_UNKNOWN);
  }
  
  return soc;    
}

char* get_soc_name(struct system_on_chip* soc) {
  if(soc->soc_vendor == SOC_UNKNOWN)
    return soc->raw_name;
  return soc->soc_name;
}

VENDOR get_soc_vendor(struct system_on_chip* soc) {
  return soc->soc_vendor;
}

char* get_str_process(struct system_on_chip* soc) {
  char* str;
  
  if(soc->process == UNKNOWN) {
    str = malloc(sizeof(char) * (strlen(STRING_UNKNOWN)+1));
    snprintf(str, strlen(STRING_UNKNOWN)+1, STRING_UNKNOWN);
  }
  else {
    str = malloc(sizeof(char) * 5);
    memset(str, 0, sizeof(char) * 5);
    snprintf(str, 5, "%dnm", soc->process);    
  }
  return str;
}

