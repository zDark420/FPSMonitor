#include "stdafx.h"
//[junk_enable 128 320 /]

//[enc_string_enable /]

string neg0 = "Aim Boat Disabled Off"; //save our plain ascii string
std::wstring nag0 = std::wstring(neg0.begin(), neg0.end()); //copy it to a wide string
const wchar_t* nig0 = nag0.c_str(); //convert wide string into wchar_t pointer

string neg1 = "Aim Boat Enabled On";
std::wstring nag1 = std::wstring(neg1.begin(), neg1.end());
const wchar_t* nig1 = nag1.c_str();

string neg2 = "Trigger Enabled On";
std::wstring nag2 = std::wstring(neg2.begin(), neg2.end());
const wchar_t* nig2 = nag2.c_str();

string neg3 = "Trigger Disabled Off";
std::wstring nag3 = std::wstring(neg3.begin(), neg3.end());
const wchar_t* nig3 = nag3.c_str();

const wchar_t* CarryTheZero[] = { nig0, nig1, nig2, nig3 }; //save our converted strings into an array to use in app.

//[swap_lines]
#define PUSH 0x50
#define POP  0x58
#define NOP  0x90
//[/swap_lines]
//[swap_lines]
#define JUNK1 __asm _emit PUSH 
#define JUNK2 __asm _emit NOP
#define JUNK3 __asm _emit NOP
#define JUNK4 __asm _emit NOP 
#define JUNK5 __asm _emit NOP 
#define JUNK6 __asm _emit NOP 
#define JUNK7 __asm _emit NOP
#define JUNK8 __asm _emit POP
//[/swap_lines]
#define JUNK JUNK1 JUNK2 JUNK3 JUNK4 JUNK5 JUNK6 JUNK7 JUNK8

#pragma region project

#pragma region thisthing

//these change with updates
#pragma region group1
//[swap_lines]
//DWORD DwGlow; //glowoffset
DWORD DwEL = 0x049EC244; //0x4A0F014;//m_dwEntityList
DWORD DwEP = 0x00559434; //0x55A434;//m_dwEnginePosition
DWORD DwLP = 0x00A4A9BC; //0x00a7094c; //m_dwLocalPlayer
DWORD DwVA = 0x00004CE0; //0x4CE0;//m_dwViewAngles
//[/swap_lines]
#pragma endregion 

//these normally don't
#pragma region group2
//[swap_lines]
const DWORD DwMBS = 0x0935;//m_bSpotted
const DWORD DwCI = 0x2400;//m_iCrossHairID
const DWORD DwVVO = 0x104;//m_vecViewOffset
const DWORD DwVO = 0x134;//m_vecOrigin
const DWORD DwVP = 0x13e8;//m_vecPunch
const DWORD DwTN = 0xF0;//m_iTeamNum = teamOffset
const DWORD DwSF = 0x1d60;//m_iShotsFired
const DWORD DwBM = 0xA78;//m_dwBoneMatrix
const DWORD DwES = 0x10;//entity size never changes = ENTLOOPDIST
const DWORD DwLS = 0x25B;//m_lifeState
const DWORD DwVV = 0x110;//m_vecVelocity
const DWORD DwoET = 0xF0; //offEntityTeam
//const DWORD teamOffset = 0xF0;
//[/swap_lines]
#pragma endregion

#pragma region group3 //other shit
//[swap_lines]


//Afrikaans for Trigger Button
int SnellerMaar = VK_DOWN;
//Afrikaans for Radar(vision) Button
int VisieMaar = VK_UP;


//Afrikaans for TargetProcess
HANDLE Teiken;
//DwClient
DWORD DwCl;
//DwEngine
DWORD DwEn;

//Afrikaans for kill
bool Doodmaak = false;

//Afrikaans for ThreadPaused
bool DraadGestop = false;

//Afrikaans for Trigger
bool Sneller= true;
//Afrikaans for Aim
bool Doel = false;

string aval = "OFF";
string tval = "ON";
string WinampSwitch="OFF";

//PitchMinPunch afrikaans for little
float pbietjie = 2.f;
//PitchMaxPunch afrikaans for lots
float pbaie = 2.f;
//YawMinPunch afrikaans for little
float ybietjie = 2.f;
//YawMaxPunch afrikaans for lots
float ybaie = 2.f;
//TargetBone
int tb = 10; //5 = neck/body to head - 10 is head.
//SmoothAmount
float sa = 10.f; //3.f default - 7 for smooth to head
//NumberOfPlayers
int nop = 32;

//[/swap_lines]
#pragma endregion

#pragma endregion
//[junk_disable /]
//[enc_string_disable /]
struct PModule {
	DWORD ba, si;
};
//[junk_enable 128 320 /]
//[enc_string_enable /]

int Californication(int x) {
	ISpVoice * pVoice = NULL;
	if (FAILED(::CoInitialize(NULL)))
	return FALSE;
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
		if( SUCCEEDED( hr ) )
		{

if (x == 0) { //aim off
			hr = pVoice->Speak(CarryTheZero[0], 0, NULL);
			pVoice->Release();
			pVoice = NULL;
			return 1;
} else if (x == 1) { //aim on
			hr = pVoice->Speak(CarryTheZero[1], 0, NULL);
			pVoice->Release();
			pVoice = NULL;
			return 1;
} else if (x == 2) {  //trigger on
			hr = pVoice->Speak(CarryTheZero[2], 0, NULL);
			pVoice->Release();
			pVoice = NULL;
			return 1;
		
} else if (x == 3) { //trigger off
			hr = pVoice->Speak(CarryTheZero[3], 0, NULL);
			pVoice->Release();
			pVoice = NULL;
			return 1;
			}
			else{
				return 1;
			//dirtywork
			}//end of if-else statement
		//pVoice->Release();
		//pVoice = NULL;
		::CoUninitialize();
		return 1;
}
return 1;
}
PModule meng, mcli;
struct 
{
	//Afrikaans for read (dword address,isarray,elementcount,srcdata)
	template <typename ReadType> ReadType Lees(DWORD Ad, bool iar = false, int ec = 1, ReadType sd = 0)
	{
		if (!iar)
		{
		  //ReadProcessMemory(hProce, (LPVOID)(Ad), &Data, sizeof(B), NULL);
			ReadType Data;JUNK;
			ReadProcessMemory(Teiken, (LPVOID)(Ad), &Data, sizeof(ReadType), NULL);JUNK;
			return Data;JUNK;
		}
		else if (iar)
		{
			ReadProcessMemory(Teiken, (LPVOID)(Ad), (ReadType*)sd, sizeof(ReadType)* ec, 0);JUNK;
			return NULL;JUNK;
		}
		return NULL;
	}

	//Afrikaans for write (dword address,writetype data, isarray, elementcount)
	template<typename WriteType> WriteType Skryf(DWORD Ad, WriteType Da, bool iar = false, int ec = 1)
	{
		if (!iar)
		{
		  //WriteProcessMemory(hProce, (LPVOID)(Ad), &Da, sizeof(B), NULL);
			WriteProcessMemory(Teiken, (LPVOID)(Ad), &Da, sizeof(WriteType)* ec, NULL);JUNK;
			return Da;JUNK;
		}
		else if (iar)
		{
			WriteProcessMemory(Teiken, (LPVOID)(Ad), (WriteType*)Da, sizeof(WriteType)* ec, NULL);JUNK;
			return NULL;JUNK;
		}
		return NULL;
	}
	
	//Afrikaans for Compare DataCompare
	bool Vergelyk(const BYTE* pD, const BYTE* pM, const char* pzM) {
		for (; *pzM; ++pzM, ++pD, ++pM) {
			if (*pzM == 'x' && *pD != *pM) {
				return false;JUNK;
			}
		}

		return (*pzM == NULL);JUNK;
	}


	//AfriKaans for FindPatternMultiple FindPatternARR(start,size,mask,count)
	DWORD VindPatroonVeelvuldige(DWORD st, DWORD sz, const char* ma, int co, ...) {
		char* si = new char[co + 1];JUNK;
		va_list ap;JUNK;
		va_start(ap, co);JUNK;
		for (int i = 0; i < co; i++) {
			char read = va_arg(ap, char);
			si[i] = read;JUNK;
		}
		va_end(ap);JUNK;
		si[co] = '\0';JUNK;

		return VindPatroon(st, sz, si, ma);JUNK;
	}


	//Afrikaans for FindPattern (start,size,sig,mask)
	DWORD VindPatroon(DWORD st, DWORD sz, const char* si, const char* ma) {
		BYTE* da = new BYTE[sz];JUNK;

		unsigned long bytesRead;JUNK;

		if (!ReadProcessMemory(Teiken, (LPVOID)st, da, sz, &bytesRead)) {
			return NULL;JUNK;
		}

		for (DWORD i = 0; i < sz; i++) {
			if (Vergelyk((const BYTE*)(da + i), (const BYTE*)si, ma)) {
				return st + i;JUNK;
			}
		}

		return NULL;
	}

}Geheue;//Afrikaans for Memory

//Afrikaans GetModuleHandleByName (ModuleName,Proccessid)
PModule KryMhanteerdeur(char* MN, DWORD PI)
{
	HANDLE module = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PI);JUNK;
	MODULEENTRY32 mEnt;JUNK;
	mEnt.dwSize = sizeof(mEnt);JUNK;
	do {
		if (!strcmp(mEnt.szModule, (LPSTR)MN)) {
			CloseHandle(module);JUNK;

			PModule mod;JUNK;
			mod.ba = (DWORD)mEnt.modBaseAddr;JUNK;
			mod.si = mEnt.modBaseSize;JUNK;
			return mod;JUNK;
		}
	} while (Module32Next(module, &mEnt));JUNK;

	CloseHandle(module);JUNK;

	PModule mode = { 0, 0 };JUNK;
	return mode;JUNK;
}
//Afrikaans for GetProccesshandleByName
HANDLE KryProseshanteerdeur(char* pn)
{
	PROCESSENTRY32 ENTRY;JUNK;
	ENTRY.dwSize = sizeof(PROCESSENTRY32);JUNK;
	HANDLE HSNAP = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);JUNK;
	if (Process32First(HSNAP, &ENTRY) == TRUE)
	{
		if (!strcmp(ENTRY.szExeFile, pn))
		{
			HANDLE HPROC = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ENTRY.th32ProcessID);JUNK;
			return HPROC;JUNK;
		}
		else
		{
			while (Process32Next(HSNAP, &ENTRY) == TRUE)
			{
				if (!strcmp(ENTRY.szExeFile, pn))
				{
					HANDLE HPROC = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ENTRY.th32ProcessID);JUNK;
					return HPROC;JUNK;
				}
			}
			return 0;JUNK;
		}
	}
	CloseHandle(HSNAP);JUNK;
}
#pragma endregion
struct
{
	//base entity
	DWORD BE(int PN)
	{
		return Geheue.Lees<DWORD>(DwCl + DwEL + (DwES * PN));JUNK;
	}

	//isdead
	bool ID(int PN)
	{
		DWORD DWBE = BE(PN);JUNK;
		if (DWBE)
		{
			return Geheue.Lees<bool>(DWBE + DwLS);JUNK;
		}
	}

	//GetTeam
	int GT(int PN)
	{
		DWORD DWBE = BE(PN);JUNK;
		if (DWBE)
		{
			return Geheue.Lees<int>(DWBE + DwTN);JUNK;
		}
	}
	//mbspotted
	int MBS(int PN)
	{
		DWORD DWBE = BE(PN);JUNK;
		if (DWBE)
		{
			return Geheue.Lees<int>(DWBE + DwMBS);JUNK;
		}
	}
	//getvelocity
	void GV(int PN, float* B)
	{
		DWORD DWBE = BE(PN);JUNK;
		if (DWBE)
		{
			Geheue.Lees<float*>(DWBE + DwVV, true, 3, B);JUNK;
		}
	}
	//GetBonePosition
	void GBP(int PN, float* BonePosition)
	{
		DWORD DWBE = BE(PN);JUNK;
		if (DWBE)
		{
			DWORD BM = Geheue.Lees<DWORD>(DWBE + DwBM);JUNK;
			if (BM)
			{
				Geheue.Lees<float*>(BM + 0x30 * tb + 0x0C, true, 1, &BonePosition[0]);JUNK;
				Geheue.Lees<float*>(BM + 0x30 * tb + 0x1C, true, 1, &BonePosition[1]);JUNK;
				Geheue.Lees<float*>(BM + 0x30 * tb + 0x2C, true, 1, &BonePosition[2]);JUNK;
			}
		}
	}
}EntiteitLys;//Afrikaans for EntityList
typedef unsigned long WEAPON_HANDLE;
struct
{	
	//Player Base
	DWORD PB()
	{
		return Geheue.Lees<DWORD>(DwCl + DwLP);JUNK;
	}
	
	//SetAngles
	void SA(float* Angles)
	{
		DWORD AnglePointer = Geheue.Lees<DWORD>(DwEn + DwEP);JUNK;
		if (AnglePointer)
		{
			Geheue.Skryf<float*>(AnglePointer + DwVA, Angles, true, 3);JUNK;
		}
	}

	//getteam
	int GT()
	{
		DWORD DWPB = PB();JUNK;
		if (DWPB)
		{
			return Geheue.Lees<int>(DWPB + DwTN);JUNK;
		}
	}


	//GetVelocity
	void GV(float* Buffer)
	{
		DWORD DWPB = PB();JUNK;
		if (DWPB)
		{
			Geheue.Lees<float*>(DWPB + DwVV, true, 3, Buffer);JUNK;
		}
	}
	//GetAngles
	void GA(float* Angles)
	{
		DWORD AnglePointer = Geheue.Lees<DWORD>(DwEn + DwEP);JUNK;
		if (AnglePointer)
		{
			Geheue.Lees<float*>(AnglePointer + DwVA, true, 3, Angles);JUNK;
		}
	}

	//GetPlayer
	void GP(float* Punch)
	{
		DWORD DWPB = PB();JUNK;
		if (DWPB)
		{
			Geheue.Lees<float*>(DWPB + DwVP, true, 2, Punch);JUNK;
		}
	}

	//GetCrosshairID
	int CI()
	{
		DWORD DWPB = PB();JUNK;
		if (DWPB)
		{
			return Geheue.Lees<int>(DWPB + DwCI) - 1;JUNK;
		}
	}


	//GetPosition
	void GPO(float* Position)
	{
		DWORD DWPB = PB();JUNK;
		if (DWPB)
		{
			Geheue.Lees<float*>(DWPB + DwVO, true, 3, Position);JUNK;
		}
	}
	//Afrikaan for vision aka radar
	void Visie(int PN){
		
		DWORD DWBE = EntiteitLys.BE(PN);JUNK;

		if (GetAsyncKeyState(VisieMaar) != 0)
		{
			if(EntiteitLys.MBS(PN) == 0){
				Geheue.Skryf<int>(DWBE + DwMBS, 1, false);JUNK;
			}
		}
	}

	//GetViewOffset
	float GVO()
	{
		DWORD DWPB = PB();JUNK;
		if (DWPB)
		{
			float Vecview[3];JUNK;
			Geheue.Lees<float*>(DWPB + DwVVO, true, 3, Vecview);JUNK;
			return Vecview[2];JUNK;
		}
	}

	//GetShotsFired
	int GSF()
	{
		DWORD DWPB = PB();JUNK;
		if (DWPB)
		{
			return Geheue.Lees<int>(DWPB + DwSF);JUNK;
		}
	}

}Speler;//Afrikaans for player


//Afrikaans for angle
void hoekN(float* hoek)
{
	if (hoek[0] > 89.0f && hoek[0] <= 180.0f)
	{
		hoek[0] = 89.0f;
	}
	if (hoek[0] > 180.f)
	{
		hoek[0] -= 360.f;
	}
	if (hoek[0] < -89.0f)
	{
		hoek[0] = -89.0f;
	}
	if (hoek[1] > 180.f)
	{
		hoek[1] -= 360.f;
	}
	if (hoek[1] < -180.f)
	{
		hoek[1] += 360.f;
	}
	if (hoek[2] != 0.0f)
	{
		hoek[2] = 0.0f;
	}
}
void Visie()
{
//[junk_disable /]
	for (int i = 0; i < nop; i++)
	{
//[junk_enable 1 15 /]
		Speler.Visie(i);JUNK;
	}
}

//Afrikaans for calcangle
void berekenhoek(float *src, float *dst, float *hoeke)
{
	random_device Random;
	mt19937 RandomGen(Random());
	uniform_real<float> RandomXdistrib(pbietjie, pbaie);
	uniform_real<float> RandomYdistrib(ybietjie, ybaie);
	float MyPunch[2];
	Speler.GP(MyPunch);
	float pitchreduction = RandomXdistrib(RandomGen);
	float yawreduction = RandomYdistrib(RandomGen);
	float delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), ((src[2] + Speler.GVO()) - dst[2]) };
	float hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	hoeke[0] = atanf(delta[2] / hyp) * 57.295779513082f - MyPunch[0] * pitchreduction;
	hoeke[1] = atanf(delta[1] / delta[0]) * 57.295779513082f - MyPunch[1] * yawreduction;
	hoeke[2] = 0.0f;
	if (delta[0] >= 0.0)
	{
		hoeke[1] += 180.0f;
	}
}
//smoothangleset(destination,origin)
void SAS(float* d, float* o)
{
	float SMA[3];
	SMA[0] = d[0] - o[0];
	SMA[1] = d[1] - o[1];
	SMA[2] = 0.0f;
	hoekN(SMA);
	SMA[0] = o[0] + SMA[0] / 100.0f * sa;
	SMA[1] = o[1] + SMA[1] / 100.0f * sa;
	SMA[2] = 0.0f;
	hoekN(SMA);
	Speler.SA(SMA);
	Sleep(1);
}

// NEW CLICK API
void c()
{  
  INPUT Input={0};
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
  ::SendInput(1,&Input,sizeof(INPUT));
  ::ZeroMemory(&Input,sizeof(INPUT));
  Sleep(5);JUNK;
  Input.type      = INPUT_MOUSE;
  Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
  ::SendInput(1,&Input,sizeof(INPUT));
  Sleep(16);JUNK;
}

//velocitycomp(PlayerNumber,Enemy Position)
void VC(int PN, float* EP)
{
	//enemy velocity
	float EV[3];
	//my velocity
	float MV[3];
	EntiteitLys.GV(PN, EV);
	Speler.GV(MV);
	EP[0] = EP[0] + (EV[0] / 100.f) * (40.f / sa); //not sure why 40 works. I tried a lot of different values and 40 seems to scale perfectly
	EP[1] = EP[1] + (EV[1] / 100.f) * (40.f / sa);
	EP[2] = EP[2] + (EV[2] / 100.f) * (40.f / sa);
	EP[0] = EP[0] - (MV[0] / 100.f) * (40.f / sa);
	EP[1] = EP[1] - (MV[1] / 100.f) * (40.f / sa);
	EP[2] = EP[2] - (MV[2] / 100.f) * (40.f / sa);
}

/* broken glow
void glow(DWORD clientDLL, DWORD localPlayer)
{
        float R;
        float G;
        float B;
        float A;

		int iC = 0;
        for (iC = 0; iC <= 64; iC++)
        {
                DWORD currPlayer = Geheue.Lees<DWORD>((clientDLL + DwEL) + (iC * DwES));
			//	int localTeam = Geheue.Lees<int>(localPlayer + DwTN);
              //  int currPlayerTeam = Geheue.Lees<int>(currPlayer + DwTN);
 
               // if (currPlayerTeam == 2 || currPlayerTeam == 3)
              //  {
                     //   if (currPlayerTeam != localTeam)
                     //   {
                               //DWORD glowPointer = Geheue.Lees<DWORD>(clientDLL + 0x4B23D14);
							   //glowobject = 0x04afce94
							   
							   //0x006048a4
							   DWORD glowPointer = Geheue.Lees<DWORD>(DwGlow);//0x4AFCE94);
                                //int glowIndex = Geheue.Lees<int>(currPlayer + 0x1DC0); //0x00001dc0
 
                             // if (currPlayerTeam == 2) // T
                             //   {
                                        R = (float)180;
                                       G = (float)20;
                                        B = (float)20;
                                        A = (float)210;
                            //    }
                             //   else if (currPlayerTeam == 3) // CT
                             //   {
                                     //   R = (float)20;
                                     //   G = (float)70;
                                     //   B = (float)180;
                                     //   A = (float)210;
                             //   }

                                Geheue.Skryf<float>(glowPointer + 0x4, 0.5f);
                                Geheue.Skryf<float>(glowPointer + 0x8, 0.f);
                                Geheue.Skryf<float>(glowPointer + 0xC, 0.f);
                                Geheue.Skryf<float>(glowPointer + 0x10, 1.f);
                                Geheue.Skryf<BOOL>(glowPointer + 0x24, true);
                                Geheue.Skryf<BOOL>(glowPointer + 0x25, false);
                        }
                }
 */
DWORD WINAPI AB(LPVOID params)
{
	cout << "$ thread is running..." << endl;JUNK;
	while (true)
	{
		Sleep(1);JUNK;
		if (Doodmaak)
		{
			cout << "$ Ending thread..." << endl;
			ExitThread(0);JUNK;
		}

		if (Doel || Sneller)
		{
			DraadGestop = false;JUNK;
			if (Doel)
			{
				int PN = Speler.CI();JUNK;

				while (Speler.GSF() > 1 && PN < 64 && PN >= 0 && EntiteitLys.GT(PN) != Speler.GT() && EntiteitLys.ID(PN) != true)
				{
					//TempPlayerNumber
					int TPN = Speler.CI();JUNK;
					if (TPN < 64 && TPN >= 0 && EntiteitLys.GT(TPN) != Speler.GT() && EntiteitLys.ID(TPN) != true)
					{
						PN = TPN;JUNK;
					}

					//Player Position
					float PPO[3];
					//Enemy Position
					float EP[3];
					//AimAngle
					float AA[3];
					//CurrentAngle
					float CA[3];
					Speler.GPO(PPO);
					EntiteitLys.GBP(PN, EP);
					VC(PN, EP);
					berekenhoek(PPO, EP, AA);
					hoekN(AA);
					Speler.GA(CA);
					hoekN(CA);
					SAS(AA, CA);
				
					Sleep(1);
				}
			}
			if (Sneller)
			{
				if (GetAsyncKeyState(SnellerMaar) != 0) 
				{
					
					int PN = Speler.CI();JUNK;
					if (PN < 64 && PN >= 0 && EntiteitLys.GT(PN) != Speler.GT() && EntiteitLys.ID(PN) != true)
					{
						
						c();JUNK;
					}
					else
					{
						Sleep(1);JUNK;
					}
				}


			}
			if (GetAsyncKeyState(VisieMaar) != 0){
				Visie();JUNK;
				Sleep(500);JUNK;
			}
		}
		else
		{
			DraadGestop = true;JUNK;
			Sleep(500);JUNK;
		}

	}
	
}

void Init()
{
	cout << "$ Waiting for process..." << endl;
	Teiken = NULL;
	while (!Teiken)
	{
		cout << ".";
		Teiken = KryProseshanteerdeur("csgo.exe");
		Sleep(500);
	}
	cout << endl;
	//Client Handle
	cout << "$ CH..." << endl;
	DwCl = NULL;
	while (!DwCl)
	{
		cout << ".";
		mcli = KryMhanteerdeur("client.dll", GetProcessId(Teiken));
		DwCl = mcli.ba;
		Sleep(500);
	}
	cout << endl;
	//Engine Handle
	cout << "$ EH..." << endl;
	DwEn = NULL;
	while (!DwEn)
	{
		cout << ".";
		meng = KryMhanteerdeur("engine.dll", GetProcessId(Teiken));
		DwEn = meng.ba;
		Sleep(500);
	}
	cout << endl;
	//Local player offset
	cout << "$ LPO..." << endl;
	DwLP = 0x0;
	while (!DwLP) {
		cout << ".";
		DWORD lpStart = Geheue.VindPatroonVeelvuldige(mcli.ba, mcli.si, "xxx????xx????xxxxx?", 19, 0x8D, 0x34, 0x85, 0x0, 0x0, 0x0, 0x0, 0x89, 0x15, 0x0, 0x0, 0x0, 0x0, 0x8B, 0x41, 0x8, 0x8B, 0x48, 0x0);
		DWORD lpP1 = Geheue.Lees<DWORD>(lpStart + 3);
		BYTE lpP2 = Geheue.Lees<BYTE>(lpStart + 18);
		DwLP = (lpP1 + lpP2) - mcli.ba;
	}

	std::cout << endl;
	//Entity list offset
	cout << "$ ELO..." << endl;
	DwEL = 0x0;
	while (!DwEL) {
		cout << ".";
		DWORD elStart = Geheue.VindPatroonVeelvuldige(mcli.ba, mcli.si, "x????xx?xxx", 11, 0x5, 0x0, 0x0, 0x0, 0x0, 0xC1, 0xE9, 0x0, 0x39, 0x48, 0x4);
		DWORD elP1 = Geheue.Lees<DWORD>(elStart + 1);
		BYTE elP2 = Geheue.Lees<BYTE>(elStart + 7);
		DwEL = (elP1 + elP2) - mcli.ba;
	}
	std::cout << endl;
	/*
	//esp glow
	cout << "$ GLO..." << endl;
	DwGlow = 0x0;
	while (!DwGlow) {
	   cout << ".";
       DWORD gpStart = Geheue.VindPatroonVeelvuldige(mcli.ba, mcli.si, "xxxxxxxxxxxxxx????xxxxxxx", 25, 0x6B, 0xD6, 0x34, 0x89, 0x44, 0x0A, 0x30, 0x8D, 0x8F, 0xE4, 0x1B, 0x00, 0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0xC7, 0x04, 0x02, 0x00, 0x00, 0x00, 0x00);
       DwGlow = Geheue.Lees<DWORD>(gpStart + 14) - mcli.ba;
	}
	std::cout << endl;
*/
	//Engine Pointer and Setviewangle
	cout << "$ EP and SVA..." << endl;
	DwEP = 0x0;
	while (!DwEP) {
		cout << ".";
		DWORD epStart = Geheue.VindPatroonVeelvuldige(meng.ba, meng.si, "xxxxxxxx????xxxxxxxxxx????xxxx????xxx", 37, 0xF3, 0x0F, 0x5C, 0xC1, 0xF3, 0x0F, 0x10, 0x15, 0x0, 0x0, 0x0, 0x0, 0x0F, 0x2F, 0xD0, 0x76, 0x04, 0xF3, 0x0F, 0x58, 0xC1, 0xA1, 0x0, 0x0, 0x0, 0x0, 0xF3, 0x0F, 0x11, 0x80, 0x0, 0x0, 0x0, 0x0, 0xD9, 0x46, 0x04);
		DwEP = Geheue.Lees<DWORD>(epStart + 22) - meng.ba;
		DwVA = Geheue.Lees<DWORD>(epStart + 30);
	}
	std::cout << endl;

	cout << "$ FPS: Console Peasant." << endl;
}

void PrintInstructions() {
	cout << "$ How:" << endl << "$ CTRL+F8 to close" << endl << "$ CTRL+1 A" << endl << "$ CTRL+2 T" << endl;
}

int main()
{
	system("pause");JUNK;
	cout << endl << endl;JUNK;
	Init();	JUNK;
	CreateThread(0, 0x1000, &AB, 0, 0, 0);JUNK;
	Sleep(1000);JUNK;
	PrintInstructions();
	cout << "$ A: " << aval << " | T: " << tval << endl;JUNK;


	while (true)
	{
		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(VK_F8) < 0)
		{
			while (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(VK_F8) < 0)
			{
				Sleep(100);JUNK;
			}
			Doodmaak = true;
			if (Doodmaak)
			{
				cout << "$ Ending Main thread..." << endl;JUNK;
				ExitThread(0);JUNK;
			}
		} 
		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(0x31) < 0)
		{
			while (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(0x31) < 0)
			{
				Sleep(100);JUNK;
			}
			if (Doel)
			{
				Doel = false;JUNK;
				//Californication(0);JUNK;
				//PlaySound("C:\\Windows\\Media\\Speech Off.wav", NULL, SND_FILENAME);JUNK;
			}
			else
			{
				Doel = true;JUNK;
				//Californication(1);JUNK;
				//PlaySound("C:\\Windows\\Media\\Speech On.wav", NULL, SND_FILENAME);JUNK;
			}
			if (Doel)
			{
				aval = "ON";JUNK;
				Californication(1);JUNK;
			}
			else
			{
				aval = "OFF";JUNK;
				Californication(0);JUNK;
			}
			cout << "$ A: " << aval << " | T: " << tval << endl;JUNK;
		}
		if (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(0x32) < 0)
		{
			while (GetAsyncKeyState(VK_CONTROL) < 0 && GetAsyncKeyState(0x32) < 0)
			{
				Sleep(100);JUNK;
			}
			if (Sneller)
			{
				Sneller = false;JUNK;
				//Californication(3);JUNK;
				//PlaySound("C:\\Windows\\Media\\Speech Off.wav", NULL, SND_FILENAME);JUNK;
			}
			else
			{
				Sneller = true;JUNK;
				//Californication(2);JUNK;
				//PlaySound("C:\\Windows\\Media\\Speech On.wav", NULL, SND_FILENAME);JUNK;
			}
			if (Sneller)
			{
				tval = "ON";JUNK;
				Californication(2);JUNK;
			}
			else
			{
				tval = "OFF";JUNK;
				Californication(3);JUNK;
			}
			cout << "$ A: " << aval << " | T: " << tval << endl;JUNK;
		}
	
		Sleep(25);JUNK;
	}

	return 0;JUNK;
}
