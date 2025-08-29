--LUA SCRIPT--

--======================================================================================
--Глобальные переменные
--======================================================================================

lua_idx					= 6660 -- уникальный индекс
pwskill_mod136 			= 0 -- использовать скиллы версии 136

Rate					= 0x08D6F89C -- Таблица рейтов (float ) -- 6 рейтов
Balance					= 0x095E7B80 -- Таблица баланса (480h) -- 11 классов(float,float[5])
FirsRun					= 0x095E8000 -- Таблица инкаст/перекаст(60h) -- 11 классов(int,int)
Incast					= 0x095E8060 -- Таблица уменьшения каста(30h) -- 11 классов(int)
IncastSkill				= 0x095E8090 -- Таблица отдельных скиллов(370h) -- 110 скиллов(int,int)
IncastCooldown			= 0x095E8400 -- Таблица задержки скиллов(50h) -- 10 куллдаунов(int,int)
BugBless				= 0x095E8450 -- Таблица включения баг скиллов по классам(30h) -- 11 классов(int)
BugBlessSkill			= 0x095E8480 -- Таблица отдельных баг скиллов(380h) -- 112 скиллов(int,int)
Swap					= 0x095E8800 -- Таблица свапа шмоток в бою(80h) -- 32 слота(int)
SwapCooldown			= 0x095E8880 -- Таблица задержки свапа шмоток(50h) -- 10 куллдаунов(int,int)
AutoSwapCooldown		= 0x095E88D0 -- Таблица задержки автосвапа шмоток(50h) -- 10 куллдаунов(int,int)
AutoSwap				= 0x095E8920 -- Таблица слотов автосвапа(110h) -- 32 ячейки(int,int)
AttackSpeed				= 0x095E8A30 -- Таблица аспида с типами оружия(A0h) -- 20 тип, скорость  (int, int)
AttackSpeedGood			= 0x095E8AD0 -- Таблица рай аспида с типами оружия(A0h) -- 20 тип, скорость  (int, int)
AttackSpeedEvil			= 0x095E8B70 -- Таблица ад аспида с типами оружия(A0h) -- 20 тип, скорость  (int, int)
DistanceService			= 0x095E8C10 -- Таблица дистанционных сервисов(60) -- 24 сервиса(int)
g17Cooldown				= 0x095E8C70 -- Таблица щалержки бафов пушки(50h) -- 10 куллдаунов(int,int)
DistanceServiceWorld	= 0x095E8CC0 -- Таблица локаций в которых включены дистанционные сервисы(200h) -- 128 локаций (int)
PetSummon				= 0x095E8EC0 -- Таблица перепризыва питомца(10h) -- 4 значения -- 4 параметра (int)
VipPickupWorld			= 0x095E8ED0 -- Таблица локаций в которых недоступен вип сбор лута(200h) -- 128 локаций (int)
FreeAmuletWorld			= 0x095E90D0 -- Таблица локаций в которых хирки бесконечны(200h) -- 128 локаций (int)
FreeItems				= 0x095E92D0 -- Таблица неизсякаемых итемов (200h) -- 128 итемов(int)
DummyItems				= 0x095E94D0 -- Таблица кукол воскрешения (40h) -- 16 итемов (int)
ItemUseFunctions		= 0x095E9510 -- Таблица функций при использовании итемов (180h) -- 32 функции (int,offt,int)
SpeekerItems			= 0x095E9690 -- Таблица рупоров (40h) -- 16 итемов (int)
Speeker2Items			= 0x095E96D0 -- Таблица горнов (40h) -- 16 итемов (int)
FreeAmulet				= 0x095E9710 -- Таблица бесконечных хирок (40h) -- 16 итемов (int)
ItemDistableWorld		= 0x095E9750 -- Таблица локаций в которых не работают джинны (200h) -- 128 локаций (int)
OfflineCats				= 0x095E9950 -- Таблица итемов для оффлайн котов (40h) -- 16 итемов (int)


--======================================================================================
--Переменные получаемые из программы
--======================================================================================

hw_limiter				= 0x0 -- Тоблица ограничения окон в локациях


--======================================================================================
--функции которые можно использовать в луа
--======================================================================================

--void game__BroadcastChat(int roleid, char channel, const char * src)
--int game__GetWorldTag()
--int game__GetWorldIndex()
--void game__SetBlackHwid(const char hw)
--void game__ClearBlackHwid()

--======================================================================================
--Математические функции
--======================================================================================

-- Получить время суток
function get_time_dey()
	return int(os.time() / 86400)
end

function strtoint(inputstr)
        if inputstr == nil then
			return 0
        end
		return tonumber(inputstr)
end

-- Конвертировать текст в хекс
function string.fromhex(str)
    return (str:gsub('..', function (cc)
        return string.char(tonumber(cc, 16))
    end))
end

-- конвертировать хекс в текст
function string.tohex(str)
    return (str:gsub('.', function (c)
        return string.format('%02X', string.byte(c))
    end))
end

-- Конвертировать число в int
function int(numb)
	return math.floor(numb)
end

-- получить дату и время
function mydata()
	return os.date("%d/%m/%Y %H:%M:%S")
end

-- Запись в лог файл
function mylogfunc(text)
	local outstr = mydata().." ["..game__GetWorldTag().."] "..text.."\n"
	local file = io.open("lualog.txt", "a")
	file:write(outstr)
	file:close()
	io.write(outstr)
end

-- фан чатик
function funnytext (message)
str = message
as = {'а', 'о', 'е', 'ы', 'ё', 'э'}
whereat = {'у', 'а', 'ы', 'а', 'о', 'е'}
if #as == #whereat then
    for i=1,#as do
        str = str:gsub(as[i], whereat[i])
    end
end
	return str

end

-- разбить чатик на слова
function mysplit(inputstr, sep)
        if sep == nil then
                sep = "%s"
        end
        local t={} ; i=1
        for str in string.gmatch(inputstr, "([^"..sep.."]+)") do
                t[i] = str
                i = i + 1
        end
        return t
end

-- проверить таблицу на верный итем
function check_true_item(item , items)

	if items[item] == nil then
		return 0
	end
	return items[item]

end

--======================================================================================
--===============================[Функции патчинга]=====================================
--======================================================================================

--Патчинг таблицы из 1 чара
function CharTable(pushd, value)

	game__PatchGS(pushd,"char",value)
	pushd = pushd + 1
	return pushd
end

--Патчинг таблицы из 1 чара
function ShortTable(pushd, value)

	game__PatchGS(pushd,"short",value)
	pushd = pushd + 2
	return pushd
end

--Патчинг таблицы из 1 инта
function IntTable(pushd, value)

	game__PatchGS(pushd,"int",value)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 1 флоата
function FloatTable(pushd, value)

	game__PatchGS(pushd,"float",value)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 2х интов
function IntIntTable(pushd, value1, value2)

	game__PatchGS(pushd,"int",value1)
	pushd = pushd + 4
	game__PatchGS(pushd,"int",value2)
	pushd = pushd + 4
	return pushd
end

--Патчинг таблицы из 2х флоатов
function FloatFloatTable(pushd, value1, value2)

	game__PatchGS(pushd,"float",value1)
	pushd = pushd + 4
	game__PatchGS(pushd,"float",value2)
	pushd = pushd + 4
	return pushd
end

-- XID++
function HashIDX()
	lua_idx = lua_idx+1
	return lua_idx
end

--======================================================================================
--Серверные функции
--======================================================================================

--Редактор баланса между классами
function LUA_BALANCE_EDITOR_PATCHING()

	local xid_table = 96
	local buff = Balance
	local pushd = 0 -- float buff[4*2*12];
	--[CLS::0]--------------[Дамаг вара]-----------------------
	pushd = buff + xid_table * 0   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::1]--------------[Дамаг мага]-----------------------
	pushd = buff + xid_table * 1   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::2]--------------[Дамаг шамана]-----------------------
	pushd = buff + xid_table * 2   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::3]--------------[Дамаг друида]---------------------
	pushd = buff + xid_table * 3   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::4]--------------[Дамаг оборотня]-------------------
	pushd = buff + xid_table * 4   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::5]--------------[Дамаг убийцы]-----------------------
	pushd = buff + xid_table * 5   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::6]--------------[Дамаг лучника]--------------------
	pushd = buff + xid_table * 6   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::7]--------------[Дамаг жреца]----------------------
	pushd = buff + xid_table * 7   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу
	--[CLS::8]--------------[Дамаг стража]-----------------------
	pushd = buff + xid_table * 8   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	
	--[CLS::9]--------------[Дамаг мистика]-----------------------
	pushd = buff + xid_table * 9   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	
	--[CLS::10]--------------[Дамаг призрака]-----------------------
	pushd = buff + xid_table * 10   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	
	--[CLS::11]--------------[Дамаг жнеца]-----------------------
	pushd = buff + xid_table * 11   --(физ, маг) --
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По вару
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По магу							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По шаману						  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По друиду
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По оборотню							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По сину							  
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По лучнику
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По присту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По стражу
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По мисту
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По призраку
	pushd = FloatFloatTable(pushd,0.0,0.0) -- По жнецу	

	mylogfunc("BALANCE_EDITOR_PATCHING: --OK-- ")
	return 0
end

--======================================================================================

--Редактор инкаста
function LUA_INCAST_EDITOR()
	
	local pushd = 0

	--Редактор инкаста и перекаста для каждого класса
	pushd = FirsRun --Incast::FirstRun(инкаст, перекаст)
	pushd = IntIntTable(pushd,99,90) --CLS 0 ; вар
	pushd = IntIntTable(pushd,99,90) --CLS 1 ; маг
	pushd = IntIntTable(pushd,99,90) --CLS 2 ; шаман
	pushd = IntIntTable(pushd,99,90) --CLS 3 ; друид
	pushd = IntIntTable(pushd,99,90) --CLS 4 ; обор
	pushd = IntIntTable(pushd,99,90) --CLS 5 ; син
	pushd = IntIntTable(pushd,99,90) --CLS 6 ; лучник
	pushd = IntIntTable(pushd,99,90) --CLS 7 ; жрец
	pushd = IntIntTable(pushd,99,90) --CLS 8 ; страж
	pushd = IntIntTable(pushd,99,90) --CLS 9 ; мистик

	--Редактор всех скиллов глобально для каждого класса при 99 пения
	pushd = Incast --Incast::Editor(Ускорение пения от 0 до 32(0 - стандарт, 32+ инкаст как на 136))
	pushd = IntTable(pushd,0 ) --CLS 0 ; вар
	pushd = IntTable(pushd,0 ) --CLS 1 ; маг
	pushd = IntTable(pushd,0 ) --CLS 2 ; шаман
	pushd = IntTable(pushd,0 ) --CLS 3 ; друид
	pushd = IntTable(pushd,0 ) --CLS 4 ; обор
	pushd = IntTable(pushd,0 ) --CLS 5 ; син
	pushd = IntTable(pushd,0 ) --CLS 6 ; лучник
	pushd = IntTable(pushd,0 ) --CLS 7 ; жрец
	pushd = IntTable(pushd,0 ) --CLS 8 ; страж
	pushd = IntTable(pushd,0 ) --CLS 9 ; мистик

	--Редактор инкаста отдельных скиллов при -99 пения
	pushd = IncastSkill --Skill::IncastTable(Ид скилла, Ускорение пения от 0 до 32(0 - стандарт, 32+ инкаст как на 136))
	pushd = IntIntTable(pushd,99 ,0) --Маг: Сила гор
	pushd = IntIntTable(pushd,484,0) --Маг:Сила гор светлый
	pushd = IntIntTable(pushd,485,0) --Маг: Сила гор темный

	--Защита от кликеров
	pushd = IncastCooldown --Skill::LockTimer
	pushd = IntIntTable(pushd, lua_idx, 400) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 300) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 200) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 100) HashIDX()

	mylogfunc("Patching incast OK")
	return 0
end

--======================================================================================

--Редактор баг скиллов 
function LUA_BUG_SKILL_EDITOR()

	local pushd = 0

	--Редактор всех скиллов глобально для каждого класса
	pushd = BugBless --BugSkill::Editor(0 выключить - 1 включить)
	pushd = IntTable(pushd,0) --CLS == 0 ; вар
	pushd = IntTable(pushd,0) --CLS == 1 ; маг
	pushd = IntTable(pushd,0) --CLS == 2 ; шаман
	pushd = IntTable(pushd,0) --CLS == 3 ; друид
	pushd = IntTable(pushd,0) --CLS == 4 ; обор
	pushd = IntTable(pushd,0) --CLS == 5 ; син
	pushd = IntTable(pushd,0) --CLS == 6 ; лучник
	pushd = IntTable(pushd,0) --CLS == 7 ; жрец
	pushd = IntTable(pushd,0) --CLS == 8 ; страж
	pushd = IntTable(pushd,0) --CLS == 9 ; мистик

	--Редактор отдельных скиллов
	pushd = BugBlessSkill --BugSkill::Table(Ид скилла, 0 выключить - 1 включить)
	pushd = IntIntTable(pushd,58  ,0) -- Вар: парящий дракон
	pushd = IntIntTable(pushd,59  ,0) -- Вар: прыжок тигра
	pushd = IntIntTable(pushd,100 ,0) -- Маг: сдвиг земли
	pushd = IntIntTable(pushd,478 ,0) -- Маг: сдвиг земли светлый
	pushd = IntIntTable(pushd,479 ,0) -- Маг: сдвиг земли темный

	mylogfunc("Patching bug_skill OK")
	return 0
end

--======================================================================================

function LUA_SWAP_ITEM_EDITOR()

	local pushd = 0
	local swap_item = 64944 --ID предмета для автосвапа
	
	IntTable(0x095E033A,swap_item)
	IntTable(0x095E9528,swap_item)
	
	-- Список позиций (из PWA) снаряжений которые нельзя использовать в бою
	-- 0 - можно, 1 - нельзя(джинн), 2 нельзя вообще(хирки)
	pushd = Swap
	pushd = IntTable(pushd,0) -- оружие
	pushd = IntTable(pushd,0) -- шлем
	pushd = IntTable(pushd,0) -- ожирелье
	pushd = IntTable(pushd,0) -- накидка
	pushd = IntTable(pushd,0) -- броня
	pushd = IntTable(pushd,0) -- пояс
	pushd = IntTable(pushd,0) -- штаны
	pushd = IntTable(pushd,0) -- сапоги
	pushd = IntTable(pushd,0) -- наручи
	pushd = IntTable(pushd,0) -- кольцо 1
	pushd = IntTable(pushd,0) -- кольцо 2
	pushd = IntTable(pushd,0) -- стрелы
	pushd = IntTable(pushd,0) -- полёт
	pushd = IntTable(pushd,0) -- стиль куртка
	pushd = IntTable(pushd,0) -- стиль штаны
	pushd = IntTable(pushd,0) -- стиль сапоги
	pushd = IntTable(pushd,0) -- стиль перчатки
	pushd = IntTable(pushd,0) -- соски на атаку
	pushd = IntTable(pushd,0) -- трактат
	pushd = IntTable(pushd,0) -- смайлы
	pushd = IntTable(pushd,0) -- хирка на жс
	pushd = IntTable(pushd,0) -- хирка на ману
	pushd = IntTable(pushd,0) -- цитатник
	pushd = IntTable(pushd,1) -- джинн
	pushd = IntTable(pushd,0) -- торговая лавка
	pushd = IntTable(pushd,0) -- стиль шапка
	pushd = IntTable(pushd,0) -- грамата альянса
	pushd = IntTable(pushd,0) -- печать воителя 1
	pushd = IntTable(pushd,0) -- печать воителя 2
	pushd = IntTable(pushd,0) -- стиль пуха
	pushd = IntTable(pushd,0) -- ???
	pushd = IntTable(pushd,0) -- ???
	pushd = IntTable(pushd,0) -- ???	

	--Таблица задержки от флуда на свап (защита от стороннего свапа)
	pushd = SwapCooldown
	pushd = IntIntTable(pushd, lua_idx, 800) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 600) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 400) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 200) HashIDX()

	--Таблица слотов автосвапа (110h) -- 32 ячейки(int, int)
	pushd = AutoSwap
	pushd = IntTable(pushd,5)
	pushd = IntIntTable(pushd, 0, 0)   -- оружие
	pushd = IntIntTable(pushd, 2, 9)   -- левое кольцо
	pushd = IntIntTable(pushd, 3, 2)   -- ожерелье
	pushd = IntIntTable(pushd, 4, 5)   -- пояс
	pushd = IntIntTable(pushd, 5, 4)   -- броня

	--Таблица задержки от флуда на автосвап
	pushd = AutoSwapCooldown
	pushd = IntIntTable(pushd, lua_idx, 4000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 3000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 2000) HashIDX()
	pushd = IntIntTable(pushd, lua_idx, 1000) HashIDX()

mylogfunc("swap_editor OK")
return 0
end

--======================================================================================

--Редактор скорости автоатаки с различной культивацией и разными типами оружия
function LUA_ATTACK_SPEED_EDITOR()

	local pushd = 0

	-- Скорость атаки для культивации 0 - 8 пример: (4 = 5.00 ; 5 = 4.00 ; 6 = 3.33) и далее по аналогии
	pushd = AttackSpeed --AttackSpeed::Editor(Тип оружия, скорость атаки)
	pushd = IntIntTable(pushd,1,    4) -- мечи 
	pushd = IntIntTable(pushd,5,    4) -- копья 
	pushd = IntIntTable(pushd,9,    4) -- топоры 
	pushd = IntIntTable(pushd,13,   4) -- дальнобойное 
	pushd = IntIntTable(pushd,182,  4) -- кастеты 
	pushd = IntIntTable(pushd,291,  4) -- бичи 
	pushd = IntIntTable(pushd,292,  4) -- магическое оружие 
	pushd = IntIntTable(pushd,23749,4) -- кинжалы 
	pushd = IntIntTable(pushd,25333,4) -- сферы 
	pushd = IntIntTable(pushd,44878,4) -- Сабля
	pushd = IntIntTable(pushd,44879,4) -- Коса
	pushd = IntIntTable(pushd,59830,4) -- Щит
	pushd = IntIntTable(pushd,59831,4) -- Пушка

	-- Скорость атаки для культивации 20 - 22 пример: (4 = 5.00 ; 5 = 4.00 ; 6 = 3.33) и далее по аналогии
	pushd = AttackSpeedGood --AttackSpeed::Editor(Тип оружия, скорость атаки)
	pushd = IntIntTable(pushd,1,    4) -- мечи 
	pushd = IntIntTable(pushd,5,    4) -- копья 
	pushd = IntIntTable(pushd,9,    4) -- топоры 
	pushd = IntIntTable(pushd,13,   4) -- дальнобойное 
	pushd = IntIntTable(pushd,182,  4) -- кастеты 
	pushd = IntIntTable(pushd,291,  4) -- бичи 
	pushd = IntIntTable(pushd,292,  4) -- магическое оружие 
	pushd = IntIntTable(pushd,23749,4) -- кинжалы 
	pushd = IntIntTable(pushd,25333,4) -- сферы 
	pushd = IntIntTable(pushd,44878,4) -- Сабля
	pushd = IntIntTable(pushd,44879,4) -- Коса
	pushd = IntIntTable(pushd,59830,4) -- Щит
	pushd = IntIntTable(pushd,59831,4) -- Пушка

	-- Скороcть атаки для культивации 30 - 32 пример: (4 = 5.00 ; 5 = 4.00 ; 6 = 3.33) и далее по аналогии
	pushd = AttackSpeedEvil --AttackSpeed::Editor(Тип оружия, скорость атаки)
	pushd = IntIntTable(pushd,1,    4) -- мечи 
	pushd = IntIntTable(pushd,5,    4) -- копья 
	pushd = IntIntTable(pushd,9,    4) -- топоры 
	pushd = IntIntTable(pushd,13,   4) -- дальнобойное 
	pushd = IntIntTable(pushd,182,  4) -- кастеты 
	pushd = IntIntTable(pushd,291,  4) -- бичи 
	pushd = IntIntTable(pushd,292,  4) -- магическое оружие 
	pushd = IntIntTable(pushd,23749,4) -- кинжалы 
	pushd = IntIntTable(pushd,25333,4) -- сферы 
	pushd = IntIntTable(pushd,44878,4) -- Сабля
	pushd = IntIntTable(pushd,44879,4) -- Коса
	pushd = IntIntTable(pushd,59830,4) -- Щит
	pushd = IntIntTable(pushd,59831,4) -- Пушка

	mylogfunc("Patching attack_speed OK")
	return 0
end

--======================================================================================

--Редактор дистанционных сервисов
function LUA_DISTANCE_SERVICE_TYPE()

	local pushd = 0
	pushd = DistanceService
	
	--pushd = IntTable(pushd,1 ) --покупка итемов(другой обработчик)
	pushd = IntTable(pushd,2 ) --продажа итемов	
	pushd = IntTable(pushd,3 ) --починка итемов
	pushd = IntTable(pushd,9 ) --изучение скиллов
	pushd = IntTable(pushd,35) --заточка снаряжения
	pushd = IntTable(pushd,10) --вплавка камней
	pushd = IntTable(pushd,11) --очистка снаряжения
	pushd = IntTable(pushd,47) --создание ячеек
	pushd = IntTable(pushd,14) --пароль от банка
	pushd = IntTable(pushd,15) --банк
	pushd = IntTable(pushd,25) --почта
	pushd = IntTable(pushd,28) --инкубация петов
	pushd = IntTable(pushd,29) --восстановление яиц петов
	--pushd = IntTable(pushd,36) --сменить имя питомца
	pushd = IntTable(pushd,69) --дистанционная гравировка

	pushd = IntTable(pushd,0) --последний элемент массива
	mylogfunc("LUA_DISTANCE_SERVICE_TYPE OK!")
	return 1
end

--======================================================================================

--локации в которых работают дистанционные сервисы
function LUA_DISTANCE_SERVICE_TAG()

	local pushd = 0
	pushd = DistanceServiceWorld

	pushd = IntTable(pushd,1  )	--[PvE] Мир
	pushd = IntTable(pushd,121)	--[PvE] Рай
	pushd = IntTable(pushd,122)	--[PvE] Ад
	pushd = IntTable(pushd,133)	--[PvE] Прошлое
	pushd = IntTable(pushd,135)	--[PvE] База гильдии
	pushd = IntTable(pushd,137)	--[PvE] Морай
	pushd = IntTable(pushd,161)	--[???] переправа душ 152+
	pushd = IntTable(pushd,162)	--[???] переправа душ 151+
	pushd = IntTable(pushd,168)	--[PvP] Таинственный мир
	pushd = IntTable(pushd,198)	--[PvE] Персиковая обитель
	
	pushd = IntTable(pushd,0) --последний элемент массива
	mylogfunc("LUA_DISTANCE_SERVICE_TAG OK!")
	return 1
end

--======================================================================================

--редактор ограничения окон по локациям
function LUA_HWID_TAG_LIMITER()

	local pushd = 0
	pushd = hw_limiter
	
	pushd = IntIntTable(pushd,128,6) -- Долина бездушия ( Гуй )
	pushd = IntIntTable(pushd,143,1) -- Зал пяти императоров ( Основная локация Битвы династий )
	pushd = IntIntTable(pushd,144,1) -- Поле боя Битвы династий "Захват флага"
	pushd = IntIntTable(pushd,145,1) -- Поле боя Битвы династий "Бой за кристаллы"
	pushd = IntIntTable(pushd,146,1) -- Поле боя Битвы династий "Битва на мосту"
	pushd = IntIntTable(pushd,147,1) -- Долина заката ( Лока для ивента "Битва катапульт" )
--	pushd = IntIntTable(pushd,111,2) -- Долина расхитителей небес ( Данж: 59)
--	pushd = IntIntTable(pushd,114,2) -- Врата беспокойных духов ( Данж: 69 )
--	pushd = IntIntTable(pushd,115,2) -- Пещера драгоценностей ( Данж: 79 )
--	pushd = IntIntTable(pushd,116,2) -- Небо иллюзий ( Данж: 89 - Рай )
--	pushd = IntIntTable(pushd,117,2) -- Небо наваждений ( Данж: 89 - Ад )
--	pushd = IntIntTable(pushd,121,2) -- Земли небожителей ( Основная локация - Рай )
--	pushd = IntIntTable(pushd,122,2) -- Земли магов и демонов ( Основная локация - Ад )
--	pushd = IntIntTable(pushd,123,2) -- Чистилище ( Данж: 99 - Рай )
--	pushd = IntIntTable(pushd,124,2) -- Земной ад ( Данж: 99 - Ад )
--	pushd = IntIntTable(pushd,125,2) -- Сумеречный город ( Данж: 109 - Рай )
--	pushd = IntIntTable(pushd,126,2) -- Обитель мятежников ( Данж: 109 - Ад )
--	pushd = IntIntTable(pushd,129,2) -- Город инея ( Данж: Иней )
--	pushd = IntIntTable(pushd,131,2) -- Сумеречный храм ( Данж: ХХ )
--	pushd = IntIntTable(pushd,127,2) -- Долина священной луны ( Данж: Луна )
--	pushd = IntIntTable(pushd,101,1) -- Ивент: Город темных зверей
--	pushd = IntIntTable(pushd,118,1) -- Ивент: Дворец царя драконов
--	pushd = IntIntTable(pushd,201,1) -- Ивент: Асурсы
--	pushd = IntIntTable(pushd,204,1) -- Ивент: Арена города драконов
--	pushd = IntIntTable(pushd,135,2) -- База гильдии ( Клан Холл )
--	pushd = IntIntTable(pushd,139,2) -- Пещеры вечности ( Низ )
--	pushd = IntIntTable(pushd,141,2) -- Пещеры вечности ( Верх )		
	
	pushd = IntIntTable(pushd,0  ,0) -- Последний Элемент Массива
	mylogfunc("LUA_HWID_TAG_LIMITER OK!")
	return 0
end

--======================================================================================

function LUA_BLACKLIST_EDITOR()

	game__ClearBlackHwid()
	game__SetBlackHwid("42945378002703")
	mylogfunc("ADD_BLACK_HWID: --OK-- ")

end

--======================================================================================

function LUA_OTHER_EDITOR()

	local pushd = 0

	--дебаг пароль
	IntTable(0x095E0B7C,6795)

	--количество человек в группе
	local team_max_members = 9
	CharTable(0x0818831B,team_max_members)
	CharTable(0x08187860,team_max_members)
	CharTable(0x081876C3,team_max_members)
	CharTable(0x08186E95,team_max_members)

	--Перезарядка Руны переноса
	IntTable(0x082ED42B,5000) --Время в мс

	--Синий ник
	CharTable(0x0809F460, 29)
	CharTable(0x080A0A4B, 29)
		
	--Максимальная сила духа шамана
	--IntTable(0x095E0A1A,0)
	--IntTable(0x095E0A21,0)
	
	--Сила духа
	--IntTable(0x095E1FEC,1) --ограничивать - 1 да , 0 нет
	--IntTable(0x095E1FF0,0) --максимальная сила духа
	
	--Боевой дух
	IntTable(0x095E1EE4,1) --ограничивать - 1 да , 0 нет
	IntTable(0x095E1EE8,0) --максимальный боевой дух
	
	--Требовать убрать пета
	IntTable(0x095E8EC0,0) --1 да; 0 нет
	
	--Меридианы
	IntTable(0x095E1FB0,9999) --количество попыток в день 
	IntTable(0x095E1FB4,9999) --максимальное количество попыток
		
	--Удалить меридианы
	--ShortTable(0x0821951D,0x9090)
	--ShortTable(0x0821928D,0x9090)
	
	--Убрать вход в пати на бд
	ShortTable(0x080BB0A0,0x9090)
	
	--Удалить календарь
	--CharTable(0x080C393C,0xC3)
	--CharTable(0x080C3984,0xC3)	
	
	--Время выхода из фракции
	IntTable(0x080B7506,60) --1 раз
	IntTable(0x080B7524,60) --последующие
	
	--удалить vip сервисы
	--IntTable(0x080CA390,2210644017) --проверка всегда возвращает 0
	
	--Удалить замочек
	--IntTable(0x08061EF2,12828721)
	
	--Удалить бонус удачи
	CharTable(0x0808D37A,0xC3)
	CharTable(0x0808D3FE,0xC3)
	FloatTable(0x08D54DD4,1.0)
	CharTable(0x080FE132,0xEB)
			
	--Сколько чи давать за медитацию
	IntTable(0x095E0A95,30)
	
	--Сколько времени не работает руна переноса после выкапывания шахты
	IntTable(0x095E08D2,1000)

	--Исправить питомцев на кочках
	IntTable(0x083A1CB5,1)
	
	--Масс сбор лута
	--IntTable(0x095E1F20,0) --0 по вип статусу, 1 по итему
	--IntTable(0x095E1F24,60000) --ид итема

	
	local elflvlup_item = 64947 --ID предмета для джинокача	
	IntTable(0x095E9510,elflvlup_item)
	IntTable(0x095E168A,elflvlup_item)

	-- задержка между бафами оружия 155+
	IntIntTable(g17Cooldown, lua_idx, 30000) HashIDX() --милисекунд задержки
	
	--Рейты
	pushd = Rate
	pushd = FloatTable(pushd,10.0) --опыт
	pushd = FloatTable(pushd,10.0) --дух
	pushd = FloatTable(pushd,1.0) --дроп
	pushd = FloatTable(pushd,5.0) --деньги
	pushd = FloatTable(pushd,10.0) --кв опыт
	pushd = FloatTable(pushd,10.0) --кв дух
	pushd = FloatTable(pushd,5.0) --кв деньги	
	
	--Локации в которых выключен масс сбор лута
	pushd = VipPickupWorld
	pushd = IntTable(pushd,201)	--ГМ Арена -- Асуры

	--Таблица локаций в которых хирки бесконечны
	pushd = FreeAmuletWorld
	pushd = IntTable(pushd,143)	-- a43 - Зал пяти императоров(Основная локация Битвы династий)
	pushd = IntTable(pushd,144) -- a44 - Поле боя Битвы династий "Захват флага"
	pushd = IntTable(pushd,145) -- a45 - Поле боя Битвы династий "Бой за кристаллы"
	pushd = IntTable(pushd,146) -- a46 - Поле боя Битвы династий "Битва на мосту"
	pushd = IntTable(pushd,147) -- a47 - Битва катапульт
	
	--Итемы которые не тратяться при использовании
	pushd = FreeItems
	pushd = IntTable(pushd,59410) -- неиссякаемая руна переноса
	pushd = IntTable(pushd,64946) -- неиссякаемая карта жизни
	pushd = IntTable(pushd,64950) -- неиссякаемый рупор
	pushd = IntTable(pushd,64951) -- неиссякаемый горн

	--Итемы - карты жизни
	pushd = DummyItems
	pushd = IntTable(pushd,64946)
	pushd = IntTable(pushd,31878)
	pushd = IntTable(pushd,12361)
	pushd = IntTable(pushd,36309)
	
	--Итемы - рупоры
	pushd = SpeekerItems
	pushd = IntTable(pushd,64950)
	pushd = IntTable(pushd,12979)
	pushd = IntTable(pushd,36092)

	--Итемы - горны
	pushd = Speeker2Items
	pushd = IntTable(pushd,64951)
	pushd = IntTable(pushd,27728)
	pushd = IntTable(pushd,27729)
	
	--бесконечные хирки
	pushd = FreeAmulet
	pushd = IntTable(pushd,64952) --неиссякаемая хирка ЖС
	pushd = IntTable(pushd,64953) --неиссякаемая хирка МЭ

	--Итемы - торговые монеты для оффлайн котов
	pushd = OfflineCats
	pushd = IntTable(pushd,65532)
	pushd = IntTable(pushd,65533)
	
	mylogfunc("LUA_OTHER_EDITOR: --OK-- ")
end

--======================================================================================
--IVENTS & FUNC
--======================================================================================

-- Релог Lua файла 
function EventOnReloadScript()

	LUA_BALANCE_EDITOR_PATCHING()
	LUA_INCAST_EDITOR()
	LUA_BUG_SKILL_EDITOR()
	LUA_SWAP_ITEM_EDITOR()
	LUA_ATTACK_SPEED_EDITOR()
	LUA_DISTANCE_SERVICE_TYPE()
	LUA_DISTANCE_SERVICE_TAG()
	LUA_HWID_TAG_LIMITER()
	LUA_BLACKLIST_EDITOR()
	LUA_OTHER_EDITOR()
	mylogfunc("EventOnReloadScript: --OK-- ")

end

--======================================================================================

-- Патчинг при запуске GS 
function EventOnBeforeStartGS()

	LUA_BALANCE_EDITOR_PATCHING()
	LUA_INCAST_EDITOR()
	LUA_BUG_SKILL_EDITOR()
	LUA_SWAP_ITEM_EDITOR()
	LUA_ATTACK_SPEED_EDITOR()
	LUA_DISTANCE_SERVICE_TYPE()
	LUA_DISTANCE_SERVICE_TAG()
	LUA_HWID_TAG_LIMITER()
	LUA_BLACKLIST_EDITOR()
	LUA_OTHER_EDITOR()
	mylogfunc("EventOnBeforeStartGS: --OK-- ")

end

--======================================================================================

-- Патчинг после полной загрузки GS
function EventOnInitWorld()

	local pushd = 0
	local world_tag = game__GetWorldTag() -- получить ид локации
	
	if world_tag == 131 then -- устанавливаем свои рейты в ХХ(is31 tag 131) (2 дроп)
		
		pushd = Rate
		pushd = FloatTable(pushd,10.0) --опыт
		pushd = FloatTable(pushd,10.0) --дух
		pushd = FloatTable(pushd,2.0) --дроп
		pushd = FloatTable(pushd,5.0) --деньги
		pushd = FloatTable(pushd,10.0) --кв опыт
		pushd = FloatTable(pushd,10.0) --кв дух
		pushd = FloatTable(pushd,5.0) --кв деньги
		
	end

	mylogfunc("EventOnInitWorld: --OK-- WorldTag = "..world_tag)

end

--======================================================================================

function EventPlayerSetHwid(roleid, hw)

	mylogfunc("EventOnBeforeStartGS: roleid = "..int(roleid)..", hwid = "..hw)
end







