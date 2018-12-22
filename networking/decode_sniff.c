#include <pcap.h>

#include "../common/hacking.h"
#include "../common/hacking-network.h"

void pcap_fatal(char const *, char const *);
void decode_ethernet(u_char const *);
void decode_ip(u_char const *);
u_int decode_tcp(u_char const *);
void caught_packet(u_char *, struct pcap_pkthdr const *, u_char const *);

int main() {
    struct pcap_pkthdr cap_header;
    u_char const * packet, *pkt_data;
    char errbuf[PCAP_ERRBUF_SIZE];
    char *device;

    pcap_t *pcap_handle;

    device = pcap_lookupdev(errbuf);
    if (device == NULL)
        pcap_fata("pcap_lookupdev", errbuf);

    printf("sniffing on device %s\n", device);

    pcap_handle = pcap_open_live(device, 4096, 1, 0, errbuf);
    if (pcap_handle == NULL)
        pcap_fatal("pcap_open_live", errbuf);

    pcap_loop(pcap_handle, 3, caught_packet, NULL);

    pcap_close(pcap_handle);
}

void caught_packet(u_char *user_args, struct pcap_pkthdr const *cap_header,
                   u_char const *packet) {
    int tcp_header_length, total_header_size, pkt_data_len;
    u_char *pkt_data;

    printf("==== got a %d byte packet ====\n", cap_header->len);

    decode_ethernet(packet);
    decode_ip(packet + ETHER_HDR_LEN);
    tcp_header_length = decode_tcp(packet + ETHER_HDR_LEN + sizeof(struct ip_hdr));

    total_header_size = ETHER_HDR_LEN + sizeof(struct ip_hdr) + tcp_header_length;
    pkt_data = (u_char *)packet + total_header_size; // pkt_data points to the data portion
    pkt_data_len = cap_header->len - total_header_size;
    if (pkt_data_len > 0) {
        printf("\t\t\t%u bytes of packet data\n", pkt_data_len);
        dump(pkt_data, pkt_data_len);
    } else 
        printf("\t\t\tNo Packet Data\n");
}

void pcap_data(char const *failed_in, char const * errbuf) {
    printf("Fatal Error in %s: %s\n", failed_in, errbuf);
    exit(1);
}

void decode_ethernet(u_char const *header_start) {
    int i;
    struct ether_hdr const *ethernet_header;

    ethernet_header = (struct ether_hdr const *)header_start;
    printf("[[ Layer 2 :: Ethernet Header ]]\n");
    printf("[ Source: %02x", ethernet_header->ether_src_addr[0]);
    for (i=1; i<ETHER_ADDR_LEN; i++)
        printf(":%02x", ethernet_header->ether_src_addr[i]);

    printf("\tDest: %02x", ethernet_header->ether_dest_addr[0]);
    for (i=1; i<ETHER_ADDR_LEN; i++)
        printf(":%02x", ethernet_header->ether_dest_addr[i]);
    printf("\tType: %hu ]\n", ethernet_header->ether_type);
}

void decode_ip(u_char const *header_start) {

}
