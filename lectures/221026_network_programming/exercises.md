# Exercises for Network Programming

## An echoing server
Within the code_echo directory you should find running a very simple server and client. You can start a server on port 12345 with:

    ./echoserver 12345

You can then start a client to connect to that server with:

    ./echoclient 0.0.0.0 12345

Note that both will run forver, with the client waiting for you to type in some text, which will be sent to the server.

### Ping/pong
Modify the server so that if it recieves a `ping` message, it replies with a `pong`. In all other cases the server returns `BAD REQUEST`.

### Distributed variable
The server accepts two different kinds of messages.

* `PUT [SOME STRING]` that stores a string in the internal storage of the server. Note that the first space is a separator and thus part of the protocol syntax.
* `GET` that returns the string that is stored.

When the server receives a `PUT` it saves the string to an internal variable and returns `OK`. The following `PUT` messages will not update the variable, but return `VARIABLE FILLED`.

When the server receives a `GET` it returns the stored variable. All `GET`s should be blocking, until the server has received the first `PUT`. Thus, clients sending a `GET` before another client send a `PUT` should block and wait until the server receives the first `PUT` and responds to all waiting clients.

