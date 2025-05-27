#include <Arduino.h>
#include "MyLibrary.h"
#include "gif_frames.h"

MyLibrary::MyLibrary(int width, int height, int resetPin)
: display(width, height, &Wire, resetPin) {}
const unsigned char* cry_gif_frames[] = {
    cry_gImage_IMG00000,
    cry_gImage_IMG00001,
    cry_gImage_IMG00002,
    cry_gImage_IMG00003,
    cry_gImage_IMG00004,
    cry_gImage_IMG00005,
    cry_gImage_IMG00006,
    cry_gImage_IMG00007,
    cry_gImage_IMG00008,
    cry_gImage_IMG00009,
    cry_gImage_IMG00010,
    cry_gImage_IMG00011,
    cry_gImage_IMG00012,
    cry_gImage_IMG00013,
    cry_gImage_IMG00014,
    cry_gImage_IMG00015,
    cry_gImage_IMG00016,
    cry_gImage_IMG00017,
    cry_gImage_IMG00018,
    cry_gImage_IMG00019,
    cry_gImage_IMG00020,
    cry_gImage_IMG00021,
    cry_gImage_IMG00022,
    cry_gImage_IMG00023,
    cry_gImage_IMG00024,
    cry_gImage_IMG00025,
    cry_gImage_IMG00026,
    cry_gImage_IMG00027
};
const int cry_total_frames = sizeof(cry_gif_frames) / sizeof(cry_gif_frames[0]);

const unsigned char* book_gif_frames[] = {
    book_gImage_IMG00000,
    book_gImage_IMG00001,
    book_gImage_IMG00002,
    book_gImage_IMG00003,
    book_gImage_IMG00004,
    book_gImage_IMG00005,
    book_gImage_IMG00006,
    book_gImage_IMG00007,
    book_gImage_IMG00008,
    book_gImage_IMG00009,
    book_gImage_IMG00010,
    book_gImage_IMG00011,
    book_gImage_IMG00012,
    book_gImage_IMG00013,
    book_gImage_IMG00014,
    book_gImage_IMG00015,
    book_gImage_IMG00016,
    book_gImage_IMG00017,
    book_gImage_IMG00018,
    book_gImage_IMG00019,
    book_gImage_IMG00020,
    book_gImage_IMG00021,
    book_gImage_IMG00022,
    book_gImage_IMG00023,
    book_gImage_IMG00024,
    book_gImage_IMG00025,
    book_gImage_IMG00026,
    book_gImage_IMG00027,
    book_gImage_IMG00028,
    book_gImage_IMG00029,
    book_gImage_IMG00030,
    book_gImage_IMG00031,
    book_gImage_IMG00032,
    book_gImage_IMG00033
};
const int book_total_frames = sizeof(book_gif_frames) / sizeof(book_gif_frames[0]);

const unsigned char* birdvisit_gif_frames[] = {
    birdvisit_gImage_IMG00000,
    birdvisit_gImage_IMG00001,
    birdvisit_gImage_IMG00002,
    birdvisit_gImage_IMG00003,
    birdvisit_gImage_IMG00004,
    birdvisit_gImage_IMG00005,
    birdvisit_gImage_IMG00006,
    birdvisit_gImage_IMG00007,
    birdvisit_gImage_IMG00008,
    birdvisit_gImage_IMG00009,
    birdvisit_gImage_IMG00010,
    birdvisit_gImage_IMG00011,
    birdvisit_gImage_IMG00012,
    birdvisit_gImage_IMG00013,
    birdvisit_gImage_IMG00014,
    birdvisit_gImage_IMG00015,
    birdvisit_gImage_IMG00016,
    birdvisit_gImage_IMG00017,
    birdvisit_gImage_IMG00018,
    birdvisit_gImage_IMG00019,
    birdvisit_gImage_IMG00020,
    birdvisit_gImage_IMG00021,
    birdvisit_gImage_IMG00022,
    birdvisit_gImage_IMG00023,
    birdvisit_gImage_IMG00024,
    birdvisit_gImage_IMG00025,
    birdvisit_gImage_IMG00026,
    birdvisit_gImage_IMG00027,
    birdvisit_gImage_IMG00028,
    birdvisit_gImage_IMG00029,
    birdvisit_gImage_IMG00030,
    birdvisit_gImage_IMG00031,
    birdvisit_gImage_IMG00032,
    birdvisit_gImage_IMG00033,
    birdvisit_gImage_IMG00034,
    birdvisit_gImage_IMG00035,
    birdvisit_gImage_IMG00036,
    birdvisit_gImage_IMG00037,
    birdvisit_gImage_IMG00038,
    birdvisit_gImage_IMG00039,
    birdvisit_gImage_IMG00040,
    birdvisit_gImage_IMG00041,
    birdvisit_gImage_IMG00042,
    birdvisit_gImage_IMG00043,
    birdvisit_gImage_IMG00044,
    birdvisit_gImage_IMG00045,
    birdvisit_gImage_IMG00046,
    birdvisit_gImage_IMG00047,
    birdvisit_gImage_IMG00048,
    birdvisit_gImage_IMG00049,
    birdvisit_gImage_IMG00050,
    birdvisit_gImage_IMG00051,
    birdvisit_gImage_IMG00052,
    birdvisit_gImage_IMG00053,
    birdvisit_gImage_IMG00054
};
const int birdvisit_total_frames = sizeof(birdvisit_gif_frames) / sizeof(birdvisit_gif_frames[0]);

const unsigned char* cake_gif_frames[] = {
    cake_gImage_IMG00000,
    cake_gImage_IMG00001,
    cake_gImage_IMG00002,
    cake_gImage_IMG00003,
    cake_gImage_IMG00004,
    cake_gImage_IMG00005,
    cake_gImage_IMG00006,
    cake_gImage_IMG00007,
    cake_gImage_IMG00008,
    cake_gImage_IMG00009,
    cake_gImage_IMG00010,
    cake_gImage_IMG00011,
    cake_gImage_IMG00012,
    cake_gImage_IMG00013,
    cake_gImage_IMG00014,
    cake_gImage_IMG00015,
    cake_gImage_IMG00016,
    cake_gImage_IMG00017,
    cake_gImage_IMG00018,
    cake_gImage_IMG00019,
    cake_gImage_IMG00020,
    cake_gImage_IMG00021,
    cake_gImage_IMG00022,
    cake_gImage_IMG00023,
    cake_gImage_IMG00024,
    cake_gImage_IMG00025,
    cake_gImage_IMG00026,
    cake_gImage_IMG00027,
    cake_gImage_IMG00028,
    cake_gImage_IMG00029,
    cake_gImage_IMG00030,
    cake_gImage_IMG00031,
    cake_gImage_IMG00032,
    cake_gImage_IMG00033,
    cake_gImage_IMG00034,
    cake_gImage_IMG00035,
    cake_gImage_IMG00036,
    cake_gImage_IMG00037,
    cake_gImage_IMG00038,
    cake_gImage_IMG00039,
    cake_gImage_IMG00040,
    cake_gImage_IMG00041,
    cake_gImage_IMG00042,
    cake_gImage_IMG00043,
    cake_gImage_IMG00044,
    cake_gImage_IMG00045,
    cake_gImage_IMG00046,
    cake_gImage_IMG00047,
    cake_gImage_IMG00048,
    cake_gImage_IMG00049,
    cake_gImage_IMG00050,
    cake_gImage_IMG00051,
    cake_gImage_IMG00052,
    cake_gImage_IMG00053,
    cake_gImage_IMG00054,
    cake_gImage_IMG00055,
    cake_gImage_IMG00056,
    cake_gImage_IMG00057,
    cake_gImage_IMG00058,
    cake_gImage_IMG00059,
    cake_gImage_IMG00060,
    cake_gImage_IMG00061,
    cake_gImage_IMG00062,
    cake_gImage_IMG00063,
    cake_gImage_IMG00064,
    cake_gImage_IMG00065,
    cake_gImage_IMG00066,
    cake_gImage_IMG00067,
    cake_gImage_IMG00068,
    cake_gImage_IMG00069,
    cake_gImage_IMG00070,
    cake_gImage_IMG00071,
    cake_gImage_IMG00072,
    cake_gImage_IMG00073,
    cake_gImage_IMG00074,
    cake_gImage_IMG00075,
    cake_gImage_IMG00076,
    cake_gImage_IMG00077,
    cake_gImage_IMG00078,
    cake_gImage_IMG00079,
    cake_gImage_IMG00080,
    cake_gImage_IMG00081,
    cake_gImage_IMG00082,
    cake_gImage_IMG00083,
    cake_gImage_IMG00084,
    cake_gImage_IMG00085,
    cake_gImage_IMG00086,
    cake_gImage_IMG00087,
    cake_gImage_IMG00088,
    cake_gImage_IMG00089,
    cake_gImage_IMG00090,
    cake_gImage_IMG00091,
    cake_gImage_IMG00092,
    cake_gImage_IMG00093
};
const int cake_total_frames = sizeof(cake_gif_frames) / sizeof(cake_gif_frames[0]);

const unsigned char* snow_gif_frames[] = {
    snow_snow_gImage_IMG00000,
    snow_snow_gImage_IMG00001,
    snow_snow_gImage_IMG00002,
    snow_snow_gImage_IMG00003,
    snow_snow_gImage_IMG00004,
    snow_snow_gImage_IMG00005,
    snow_snow_gImage_IMG00006,
    snow_snow_gImage_IMG00007,
    snow_snow_gImage_IMG00008,
    snow_snow_gImage_IMG00009,
    snow_snow_gImage_IMG00010,
    snow_snow_gImage_IMG00011,
    snow_snow_gImage_IMG00012,
    snow_snow_gImage_IMG00013,
    snow_snow_gImage_IMG00014,
    snow_snow_gImage_IMG00015,
    snow_snow_gImage_IMG00016,
    snow_snow_gImage_IMG00017,
    snow_snow_gImage_IMG00018,
    snow_snow_gImage_IMG00019,
    snow_snow_gImage_IMG00020,
    snow_snow_gImage_IMG00021,
    snow_snow_gImage_IMG00022,
    snow_snow_gImage_IMG00023,
    snow_snow_gImage_IMG00024,
    snow_snow_gImage_IMG00025,
    snow_snow_gImage_IMG00026,
    snow_snow_gImage_IMG00027,
    snow_snow_gImage_IMG00028,
    snow_snow_gImage_IMG00029,
    snow_snow_gImage_IMG00030,
    snow_snow_gImage_IMG00031,
    snow_snow_gImage_IMG00032,
    snow_snow_gImage_IMG00033,
    snow_snow_gImage_IMG00034,
    snow_snow_gImage_IMG00035,
    snow_snow_gImage_IMG00036,
    snow_snow_gImage_IMG00037,
    snow_snow_gImage_IMG00038,
    snow_snow_gImage_IMG00039,
    snow_snow_gImage_IMG00040,
    snow_snow_gImage_IMG00041,
    snow_snow_gImage_IMG00042,
    snow_snow_gImage_IMG00043,
    snow_snow_gImage_IMG00044,
    snow_snow_gImage_IMG00045,
    snow_snow_gImage_IMG00046,
    snow_snow_gImage_IMG00047,
    snow_snow_gImage_IMG00048,
    snow_snow_gImage_IMG00049,
    snow_snow_gImage_IMG00050,
    snow_snow_gImage_IMG00051,
    snow_snow_gImage_IMG00052,
    snow_snow_gImage_IMG00053,
    snow_snow_gImage_IMG00054,
    snow_snow_gImage_IMG00055,
    snow_snow_gImage_IMG00056,
    snow_snow_gImage_IMG00057
};
const int snow_total_frames = sizeof(snow_gif_frames) / sizeof(snow_gif_frames[0]);

const unsigned char* transformers_gif_frames[] = {
    transformers_gImage_IMG00000,
    transformers_gImage_IMG00001,
    transformers_gImage_IMG00002,
    transformers_gImage_IMG00003,
    transformers_gImage_IMG00004,
    transformers_gImage_IMG00005,
    transformers_gImage_IMG00006,
    transformers_gImage_IMG00007,
    transformers_gImage_IMG00008,
    transformers_gImage_IMG00009,
    transformers_gImage_IMG00010,
    transformers_gImage_IMG00011,
    transformers_gImage_IMG00012,
    transformers_gImage_IMG00013,
    transformers_gImage_IMG00014,
    transformers_gImage_IMG00015,
    transformers_gImage_IMG00016,
    transformers_gImage_IMG00017,
    transformers_gImage_IMG00018,
    transformers_gImage_IMG00019,
    transformers_gImage_IMG00020,
    transformers_gImage_IMG00021,
    transformers_gImage_IMG00022,
    transformers_gImage_IMG00023,
    transformers_gImage_IMG00024,
    transformers_gImage_IMG00025,
    transformers_gImage_IMG00026,
    transformers_gImage_IMG00027,
    transformers_gImage_IMG00028,
    transformers_gImage_IMG00029,
    transformers_gImage_IMG00030,
    transformers_gImage_IMG00031,
    transformers_gImage_IMG00032,
    transformers_gImage_IMG00033,
    transformers_gImage_IMG00034,
    transformers_gImage_IMG00035,
    transformers_gImage_IMG00036,
    transformers_gImage_IMG00037,
    transformers_gImage_IMG00038,
    transformers_gImage_IMG00039,
    transformers_gImage_IMG00040,
    transformers_gImage_IMG00041,
    transformers_gImage_IMG00042,
    transformers_gImage_IMG00043,
    transformers_gImage_IMG00044,
    transformers_gImage_IMG00045,
    transformers_gImage_IMG00046,
    transformers_gImage_IMG00047,
    transformers_gImage_IMG00048,
    transformers_gImage_IMG00049,
    transformers_gImage_IMG00050,
    transformers_gImage_IMG00051,
    transformers_gImage_IMG00052,
    transformers_gImage_IMG00053,
    transformers_gImage_IMG00054,
    transformers_gImage_IMG00055,
    transformers_gImage_IMG00056,
    transformers_gImage_IMG00057,
    transformers_gImage_IMG00058,
    transformers_gImage_IMG00059,
    transformers_gImage_IMG00060,
    transformers_gImage_IMG00061,
    transformers_gImage_IMG00062,
    transformers_gImage_IMG00063,
    transformers_gImage_IMG00064,
    transformers_gImage_IMG00065,
    transformers_gImage_IMG00066,
    transformers_gImage_IMG00067,
    transformers_gImage_IMG00068,
    transformers_gImage_IMG00069,
    transformers_gImage_IMG00070,
    transformers_gImage_IMG00071,
    transformers_gImage_IMG00072,
    transformers_gImage_IMG00073,
    transformers_gImage_IMG00074,
    transformers_gImage_IMG00075,
    transformers_gImage_IMG00076,
    transformers_gImage_IMG00077,
    transformers_gImage_IMG00078,
    transformers_gImage_IMG00079,
    transformers_gImage_IMG00080,
    transformers_gImage_IMG00081,
    transformers_gImage_IMG00082,
    transformers_gImage_IMG00083,
    transformers_gImage_IMG00084,
    transformers_gImage_IMG00085,
    transformers_gImage_IMG00086,
    transformers_gImage_IMG00087
};
const int transformers_total_frames = sizeof(transformers_gif_frames) / sizeof(transformers_gif_frames[0]);


const unsigned char* sneeze_gif_frames[] = {
    sneeze_gImage_IMG00000,
    sneeze_gImage_IMG00001,
    sneeze_gImage_IMG00002,
    sneeze_gImage_IMG00003,
    sneeze_gImage_IMG00004,
    sneeze_gImage_IMG00005,
    sneeze_gImage_IMG00006,
    sneeze_gImage_IMG00007,
    sneeze_gImage_IMG00008,
    sneeze_gImage_IMG00009,
    sneeze_gImage_IMG00010,
    sneeze_gImage_IMG00011,
    sneeze_gImage_IMG00012,
    sneeze_gImage_IMG00013,
    sneeze_gImage_IMG00014,
    sneeze_gImage_IMG00015,
    sneeze_gImage_IMG00016,
    sneeze_gImage_IMG00017,
    sneeze_gImage_IMG00018,
    sneeze_gImage_IMG00019,
    sneeze_gImage_IMG00020,
    sneeze_gImage_IMG00021,
    sneeze_gImage_IMG00022,
    sneeze_gImage_IMG00023,
    sneeze_gImage_IMG00024,
    sneeze_gImage_IMG00025,
    sneeze_gImage_IMG00026,
    sneeze_gImage_IMG00027
};
const int sneeze_total_frames = sizeof(sneeze_gif_frames) / sizeof(sneeze_gif_frames[0]);

const unsigned char* eyebrow_gif_frames[] = {
    eyebrow_gImage_IMG00000,
    eyebrow_gImage_IMG00001,
    eyebrow_gImage_IMG00002,
    eyebrow_gImage_IMG00003,
    eyebrow_gImage_IMG00004,
    eyebrow_gImage_IMG00005,
    eyebrow_gImage_IMG00006,
    eyebrow_gImage_IMG00007,
    eyebrow_gImage_IMG00008,
    eyebrow_gImage_IMG00009,
    eyebrow_gImage_IMG00010,
    eyebrow_gImage_IMG00011,
    eyebrow_gImage_IMG00012,
    eyebrow_gImage_IMG00013,
    eyebrow_gImage_IMG00014,
    eyebrow_gImage_IMG00015,
    eyebrow_gImage_IMG00016,
    eyebrow_gImage_IMG00017,
    eyebrow_gImage_IMG00018,
    eyebrow_gImage_IMG00019,
    eyebrow_gImage_IMG00020,
    eyebrow_gImage_IMG00021,
    eyebrow_gImage_IMG00022,
    eyebrow_gImage_IMG00023,
    eyebrow_gImage_IMG00024,
    eyebrow_gImage_IMG00025,
    eyebrow_gImage_IMG00026,
    eyebrow_gImage_IMG00027,
    eyebrow_gImage_IMG00028,
    eyebrow_gImage_IMG00029,
    eyebrow_gImage_IMG00030,
    eyebrow_gImage_IMG00031,
    eyebrow_gImage_IMG00032,
    eyebrow_gImage_IMG00033,
    eyebrow_gImage_IMG00034,
    eyebrow_gImage_IMG00035,
    eyebrow_gImage_IMG00036,
    eyebrow_gImage_IMG00037,
    eyebrow_gImage_IMG00038,
    eyebrow_gImage_IMG00039,
    eyebrow_gImage_IMG00040,
    eyebrow_gImage_IMG00041,
    eyebrow_gImage_IMG00042,
    eyebrow_gImage_IMG00043,
    eyebrow_gImage_IMG00044,
    eyebrow_gImage_IMG00045,
    eyebrow_gImage_IMG00046,
    eyebrow_gImage_IMG00047,
    eyebrow_gImage_IMG00048,
    eyebrow_gImage_IMG00049,
    eyebrow_gImage_IMG00050,
    eyebrow_gImage_IMG00051
};
const int eyebrow_total_frames = sizeof(eyebrow_gif_frames) / sizeof(eyebrow_gif_frames[0]);

const unsigned char* escape_gif_frames[] = {
    escape_gImage_IMG00000,
    escape_gImage_IMG00001,
    escape_gImage_IMG00002,
    escape_gImage_IMG00003,
    escape_gImage_IMG00004,
    escape_gImage_IMG00005,
    escape_gImage_IMG00006,
    escape_gImage_IMG00007,
    escape_gImage_IMG00008,
    escape_gImage_IMG00009,
    escape_gImage_IMG00010,
    escape_gImage_IMG00011,
    escape_gImage_IMG00012,
    escape_gImage_IMG00013,
    escape_gImage_IMG00014,
    escape_gImage_IMG00015,
    escape_gImage_IMG00016,
    escape_gImage_IMG00017,
    escape_gImage_IMG00018,
    escape_gImage_IMG00019,
    escape_gImage_IMG00020,
    escape_gImage_IMG00021,
    escape_gImage_IMG00022,
    escape_gImage_IMG00023,
    escape_gImage_IMG00024,
    escape_gImage_IMG00025,
    escape_gImage_IMG00026,
    escape_gImage_IMG00027,
    escape_gImage_IMG00028,
    escape_gImage_IMG00029,
    escape_gImage_IMG00030,
    escape_gImage_IMG00031,
    escape_gImage_IMG00032,
    escape_gImage_IMG00033,
    escape_gImage_IMG00034,
    escape_gImage_IMG00035,
    escape_gImage_IMG00036,
    escape_gImage_IMG00037,
    escape_gImage_IMG00038,
    escape_gImage_IMG00039,
    escape_gImage_IMG00040,
    escape_gImage_IMG00041,
    escape_gImage_IMG00042,
    escape_gImage_IMG00043,
    escape_gImage_IMG00044,
    escape_gImage_IMG00045,
    escape_gImage_IMG00046,
    escape_gImage_IMG00047,
    escape_gImage_IMG00048,
    escape_gImage_IMG00049,
    escape_gImage_IMG00050,
    escape_gImage_IMG00051,
    escape_gImage_IMG00052,
    escape_gImage_IMG00053,
    escape_gImage_IMG00054,
    escape_gImage_IMG00055,
    escape_gImage_IMG00056,
    escape_gImage_IMG00057,
    escape_gImage_IMG00058,
    escape_gImage_IMG00059,
    escape_gImage_IMG00060,
    escape_gImage_IMG00061,
    escape_gImage_IMG00062,
    escape_gImage_IMG00063,
    escape_gImage_IMG00064,
    escape_gImage_IMG00065,
    escape_gImage_IMG00066,
    escape_gImage_IMG00067,
    escape_gImage_IMG00068
};
const int escape_total_frames = sizeof(escape_gif_frames) / sizeof(escape_gif_frames[0]);

const unsigned char* beady_gif_frames[] = {
    beady_gImage_IMG00000,
    beady_gImage_IMG00001,
    beady_gImage_IMG00002,
    beady_gImage_IMG00003,
    beady_gImage_IMG00004,
    beady_gImage_IMG00005,
    beady_gImage_IMG00006,
    beady_gImage_IMG00007,
    beady_gImage_IMG00008,
    beady_gImage_IMG00009,
    beady_gImage_IMG00010,
    beady_gImage_IMG00011,
    beady_gImage_IMG00012,
    beady_gImage_IMG00013,
    beady_gImage_IMG00014,
    beady_gImage_IMG00015,
    beady_gImage_IMG00016,
    beady_gImage_IMG00017,
    beady_gImage_IMG00018,
    beady_gImage_IMG00019,
    beady_gImage_IMG00020,
    beady_gImage_IMG00021,
    beady_gImage_IMG00022,
    beady_gImage_IMG00023,
    beady_gImage_IMG00024,
    beady_gImage_IMG00025,
    beady_gImage_IMG00026
};
const int beady_total_frames = sizeof(beady_gif_frames) / sizeof(beady_gif_frames[0]);

const unsigned char* dance_gif_frames[] = {
    dance_gImage_IMG00000,
    dance_gImage_IMG00001,
    dance_gImage_IMG00002,
    dance_gImage_IMG00003,
    dance_gImage_IMG00004,
    dance_gImage_IMG00005,
    dance_gImage_IMG00006,
    dance_gImage_IMG00007,
    dance_gImage_IMG00008,
    dance_gImage_IMG00009,
    dance_gImage_IMG00010,
    dance_gImage_IMG00011,
    dance_gImage_IMG00012,
    dance_gImage_IMG00013,
    dance_gImage_IMG00014,
    dance_gImage_IMG00015,
    dance_gImage_IMG00016,
    dance_gImage_IMG00017,
    dance_gImage_IMG00018,
    dance_gImage_IMG00019,
    dance_gImage_IMG00020,
    dance_gImage_IMG00021,
    dance_gImage_IMG00022,
    dance_gImage_IMG00023,
    dance_gImage_IMG00024,
    dance_gImage_IMG00025,
    dance_gImage_IMG00026,
    dance_gImage_IMG00027,
    dance_gImage_IMG00028,
    dance_gImage_IMG00029,
    dance_gImage_IMG00030,
    dance_gImage_IMG00031,
    dance_gImage_IMG00032,
    dance_gImage_IMG00033,
    dance_gImage_IMG00034,
    dance_gImage_IMG00035,
    dance_gImage_IMG00036,
    dance_gImage_IMG00037,
    dance_gImage_IMG00038,
    dance_gImage_IMG00039,
    dance_gImage_IMG00040,
    dance_gImage_IMG00041,
    dance_gImage_IMG00042,
    dance_gImage_IMG00043,
    dance_gImage_IMG00044,
    dance_gImage_IMG00045,
    dance_gImage_IMG00046,
    dance_gImage_IMG00047,
    dance_gImage_IMG00048,
    dance_gImage_IMG00049,
    dance_gImage_IMG00050,
    dance_gImage_IMG00051,
    dance_gImage_IMG00052,
    dance_gImage_IMG00053,
    dance_gImage_IMG00054,
    dance_gImage_IMG00055,
    dance_gImage_IMG00056,
    dance_gImage_IMG00057,
    dance_gImage_IMG00058,
    dance_gImage_IMG00059,
    dance_gImage_IMG00060,
    dance_gImage_IMG00061,
    dance_gImage_IMG00062,
    dance_gImage_IMG00063,
    dance_gImage_IMG00064,
    dance_gImage_IMG00065,
    dance_gImage_IMG00066,
    dance_gImage_IMG00067,
    dance_gImage_IMG00068,
    dance_gImage_IMG00069,
    dance_gImage_IMG00070,
    dance_gImage_IMG00071,
    dance_gImage_IMG00072,
    dance_gImage_IMG00073,
    dance_gImage_IMG00074,
    dance_gImage_IMG00075,
    dance_gImage_IMG00076,
    dance_gImage_IMG00077,
    dance_gImage_IMG00078,
    dance_gImage_IMG00079,
    dance_gImage_IMG00080,
    dance_gImage_IMG00081,
    dance_gImage_IMG00082,
    dance_gImage_IMG00083,
    dance_gImage_IMG00084,
    dance_gImage_IMG00085,
    dance_gImage_IMG00086,
    dance_gImage_IMG00087,
    dance_gImage_IMG00088,
    dance_gImage_IMG00089,
    dance_gImage_IMG00090,
    dance_gImage_IMG00091,
    dance_gImage_IMG00092,
    dance_gImage_IMG00093,
    dance_gImage_IMG00094,
    dance_gImage_IMG00095,
    dance_gImage_IMG00096,
    dance_gImage_IMG00097,
    dance_gImage_IMG00098,
    dance_gImage_IMG00099,
    dance_gImage_IMG00100,
    dance_gImage_IMG00101,
    dance_gImage_IMG00102,
    dance_gImage_IMG00103,
    dance_gImage_IMG00104,
    dance_gImage_IMG00105,
    dance_gImage_IMG00106
};
const int dance_total_frames = sizeof(dance_gif_frames) / sizeof(dance_gif_frames[0]);



const unsigned char* bath_gif_frames[] = {
    bath_gImage_IMG00000,
    bath_gImage_IMG00001,
    bath_gImage_IMG00002,
    bath_gImage_IMG00003,
    bath_gImage_IMG00004,
    bath_gImage_IMG00005,
    bath_gImage_IMG00006,
    bath_gImage_IMG00007,
    bath_gImage_IMG00008,
    bath_gImage_IMG00009,
    bath_gImage_IMG00010,
    bath_gImage_IMG00011,
    bath_gImage_IMG00012,
    bath_gImage_IMG00013,
    bath_gImage_IMG00014,
    bath_gImage_IMG00015,
    bath_gImage_IMG00016,
    bath_gImage_IMG00017,
    bath_gImage_IMG00018,
    bath_gImage_IMG00019,
    bath_gImage_IMG00020,
    bath_gImage_IMG00021,
    bath_gImage_IMG00022,
    bath_gImage_IMG00023,
    bath_gImage_IMG00024,
    bath_gImage_IMG00025,
    bath_gImage_IMG00026,
    bath_gImage_IMG00027,
    bath_gImage_IMG00028,
    bath_gImage_IMG00029,
    bath_gImage_IMG00030,
    bath_gImage_IMG00031,
    bath_gImage_IMG00032,
    bath_gImage_IMG00033,
    bath_gImage_IMG00034,
    bath_gImage_IMG00035,
    bath_gImage_IMG00036,
    bath_gImage_IMG00037,
    bath_gImage_IMG00038,
    bath_gImage_IMG00039,
    bath_gImage_IMG00040,
    bath_gImage_IMG00041,
    bath_gImage_IMG00042,
    bath_gImage_IMG00043,
    bath_gImage_IMG00044,
    bath_gImage_IMG00045,
    bath_gImage_IMG00046,
    bath_gImage_IMG00047,
    bath_gImage_IMG00048,
    bath_gImage_IMG00049,
    bath_gImage_IMG00050,
    bath_gImage_IMG00051,
    bath_gImage_IMG00052,
    bath_gImage_IMG00053,
    bath_gImage_IMG00054,
    bath_gImage_IMG00055,
    bath_gImage_IMG00056,
    bath_gImage_IMG00057,
    bath_gImage_IMG00058,
    bath_gImage_IMG00059
};
const int bath_total_frames = sizeof(bath_gif_frames) / sizeof(bath_gif_frames[0]);

void MyLibrary::begin(int roation) {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    if (roation != -1) {
        display.setRotation(roation);
    }
    display.clearDisplay();
    display.display();
}

void MyLibrary::setFrameDelay(int delayMs) {
    frameDelay = delayMs;
}

// 获取当前帧间隔
int MyLibrary::getFrameDelay() const {
    return frameDelay;
}

void MyLibrary::show(DisplayModel model) {
    if (model != currentModel) {
        currentFrame = 0;          // 切换模式时重置帧索引
        currentModel = model;      // 更新当前模式
        lastFrameTime = millis();  // 重置时间戳以立即开始新动画
    }
}

// turnOff Order
void MyLibrary::turnOffScreen() {
    // 关闭显示命令 (0xAE)
    display.ssd1306_command(SSD1306_DISPLAYOFF);
}
// turnon Order
void MyLibrary::turnOnScreen() {
    // 开启显示命令 
    display.ssd1306_command(SSD1306_DISPLAYON);
    display.clearDisplay();  // 清除残留画面
    display.display();       // 确保刷新
}

void MyLibrary::update() {
    unsigned long currentTime = millis();
    
    // 检查是否达到帧间隔时间
    if (currentTime - lastFrameTime >= frameDelay) {
        lastFrameTime = currentTime;  // 更新上次绘制时间
        display.clearDisplay();       // 清空显示缓冲区
        
        // 根据当前模式绘制对应帧
        switch (currentModel) {
            case DisplayModel::CRY:
                display.drawBitmap(0, 0, cry_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % cry_total_frames; 
                break;
            case DisplayModel::BOOK:
                display.drawBitmap(0, 0, book_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % book_total_frames; 
                break;
            case DisplayModel::BIRDVISIT:
                display.drawBitmap(0, 0, birdvisit_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % birdvisit_total_frames; 
                break;
            case DisplayModel::CAKE:
                display.drawBitmap(0, 0, cake_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % cake_total_frames; 
                break;
            case DisplayModel::SNOW:
                display.drawBitmap(0, 0, snow_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % snow_total_frames; 
                break;
            case DisplayModel::TRANSFORMERS:
                display.drawBitmap(0, 0, transformers_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % transformers_total_frames; 
                break;
            case DisplayModel::SNEEZE:
                display.drawBitmap(0, 0, sneeze_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % sneeze_total_frames; 
                break;
            case DisplayModel::EYEBROW:
                display.drawBitmap(0, 0, eyebrow_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % eyebrow_total_frames; 
                break;
            case DisplayModel::ESCAPE:
                display.drawBitmap(0, 0, escape_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % escape_total_frames; 
                break;
            case DisplayModel::BEADY:
                display.drawBitmap(0, 0, beady_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % beady_total_frames; 
                break;
            case DisplayModel::DANCE:
                display.drawBitmap(0, 0, dance_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % dance_total_frames; 
                break;
            case DisplayModel::BATH:
                display.drawBitmap(0, 0, bath_gif_frames[currentFrame], 128, 64, SSD1306_WHITE);
                currentFrame = (currentFrame + 1) % bath_total_frames;  // 循环播放
                break;
            case DisplayModel::INVALID:
                // 未选择有效模式时不绘制
                break;
        }
        
        display.display();  // 显示当前帧
    }
}
