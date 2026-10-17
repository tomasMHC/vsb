using System;
using System.IO;
using System.Threading;

namespace MazeProject
{
    public class JaggedArray
    {
        private const char WALL = '#';
        private const char EMPTY = ' ';
        private const char PLAYER = '@';

        private int playerX;
        private int playerY;

        public void Run()
        {
            Console.CursorVisible = false;

            // 1) Načtení mapy
            char[][] map = LoadMap("mapa.txt");

            // 2) Přidání figurky
            AddPlayer(map, 1, 1);

            // 3) Nekonečná smyčka
            while (true)
            {
                MainLoop(map);
                Thread.Sleep(500);
            }
        }

        private char[][] LoadMap(string file)
        {
            string[] lines = File.ReadAllLines(file);
            char[][] map = new char[lines.Length][];

            for (int i = 0; i < lines.Length; i++)
            {
                map[i] = lines[i].ToCharArray();
            }

            return map;
        }

        private void AddPlayer(char[][] map, int x, int y)
        {
            if (map[y][x] == '0' || map[y][x] == EMPTY)
            {
                playerX = x;
                playerY = y;
                map[y][x] = PLAYER;
            }
        }

        private void MainLoop(char[][] map)
        {
            ClearConsole();

            // 1) Posun figurky
            MovePlayer(map);

            // 2) Vykreslení scény
            Draw(map);
        }

        private void MovePlayer(char[][] map)
        {
            int[][] dirs = new int[][]
            {
                new[]{ 1, 0 },
                new[]{ -1, 0 },
                new[]{ 0, 1 },
                new[]{ 0, -1 }
            };

            Random rnd = new Random();
            int[] d = dirs[rnd.Next(dirs.Length)];

            int nx = playerX + d[0];
            int ny = playerY + d[1];

            // Kontrola hranic + volného pole
            if (ny >= 0 && ny < map.Length &&
                nx >= 0 && nx < map[ny].Length &&
                map[ny][nx] != WALL)
            {
                map[playerY][playerX] = EMPTY;
                playerX = nx;
                playerY = ny;
                map[playerY][playerX] = PLAYER;
            }
        }

        private void Draw(char[][] map)
        {
            for (int y = 0; y < map.Length; y++)
            {
                for (int x = 0; x < map[y].Length; x++)
                {
                    char c = map[y][x];

                    if (c == WALL)
                    {
                        Console.ForegroundColor = ConsoleColor.Gray;
                        Console.Write("\u2588\u2588");
                    }
                    else if (c == PLAYER)
                    {
                        Console.ForegroundColor = ConsoleColor.Yellow;
                        Console.Write("@@");
                    }
                    else
                    {
                        Console.Write("  ");
                    }
                }
                Console.WriteLine();
            }
        }

        private void ClearConsole()
        {
            Console.Clear();
            Console.Write("\x1b[3J\x1b[H\x1b[2J");
            Console.SetCursorPosition(0, 0);
            Console.ForegroundColor = ConsoleColor.White;
            Console.BackgroundColor = ConsoleColor.Black;
        }
    }
}
