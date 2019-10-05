

from subprocess import Popen, PIPE


import numpy as np
import matplotlib
#matplotlib.use("Agg")
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

cmd = "./resources/filler_vm -f resources/maps/map01 -p1 ./kprytkov.filler -p2 ./resources/players/superjeannot.filler"


#plt.axis([0, 10, 0, 1])


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


count = 0
def create_frame(settings, board):
	pass

	xs_empty, ys_empty = [], []
	xs_player, ys_player = [], []
	xs_enemy, ys_enemy = [], []

	for i, line in enumerate(board):
		for j, c in enumerate(c for c in line):
			if c == 'X' or c == 'x':
				xs_player += [i]
				ys_player += [j]
			elif c == 'O' or c == 'o':
				xs_enemy += [i]
				ys_enemy += [j]
			else:
				xs_empty += [i]
				ys_empty += [j]

	#plt.clear()
	plt.plot(xs_player, ys_player, 's', color='green', alpha=0.5)
	plt.plot(xs_enemy, ys_enemy, 's', color='red', alpha=0.5)
	plt.pause(0.02)


	#print(str(board) + '\n')
	#for e in board:
	#	print(e)
	#print('\n')

	#y = np.random.random()
	#plt.scatter(count, y)
	#plt.pause(0.05)

	#count += 1


def read_reg(settings, p, state):
	line = p.stdout.readline()

	if line:
		if state == -2:
			if 'Plateau' in line:
				state = -1
		elif state == -1:
			state += 1
		elif state == 0:
			# Create a frame.
			board = [line.split(' ')[1].strip()]
			while state < settings['board_dim_x'] - 1:
				line = p.stdout.readline()
				board += [line.split(' ')[1].strip()]
				state += 1
			create_frame(settings, board)
			state = -2

	return line, state

if __name__ == "__main__":
	p = Popen(cmd, stdout=PIPE, shell=True)
	settings = {}
	init = True
	state = -2
	while init:
		line, init, state = read_init(settings, p, state)

	plt.axis([-0.5, settings['board_dim_y']+0.5, -0.5, settings['board_dim_x']+0.5])

	while True:
		line, state = read_reg(settings, p, state)

		if not line:
			break
	plt.pause(2.0)




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