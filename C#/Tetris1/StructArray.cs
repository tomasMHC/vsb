using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Tetris1
{
  

    internal class StructArray
    {
        internal struct Brick
        {
            public int X;
            public int Y;
        }

        internal struct CompositeBrick
        {
            public Brick[] Bricks;
            public int X;
            public int Y;
        }

        public void Run()
        {
            CompositeBrick[] bricks = new CompositeBrick[2];
            CreateT(0, 1, ref bricks[0]);
            CreateT(4, 5, ref bricks[1]);

            while (true)
            {
                MainLoop(bricks);
                Thread.Sleep(1000);
            }
        }

        private void MainLoop(CompositeBrick[] bricks)
        {
            Console.BackgroundColor = ConsoleColor.Black;
            Console.Clear();
            Print(bricks);

            Shift(bricks);
        }


        private void Shift(CompositeBrick[] bricks)
        {
            for (int i = 0; i < bricks.Length; i++)
            {
                bricks[i].Y++;
            }
        }

        private void Print(CompositeBrick[] bricks)
        {
            for (int i = 0; i < bricks.Length; i++)
            {
                CompositeBrick cp = bricks[i];

                for (int j = 0; j < cp.Bricks.Length; j++)
                {
                    Brick b = cp.Bricks[j];

                    Console.SetCursorPosition((cp.X + b.X) * 2, cp.Y + b.Y);
                    Console.Write("\u2588\u2588");
                }

            }
        }

        private CompositeBrick CreateT(int x, int y, ref CompositeBrick cp)
        {
            Brick[] bricks = new Brick[4];
            bricks[0].X = 0;
            bricks[0].Y = 0;

            bricks[1].X = 1;
            bricks[1].Y = 0;

            bricks[2].X = 2;
            bricks[2].Y = 0;

            bricks[3].X = 1;
            bricks[3].Y = 1;

            cp.Bricks = bricks;

            cp.X = x;
            cp.Y = y;
            return cp;
        }


    }
}
