# здесь подключаются модули
import pygame
 
# здесь определяются константы, классы и функции
FPS = 60
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (125, 125, 125)
LIGHT_BLUE = (64, 128, 255)
GREEN = (0, 200, 64)
YELLOW = (225, 225, 0)
PINK = (230, 50, 230)
 
# здесь происходит инициация, создание объектов и др.
pygame.init()
clock = pygame.time.Clock()
 
sc = pygame.display.set_mode((300, 200))
sc.fill(GRAY)
 
# здесь будут рисоваться фигуры

pygame.draw.rect(sc, (255, 255, 255), (20, 20, 100, 75))
pygame.draw.rect(sc, (64, 128, 255), (150, 20, 100, 75), 8)
pygame.display.update()
 
 
# главный цикл
while True:
 
    # задержка
    clock.tick(FPS)
 
    # цикл обработки событий
    for i in pygame.event.get():
        if i.type == pygame.QUIT:
            exit()
 
    # --------
    # изменение объектов и многое др.
    # --------
 
    # обновление экрана
    pygame.display.update()