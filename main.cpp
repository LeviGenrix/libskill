//---------------------------------------------------------------------------------------------------------------------------
// Headers
//---------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <wchar.h> 
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <execinfo.h>
#include <signal.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "utf.h"
#include "utf.hpp"
#include "macro_lib.h"
#include "pwstruct_lib.h"
#include "pwfunc_lib.h"
#define __MAX_BLACKHWID_SIZE 128
static int tick = 0;
static int pwskill_mod136 = 0;
static std::vector<STORAGE> storage;
static HWID_LIMITER hw_limiter[128];
static int64_t BLACKHWID[__MAX_BLACKHWID_SIZE] = { 0 };
#include "patch_lib.hpp"
#include "pwskill_lib.hpp"
#include "pwstorage_lib.hpp"

//---------------------------------------------------------------------------------------------------------------------------
// Цикл таймера
//---------------------------------------------------------------------------------------------------------------------------
void* lib_TimerLoop(void*)
{
pthread_detach(pthread_self());
while(true)
	{
	usleep(1000000);
	tick++;
	lua_OnTimer(tick);
	// Действия каждую секунду
	// ...
	}
return 0;
}
//---------------------------------------------------------------------------------------------------------------------------
// Загрузка локации
//---------------------------------------------------------------------------------------------------------------------------
int lib_OnWorldInit(char *name, char *world_name)
{
	// Вызываем оригинальную функцию
	int res = InitWorld(name, world_name);

	// Действия после загрузки локации
	int worldtag = GetWorldTag();
	printf("%s [lib_OnWorldInit]: worldtag:%d name:%s res:%d\n",
		nowstr(get_systime()), worldtag, world_name, res);

	// Иные действия
	lua_OnInitWorld();
	// ...

	// Создаём поток таймера
	pthread_t thread;
	pthread_create(&thread,0,lib_TimerLoop,0);

	return res;
}
//------------------------------------------------------------------------
// Обработчик сигналов ошибок
//------------------------------------------------------------------------
void lib_OnSignal(int signum, siginfo_t *info, ucontext_t *uc)
{
	#define CALL_SIZE 100
	void *buffer[CALL_SIZE];
	int nptrs = backtrace(buffer, CALL_SIZE);
	char **strings = backtrace_symbols(buffer, nptrs);

	printf("********************** %s  **********************\n",nowstr());
	const char* signal_str[] = {	" ","SIGHUP","SIGINT","SIGQUIT", "SIGILL","SIGTRAP","SIGABRT","SIGIOT",
									"SIGBUS","SIGFPE","SIGKILL","SIGUSR1","SIGSEGV","SIGUSR2","SIGPIPE","SIGALRM",
									"SIGTERM","SIGSTKFLT","SIGCHLD","SIGCONT","SIGSTOP","SIGTSTP","SIGTTIN","SIGTTOU",
									"SIGURG","SIGXCPU","SIGXFSZ","SIGVTALRM","SIGPROF","SIGWINCH","SIGIO","SIGPWR","SIGSYS" };
	printf("Signal: %s(%d), si_signo: %d, si_code: %d, si_addr: %08X\n",
		signal_str[signum], signum, info->si_signo, info->si_code, info->si_addr);
	printf("Registers: EIP=%08X, EAX=%08X ,EBX=%08X, ECX=%08X, EDX=%08X, ESI=%08X, EDI=%08X, EBP=%08X, ESP=%08X\n",
		uc->uc_mcontext.gregs[REG_EIP],uc->uc_mcontext.gregs[REG_EAX],uc->uc_mcontext.gregs[REG_EBX],
		uc->uc_mcontext.gregs[REG_ECX],uc->uc_mcontext.gregs[REG_EDX],uc->uc_mcontext.gregs[REG_ESI],
		uc->uc_mcontext.gregs[REG_EDI],uc->uc_mcontext.gregs[REG_EBP],uc->uc_mcontext.gregs[REG_ESP]);
	fflush(stdout);

	if(strings)
		{
		for(int j = 0; j < nptrs; ++j)
			{
			printf(".%02d) [%08X] => %s\n", j+1, buffer[j], strings[j]);
			}
		fflush(stdout);
		free(strings);
		}

	fflush(stdout);
	kill(getpid(),9);
}
//------------------------------------------------------------------------
void lib_SetupSignalHandler()
{
	struct sigaction act;
	memset(&act, 0, sizeof(act));
	*(void**)&act.sa_sigaction = (void*)lib_OnSignal;
	act.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGSEGV, &act, 0);
	sigaction(SIGQUIT, &act, 0);
	sigaction(SIGILL, &act, 0);
	sigaction(SIGABRT, &act, 0);
	sigaction(SIGFPE, &act, 0);
	sigaction(SIGKILL, &act, 0);
	sigaction(SIGSYS, &act, 0);
	sigaction(SIGALRM, &act, 0);
}
//---------------------------------------------------------------------------------------------------------------------------
// Загрузка плагина
//---------------------------------------------------------------------------------------------------------------------------
void __attribute__ ((constructor)) lib_onload(void)
{
// Настройка окружения
putenv("LD_PRELOAD=");
srand((unsigned int)time(0));
lib_SetupSignalHandler();

// Разрешаем модифицировать секции
setup_rotect_mem(0x08053E40, 0x08D4AD4B, PROT_RWX);		// .text
setup_rotect_mem(0x08D4AD80, 0x08FD7A2A, PROT_RW);		// .rodata

//Функция установки хуков и патчей
setup_call(0x08054562,lib_OnWorldInit);

//Глобальные функции патчинга
OnStoragePatch(); //расширенная база данных
lua_OnPatch(); //луа движок
OnSkillPatch(); //редактор скиллов

}
//---------------------------------------------------------------------------------------------------------------------------
// Выгрузка плагина
//---------------------------------------------------------------------------------------------------------------------------
void __attribute__ ((destructor)) lib_onunload(void)
{

}
//---------------------------------------------------------------------------------------------------------------------------
