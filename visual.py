

from subprocess import Popen, PIPE


import numpy as np
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib import animation
from matplotlib.animation import FFMpegWriter
import time
#from IPython import display
import random

#import matplotlib.animation as animation
#import numpy as np
#from pylab import *


__PLAYER_BINARY = "kprytkov.filler"

cmd = "./resources/filler_vm -f resources/maps/map00 -p1 ./kprytkov.filler -p2 ./resources/players/superjeannot.filler"


def read_init(data, p, state):
	cont = True

	line = p.stdout.readline()
	if '$$$' in line:
		if __PLAYER_BINARY in line:
			settings['player_self_nm'] = int(line.split(' ')[2][1])
			settings['player_self_name'] = line[line.rfind('/')+1:-2]
		else:
			settings['player_enemy_nm'] = int(line.split(' ')[2][1])
			settings['player_enemy_name'] = line[line.rfind('/')+1:-2]

	if 'Plateau' in line:
		settings['board_dim_x'] = int(line.split(' ')[1])
		settings['board_dim_y'] = int(line.split(' ')[2][:-2])
		print("board x, y: {}, {}".format(settings['board_dim_x'], settings['board_dim_y']))
		cont = False
		state = -1

	return line, cont, state


def create_frame(settings, line):
	print(line)


def read_reg(settings, p, state):
	line = p.stdout.readline()

	if line:
		if state == -2:
			if 'Plateau' in line:
				state = -1
		elif state == -1:
			state += 1
		elif state < settings['board_dim_x']:
			create_frame(settings, line.split(' ')[1])
			state += 1
		else:
			state = -2

	return line, state

if __name__ == "__main__":
	p = Popen(cmd, stdout=PIPE, shell=True)
	settings = {}
	init = True
	state = -2
	while init:
		line, init, state = read_init(settings, p, state)

	while True:
		line, state = read_reg(settings, p, state)

		if not line:
			break




'''launched ./kprytkov.filler
$$$ exec p1 : [./kprytkov.filler]
launched ./resources/players/superjeannot.filler
$$$ exec p2 : [./resources/players/superjeannot.filler]
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..O..............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 1 3:
.**
<got (O): [8, 1]
Plateau 15 17:
    01234567890123456
000 .................
001 .................
002 .................
003 .................
004 .................
005 .................
006 .................
007 .................
008 ..oo.............
009 .................
010 .................
011 .................
012 ..............X..
013 .................
014 .................
Piece 1 3:
.**
<got (X): [12, 12]'''

print(str(settings))
## $$$ exec p1 : [./kprytkov.filler]
## launched ./resources/players/superjeannot.filler
## $$$ exec p2 : [./resources/players/superjeannot.filler]