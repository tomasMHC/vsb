using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tetris1
{
    internal class JaggedArray
    {
        public void Run()
        {
            bool[][] stage = new bool[20][];
            for (int i = 0; i < stage.Length; i++) {
                stage[i] = new bool[10];
            }

            CreateT(1, 0, stage);

            while (true)
            {
                MainLoop(stage);
                Thread.Sleep(1000);
            }
        }


        private void MainLoop(bool[][] stage)
        {
            Console.BackgroundColor = ConsoleColor.Black;
            Console.Clear();
            Print(stage);

            Shift(stage);
        }

        private void Shift(bool[][] stage)
        {
            for (int r = stage.Length - 1; r > 0; r--)
            {
                stage[r] = stage[r - 1];
            }
            stage[0] = new bool[stage[0].Length];
        }



        private void Print(bool[][] stage)
        {
            Console.BackgroundColor = ConsoleColor.Gray;
            Console.ForegroundColor = ConsoleColor.Red;

            for (int r = 0; r < stage.Length; r++)
            {
                for (int c = 0; c < stage[r].Length; c++)
                {
                    if (stage[r][c])
                    {
                        Console.Write("\u2588\u2588");
                    }
                    else
                    {
                        Console.Write("  ");
                    }
                }
                Console.WriteLine();
            }
        }


        private void CreateT(int x, int y, bool[][] stage)
        {
            stage[y][x] = true;
            stage[y][x + 1] = true;
            stage[y][x + 2] = true;

            stage[y + 1][x + 1] = true;
        }


    }
}
