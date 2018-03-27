using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Collections;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            int num = 4;
            string txtFile = "";           
            while (num != 0)
            {
                Console.WriteLine("Оберіть файл для переірки, введіть цифру і нажміть ентер (1-Перший файл, 2-Другий файл, 3-Третій файл і 0 якщо хочете завершити).");
                num = Int32.Parse(Console.ReadLine());
                switch (num)
                {
                    case 1: txtFile = "OneTxtFile.TXT"; break;
                    case 2: txtFile = "TwoTxtFile.TXT"; break;
                    case 3: txtFile = "ThreeTxtFile.TXT"; break;
                }
                if (num != 0)
                {
                    StreamReader readFile = File.OpenText(txtFile);
                    string symbolALL = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZzАаБбВвГгҐґДдЕеЄєЖжЗзИиІіЇїЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЬьЮюЯя0123456789 '\\\"!@#№$%^&*()_+-=/,.<>?[]{}~ЁЫ";
                    Dictionary<char, double> charDictionary = new Dictionary<char, double>();

                    FillDictionary(charDictionary, symbolALL);
                    EvalChar(charDictionary, readFile);
                    EvalFric(charDictionary, symbolALL);
                    Console.WriteLine("Частота появи символів в тексті:");
                    foreach (char c in charDictionary.Keys)
                        if (c != 'Ё' && c != 'Ы' && c != 'Э')
                        {

                            Console.Write(c);
                            Console.WriteLine(": " + charDictionary[c]);
                        }
                        else if (c == 'Ё')
                        {
                            Console.WriteLine("Перенесення строки: " + charDictionary[c]);
                        }
                        else if (c == 'Ы')
                        {
                            Console.WriteLine("Символів поза алфавітом: " + charDictionary[c]);
                        }

                    double en = EvalEntropi(charDictionary, symbolALL);
                    Console.WriteLine("Ентропія: " + en);
                    Console.WriteLine("Кількість інформації: " + en * charDictionary['Э'] + "bit (" + (en * charDictionary['Э']) / 8 + "byte)");
                    Console.WriteLine("Довжна файлу: " + readFile.BaseStream.Length + "byte");
                    readFile.Close();
                }
            }
        }
        static void FillDictionary(Dictionary<char, double> chars, string symbolALL)
        {
            foreach (char c in symbolALL)
                chars.Add(c, 0);

            chars.Add('Э', 0);

        }
        static void EvalChar(Dictionary<char, double> chars, StreamReader readFile)
        {
            while (!readFile.EndOfStream)
            {
                string symbol = readFile.ReadLine();
                foreach (char c in symbol)
                {
                    try
                    {
                        chars[c]++;
                    }
                    catch (Exception)
                    {
                        chars['Ы']++;
                    }
                    finally { chars['Э']++; }
                }
                chars['Ё']++;
                chars['Э']++;
            }

        }
        static void EvalFric(Dictionary<char, double> charDictionary, string symbolALL)
        {
            foreach (char c in symbolALL)
                charDictionary[c] = charDictionary[c] / charDictionary['Э'];
        }
        static double EvalEntropi(Dictionary<char, double> charDictionary, string symbolALL)
        {
            double entropi = 0.0;
            foreach (char c in symbolALL)
                if (charDictionary[c] != 0)
                {
                    entropi -= charDictionary[c] * Math.Log(charDictionary[c], 2);
                }
            return entropi;
        }
    }
}