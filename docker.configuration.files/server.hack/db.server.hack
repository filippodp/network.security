;
; BIND reverse data file for broadcast zone.nerd.emoji.fun
;
$TTL    604800
@       IN      SOA     dns-hack.emoji.fun. root.dns-hack.emoji.fun. (
                              1         ; Serial
                         604800         ; Refresh
                          86400         ; Retry
                        2419200         ; Expire
                         604800 )       ; Negative Cache TTL
;                                             
@                    IN   NS    dns-hack.emoji.fun.
dns-hack.emoji.fun.  IN   A     10.10.50.2

nerd                 IN   A     10.10.50.2
monkey               IN   A     10.10.50.2
tiger                IN   A     10.10.50.2
smile                IN   A     10.10.50.2
relax                IN   A     10.10.50.2
