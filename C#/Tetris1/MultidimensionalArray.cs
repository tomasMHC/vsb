using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tetris1
{
    internal class MultidimensionalArray
    {

        public void Run()
        {
            // sloupce x řádky
            bool[,] stage = new bool[10, 20];

            CreateT(1, 0, stage);

            while (true)
            {
                MainLoop(stage);
                Thread.Sleep(1000);
            }
        }

        private void MainLoop(bool[,] stage)
        {
            Console.BackgroundColor = ConsoleColor.Black;
            Console.Clear();
            Print(stage);

            Shift(stage);
        }


        private void Shift(bool[,] stage)
        {
            for(int r = stage.GetLength(1) - 1; r > 0; r--)
            {
                for(int c = 0; c < stage.GetLength(0); c++)
                {
                    stage[c, r] = stage[c, r - 1];
                }
            }

            for (int c = 0; c < stage.GetLength(0); c++)
            {
                stage[c, 0] = false;
            }
        }

        private void Print(bool[,] stage)
        {
            Console.BackgroundColor = ConsoleColor.Gray;
            Console.ForegroundColor = ConsoleColor.Red;

            for(int r = 0; r < stage.GetLength(1); r++)
            {
                for(int c = 0; c < stage.GetLength(0); c++)
                {
                    if (stage[c, r])
                    {
                        Console.Write("\u2588\u2588");
                    }
                    else
                    {
                        Console.Write("  ");
                    }
                    // Console.Write(stage[c, r] ? "X" : "O");
                }
                Console.WriteLine();
            }
        }

        private void CreateT(int x, int y, bool[,] stage)
        {
            stage[x, y] = true;
            stage[x + 1, y] = true;
            stage[x + 2, y] = true;

            stage[x + 1, y + 1] = true;
        }

    }
}
