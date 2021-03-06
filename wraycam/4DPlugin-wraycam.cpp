/* --------------------------------------------------------------------------------
 #
 #  4DPlugin-wraycam.cpp
 #	source generated by 4D Plugin Wizard
 #	Project : wraycam
 #	author : miyako
 #	2019/12/05
 #  
 # --------------------------------------------------------------------------------*/

#include "4DPlugin-wraycam.h"
#include "wraycam.h"

#if VERSIONWIN
typedef std::wstring wraycam_string_t;
#else
typedef std:: string wraycam_string_t;
#endif

std::map<wraycam_string_t, HWraycam> _handles;

std::mutex globalMutex;

#pragma mark -

#define CALLBACK_SLEEP_TIME 1

#pragma mark -

void listenerLoop(void);
void listenerLoopStart(void);
void listenerLoopFinish(void);
void listenerLoopExecute(void);
void listenerLoopExecuteMethod(void);

void OnHotplug(void *pCallbackCtx) {
    
}

void OnStartup()
{
#if VERSIONMAC
    void *pCallbackCtx = NULL;
        OnHotplug(pCallbackCtx);
#else

#endif
    listenerLoopStart();
}

void OnExit()
{
#if VERSIONMAC

#else

#endif
    listenerLoopFinish();
}

#pragma mark -

std::mutex globalMutex1;/* for METHOD_PROCESS_ID */
std::mutex globalMutex2;/* for LISTENER_METHOD */
std::mutex globalMutex3;/* PROCESS_SHOULD_TERMINATE */
std::mutex globalMutex4;/* PROCESS_SHOULD_RESUME */

typedef PA_long32 process_number_t;
typedef PA_long32 process_stack_size_t;
typedef PA_long32 method_id_t;
typedef PA_Unichar* process_name_t;
typedef std::basic_string<PA_Unichar> wraycam_basic_string;

namespace wraycam
{
    //constants
    process_stack_size_t STACK_SIZE = 0;
    const process_name_t PROCESS_NAME = (PA_Unichar *)"$\0w\0r\0a\0y\0c\0a\0m\0\0\0";
    
    //context management
//    std::vector<wraycam_basic_string>messages;
    std::vector<unsigned>events;
    wraycam_basic_string LISTENER_CONTEXT;
    
    //callback management
    wraycam_basic_string LISTENER_METHOD;
    process_number_t METHOD_PROCESS_ID = 0;
    bool PROCESS_SHOULD_TERMINATE = false;
    bool PROCESS_SHOULD_RESUME = false;
}

#pragma mark -

void listenerLoop() {
    
    if(1)
    {
         std::lock_guard<std::mutex> lock(globalMutex3);

        wraycam::PROCESS_SHOULD_TERMINATE = false;
    }
    
    /* Current process returns 0 for PA_NewProcess */
    PA_long32 currentProcessNumber = PA_GetCurrentProcessNumber();
    
    while(!PA_IsProcessDying())
    {
        PA_YieldAbsolute();
        
        bool PROCESS_SHOULD_RESUME;
        bool PROCESS_SHOULD_TERMINATE;
        
        if(1)
        {
            PROCESS_SHOULD_RESUME = wraycam::PROCESS_SHOULD_RESUME;
            PROCESS_SHOULD_TERMINATE = wraycam::PROCESS_SHOULD_TERMINATE;
        }
        
        if(PROCESS_SHOULD_RESUME)
        {
            size_t cnt;
            
            if(1)
            {
                std::lock_guard<std::mutex> lock(globalMutex);
                
//                cnt = wraycam::messages.size();
                cnt = wraycam::events.size();
            }
            
            while(cnt)
            {
                PA_YieldAbsolute();

                listenerLoopExecuteMethod();

                if (PROCESS_SHOULD_TERMINATE)
                    break;
                
                if(1)
                {
                    std::lock_guard<std::mutex> lock(globalMutex);
                    
//                    cnt = wraycam::messages.size();
                    cnt = wraycam::events.size();
                    PROCESS_SHOULD_TERMINATE = wraycam::PROCESS_SHOULD_TERMINATE;
                }
            }
            
            if(1)
            {
                std::lock_guard<std::mutex> lock(globalMutex4);
                
                wraycam::PROCESS_SHOULD_RESUME = false;
            }

        }else
        {
            /* DELAY PROCESS does not work for PA_NewProcess */
            PA_PutProcessToSleep(currentProcessNumber, CALLBACK_SLEEP_TIME);
        }
        
        if(1)
        {
            PROCESS_SHOULD_TERMINATE = wraycam::PROCESS_SHOULD_TERMINATE;
        }
        
        if (PROCESS_SHOULD_TERMINATE)
            break;
    }
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex);
        
//        wraycam::messages.clear();
        wraycam::events.clear();
    }
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex2);
        
        wraycam::LISTENER_METHOD = wraycam_basic_string((PA_Unichar *)"\0\0", 0);
    }
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex1);
        
        wraycam::METHOD_PROCESS_ID = 0;
    }
        
    PA_KillProcess();
}

void listenerLoopStart() {
    
    if(!wraycam::METHOD_PROCESS_ID)
    {
        std::lock_guard<std::mutex> lock(globalMutex1);
        
        wraycam::METHOD_PROCESS_ID = PA_NewProcess((void *)listenerLoop,
                                                       wraycam::STACK_SIZE,
                                                       wraycam::PROCESS_NAME);
    }
}

void listenerLoopFinish() {
    
    if(wraycam::METHOD_PROCESS_ID)
    {
        if(1)
        {
            std::lock_guard<std::mutex> lock(globalMutex3);
            
            wraycam::PROCESS_SHOULD_TERMINATE = true;
        }

        PA_YieldAbsolute();
        
        if(1)
        {
            std::lock_guard<std::mutex> lock(globalMutex4);
            
            wraycam::PROCESS_SHOULD_RESUME = true;
        }
    }
}

void listenerLoopExecute() {
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex3);
        
        wraycam::PROCESS_SHOULD_TERMINATE = false;
    }
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex4);
        
        wraycam::PROCESS_SHOULD_RESUME = true;
    }
    
}

void listenerLoopExecuteMethod() {
    
//    wraycam_basic_string message;
    unsigned event;

    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex);

//        std::vector<CUTF16String>::iterator p;
        std::vector<unsigned>::iterator p;
        
//        p = wraycam::messages.begin();
        p = wraycam::events.begin();
        
//        message = *p;
        event = *p;
        
//        wraycam::messages.erase(p);
        wraycam::events.erase(p);
    }
    
    method_id_t methodId = PA_GetMethodID((PA_Unichar *)wraycam::LISTENER_METHOD.c_str());
    
    if(methodId)
    {
        PA_Variable    params[2];
//        params[0] = PA_CreateVariable(eVK_Unistring);
        params[0] = PA_CreateVariable(eVK_Longint);
        params[1] = PA_CreateVariable(eVK_Unistring);
        
//        PA_Unistring command = PA_CreateUnistring((PA_Unichar *)message.c_str());
        PA_Unistring context = PA_CreateUnistring((PA_Unichar *)wraycam::LISTENER_CONTEXT.c_str());
    
//        PA_SetStringVariable(&params[0], &command);
        PA_SetLongintVariable(&params[0], event);
        PA_SetStringVariable(&params[1], &context);
        
        PA_ExecuteMethodByID(methodId, params, 2);
        
        PA_ClearVariable(&params[0]);
        PA_ClearVariable(&params[1]);
        
    }else
    {
        PA_Variable    params[3];
//        params[1] = PA_CreateVariable(eVK_Unistring);
        params[1] = PA_CreateVariable(eVK_Longint);
        params[2] = PA_CreateVariable(eVK_Unistring);
        
//        PA_Unistring command = PA_CreateUnistring((PA_Unichar *)message.c_str());
        PA_Unistring context = PA_CreateUnistring((PA_Unichar *)wraycam::LISTENER_CONTEXT.c_str());
        
//        PA_SetStringVariable(&params[1], &command);
        PA_SetLongintVariable(&params[1], event);
        PA_SetStringVariable(&params[2], &context);
        
        params[0] = PA_CreateVariable(eVK_Unistring);
        PA_Unistring method = PA_CreateUnistring((PA_Unichar *)wraycam::LISTENER_METHOD.c_str());
        PA_SetStringVariable(&params[0], &method);
        
        /* execute method */
        PA_ExecuteCommandByID(1007, params, 3);

        PA_ClearVariable(&params[0]);
        PA_ClearVariable(&params[1]);
        PA_ClearVariable(&params[2]);
    }
}

#pragma mark -

void PluginMain(PA_long32 selector, PA_PluginParameters params) {
    
	try
	{
        switch(selector)
        {
                case kInitPlugin :
                case kServerInitPlugin :
                    OnStartup();
                    break;
                    
                case kDeinitPlugin:
                case kServerDeinitPlugin:
                    OnExit();
                    break;
                
			// --- wraycam
            
            case 1 :
                wraycam_Get_version(params);
                break;
            case 2 :
                wraycam_Get_devices(params);
                break;
            case 3 :
                wraycam_Open(params);
                break;
            case 4 :
                wraycam_Close(params);
                break;
            case 5 :
                wraycam_Get_info(params);
                break;
            case 6 :
                wraycam_Get_property(params);
                break;
            case 7 :
                wraycam_Set_property(params);
                break;
            case 8 :
                wraycam_Get_option(params);
                break;
            case 9 :
                wraycam_Set_option(params);
                break;
            case 10 :
                wraycam_Start(params);
                break;
            case 11 :
                wraycam_Stop(params);
                break;
            case 12 :
                wraycam_Pause(params);
                break;
            case 13 :
                wraycam_Snap(params);
                break;
            case 14 :
                wraycam_Trigger(params);
                break;
            case 15 :
                wraycam_Flush(params);
                break;
            case 16 :
                wraycam_Get_image(params);
                break;
            case 17 :
                wraycam_Correct_flat_field(params);
                break;
            case 18 :
                wraycam_Correct_dark_field(params);
                break;
            case 19 :
                wraycam_Auto_level_range(params);
                break;
            case 20 :
                wraycam_Set_LED_state(params);
                break;

        }

	}
	catch(...)
	{

	}
}

#pragma mark -

wraycam_basic_string getString(wraycam_string_t &str) {

    wraycam_basic_string ustr;
    
#if VERSIONWIN
    int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)str.c_str(), str.length(), NULL, 0);
    
    if(len){
        std::vector<uint8_t> buf((len + 1) * sizeof(PA_Unichar));
        if(MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)str.c_str(), str.length(), (LPWSTR)&buf[0], len)){
            ustr = CUTF16String((const PA_Unichar *)&buf[0]);
        }
    }else{
            ustr = CUTF16String((const PA_Unichar *)L"");
    }
    
#else
    CFStringRef s = CFStringCreateWithBytes(kCFAllocatorDefault,
                                            (const UInt8 *)str.c_str(), str.length(),
                                            kCFStringEncodingUTF8, true);
    if(s){
        CFIndex len = CFStringGetLength(s);
        std::vector<uint8_t> buf((len+1) * sizeof(PA_Unichar));
        CFStringGetCharacters(s, CFRangeMake(0, len), (UniChar *)&buf[0]);
        ustr = CUTF16String((const PA_Unichar *)&buf[0]);
        CFRelease(s);
    }
#endif
    
    return ustr;
}

void wraycam_Get_version(PA_PluginParameters params) {

    wraycam_string_t _version = Wraycam_Version();
    wraycam_basic_string version = getString(_version);
    
    PA_ReturnString(params, (PA_Unichar *)version.c_str());
}

void wraycam_Get_devices(PA_PluginParameters params) {

    PA_CollectionRef c = PA_CreateCollection();
    
    WraycamDeviceV2 devices[WRAYCAM_MAX];
    
    unsigned cnt = Wraycam_EnumV2(devices);
    for (unsigned i = 0; i < cnt; ++i) {
        
        WraycamDeviceV2 device = devices[i];
        
        PA_ObjectRef o = PA_CreateObject();
        
        const WraycamModelV2 *model = device.model;
        
#if VERSIONWIN
        wchar_t *displayname = device.displayname;
        wchar_t *device_id = device.id;
        const wchar_t *name = model->name;
        ob_set_a(o, L"displayname", displayname);
        ob_set_a(o, L"name", name);
        ob_set_a(o, L"id", device_id);
#else
        char *displayname = device.displayname;
        const char *name = model->name;
        char *device_id = device.id;
        ob_set_s(o, L"displayname", displayname);
        ob_set_s(o, L"name", name);
        ob_set_s(o, L"id", device_id);
#endif
        
        unsigned long long flag = model->flag;
        unsigned maxspeed = model->maxspeed;
        unsigned preview = model->preview;
        unsigned still = model->still;
        unsigned maxfanspeed = model->maxfanspeed;
        unsigned ioctrol = model->ioctrol;
        float xpixsz = model->xpixsz;
        float ypixsz = model->ypixsz;
        unsigned width = model->res->width;
        unsigned height = model->res->height;
        
        ob_set_n(o, L"flag", flag);
        ob_set_n(o, L"maxspeed", maxspeed);
        ob_set_n(o, L"preview", preview);
        ob_set_n(o, L"still", still);
        ob_set_n(o, L"maxfanspeed", maxfanspeed);
        ob_set_n(o, L"ioctrol", ioctrol);
        ob_set_n(o, L"xpixsz", xpixsz);
        ob_set_n(o, L"ypixsz", ypixsz);
        
        PA_ObjectRef res = PA_CreateObject();
        
        ob_set_n(res, L"width", width);
        ob_set_n(res, L"height", height);

        ob_set_o(o, L"res", res);
    }
    
    PA_ReturnCollection(params, c);
}

#if VERSIONWIN
wraycam_string_t getdeviceid(PA_Unistring *u) {
    return wraycam_string_t((const wchar_t *)u->fString, u->fLength);
}
#else
wraycam_string_t getdeviceid(PA_Unistring *u) {
    
    std::string deviceid;
    CFStringRef str = CFStringCreateWithCharacters(kCFAllocatorDefault, (const UniChar *)u->fString, u->fLength);
    if(str) {
        size_t size = CFStringGetMaximumSizeForEncoding(CFStringGetLength(str), kCFStringEncodingUTF8) + sizeof(uint8_t);
        std::vector<uint8_t> buf(size);
        CFIndex len = 0;
        CFStringGetBytes(str, CFRangeMake(0, CFStringGetLength(str)), kCFStringEncodingUTF8, 0, true, (UInt8 *)&buf[0], size, &len);

        deviceid = wraycam_string_t((const char *)&buf[0], len);
        CFRelease(str);
    }
    return deviceid;
}
#endif

void _set_handle(wraycam_string_t &device, HWraycam h){

    std::lock_guard<std::mutex> lock(globalMutex);
    
    _handles.insert(std::map<wraycam_string_t, HWraycam>::value_type(device, h));
}

HWraycam _get_handle(wraycam_string_t &device){
    
    std::lock_guard<std::mutex> lock(globalMutex);
    
    std::map<wraycam_string_t, HWraycam>::iterator pos = _handles.find(device);
    
    if(pos != _handles.end()) {
        return pos->second;
    }
    
    return 0;
}

void _delete_handle(wraycam_string_t &device){
    
    std::lock_guard<std::mutex> lock(globalMutex);

    std::map<wraycam_string_t, HWraycam>::iterator pos = _handles.find(device);
    
    if(pos != _handles.end()) {

        _handles.erase(pos);
    }
    
}

void wraycam_Close(PA_PluginParameters params) {
    
    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    if(h) {
        Wraycam_Close(h);
    }
    _delete_handle(deviceid);
}

void ob_set_s(PA_ObjectRef obj, const wchar_t *_key, PA_Unistring *u) {
    
    if(u) {
        PA_Variable v = PA_CreateVariable(eVK_Unistring);
        
        CUTF16String ukey;
        
        json_wconv(_key, &ukey);

        PA_Unistring key = PA_CreateUnistring((PA_Unichar *)ukey.c_str());
        PA_Unistring value = PA_CreateUnistring((PA_Unichar *)u->fString);
        
        PA_SetStringVariable(&v, &value);
        PA_SetObjectProperty(obj, &key, v);
        
        PA_DisposeUnistring(&key);
        
        PA_ClearVariable(&v);
    }
 
}

void wraycam_Open(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    PA_Unistring *m = PA_GetStringParameter(params, 2);
    PA_Unistring *c = PA_GetStringParameter(params, 3);
    wraycam_string_t deviceid = getdeviceid(u);
    
    HWraycam h = NULL;
    
    if(deviceid.length()) {
       h = Wraycam_Open(deviceid.c_str());
    }else{
        
        WraycamDeviceV2 devices[WRAYCAM_MAX];
        
        unsigned cnt = Wraycam_EnumV2(devices);
        if(cnt) {
            WraycamDeviceV2 device = devices[0];
            deviceid = wraycam_string_t(device.id);
            h = Wraycam_OpenByIndex(0);
        }
    }
    
    if(h) {
        _set_handle(deviceid, h);
    }
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex2);

        wraycam::LISTENER_METHOD = wraycam_basic_string((const PA_Unichar *)m->fString, m->fLength);
    }
    
    if(1)
    {
        std::lock_guard<std::mutex> lock(globalMutex);

        wraycam::LISTENER_CONTEXT = wraycam_basic_string((const PA_Unichar *)c->fString, c->fLength);
    }
    
    PA_ObjectRef o = PA_CreateObject();
    
#if VERSIONWIN
        ob_set_a(o, L"id", deviceid.c_str());
#else
        ob_set_s(o, L"id", deviceid.c_str());
#endif

    ob_set_s(o, L"params", c);
    ob_set_s(o, L"method", m);
    
    ob_set_b(o, L"success", (bool)h);

    PA_ReturnObject(params, o);
}

void wraycam_Set_option(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    if(h) {

    }
    
}

void wraycam_Get_option(PA_PluginParameters params) {
    
    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    if(h) {

    }
}

void wraycam_Get_info(PA_PluginParameters params) {

}

void wraycam_Get_property(PA_PluginParameters params) {

}

void wraycam_Set_property(PA_PluginParameters params) {

}

void wraycam_callback_method(unsigned nEvent, void* pCallbackCtx) {

     if(1)
     {
         std::lock_guard<std::mutex> lock(globalMutex);
         
//         wraycam_basic_string message;
         
//         wraycam::messages.push_back(message);
         wraycam::events.push_back(nEvent);
     }
     
     listenerLoopExecute();
}
void wraycam_Start(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_StartPullModeWithCallback(h, wraycam_callback_method, NULL);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Stop(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_Stop(h);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Pause(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    int bPause = PA_GetLongParameter(params, 2);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_Pause(h, bPause);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Snap(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    unsigned nResolutionIndex = PA_GetLongParameter(params, 2);
    unsigned nNumber = PA_GetLongParameter(params, 3);
    nNumber = nNumber > 0 ? nNumber : 1;
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_SnapN(h, nResolutionIndex, nNumber);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Trigger(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    unsigned short nNumber = PA_GetLongParameter(params, 2);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_Trigger(h, nNumber);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Flush(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_Flush(h);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

#ifndef TDIBWIDTHBYTES
#define TDIBWIDTHBYTES(bits) ((unsigned)(((bits)+31)&(~31))/8)
#endif

typedef enum {
    WRAYCAM_IMAGE = 0,
    WRAYCAM_STILL_IMAGE = 1,
    WRAYCAM_IMAGE_WITH_PITCH = 2,
    WRAYCAM_STILL_IMAGE_WITH_PITCH = 3
}wraycam_image_type_t;

void wraycam_Get_image(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    wraycam_image_type_t type = (wraycam_image_type_t)PA_GetLongParameter(params, 2);
    
    int bits = 24;
    int pitch = 0;/* default pitch */
    int oRaw = 0;
    size_t size = 0;
    WraycamFrameInfoV2 info = {0};
    unsigned width = 0;
    unsigned height = 0;
    
    PA_ObjectRef options = PA_GetObjectParameter(params, 3);
    PA_ObjectRef o = PA_CreateObject();
    HRESULT hr = 0;
    
    if(h) {

        if(options) {
            if(ob_is_defined(options, L"pitch"))
            {
                int _pitch = ob_get_n(options, L"pitch");
                if(_pitch > 0) {
                    pitch = _pitch;
                }
            }
        }
        
        switch (type) {
            case WRAYCAM_IMAGE:
            {
                if(SUCCEEDED(Wraycam_PullImageV2(h, NULL, bits, &info))) {
                    width = info.width;
                    height = info.height;
                }
            }
            break;
            case WRAYCAM_STILL_IMAGE:
            {
                if(SUCCEEDED(Wraycam_PullStillImageV2(h, NULL, bits, &info))) {
                    width = info.width;
                    height = info.height;
                }
            }
            break;
            case WRAYCAM_IMAGE_WITH_PITCH:
            {
                if(SUCCEEDED(Wraycam_PullImageWithRowPitchV2(h, NULL, bits, pitch, &info))) {
                    width = info.width;
                    height = info.height;
                }
            }
            break;
            case WRAYCAM_STILL_IMAGE_WITH_PITCH:
            {
                if(SUCCEEDED(Wraycam_PullStillImageWithRowPitchV2(h, NULL, bits, pitch, &info))) {
                    width = info.width;
                    height = info.height;
                }
            }
            break;
            default:
            break;
        }
        
        if(SUCCEEDED(Wraycam_get_Option(h, WRAYCAM_OPTION_RAW, &oRaw))) {
            
            if(oRaw == 1) {
                /*raw*/
                int oFormat = 0;
                if(SUCCEEDED(Wraycam_get_Option(h, WRAYCAM_OPTION_PIXEL_FORMAT, &oFormat))) {
                    switch (oFormat) {
                        case WRAYCAM_PIXELFORMAT_RAW8:
                            bits =  8;
                            size = width;
                            break;
                        case WRAYCAM_PIXELFORMAT_RAW10:
                            bits = 10;
                            size = width * 2;
                            break;
                         case WRAYCAM_PIXELFORMAT_RAW12:
                            bits = 12;
                            size = width * 2;
                            break;
                         case WRAYCAM_PIXELFORMAT_RAW14:
                            bits = 14;
                            size = width * 2;
                            break;
                         case WRAYCAM_PIXELFORMAT_RAW16:
                            bits = 16;
                            size = width * 2;
                         break;
                        default:
                            break;
                    }
                }
            }else{
                /*rgb*/
                int oRgb = 0;
                if(SUCCEEDED(Wraycam_get_Option(h, WRAYCAM_OPTION_RGB, &oRgb))) {

                    switch (oRgb) {
                        case 0 /*RGB24*/:
                            bits = 24;
                            size = TDIBWIDTHBYTES(24*width);
                            break;
                        case 1 /*RGB48*/:
                            bits = 48;
                            size = TDIBWIDTHBYTES(48*width);
                            break;
                        case 2 /*RGB32*/:
                            bits = 32;
                            size = 4*width;
                            break;
                        case 3 /*BW  8*/:
                            bits = 8;
                            size = TDIBWIDTHBYTES(8*width);
                            break;
                        case 4 /*BW 16*/:
                            bits = 16;
                            size = 2*width;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        
        if(options) {
            if(ob_is_defined(options, L"bits"))
            {
                int _bits = ob_get_n(options, L"bits");
                if(_bits >= 8) {
                    bits = _bits;
                }
            }
        }
        
        ob_set_i(o, L"pitch", pitch);
        ob_set_i(o, L"bits", bits);
        ob_set_i(o, L"width", width);
        ob_set_i(o, L"height", height);
        
        if(oRaw == 0) {
            
            /*only rgb (bmp) is supported */
            if(size) {
                std::vector<unsigned> buf(size);
                switch (type) {
                    case WRAYCAM_IMAGE:
                    {
                        hr = Wraycam_PullImageV2(h, &buf[0], bits, &info);
                        if(SUCCEEDED(hr)) {
                            PA_Picture p = PA_CreatePicture(&buf[0], (PA_long32)size);
                            ob_set_p(o, L"image", p);
                        }
                    }
                    break;
                    case WRAYCAM_STILL_IMAGE:
                    {
                        hr = Wraycam_PullStillImageV2(h, &buf[0], bits, &info);
                        if(SUCCEEDED(hr)) {
                            PA_Picture p = PA_CreatePicture(&buf[0], (PA_long32)size);
                            ob_set_p(o, L"image", p);
                        }
                    }
                    break;
                    case WRAYCAM_IMAGE_WITH_PITCH:
                        {
                            hr = Wraycam_PullImageWithRowPitchV2(h, &buf[0], bits, pitch, &info);
                            if(SUCCEEDED(hr)) {
                                PA_Picture p = PA_CreatePicture(&buf[0], (PA_long32)size);
                                ob_set_p(o, L"image", p);
                            }
                        }
                    break;
                    case WRAYCAM_STILL_IMAGE_WITH_PITCH:
                        {
                            hr = Wraycam_PullStillImageWithRowPitchV2(h, &buf[0], bits, pitch, &info);
                            if(SUCCEEDED(hr)) {
                                PA_Picture p = PA_CreatePicture(&buf[0], (PA_long32)size);
                                ob_set_p(o, L"image", p);
                            }
                        }
                    break;
                    default:
                    break;
                }
            }
        }
    }
    
    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Correct_flat_field(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_FfcOnePush(h);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Correct_dark_field(PA_PluginParameters params) {
    
    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_DfcOnePush(h);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Auto_level_range(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_LevelRangeAuto(h);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

void wraycam_Set_LED_state(PA_PluginParameters params) {

    PA_Unistring *u = PA_GetStringParameter(params, 1);
    wraycam_string_t deviceid = getdeviceid(u);
    unsigned short iLed = PA_GetLongParameter(params, 2);
    unsigned short iState = PA_GetLongParameter(params, 3);
    unsigned short iPeriod = PA_GetLongParameter(params, 4);
    HWraycam h = _get_handle(deviceid);
    
    HRESULT hr = 0;
    
    PA_ObjectRef o = PA_CreateObject();
    
    if(h) {
        
        hr = Wraycam_put_LEDState(h, iLed, iState, iPeriod);

    }

    ob_set_i(o, L"result", hr);
    
    PA_ReturnObject(params, o);
}

