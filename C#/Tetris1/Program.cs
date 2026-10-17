namespace Tetris1
{
    internal class Program
    {
        static void Main(string[] args)
        {

            StructArray impl4 = new StructArray();
            impl4.Run();

            //ClassArray impl3 = new ClassArray();
            //impl3.Run();

            //JaggedArray impl2 = new JaggedArray();
            //impl2.Run();

            //MultidimensionalArray impl1 = new MultidimensionalArray();
            //impl1.Run();








            int[] arr1 = new int[10];
            arr1[0] = 1;
            arr1[5] = 3;

            Console.WriteLine(arr1.Length);

            // -----

            int[][] arr2 = new int[10][];
            arr2[0] = new int[10];
            arr2[0][1] = 32;

            // -----


            int[,] arr3 = new int[10, 3];
            arr3[1, 2] = 34;
            int len = arr3.Length;
            int len2 = arr2.GetLength(0);
            int len3 = arr2.GetLength(1);




        }
    }
}
