;
; BIND reverse data file for broadcast zone.emoji.fun
;
$TTL    604800
@       IN      SOA     dns-auth.fun. root.dns-auth.fun. (
                              1         ; Serial
                         604800         ; Refresh
                          86400         ; Retry
                        2419200         ; Expire
                         604800 )       ; Negative Cache TTL
;                                             
@                    IN   NS    dns-auth.fun.
dns-auth.fun.        IN   A     10.10.0.3

emoji                IN   NS    dns-auth.emoji.fun.
dns-auth.emoji.fun.  IN   A     10.10.0.4
