;
; BIND reverse data file for broadcast zone.nerd.emoji.fun
;
$TTL    604800
@       IN      SOA     dns-auth.emoji.fun. root.dns-auth.emoji.fun. (
                              1         ; Serial
                         604800         ; Refresh
                          86400         ; Retry
                        2419200         ; Expire
                         604800 )       ; Negative Cache TTL
;                                             
@                    IN   NS    dns-auth.emoji.fun.
dns-auth.emoji.fun.  IN   A     10.10.0.4

nerd                 IN   A     10.10.0.5
monkey               IN   A     10.10.0.6
tiger                IN   A     10.10.0.7
smile                IN   A     10.10.0.8
relax                IN   A     10.10.0.9
