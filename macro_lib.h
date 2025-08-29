//---------------------------------------------------------------------------------------------------------------------------

typedef void* (*void_call_prototype)(...);
typedef int (*int_call_prototype)(...);
typedef int64_t (*int64_call_prototype)(...);
typedef float (*float_call_prototype)(...);
typedef double (*double_call_prototype)(...);

#define void_func_call(address,...)((void_call_prototype)address)(__VA_ARGS__)
#define int_func_call(address,...)((int_call_prototype)address)(__VA_ARGS__)
#define int64_t_func_call(address,...)((int64_call_prototype)address)(__VA_ARGS__)
#define float_func_call(address,...)((float_call_prototype)address)(__VA_ARGS__)
#define double_func_call(address,...)((double_call_prototype)address)(__VA_ARGS__)

//---------------------------------------------------------------------------------------------------------------------------

#define setup_call(address,dest) ((int*)((unsigned int)address + 1))[0] = (int)((unsigned int)dest - (unsigned int)(address + 5)); \
								 ((char*)address)[0] = 0xE8;

#define setup_farjmp(address,dest) ((int*)((unsigned int)address + 1))[0] = (int)((unsigned int)dest - (unsigned int)(address + 5)); \
								 ((char*)address)[0] = 0xE9;


#define setup_char(address,value) *(char*)address = value;
#define setup_uchar(address,value) *(unsigned char*)address = value;
#define setup_short(address,value) *(short*)address = value;
#define setup_ushort(address,value) *(unsigned short*)address = value;
#define setup_int(address,value) *(int*)address = value;
#define setup_uint(address,value) *(unsigned int*)address = value;
#define setup_float(address,value) *(float*)address = value;
#define setup_double(address,value) *(double*)address = value;
#define setup_void(address,value) *(void**)address = (void*)value;
#define setup_fillmem(address,value,size) memset((void*)address,value,size);
#define setup_copymem(address,value,size) memcpy((void*)address,value,size);

#define pFloat(arg) (*(int*)&arg)

#define get_int(address,offset) ( *(int*)( &((char*)address)[offset] )  )
#define get_uint(address,offset) ( *(unsigned int*)( &((char*)address)[offset] )  )
#define get_char(address,offset) ( *(char*)( &((char*)address)[offset] )  )
#define get_uchar(address,offset) ( *(unsigned char*)( &((char*)address)[offset] )  )
#define get_short(address,offset) ( *(short*)( &((char*)address)[offset] )  )
#define get_ushort(address,offset) ( *(unsigned short*)( &((char*)address)[offset] )  )
#define get_float(address,offset) ( *(float*)( &((char*)address)[offset] )  )
#define get_double(address,offset) ( *(double*)( &((char*)address)[offset] )  )
#define get_void(address,offset) ( *(void**)( &((char*)address)[offset] )  )

//---------------------------------------------------------------------------------------------------------------------------

#ifndef PAGESIZE
#define PAGESIZE 4096
#endif

#define PROT_RWX (PROT_READ | PROT_WRITE | PROT_EXEC)
#define PROT_RW  (PROT_READ | PROT_WRITE)

#define DAY(v) (time & 604800) / 7

inline int setup_rotect_mem(unsigned int addr_begin, unsigned int addr_end, int prot)
{
addr_begin &= ~(PAGESIZE-1);
unsigned int count = ((addr_end - addr_begin) / PAGESIZE) + 1;
return mprotect((void*)addr_begin,(PAGESIZE * count),prot);
}

//---------------------------------------------------------------------------------------------------------------------------
char* nowstr(long intime = time(0))
{
char *res = (char*)ctime(&intime);
res[strlen(res) - 1] = 0;
return res;
}
//---------------------------------------------------------------------------------------------------------------------------
inline int ID2WIDX(int id)
{
  return (id & 0xFF00000u) >> 20;
}
//---------------------------------------------------------------------------------------------------------------------------
inline int ID2IDX(int id)
{
  return id & 0xFFFFF;
}
//---------------------------------------------------------------------------------------------------------------------------



