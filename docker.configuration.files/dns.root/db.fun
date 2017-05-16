;
; BIND reverse data file for broadcast zone.fun
;
$TTL    604800
@       IN      SOA     dns-root. root.dns-root. (
                              1         ; Serial
                         604800         ; Refresh
                          86400         ; Retry
                        2419200         ; Expire
                         604800 )       ; Negative Cache TTL
;                                             
@                      IN NS    dns-root.
dns-root.              IN A     10.10.0.2

fun.                   IN NS    dns-auth.fun.
dns-auth.fun.          IN A     10.10.0.3
