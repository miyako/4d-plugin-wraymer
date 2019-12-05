#ifndef __wraycam_h__
#define __wraycam_h__

/* Version: 39.15485.2019.0901 */
/*
   Platform & Architecture:
       (1) Win32:
              (a) x86: XP SP3 or above; CPU supports SSE2 instruction set or above
              (b) x64: Win7 or above
              (c) arm: Win10 or above
              (d) arm64: Win10 or above
       (2) WinRT: x86, x64, arm, arm64; Win10 or above
       (3) macOS: universal (x64 + x86); macOS 10.10 or above
       (4) Linux: kernel 2.6.27 or above
              (a) x86: CPU supports SSE3 instruction set or above; GLIBC 2.8 or above
              (b) x64: GLIBC 2.14 or above
              (c) armel: GLIBC 2.17 or above; built by toolchain arm-linux-gnueabi (version 4.9.2)
              (d) armhf: GLIBC 2.17 or above; built by toolchain arm-linux-gnueabihf (version 4.9.2)
              (e) arm64: GLIBC 2.17 or above; built by toolchain aarch64-linux-gnu (version 4.9.2)
       (5) Android: arm, arm64, x86, x64; built by android-ndk-r18b; __ANDROID_API__ = 23
*/
/*
    doc:
       (1) en.html, English
       (2) hans.html, Simplified Chinese
*/

#ifdef _WIN32
#ifndef _INC_WINDOWS
#include <windows.h>
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__cplusplus) && (__cplusplus >= 201402L)
#define WRAYCAM_DEPRECATED  [[deprecated]]
#elif defined(_MSC_VER)
#define WRAYCAM_DEPRECATED  __declspec(deprecated)
#elif defined(__GNUC__) || defined(__clang__)
#define WRAYCAM_DEPRECATED  __attribute__((deprecated))
#else
#define WRAYCAM_DEPRECATED
#endif

#ifdef _WIN32 /* Windows */

#pragma pack(push, 8)
#ifdef WRAYCAM_EXPORTS
#define WRAYCAM_API(x)    __declspec(dllexport)   x   __stdcall  /* in Windows, we use __stdcall calling convention, see https://docs.microsoft.com/en-us/cpp/cpp/stdcall */
#elif !defined(WRAYCAM_NOIMPORTS)
#define WRAYCAM_API(x)    __declspec(dllimport)   x   __stdcall
#else
#define WRAYCAM_API(x)    x   __stdcall
#endif

#else   /* Linux or macOS */

#define WRAYCAM_API(x)    x
#if (!defined(HRESULT)) && (!defined(__COREFOUNDATION_CFPLUGINCOM__)) /* CFPlugInCOM.h */
#define HRESULT int
#endif
#ifndef SUCCEEDED
#define SUCCEEDED(hr)   (((HRESULT)(hr)) >= 0)
#endif
#ifndef FAILED
#define FAILED(hr)      (((HRESULT)(hr)) < 0)
#endif

#ifndef __stdcall
#define __stdcall
#endif

#ifndef __BITMAPINFOHEADER_DEFINED__
#define __BITMAPINFOHEADER_DEFINED__
typedef struct {
    unsigned        biSize;
    int             biWidth;
    int             biHeight;
    unsigned short  biPlanes;
    unsigned short  biBitCount;
    unsigned        biCompression;
    unsigned        biSizeImage;
    int             biXPelsPerMeter;
    int             biYPelsPerMeter;
    unsigned        biClrUsed;
    unsigned        biClrImportant;
} BITMAPINFOHEADER;
#endif

#ifndef __RECT_DEFINED__
#define __RECT_DEFINED__
typedef struct {
    int left;
    int top;
    int right;
    int bottom;
} RECT, *PRECT;
#endif

#endif

#ifndef TDIBWIDTHBYTES
#define TDIBWIDTHBYTES(bits)  ((unsigned)(((bits) + 31) & (~31)) / 8)
#endif

/********************************************************************************/
/* HRESULT                                                                      */
/*    |----------------|---------------------------------------|------------|   */
/*    | S_OK           |   Operation successful                | 0x00000000 |   */
/*    | S_FALSE        |   Operation successful                | 0x00000001 |   */
/*    | E_FAIL         |   Unspecified failure                 | 0x80004005 |   */
/*    | E_ACCESSDENIED |   General access denied error         | 0x80070005 |   */
/*    | E_INVALIDARG   |   One or more arguments are not valid | 0x80070057 |   */
/*    | E_NOTIMPL      |   Not supported or not implemented    | 0x80004001 |   */
/*    | E_NOINTERFACE  |   Interface not supported             | 0x80004002 |   */
/*    | E_POINTER      |   Pointer that is not valid           | 0x80004003 |   */
/*    | E_UNEXPECTED   |   Unexpected failure                  | 0x8000FFFF |   */
/*    | E_OUTOFMEMORY  |   Out of memory                       | 0x8007000E |   */
/*    | E_WRONG_THREAD |   call function in the wrong thread   | 0x8001010E |   */
/*    | E_GEN_FAILURE  |   device not functioning              | 0x8007001F |   */
/*    |----------------|---------------------------------------|------------|   */
/********************************************************************************/

/* handle */
typedef struct WraycamT { int unused; } *HWraycam, *HToupCam;

#define WRAYCAM_MAX                      16
                                         
#define WRAYCAM_FLAG_CMOS                0x00000001  /* cmos sensor */
#define WRAYCAM_FLAG_CCD_PROGRESSIVE     0x00000002  /* progressive ccd sensor */
#define WRAYCAM_FLAG_CCD_INTERLACED      0x00000004  /* interlaced ccd sensor */
#define WRAYCAM_FLAG_ROI_HARDWARE        0x00000008  /* support hardware ROI */
#define WRAYCAM_FLAG_MONO                0x00000010  /* monochromatic */
#define WRAYCAM_FLAG_BINSKIP_SUPPORTED   0x00000020  /* support bin/skip mode, see Wraycam_put_Mode and Wraycam_get_Mode */
#define WRAYCAM_FLAG_USB30               0x00000040  /* usb3.0 */
#define WRAYCAM_FLAG_TEC                 0x00000080  /* Thermoelectric Cooler */
#define WRAYCAM_FLAG_USB30_OVER_USB20    0x00000100  /* usb3.0 camera connected to usb2.0 port */
#define WRAYCAM_FLAG_ST4                 0x00000200  /* ST4 port */
#define WRAYCAM_FLAG_GETTEMPERATURE      0x00000400  /* support to get the temperature of the sensor */
#define WRAYCAM_FLAG_PUTTEMPERATURE      0x00000800  /* support to put the target temperature of the sensor */
#define WRAYCAM_FLAG_RAW10               0x00001000  /* pixel format, RAW 10bits */
#define WRAYCAM_FLAG_RAW12               0x00002000  /* pixel format, RAW 12bits */
#define WRAYCAM_FLAG_RAW14               0x00004000  /* pixel format, RAW 14bits */
#define WRAYCAM_FLAG_RAW16               0x00008000  /* pixel format, RAW 16bits */
#define WRAYCAM_FLAG_FAN                 0x00010000  /* cooling fan */
#define WRAYCAM_FLAG_TEC_ONOFF           0x00020000  /* Thermoelectric Cooler can be turn on or off, support to set the target temperature of TEC */
#define WRAYCAM_FLAG_ISP                 0x00040000  /* ISP (Image Signal Processing) chip */
#define WRAYCAM_FLAG_TRIGGER_SOFTWARE    0x00080000  /* support software trigger */
#define WRAYCAM_FLAG_TRIGGER_EXTERNAL    0x00100000  /* support external trigger */
#define WRAYCAM_FLAG_TRIGGER_SINGLE      0x00200000  /* only support trigger single: one trigger, one image */
#define WRAYCAM_FLAG_BLACKLEVEL          0x00400000  /* support set and get the black level */
#define WRAYCAM_FLAG_AUTO_FOCUS          0x00800000  /* support auto focus */
#define WRAYCAM_FLAG_BUFFER              0x01000000  /* frame buffer */
#define WRAYCAM_FLAG_DDR                 0x02000000  /* use very large capacity DDR (Double Data Rate SDRAM) for frame buffer */
#define WRAYCAM_FLAG_CG                  0x04000000  /* Conversion Gain: HCG, LCG */
#define WRAYCAM_FLAG_YUV411              0x08000000  /* pixel format, yuv411 */
#define WRAYCAM_FLAG_VUYY                0x10000000  /* pixel format, yuv422, VUYY */
#define WRAYCAM_FLAG_YUV444              0x20000000  /* pixel format, yuv444 */
#define WRAYCAM_FLAG_RGB888              0x40000000  /* pixel format, RGB888 */
#define WRAYCAM_FLAG_RAW8                0x80000000  /* pixel format, RAW 8 bits */
#define WRAYCAM_FLAG_GMCY8               0x0000000100000000  /* pixel format, GMCY, 8bits */
#define WRAYCAM_FLAG_GMCY12              0x0000000200000000  /* pixel format, GMCY, 12bits */
#define WRAYCAM_FLAG_UYVY                0x0000000400000000  /* pixel format, yuv422, UYVY */
#define WRAYCAM_FLAG_CGHDR               0x0000000800000000  /* Conversion Gain: HCG, LCG, HDR */
#define WRAYCAM_FLAG_GLOBALSHUTTER       0x0000001000000000  /* global shutter */
#define WRAYCAM_FLAG_FOCUSMOTOR          0x0000002000000000  /* support focus motor */

#define WRAYCAM_TEMP_DEF                 6503    /* temp */
#define WRAYCAM_TEMP_MIN                 2000    /* temp */
#define WRAYCAM_TEMP_MAX                 15000   /* temp */
#define WRAYCAM_TINT_DEF                 1000    /* tint */
#define WRAYCAM_TINT_MIN                 200     /* tint */
#define WRAYCAM_TINT_MAX                 2500    /* tint */
#define WRAYCAM_HUE_DEF                  0       /* hue */
#define WRAYCAM_HUE_MIN                  (-180)  /* hue */
#define WRAYCAM_HUE_MAX                  180     /* hue */
#define WRAYCAM_SATURATION_DEF           128     /* saturation */
#define WRAYCAM_SATURATION_MIN           0       /* saturation */
#define WRAYCAM_SATURATION_MAX           255     /* saturation */
#define WRAYCAM_BRIGHTNESS_DEF           0       /* brightness */
#define WRAYCAM_BRIGHTNESS_MIN           (-64)   /* brightness */
#define WRAYCAM_BRIGHTNESS_MAX           64      /* brightness */
#define WRAYCAM_CONTRAST_DEF             0       /* contrast */
#define WRAYCAM_CONTRAST_MIN             (-100)  /* contrast */
#define WRAYCAM_CONTRAST_MAX             100     /* contrast */
#define WRAYCAM_GAMMA_DEF                100     /* gamma */
#define WRAYCAM_GAMMA_MIN                20      /* gamma */
#define WRAYCAM_GAMMA_MAX                180     /* gamma */
#define WRAYCAM_AETARGET_DEF             120     /* target of auto exposure */
#define WRAYCAM_AETARGET_MIN             16      /* target of auto exposure */
#define WRAYCAM_AETARGET_MAX             220     /* target of auto exposure */
#define WRAYCAM_WBGAIN_DEF               0       /* white balance gain */
#define WRAYCAM_WBGAIN_MIN               (-127)  /* white balance gain */
#define WRAYCAM_WBGAIN_MAX               127     /* white balance gain */
#define WRAYCAM_BLACKLEVEL_MIN           0       /* minimum black level */
#define WRAYCAM_BLACKLEVEL8_MAX          31              /* maximum black level for bit depth = 8 */
#define WRAYCAM_BLACKLEVEL10_MAX         (31 * 4)        /* maximum black level for bit depth = 10 */
#define WRAYCAM_BLACKLEVEL12_MAX         (31 * 16)       /* maximum black level for bit depth = 12 */
#define WRAYCAM_BLACKLEVEL14_MAX         (31 * 64)       /* maximum black level for bit depth = 14 */
#define WRAYCAM_BLACKLEVEL16_MAX         (31 * 256)      /* maximum black level for bit depth = 16 */
#define WRAYCAM_SHARPENING_STRENGTH_DEF  0       /* sharpening strength */
#define WRAYCAM_SHARPENING_STRENGTH_MIN  0       /* sharpening strength */
#define WRAYCAM_SHARPENING_STRENGTH_MAX  500     /* sharpening strength */
#define WRAYCAM_SHARPENING_RADIUS_DEF    2       /* sharpening radius */
#define WRAYCAM_SHARPENING_RADIUS_MIN    1       /* sharpening radius */
#define WRAYCAM_SHARPENING_RADIUS_MAX    10      /* sharpening radius */
#define WRAYCAM_SHARPENING_THRESHOLD_DEF 0       /* sharpening threshold */
#define WRAYCAM_SHARPENING_THRESHOLD_MIN 0       /* sharpening threshold */
#define WRAYCAM_SHARPENING_THRESHOLD_MAX 255     /* sharpening threshold */
#define WRAYCAM_AUTOEXPO_THRESHOLD_DEF   5       /* auto exposure threshold */
#define WRAYCAM_AUTOEXPO_THRESHOLD_MIN   5       /* auto exposure threshold */
#define WRAYCAM_AUTOEXPO_THRESHOLD_MAX   25      /* auto exposure threshold */

typedef struct{
    unsigned    width;
    unsigned    height;
}WraycamResolution;

/* In Windows platform, we always use UNICODE wchar_t */
/* In Linux or macOS, we use char */

typedef struct {
#ifdef _WIN32
    const wchar_t*      name;        /* model name, in Windows, we use unicode */
#else
    const char*         name;        /* model name */
#endif
    unsigned long long  flag;        /* WRAYCAM_FLAG_xxx, 64 bits */
    unsigned            maxspeed;    /* number of speed level, same as Wraycam_get_MaxSpeed(), the speed range = [0, maxspeed], closed interval */
    unsigned            preview;     /* number of preview resolution, same as Wraycam_get_ResolutionNumber() */
    unsigned            still;       /* number of still resolution, same as Wraycam_get_StillResolutionNumber() */
    unsigned            maxfanspeed; /* maximum fan speed */
    unsigned            ioctrol;     /* number of input/output control */
    float               xpixsz;      /* physical pixel size */
    float               ypixsz;      /* physical pixel size */
    WraycamResolution   res[WRAYCAM_MAX];
}WraycamModelV2; /* camera model v2 */

typedef struct {
#ifdef _WIN32
    wchar_t               displayname[64];    /* display name */
    wchar_t               id[64];             /* unique and opaque id of a connected camera, for Wraycam_Open */
#else
    char                  displayname[64];    /* display name */
    char                  id[64];             /* unique and opaque id of a connected camera, for Wraycam_Open */
#endif
    const WraycamModelV2* model;
}WraycamDeviceV2, WraycamInstV2; /* camera instance for enumerating */

/*
    get the version of this dll/so/dylib, which is: 39.15485.2019.0901
*/
#ifdef _WIN32
WRAYCAM_API(const wchar_t*)   Wraycam_Version();
#else
WRAYCAM_API(const char*)      Wraycam_Version();
#endif

/*
    enumerate the cameras connected to the computer, return the number of enumerated.

    WraycamDeviceV2 arr[WRAYCAM_MAX];
    unsigned cnt = Wraycam_EnumV2(arr);
    for (unsigned i = 0; i < cnt; ++i)
        ...

    if pti == NULL, then, only the number is returned.
    Wraycam_Enum is obsolete.
*/
WRAYCAM_API(unsigned) Wraycam_EnumV2(WraycamDeviceV2 pti[WRAYCAM_MAX]);

/* use the id of WraycamDeviceV2, which is enumerated by Wraycam_EnumV2.
    if id is NULL, Wraycam_Open will open the first camera.
*/
#ifdef _WIN32
WRAYCAM_API(HWraycam) Wraycam_Open(const wchar_t* id);
#else
WRAYCAM_API(HWraycam) Wraycam_Open(const char* id);
#endif

/*
    the same with Wraycam_Open, but use the index as the parameter. such as:
    index == 0, open the first camera,
    index == 1, open the second camera,
    etc
*/
WRAYCAM_API(HWraycam) Wraycam_OpenByIndex(unsigned index);

WRAYCAM_API(void)     Wraycam_Close(HWraycam h); /* close the handle */

#define WRAYCAM_EVENT_EXPOSURE      0x0001    /* exposure time changed */
#define WRAYCAM_EVENT_TEMPTINT      0x0002    /* white balance changed, Temp/Tint mode */
#define WRAYCAM_EVENT_IMAGE         0x0004    /* live image arrived, use Wraycam_PullImage to get this image */
#define WRAYCAM_EVENT_STILLIMAGE    0x0005    /* snap (still) frame arrived, use Wraycam_PullStillImage to get this frame */
#define WRAYCAM_EVENT_WBGAIN        0x0006    /* white balance changed, RGB Gain mode */
#define WRAYCAM_EVENT_TRIGGERFAIL   0x0007    /* trigger failed */
#define WRAYCAM_EVENT_BLACK         0x0008    /* black balance changed */
#define WRAYCAM_EVENT_FFC           0x0009    /* flat field correction status changed */
#define WRAYCAM_EVENT_DFC           0x000a    /* dark field correction status changed */
#define WRAYCAM_EVENT_ERROR         0x0080    /* generic error */
#define WRAYCAM_EVENT_DISCONNECTED  0x0081    /* camera disconnected */
#define WRAYCAM_EVENT_TIMEOUT       0x0082    /* timeout error */
#define WRAYCAM_EVENT_AFFEEDBACK    0x0083    /* auto focus feedback information */
#define WRAYCAM_EVENT_AFPOSITION    0x0084    /* auto focus sensor board positon */
#define WRAYCAM_EVENT_FACTORY       0x8001    /* restore factory settings */

#ifdef _WIN32
WRAYCAM_API(HRESULT)  Wraycam_StartPullModeWithWndMsg(HWraycam h, HWND hWnd, UINT nMsg);
#endif

/* Do NOT call Wraycam_Close, Wraycam_Stop in this callback context, it deadlocks. */
typedef void (__stdcall* PWRAYCAM_EVENT_CALLBACK)(unsigned nEvent, void* pCallbackCtx);
WRAYCAM_API(HRESULT)  Wraycam_StartPullModeWithCallback(HWraycam h, PWRAYCAM_EVENT_CALLBACK pEventCallback, void* pCallbackContext);

#define WRAYCAM_FRAMEINFO_FLAG_SEQ          0x01 /* sequence number */
#define WRAYCAM_FRAMEINFO_FLAG_TIMESTAMP    0x02 /* timestamp */

typedef struct {
    unsigned            width;
    unsigned            height;
    unsigned            flag;       /* WRAYCAM_FRAMEINFO_FLAG_xxxx */
    unsigned            seq;        /* sequence number */
    unsigned long long  timestamp;  /* microsecond */
}WraycamFrameInfoV2;

/*
    bits: 24 (RGB24), 32 (RGB32), 8 (Gray) or 16 (Gray). In RAW mode, this parameter is ignored.
    pnWidth, pnHeight: OUT parameter
    rowPitch: The distance from one row to the next row. rowPitch = 0 means using the default row pitch.
*/
WRAYCAM_API(HRESULT)  Wraycam_PullImageV2(HWraycam h, void* pImageData, int bits, WraycamFrameInfoV2* pInfo);
WRAYCAM_API(HRESULT)  Wraycam_PullStillImageV2(HWraycam h, void* pImageData, int bits, WraycamFrameInfoV2* pInfo);
WRAYCAM_API(HRESULT)  Wraycam_PullImageWithRowPitchV2(HWraycam h, void* pImageData, int bits, int rowPitch, WraycamFrameInfoV2* pInfo);
WRAYCAM_API(HRESULT)  Wraycam_PullStillImageWithRowPitchV2(HWraycam h, void* pImageData, int bits, int rowPitch, WraycamFrameInfoV2* pInfo);

WRAYCAM_API(HRESULT)  Wraycam_PullImage(HWraycam h, void* pImageData, int bits, unsigned* pnWidth, unsigned* pnHeight);
WRAYCAM_API(HRESULT)  Wraycam_PullStillImage(HWraycam h, void* pImageData, int bits, unsigned* pnWidth, unsigned* pnHeight);
WRAYCAM_API(HRESULT)  Wraycam_PullImageWithRowPitch(HWraycam h, void* pImageData, int bits, int rowPitch, unsigned* pnWidth, unsigned* pnHeight);
WRAYCAM_API(HRESULT)  Wraycam_PullStillImageWithRowPitch(HWraycam h, void* pImageData, int bits, int rowPitch, unsigned* pnWidth, unsigned* pnHeight);

/*
    (NULL == pData) means that something is error
    pCallbackCtx is the callback context which is passed by Wraycam_StartPushModeV3
    bSnap: TRUE if Wraycam_Snap

    pDataCallback is callbacked by an internal thread of wraycam.dll, so please pay attention to multithread problem.
    Do NOT call Wraycam_Close, Wraycam_Stop in this callback context, it deadlocks.
*/
typedef void (__stdcall* PWRAYCAM_DATA_CALLBACK_V3)(const void* pData, const WraycamFrameInfoV2* pInfo, int bSnap, void* pCallbackCtx);
WRAYCAM_API(HRESULT)  Wraycam_StartPushModeV3(HWraycam h, PWRAYCAM_DATA_CALLBACK_V3 pDataCallback, void* pDataCallbackCtx, PWRAYCAM_EVENT_CALLBACK pEventCallback, void* pEventCallbackContext);

WRAYCAM_API(HRESULT)  Wraycam_Stop(HWraycam h);
WRAYCAM_API(HRESULT)  Wraycam_Pause(HWraycam h, int bPause);

/*  for pull mode: WRAYCAM_EVENT_STILLIMAGE, and then Wraycam_PullStillImage
    for push mode: the snapped image will be return by PWRAYCAM_DATA_CALLBACK(V2), with the parameter 'bSnap' set to 'TRUE'
*/
WRAYCAM_API(HRESULT)  Wraycam_Snap(HWraycam h, unsigned nResolutionIndex);  /* still image snap */
WRAYCAM_API(HRESULT)  Wraycam_SnapN(HWraycam h, unsigned nResolutionIndex, unsigned nNumber);  /* multiple still image snap */
/*
    soft trigger:
    nNumber:    0xffff:     trigger continuously
                0:          cancel trigger
                others:     number of images to be triggered
*/
WRAYCAM_API(HRESULT)  Wraycam_Trigger(HWraycam h, unsigned short nNumber);

/*
    put_Size, put_eSize, can be used to set the video output resolution BEFORE Wraycam_Start.
    put_Size use width and height parameters, put_eSize use the index parameter.
    for example, UCMOS03100KPA support the following resolutions:
            index 0:    2048,   1536
            index 1:    1024,   768
            index 2:    680,    510
    so, we can use put_Size(h, 1024, 768) or put_eSize(h, 1). Both have the same effect.
*/
WRAYCAM_API(HRESULT)  Wraycam_put_Size(HWraycam h, int nWidth, int nHeight);
WRAYCAM_API(HRESULT)  Wraycam_get_Size(HWraycam h, int* pWidth, int* pHeight);
WRAYCAM_API(HRESULT)  Wraycam_put_eSize(HWraycam h, unsigned nResolutionIndex);
WRAYCAM_API(HRESULT)  Wraycam_get_eSize(HWraycam h, unsigned* pnResolutionIndex);

WRAYCAM_API(HRESULT)  Wraycam_get_ResolutionNumber(HWraycam h);
WRAYCAM_API(HRESULT)  Wraycam_get_Resolution(HWraycam h, unsigned nResolutionIndex, int* pWidth, int* pHeight);
/*
    numerator/denominator, such as: 1/1, 1/2, 1/3
*/
WRAYCAM_API(HRESULT)  Wraycam_get_ResolutionRatio(HWraycam h, unsigned nResolutionIndex, int* pNumerator, int* pDenominator);
WRAYCAM_API(HRESULT)  Wraycam_get_Field(HWraycam h);

/*
see: http://www.fourcc.org
FourCC:
    MAKEFOURCC('G', 'B', 'R', 'G'), see http://www.siliconimaging.com/RGB%20Bayer.htm
    MAKEFOURCC('R', 'G', 'G', 'B')
    MAKEFOURCC('B', 'G', 'G', 'R')
    MAKEFOURCC('G', 'R', 'B', 'G')
    MAKEFOURCC('Y', 'Y', 'Y', 'Y'), monochromatic sensor
    MAKEFOURCC('Y', '4', '1', '1'), yuv411
    MAKEFOURCC('V', 'U', 'Y', 'Y'), yuv422
    MAKEFOURCC('U', 'Y', 'V', 'Y'), yuv422
    MAKEFOURCC('Y', '4', '4', '4'), yuv444
    MAKEFOURCC('R', 'G', 'B', '8'), RGB888

#ifndef MAKEFOURCC
#define MAKEFOURCC(a, b, c, d) ((unsigned)(unsigned char)(a) | ((unsigned)(unsigned char)(b) << 8) | ((unsigned)(unsigned char)(c) << 16) | ((unsigned)(unsigned char)(d) << 24))
#endif
*/
WRAYCAM_API(HRESULT)  Wraycam_get_RawFormat(HWraycam h, unsigned* nFourCC, unsigned* bitsperpixel);

/*
    ------------------------------------------------------------------|
    | Parameter               |   Range       |   Default             |
    |-----------------------------------------------------------------|
    | Auto Exposure Target    |   10~230      |   120                 |
    | Temp                    |   2000~15000  |   6503                |
    | Tint                    |   200~2500    |   1000                |
    | LevelRange              |   0~255       |   Low = 0, High = 255 |
    | Contrast                |   -100~100    |   0                   |
    | Hue                     |   -180~180    |   0                   |
    | Saturation              |   0~255       |   128                 |
    | Brightness              |   -64~64      |   0                   |
    | Gamma                   |   20~180      |   100                 |
    | WBGain                  |   -127~127    |   0                   |
    ------------------------------------------------------------------|
*/

#ifndef __WRAYCAM_CALLBACK_DEFINED__
#define __WRAYCAM_CALLBACK_DEFINED__
typedef void (__stdcall* PIWRAYCAM_EXPOSURE_CALLBACK)(void* pCtx);                                     /* auto exposure */
typedef void (__stdcall* PIWRAYCAM_WHITEBALANCE_CALLBACK)(const int aGain[3], void* pCtx);             /* one push white balance, RGB Gain mode */
typedef void (__stdcall* PIWRAYCAM_BLACKBALANCE_CALLBACK)(const unsigned short aSub[3], void* pCtx);   /* one push black balance */
typedef void (__stdcall* PIWRAYCAM_TEMPTINT_CALLBACK)(const int nTemp, const int nTint, void* pCtx);   /* one push white balance, Temp/Tint Mode */
typedef void (__stdcall* PIWRAYCAM_HISTOGRAM_CALLBACK)(const float aHistY[256], const float aHistR[256], const float aHistG[256], const float aHistB[256], void* pCtx);
typedef void (__stdcall* PIWRAYCAM_CHROME_CALLBACK)(void* pCtx);
#endif

WRAYCAM_API(HRESULT)  Wraycam_get_AutoExpoEnable(HWraycam h, int* bAutoExposure);
WRAYCAM_API(HRESULT)  Wraycam_put_AutoExpoEnable(HWraycam h, int bAutoExposure);
WRAYCAM_API(HRESULT)  Wraycam_get_AutoExpoTarget(HWraycam h, unsigned short* Target);
WRAYCAM_API(HRESULT)  Wraycam_put_AutoExpoTarget(HWraycam h, unsigned short Target);

/*set the maximum/minimal auto exposure time and agin. The default maximum auto exposure time is 350ms */
WRAYCAM_API(HRESULT)  Wraycam_put_MaxAutoExpoTimeAGain(HWraycam h, unsigned maxTime, unsigned short maxAGain);
WRAYCAM_API(HRESULT)  Wraycam_get_MaxAutoExpoTimeAGain(HWraycam h, unsigned* maxTime, unsigned short* maxAGain);
WRAYCAM_API(HRESULT)  Wraycam_put_MinAutoExpoTimeAGain(HWraycam h, unsigned minTime, unsigned short minAGain);
WRAYCAM_API(HRESULT)  Wraycam_get_MinAutoExpoTimeAGain(HWraycam h, unsigned* minTime, unsigned short* minAGain);

WRAYCAM_API(HRESULT)  Wraycam_get_ExpoTime(HWraycam h, unsigned* Time); /* in microseconds */
WRAYCAM_API(HRESULT)  Wraycam_put_ExpoTime(HWraycam h, unsigned Time); /* in microseconds */
WRAYCAM_API(HRESULT)  Wraycam_get_RealExpoTime(HWraycam h, unsigned* Time); /* in microseconds, based on 50HZ/60HZ/DC */
WRAYCAM_API(HRESULT)  Wraycam_get_ExpTimeRange(HWraycam h, unsigned* nMin, unsigned* nMax, unsigned* nDef);

WRAYCAM_API(HRESULT)  Wraycam_get_ExpoAGain(HWraycam h, unsigned short* AGain); /* percent, such as 300 */
WRAYCAM_API(HRESULT)  Wraycam_put_ExpoAGain(HWraycam h, unsigned short AGain); /* percent */
WRAYCAM_API(HRESULT)  Wraycam_get_ExpoAGainRange(HWraycam h, unsigned short* nMin, unsigned short* nMax, unsigned short* nDef);

/* Auto White Balance, Temp/Tint Mode */
WRAYCAM_API(HRESULT)  Wraycam_AwbOnePush(HWraycam h, PIWRAYCAM_TEMPTINT_CALLBACK fnTTProc, void* pTTCtx); /* auto white balance "one push". This function must be called AFTER Wraycam_StartXXXX */

/* Auto White Balance, RGB Gain Mode */
WRAYCAM_API(HRESULT)  Wraycam_AwbInit(HWraycam h, PIWRAYCAM_WHITEBALANCE_CALLBACK fnWBProc, void* pWBCtx);

/* White Balance, Temp/Tint mode */
WRAYCAM_API(HRESULT)  Wraycam_put_TempTint(HWraycam h, int nTemp, int nTint);
WRAYCAM_API(HRESULT)  Wraycam_get_TempTint(HWraycam h, int* nTemp, int* nTint);

/* White Balance, RGB Gain mode */
WRAYCAM_API(HRESULT)  Wraycam_put_WhiteBalanceGain(HWraycam h, int aGain[3]);
WRAYCAM_API(HRESULT)  Wraycam_get_WhiteBalanceGain(HWraycam h, int aGain[3]);

/* Black Balance */
WRAYCAM_API(HRESULT)  Wraycam_AbbOnePush(HWraycam h, PIWRAYCAM_BLACKBALANCE_CALLBACK fnBBProc, void* pBBCtx); /* auto black balance "one push". This function must be called AFTER Wraycam_StartXXXX */
WRAYCAM_API(HRESULT)  Wraycam_put_BlackBalance(HWraycam h, unsigned short aSub[3]);
WRAYCAM_API(HRESULT)  Wraycam_get_BlackBalance(HWraycam h, unsigned short aSub[3]);

/* Flat Field Correction */
WRAYCAM_API(HRESULT)  Wraycam_FfcOnePush(HWraycam h);
#ifdef _WIN32
WRAYCAM_API(HRESULT)  Wraycam_FfcExport(HWraycam h, const wchar_t* filepath);
WRAYCAM_API(HRESULT)  Wraycam_FfcImport(HWraycam h, const wchar_t* filepath);
#else
WRAYCAM_API(HRESULT)  Wraycam_FfcExport(HWraycam h, const char* filepath);
WRAYCAM_API(HRESULT)  Wraycam_FfcImport(HWraycam h, const char* filepath);
#endif

/* Dark Field Correction */
WRAYCAM_API(HRESULT)  Wraycam_DfcOnePush(HWraycam h);

#ifdef _WIN32
WRAYCAM_API(HRESULT)  Wraycam_DfcExport(HWraycam h, const wchar_t* filepath);
WRAYCAM_API(HRESULT)  Wraycam_DfcImport(HWraycam h, const wchar_t* filepath);
#else
WRAYCAM_API(HRESULT)  Wraycam_DfcExport(HWraycam h, const char* filepath);
WRAYCAM_API(HRESULT)  Wraycam_DfcImport(HWraycam h, const char* filepath);
#endif

WRAYCAM_API(HRESULT)  Wraycam_put_Hue(HWraycam h, int Hue);
WRAYCAM_API(HRESULT)  Wraycam_get_Hue(HWraycam h, int* Hue);
WRAYCAM_API(HRESULT)  Wraycam_put_Saturation(HWraycam h, int Saturation);
WRAYCAM_API(HRESULT)  Wraycam_get_Saturation(HWraycam h, int* Saturation);
WRAYCAM_API(HRESULT)  Wraycam_put_Brightness(HWraycam h, int Brightness);
WRAYCAM_API(HRESULT)  Wraycam_get_Brightness(HWraycam h, int* Brightness);
WRAYCAM_API(HRESULT)  Wraycam_get_Contrast(HWraycam h, int* Contrast);
WRAYCAM_API(HRESULT)  Wraycam_put_Contrast(HWraycam h, int Contrast);
WRAYCAM_API(HRESULT)  Wraycam_get_Gamma(HWraycam h, int* Gamma); /* percent */
WRAYCAM_API(HRESULT)  Wraycam_put_Gamma(HWraycam h, int Gamma);  /* percent */

WRAYCAM_API(HRESULT)  Wraycam_get_Chrome(HWraycam h, int* bChrome);  /* monochromatic mode */
WRAYCAM_API(HRESULT)  Wraycam_put_Chrome(HWraycam h, int bChrome);

WRAYCAM_API(HRESULT)  Wraycam_get_VFlip(HWraycam h, int* bVFlip);  /* vertical flip */
WRAYCAM_API(HRESULT)  Wraycam_put_VFlip(HWraycam h, int bVFlip);
WRAYCAM_API(HRESULT)  Wraycam_get_HFlip(HWraycam h, int* bHFlip);
WRAYCAM_API(HRESULT)  Wraycam_put_HFlip(HWraycam h, int bHFlip); /* horizontal flip */

WRAYCAM_API(HRESULT)  Wraycam_get_Negative(HWraycam h, int* bNegative);  /* negative film */
WRAYCAM_API(HRESULT)  Wraycam_put_Negative(HWraycam h, int bNegative);

WRAYCAM_API(HRESULT)  Wraycam_put_Speed(HWraycam h, unsigned short nSpeed);
WRAYCAM_API(HRESULT)  Wraycam_get_Speed(HWraycam h, unsigned short* pSpeed);
WRAYCAM_API(HRESULT)  Wraycam_get_MaxSpeed(HWraycam h); /* get the maximum speed, see "Frame Speed Level", the speed range = [0, max], closed interval */

WRAYCAM_API(HRESULT)  Wraycam_get_FanMaxSpeed(HWraycam h); /* get the maximum fan speed, the fan speed range = [0, max], closed interval */

WRAYCAM_API(HRESULT)  Wraycam_get_MaxBitDepth(HWraycam h); /* get the max bit depth of this camera, such as 8, 10, 12, 14, 16 */

/* power supply of lighting:
        0 -> 60HZ AC
        1 -> 50Hz AC
        2 -> DC
*/
WRAYCAM_API(HRESULT)  Wraycam_put_HZ(HWraycam h, int nHZ);
WRAYCAM_API(HRESULT)  Wraycam_get_HZ(HWraycam h, int* nHZ);

WRAYCAM_API(HRESULT)  Wraycam_put_Mode(HWraycam h, int bSkip); /* skip or bin */
WRAYCAM_API(HRESULT)  Wraycam_get_Mode(HWraycam h, int* bSkip); /* If the model don't support bin/skip mode, return E_NOTIMPL */

WRAYCAM_API(HRESULT)  Wraycam_put_AWBAuxRect(HWraycam h, const RECT* pAuxRect); /* auto white balance ROI */
WRAYCAM_API(HRESULT)  Wraycam_get_AWBAuxRect(HWraycam h, RECT* pAuxRect);
WRAYCAM_API(HRESULT)  Wraycam_put_AEAuxRect(HWraycam h, const RECT* pAuxRect);  /* auto exposure ROI */
WRAYCAM_API(HRESULT)  Wraycam_get_AEAuxRect(HWraycam h, RECT* pAuxRect);

WRAYCAM_API(HRESULT)  Wraycam_put_ABBAuxRect(HWraycam h, const RECT* pAuxRect); /* auto black balance ROI */
WRAYCAM_API(HRESULT)  Wraycam_get_ABBAuxRect(HWraycam h, RECT* pAuxRect);

/*
    S_FALSE:    color mode
    S_OK:       mono mode, such as EXCCD00300KMA and UHCCD01400KMA
*/
WRAYCAM_API(HRESULT)  Wraycam_get_MonoMode(HWraycam h);

WRAYCAM_API(HRESULT)  Wraycam_get_StillResolutionNumber(HWraycam h);
WRAYCAM_API(HRESULT)  Wraycam_get_StillResolution(HWraycam h, unsigned nResolutionIndex, int* pWidth, int* pHeight);

/* use minimum frame buffer.
    If DDR present, also limit the DDR frame buffer to only one frame.
    default: FALSE
*/
WRAYCAM_API(HRESULT)  Wraycam_put_RealTime(HWraycam h, int bEnable);
WRAYCAM_API(HRESULT)  Wraycam_get_RealTime(HWraycam h, int* bEnable);

/* discard the current internal frame cache.
    If DDR present, also discard the frames in the DDR.
*/
WRAYCAM_API(HRESULT)  Wraycam_Flush(HWraycam h);

/* get the temperature of the sensor, in 0.1 degrees Celsius (32 means 3.2 degrees Celsius, -35 means -3.5 degree Celsius)
    return E_NOTIMPL if not supported
*/
WRAYCAM_API(HRESULT)  Wraycam_get_Temperature(HWraycam h, short* pTemperature);

/* set the target temperature of the sensor or TEC, in 0.1 degrees Celsius (32 means 3.2 degrees Celsius, -35 means -3.5 degree Celsius)
    return E_NOTIMPL if not supported
*/
WRAYCAM_API(HRESULT)  Wraycam_put_Temperature(HWraycam h, short nTemperature);

/*
    get the revision
*/
WRAYCAM_API(HRESULT)  Wraycam_get_Revision(HWraycam h, unsigned short* pRevision);

/*
    get the serial number which is always 32 chars which is zero-terminated such as "TP110826145730ABCD1234FEDC56787"
*/
WRAYCAM_API(HRESULT)  Wraycam_get_SerialNumber(HWraycam h, char sn[32]);

/*
    get the camera firmware version, such as: 3.2.1.20140922
*/
WRAYCAM_API(HRESULT)  Wraycam_get_FwVersion(HWraycam h, char fwver[16]);

/*
    get the camera hardware version, such as: 3.12
*/
WRAYCAM_API(HRESULT)  Wraycam_get_HwVersion(HWraycam h, char hwver[16]);

/*
    get the production date, such as: 20150327, YYYYMMDD, (YYYY: year, MM: month, DD: day)
*/
WRAYCAM_API(HRESULT)  Wraycam_get_ProductionDate(HWraycam h, char pdate[10]);

/*
    get the FPGA version, such as: 1.13
*/
WRAYCAM_API(HRESULT)  Wraycam_get_FpgaVersion(HWraycam h, char fpgaver[16]);

/*
    get the sensor pixel size, such as: 2.4um
*/
WRAYCAM_API(HRESULT)  Wraycam_get_PixelSize(HWraycam h, unsigned nResolutionIndex, float* x, float* y);

WRAYCAM_API(HRESULT)  Wraycam_put_LevelRange(HWraycam h, unsigned short aLow[4], unsigned short aHigh[4]);
WRAYCAM_API(HRESULT)  Wraycam_get_LevelRange(HWraycam h, unsigned short aLow[4], unsigned short aHigh[4]);

/*
    The following functions must be called AFTER Wraycam_StartPushMode or Wraycam_StartPullModeWithWndMsg or Wraycam_StartPullModeWithCallback
*/
WRAYCAM_API(HRESULT)  Wraycam_LevelRangeAuto(HWraycam h);
WRAYCAM_API(HRESULT)  Wraycam_GetHistogram(HWraycam h, PIWRAYCAM_HISTOGRAM_CALLBACK fnHistogramProc, void* pHistogramCtx);

/* led state:
    iLed: Led index, (0, 1, 2, ...)
    iState: 1 -> Ever bright; 2 -> Flashing; other -> Off
    iPeriod: Flashing Period (>= 500ms)
*/
WRAYCAM_API(HRESULT)  Wraycam_put_LEDState(HWraycam h, unsigned short iLed, unsigned short iState, unsigned short iPeriod);

WRAYCAM_API(HRESULT)  Wraycam_write_EEPROM(HWraycam h, unsigned addr, const unsigned char* pBuffer, unsigned nBufferLen);
WRAYCAM_API(HRESULT)  Wraycam_read_EEPROM(HWraycam h, unsigned addr, unsigned char* pBuffer, unsigned nBufferLen);

WRAYCAM_API(HRESULT)  Wraycam_read_Pipe(HWraycam h, unsigned pipeNum, void* pBuffer, unsigned nBufferLen);
WRAYCAM_API(HRESULT)  Wraycam_write_Pipe(HWraycam h, unsigned pipeNum, const void* pBuffer, unsigned nBufferLen);
WRAYCAM_API(HRESULT)  Wraycam_feed_Pipe(HWraycam h, unsigned pipeNum);

#define WRAYCAM_TEC_TARGET_MIN           (-300)  /* -30.0 degrees Celsius */
#define WRAYCAM_TEC_TARGET_DEF           0       /* 0.0 degrees Celsius */
#define WRAYCAM_TEC_TARGET_MAX           300     /* 30.0 degrees Celsius */
                                         
#define WRAYCAM_OPTION_NOFRAME_TIMEOUT   0x01    /* 1 = enable; 0 = disable. default: disable */
#define WRAYCAM_OPTION_THREAD_PRIORITY   0x02    /* set the priority of the internal thread which grab data from the usb device. iValue: 0 = THREAD_PRIORITY_NORMAL; 1 = THREAD_PRIORITY_ABOVE_NORMAL; 2 = THREAD_PRIORITY_HIGHEST; default: 0; see: msdn SetThreadPriority */
#define WRAYCAM_OPTION_PROCESSMODE       0x03    /* 0 = better image quality, more cpu usage. this is the default value
                                                    1 = lower image quality, less cpu usage */
#define WRAYCAM_OPTION_RAW               0x04    /* raw data mode, read the sensor "raw" data. This can be set only BEFORE Wraycam_StartXXX(). 0 = rgb, 1 = raw, default value: 0 */
#define WRAYCAM_OPTION_HISTOGRAM         0x05    /* 0 = only one, 1 = continue mode */
#define WRAYCAM_OPTION_BITDEPTH          0x06    /* 0 = 8 bits mode, 1 = 16 bits mode, subset of WRAYCAM_OPTION_PIXEL_FORMAT */
#define WRAYCAM_OPTION_FAN               0x07    /* 0 = turn off the cooling fan, [1, max] = fan speed */
#define WRAYCAM_OPTION_TEC               0x08    /* 0 = turn off the thermoelectric cooler, 1 = turn on the thermoelectric cooler */
#define WRAYCAM_OPTION_LINEAR            0x09    /* 0 = turn off the builtin linear tone mapping, 1 = turn on the builtin linear tone mapping, default value: 1 */
#define WRAYCAM_OPTION_CURVE             0x0a    /* 0 = turn off the builtin curve tone mapping, 1 = turn on the builtin polynomial curve tone mapping, 2 = logarithmic curve tone mapping, default value: 2 */
#define WRAYCAM_OPTION_TRIGGER           0x0b    /* 0 = video mode, 1 = software or simulated trigger mode, 2 = external trigger mode, default value = 0 */
#define WRAYCAM_OPTION_RGB               0x0c    /* 0 => RGB24; 1 => enable RGB48 format when bitdepth > 8; 2 => RGB32; 3 => 8 Bits Gray (only for mono camera); 4 => 16 Bits Gray (only for mono camera when bitdepth > 8) */
#define WRAYCAM_OPTION_COLORMATIX        0x0d    /* enable or disable the builtin color matrix, default value: 1 */
#define WRAYCAM_OPTION_WBGAIN            0x0e    /* enable or disable the builtin white balance gain, default value: 1 */
#define WRAYCAM_OPTION_TECTARGET         0x0f    /* get or set the target temperature of the thermoelectric cooler, in 0.1 degree Celsius. For example, 125 means 12.5 degree Celsius, -35 means -3.5 degree Celsius */
#define WRAYCAM_OPTION_AUTOEXP_POLICY    0x10    /* auto exposure policy:
                                                     0: Exposure Only
                                                     1: Exposure Preferred
                                                     2: Gain Only
                                                     3: Gain Preferred
                                                     default value: 1
                                                 */
#define WRAYCAM_OPTION_FRAMERATE         0x11    /* limit the frame rate, range=[0, 63], the default value 0 means no limit */
#define WRAYCAM_OPTION_DEMOSAIC          0x12    /* demosaic method for both video and still image: BILINEAR = 0, VNG(Variable Number of Gradients interpolation) = 1, PPG(Patterned Pixel Grouping interpolation) = 2, AHD(Adaptive Homogeneity-Directed interpolation) = 3, see https://en.wikipedia.org/wiki/Demosaicing, default value: 0 */
#define WRAYCAM_OPTION_DEMOSAIC_VIDEO    0x13    /* demosaic method for video */
#define WRAYCAM_OPTION_DEMOSAIC_STILL    0x14    /* demosaic method for still image */
#define WRAYCAM_OPTION_BLACKLEVEL        0x15    /* black level */
#define WRAYCAM_OPTION_MULTITHREAD       0x16    /* multithread image processing */
#define WRAYCAM_OPTION_BINNING           0x17    /* binning, 0x01 (no binning), 0x02 (add, 2*2), 0x03 (add, 3*3), 0x04 (add, 4*4), 0x82 (average, 2*2), 0x83 (average, 3*3), 0x84 (average, 4*4) */
#define WRAYCAM_OPTION_ROTATE            0x18    /* rotate clockwise: 0, 90, 180, 270 */
#define WRAYCAM_OPTION_CG                0x19    /* Conversion Gain: 0 = LCG, 1 = HCG, 2 = HDR */
#define WRAYCAM_OPTION_PIXEL_FORMAT      0x1a    /* pixel format, WRAYCAM_PIXELFORMAT_xxxx */
#define WRAYCAM_OPTION_FFC               0x1b    /* flat field correction
                                                     set:
                                                          0: disable
                                                          1: enable
                                                         -1: reset
                                                         (0xff000000 | n): set the average number to n, [1~255]
                                                     get:
                                                          (val & 0xff): 0 -> disable, 1 -> enable, 2 -> inited
                                                          ((val & 0xff00) >> 8): sequence
                                                          ((val & 0xff0000) >> 8): average number
                                                 */
#define WRAYCAM_OPTION_DDR_DEPTH         0x1c    /* the number of the frames that DDR can cache
                                                         1: DDR cache only one frame
                                                         0: Auto:
                                                                 ->one for video mode when auto exposure is enabled
                                                                 ->full capacity for others
                                                        -1: DDR can cache frames to full capacity
                                                 */
#define WRAYCAM_OPTION_DFC               0x1d    /* dark field correction
                                                     set:
                                                         0: disable
                                                         1: enable
                                                        -1: reset
                                                         (0xff000000 | n): set the average number to n, [1~255]
                                                     get:
                                                         (val & 0xff): 0 -> disable, 1 -> enable, 2 -> inited
                                                         ((val & 0xff00) >> 8): sequence
                                                         ((val & 0xff0000) >> 8): average number
                                                 */
#define WRAYCAM_OPTION_SHARPENING        0x1e    /* Sharpening: (threshold << 24) | (radius << 16) | strength)
                                                     strength: [0, 500], default: 0 (disable)
                                                     radius: [1, 10]
                                                     threshold: [0, 255]
                                                 */
#define WRAYCAM_OPTION_FACTORY           0x1f    /* restore the factory settings */
#define WRAYCAM_OPTION_TEC_VOLTAGE       0x20    /* get the current TEC voltage in 0.1V, 59 mean 5.9V; readonly */
#define WRAYCAM_OPTION_TEC_VOLTAGE_MAX   0x21    /* get the TEC maximum voltage in 0.1V; readonly */
#define WRAYCAM_OPTION_DEVICE_RESET      0x22    /* reset usb device, simulate a replug */
#define WRAYCAM_OPTION_UPSIDE_DOWN       0x23    /* upsize down:
                                                     1: yes
                                                     0: no
                                                     default: 1 (win), 0 (linux/macos)
                                                 */
#define WRAYCAM_OPTION_AFPOSITION        0x24    /* auto focus sensor board positon */
#define WRAYCAM_OPTION_AFMODE            0x25    /* auto focus mode (0:manul focus; 1:auto focus; 2:onepush focus; 3:conjugate calibration) */
#define WRAYCAM_OPTION_AFZONE            0x26    /* auto focus zone */
#define WRAYCAM_OPTION_AFFEEDBACK        0x27    /* auto focus information feedback; 0:unknown; 1:focused; 2:focusing; 3:defocus; 4:up; 5:down */
#define WRAYCAM_OPTION_TESTPATTERN       0x28    /* test pattern:
                                                    0: TestPattern Off
                                                    3: monochrome diagonal stripes
                                                    5: monochrome vertical stripes
                                                    7: monochrome horizontal stripes
                                                    9: chromatic diagonal stripes
                                                */
#define WRAYCAM_OPTION_AUTOEXP_THRESHOLD 0x29   /* threshold of auto exposure, default value: 5, range = [5, 15] */
#define WRAYCAM_OPTION_BYTEORDER         0x2a   /* Byte order, BGR or RGB: 0->RGB, 1->BGR, default value: 1(Win), 0(macOS, Linux, Android) */

/* pixel format */
#define WRAYCAM_PIXELFORMAT_RAW8         0x00
#define WRAYCAM_PIXELFORMAT_RAW10        0x01
#define WRAYCAM_PIXELFORMAT_RAW12        0x02
#define WRAYCAM_PIXELFORMAT_RAW14        0x03
#define WRAYCAM_PIXELFORMAT_RAW16        0x04
#define WRAYCAM_PIXELFORMAT_YUV411       0x05
#define WRAYCAM_PIXELFORMAT_VUYY         0x06
#define WRAYCAM_PIXELFORMAT_YUV444       0x07
#define WRAYCAM_PIXELFORMAT_RGB888       0x08
#define WRAYCAM_PIXELFORMAT_GMCY8        0x09   /* map to RGGB 8 bits */
#define WRAYCAM_PIXELFORMAT_GMCY12       0x0a   /* map to RGGB 12 bits */
#define WRAYCAM_PIXELFORMAT_UYVY         0x0b

WRAYCAM_API(HRESULT)  Wraycam_put_Option(HWraycam h, unsigned iOption, int iValue);
WRAYCAM_API(HRESULT)  Wraycam_get_Option(HWraycam h, unsigned iOption, int* piValue);

WRAYCAM_API(HRESULT)  Wraycam_put_Roi(HWraycam h, unsigned xOffset, unsigned yOffset, unsigned xWidth, unsigned yHeight);
WRAYCAM_API(HRESULT)  Wraycam_get_Roi(HWraycam h, unsigned* pxOffset, unsigned* pyOffset, unsigned* pxWidth, unsigned* pyHeight);

/*  simulate replug:
    return > 0, the number of device has been replug
    return = 0, no device found
    return E_ACCESSDENIED if without UAC Administrator privileges
    for each device found, it will take about 3 seconds
*/
#ifdef _WIN32
WRAYCAM_API(HRESULT) Wraycam_Replug(const wchar_t* id);
#else
WRAYCAM_API(HRESULT) Wraycam_Replug(const char* id);
#endif

#ifndef __WRAYCAMAFPARAM_DEFINED__
#define __WRAYCAMAFPARAM_DEFINED__
typedef struct {
    int imax;    /* maximum auto focus sensor board positon */
    int imin;    /* minimum auto focus sensor board positon */
    int idef;    /* conjugate calibration positon */
    int imaxabs; /* maximum absolute auto focus sensor board positon, micrometer */
    int iminabs; /* maximum absolute auto focus sensor board positon, micrometer */
    int zoneh;   /* zone horizontal */
    int zonev;   /* zone vertical */
}WraycamAfParam;
#endif

WRAYCAM_API(HRESULT)  Wraycam_get_AfParam(HWraycam h, WraycamAfParam* pAfParam);

#define WRAYCAM_IOCONTROLTYPE_GET_SUPPORTEDMODE           0x01 /* 0x01->Input, 0x02->Output, (0x01 | 0x02)->support both Input and Output */
#define WRAYCAM_IOCONTROLTYPE_GET_GPIODIR                 0x03 /* 0x00->Input, 0x01->Output */
#define WRAYCAM_IOCONTROLTYPE_SET_GPIODIR                 0x04
#define WRAYCAM_IOCONTROLTYPE_GET_FORMAT                  0x05 /*
                                                                   0x00-> not connected
                                                                   0x01-> Tri-state: Tri-state mode (Not driven)
                                                                   0x02-> TTL: TTL level signals
                                                                   0x03-> LVDS: LVDS level signals
                                                                   0x04-> RS422: RS422 level signals
                                                                   0x05-> Opto-coupled
                                                               */
#define WRAYCAM_IOCONTROLTYPE_SET_FORMAT                  0x06
#define WRAYCAM_IOCONTROLTYPE_GET_OUTPUTINVERTER          0x07 /* boolean, only support output signal */
#define WRAYCAM_IOCONTROLTYPE_SET_OUTPUTINVERTER          0x08
#define WRAYCAM_IOCONTROLTYPE_GET_INPUTACTIVATION         0x09 /* 0x00->Positive, 0x01->Negative */
#define WRAYCAM_IOCONTROLTYPE_SET_INPUTACTIVATION         0x0a
#define WRAYCAM_IOCONTROLTYPE_GET_DEBOUNCERTIME           0x0b /* debouncer time in microseconds, [0, 20000] */
#define WRAYCAM_IOCONTROLTYPE_SET_DEBOUNCERTIME           0x0c
#define WRAYCAM_IOCONTROLTYPE_GET_TRIGGERSOURCE           0x0d /*
                                                                  0x00-> Opto-isolated input
                                                                  0x01-> GPIO0
                                                                  0x02-> GPIO1
                                                                  0x03-> Counter
                                                                  0x04-> PWM
                                                                  0x05-> Software
                                                               */
#define WRAYCAM_IOCONTROLTYPE_SET_TRIGGERSOURCE           0x0e
#define WRAYCAM_IOCONTROLTYPE_GET_TRIGGERDELAY            0x0f /* Trigger delay time in microseconds, [0, 5000000] */
#define WRAYCAM_IOCONTROLTYPE_SET_TRIGGERDELAY            0x10
#define WRAYCAM_IOCONTROLTYPE_GET_BURSTCOUNTER            0x11 /* Burst Counter: 1, 2, 3 ... 1023 */
#define WRAYCAM_IOCONTROLTYPE_SET_BURSTCOUNTER            0x12
#define WRAYCAM_IOCONTROLTYPE_GET_COUNTERSOURCE           0x13 /* 0x00-> Opto-isolated input, 0x01-> GPIO0, 0x02-> GPIO1 */
#define WRAYCAM_IOCONTROLTYPE_SET_COUNTERSOURCE           0x14
#define WRAYCAM_IOCONTROLTYPE_GET_COUNTERVALUE            0x15 /* Counter Value: 1, 2, 3 ... 1023 */
#define WRAYCAM_IOCONTROLTYPE_SET_COUNTERVALUE            0x16
#define WRAYCAM_IOCONTROLTYPE_SET_RESETCOUNTER            0x18
#define WRAYCAM_IOCONTROLTYPE_GET_PWM_FREQ                0x19
#define WRAYCAM_IOCONTROLTYPE_SET_PWM_FREQ                0x1a
#define WRAYCAM_IOCONTROLTYPE_GET_PWM_DUTYRATIO           0x1b
#define WRAYCAM_IOCONTROLTYPE_SET_PWM_DUTYRATIO           0x1c
#define WRAYCAM_IOCONTROLTYPE_GET_PWMSOURCE               0x1d /* 0x00-> Opto-isolated input, 0x01-> GPIO0, 0x02-> GPIO1 */
#define WRAYCAM_IOCONTROLTYPE_SET_PWMSOURCE               0x1e
#define WRAYCAM_IOCONTROLTYPE_GET_OUTPUTMODE              0x1f /*
                                                                  0x00-> Frame Trigger Wait
                                                                  0x01-> Exposure Active
                                                                  0x02-> Strobe
                                                                  0x03-> User output
                                                               */
#define WRAYCAM_IOCONTROLTYPE_SET_OUTPUTMODE              0x20
#define WRAYCAM_IOCONTROLTYPE_GET_STROBEDELAYMODE         0x21 /* boolean, 0-> pre-delay, 1-> delay; compared to exposure active signal */
#define WRAYCAM_IOCONTROLTYPE_SET_STROBEDELAYMODE         0x22
#define WRAYCAM_IOCONTROLTYPE_GET_STROBEDELAYTIME         0x23 /* Strobe delay or pre-delay time in microseconds, [0, 5000000] */
#define WRAYCAM_IOCONTROLTYPE_SET_STROBEDELAYTIME         0x24
#define WRAYCAM_IOCONTROLTYPE_GET_STROBEDURATION          0x25 /* Strobe duration time in microseconds, [0, 5000000] */
#define WRAYCAM_IOCONTROLTYPE_SET_STROBEDURATION          0x26
#define WRAYCAM_IOCONTROLTYPE_GET_USERVALUE               0x27 /* 
                                                                  bit0-> Opto-isolated output
                                                                  bit1-> GPIO0 output
                                                                  bit2-> GPIO1 output
                                                               */
#define WRAYCAM_IOCONTROLTYPE_SET_USERVALUE               0x28

WRAYCAM_API(HRESULT)  Wraycam_IoControl(HWraycam h, unsigned index, unsigned nType, int outVal, int* inVal);

WRAYCAM_API(HRESULT)  Wraycam_write_UART(HWraycam h, const unsigned char* pData, unsigned nDataLen);
WRAYCAM_API(HRESULT)  Wraycam_read_UART(HWraycam h, unsigned char* pBuffer, unsigned nBufferLen);

WRAYCAM_API(HRESULT)  Wraycam_put_Linear(HWraycam h, const unsigned char* v8, const unsigned short* v16);
WRAYCAM_API(HRESULT)  Wraycam_put_Curve(HWraycam h, const unsigned char* v8, const unsigned short* v16);
WRAYCAM_API(HRESULT)  Wraycam_put_ColorMatrix(HWraycam h, const double v[9]);
WRAYCAM_API(HRESULT)  Wraycam_put_InitWBGain(HWraycam h, const unsigned short v[3]);

/*
    get the frame rate: framerate (fps) = Frame * 1000.0 / nTime
*/
WRAYCAM_API(HRESULT)  Wraycam_get_FrameRate(HWraycam h, unsigned* nFrame, unsigned* nTime, unsigned* nTotalFrame);

/* astronomy: for ST4 guide, please see: ASCOM Platform Help ICameraV2.
    nDirect: 0 = North, 1 = South, 2 = East, 3 = West, 4 = Stop
    nDuration: in milliseconds
*/
WRAYCAM_API(HRESULT)  Wraycam_ST4PlusGuide(HWraycam h, unsigned nDirect, unsigned nDuration);

/* S_OK: ST4 pulse guiding
   S_FALSE: ST4 not pulse guiding
*/
WRAYCAM_API(HRESULT)  Wraycam_ST4PlusGuideState(HWraycam h);

/*
    calculate the clarity factor:
    pImageData: pointer to the image data
    bits: 8(Grey), 24 (RGB24), 32(RGB32)
    nImgWidth, nImgHeight: the image width and height
*/
WRAYCAM_API(double)   Wraycam_calc_ClarityFactor(const void* pImageData, int bits, unsigned nImgWidth, unsigned nImgHeight);

/*
    nBitCount: output bitmap bit count
    when nBitDepth == 8:
        nBitCount must be 24 or 32
    when nBitDepth > 8
        nBitCount:  24 -> RGB24
                    32 -> RGB32
                    48 -> RGB48
                    64 -> RGB64
*/
WRAYCAM_API(void)     Wraycam_deBayerV2(unsigned nBayer, int nW, int nH, const void* input, void* output, unsigned char nBitDepth, unsigned char nBitCount);

/*
    obsolete, please use Wraycam_deBayerV2
*/
WRAYCAM_DEPRECATED
WRAYCAM_API(void)     Wraycam_deBayer(unsigned nBayer, int nW, int nH, const void* input, void* output, unsigned char nBitDepth);

typedef void (__stdcall* PWRAYCAM_DEMOSAIC_CALLBACK)(unsigned nBayer, int nW, int nH, const void* input, void* output, unsigned char nBitDepth, void* pCallbackCtx);
WRAYCAM_API(HRESULT)  Wraycam_put_Demosaic(HWraycam h, PWRAYCAM_DEMOSAIC_CALLBACK pCallback, void* pCallbackCtx);

/*
    obsolete, please use WraycamModelV2
*/
typedef struct {
#ifdef _WIN32
    const wchar_t*      name;       /* model name, in Windows, we use unicode */
#else
    const char*         name;       /* model name */
#endif
    unsigned            flag;       /* WRAYCAM_FLAG_xxx */
    unsigned            maxspeed;   /* number of speed level, same as Wraycam_get_MaxSpeed(), the speed range = [0, maxspeed], closed interval */
    unsigned            preview;    /* number of preview resolution, same as Wraycam_get_ResolutionNumber() */
    unsigned            still;      /* number of still resolution, same as Wraycam_get_StillResolutionNumber() */
    WraycamResolution   res[WRAYCAM_MAX];
}WraycamModel; /* camera model */

/*
    obsolete, please use WraycamDeviceV2
*/
typedef struct {
#ifdef _WIN32
    wchar_t             displayname[64];    /* display name */
    wchar_t             id[64];             /* unique and opaque id of a connected camera, for Wraycam_Open */
#else
    char                displayname[64];    /* display name */
    char                id[64];             /* unique and opaque id of a connected camera, for Wraycam_Open */
#endif
    const WraycamModel* model;
}WraycamDevice; /* camera instance for enumerating */

/*
    obsolete, please use Wraycam_EnumV2
*/
WRAYCAM_DEPRECATED
WRAYCAM_API(unsigned) Wraycam_Enum(WraycamDevice pti[WRAYCAM_MAX]);

typedef PWRAYCAM_DATA_CALLBACK_V3 PWRAYCAM_DATA_CALLBACK_V2;
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_StartPushModeV2(HWraycam h, PWRAYCAM_DATA_CALLBACK_V2 pDataCallback, void* pCallbackCtx);

typedef void (__stdcall* PWRAYCAM_DATA_CALLBACK)(const void* pData, const BITMAPINFOHEADER* pHeader, int bSnap, void* pCallbackCtx);
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_StartPushMode(HWraycam h, PWRAYCAM_DATA_CALLBACK pDataCallback, void* pCallbackCtx);

WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_put_ExpoCallback(HWraycam h, PIWRAYCAM_EXPOSURE_CALLBACK fnExpoProc, void* pExpoCtx);
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_put_ChromeCallback(HWraycam h, PIWRAYCAM_CHROME_CALLBACK fnChromeProc, void* pChromeCtx);

#ifndef _WIN32

/*
This function is only available on macOS and Linux, it's unnecessary on Windows.
  (1) To process the device plug in / pull out in Windows, please refer to the MSDN
       (a) Device Management, http://msdn.microsoft.com/en-us/library/windows/desktop/aa363224(v=vs.85).aspx
       (b) Detecting Media Insertion or Removal, http://msdn.microsoft.com/en-us/library/windows/desktop/aa363215(v=vs.85).aspx
  (2) To process the device plug in / pull out in Linux / macOS, please call this function to register the callback function.
      When the device is inserted or pulled out, you will be notified by the callback funcion, and then call Wraycam_EnumV2(...) again to enum the cameras.
Recommendation: for better rubustness, when notify of device insertion arrives, don't open handle of this device immediately, but open it after delaying a short time (e.g., 200 milliseconds).
*/
typedef void (*PWRAYCAM_HOTPLUG)(void* pCallbackCtx);
WRAYCAM_API(void)   Wraycam_HotPlug(PWRAYCAM_HOTPLUG pHotPlugCallback, void* pCallbackCtx);

#else

/* Wraycam_Start is obsolete, it's a synonyms for Wraycam_StartPushMode. */
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_Start(HWraycam h, PWRAYCAM_DATA_CALLBACK pDataCallback, void* pCallbackCtx);

/* Wraycam_put_TempTintInit is obsolete, it's a synonyms for Wraycam_AwbOnePush. */
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_put_TempTintInit(HWraycam h, PIWRAYCAM_TEMPTINT_CALLBACK fnTTProc, void* pTTCtx);

/*
    obsolete, please use Wraycam_put_Option or Wraycam_get_Option to set or get the process mode: WRAYCAM_PROCESSMODE_FULL or WRAYCAM_PROCESSMODE_FAST.
    default is WRAYCAM_PROCESSMODE_FULL.
*/
#ifndef __WRAYCAM_PROCESSMODE_DEFINED__
#define __WRAYCAM_PROCESSMODE_DEFINED__
#define WRAYCAM_PROCESSMODE_FULL        0x00    /* better image quality, more cpu usage. this is the default value */
#define WRAYCAM_PROCESSMODE_FAST        0x01    /* lower image quality, less cpu usage */
#endif

WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_put_ProcessMode(HWraycam h, unsigned nProcessMode);
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_get_ProcessMode(HWraycam h, unsigned* pnProcessMode);

#endif

/* obsolete, please use Wraycam_put_Roi and Wraycam_get_Roi */
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_put_RoiMode(HWraycam h, int bRoiMode, int xOffset, int yOffset);
WRAYCAM_DEPRECATED
WRAYCAM_API(HRESULT)  Wraycam_get_RoiMode(HWraycam h, int* pbRoiMode, int* pxOffset, int* pyOffset);

/* obsolete:
     ------------------------------------------------------------|
     | Parameter         |   Range       |   Default             |
     |-----------------------------------------------------------|
     | VidgetAmount      |   -100~100    |   0                   |
     | VignetMidPoint    |   0~100       |   50                  |
     -------------------------------------------------------------
*/
WRAYCAM_API(HRESULT)  Wraycam_put_VignetEnable(HWraycam h, int bEnable);
WRAYCAM_API(HRESULT)  Wraycam_get_VignetEnable(HWraycam h, int* bEnable);
WRAYCAM_API(HRESULT)  Wraycam_put_VignetAmountInt(HWraycam h, int nAmount);
WRAYCAM_API(HRESULT)  Wraycam_get_VignetAmountInt(HWraycam h, int* nAmount);
WRAYCAM_API(HRESULT)  Wraycam_put_VignetMidPointInt(HWraycam h, int nMidPoint);
WRAYCAM_API(HRESULT)  Wraycam_get_VignetMidPointInt(HWraycam h, int* nMidPoint);

/* obsolete flags */
#define WRAYCAM_FLAG_BITDEPTH10    WRAYCAM_FLAG_RAW10  /* pixel format, RAW 10bits */
#define WRAYCAM_FLAG_BITDEPTH12    WRAYCAM_FLAG_RAW12  /* pixel format, RAW 12bits */
#define WRAYCAM_FLAG_BITDEPTH14    WRAYCAM_FLAG_RAW14  /* pixel format, RAW 14bits */
#define WRAYCAM_FLAG_BITDEPTH16    WRAYCAM_FLAG_RAW16  /* pixel format, RAW 16bits */

#ifdef _WIN32
#pragma pack(pop)
#endif

#ifdef __cplusplus
}
#endif

#endif