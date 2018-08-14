#ifndef CLIENTSTATE_H
#define CLIENTSTATE_H

class CClientState
{
  public:
	char pad_0x0[0xC];
	float connectTime;
	int retryNumber;
	char pad_0x14[0x4];
	int int7;
	char pad_0x1C[0x4];
	int int9;
	char pad_0x24[0x40];
	int currentSequence;
	char pad_0x68[0x8];
	int deltaTick;
	int paused;
	int viewEntity;
	int playerSlot;
	char levelName[40];
	char pad_0xA8[0x57];
	char levelNameShort[40];
	char pad_0x127[0x59];
	uint32_t maxClients;
	char pad_0x184[0x55C];
};

#endif
