#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

class INetChannel
{
  public:
	long pad_0000[5]; //0x0000
	bool processingMessages; //0x0014
	bool shouldDelete; //0x0015
	char pad_0016[2]; //0x0016
	int32_t outSequenceNr; //0x0018 last send outgoing sequence number
	int32_t inSequenceNr; //0x001C last received incoming sequnec number
	int32_t outSequenceNrAck; //0x0020 last received acknowledge outgoing sequnce number
	int32_t outReliableState; //0x0024 state of outgoing reliable data (0/1) flip flop used for loss detection
	int32_t inReliableState; //0x0028 state of incoming reliable data
	int32_t chokedPackets; //0x002C number of choked packets
	char pad_0030[1044]; //0x0030

	void Transmit(bool val)
	{
	    GetVFunc<void(__thiscall*)(void*, bool), PosixWin(50, 49)>(this)(this, val);
	}
}; //Size: 0x0444

class CClockDriftMgr
{
  public:
	float clockOffsets[16]; //0x0000
	uint32_t curClockOffset; //0x0044
	uint32_t serverTick; //0x0048
	uint32_t clientTick; //0x004C
}; //Size: 0x0050

// This struct is most likely wrong
// Only fields that I know to be valid are:
// - netChannel
// - currentSequence
// - deltaTick
// - maxClients
// - viewangles
class CClientState
{
  public:
	void ForceFullUpdate()
	{
		deltaTick = -1;
	}

	//TODO: Reverse struct on Linux
#ifdef _WIN32
	char pad_0000[156]; //0x0000
	INetChannel* netChannel; //0x009C
	uint32_t challengeNr; //0x00A0
	char pad_00A4[100]; //0x00A4
	uint32_t signonState; //0x0108
	char pad_010C[8]; //0x010C
	float nextCmdTime; //0x0114
	uint32_t serverCount; //0x0118
	uint32_t currentSequence; //0x011C
	char pad_0120[8]; //0x0120
#else
	char pad_0000[296];
	INetChannel* netChannel;
	char pad_0001[140];
#endif
	CClockDriftMgr clockDriftMgr; //0x0128
	uint32_t deltaTick; //0x0178
	bool paused; //0x017C
	char pad_017D[3]; //0x017D
	uint32_t viewEntity; //0x0180
	uint32_t playerSlot; //0x0184
	char levelName[260]; //0x0188
	char levelNameShort[40]; //0x028C
	char groupName[40]; //0x02B4
	char pad_02DC[56]; //0x02DC
	uint32_t maxClients; //0x0310
	char pad_0314[18940]; //0x0314
	vec3 viewangles; //0x4D10
	char pad_p100[0x400C];
	int chokedcmds;
	int lastoutgoing;
	int last_command_ack;
}; //Size: 0x4D1C

#endif
