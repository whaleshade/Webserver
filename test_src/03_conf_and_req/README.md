# Mini-WebServer

For building a fully operating mini-webserver.
This project is a team-work.
<br>
webserver connection part = up to me
<br>
server config parser = up to kyulim
<br>
request parser = up to nttmxk
<br>
Config class defines server config;
HttpServer class defines server creation and inlcudes the whloe logic of server;

```
	if (webServer.openServer() == FAIL)
		return (1);

	if (webServer.runServer() == FAIL) //runServer() includes Connection class methods
		return (1);
```
webServer.openServer() : socket() + bind() + listen();
webServer.runServer() : accept() + read() + write();

<br>
<br>
Only GET method(/home and /hello)
