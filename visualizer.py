import os
from collections import defaultdict

import numpy as np
import pygame

media_path = 'media/'
heroes_path = media_path + 'heroes/'
rooms_path = media_path + 'rooms/'

WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
GRAY = (125, 125, 125)
LIGHT_BLUE = (64, 128, 255)
GREEN = (0, 200, 64)
YELLOW = (225, 225, 0)
PINK = (230, 50, 230)
TRANSPARENT = (255, 0, 255)

width, height = 800, 800


class Graph():
    def __init__(self):
        self.start_point = None
        self.end_point = None
        self.max = {
            'x': 0,
            'y': 0
        }
        self.min = {
            'x': 10000000,
            'y': 10000000
        }
        self.ants = 0
        self.points = dict()
        self.edges = defaultdict(list)
        self.line = self.read_points()
        self.line = self.read_edges(self.line)
        self.zero = (self.min['x'], self.min['y'])
        self.scale = None

    def __repr__(self):
        return f'Graph with {len(self.points)} points and {len(self.edges)} edges'

    def read_points(self):
        start_flag = 0
        self.ants = int(input())

        line = input()
        while 1:
            if line.startswith('##start'):
                start_flag = 1
            if line.startswith('#'):
                line = input()
                continue
            if '-' in line:
                break
            coords = [int(val) if i in [1, 2] else val for i, val in
                      enumerate(line.split())]
            self.points[coords[0]] = coords[1:]
            if start_flag:
                self.start_point = coords[0]
                start_flag = 0
            self.max['x'] = max(coords[1], self.max['x'])
            self.max['y'] = max(coords[2], self.max['y'])
            self.min['x'] = min(coords[1], self.min['x'])
            self.min['y'] = min(coords[2], self.min['y'])
            line = input()

        return line

    def read_edges(self, line):

        while 1:
            if line.startswith('#'):
                line = input()
                continue
            if line == '':
                break
            points = line.split('-')
            self.edges[points[0]].append(points[1])
            line = input()

        return line

    def transform_point(self, point, bias=-16):
        return [
            (point[0] - self.zero[0] + 16 / self.scale['x']) * self.scale[
                'x'] + bias,
            (point[1] - self.zero[1] + 16 / self.scale['y']) * self.scale[
                'y'] + bias
        ]


def place_rooms(graph, img_object, screen):
    # print(graph.points)
    for point_1_name in graph.edges:
        point_1 = graph.points[point_1_name]
        for point_2_name in graph.edges[point_1_name]:
            point_2 = graph.points[point_2_name]

            pygame.draw.aaline(screen, BLACK,
                               graph.transform_point(point_1, bias=0),
                               graph.transform_point(point_2, bias=0))

    for point in graph.points:
        screen.blit(img_object, graph.transform_point(graph.points[point]))


def load_files(heroes, rooms):
    for hero in os.listdir(heroes_path):
        hero_img = pygame.image.load(heroes_path + hero)
        hero_img.set_colorkey(WHITE)
        heroes[hero.split('.')[0]] = hero_img
    for room in os.listdir(rooms_path):
        room_img = pygame.image.load(rooms_path + room)
        room_img.set_colorkey(WHITE)
        rooms[room.split('.')[0]] = room_img


def init_view(graph, room):
    pygame.init()
    pygame.display.set_caption("lemin")
    width_, height_ = width - 32, height - 32
    graph.scale = {
        'x': width_ / (graph.max['x'] - graph.min['x']) if (graph.max['x'] -
                                                            graph.min[
                                                                'x']) != 0 else 1,
        'y': height_ / (graph.max['y'] - graph.min['y']) if (graph.max['y'] -
                                                             graph.min[
                                                                 'y']) != 0 else 1,
    }

    screen = pygame.display.set_mode((width, height))

    screen.fill(WHITE)
    place_rooms(graph, room, screen)
    pygame.display.update()
    pygame.time.delay(500)
    return screen


def points_dif(p1, p2):
    print(p1, p2)
    return (p1[0] - p2[0], p1[1] - p2[1])


def launch_ants(graph, screen, hero, room_img):
    line = input()
    ants = defaultdict(list)
    fps = 60

    while 1:
        ants_steps = dict()
        if line.startswith('#'):
            line = input()
            continue
        moves = line.split()
        for move in moves:
            ant, room = move.split('-')
            ant = ant[1:]
            if len(ants[ant]) == 0:
                ants[ant].append(graph.start_point)
            ants[ant].append(room)
            if len(ants[ant]) == 2:
                ants_steps[ant] = points_dif(
                    np.divide(graph.transform_point(graph.points[ants[ant][0]]),
                              fps),
                    np.divide(graph.transform_point(graph.points[ants[ant][1]]),
                              fps)
                )
                ants[ant].pop(0)
        for frame in range(fps + 1):
            screen.fill(WHITE)
            place_rooms(graph, room_img, screen)
            for ant in ants:
                if ants_steps.get(ant):
                    screen.blit(hero, np.add(
                        graph.transform_point(graph.points[ants[ant][0]]),
                        np.multiply(fps - frame, ants_steps[ant])
                    ))
                else:
                    screen.blit(hero, graph.transform_point(
                        graph.points[ants[ant][0]]))
            pygame.display.update()
            pygame.time.delay(1000 // fps)

        try:
            line = input()
        except Exception:
            return


def main():
    heroes = dict()
    rooms = dict()
    graph = Graph()
    load_files(heroes, rooms)
    room = rooms['death_star']
    hero = heroes['hero2']
    screen = init_view(graph, room)
    launch_ants(graph, screen, hero, room)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    main()

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
