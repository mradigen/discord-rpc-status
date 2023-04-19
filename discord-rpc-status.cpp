#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "discord_rpc.h"

static const char* APPLICATION_ID = "847356917122334762";
char statuses[][100] = {
	"ricing",
	"ricing picom",
	"ricing polybar",
	"pissed at how bad ChatGPT is at code",
	"looking for techies",
	"installing updates",
	"being a Linux advocate",

	"coding the next billion dollar app",
	"programming",
	"cursing about JavaScript",

	"writing status for you to read over here",
	"time travelling",
	"being ADIGEN",
	"meeting new people",
	"making new friends",
	"waiting for DMs",

	"playing Minecraft",
	"playing War Thunder",
	"looking for SMP players",
	"sad that no one reads these anymore 🥲",
};

int statusesLength = sizeof(statuses) / sizeof(statuses[0]);
int timestamp = 0;
int taskDuration = 10 + 1;
int currentTime = time(0);

static void updateDiscordPresence(int p_status = 0) {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "for the next";
	discordPresence.details = statuses[p_status];
	discordPresence.startTimestamp = time(0);
	discordPresence.endTimestamp = time(0) + taskDuration;
	discordPresence.largeImageKey = "adjn";
	discordPresence.largeImageText = "I'm just his bot leave me alone";
	Discord_UpdatePresence(&discordPresence);
}

// static void handleDiscordReady(const DiscordUser* connectedUser) {
// 	printf("Connected to user %s#%s - %s\n",
// 		connectedUser->username,
// 		connectedUser->discriminator,
// 		connectedUser->userId);
// }

static void discordInit() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	// handlers.ready = handleDiscordReady;
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

static void statusLoop() {
	while (true) {
		updateDiscordPresence(rand() % statusesLength);
		//updateDiscordPresence(6);

#ifdef DISCORD_DISABLE_IO_THREAD
		Discord_UpdateConnection();
#endif
		Discord_RunCallbacks();
		sleep(taskDuration);
	}
}

int main(int argc, char* argv[]) {
	srand(time(0));
	discordInit();

	statusLoop();

	Discord_Shutdown();
	return 0;
}
