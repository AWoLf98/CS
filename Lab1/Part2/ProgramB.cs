using System;
using System.IO;
using System.Text;


namespace Lab1b
{
    class Program
    {
        static void Main(string[] args)
        {
            string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            string file = "TwoBZIP2File.BZ2";
            string writeToFile = "TwoBZIP2File-base64.TXT";

            StringBuilder result = new StringBuilder();
            using (BinaryReader readFile = new BinaryReader(new FileStream(file, FileMode.Open, FileAccess.Read)))
                while (true)
                {
                    int[] indices = new int[4];
                    byte[] bytes = readFile.ReadBytes(3);

                    if (bytes.Length == 0)
                        break;

                    for (int i = 0; i < bytes.Length * 8; i++)
                    {
                        if ((bytes[i / 8] & (1 << (7 - i % 8))) != 0)
                            indices[i / 6] |= (1 << (5 - i % 6));
                        if (i % 6 == 5 || i == bytes.Length * 8 - 1)
                            result.Append(base64[indices[i / 6]]);
                    }
                    if (bytes.Length == 2)
                        result.Append("=");
                    else if (bytes.Length == 1)
                        result.Append("==");
                }

            string base64ResultWithBuiltInFunc = Convert.ToBase64String(File.ReadAllBytes(file));
            if (result.ToString() == base64ResultWithBuiltInFunc)
                using (StreamWriter writer = new StreamWriter(writeToFile, append: false, encoding: Encoding.UTF8))
                    writer.WriteLine(result);

            Console.WriteLine("END");
            Console.ReadLine();
        }
    }
}