#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include "discord_rpc.h"

static const char* APPLICATION_ID = "847356917122334762";
char arr[][100] = {
	"procrastinating",
	"programming",
	"playing Minecraft",
	"looking for techies",
	"wasting time on YouTube",
	"dying",
	"installing updates",
	"having moodswings 1",
	"having moodswings 2",
	"having moodswings 3",
	"having moodswings 4",
	"having moodswings 5",
	"having moodswings 6",
	"having moodswings 7",
	"annoying Aarya",
	"destroying Aarya at a block game",
	"coding the next billion dollar app",
	"writing status for you to read over here",
	"time travelling"
	"looking for a better computer",
	"contemplating on why Edge exists",
	"being ADIGEN",
	"being the ADIGEN you hate",
	"stalking you",
	"crushing on you",
	"being a Linux advocate",
	"cursing about JavaScript",
	"meeting new people",
	"making new friends",
};
int arrLength = sizeof(arr) / sizeof(arr[0]);
int timestamp = 0;
int taskDuration = 10 + 1;
int currentTime = time(0);

static void updateDiscordPresence(int p_status = 0) {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));
	discordPresence.state = "for the next";
	discordPresence.details = arr[p_status];
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
	updateDiscordPresence(rand() % arrLength);

#ifdef DISCORD_DISABLE_IO_THREAD
		Discord_UpdateConnection();
#endif
		Discord_RunCallbacks();

	sleep(taskDuration);
	statusLoop();
}

int main(int argc, char* argv[]) {
	discordInit();

	statusLoop();

	Discord_Shutdown();
	return 0;
}
