#include "WebSocket.hpp"
#include "Callback.hpp"
#include <signal.h>
#include <cstddef>

using namespace ws;

bool running = false;
ws::WebSocket *websock;

void init(void);
void loop();

void close();

void signal_handler(int signal);

void Connected(struct ws::ClientInfo &info, char *handshake);
void Disconnected(struct ws::ClientInfo &info);
void onFrame(struct ws::ClientInfo &info, ws::Frame *frame);
void onMessage(struct ws::ClientInfo &info, char *message, size_t length);

int main(int argc, char *argv[])
{
	signal(SIGINT, signal_handler);

	init();
	loop();

	close();

	return 0;
}

void signal_handler(int signal)
{
	if(SIGINT != signal)
		return;

	if(NULL != websock)
		websock->Stop();

	running = false;

	close();

	printf("%s%s%s", CONSOLE_COLOR_MAGENTA, "\b\bApplication is shutting down...\n", CONSOLE_COLOR_RESET);

	exit(0);
}

void init(void)
{
	websock = new WebSocket();

	ws::CallbackManager::RegisterCallback(static_cast<ws::ConnectedCallback>(&Connected));
	ws::CallbackManager::RegisterCallback(static_cast<ws::DisconnectedCallback>(&Disconnected));
	ws::CallbackManager::RegisterCallback(static_cast<ws::FrameCallback>(&onFrame));
	ws::CallbackManager::RegisterCallback(static_cast<ws::MessageCallback>(&onMessage));
}

void loop()
{
	running = true;

	websock->Listen();

	while(running)
	{
	}
}

void close()
{
	if(NULL == websock)
		return;

	delete(websock);
	websock = NULL;
}

void Connected(struct ws::ClientInfo &info, char *handshake)
{
}

void Disconnected(struct ws::ClientInfo &info)
{
}

void onFrame(struct ws::ClientInfo &info, ws::Frame *frame)
{
	char buffer[frame->length];

	printf("Payload: %s%s%s\n", CONSOLE_COLOR_RED, frame->payload, CONSOLE_COLOR_RESET);
	sprintf(buffer, "You said: %s", frame->payload);

	websock->Send(buffer);
}

void onMessage(struct ws::ClientInfo &info, char *message, size_t length)
{
	printf("Message: %s%s%s\n", CONSOLE_COLOR_RED, message, CONSOLE_COLOR_RESET);
}