//---------------------------------------------------------------------------------------------------------------------------
// Function address from gs
//---------------------------------------------------------------------------------------------------------------------------

#define GetWorldTag()int_func_call(0x0805F8A2) //Получить тег локации
#define GetWorldIndex()int_func_call(0x08056230) //Получить индекс локации
#define GetMaxNPCCount()int_func_call(0x0806E8F2) //получить максимальное количество нпс
#define GetMaxMatterCount()int_func_call(0x0806E8FC) //получить максимальное количество нпс
#define GetNPCByIndex(...)void_func_call(0x0806EEF0,__VA_ARGS__) //Получить объект НПС по индексу
#define GetMatterByIndex(...)void_func_call(0x0806EEB0,__VA_ARGS__) //Получить объект Matter по индексу
#define gobject__IsActived()int_func_call(0x0805F79A) //Получить статус активности объекта

#define InitWorld(...)int_func_call(0x08287130,__VA_ARGS__) //Инициализация локации
#define mutex_spinlock(...)int_func_call(0x083BB4F8,__VA_ARGS__) //Спинлок
#define get_systime()int_func_call(0x083BD114,0x094BF840) //Таймер
#define user_save_data(...)void_func_call(0x081DDCD6,__VA_ARGS__) //Сохранение игрока

//--------------------------------------------------------------------------------------------------------------------------- 
#define Skill__GetPlayer(...)void_func_call(0x0859E18C,__VA_ARGS__) //Получить указатель на персонажа
#define Skill__GetVictim(...)void_func_call(0x08664318,__VA_ARGS__) //Получить указатель на цель
#define Skill__GetDamage(...)int_func_call(0x0859E00E,__VA_ARGS__) // получить дамаг(пета??)
#define Skill__GetLevel(...)int_func_call(0x0859DD88,__VA_ARGS__) //Получить уровень скилла

#define Skill__SetTime(...)int_func_call(0x085F926C,__VA_ARGS__) //Вставить время
#define Skill__SetRatio(...)int_func_call(0x085F92A8,__VA_ARGS__) //Вставить усиление скилла
#define Skill__SetValue(...)int_func_call(0x085F92BC,__VA_ARGS__) //Вставить параметр скилла
#define Skill__SetProbability(...)int_func_call(0x085F9226,__VA_ARGS__) //Вставить шанс успеха
#define Skill__SetAmount(...)int_func_call(0x085F92D2,__VA_ARGS__) //Установить сумму
#define Skill__SetShowicon(...)void_func_call(0x08664088,__VA_ARGS__) //Вставить иконку

#define Skill__SetAp(...)int_func_call(0x08587B3E,__VA_ARGS__) //Дать игроку чи

#define Skill__SetIronshield(...)int_func_call(0x085877AA,__VA_ARGS__) //баф на физ защиту
#define Skill__SetSpeedup(...)int_func_call(0x08580064,__VA_ARGS__) //баф на увеличение скорости
#define Skill__SetWingshield(...)int_func_call(0x08587864,__VA_ARGS__) //баф перистый барьер

#define Skill__SetBleeding(...)int_func_call(0x08582778,__VA_ARGS__) //дебаф на кровотечение
#define Skill__SetBurning(...)int_func_call(0x08582078,__VA_ARGS__) //дебаф на поджог
#define Skill__SetThunder(...)int_func_call(0x08581978,__VA_ARGS__) //дебаф на удары током
#define Skill__SetToxic(...)int_func_call(0x08581CF8,__VA_ARGS__) //дебаф на отравление
#define Skill__SetFlood(...)int_func_call(0x085815F8,__VA_ARGS__) //дебаф на обморожение
#define Skill__SetSlow(...)int_func_call(0x08582B9C,__VA_ARGS__) //дебаф на замедление
#define Skill__SetFix(...)int_func_call(0x08581324,__VA_ARGS__) //дебаф на паралич

#define Skill__SetDirecthurt(...)int_func_call(0x085806D8,__VA_ARGS__) //дебаф отсос пета
#define Skill__SetEaglecurse(...)int_func_call(0x08587BA6,__VA_ARGS__) //дебаф когти небес(птица лука)
#define Skill__SetInchurt(...)int_func_call(0x085841B8,__VA_ARGS__) //дебаф драки
#define Skill__SetDecdefence(...)int_func_call(0x08580204,__VA_ARGS__) //дебаф на физ защиту
#define Skill__SetDecresist(...)int_func_call(0x08584784,__VA_ARGS__) //дебаф на маг физ защиту

#define Skill__SetDecattack(...)int_func_call(0x08585E06,__VA_ARGS__) // атака ??
#define Skill__SetDecmagic(...)int_func_call(0x08585CF2,__VA_ARGS__) // маг атака ???
#define Skill__SetMagicleak(...)int_func_call(0x085814EA,__VA_ARGS__)

#define Skill__SetTigerform(...)int_func_call(0x08584B9A,__VA_ARGS__) //облик танка
#define Skill__SetFoxform(...)int_func_call(0x0858888C,__VA_ARGS__) //облик друльки

#define Skill__SetIncmagic(...)int_func_call(0x085836EE,__VA_ARGS__) //маг атака 3 чи

#define Skill__SetScaleincmp(...)int_func_call(0x08586D78,__VA_ARGS__) //восстановление маны
#define Skill__SetInvincible2(...)int_func_call(0x08586296,__VA_ARGS__) //3 чи снять негативные эффекты и иммун
#define Skill__SetDechurt(...)int_func_call(0x08586FFC,__VA_ARGS__) //3 чи защита от атак
#define Skill__SetFastpray(...)int_func_call(0x08586BD0,__VA_ARGS__) // апнуть пение

//---------------------------------------------------------------------------------------------------------------------------
#define CommandHandler(...)int_func_call(0x0813E424,__VA_ARGS__) //обычные команды
#define DebugCommandHandler(...)int_func_call(0x081472F2,__VA_ARGS__) //дебаг команды
#define HookCommandHandler(...)int_func_call(0x095E0BF7,__VA_ARGS__) //мои команд хендлеры
#define CheckAndSetCoolDown(...)int_func_call(0x080B2DD6,__VA_ARGS__) //Проверить и повесить кулдаун
#define PlayerEquipItem(...)void_func_call(0x08092486,__VA_ARGS__) //Свапнуть шмотку
#define LongJump(...)int_func_call(0x0809406E,__VA_ARGS__) //Телепорт персонажа

//---------------------------------------------------------------------------------------------------------------------------


#define world__object_info__object_info(...)void_func_call(0x080D438E,__VA_ARGS__) //получить инфу об объекте
#define world__QueryObject(...)int_func_call(0x08068822,__VA_ARGS__) //получить инфу об объекте
#define world__GetMatterByIndex(...)int_func_call(0x0806EEB0,__VA_ARGS__) //получить инфу об объекте

//---------------------------------------------------------------------------------------------------------------------------
#define GetEquipInventory(...)int_func_call(0x081A725C,__VA_ARGS__) //получить эквип персонажа
#define RefreshEquipment(...)void_func_call(0x08093020,__VA_ARGS__) //игрок переоделся
#define RemovePlayer(...)void_func_call(0x0806689E,__VA_ARGS__) //удалить игрока
#define IsZombie(...)int_func_call(0x0805F7A6,__VA_ARGS__) //проверка мертв ли объект
#define send_ls_msg_packet_raw_wrapper(...)int_func_call(0x080CD90A,__VA_ARGS__) //отправить клиенту статы
#define packet_raw_wrapper__push_byte(...)int_func_call(0x08078864,__VA_ARGS__) //оператор << 
#define GetImpById(...)void_func_call(0x095DFC44,__VA_ARGS__) //получить объект по иду
#define session_gather__StartSession(...)int_func_call(0x08125CD4,__VA_ARGS__) //Сессия выкапывания шахты
#define item_list__Find(...)int_func_call(0x08061DE4,__VA_ARGS__) //Получить позицию итема из инвентаря

//---------------------------------------------------------------------------------------------------------------------------
#define broadcast_chat_msg(...)int_func_call(0x080768CA,__VA_ARGS__) //Отправить сообщение глобально 

//---------------------------------------------------------------------------------------------------------------------------
typedef bool (*DisconnectPlayer)(int lid, int userid, int sid, int reason);
typedef void (*ReportToGACD)(int roleid, int cheattype, const void* buf, size_t size);
typedef int (*SetNotify)(void* imp, bool state);

gplayer_imp* gplayer_controller::GetImp(){ return ((gplayer_imp**)this)[1]; }
int gplayer_imp::GetPlayerID(){ return ((int**)this)[2][12]; }
int gplayer_imp::Get_cs_index(){ return ((int**)this)[2][41]; }
int gplayer_imp::Get_cs_sid(){ return ((int**)this)[2][42]; }
int gplayer_imp::PlaneEnterNotify(bool state){ return ((SetNotify)0x0809FDF4)(this, state); }
bool SendDisconnect(int lid, int userid, int sid, int reason){ return((DisconnectPlayer)0x083ED44A)(lid, userid, sid, reason); }
void ReportCheater2Gacd(int roleid, int cheattype, const void* buf, size_t size){ return ((ReportToGACD)0x083ED830)(roleid, cheattype, buf, size); }
//---------------------------------------------------------------------------------------------------------------------------
inline int get_roleid_pObj(char *_this){ return *((int *)_this + 12); }
inline int get_roleid_pImp(char* _this){ return *(int *)(*((int *)_this + 2) + 48); }

