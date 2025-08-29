//---------------------------------------------------------------------------------------------------------------------------
//--Названия
//---------------------------------------------------------------------------------------------------------------------------
enum
	{
	CLS_COUNT = 11,
	MAX_COOLDOWN = 10,
	
	WARRIOR = 0,
	MAG = 1,
	SHAM = 2,
	DRUID = 3,
	OBOR = 4,
	ASSASIN = 5,
	LUK = 6,
	PRIST = 7,
	STRAJ = 8,
	MIST = 9,
	GHOST = 10,
	JNEC = 11,
	
	GTI_COUIN = 8,
	
	ITEM_LIMIT = 16,
	TAG_LIMIT = 16,
	COUNT_ITEMS = 8,	
	
	HW_TAGS = 7
	};
//---------------------------------------------------------------------------------------------------------------------------
// Структуры
//---------------------------------------------------------------------------------------------------------------------------
struct XID
	{
	int type, id;
	};

struct A3DVECTOR
	{
    float x, y, z;
	};
//---------------------------------------------------------------------------------------------------------------------------
//Мои структуры
//---------------------------------------------------------------------------------------------------------------------------
struct gplayer_imp
{
	int GetPlayerID();
	int Get_cs_index();
	int Get_cs_sid();
	int CheckBanList();
	int PlaneEnterNotify(bool state);
};

struct gplayer_controller
{
  char *baseclass_0;
  gplayer_imp* GetImp();
  XID _cur_target;
  XID _cur_sub_target;
  bool _target_refresh_state;
  A3DVECTOR _last_pos;
  int _load_stats;
  short _peep_counter;
  short _select_counter;
  bool _debug_command_enable;
  char _banish_counter;
  unsigned short _move_cmd_seq;
  short _deny_cmd_list[8];
  short _pickup_counter;
  int _pickup_timestamp;
  int _safe_lock_timestamp;
  int _max_safe_lock;
  void *_gm_auth;
};
//---------------------------------------------------------------------------------------------------------------------------
struct PlayerWrapper
	{		
	void* _vptr_PlayerWrapper;
	void* object_interface;
	void* skillwrapper;
	void* skill;
	XID *target;
	int tsize;
	void* skilllevel;
	void* bufflevel;
	void* comboarg;
	void* callup;
	float probability;
	float ratio;
	float amount;
	float value;
	bool showicon;
	int time;
	int intarg;
	bool enable;
	char success;
	short immune;
	bool invader;	
	};
//---------------------------------------------------------------------------------------------------------------------------
struct SKILL
	{
	void* _vptr_Skill;
	unsigned int id;
	int level;
	void* stub;
	void* player;
	void* target;
	void* pdata;
	void* enchantmsg;
	void* attackmsg;
	XID performerid;
	int performerlevel;
	A3DVECTOR performerpos;
	float ratio;
	float plus;
	int damage;
	int magic;
	int degree;
	int magicdamage[5];
	int t0;
	int t1;
	int t2;	
	};
//---------------------------------------------------------------------------------------------------------------------------
struct world__object_info
{
  int state;
  A3DVECTOR pos;
  float body_size;
  int race;
  int faction;
  int level;
  int hp;
  int mp;
  int max_hp;
  int invisible_degree;
  int anti_invisible_degree;
  unsigned int object_state;
  unsigned int object_state2;
  int mafia_id;
  int master_id;
};
//---------------------------------------------------------------------------------------------------------------------------
struct damage_entry
	{
	float physic_damage;
	float magic_damage[5];
	};
struct WEAPON_DATA
    {
	unsigned int id, speed;
	};
struct BUG_SKILL
	{
	unsigned int id, enable;
	};
struct FIRST_RUN
	{
	int time, max_time;
	};	
struct vendor_provider__bag
	{
	int item_type;
	size_t index;
	size_t count;
	};
struct vendor_provider__request
	{
	size_t money;
	int consume_contrib;
	int cumulate_contrib;
	int force_id;
	int force_repu;
	int force_contrib;
	size_t count;
	vendor_provider__bag item_list[];
	};
struct NPC_SELL_SERVICE__ITEM
	{
	unsigned int id;
	int contrib_cost;
	int force_contribution_cost;
	int solo_tower_challenge_score_cost;
	};
struct NPC_SELL_SERVICE_PAGES
	{
	short page_title[8];
	int require_contrib;
	unsigned int require_force;
	int require_force_reputation;
	NPC_SELL_SERVICE__ITEM goods[32];
	};
struct NPC_SELL_SERVICE
	{
	unsigned int id;
	short name[32];
	NPC_SELL_SERVICE_PAGES pages[8];
	unsigned int id_dialog;
	};	
struct twman_t
	{
	bool enable;
	unsigned int begin;
	unsigned int end;
	unsigned int max;
	unsigned int battle;
	};
struct twman_rpc
	{
	int day_use;
	twman_t tw_matrix[7];
	};
struct COOLDOWN
	{
	unsigned int xid, time;
	};
struct SWAP_EQUIP
	{
	unsigned int index_inv, index_equip;
	};
struct SWAP_BUFF
	{
	unsigned int count;
	SWAP_EQUIP items[32];
	};
struct ICAST_SKILL
	{
	unsigned int id, time;
	};	
struct BALANCE_EDITOR
	{
	float fiz, mag;
	};
struct CLS_BALANCE_EDITOR
	{
	BALANCE_EDITOR cls[CLS_COUNT];
	};
struct ENABLE_ITEM
{
        int id;
        int enable;
};
struct TAG_ENABLE_ITEM
{
        ENABLE_ITEM items[ITEM_LIMIT];
        int tags[TAG_LIMIT];
};
struct GATCHER_TIME_ITEMS
{
int id, min, max;
short time;
};	
//---------------------------------------------------------------------------------------------------------------------------
struct ACT_SESSION
{
	void *baseclass_0;
	char *_imp;
	int _session_id;
	void *_plane;	
};
struct TIMER_TASK
{
	void *_vptr_timer_task;
	int _timer_index;
	int _tm;
};
struct SESSION_GATCHER
{
	ACT_SESSION ses;
	TIMER_TASK time;
	XID _self_id;
	int _mine;
	short _gather_time;
	char _gather_flag;
	char _can_be_interruputed;
	char _lock_inventory;
	char reserve1;
	char reserve2;
	char reserve3;
};
//---------------------------------------------------------------------------------------------------------------------------
struct GOBJECT_IMP
{
	void *baseclass_0;
	char *_plane;    
	char *_parent; 
	char *_commander;
	char *_runner; 
};
struct GATCHER_MINE_IMP
{
	GOBJECT_IMP gObj;
	int _collision_actived;
	int _produce_id;
	int _produce_amount;
	int _produce_tool;
	int _produce_task_id;
	int _task_id;
	void *_spawner;
	bool _eliminate_tool;
	bool _gather_no_disappear;
	bool _can_be_interrupted;
	bool _broadcast_aggro;
	char _lock_time_out;
	unsigned short _gather_time_min;
	unsigned short _gather_time_max;
	int _level;
	int _exp;
	int _sp;
	int _self_faction;
	int _ask_help_faction;
	float _aggro_range;
	int _aggro_count;
	char _mine_type;
	int _owner;
	int _gather_player_max;
	float _gather_distance_max;
	int _produce_life;
	int _mine_life;
	float _gather_success_prob;
	int _broadcast_on_gain;
	XID _gather_players[2];
	void* produce_monster[4];	
};
//---------------------------------------------------------------------------------------------------------------------------
struct GOBJECT
{
	int spinlock;
	int cur_msg;
	unsigned int crc;
	bool b_chk_state;
	bool b_zombie;
	bool b_disconnect;
	char dir;
	int msg_mask;
	void *pPrev;
	void *pNext;
	void *pPiece;
	A3DVECTOR pos;
	XID ID;
	void *imp;
	void *plane;
	float body_size;
	int collision_id;
};
//---------------------------------------------------------------------------------------------------------------------------
struct GMATTER
{
	GOBJECT obj;
	unsigned char dir1;
	unsigned char rad;
	unsigned char matter_state;
	unsigned char matter_value;
	int matter_type;
	int spawn_index;
};
//---------------------------------------------------------------------------------------------------------------------------
struct HWID_LIMITER
{
	int tag;
	int limit;
};
//---------------------------------------------------------------------------------------------------------------------------
struct STORAGE
{
    int roleid;
    gplayer_imp *pImp;
	int kill_player_count;
	int kill_monster_count;
	int64_t hwid;
		
    STORAGE(gplayer_imp* _this, char* file, size_t fsize)
    {
		setup_fillmem(this,0x00,sizeof(STORAGE));
		if(fsize && file && fsize <= sizeof(STORAGE)) 
		memcpy(this,file,fsize);
		if(_this)
		this->roleid = _this->GetPlayerID();
		this->pImp = _this;
    }
};



