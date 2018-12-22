#include <pcap.h>

#include "../common/hacking.h"

void pcap_fatal(char const *failed_in, char const *errbuf) {
    printf("fatal error in %s: %s\n", failed_in, errbuf);
    exit(1);
}

int main() {
    struct pcap_pkthdr header;
    u_char const *packet;
    char errbuf[PCAP_ERRBUF_SIZE];
    char *device;;
    pcap_t *pcap_handle;
    int i;

    device = pcap_lookupdev(errbuf);
    if (device == NULL)
        pcap_fatal("pcap_lookupdev", errbuf);

    printf("sniffing on device %s\n", device);

    pcap_handle = pcap_open_live(device, 4096, 1, 0, errbuf);
    if (pcap_handle == NULL)
        pcap_fatal("pcap_open_live", errbuf);

    for (i=0; i<3; i++) {
        packet = pcap_next(pcap_handle, &header);
        printf("got a %d byte packet\n", header.len);
        dump(packet, header.len);
    }
    pcap_close(pcap_handle);
}
