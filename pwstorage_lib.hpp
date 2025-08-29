//---------------------------------------------------------------------------------------------------------------------------
//--Вектор хранилища данных персонажей
//---------------------------------------------------------------------------------------------------------------------------
int storage_get_roleid(int roleid)
{
	int res = -1;
	pthread_mutex_lock(&lua_mutex);
	for (unsigned int i = 0; i < storage.size(); i++)
		if (storage.at(i).roleid == roleid)
			res = i;
	pthread_mutex_unlock(&lua_mutex);
	return res;
}
//---------------------------------------------------------------------------------------------------------------------------
int64_t storage_get_roleid_hwid(int roleid)
{
	int64_t res = 0;
	pthread_mutex_lock(&lua_mutex);
	for (unsigned int i = 0; i < storage.size(); i++)
		if (storage.at(i).roleid == roleid)
			res = storage.at(i).hwid;
	pthread_mutex_unlock(&lua_mutex);
	return res;
}
//---------------------------------------------------------------------------------------------------------------------------
int storage_get_imp(gplayer_imp* pImp)
{
	int res = -1;
	pthread_mutex_lock(&lua_mutex);
	for (unsigned int i = 0; i < storage.size(); i++)
		if (storage.at(i).pImp == pImp)
			res = i;
	pthread_mutex_unlock(&lua_mutex);
	return res;
}
//---------------------------------------------------------------------------------------------------------------------------
int storage_get_hwid(int64_t hw)
{
	int res = -1;
	pthread_mutex_lock(&lua_mutex);
	for (unsigned int i = 0; i < storage.size(); i++)
		if (storage.at(i).hwid == hw)
			res = i;
	pthread_mutex_unlock(&lua_mutex);
	return res;	
}
//---------------------------------------------------------------------------------------------------------------------------
int storage_get_count_hwid(int idx)
{
	int res = 0;
	pthread_mutex_lock(&lua_mutex);
	if (idx != -1 && idx < storage.size() && storage.at(idx).hwid != 0)
	{
		int64_t hw = storage.at(idx).hwid;
		for (unsigned int i = 0; i < storage.size(); i++)
			if (storage.at(i).hwid == hw)
				res++;
	}
	else
		res = -1;
	pthread_mutex_unlock(&lua_mutex);
	return res;
}
//---------------------------------------------------------------------------------------------------------------------------
int storage_destroy(int roleid)
{
	int idx = storage_get_roleid(roleid);
	if (idx != -1)
	{
		pthread_mutex_lock(&lua_mutex);
		int size = sizeof(STORAGE);
		char line[16];
		sprintf(line,"./var/%d",roleid);
		FILE *var = fopen(line, "wb");
		if (var != NULL) 
		{			
			fwrite(&storage.at(idx), 1, size, var);		
			storage.erase(storage.begin() + idx);
			fclose(var);
		}
		pthread_mutex_unlock(&lua_mutex);
	}	
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------
int storage_open(gplayer_imp* _this)
{
	if(!_this) return 0;
	int roleid = _this->GetPlayerID();
	int idx = storage_get_roleid(roleid);
	
	pthread_mutex_lock(&lua_mutex);
	if(idx != -1) 
	storage.erase(storage.begin() + idx);
	
	char line[16]; 
	sprintf(line,"./var/%d",roleid);
	FILE *var = fopen(line, "a+b");
	fseek(var , 0 , SEEK_END);
	size_t fsize = ftell(var); 
	rewind (var);
	char *src = (char*)malloc(fsize);
	if(src == NULL) 
	{
		fclose(var);
		pthread_mutex_unlock(&lua_mutex);
		return 0;
	}
	
	size_t fres = fread(src, 1, fsize, var);
	if(fres != fsize) 
	{
		fclose(var);
		free(src);
		pthread_mutex_unlock(&lua_mutex);	
		return 0;
	}
	
	puts(src);	
	storage.push_back(STORAGE(_this,src,fsize));
	fclose(var);
	free(src);
	pthread_mutex_unlock(&lua_mutex);
	return 1;	
}
//---------------------------------------------------------------------------------------------------------------------------
int storage_save(char* _this)
{
	if(!_this) return 0;
	int roleid = get_roleid_pImp(_this);
	int idx = storage_get_roleid(roleid);
	pthread_mutex_lock(&lua_mutex);
	if(idx == -1) 
	{
		pthread_mutex_unlock(&lua_mutex);
		return 0;
	}

	int size = sizeof(STORAGE);
	char line[16];
	sprintf(line,"./var/%d",roleid);
	FILE *var = fopen(line, "wb");
	if (var == NULL)
	{
		pthread_mutex_unlock(&lua_mutex);
		return 0;
	}
	
	fwrite(&storage.at(idx), 1, size, var);
	fclose(var);
	pthread_mutex_unlock(&lua_mutex);
	return 1;	
}
//---------------------------------------------------------------------------------------------------------------------------
int storage_load(gplayer_imp* _this)
{
	if(!_this) return 0;
	int roleid = _this->GetPlayerID();	
	int idx = storage_get_roleid(roleid);
	pthread_mutex_lock(&lua_mutex);
	if(idx != -1) 
	storage.erase(storage.begin() + idx);
	
	char line[16]; 
	sprintf(line,"./var/%d",roleid);
	FILE *var = fopen(line, "a+b");	
	fseek(var , 0 , SEEK_END);
	size_t fsize = ftell(var); 
	rewind (var);
	char *src = (char*)malloc(fsize);
	if(src == NULL) 
	{
		fclose(var);
		pthread_mutex_unlock(&lua_mutex);
		return 0;
	}
	
	size_t fres = fread(src, 1, fsize, var);
	if(fres != fsize) 
	{
		fclose(var);
		free(src);
		pthread_mutex_unlock(&lua_mutex);
		return 0;
	}
	
	puts(src);			
	storage.push_back(STORAGE(_this,src,fsize));
	fclose(var);
	free(src);
	pthread_mutex_unlock(&lua_mutex);
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------
//--функции работы с вектором
//---------------------------------------------------------------------------------------------------------------------------
void BLACKHWID_clean()
{
	setup_fillmem(BLACKHWID,0x00,sizeof(BLACKHWID));
}
//---------------------------------------------------------------------------------------------------------------------------
void BLACKHWID_set(const char * hw)
{
	for (int i = 0; i < (__MAX_BLACKHWID_SIZE-1); i++)
	{
		if(BLACKHWID[i] == 0)
		{
			BLACKHWID[i] = atoll(hw);
			printf("BLACKHWID: hwid = %lld, pos = %d \n",BLACKHWID[i],i);
			BLACKHWID[++i] = 0;
			return;
		}
	}
}
//---------------------------------------------------------------------------------------------------------------------------
int gplayer_imp::CheckBanList() 
{
	int64_t hw = storage_get_roleid_hwid(GetPlayerID());
	for (int i = 0; BLACKHWID[i] && i < __MAX_BLACKHWID_SIZE; i++)
	{
		if (hw == BLACKHWID[i])
		{
			SendDisconnect(Get_cs_index(), GetPlayerID(), Get_cs_sid(), 0);
			ReportCheater2Gacd(GetPlayerID(), 777, 0, 0);
			pthread_mutex_unlock(&lua_mutex);
			return printf("Player [%d] already banned by BlackList Checker! \n", GetPlayerID());
		}
	}
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------------
int PlayerEnterWorld(gplayer_imp* pImp, bool state)
{
	printf("Персонаж вошел в мир c ID %d \n", pImp->GetPlayerID());
	return pImp->PlaneEnterNotify(true);
}
//---------------------------------------------------------------------------------------------------------------------------
int hwid_server_enter(gplayer_imp* _this) // 1 можно, 0 нельзя
{
	if(!_this) return 1;
	int roleid = _this->GetPlayerID();
	int tag = GetWorldTag();
	
	for (unsigned int i = 0; hw_limiter[i].tag && i < HW_TAGS; i++ )
	{
		if(hw_limiter[i].tag == tag)
		{
			int idx = storage_get_roleid(roleid);
			int count_tag = storage_get_count_hwid(idx);
			if( idx == -1 || count_tag == -1 || count_tag > hw_limiter[i].limit ) 
			{
				A3DVECTOR pos;
				pos.x = 1290.0f;
				pos.y = 220.0f;
				pos.z = 1135.0f;
				LongJump(_this,&pos,1,0);
				printf("HWID_MASTER: roleid = %d, tag = %d, tag_limit > hwid.count \n",roleid,tag);
				return 0;
			}
		}
	}
	return 1;
}
//---------------------------------------------------------------------------------------------------------------------------




//---------------------------------------------------------------------------------------------------------------------------
//--Набор функций 
//---------------------------------------------------------------------------------------------------------------------------
int Login_GetEquipInventory(gplayer_imp *pImp)
{
	storage_open(pImp);
	return GetEquipInventory(pImp);
}
//---------------------------------------------------------------------------------------------------------------------------
int Save_GetEquipInventory(char *pImp)
{
	storage_save(pImp);
	return GetEquipInventory(pImp);
}
//---------------------------------------------------------------------------------------------------------------------------
void Load_RefreshEquipment(gplayer_imp *pImp)
{
	storage_load(pImp);
	hwid_server_enter(pImp);
	RefreshEquipment(pImp);
}
//---------------------------------------------------------------------------------------------------------------------------
void Destroy_RemovePlayer(char *pWorld, char *pObj)
{
	storage_destroy(get_roleid_pObj(pObj)); 
	RemovePlayer(pWorld,pObj);
}
//---------------------------------------------------------------------------------------------------------------------------
int PlayerKill(char *pObj, XID* killer)
{
	int id = killer->id;
	if( id >= 32 )
	{
		int idx = storage_get_roleid(id);
		if (idx != -1) 
			storage.at(idx).kill_player_count++;
	}
	return IsZombie(pObj);
}
//---------------------------------------------------------------------------------------------------------------------------
int MonsterKill(char *pObj, XID* killer)
{
	int id = killer->id;
	if( id >= 32 )
	{
		int idx = storage_get_roleid(id);
		if (idx != -1) 
			storage.at(idx).kill_monster_count++;
	}
	return IsZombie(pObj);
}
//---------------------------------------------------------------------------------------------------------------------------
int AddCounterProperty(char *pPlayer, char *wrapper)
{
	char *pImp = (char *)*((int *)pPlayer + 13);
	int id = get_roleid_pImp(pImp);
	int idx = storage_get_roleid(id);
	if (idx != -1)
	{
		packet_raw_wrapper__push_byte(wrapper, storage.at(idx).kill_monster_count);
		packet_raw_wrapper__push_byte(wrapper, storage.at(idx).kill_player_count); 
	}	
	return send_ls_msg_packet_raw_wrapper(pPlayer,wrapper);
}
//---------------------------------------------------------------------------------------------------------------------------
int DeadrakyCommandHandler(gplayer_controller *pCtrl, int cmd_type, unsigned char* buf, size_t size)
{
	if(!pCtrl && !buf) return 0;
	int roleid = pCtrl->GetImp()->GetPlayerID();
	
	printf("New Command Handler: roleid = %d, cmd = %d , size = %d \n", roleid, cmd_type, size);
	if(cmd_type == 711 && size == 10)
	{
		int idx = storage_get_roleid(roleid);
		if(idx == -1) return 0;
		int64_t hw = *(int64_t*)&buf[2];
		storage.at(idx).hwid = hw;
		lua_EventPlayerSetHwid(roleid,hw);
		pCtrl->GetImp()->CheckBanList();
		hwid_server_enter(pCtrl->GetImp());
	}
	
	return 0;
}
//---------------------------------------------------------------------------------------------------------------------------
//--патчинг функций
//---------------------------------------------------------------------------------------------------------------------------
void OnStoragePatch()
{
	storage.clear();
	storage.reserve(1000);
	//pthread_mutex_init(&storage_mutex,0);
	setup_void(0x095E0BF7,DeadrakyCommandHandler);
	setup_call(0x081DC852,Login_GetEquipInventory);	//hook_ivent_login
	setup_call(0x081DE280,Save_GetEquipInventory);	//hook_user_save_data
	setup_call(0x0809F6FF,Load_RefreshEquipment);	//enter_server
	setup_call(0x08096D2E,Destroy_RemovePlayer);	//gplayer_imp::Logout
	setup_call(0x081607B9,Destroy_RemovePlayer);	//gplayer_controller::Release
	setup_call(0x082624D0,Destroy_RemovePlayer);	//instance_world_manager::InstanceSwitch
	setup_call(0x082785C9,Destroy_RemovePlayer);	//parallel_world_manager::PlayerSwitchWorld
	setup_copymem(0x0808F594,"\xFF\x75\x0C",3);		//счётчик убитых игроков
	setup_copymem(0x0808F5A2,"\x83\xC4\x08",3);
	setup_call(0x0808F59D,PlayerKill);
	setup_copymem(0x080FDCDD,"\xFF\x75\x0C",3);		//счётчик убитых монстров
	setup_copymem(0x080FDCEB,"\x83\xC4\x08",3);
	setup_call(0x080FDCE6,MonsterKill);
	setup_call(0x095E07C9,AddCounterProperty);	//get_self_property
	setup_call(0x0807D652, PlayerEnterWorld);
	return;
}
//---------------------------------------------------------------------------------------------------------------------------

