//---------------------------------------------------------------------------------------------------------------------------
//--LUA SCRIPT 
//---------------------------------------------------------------------------------------------------------------------------
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "LuaBridge/LuaBridge.h"
//---------------------------------------------------------------------------------------------------------------------------
//--Глобальные функции
//---------------------------------------------------------------------------------------------------------------------------
void BLACKHWID_clean();
void BLACKHWID_set(const char * hw);
//---------------------------------------------------------------------------------------------------------------------------
//--Мои функции
//---------------------------------------------------------------------------------------------------------------------------
#define __MAX_MESSAGE_SIZE 128
void game__BroadcastChat(int roleid, char channel, const char * src)
{
	size_t len = strlen(src);
	if(len < 1 || len > __MAX_MESSAGE_SIZE) return;
	size_t wlen = (len * 2);
	static utf16_t wbuf[__MAX_MESSAGE_SIZE];
	setup_fillmem(wbuf,0x00,(__MAX_MESSAGE_SIZE*2));
	utf8_to_utf16(src, len, wbuf, wlen );
	broadcast_chat_msg(roleid,wbuf,wlen,channel,0,0, 0);
}
//-----------------------------------------------------------------------------------------------------------------------------
int game__GetWorldTag()
{
	return GetWorldTag();
}
//-----------------------------------------------------------------------------------------------------------------------------
int game__GetWorldIndex()
{
	return GetWorldIndex();
}
//-----------------------------------------------------------------------------------------------------------------------------
void game__SetBlackHwid(const char * hw)
{
	return BLACKHWID_set(hw);
}
//-----------------------------------------------------------------------------------------------------------------------------
void game__ClearBlackHwid()
{
	return BLACKHWID_clean();
}
//-----------------------------------------------------------------------------------------------------------------------------


// ...


//-----------------------------------------------------------------------------------------------------------------------------
//--LUA PARAMETRS--
//-----------------------------------------------------------------------------------------------------------------------------
using namespace luabridge;
lua_State* L;
pthread_mutex_t lua_mutex;
volatile const char lua_fname[] = "script.lua";
volatile int lua_file_edit_time = 0;
//-----------------------------------------------------------------------------------------------------------------------------
//--LUA REGISTER--
//-----------------------------------------------------------------------------------------------------------------------------
void game__PatchGS(int address, const char * param, float value)
{
	
	if(!strcmp(param,"int"   )) setup_uint  (address,(unsigned int  )value);
	if(!strcmp(param,"short" )) setup_ushort(address,(unsigned short)value);
	if(!strcmp(param,"char"  )) setup_uchar (address,(unsigned char )value);
	if(!strcmp(param,"float" )) setup_float (address,(float         )value);
	if(!strcmp(param,"double")) setup_double(address,(double        )value);

}
//-----------------------------------------------------------------------------------------------------------------------------
float game__GetGS(int address, const char * param, int offt)
{
	float res = 0;
	if(!address) return res;
	if(!strcmp(param,"int"   )) { res = get_uint  (address,offt); return res; }
	if(!strcmp(param,"short" )) { res = get_ushort(address,offt); return res; }
	if(!strcmp(param,"char"  )) { res = get_uchar (address,offt); return res; }
	if(!strcmp(param,"float" )) { res = get_float (address,offt); return res; }
	if(!strcmp(param,"double")) { res = get_double(address,offt); return res; }
	return res;
}
//---------------------------------------------------------------------------------------------------------------------------
void global_FunctionsRegister()
{
	getGlobalNamespace(L).addFunction("game__PatchGS",game__PatchGS);
	getGlobalNamespace(L).addFunction("game__GetGS",game__GetGS);
	getGlobalNamespace(L).addFunction("game__BroadcastChat",game__BroadcastChat);
	getGlobalNamespace(L).addFunction("game__GetWorldTag",game__GetWorldTag);
	getGlobalNamespace(L).addFunction("game__GetWorldIndex",game__GetWorldIndex);
	getGlobalNamespace(L).addFunction("game__SetBlackHwid",game__SetBlackHwid);
	getGlobalNamespace(L).addFunction("game__ClearBlackHwid",game__ClearBlackHwid);
}
//---------------------------------------------------------------------------------------------------------------------------
//--LUA LOADER--
//-----------------------------------------------------------------------------------------------------------------------------
int global_GetInt(const char *s)
{
	LuaRef out = getGlobal(L,s);
	if(out.isNil())
	{
		printf("LUA_GET_INT: error %s not found! \n",s);
		return 0;
	}
	return out.cast<int>();
}
//-----------------------------------------------------------------------------------------------------------------------------
float global_GetFloat(const char *s)
{
	LuaRef out = getGlobal(L,s);
	if(out.isNil())
	{
		printf("LUA_GET_FLOAT: error %s not found! \n",s);
		return 0;
	}
	return out.cast<float>();
}
//-----------------------------------------------------------------------------------------------------------------------------
const char * global_GetText(const char *s)
{
	LuaRef out = getGlobal(L,s);
	if(out.isNil() || !out.isString())
	{
		printf("LUA_GET_STRING: error %s not found! \n",s);
		return "text failed!";
	}
	return out.cast<const char *>();	
}
//-----------------------------------------------------------------------------------------------------------------------------
time_t lua_get_mtime(const char *path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) == -1) {
        perror(path);
        exit(1);
    }
    return statbuf.st_mtime;
}
//-----------------------------------------------------------------------------------------------------------------------------
void lua_GetGlobalItems()
{
	pwskill_mod136 = global_GetInt("pwskill_mod136");
}
//-----------------------------------------------------------------------------------------------------------------------------
void lua_SetGlobalItems()
{
	setGlobal(L,(int)hw_limiter,"hw_limiter");
}
//-----------------------------------------------------------------------------------------------------------------------------
void lua_load()
{
	pthread_mutex_init(&lua_mutex,0);
	pthread_mutex_lock(&lua_mutex);
	usleep(64);
	lua_file_edit_time = lua_get_mtime(lua_fname);
	L = luaL_newstate();
	luaL_openlibs(L);
	global_FunctionsRegister();
    luaL_dofile(L, lua_fname);
	lua_SetGlobalItems();
	LuaRef EventOnBeforeStartGS = getGlobal(L, "EventOnBeforeStartGS");
	if(!EventOnBeforeStartGS.isNil())
	EventOnBeforeStartGS();
	lua_GetGlobalItems();
	pthread_mutex_unlock(&lua_mutex);
}
//-----------------------------------------------------------------------------------------------------------------------------
void lua_reloader()
{
	int last = lua_get_mtime(lua_fname);
	if(lua_file_edit_time == last) return;	
	lua_file_edit_time = last;
	pthread_mutex_lock(&lua_mutex);
	usleep(64);
	lua_close(L);
	L = luaL_newstate();
	luaL_openlibs(L);
	global_FunctionsRegister();
    luaL_dofile(L, lua_fname);
	lua_SetGlobalItems();
	LuaRef EventOnReloadScript = getGlobal(L, "EventOnReloadScript");
	if(!EventOnReloadScript.isNil())
	EventOnReloadScript(GetWorldTag());
	lua_GetGlobalItems();
	pthread_mutex_unlock(&lua_mutex);
}
//---------------------------------------------------------------------------------------------------------------------------
void lua_world()
{
	pthread_mutex_lock(&lua_mutex);
	usleep(16);
	LuaRef EventOnInitWorld = getGlobal(L, "EventOnInitWorld");
	if(!EventOnInitWorld.isNil())
	EventOnInitWorld();
	pthread_mutex_unlock(&lua_mutex);
}

//---------------------------------------------------------------------------------------------------------------------------
//--LUA IVENTS--
//---------------------------------------------------------------------------------------------------------------------------
void lua_OnTimer(int tick) //выполнение функции по таймеру
{
	if( !(tick & 10) )
	lua_reloader();
}
//---------------------------------------------------------------------------------------------------------------------------
void lua_OnInitWorld() //пропатчить после инициализации локации
{
	lua_world();
}
//---------------------------------------------------------------------------------------------------------------------------
void lua_OnPatch() //пропатчить до загрузки данжей для всех функций
{
	lua_load();
}
//---------------------------------------------------------------------------------------------------------------------------
#define __MAX_HWID_SIZE 16
//---------------------------------------------------------------------------------------------------------------------------
void lua_EventPlayerSetHwid(int roleid, int64_t hw) //игрок отправил хвид
{
	
	static char hwid[__MAX_HWID_SIZE];
	setup_fillmem(hwid,0x00,__MAX_HWID_SIZE);
	sprintf(hwid,"%lld",hw);
	pthread_mutex_lock(&lua_mutex);
	usleep(4);
	LuaRef EventPlayerSetHwid = getGlobal(L, "EventPlayerSetHwid");
	if(!EventPlayerSetHwid.isNil())
	EventPlayerSetHwid(roleid,(const char*)hwid);
	pthread_mutex_unlock(&lua_mutex);
}
//---------------------------------------------------------------------------------------------------------------------------









