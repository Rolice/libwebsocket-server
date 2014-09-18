libwebsocket-server
===================

Example Server for libwebsocket

This repository contains an example server that utilized the libwebsocket library, which project is also hosted here in GitHub: [libwebsocket](https://github.com/Rolice/libwebsocket)

The code here is not built in complete WebSocket server and it will be updated as the library development progresses.

The program built from that code is used to debug the libwebsocket project.

Usage
=====
The server code uses the following headers from libwebsocket:

```
#include "WebSocket.hpp"
#include "Callback.hpp"
```

These files contains definitions about the WebSocket implementation and enable callback usage inside the client application.

Registering Callbacks
=====================
To register callback function to be called on certain actions inside WebSocket communication you could use the `RegisterCallback` method or its overloads from the `CallbackManager` like:

```
void Connected(struct ws::ClientInfo &info, char *handshake);
void Disconnected(struct ws::ClientInfo &info);
void onFrame(struct ws::ClientInfo &info, ws::Frame *frame);
void onMessage(struct ws::ClientInfo &info, char *message, size_t length);

ws::CallbackManager::RegisterCallback(static_cast<ws::ConnectedCallback>(&Connected));
ws::CallbackManager::RegisterCallback(static_cast<ws::DisconnectedCallback>(&Disconnected));
ws::CallbackManager::RegisterCallback(static_cast<ws::FrameCallback>(&onFrame));
ws::CallbackManager::RegisterCallback(static_cast<ws::MessageCallback>(&onMessage));

void Connected(struct ws::ClientInfo &info, char *handshake)
{
  printf("New client connected.\n");
}

void Disconnected(struct ws::ClientInfo &info)
{
  printf("Client disconnected.\n");
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
```

The callback functions above implement the signatures of the expected callbacks, which are declared as:

```
typedef void (*ConnectedCallback)(struct ClientInfo &info, char *handshake_key);
typedef void (*DisconnectedCallback)(struct ClientInfo &info);
typedef void (*FrameCallback)(struct ClientInfo &info, ws::Frame *frame);
typedef void (*MessageCallback)(struct ClientInfo &info, char *message, size_t length);
```
