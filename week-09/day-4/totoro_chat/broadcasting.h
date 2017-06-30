#ifndef _BROADCASTING_H
#define _BROADCASTING_H

void server_broadcast();
void server_discover();
void reply_to_discovery_request(int discovery_port, char *discovery_address);
void send_discovery_request();

#endif // _BROADCASTING_H
