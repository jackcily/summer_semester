import math
import os
import time
from  random import randint
from random import uniform
import pygame
from pygame.locals import * #导入一些常用的变量
from collections import deque#加入了队列

FPS = 60
BK_WIDTH = 900  #背景宽度
BK_HEIGHT = 650  #背景高度
PIPE_WIDTH = 80 #水管的宽度
PIPE_HEIGHT = 10 #水管素材的高度
PIPE_HEAD_HEIGHT = 32#管子头的高度

#初始化全局变量
BK_MOVE_SPEED = 0.22#主柱子每毫秒移动的速度
ADD_TIME = 2500##每隔多少毫秒就增加一个柱子 这种方法不会有漏洞吗  就是当毫秒数和帧数不匹配啥的  #还需要仔细的思考
TOTAL_PIPE_BODY  =  int(3/5 * BK_HEIGHT)  # 像素值必须为整数   占窗口的3/5
PIPE_RATE =0.96
a_i="bird-wingup"
b_i="bird-wingmid"
c_i="bird-wingdown"

INITAL_SPEED = -0.37#鸟的Y轴初速度
BIRD_WIDTH = 50
BIRD_HEIGHT = 40
BIRD_INIT_SCORE  = 7#鸟的初始通关分数

STONE_ADD_TIME = 1000 #每隔多少毫秒就增加一个石头
STONE_WIDTH = 40
STONE_HEIGHT = 30
STONE_LEVEL = 4#石头出现的等级

BUTTON_WIDTH = 140
BUTT0N_HEIGHT = 60

BULLET_SPEED = 0.32#子弹的速度
BULLET_WIETH = 50
BULLET_HEIGHT = 30
#设置全局变量 方便修改参数


pygame.init()
screen = pygame.display.set_mode((BK_WIDTH,BK_HEIGHT))
pygame.mixer.init()

music_lose = pygame.mixer.Sound("lose.wav")
music1 = pygame.mixer.Sound("touch.wav")
pygame.mixer.music.load("bkm.mp3")
font = pygame.font.SysFont('comicsansms', 25)


#用于设置鸟的种类
def little_bird(list):
	global a_i
	global b_i
	global c_i
	a_i=list[0]
	b_i=list[1]
	c_i=list[2]


#用于设置关卡难度
def seteasy(list):
	global BK_MOVE_SPEED  # 背景每毫秒移动的速度   就是柱子移动的速度
	global ADD_TIME  # 每隔多少毫秒就增加一个柱子
	global TOTAL_PIPE_BODY  # 像素值必须为整数   占窗口的3/5
	global PIPE_RATE
	global STONE_LEVEL  # 鸟出现的等
	global BIRD_INIT_SCORE

	BK_MOVE_SPEED = list[0]  # 背景每毫秒移动的速度
	ADD_TIME = list[1]  # 每隔多少毫秒就增加一个柱子
	TOTAL_PIPE_BODY =list[2]  # 像素值必须为整数   占窗口的3/5
	PIPE_RATE = list[3]
	Pipe.add_time = list[1]
	BIRD_INIT_SCORE = list[4]
	STONE_LEVEL = list[5]


#子弹类
class Bullet(pygame.sprite.Sprite):
	speed = BULLET_SPEED
	width = BULLET_WIETH
	height = BULLET_HEIGHT

	def __init__(self,bird,images):
		super(Bullet,self).__init__() #d调用父类的初始函数 使用此方法 可以减少代码的更改量 并且解决了多重继承的问题
		self.x,self.y = bird.x,bird.y
		self.bullet = images #给鸟的图片进行赋值
		self.mask_bullet = pygame.mask.from_surface(self.bullet)
	def update(self):#计算鸟在下一点的新坐标并更新
		self.x=self.x+self.speed*frames_to_msec(1)
	@property
	def image(self):
		return self.bullet
	@property
	def mask(self):
		return self.mask_bullet
	@property
	def rect(self):
		return Rect(self.x,self.y,Bullet.width,Bullet.height)
	def visible(self):
		return 0<self.x<BK_WIDTH+Bullet.width


#小鸟做竖直上抛运动  当小鸟加速到一定状态时 就不再加速了
class Bird(pygame.sprite.Sprite):

	width =BIRD_WIDTH #鸟宽
	height = BIRD_HEIGHT #鸟长
	sink_gravity = 0.001#鸟的下降重力

	def __init__(self,x,y,level,images):
		super(Bird,self).__init__() #d调用父类的初始函数 使用此方法 可以减少代码的更改量 并且解决了多重继承的问题
		self.x,self.y = x,y
		self.wing_up,self.wing_mid,self.wing_down = images #给鸟的图片进行赋值
		self.mask_wing_up = pygame.mask.from_surface(self.wing_up)
		self.mask_wing_mid = pygame.mask.from_surface(self.wing_mid)
		self.mask_wing_down = pygame.mask.from_surface(self.wing_down)
		self.inital_speed = 0 #鸟向上的初速度
		self.level = level #鸟的初始等级
		self.score = 0 #鸟的初始分数为 0

	def update(self,t):#计算鸟在下一点的新坐标并更新
		y_ = self.inital_speed*t+0.5*self.sink_gravity*t*t
		if self.inital_speed<=0.3:
			self.inital_speed = self.inital_speed +self.sink_gravity*t
		self.y+=y_   #在主函数里计算时间

	@property
	def image(self):
		if pygame.time.get_ticks()%400>=120:
			return self.wing_up
		elif pygame.time.get_ticks()%400>=280:
			return self.wing_mid
		else:
			return self.wing_down
	@property
	def mask(self):
		if pygame.time.get_ticks()%400>=120:
			return self.mask_wing_up
		elif pygame.time.get_ticks()%400>=280:
			return self.mask_wing_mid
		else:
			return self.mask_wing_down

	@property
	def rect(self):
		return Rect(self.x,self.y,Bird.width,Bird.height)



class Pipe(pygame.sprite.Sprite):
	width = PIPE_WIDTH
	pipe_head_height = PIPE_HEAD_HEIGHT
	add_time = ADD_TIME

	def __init__(self,pipe_head_image,pipe_body_image):
		super(Pipe, self).__init__()
		self.x = float(BK_WIDTH-1)
		self.score_count = False
		self.image = pygame.Surface((Pipe.width,BK_HEIGHT),SRCALPHA)#创建一个surface 我理解为能画到窗口上的对象
		# #意为创建一个有ALPHA 通道的surface 如果需要透明就需要这个选项
		self.image.convert()
		self.image.fill((0,0,0,0))#前三位是颜色  最后一位是透明度
		total_pipe_length = TOTAL_PIPE_BODY

		self.bottom_length = randint(int(0.1*total_pipe_length),int(0.8*total_pipe_length))#用于生成指定范围内的整数
		self.top_length = total_pipe_length-self.bottom_length

		for i in range(1,self.bottom_length+1):
			pos = (0,BK_HEIGHT - i)
			self.image.blit (pipe_body_image,pos)#用重叠的技术画出来管子

		bottom_head_y = BK_HEIGHT - self.bottom_length-self.pipe_head_height  #求出管子头的长度
		bottom_head_pos = (0,bottom_head_y)
		self.image.blit(pipe_head_image,bottom_head_pos)#画管子

		for i in range(-PIPE_HEIGHT,self.top_length-PIPE_HEIGHT):
			pos = (0,i)
			self.image.blit(pipe_body_image,pos)
		top_head_y = self.top_length
		self.image.blit(pipe_head_image,(0,top_head_y))

		self.mask = pygame.mask.from_surface(self.image)
	@property
	def rect(self):
		return Rect(self.x,0,Pipe.width,PIPE_HEIGHT)
	@property
	def visible(self):
		return -Pipe.width<self.x<BK_WIDTH

	def update(self,delta_frames=1):
		self.x-=BK_MOVE_SPEED*frames_to_msec(delta_frames)

	def collides(self,bird):
		return pygame.sprite.collide_mask(self,bird)


def change_add_time():
	Pipe.add_time= int( (Pipe.add_time*PIPE_RATE) /100)*100
#改变管子的增加时间


#石头具有速度 位置等不同属性
#起始的x属性为固定值 y随机 速度在一定范围内随机
class Stone(pygame.sprite.Sprite):
	add_time  = STONE_ADD_TIME
	width = STONE_WIDTH
	height = STONE_HEIGHT
	def __init__(self,image):
		super(Stone, self).__init__()
		self.x =BK_WIDTH-5
		self.y = randint(1,int(0.95*BK_HEIGHT))
		self.speed = uniform(0.1 ,0.5)
		self.stone_image = image
		self.mask_image = pygame.mask.from_surface(self.image)

	@property
	def rect(self):
		return Rect(self.x,self.y,self.width,self.height)
	@property
	def image(self):
		return self.stone_image

	@property
	def mask(self):
		return self.mask_image

	def update(self,frame = 1):
		self.x -= int(self.speed*frames_to_msec(frame))

	def collides(self, b):
		return pygame.sprite.collide_mask(self, b)

	def visible(self):
		return -self.width<self.x<BK_WIDTH


#返回每关需要达到的通关分数
def level_goal(bird):
	return bird.level*BIRD_INIT_SCORE

#载入图片
def load_image(img_file_name):
	file_name = os.path.join(".","images",img_file_name)#进行路径字符串的合并
	img = pygame.image.load(file_name)
	img.convert()
	return img

#根据所在的等级返回需要的背景名
def search_bk(bird):
	return "bk"+str(bird.level)

img_x = load_image('backgroundx.png')#加载背景图像
def load_images():
    #加载所有游戏需要用到的图像
        #上面写了这个函数下面就用了起来  join用于分隔符和元组的拼接  os.path.join 用于路径的顺序拼接
    return {'bk1': load_image('background.png'),
			 'bk2':load_image("background2.png"),
			"bk3":load_image("background3.png"),
			"bk4":load_image("background4.png"),
			"bk5":load_image("background5.png"),
			"bk6":load_image("background6.png"),
			'stone':load_image('stone.png'),
			'bullet': load_image('bullet.png'),
            'pipe-end': load_image('pipe_end.png'),
            'pipe-body': load_image('pipe_body.png'),
			'f_u': load_image('fenghuang_up.png'),
			'f_m': load_image('fenghuang_mid.png'),
			'f_w': load_image('fenghuang_down.png'),
            'bird-wingup': load_image('bird_wing_up.png'),
			'bird-wingmid': load_image('bird_wing_mid.png'),
            'bird-wingdown': load_image('bird_wing_down.png')}

def frames_to_msec(frames,fps=FPS):
	return 1000.0*frames/fps   #难道限制的意思就是我可以限制图片出来的时间

def msec_to_frames(milliseconds, fps=FPS):
    return fps * milliseconds / 1000.0#转化成对应的帧数
    #转化成每秒的相应的帧数


def game_loop():
	pygame.mixer.music.play(-1)
	pygame.display.set_caption("Flappy Bird")
	clock = pygame.time.Clock()#创建一个时钟对象
	images = load_images()#建立所有需要的图像字典

	bird = Bird(20,BK_HEIGHT//2,1,(images[a_i],images[b_i] ,images[c_i]))
	score_font = pygame.font.SysFont(None,50,bold=True)#名字 大小  粗体  建立画笔  用于记录 分数
	score_font2 = pygame.font.SysFont(None, 40, bold=True)  # 名字 大小  粗体  建立画笔  用于记录 分数
	score_font3 = pygame.font.SysFont(None, 70, bold=True)  # 名字 大小  粗体  建立画笔  用于记录 分数
	pipes = deque()

	stones =pygame.sprite.Group()#将石头新建为一个精灵组
	bullets =pygame.sprite.Group()#将子弹新建为一个精灵组

	pause = done = False
	frames=0

	while not done :#当没有按下中止键
		clock.tick(FPS)
		if not (pause or frames%msec_to_frames(Pipe.add_time)):#如果没有按下暂停 或者满足新生成柱子的条件
			pp=Pipe(images['pipe-end'], images['pipe-body'])
			pipes.append(pp)#生成新管子 并加入队列

		if not (pause or frames%msec_to_frames(Stone.add_time)or bird.level<STONE_LEVEL):
			ss = Stone(images["stone"])
			stones.add(ss) #加入新生成的石头

		#判断发生了什么事件进行相应的处理
		for e in pygame.event.get():
			if e.type == QUIT:
				done = True
				break
			elif e.type == KEYUP :
				if  e.key == K_p:
					pause = not pause
				elif e.key ==K_d:#发射子弹
					bb=Bullet(bird,images["bullet"])
					bullets.add(bb)
				elif e.key ==K_s or e.key == K_SPACE:
					bird.inital_speed = INITAL_SPEED


			elif e.type == MOUSEBUTTONUP:
				bird.inital_speed =INITAL_SPEED

			# 重新更新时间
			# 使小鸟又进入相应的运动的开始
		if pause:
			continue  # 这个时段什么都不做

		pygame.sprite.groupcollide(stones,bullets,True,True,pygame.sprite.collide_mask)
		pipe_collision = any(p.collides(bird) for p in pipes)
		stone_collision = any(s.collides(bird) for s in stones)

		if pipe_collision:
			pygame.mixer.music.stop()
			done = True
			pygame.mixer.Sound.play(music_lose, -1)
			time.sleep(3.5)
			pygame.mixer.Sound.stop(music_lose)
			time.sleep(0.1)

		if stone_collision:
			pygame.mixer.music.stop()
			pygame.mixer.Sound.play(music_lose, -1)
			time.sleep(3.5)
			pygame.mixer.Sound.stop(music_lose)
			time.sleep(0.1)
			done = True
		if 0>=bird.y or bird.y>BK_HEIGHT-Bird.height:
			done = True
			pygame.mixer.music.stop()
			pygame.mixer.Sound.play(music_lose, -1)
			time.sleep(3.5)
			pygame.mixer.Sound.stop(music_lose)
			time.sleep(0.1)


		screen.blit(images[search_bk(bird)], (0, 0))#画背景墙 这种是分开两张的

		while pipes and not pipes[0].visible:
			pipes.popleft()#当队列不为空  且管子 0 已经不可见的时候
		for s in stones:#删除看不见的石头
			if  not s.visible():
				del s
		for b in bullets:#删除看不见的子弹
			if not b.visible():
				del b


		for p in pipes:
			p.update()
			screen.blit(p.image,p.rect)#在指定的位置 画柱子
		for s in stones:
			s.update()
			screen.blit(s.image,s.rect)

		for b in bullets:
			b.update()
			screen.blit(b.bullet,b.rect)

		for p in pipes:
			if bird.x>p.x+Pipe.width and not p.score_count:  #当柱子超过了鸟的位置并且柱子还没有被计分
				bird.score+=1
				p.score_count = True

		sl = score_font.render("level:",True,(255,255,255))
		sc = score_font.render("score:",True,(255,255,255))
		sl2 = score_font2.render(str(bird.level),True,(255,255,255))
		sc2 = score_font2.render(str(bird.score),True,(255,255,255))
		screen.blit (sc,(BK_WIDTH-170,20))
		screen.blit(sl, (BK_WIDTH - 320, 20))
		screen.blit(sc2, (BK_WIDTH - 50, 27))
		screen.blit(sl2, (BK_WIDTH - 210, 27))

		bird.update(frames_to_msec(1))#计算一帧所需要的时间
		screen.blit(bird.image,bird.rect)

		pygame.display.flip()#绘制图像到屏幕
		if bird.score >= level_goal(bird):#如果已经达到了通关分数
		#升入下一级  首先要初始化所有变量#清空柱子#改变等级
			change_add_time()
			pipes.clear()
			stones.empty()
			bullets.empty()
			bird.level += 1  # 分数先暂不做清空后续再加入吧
			if bird.level<=6:
				s3 = score_font3.render("Next   Level", True, (255, 255, 255))
				screen.blit(s3, (BK_WIDTH//2-150, BK_HEIGHT//2-50))
				pygame.display.flip()
				time.sleep(2)
			if bird.level >6:
				s3 = score_font3.render("You   Win!", True, (255, 255, 255))
				screen.blit(s3, (BK_WIDTH // 2 - 150, BK_HEIGHT // 2 - 50))
				pygame.display.flip()
				time.sleep(2)
				exit()
		frames+= 1
	pygame.mixer.music.stop()

	Pipe.add_time = ADD_TIME#再次初始化柱子的速度
	main()


def quit_but():
	pygame.quit()
	exit()


def buttons(x, y, w, h, color, color2, text,action,list=[]):
	mouse_position = pygame.mouse.get_pos()
	click = pygame.mouse.get_pressed()
	if x+w > mouse_position[0] > x and y+h > mouse_position[1] > y:
		color = color2
		#get_pressed  只返回鼠标三个键是否被按过的状态 不会分辨它是在哪里被按的
		if click[0]== 1 and action != None:
			pygame.mixer.Sound.play(music1, -1)
			time.sleep(0.215)
			pygame.mixer.Sound.stop(music1)
			if list:
				action(list)
			else:
				action()

	pygame.draw.rect(screen, color, (x, y, w, h))
	# font = pygame.font.SysFont('comicsansms', 25)
	TextSurf = font.render(text, True, (0,0,0))
	TextRect = TextSurf.get_rect()
	TextRect.center = ((x + (w / 2)), (y + (h / 2)))
	screen.blit(TextSurf, TextRect)
	pygame.display.update()


def setting():
	# img = load_image('backgroundx.png')
	screen.blit(img_x, (0, 0))  # 画背景墙 这种是分开两张的
	pygame.display.flip()
	while True:
		for event in pygame.event.get():
			if event.type==pygame.QUIT:
				exit()

		buttons(100, 200, BUTTON_WIDTH, BUTT0N_HEIGHT,(255, 0, 0), (170, 0, 0), 'easy',seteasy,[0.19,2500,int(5 / 11 * BK_HEIGHT),0.97,5,6])  # 绘制图标  进行事件
		buttons(400, 200, BUTTON_WIDTH, BUTT0N_HEIGHT,(0, 255, 0), (0, 170, 0), 'normal', seteasy,[0.19,2500,int(3 / 5 * BK_HEIGHT),0.96,7,4])  # 绘制图标  进行事件
		buttons(700 ,200, BUTTON_WIDTH, BUTT0N_HEIGHT,(0, 0, 255), (0, 0, 160),'hard',seteasy,[0.21,1300,int(9 / 14 * BK_HEIGHT),0.96,2,1])  # 绘制图标  进行事件
		buttons(700, 550, BUTTON_WIDTH, BUTT0N_HEIGHT, (0, 0, 255), (0, 0, 160), 'back', main)  # 绘制图标  进行事件
		buttons(100, 400, BUTTON_WIDTH, BUTT0N_HEIGHT, (255, 0, 0), (170, 0, 0), 'huo lie niao',little_bird,["f_u","f_m","f_w"])  # 绘制图标  进行事件
		buttons(400, 400, BUTTON_WIDTH, BUTT0N_HEIGHT, (0, 255, 0), (0, 170, 0),  'xiao niao',little_bird,["bird-wingup","bird-wingmid","bird-wingdown"])  # 绘制图标  进行事件
		# buttons(700, 400, BUTTON_WIDTH, BUTT0N_HEIGHT, (0, 0, 255), (0, 0, 160), 'back', main)  # 绘制图标  进行事件


def main():
	screen.blit(img_x, (0, 0))  # 画背景墙 这种是分开两张的
	pygame.display.flip()
	while True:
		for event in pygame.event.get():
			if event.type==pygame.QUIT:
				exit()
		buttons((BK_WIDTH-BUTTON_WIDTH)//2,(BK_HEIGHT-BUTT0N_HEIGHT-100)//2,BUTTON_WIDTH,BUTT0N_HEIGHT,(0,255,0),(0,170,0),'Play!',game_loop)#绘制图标  进行事件
		buttons((BK_WIDTH - BUTTON_WIDTH) // 2, (BK_HEIGHT - BUTT0N_HEIGHT + 100) // 2, BUTTON_WIDTH, BUTT0N_HEIGHT,(0, 0, 255), (0, 0, 160), 'setting', setting)  # 绘制图标  进行事件
		buttons((BK_WIDTH - BUTTON_WIDTH) // 2, (BK_HEIGHT - BUTT0N_HEIGHT + 300) // 2, BUTTON_WIDTH, BUTT0N_HEIGHT,(255, 0, 0), (170, 0, 0), 'Quit', quit_but)

if __name__ =="__main__":
   main()





















