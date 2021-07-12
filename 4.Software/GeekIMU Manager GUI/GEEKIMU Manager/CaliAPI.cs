using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace DM_CalibrationTools
{
    struct Quaternion{
        public float w, x, y, z;
    };
    struct mVector3
    {
        public float x, y, z;
    };
	struct MagCaliParam
	{
		public float xOffset;
        public float yOffset;
		public float zOffset;
		public float xScale;
		public float yScale;
		public float zScale;
	};
    [StructLayoutAttribute(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    class CaliAPI
    {

        [DllImport("libDM.dll", EntryPoint = "Init", CallingConvention = CallingConvention.Cdecl)]
        public extern static int InitCaliAPI([MarshalAs(UnmanagedType.LPStr)]string devpath);

        [DllImport("libDM.dll", EntryPoint = "CheckDevice", CallingConvention = CallingConvention.Cdecl)]
        public extern static int CheckDevice();

        [DllImport("libDM.dll", EntryPoint = "GyroCali", CallingConvention = CallingConvention.Cdecl)]
        public extern static int GyroCali();

        [DllImport("libDM.dll", EntryPoint = "GetGyroCali", CallingConvention = CallingConvention.Cdecl)]
        public extern static mVector3 GetGyroCali();

        [DllImport("libDM.dll", EntryPoint = "GetMagCali", CallingConvention = CallingConvention.Cdecl)]
        public extern static MagCaliParam GetMagCali();

        [DllImport("libDM.dll", EntryPoint = "MagCali", CallingConvention = CallingConvention.Cdecl)]
        public extern static int MagCali();

        [DllImport("libDM.dll", EntryPoint = "FinishMagCali", CallingConvention = CallingConvention.Cdecl)]
        public extern static int FinishMagCali();

        [DllImport("libDM.dll", EntryPoint = "SetMagCali", CallingConvention = CallingConvention.Cdecl)]
        public extern static int SetMagCali(float x, float y, float z, float x0, float y0, float z0);

        [DllImport("libDM.dll", EntryPoint = "CalculateMagParam", CallingConvention = CallingConvention.Cdecl)]
        public extern static MagCaliParam CalculateMagParam();

        [DllImport("libDM.dll", EntryPoint = "GetPoint", CallingConvention = CallingConvention.Cdecl)]
        public extern static mVector3 GetPoint();

        [DllImport("libDM.dll", EntryPoint = "GetEulerianAngle", CallingConvention = CallingConvention.Cdecl)]
        public extern static mVector3 GetEulerianAngle();

        [DllImport("libDM.dll", EntryPoint = "Correction", CallingConvention = CallingConvention.Cdecl)]
        public extern static int Correction();

        [DllImport("libDM.dll", EntryPoint = "GetQuaternion", CallingConvention = CallingConvention.Cdecl)]
        public extern static Quaternion GetQuaternion();

    }
}
