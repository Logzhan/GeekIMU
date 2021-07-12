using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DM_CalibrationTools
{
    class txtreader
    {
        HashSet<double[]> hs;
        string filepath;
        public txtreader(string s)
        {
            if(File.Exists(s))
            {
                filepath = s;
            }
            hs = new HashSet<double[]>();
        }
        public void GetData()
        {

            // StreamReader sr = File.OpenText("task.txt",System.Text.Encoding.Default);
            if (!File.Exists(System.AppDomain.CurrentDomain.BaseDirectory + "data.txt"))
            {
                //StreamWriter sw = File.CreateText("task.txt");//在程序所在文件夹创建txt文件
                //sw.Close();
            }
            FileStream fs = new FileStream("data.txt", FileMode.Open, FileAccess.Read, FileShare.Read);
            StreamReader sr = new StreamReader(fs, System.Text.Encoding.UTF8);
            //string[] parameters = sr.ReadLine().ToString().Split('|');
            int i = 0;
            
 
            ArrayList arr = new ArrayList();
            while (true)
            {
                string cmdtempstr = sr.ReadLine();
                if (cmdtempstr == null)
                {
                    break;
                }
                i++;
                string[] strarr = cmdtempstr.Split(' ');
                ////add  into arr to be finished 
                double[] v = { double.Parse(strarr[0]), double.Parse(strarr[1]), double.Parse(strarr[2]) };
                arr.Add(v);
                hs.Add(v);
            }
            sr.Close();
            fs.Close();

        }
            public double[][] getArr()
            {
                double[][] result=new double [hs.Count][];
                hs.CopyTo(result);
                return result;
            }
            public HashSet<double[]> getHashset()
            {
                return hs;
            }
        public void show()
        {
            for(int i = 0;i<hs.Count;i++)
            {
                Debug.WriteLine(hs.ElementAt(i)[0].ToString() + " " + hs.ElementAt(i)[1].ToString() + " " + hs.ElementAt(i)[2].ToString());
            }
        }

        public static void  saveData(HashSet<double[]> hs)
        {
            StreamWriter sw = File.CreateText("data.txt");//在程序所在文件夹创建txt文件
            
            foreach (var d in hs)
            {
                sw.WriteLine(((float)d[0]).ToString() + " " + ((float)d[1]).ToString() + " " + ((float)d[2]).ToString());
            }
            sw.Close();
            Debug.WriteLine("保存成功！");
        }
    }
}
