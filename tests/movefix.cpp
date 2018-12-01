#include <stdio.h>

#include "../source_shared/sdk.h"
#include "../features/essentials.h"

void CMove(vec3_t& oldAngles, CUserCmd* cmd, int mtype)
{
	float oldfm = cmd->forwardmove;
	float oldsm = cmd->sidemove;

	float deltaView = NormalizeFloat(cmd->viewangles[1] - oldAngles.y, 0.f, 360.f);

	cmd->forwardmove = cos(deltaView * DEG2RAD) * oldfm + cos((deltaView + 90.f) * DEG2RAD) * oldsm;
	cmd->sidemove = sin(deltaView * DEG2RAD) * oldfm + sin((deltaView + 90.f) * DEG2RAD) * oldsm;

	oldAngles = cmd->viewangles;
}

int main()
{
	CUserCmd cmd;

	for (int y1 = -180; y1 <= 180; y1 += 55)
		for (int y2 = -180; y2 <= 180; y2 += 20) {
			for (int x1 = -180; x1 <= 180; x1 += 45) {
				for (int x2 = -180; x2 <= 180; x2 += 10) {
					int z1 = 0;
					for (int z2 = -180; z2 <= 180; z2 += 14) {
						//Gimbal lock test
						if (abs(z2) == 90)
							continue;

						cmd.forwardmove = 0.f;
						cmd.sidemove = 400.f;

						vec3_t oldAngles(x1, y1, z1);

						cmd.viewangles[0] = x2;
						cmd.viewangles[1] = y2;
						cmd.viewangles[2] = z2;

						float fm = cmd.forwardmove;
						float sm = cmd.sidemove;

						SourceEssentials::CorrectMovement(oldAngles, &cmd, 0);

						cmd.viewangles[0] = x1;
						cmd.viewangles[1] = y1;
						cmd.viewangles[2] = z1;

						SourceEssentials::CorrectMovement(oldAngles, &cmd, 0);

						if (fabsf(fm - cmd.forwardmove) > 0.01f || fabsf(sm - cmd.sidemove) > 0.01f) {
							printf("Mismatch (%d %d %d %d %d %d)!\nFM: %f\t%f\nSM: %f\t%f\n", x1, x2, y1, y2, z1, z2, fm, cmd.forwardmove, sm, cmd.sidemove);
						}
					}
				}
			}
		}

	return 0;
}
