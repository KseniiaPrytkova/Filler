

from subprocess import Popen, PIPE


# $ pip install pygame
import pygame



__PLAYER_BINARY = "kprytkov.filler"

cmd = "./resources/filler_vm -f resources/maps/map01 -p1 ./kprytkov.filler -p2 ./resources/players/superjeannot.filler"


COLOR_BKG = (255, 255, 255)

COLOR_PLAYER =            (66, 135, 245)
COLOR_PLAYER_BORDER =     (0, 0, 0)
COLOR_PLAYER_NEW =        (89, 147, 245)
COLOR_PLAYER_NEW_BORDER = (255, 255, 255)

COLOR_ENEMY =             (240, 99, 38)
COLOR_ENEMY_BORDER =      (0, 0, 0)
COLOR_ENEMY_NEW =         (237, 116, 64)
COLOR_ENEMY_NEW_BORDER =  (255, 255, 255)

surface = None
board_w, board_h = None, None
piece_w, piece_h = 20, 20
padding_w, padding_h = 10, 10


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

	for i, line in enumerate(board):
		for j, c in enumerate(c for c in line):
			if c == 'X':
				pygame.draw.rect(surface, COLOR_ENEMY,
					(j*piece_h, i*piece_w, piece_h, piece_w), 0)
				pygame.draw.rect(surface, COLOR_ENEMY_BORDER,
					(j*piece_h, i*piece_w, piece_h, piece_w), 3)
			elif c == 'x':
				pygame.draw.rect(surface, COLOR_ENEMY_NEW,
					(j*piece_h, i*piece_w, piece_h, piece_w), 0)
				pygame.draw.rect(surface, COLOR_ENEMY_NEW_BORDER,
					(j*piece_h, i*piece_w, piece_h, piece_w), 3)
			if c == 'O':
				pygame.draw.rect(surface, COLOR_PLAYER,
					(j*piece_h, i*piece_w, piece_h, piece_w), 0)
				#pygame.draw.rect(surface, COLOR_PLAYER_BORDER,
				#	(padding_h + j*piece_h, padding_w + i*piece_w, piece_h, piece_w), 3)

				pygame.draw.rect(surface, COLOR_PLAYER_BORDER,
					(j*piece_h + (piece_h - 3), i*piece_w+1, 3, piece_w - 3 + 1), 3)

				pygame.draw.rect(surface, COLOR_PLAYER_BORDER,
					(j*piece_h+1, i*piece_w + (piece_h - 3), piece_h - 3 + 1, 3), 3)
			elif c == 'o':
				pygame.draw.rect(surface, COLOR_PLAYER_NEW,
					(j*piece_h, i*piece_w, piece_h, piece_w), 0)
				#pygame.draw.rect(surface, COLOR_PLAYER_NEW_BORDER,
				#	(padding_h + j*piece_h, padding_w + i*piece_w, piece_h, piece_w), 3)
	# 24, 40
	# 24 * 20 = 480
	# 40 * 20 = 800
	#pygame.draw.rect(surface, COLOR_BLUE, (0, 0, 20, 20), 0)
	#pygame.draw.rect(surface, COLOR_BLUE, (780, 460, 20, 20), 0)
				#pygame.draw.rect(surface, COLOR_BLUE, (i, j, piece_w, piece_h))

	'''xs_empty, ys_empty = [], []
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

	plt.plot(xs_player, ys_player, 's', color='green', alpha=0.5)
	plt.plot(xs_enemy, ys_enemy, 's', color='red', alpha=0.5)
	plt.pause(0.02)'''


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

	#plt.axis([-0.5, settings['board_dim_y']+0.5, -0.5, settings['board_dim_x']+0.5])

	board_w, board_h = settings['board_dim_y'] * piece_w, settings['board_dim_x'] * piece_h
	pygame.init()
	surface = pygame.display.set_mode((board_w, board_h))
	pygame.display.set_caption("Filler")
	surface.fill(COLOR_BKG)

	#font = pygame.font.SysFont("comicsansms", 48)
	#text = font.render("Test", True, (0, 128, 0))

	bkg = pygame.image.load("space_hamster.png").convert()
	bkg_rect = bkg.get_rect()
	surface.blit(bkg, bkg_rect)

	while True:
		line, state = read_reg(settings, p, state)

		if not line:
			break

		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				pygame.quit()

		#pygame.display.update()

		#surface.blit(text, (100, 100))

		pygame.display.flip()





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

#print(str(settings))
## $$$ exec p1 : [./kprytkov.filler]
## launched ./resources/players/superjeannot.filler
## $$$ exec p2 : [./resources/players/superjeannot.filler]