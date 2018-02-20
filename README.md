# Network Security - DNS Kaminsky attack - Group 15
The Domain Name System (DNS) is a hierarchical decentralized naming system for computers,
services, or other resources connected to the Internet or a private network. The DNS provides
the service of translations between a human-readable domain name (such as nerd.emoji.fun) into
a numerical IP address used for locating and identifying computer services and devices with the
underlying network protocols. By providing a worldwide, distributed directory service, the Domain
Name System is an essential component of the functionality of the Internet, that has been in use
since 1985. It works as follow.

![](https://github.com/filippodp/network.security/blob/master/images/How_DNS_Work.png "How DNS Work")

The Kaminsky attack is used to take control over an entire domain zone, replacing in a vulnerable
server a NS-type record. The attack is performed in this way.

![](https://github.com/filippodp/network.security/blob/master/images/Attack_Schema.png "Attack Schema")

For this experience we used `bind9` on every DNS servers and `apache2` into the WEB servers.
The entire lab was built on `docker`
We used the follow command for delaying the `dns-auth.fun` connections.
```
$ tc qdisc add dev eth0 root netem delay 97ms
```
The project is provided with a makefile that helps to automatize some routines.

![](https://upload.wikimedia.org/wikipedia/commons/7/79/Docker_%28container_engine%29_logo.png "Docker Logo")
